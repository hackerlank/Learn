#!/bin/sh

## 启动所有服务器脚本
#＃停止所有服务 ./RunServer stop
## 开始所有服务 ./RunServer start
## 重启所有服务 ./RunServer reboot
## 无参数启动所有服务 ./RunServer

sig="-3"

dowork()
{
	cd sql
	./database.py startsql
	echo "StartSQL"
	cd ..
	
	echo "starting PlateServer/PlateServer"
	./PlateServer/PlateServer -d
	sleep 2


	echo "starting SuperServer/SuperServer"
	./SuperServer/SuperServer -d
	sleep 2

	echo "starting RecordServer/RecordServer"
	./RecordServer/RecordServer -d
	sleep 2


	echo "starting SessionServer/SessionServer"
	./SessionServer/SessionServer -d
	sleep 2
	
	echo "starting SceneServer/SceneServer"
	./SceneServer/SceneServer -d
	sleep 2
	
	echo "starting GatewayServer/GatewayServer"
	./GatewayServer/GatewayServer -d
	sleep 2
	

	ps x|grep "Server -d"
}

stopwork()
{
	sig="-3"
	
	pkill $sig GatewayServer -u "whoami" 
	echo "stop GatewayServer/GatewayServer"
	
	pkill $sig SceneServer -u "whoami" 
	echo "stop SceneServer/SceneServer"
	
	pkill $sig SessionServer -u "whoami" 
	echo "stop SessionServer/SessionServer"
	
	pkill $sig RecordServer -u "whoami" 
	echo "stop RecordServer/RecordServer"

	pkill $sig SuperServer -u "whoami" 
	echo "stop SuperServer/SuperServer"
	
	pkill $sig PlateServer -u "whoami" 
	echo "stop PlateServer/PlateServer"
	

	TN=0
	while test -f RunServer.sh
	do
		COUNT=`ps x | grep "Server -d" | sed -e '/grep/d'  | sed -e '/NameServer/d' | sed -e '/GMServer/d' | sed -e '/TaskServer/d' | sed -e '/ChatServer/d' | sed -e '/MonitorServer/d' | wc -l`
		
		echo "running server:"$COUNT
		if [ $COUNT -eq $TN ]
		then
			break
		fi
		sleep 1
	done
}

fstopwork()
{
	sig="-9"
	
	pkill $sig GatewayServer 
	echo "stop GatewayServer/GatewayServer"


	pkill $sig SceneServer 
	echo "stop SceneServer/SceneServer"


	pkill $sig SessionServer 
	echo "stop SessionServer/SessionServer"

	pkill $sig RecordServer 
	echo "stop RecordServer/RecordServer"
	

	pkill $sig SuperServer 
	echo "stop SuperServer/SuperServer"
	
	pkill $sig PlateServer 
	echo "stop PlateServer/PlateServer"
	

	TN=0
	while test -f RunServer.sh
	do
		COUNT=`ps x | grep "Server -d" | sed -e '/grep/d'  | sed -e '/NameServer/d' | sed -e '/GMServer/d' | sed -e '/TaskServer/d' | sed -e '/ChatServer/d' | sed -e '/MonitorServer/d' | wc -l`
		
		echo "running server:"$COUNT
		if [ $COUNT -eq $TN ]
		then
			break
		fi
		sleep 1
	done
}

echo "---------------------------------------"
echo "----------------START------------------"
echo "---------------------------------------"
	
case $1 in
		stop)
		stopwork
		;;
		fstop)
		fstopwork
		;;
		reboot)
		stopwork
		sleep 3
		dowork
		;;
		debug)
		sig=""
		stopwork
		sleep 1
		dowork
		;;
		*)
		stopwork
		sleep 1
		dowork
		;;
esac
echo "-------------------------------------------"
echo "-------------------DONE--------------------"
echo "-------------------------------------------"

