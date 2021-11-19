#include <string.h>
#include <stdlib.h>

#include <coord.h>


int
main( int argc , char * argv[] )
{
     char nomprog[128] ;
     int noerr = 0 ;

     coord_t coord ;

     /*----------*/

     strcpy( nomprog , argv[0] ) ; 

     if( argc != 1 )
     {
       fprintf( stderr , "Programme de test du type coord_t\n") ; 
       fprintf( stderr , "Usage : %s \n",
		argv[0] );
	  exit(-1) ;
     }

     printf( "----- Debut %s -----\n" , nomprog ) ; 

     printf(" Affectation coord\n");
     if( ( noerr = coord_set( &coord , 5 , 10 , 123 ) ) )
       {
	 printf( "Sortie erreur avec code %d\n" , noerr ) ; 
       }

     coord_printf(coord) ;
     printf("\n");

     printf( "----- Fin %s -----\n" , nomprog ) ; 

     exit(0);

}
