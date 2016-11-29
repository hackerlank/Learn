#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../ThirdParty/mysql++-3.2.0

GroupID=`grep group Config/ServerConfig.xml | grep ServerGroup|awk '{print $2}'|awk -F= '{print $2}'|sed s/\"//g`
SSvrM=`ls ServerManager*|grep -v "\."`
already=0
if [ "$SSvrM" == "" ]; then
    SSvrM=`ls ServerManager*`
    already=1
fi

isDebug=0
D=`expr substr $SSvrM 14 1`
if [ "$D" == "D" ]; then
    isDebug=1
else
    D=""
fi

if [ $already -eq 1 ]; then
    if [ $isDebug -eq 1 ]; then
        SGroupID=`expr substr $SSvrM 16 10`
    else
        SGroupID=`expr substr $SSvrM 15 10`
    fi
    if [ $SGroupID -ne $GroupID ]; then
        echo "Group Error."
        exit -1
    fi
fi

Svrs=("LoginServer" "CenterServer" "DBServer" "GateServer" "GameServer" "LogServer")

SvrM=ServerManager$D.$GroupID
if [ "$SSvrM" != "$SvrM" ]; then
    mv -f $SSvrM $SvrM
fi

function start()
{
    if [ ! -f $SvrM ]; then
        echo "Need: " $SvrM
    else
        ./$SvrM -x

        for s in ${Svrs[*]}
        do
            S=$s$D
            if [ -f $S ]; then
                mv -f $S $S.$GroupID
            fi
        done

        sleep 1

        rm BattleLog/*
        rm BattleProtocol/*

        if [ "$D" == "D" ]; then
            ./$SvrM -d
        else
            ./$SvrM -r
        fi
    fi
}

function restart()
{
    start
}

function stop()
{
    if [ ! -f $SvrM ]; then
        echo "Need: " $SvrM
    else
        ./$SvrM -x
    fi
}

if [ $# -eq 0 ]; then
    start
fi

if [ $# -ge 1 ]; then
    if [ "$1" == "stop" ]; then
        stop
    fi
    if [ "$1" == "restart" ]; then
        restart
    fi
fi

