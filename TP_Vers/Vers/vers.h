#ifndef _VERS_H_
#define _VERS_H_

/*
 * Definition d'une liste de vers 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


#include <terrain.h>
#include <ver.h>

/*
 * Type
 */

typedef struct vers_s
{
  int nb ;
  ver_t * vers ;
} vers_t ;

/*
 * Methodes set/get
 */


/*! Acces au nombre de vers dans la liste */
extern int vers_nb_get( const vers_t * const l );
/*! Acces a un ver dans la liste */
extern ver_t vers_ver_get( const vers_t * const l  , const int ind_ver );
/* 
 * Affectation d'un ver dans une liste de vers 
 * La position du ver doit exister
 * L'ancienne valeur du ver est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans ver_t
 */
extern int vers_ver_set( vers_t * const liste_vers , 
			 const int ind_ver , 
			 const ver_t ver )  ;

/* 
 * Primitives 
 */

/*
 * Creation d'une liste de vers
 * Stockage direct des Les elements ver_t 
 */
extern vers_t * vers_new() ;

/*
 *  Destruction d'une liste de vers 
 */

extern int vers_destroy( vers_t ** liste_vers ) ;

/*!
 * Affichage d'une liste de vers sur la sortie standard 
 */
extern void vers_printf( const vers_t * const liste_vers );

/* 
 * Ajout d'un ver dans une liste de vers 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans ver_t
 */
extern int vers_ver_add( vers_t * const liste_vers , 
			 const ver_t ver ) ;

/* 
 * Deletion d'un ver dans une liste de vers 
 */
extern int vers_ver_del( vers_t * const liste_vers , 
			 const int ind_ver )  ;

/*
 * Methodes sauvegarde/restauration
 */

/*!
 * Chargement d'une liste de vers a partir d'un fichier 
 */
extern int vers_fichier_load( vers_t ** liste_vers  , /* structure liste vers a charger */
			      char * nom_fichier ) ;  /* fichier de restauration */


/*!
 * Ecriture du contenu d'une liste de vers dans un fichier
 */

extern int vers_fichier_save( const vers_t * const liste_vers  ,  /* structure liste vers a sauver */
			      char * nom_fichier ) ;   /* fichier de sauvegarde */


/*
 * Methode de recherche d'un element 
 */

/*
 * Recherche d'un ver sur son pid 
 * Valeur retournee : indice du ver dans la liste si il existe  
 *                    -1 sinon 
 */

extern int vers_pid_seek( const vers_t * const liste_vers,
			  const pid_t pid_ver ) ;

/*
 * Recherche d'un ver sur son numero de signal 
 * Valeur retournee : indice du premier ver trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern int vers_signal_seek( const vers_t * const liste_vers,
			     const int sig_ver ) ;

/*
 * Recherche d'un ver sur sa marque
 * Valeur retournee : indice du premier ver trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern int vers_marque_seek( const vers_t * const liste_vers,
			     const char marque_ver ) ;

#endif


