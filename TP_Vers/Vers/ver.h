#ifndef _VER_H_
#define _VER_H_

/* 
 * Definition d'un ver 
 */

#include <commun.h>
#include <coord.h>
#include <case.h>

/*
 * Type
 */

typedef struct ver_s
{
     coord_t   tete ;
     case_t    marque ;
     pid_t     pid ;
     int       sig ;
} ver_t ;

#define VER_VIDE ver_vide() 

extern ver_t ver_vide() ; 

/*
 * Methodes get/set 
 */

extern coord_t ver_tete_get( const ver_t ver ) ;
extern int ver_tete_set( ver_t * const ver , const coord_t tete ) ;

extern case_t ver_marque_get( const ver_t ver ) ;
extern int ver_marque_set( ver_t * const ver , const case_t marque ) ;

extern pid_t ver_pid_get( const ver_t ver ) ;
extern int ver_pid_set( ver_t * const ver , const pid_t pid ) ;

extern int ver_sig_get( const ver_t ver ) ;
extern int ver_sig_set( ver_t * const ver , const int sig ) ;

extern int ver_set( ver_t * const ver , 
		    const coord_t   tete ,
		    const case_t    marque ,
		    const pid_t     pid ,
		    const int       sig ) ;

/* 
 * Affichage d'un ver sur la sortie standard
 */
extern void ver_printf( const ver_t ver )  ;

/* 
 * Ecriture dans un fichier 
*/

extern int ver_write( const int fd , 
		      const ver_t * const ver ) ;

#endif


