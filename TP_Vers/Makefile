# MAKEFILE for TP Vers
#
#

#
# Directories
#
top_dir = .
include $(top_dir)/Makefile.dir 

all : 
	cd $(terrain_dir) ; make -f Makefile all
	cd $(vers_dir) ; make -f Makefile all 
	cd $(commun_dir) ; make -f Makefile all 
	cd $(signaux_dir) ; make -f Makefile all 
	cd $(verrous_dir) ; make -f Makefile all 

clean :
	- rm *~
	cd $(terrain_dir) ; make -f Makefile clean 
	cd $(vers_dir) ; make -f Makefile clean 
	cd $(commun_dir) ; make -f Makefile clean 
	cd $(signaux_dir) ; make -f Makefile clean 
	cd $(verrous_dir) ; make -f Makefile clean 

distrib : 
	find $(distrib_dir)/TP_Vers \( -name '*~' -o -name '*.o' \) -exec rm {} \;
	cp $(commun_dir)/*.[ch] $(commun_dir)/Makefile $(distrib_dir)/TP_Vers/Commun/.
	cp $(terrain_dir)/*.[hc] $(terrain_dir)/Makefile $(distrib_dir)/TP_Vers/Terrain/.
	cp $(vers_dir)/*.[ch] $(vers_dir)/Makefile  $(distrib_dir)/TP_Vers/Vers/.
	cp $(verrous_dir)/Makefile $(verrous_dir)/lance_vers.sh $(distrib_dir)/TP_Vers/Verrous/.
	cp $(signaux_dir)/Makefile $(signaux_dir)/lance_vers.sh $(distrib_dir)/TP_Vers/Signaux/.
	cp Makefile* $(distrib_dir)/TP_Vers/.
	- rm $(distrib_dir)/TP_Vers.tar.gz
	cd $(distrib_dir) ; tar cvf TP_Vers.tar README TP_Vers ; gzip TP_Vers.tar 

distrib-clean :
	find $(distrib_dir)/TP_Vers \( -name '*.[ch]' -o -name 'Makefile' \) -exec rm {} \;

tags : 
	etags --language=c  */*.[ch] --output=VERS.TAGS