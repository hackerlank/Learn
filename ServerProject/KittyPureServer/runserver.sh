#/bin/bash

cond=$(ps -u $(basename $HOME) | grep -c server)
condfl=$(ps -u $(basename $HOME) | grep -c Flserver)

ulimit -c unlimited

start()
{
	while [ $cond -gt 0 -o $condfl -gt 0 ];
	do
		stop
	done

    removelog
    sleep 1
    echo "redis-server ~/redis.conf"
    /usr/redis/redis-server ~/redis.conf
    sleep 1
	echo "start ./flserver/Flserver"
	./flserver/Flserver -d
	sleep 2
	echo "start ./superserver/Superserver"
	./superserver/Superserver -d
	sleep 3
	echo "start ./recordserver/Recordserver"
	./recordserver/Recordserver -d
    sleep 3
	echo "start ./sceneserver/SceneServer"
    ./sceneserver/Sceneserver -d 
	sleep 3
	./sceneserver/Sceneserver -d 
	echo "start ./gateserver/Gateserver"
	./gateserver/Gateserver -d 
	sleep 3
	./gateserver/Gateserver -d 
	sleep 3

	cond=$(ps -u $(basename $HOME) | grep server)
    condfl=$(ps -u $(basename $HOME) | grep -c Flserver)
	echo "$cond"
}

function removelog()
{
    if [ -d log ]
    then
        rm -rf log
        mkdir log
    else
        mkdir log
    fi
}

stop()
{
	sleep 1
	echo "stop ./superserver/Superserver"
	pkill Superserver
	sleep 1
	echo "stop ./recordserver/Recordserver"
	pkill Recordserver 
	sleep 1
	echo "stop ./sceneserver/Sceneserver"
	pkill Sceneserver
	sleep 1
	echo "stop ./gateserver/Gateserver"
	pkill Gateserver
    sleep 1
    echo "stop ./flserver/Flserver"
    pkill Flserver
    sleep 1
    echo "stop redis-server"
    pkill redis-server
	while [ $cond -gt 0 -o $condfl -gt 0 ]
	do
		cond=$(ps -u $(basename $HOME) | grep -c server)
        condfl=$(ps -u $(basename $HOME) | grep -c Flserver)
		echo "ServerNum:$cond"
		sleep 1
	done
}

case $1 in
	start)
	start
	;;
	stop)
	stop
	;;
    debug)
    start
    ;;
	*)
	stop
	start
	;;
esac
