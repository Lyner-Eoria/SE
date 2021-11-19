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

fich_obj_test_terrain = test_terrain.o terrain.o $(commun_dir)/coord.o
fich_obj_init_fich_terrain = init_fich_terrain.o terrain.o $(commun_dir)/coord.o


#
#-------- Mains ---------------
#

init_fich_terrain : $(fich_obj_init_fich_terrain)
	$(CCLNK) $(fich_obj_init_fich_terrain) $(FLAGS) -o init_fich_terrain -I./ -I$(commun_dir) -I$(commun_dir)

init_fich_terrain.o : init_fich_terrain.c $(commun_dir)/commun.h terrain.h
	$(CCOBJ) $(FLAGS) init_fich_terrain.c -o init_fich_terrain.o -I./ -I$(commun_dir)  -I$(commun_dir)

#
# --- Tests ---
#

test_terrain : $(fich_obj_test_terrain)
	$(CCLNK) $(fich_obj_test_terrain) $(FLAGS) -o test_terrain -I./ -I$(commun_dir)  -I$(commun_dir)

test_terrain.o : test_terrain.c $(commun_dir)/commun.h terrain.h
	$(CCOBJ) $(FLAGS) test_terrain.c -o test_terrain.o -I./ -I$(commun_dir)  -I$(commun_dir)

#
#-------- Modules -------------
#

terrain.o : terrain.c terrain.h 
	$(CCOBJ) $(FLAGS) terrain.c -o terrain.o -I./ -I$(commun_dir)  -I$(commun_dir)

#
#-------- Modules externes -------------
#

$(commun_dir)/coord.o : $(commun_dir)/coord.c $(commun_dir)/coord.h 
	$(CCOBJ) $(FLAGS) $(commun_dir)/coord.c -o $(commun_dir)/coord.o -I./ -I$(commun_dir)  -I$(commun_dir)



#
#-------- Headers -------------
#
terrain.h : $(commun_dir)/commun.h $(commun_dir)/coord.h
	touch terrain.h
#
#-------- Clean objects -------
#

clean : 
	- rm *.o *~


#
#-------- All executables -------
#

all : init_fich_terrain test_terrain 



