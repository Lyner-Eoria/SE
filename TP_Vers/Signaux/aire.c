#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>
#include <signaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256];
vers_t *liste_vers;
char marque_new = 'A';
int fd, nbv, case_libre, x_ter, y_ter;
coord_t *coordv;

/*
 * HANDLER
 */

void hand(int sig, siginfo_t *info, void *context){
	ver_t ver;
	int ind_ver;
	if ((ind_ver = vers_pid_seek(liste_vers, info->si_pid)) == -1)
	{
		// création d'un nouveau ver
		ver.marque = marque_new++;
		ver.pid = info->si_pid;
		jeu_ver_initialiser(fd, x_ter, y_ter, &ver);
		vers_ver_add(liste_vers, ver);
	}
	else
	{
		// déplacement du ver
		ver = liste_vers->vers[ind_ver];
		terrain_voisins_rechercher(fd, ver.tete, &coordv, &nbv);
		terrain_case_libre_rechercher(fd, coordv, nbv, &case_libre);
		if (case_libre != -1)
		{
			terrain_marque_ecrire(fd, coordv[case_libre], ver.marque);
			ver.tete = coordv[case_libre];
			liste_vers->vers[ind_ver] = ver;
		}
		else
		{
			// affiche le gagnant (si c'est la fin)
			if (liste_vers->nb == 1)
				printf("Le gagnant est %c", ver.marque);
			// indique au ver qu'il est mort
			vers_ver_del(liste_vers, ind_ver);
			kill(info->si_pid, SIGUSR2);
		}
	}
}

int main(int nb_arg, char *tab_arg[])
{
	char fich_terrain[128];
	pid_t pid_aire;

	/*----------*/

	/*
   * Capture des parametres
   */
	strcpy(Nom_Prog, tab_arg[0]);

	if (nb_arg != 2)
	{
		fprintf(stderr, "Usage : %s <fichier terrain>\n",
				Nom_Prog);
		exit(-1);
	}

	strcpy(fich_terrain, tab_arg[1]);
	pid_aire = getpid();

	/* Affichage du pid pour les processus verDeTerre */
	printf("\n\t-----------------.\n");
	printf("--- pid %s = %d ---\n", Nom_Prog, pid_aire);
	printf("\t-----------------.\n\n");

	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)pid_aire);

	/*----------*/

	printf("\n\t----- %s : Debut du jeu -----\n\n", Nom_Prog);

	// initialisation liste des vers et terrain
	liste_vers = vers_new();
	fd = open(fich_terrain, O_RDWR);
	terrain_dim_lire(fd, &x_ter, &y_ter);

	// masque pour ne pas interrompre l'affichage du terrain
	sigset_t mask_old, mask_new;
	sigemptyset(&mask_new);
	sigaddset(&mask_new, SIGUSR1);

	// initialisation signal des vers
	struct sigaction deplacement;
	sigemptyset(&deplacement.sa_mask);
	deplacement.sa_flags = SA_SIGINFO;
	deplacement.sa_sigaction = hand;

	sigaction(SIGUSR1, &deplacement, NULL);

	do
	{
		sigprocmask(SIG_BLOCK, &mask_new, &mask_old);
		terrain_afficher(fd);
		sigprocmask(SIG_SETMASK, &mask_old, NULL);

		// attente du prochain signal de ver (s'il en reste)
		pause();
	} while (liste_vers->nb);
	close(fd);
	
	printf("\n\n\t----- %s : Fin du jeu -----\n\n", Nom_Prog);

	exit(0);
}
