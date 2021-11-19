#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <vers.h>


int
main( int nb_arg , char * tab_arg[] )
{
  ver_t ver ;
  char fich_vers[128];
  int i ; 
  vers_t * liste_vers = (vers_t *) NULL ; /* ATTENTION a bien initialiser la liste des vers */
  int ind ; 
  int noerr = 0 ; 
  coord_t tete ; 
  int nbvers = 0 ; 
  pid_t pid ; 
  int sig ; 
  char marque ;

  /*----------*/

  if( nb_arg != 3 )
    {
      fprintf( stderr , "Usage : %s <fichier vers> <nb vers>\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  srandom(getpid()) ;

  strcpy( fich_vers , tab_arg[1]) ;
  nbvers = atoi( tab_arg[2] ) ; 

     

  printf("Creation liste\n");
  liste_vers = vers_new() ; 

  printf("Ajout de vers dans la liste\n");
  for( i=0 ; i<nbvers ; i++ )
    {
      printf( "Creation ver numero %d\n" , i ) ; 

      coord_set( &tete ,
		 random()%nbvers,
		 random()%nbvers, 
		 random()%nbvers*100) ;
     
      if( ( noerr = ver_set( &ver , 
			     tete ,
			     'A'+i,
			     random()%1000,
			     random()%32) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  exit(0) ; 
	}

      printf( "Ajout ver numero %d\n" , i ) ; 
      if( ( noerr = vers_ver_add( liste_vers, ver ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  exit(0) ; 
	}

    }

  printf("Affichage liste des vers\n");
  vers_printf(liste_vers);

  printf("Sauvegarde d'une liste de vers dans un fichier\n");
  if( ( noerr = vers_fichier_save( liste_vers , fich_vers ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }

  printf("Destruction liste\n");
  if( ( noerr = vers_destroy(&liste_vers) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }

  printf("Restauration fichier dans liste de vers\n");
  if( ( noerr = vers_fichier_load( &liste_vers, fich_vers ) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  vers_printf( liste_vers ) ;

  if( nbvers > 0 ) 
    {
      pid = ver_pid_get(vers_ver_get(liste_vers,nbvers-1)) ;
      printf("Recherche positive d'un ver dans la liste sur pid %d\n" , pid ) ;
      ind = vers_pid_seek( liste_vers, pid ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'un ver dans la liste pid 999\n" ); 
      ind = vers_pid_seek( liste_vers, 999 ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;


      sig = ver_sig_get(vers_ver_get(liste_vers,nbvers-1)) ;
      printf("Recherche positive d'un ver dans la liste sur sig %d\n" , sig ) ;
      ind = vers_signal_seek( liste_vers, sig ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'un ver dans la liste sig 999\n" ); 
      ind = vers_signal_seek( liste_vers, 999 ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;


      marque = ver_marque_get(vers_ver_get(liste_vers,nbvers-1)) ;
      printf("Recherche positive d'un ver dans la liste sur marque %c\n" , marque ) ;
      ind = vers_marque_seek( liste_vers, marque ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'un ver dans la liste marque '*' \n" ); 
      ind = vers_marque_seek( liste_vers, '*' ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;



    }


  printf("Destruction d'un ver dans la liste\n" ) ; 
  ind = random()%(vers_nb_get(liste_vers)-1) ; 
  printf("Destruction ver numero %d\n" , ind ) ;
  vers_ver_del( liste_vers , ind ) ; 
  vers_printf( liste_vers ) ;

  printf("Destruction de tous les vers un par un\n" ) ; 
  ind = vers_nb_get(liste_vers)-1 ; 
  while( vers_nb_get(liste_vers) )
    {
      printf("Destruction ver numero %d\n" , ind ) ;
      vers_ver_del( liste_vers , ind ) ; 
      ind-- ; 
    }
  vers_printf( liste_vers ) ;

  printf("Restauration dans une liste existante\n"); 
  if( ( noerr = vers_fichier_load( &liste_vers, fich_vers ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  vers_printf(liste_vers) ; 

  printf( "Destruction globale d'une liste de vers\n");      
  if( ( noerr = vers_destroy(&liste_vers) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  vers_printf(liste_vers) ; 
  
  exit(0);
}
