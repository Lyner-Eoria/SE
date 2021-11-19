if( test $# -ne 2 ) then 
    echo "Usage: $0 <pid aire> <nb vers>"
    exit 1
fi 

pid_aire=$1
nb_vers=$2
i=0
while( test $i -lt $nb_vers ) do 
 echo "lancement ver $i"
 ./verDeTerre $pid_aire &
 i=`expr $i + 1`
done 
