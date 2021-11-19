#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>

int
main( int nb_arg , char * tab_arg[] )
{

     /* Parametres */
     char fich_terrain[128] ;
     case_t marque = CASE_LIBRE ;
     char nomprog[128] ;

     /*----------*/

     /* Capture des parametres */
     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <marque>\n",
		   tab_arg[0] );
	  exit(-1);
     }

     if( strlen(tab_arg[2]) !=1 )
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   tab_arg[0] , tab_arg[2] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     marque = tab_arg[2][0] ;


   /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     printf( "\n\n%s : ----- Debut du ver %c (%d) -----\n\n ",
		nomprog , marque , getpid() );

		//ouverture fichier
		int fd = open(fich_terrain, O_RDWR);
		//initialisation ver
		ver_t ver;
		ver.marque = marque;
		jeu_ver_initialiser(fd, 10, 10, &ver);
		coord_t *coordv;
		int case_libre = 0, nbv, nbl, nbc, i;
		terrain_dim_lire(fd, &nbl, &nbc);

		//initialisation verrous
		struct flock lck;
		lck.l_whence = 0;
		lck.l_len = CASE_TAILLE;

		while(case_libre != -1) {
			terrain_voisins_rechercher(fd, ver.tete, &coordv, &nbv);
			//pose verrous
			lck.l_type = F_WRLCK;
			for(i = 0; i < nbv; i++) {
				lck.l_start = coordv[i].pos;
				fcntl(fd, F_SETLKW, &lck);
			}
			//déplacement
			//on actualise les voisins, au cas où une case a été prise pendant la pose des verrous
			terrain_voisins_rechercher(fd, ver.tete, &coordv, &nbv);
			terrain_case_libre_rechercher(fd, coordv, nbv, &case_libre);
			if(case_libre != -1)
				terrain_marque_ecrire(fd, coordv[case_libre], ver.marque);
			ver.tete = coordv[case_libre];

			//levée verrous
			lck.l_type = F_UNLCK;
			for(i = 0; i < nbv; i++) {
				lck.l_start = coordv[i].pos;
				fcntl(fd, F_SETLKW, &lck);
			}
			//attente pour le prochain tour
			sleep(random() % 3 + 1);
		}
		close(fd);
		free(coordv);
     printf( "\n\n%s : ----- Fin du ver %c (%d) -----\n\n ",
	     nomprog , marque , getpid() );

     exit(0);
}
