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

fich_obj_test_vers = test_vers.o vers.o ver.o $(commun_dir)/coord.o

#
#-------- Mains ---------------
#

#
# --- Tests ---
#

test_vers : $(fich_obj_test_vers)
	$(CCLNK) $(fich_obj_test_vers) $(FLAGS) -o test_vers -I$(commun_dir) -I$(terrain_dir) -I./

test_vers.o : test_vers.c vers.h
	$(CCOBJ) $(FLAGS) test_vers.c -o test_vers.o -I$(commun_dir) -I$(terrain_dir) -I./

#
#-------- Modules -------------
#

ver.o : ver.c ver.h
	$(CCOBJ) $(FLAGS) ver.c -o ver.o -I$(commun_dir) -I$(terrain_dir)  -I./

vers.o : vers.c vers.h
	$(CCOBJ) $(FLAGS) vers.c -o vers.o -I$(commun_dir) -I$(terrain_dir)  -I./


#
#-------- Modules externes -------------
#

$(commun_dir)/coord.o : $(commun_dir)/coord.c $(commun_dir)/coord.h
	cd $(commun_dir) ; make -f Makefile coord.o

#
#-------- Headers -------------
#

ver.h : $(commun_dir)/coord.h $(commun_dir)/case.h
	touch ver.h

vers.h : $(terrain_dir)/terrain.h ver.h
	touch vers.h

#
#-------- Clean objects -------
#

clean :
	- rm *.o *~

#
#-------- All executables -------
#

all : test_vers
