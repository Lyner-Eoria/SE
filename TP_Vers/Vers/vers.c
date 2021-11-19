/*
 * Gestion de la liste des vers 
 */

#include <vers.h>

/*! Acces au nombre de vers dans la liste */
extern 
int vers_nb_get( const vers_t * const liste_vers )
{
  return(liste_vers->nb) ; 
}

/*! Acces a un ver dans la liste */
extern 
ver_t vers_ver_get( const vers_t * const liste_vers  , const int ind_ver )
{
#ifdef _DEBUG_
  int nbvers = vers_nb_get(liste_vers) ;
  if( (ind_ver < 0) || (ind_ver >  nbvers-1) )
    {
      fprintf( stderr , "vers_ver_get: mauvais indice de ver [%d] (devrait etre dans [%d..%d])\n",
	       ind_ver , 0 , nbvers-1 );
      return(VER_VIDE);
    }
#endif

  return( liste_vers->vers[ind_ver] ) ;
}

/*
 * Methodes set
 */


/* 
 * Affectation d'un ver dans une liste de vers 
 * La position du ver doit exister
 * L'ancienne valeur du ver est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans ver_t
 */
extern int vers_ver_set( vers_t * const liste_vers , 
			 const int ind_ver , 
			 const ver_t ver ) 
{
#ifdef _DEBUG_
  int nbvers = vers_nb_get(liste_vers) ;
  if( (ind_ver < 0) || (ind_ver >  nbvers-1) )
    {
      fprintf( stderr , "vers_ver_set: mauvais indice de ver [%d] (devrait etre dans [%d..%d])\n",
	       ind_ver , 0 , nbvers-1 );
      return(-1);
    }
#endif

  /* Affectation du ver a la  position */
  liste_vers->vers[ind_ver] = ver ;

  return(0) ;
}

/* 
 * Ajout d'un ver dans une liste de vers 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans ver_t
 */
