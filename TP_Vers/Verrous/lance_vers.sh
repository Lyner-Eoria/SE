if( test $# -ne 2 ) then 
    echo "Usage: $0 <fichier terrain> <nb_vers>"
    exit 1
fi 

fich_terrain=$1
nb_vers=$2
i=0
marque='A'
while( test $i -lt $nb_vers ) do 
   for marque in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ; do 
       if( test $i -ge $nb_vers ) then
           exit 0
       fi
       echo "lancement ver $i $marque"
       ./verDeTerre $fich_terrain $marque &
       i=`expr $i + 1`
   done 
done 