# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

#
# Object files
#

fich_obj_verDeTerre = verDeTerre.o \
	$(vers_dir)/vers.o $(vers_dir)/ver.o \
	$(terrain_dir)/terrain.o \
	$(commun_dir)/coord.o 

fich_obj_aire = aire.o \
	$(vers_dir)/vers.o $(vers_dir)/ver.o \
	$(terrain_dir)/terrain.o \
	$(commun_dir)/coord.o $(commun_dir)/jeu.o

#
#-------- Mains ---------------
#

verDeTerre : $(fich_obj_verDeTerre)
	$(CCLNK) $(fich_obj_verDeTerre) $(FLAGS) -o verDeTerre -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

verDeTerre.o : verDeTerre.c $(vers_dir)/vers.h $(commun_dir)/commun.h $(terrain_dir)/terrain.h
	$(CCOBJ) $(FLAGS) verDeTerre.c -o verDeTerre.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

aire : $(fich_obj_aire)
	$(CCLNK) $(fich_obj_aire) $(FLAGS) -o aire -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

aire.o : aire.c $(commun_dir)/commun.h $(terrain_dir)/terrain.h $(vers_dir)/vers.h
	$(CCOBJ) $(FLAGS) aire.c -o aire.o -I$(commun_dir) -I$(terrain_dir) -I$(vers_dir) -I./

#
#-------- Utilitaires ---------------
#

#
# --- Tests ---
#

#
#-------- Modules externes -------------
#

$(terrain_dir)/terrain.o : 
	cd $(terrain_dir) ; make -f Makefile terrain.o 

$(vers_dir)/vers.o : 
	cd $(vers_dir) ; make -f Makefile vers.o 

$(vers_dir)/ver.o : 
	cd $(vers_dir) ; make -f Makefile ver.o 

$(commun_dir)/coord.o : 
	cd $(commun_dir) ; make -f Makefile coord.o

$(commun_dir)/jeu.o : 
	cd $(commun_dir) ; make -f Makefile jeu.o

#
#-------- Headers -------------
#



#
#-------- Clean objects -------
#

clean : 
	- rm *.o *~


#
#-------- All executables -------
#

all : verDeTerre aire 




