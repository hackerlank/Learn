CFG=run/Config/ServerConfig.xml
if [ -f $CFG ]; then
    IP=`cat run/Config/ServerConfig.xml|grep "\<Database\>"|grep "name=\"game\""|awk '{print $3}'|awk -F\" '{print $2}'`
    PT=`cat run/Config/ServerConfig.xml|grep "\<Database\>"|grep "name=\"game\""|awk '{print $4}'|awk -F\" '{print $2}'`
    DB=`cat run/Config/ServerConfig.xml|grep "\<Database\>"|grep "name=\"game\""|awk '{print $5}'|awk -F\" '{print $2}'`
    USR=`cat run/Config/ServerConfig.xml|grep "\<Database\>"|grep "name=\"game\""|awk '{print $6}'|awk -F\" '{print $2}'`
    PWD=`cat run/Config/ServerConfig.xml|grep "\<Database\>"|grep "name=\"game\""|awk '{print $7}'|awk -F\" '{print $2}'`
    mysqldump -h$IP -P$PT -u$USR -p$PWD $DB -d
else
    echo "ERROR: File " $CFG " Not exists."
fi
