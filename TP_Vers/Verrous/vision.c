#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>


/*--------------------*
 * Main demon
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
  /* Parametres */
  char fich_terrain[128] ;
  char nomprog[256] ;

     /*----------*/

  /* Capture des parametres */
  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <fichier terrain>\n",
	       tab_arg[0] );
      exit(-1);
    }

  strcpy( nomprog , tab_arg[0] );
  strcpy( fich_terrain , tab_arg[1] );


  printf("\n%s : ----- Debut de l'affichage du terrain ----- \n", nomprog );

    // ouverture du fichier
    int fichier = open(fich_terrain, O_RDONLY);
    if(fichier == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(errno);
    }

    // initialisation des structures stat
    struct stat stat_old, stat_new;
    stat(fich_terrain, &stat_new);

    // affichage
    while(1) {
        while(stat_old.st_mtime == stat_new.st_mtime)
            stat(fich_terrain, &stat_new);
        stat_old = stat_new;
        terrain_afficher(fichier);
    }

	close(fichier);

  printf("\n%s : --- Arret de l'affichage du terrain ---\n", nomprog );

  exit(0);
}
