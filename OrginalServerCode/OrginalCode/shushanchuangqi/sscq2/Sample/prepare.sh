#!/bin/bash

#XXX: example of cfg.local

CFGLOADDST=Generated/ConfigLoad
CFGTABLDST=Generated/Config/Conf/Table
CFGMAPDST=Generated/Config/Conf/Map
CFGMISCDST=Generated/Config/Conf/Misc
CFGTASKDST=Generated/Config/Conf/Task
CFGSCRIPTSDST=Generated/Scripts

# 将自动化生成的代码/资源复制到指定目录下
function copy_dir()
{
    if [ $# -le 1 ]; then
        echo "ERROR: copy_dir."
        return
    fi

    if [ ! -d $2 ]; then
        mkdir -p $2
    fi
    rsync -rvc --exclude '.svn' $1/ $2/ --delete
}

SVNP="--accept theirs-conflict"

if [ ! -f cfg.local ];
then
    echo "请提供cfg.local，设置好PROT,CFGLOAD,CFGTABL,MAP,MISC,TASK,SCRIPTS。"
    exit
fi

source cfg.local

if [ "$PROT" == "" -o "$CFGLOAD" == "" -o "$CFGTABL" == "" -o "$MAP" == "" -o "$MISC" == "" -o "$PROTDST" == "" -o "$TASK" == ""  -o "$SCRIPTS" == "" -o "$ROBOTDST" == "" ]; then
    echo "以下配置都不能为空，为空者无法继续："
    echo "PROT: " $PROT
    echo "CFGLOAD: " $CFGLOAD
    echo "CFGTABL: " $CFGTABL
    echo "MAP: " $MAP
    echo "MISC: " $MISC
    echo "PROTDST: " $PROTDST
    echo "TASK: " $TASK
    echo "SCRIPTS: " $SCRIPTS
    echo "ROBOTDST: " $ROBOTDST
    exit
fi

if [ "$0" == "./prepare.sh" ]; then

    # 更新并生成所有的协议程序
    cd $PROT && svn up $SVNP && sh ./genall.sh && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: Proto gen."
    fi

    # 更新所有配置加载程序
    cd $CFGLOAD && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP ConfigLoad."
    fi

    # 更新所有配置数据文件
    cd $CFGTABL && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP Config Table."
    fi

    # 更新所有地图配置文件
    cd $MAP && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP Config Table."
    fi

    # 更新所有杂项配置文件
    cd $MISC && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP Config Table."
    fi

    # 更新所有任务配置文件
    cd $TASK && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP TASK Table."
    fi
    # 更新所有SCRIPTS配置文件
    cd $SCRIPTS && svn up $SVNP && cd -
    if [ $? -ne 0 ]; then
        echo  "ERROR: svn up $SVNP SCRIPTS Table."
    fi

    # 复制所有配置加载程序
    copy_dir $CFGLOAD/ $CFGLOADDST/
    # 复制所有配置数据
    copy_dir $CFGTABL/ $CFGTABLDST/
    # 复制所有地图配置
    copy_dir $MAP/ $CFGMAPDST/
    # 复制所有的杂项配置
    copy_dir $MISC/ $CFGMISCDST/
    # 复制所有的任务配置
    copy_dir $TASK/ $CFGTASKDST/
    # 复制所有的npc配置
    copy_dir $SCRIPTS/ $CFGSCRIPTSDST/

fi #if [ "$0" == "./prepare.sh" ];

