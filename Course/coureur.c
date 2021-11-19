#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <messages.h>

int boite, type;
const int TIMEOUT = 10;

void hand(int sig)
{
	//abandon
	requete_t msg;
	ack_t rep;
	msg.type = PC_COURSE;
	msg.corps.dossard = type;
	msg.corps.etat = ABANDON;
	msgsnd(boite, &msg, sizeof(corps_requete_t), 0);

	//VERSION 2, on attend pour l'ack
	int reception = 0;
	while(msgrcv(boite, &rep, sizeof(ack_t), type, IPC_NOWAIT) == -1 && reception < TIMEOUT)
	{
		reception++;
		sleep(1);
	};
	if(reception == TIMEOUT)
	{
		printf("TIMEOUT(%ds): ACK perdu\n", TIMEOUT);
	}

	//nettoyage de la boite
	reponse_t r;
	while(msgrcv(boite, &r, sizeof(reponse_t), type, IPC_NOWAIT) != -1 && errno != ENOMSG);
	exit(1);
}


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("usage: %s <cle>\n", argv[0]);
		exit(-1);
	}

	boite = msgget(atoi(argv[1]), 0), type = getpid();

	etat_coureur_t etat = EN_COURSE;
	requete_t req;
	req.type = PC_COURSE;
	req.corps.dossard = type;
	req.corps.etat = EN_COURSE;

	reponse_t rep;

	//tour sert juste à indiquer le numéro du tour
	int tour = 1;

	//VERSION 2, TIMEOUT = nombre de secondes à attendre pour la réponse
	int reception = 0;

	messages_initialiser_attente();

	//SIGINT = abandon => envoie message ABANDON, attente ack
	signal(SIGINT, hand);
	while(etat == EN_COURSE)
	{
		//envoie requete
		msgsnd(boite, &req, sizeof(requete_t), 0);

		//réponse
		//VERSION 2, on n'attend pas la réponse dans msgrcv, mais si on ne l'a pas, on attend une seconde et reessaye  tant qu'on ne dépasse pas le timeout
		while(msgrcv(boite, &rep, sizeof(reponse_t), type, IPC_NOWAIT) == -1 && reception < TIMEOUT)
		{
			reception++;
			sleep(1);
		};

		//pour avoir le numéro du tour avant les affichages
		printf("%d:\n", tour);
		//VERSION 2,
		if(reception == TIMEOUT)
		{
			printf("TIMEOUT(%ds): Réponse perdue\n", TIMEOUT);
		}
		else
		{
			etat = rep.corps.etat;
			if(rep.corps.compte_rendu != OK)
			{
				messages_afficher_erreur(rep.corps.compte_rendu);
			}
			else
			{
				messages_afficher_reponse(&rep);
				messages_afficher_parcours(&rep);
			}
		}
		//pause
		messages_attendre_tour();

		//VERSION 2, réinitialisation du temps de réponse
		reception = 0;
		tour++;
	}

	return 0;
}
