#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int min(suseconds_t *a, suseconds_t *b)
{
	return *a - *b;
}

int main(int argc, char **argv)
{
	// gestion des arguments
	if (argc < 4)
	{
		printf("Usage : %s <nb_exec> <commande> <nb_proc>\n", argv[0]);
		exit(1);
	}

	int nb_exec = atoi(argv[1]), nb_proc = atoi(argv[3]);
	char commande[50];
	strcpy(commande, argv[2]);

	// initialisation des variables
	struct timeval avant, apres;
	suseconds_t chrono[nb_exec], med, moy[nb_proc], temps_proc[nb_proc];
	int i, j, tubes[nb_proc][2], cr, pid, reussi = 0;
	for (i = 0; i < nb_exec; i++)
	{
		chrono[i] = 0;
	}
	for (i = 0; i < nb_proc; i++)
	{
		moy[i] = 0;
	}

	// benchmark
	for (i = 0; i < nb_proc; i++)
	{
		pipe(tubes[i]);
		switch (fork())
		{
		case -1:
			perror("Erreur fork");
			exit(-1);
		case 0:
			close(tubes[i][0]);
			for (j = 0; j < nb_exec; j++)
			{
				switch (fork())
				{
				case -1:
					perror("Erreur fork");
					exit(-1);
				case 0:
					close(1);
					close(2);
					open("/dev/null", O_RDWR);
					open("/dev/null", O_RDWR);
					execlp(commande, commande, NULL);
					exit(1);
				default:
					gettimeofday(&avant, NULL);
					pid = wait(&cr);
					gettimeofday(&apres, NULL);
					if (cr)
					{
						if (cr >> sizeof(int) / 2)
						{
							printf("Le processus %d s'est arrêté avec le code %d\n", pid, cr >> sizeof(int) / 2);
						}
						else
						{
							printf("Le processus %d a été interrompu par le signal %d\n", pid, cr);
						}
					}
					else // on n'ajoute que les temps des processus qui se sont exécutés sans erreur
					{
						chrono[reussi++] = (apres.tv_sec * 1000000 + apres.tv_usec) - (avant.tv_sec * 1000000 + avant.tv_usec);
					}
				}
			}
			// ici reussi représente le nombre d'exécutions réussies par le processus, med est le temps moyen de ces exécutions
			qsort(chrono, reussi, sizeof(suseconds_t), min);
			med = chrono[reussi / 2];
			write(tubes[i][1], &med, sizeof(suseconds_t));
			exit(0);
		default:
			close(tubes[i][1]);
		}
	}

	// récupération et affichage des résultats
	while (wait(NULL) != -1);
	for (i = 0; i < nb_proc; i++)
	{
		read(tubes[i][0], temps_proc + i, sizeof(suseconds_t));
	}
	/*
	printf("Temps moyens des processus:\nNo proc\tTemps\n");
	*/
	for (i = 0; i < nb_proc; i++)
	{
		if (temps_proc[i])
		{
			// ici reussi représente le nombre de processus qui ont au moins une exécution réussie (donc un temps moyen autre que 0)
			moy[reussi++] = temps_proc[i];
		}
		/*
		printf("%d\t%ld\n", i, moy[reussi]);
		*/
	}
	qsort(moy, reussi, sizeof(suseconds_t), min);
	printf("Temps processus triés:\nIndice\tNo proc\tTemps\n");
	for (i = 0; i < nb_proc; i++)
	{
		for (j = 0; moy[i] != temps_proc[j]; j++);
		if (moy[i])
		{
			printf("%d\t%d\t%ld\n", i, j, moy[i]);
		}
	}
	// ici med est le temps médian de toutes les exécutions de tous les processus
	// selon si le nombre de processus qui au moins une exécution réussie est pair ou impair
	med = reussi % 2 ? moy[reussi / 2] : (moy[reussi / 2] + moy[reussi / 2 - 1]) / 2;
	printf("Temps moyen : %ldµs\n", med);
	return 0;
}