extern int vers_ver_add( vers_t * const liste_vers , 
			 const ver_t ver ) 
{
  int nbvers = vers_nb_get(liste_vers) ; 
 
  if( nbvers == 0 ) 
    {
      if( ( liste_vers->vers = malloc( sizeof(ver_t) ) ) == NULL ) 
	{
	  fprintf( stderr , "vers_ver_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(ver_t) ) ;
	  return(-1) ; 
	} 
    }
  else
    {
      if( ( liste_vers->vers = realloc( liste_vers->vers , sizeof(ver_t) * (nbvers+1) ) ) == NULL ) 
	{
	  fprintf( stderr , "vers_ver_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(ver_t) * (nbvers+1) ) ;
	  return(-1) ; 
	} 
    }

  /* Affectation du ver a la derniere position */
  liste_vers->vers[nbvers] = ver ;

  /* Mise a jour du nombre de vers */
  liste_vers->nb++ ; 
 
  return(0) ;
}


/* 
 * Deletion d'un ver dans une liste de ver 
 */
extern 
int vers_ver_del( vers_t * const liste_vers , 
		  const int ind_ver ) 
{
  int nbvers = 0 ; 
  int i = 0 ;

  /* --- Assertions --- */
  if( liste_vers == NULL  ) 
    {
      fprintf( stderr , "vers_ver_del: liste de vers inexistante\n");
      return(-1) ;
    }

  nbvers = vers_nb_get(liste_vers) ; 

  if( (ind_ver < 0) || (ind_ver > nbvers-1 ) )
    {
      fprintf( stderr , "vers_ver_del: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind_ver , 0 , nbvers-1 );
      return(-1);
    }

  /* ----------------- */

  /* Decalage des pointeurs depuis la position d'extraction jusqu'a la fin */
  for( i=ind_ver ; i<nbvers-1 ; i++ ) 
    {
      liste_vers->vers[i] = liste_vers->vers[i+1] ;
    }

 /* Mise a jour de la taille du versleau */
  nbvers-- ; 
  liste_vers->nb = nbvers ; 
 
  if( nbvers == 0 ) 
    {
      free(liste_vers->vers) ; 
      liste_vers->vers = NULL ; 
    }
  else
    {
      if( ( liste_vers->vers = realloc( liste_vers->vers , sizeof(ver_t) * nbvers ) ) == NULL ) 
	{
	  fprintf( stderr , "vers_ver_del: debordement memoire %lu octets demandes\n" ,
		   sizeof(ver_t) * nbvers ) ;
	  return(-1) ; 
	} 
    }

  return(0) ; 
}


/*
 * Creation d'une liste de vers
 * Stockage direct des Les elements ver_t 
 */
extern 
vers_t * vers_new()
{
  vers_t * liste ;

  if( (liste=(vers_t *)malloc(sizeof(vers_t))) == NULL )
    {
      fprintf( stderr , "vers_creer: debordement memoire lors de la creation d'une liste de vers\n");
      return((vers_t *)NULL);
    }
  
  liste->nb = 0 ;
  liste->vers = (ver_t *)NULL ;

  return(liste) ;
}

/*
 *  Destruction d'une liste de vers 
 */

extern 
int vers_destroy( vers_t ** liste_vers )
{
  
  if( (*liste_vers) == NULL )
    return(0) ;

  /* 
   * Destruction globale des elements de la liste
   * (stockage direct)
   */

  free( (*liste_vers)->vers ) ;
  free( (*liste_vers) ) ;
  (*liste_vers) = (vers_t *)NULL ;

  return(0) ;
}

/*
 * Affichage d'une liste de vers sur la sortie standard 
 */
extern 
void vers_printf( const vers_t * const liste_vers )
{
  int v ;
  int  nbvers ; 

  if( liste_vers == NULL )
    {
      printf("(Liste vers vide)\n");
      return ;
    }

  nbvers = vers_nb_get(liste_vers) ;

  printf( "Nombre de vers = %d\n" , nbvers ) ;
  printf( "Liste des vers:\n");
  for( v=0 ; v<nbvers ; v++ )
    {
      ver_printf(vers_ver_get( liste_vers , v ) ) ;
      printf("\n");
    }
  printf("\n");
}


/*
 * Chargement d'une liste de vers a partir d'un fichier 
 */
extern 
int vers_fichier_load( vers_t ** liste_vers  , /* structure liste vers a charger */
		       char * nom_fichier )  /* fichier de restauration */
{
  int noerr ;
  int fd ;
  int ind_ver  ;
  int nbvers ;
  ver_t ver ; 

  /* Destruction de la liste si elle existe deja */
  if( (*liste_vers) != NULL )
    {
      vers_destroy( liste_vers ) ;
    }


  /* Ouverture du fichier des vers */
  if( (fd = open( nom_fichier , O_RDONLY , 0666 )) == -1 )
    {
      fprintf( stderr , "vers_fichier_charger: impossible d'ouvrir le fichier [%s] en lecture\n",
	       nom_fichier ) ;
      return(-1);
    }

  /* Lecture du nombre de vers */
  read( fd , &nbvers , sizeof(int) ) ;

  /* Creation de la liste */
  (*liste_vers) = vers_new() ;

  for( ind_ver=0 ; ind_ver<nbvers ; ind_ver++ )
    {
      read( fd , &ver , sizeof(ver_t) ) ; 
      if( ( noerr = vers_ver_add( (*liste_vers) , ver ) ) )
	return(noerr) ; 

    }

  /* Fermeture du fichier des vers */
  close(fd) ;

  return(0) ;
}


/*
 * Ecriture du contenu d'une liste de vers dans un fichier
 */

extern 
int vers_fichier_save( const vers_t * const liste_vers  ,  /* structure liste vers a sauver */
		       char * nom_fichier )    /* fichier de sauvegarde */
{
  int fd ;
  int ind_ver  ;
  int nbvers ;
  ver_t ver ; 

  /* Destruction de la liste si elle existe deja */
  if( liste_vers == NULL )
    {
      fprintf( stderr , "WARNING : vers_fichier_sauver: la liste de vers est inexistante\n") ;
      return(0) ;
    }
 
  /* Ouverture du fichier des sauvegardes */
  if( (fd = open( nom_fichier , O_WRONLY , 0666 )) == -1 )
    {
      fprintf( stderr , "vers_fichier_sauver: impossible d'ouvrir le fichier [%s] en lecture\n",
	       nom_fichier ) ;
      return(-1);
    }

  nbvers = vers_nb_get(liste_vers) ;
  
  /* Ecriture du nombre de vers */
  write( fd , &nbvers , sizeof(int) ) ;
  
  /* Parcours de la liste */
  for( ind_ver=0 ; ind_ver<nbvers ; ind_ver++ )
    {
      ver = vers_ver_get( liste_vers , ind_ver ) ;
      write( fd , &ver , sizeof(ver_t) ) ; 

    }

  /* Fermeture du fichier de sauvegarde */
  close(fd) ;

  return(0) ;

}



/*
 * Recherche d'un ver sur son pid 
 * Valeur retournee : indice du ver dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int vers_pid_seek( const vers_t * const liste_vers,
		   const pid_t pid_ver ) 
{
  int ind_ver = 0  ;
  booleen_t trouve = FAUX ;
  int nbvers= vers_nb_get(liste_vers) ;
 
  while( (ind_ver<nbvers) && (!trouve) ) 
    {
      if( pid_ver ==  ver_pid_get(vers_ver_get(liste_vers , ind_ver)) )
	  trouve = VRAI ;
      else
	  ind_ver++ ;
    }
  
  if( trouve ) 
    {
      return(ind_ver);
    }
  else
    {
      return(-1) ;
    }
}

/*
 * Recherche d'un ver sur son numero de signal 
 * Valeur retournee : indice du premier ver trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int vers_signal_seek( const vers_t * const liste_vers,
		      const int sig_ver ) 
{
  int ind_ver = 0  ;
  booleen_t trouve = FAUX ;
  int nbvers= vers_nb_get(liste_vers) ;
 
  while( (ind_ver<nbvers) && (!trouve) ) 
    {
      if( sig_ver ==  ver_sig_get(vers_ver_get(liste_vers , ind_ver)) )
	  trouve = VRAI ;
      else
	  ind_ver++ ;
    }
  
  if( trouve ) 
    {
      return(ind_ver);
    }
  else
    {
      return(-1) ;
    }
}

/*
 * Recherche d'un ver sur sa marque
 * Valeur retournee : indice du premier ver trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int vers_marque_seek( const vers_t * const liste_vers,
		      const char marque_ver ) 
{
  int ind_ver = 0  ;
  booleen_t trouve = FAUX ;
  int nbvers= vers_nb_get(liste_vers) ;
 
  while( (ind_ver<nbvers) && (!trouve) ) 
    {
      if( marque_ver ==  ver_marque_get(vers_ver_get(liste_vers , ind_ver)) )
	  trouve = VRAI ;
      else
	  ind_ver++ ;
    }
  
  if( trouve ) 
    {
      return(ind_ver);
    }
  else
    {
      return(-1) ;
    }
}
