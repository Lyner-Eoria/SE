#include <stdio.h>
#include <unistd.h>

#include <ver.h>

extern 
coord_t ver_tete_get( const ver_t ver ) 
{
  return( ver.tete ) ; 
}

extern 
int ver_tete_set( ver_t * const ver , const coord_t tete ) 
{
  ver->tete = tete ;
  return(0) ; 
}

extern 
case_t ver_marque_get( const ver_t ver ) 
{
  return( ver.marque ) ; 
}

extern 
int ver_marque_set( ver_t * const ver , const case_t marque ) 
{
  ver->marque = marque ;
  return(0) ; 
}

extern 
pid_t ver_pid_get( const ver_t ver ) 
{
  return( ver.pid ) ; 
}

extern 
int ver_pid_set( ver_t * const ver , const pid_t pid ) 
{
  ver->pid = pid ;
  return(0) ; 
}

extern 
int ver_sig_get( const ver_t ver ) 
{
  return( ver.sig ) ; 
}

extern 
int ver_sig_set( ver_t * const ver , const int sig ) 
{
  ver->sig = sig ;
  return(0) ; 
}

extern 
int ver_set( ver_t * const ver , 
	     const coord_t   tete ,
	     const case_t    marque ,
	     const pid_t     pid ,
	     const int       sig )
{
  int noerr = 0 ; 

  if( ( noerr = ver_tete_set( ver , tete ) ) )
    return(noerr) ;

  if( ( noerr = ver_marque_set( ver , marque ) ) )
    return(noerr) ;

  if( ( noerr = ver_pid_set( ver , pid ) ) )
    return(noerr) ; 

  if( ( noerr = ver_sig_set( ver , sig ) ) )
    return(noerr) ; 

  return(0) ; 
}

/* Affichage sortie standard */

extern
void ver_printf( const ver_t ver ) 
{ 
  printf( "{") ; 
  printf( "Coord = " ) ; coord_printf(ver_tete_get(ver)) ;
  printf( ", Marque = %c" , ver_marque_get(ver) ) ;
  printf( ", pid = %d" , ver_pid_get(ver) ) ;
  printf( ", sig = %d" , ver_sig_get(ver) ) ; 
  printf( "}") ; 
}

/* Ecriture dans un fichier */

extern
int ver_write( const int fd , 
	       const ver_t * const ver ) 
{ 
  return( write( fd , &ver , sizeof(ver_t) ) ) ; 
}



extern 
ver_t ver_vide() 
{
  ver_t ver ; 
  ver.tete = COORD_VIDE ;
  ver.marque = ' ' ;
  ver.pid = -1 ;
  ver.sig = -1 ;
  return(ver) ;
}
