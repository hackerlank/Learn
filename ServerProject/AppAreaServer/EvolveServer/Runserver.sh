#/bin/bash

HOST="121.40.77.217"
USER="flyer"
PASSWD="flyer"
DATABASE="medo"
TABLE="t_serverinfo"

COMMAND="select NAME from ${TABLE}"
declare count=`mysql -h${HOST} -u${USER} -p${PASSWD} -D ${DATABASE} -e "${COMMAND}" --skip-column-name`
cond=$(ps -u $(basename $HOME) | grep -c Server)
ulimit -c unlimited

start()
{
    #先暂停服务器
    while [ $cond -gt 0 ];
	do
		stop
	done

    #建立日志文件夹
    if [ -d log ]
    then
        rm -rf log
    fi
    mkdir log

    #启动redis
    echo "redis-server configdir/redis.conf"
    redis-server configdir/redis.conf

    #启动login
    for list in $count
    do
        if [ ${list} = "LoginServer" ]
        then
            echo "start ./loginserver/LoginServer"
            ./loginserver/LoginServer -d
            sleep 5
        fi
    done

    #启动superserver
    for list in $count
    do
        if [ ${list} = "SuperServer" ]
        then
            echo "start ./superserver/SuperServer"
            ./superserver/SuperServer -d
            sleep 1
            break
        fi
    done

    #启动recordserver
    for list in $count
    do
        if [ ${list} = "RecordServer" ]
        then
            echo "start ./recordserver/RecordServer"
            ./recordserver/RecordServer -d
            sleep 5
        fi
    done

    #启动sceneserver
    for list in $count
    do
        if [ ${list} = "SceneServer" ]
        then
            echo "start ./sceneserver/SceneServer"
            ./sceneserver/SceneServer -d
            sleep 1
        fi
    done

    #启动gatewayserver
    for list in $count
    do
        if [ ${list} = "GatewayServer" ]
        then
            echo "start ./gatewayserver/GatewayServer"
            ./gatewayserver/GatewayServer -d
            sleep 1
        fi
    done

    #启动机器人服务器
    #echo "start ./robotserver/RobotServer"
    #./robotserver/RobotServer -d

    cond=$(ps -u $(basename $HOME) | grep Server)
    echo "$cond"
}

stop()
{

    #暂停登录服务器
    sleep 1
	echo "stop ./loginserver/LoginServer"
	pkill LoginServer 


    #暂停网关服务器
    sleep 1
	echo "stop ./gatewayserver/GatewayServer"
	pkill GatewayServer 

    #暂停场景服务器
    sleep 1
	echo "stop ./sceneserver/SceneServer"
	pkill SceneServer

    #暂停db服务器
    sleep 1
	echo "stop ./recordserver/RecordServer"
	pkill RecordServer 

    #暂停管理服务器
	sleep 1
	echo "stop ./superserver/SuperServer"
	pkill SuperServer
	sleep 1

    #先暂停登录服务器
    sleep 1
    echo "stop ./loginserver/LoginServer"
	pkill LoginServer 

    #暂停机器人服务器
    echo "stop ./robotserver/RobotServer"
    pkill RobotServer


    #暂停redis服务器
    echo "stop redis-server"
    pkill redis-server

	while [ $cond -gt 0 ]
	do
		cond=$(ps -u $(basename $HOME) | grep -c server)
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
    stop
    start
    ;;
	*)
	stop
	start
	;;
esac
