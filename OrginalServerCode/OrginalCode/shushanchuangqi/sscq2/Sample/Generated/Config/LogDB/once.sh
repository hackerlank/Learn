#!/bin/bash
# 这个文件只在每次更新的时候执行一次
# 执行完后会被自动化脚本删除
if [ $# -lt 5 ]; then
    echo "ERROR: usage ./once.sh %s %s %s %u %s"
    return -1
fi
chmod +x ./update.sh && ./update.sh $1 $2 $3 $4 $5
