#include <coord.h>


extern 
int coord_x_get( const coord_t coord ) 
{
  return( coord.x ) ; 
}

extern 
int coord_x_set( coord_t * const coord ,
		 const int x ) 
{
  coord->x = x ;
  return(0);
}

extern 
int coord_y_get( const coord_t coord ) 
{
  return( coord.y ) ; 
}

extern 
int coord_y_set( coord_t * const coord ,
		 const int y ) 
{
  coord->y = y ;
  return(0) ; 
}

extern 
off_t coord_pos_get( const coord_t coord ) 
{
  return( coord.pos ) ; 
}

extern 
int coord_pos_set( coord_t * const coord ,
		   const off_t pos ) 
{
  coord->pos = pos ;
  return(0) ; 
}

extern
int coord_set( coord_t * const coord ,
	       const int x ,
	       const int y , 
	       const off_t pos )
{
  int noerr =  0 ; 
  if( ( noerr = coord_x_set( coord , x ) ) )
    return(noerr) ; 
  
  if( ( noerr = coord_y_set(coord , y ) ) )
    return(noerr) ; 

  if( ( noerr = coord_pos_set(coord , pos ) ) )
    return(noerr) ; 

  return(0);
}

/* Affichage sortie standard */

extern
void coord_printf( const coord_t coord )
{
  printf("[x=%d y=%d pos=%lld]" , 
	 coord_x_get(coord) ,
	 coord_y_get(coord) , 
	 coord_pos_get(coord) ) ;
}

/* Ecriture dans un fichier */
extern 
int coord_write( const int fd ,
		 const coord_t * const coord )
{
  return( write( fd , coord , sizeof(coord_t) ) ) ; 
}

/* renvoie d'une coordonnee vide */
extern
coord_t coord_vide() 
{
  coord_t coord ; 
  coord.x = -1 ;
  coord.y = -1 ;
  coord.pos = -1 ; 
  return(coord) ; 
}
