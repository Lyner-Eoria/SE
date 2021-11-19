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

fich_obj_test_jeu = test_jeu.o \
	jeu.o coord.o \
	$(terrain_dir)/terrain.o \
	$(vers_dir)/ver.o 

fich_obj_test_coord = test_coord.o coord.o 



#
#-------- Mains ---------------
#

#
# --- Tests ---
#

test_jeu : $(fich_obj_test_jeu)
	$(CCLNK) $(fich_obj_test_jeu) $(FLAGS) -o test_jeu -I./ -I$(terrain_dir) -I$(vers_dir) 

test_jeu.o : test_jeu.c .//commun.h jeu.h
	$(CCOBJ) $(FLAGS) test_jeu.c -o test_jeu.o -I./ -I$(terrain_dir) -I$(vers_dir) 

test_coord : $(fich_obj_test_coord)
	$(CCLNK) $(fich_obj_test_coord) $(FLAGS) -o test_coord -I./ 

test_coord.o : test_coord.c .//commun.h coord.h
	$(CCOBJ) $(FLAGS) test_coord.c -o test_coord.o -I./ 


#
#-------- Modules -------------
#

jeu.o : jeu.c jeu.h commun.h
	$(CCOBJ) $(FLAGS) jeu.c -o jeu.o -I./ -I$(terrain_dir) -I$(vers_dir)

coord.o : coord.c coord.h ./commun.h
	$(CCOBJ) $(FLAGS) coord.c -o coord.o -I./ 

#
#-------- Modules externes -------------
#

$(terrain_dir)/terrain.o : 
	cd $(terrain_dir) ; make -f Makefile terrain.o 

$(vers_dir)/ver.o : 
	cd $(vers_dir) ; make -f Makefile ver.o 

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

all :  test_jeu test_coord



