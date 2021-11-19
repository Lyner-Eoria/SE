#ifndef _COORD_H_
#define _COORD_H_

#include <stdio.h>
#include <unistd.h>

/*
 * Definitions des constantes 
 */
 
#define COORD_VIDE coord_vide() 

/*
 *  Definition des structures
 */
typedef struct coord_s
{
     int x ;		/* abscisse case : # colonne */
     int y ;		/* ordonnee case : # ligne */
     off_t pos ;	/* position dans le fichier */
} coord_t ;

extern coord_t coord_vide() ; 

/*
 * Primitives de coord 
 */

extern int coord_x_get( const coord_t coord ) ;
extern int coord_x_set( coord_t * const coord , const int x ) ;

extern int coord_y_get( const coord_t coord ) ;
extern int coord_y_set( coord_t * const coord , const int y ) ;

extern off_t coord_pos_get( const coord_t coord ) ;
extern int   coord_pos_set( coord_t * const coord , const off_t pos ) ;

extern int coord_set( coord_t * const coord ,
		      const int x ,
		      const int y , 
		      const off_t pos ) ;

/* 
 * Affichage d'une coord
 */

extern void coord_printf( const coord_t coord ); 

/* Ecriture dans un fichier */
extern int coord_write( const int fd , /* Descripteur fichier */
			const coord_t * const coord ) ;

#endif

