#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <signaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int vivant = 1;

/*
 * HANDLERS
 */

void mort(int sig)
{
	vivant = 0;
}

int main(int nb_arg, char *tab_arg[])
{
	char nomprog[128];
	pid_t pid_aire;
	pid_t pid_ver;

	/*----------*/

	/*
      * Capture des parametres
      */
	/* - nom du programme */
	strcpy(nomprog, tab_arg[0]);

	if (nb_arg != 2)
	{
		fprintf(stderr, "Usage : %s <pid aire>\n",
				nomprog);
		exit(-1);
	}

	/* - parametres */
	pid_aire = atoi(tab_arg[1]);

	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());

	pid_ver = getpid();
	printf("\n\n--- Debut ver [%d] ---\n\n", pid_ver);

	//initialisation signal de mort
	struct sigaction action;
	action.sa_handler = mort;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGUSR2, &action, NULL);

	while (vivant)
	{
		//envoi du signal au processus aire
		kill(pid_aire, SIGUSR1);

		//attente pour le prochain tour
		sleep(random() % 10 + 1);
	}

	printf("\n\n--- Arret ver [%d] ---\n\n", pid_ver);

	exit(0);
}
