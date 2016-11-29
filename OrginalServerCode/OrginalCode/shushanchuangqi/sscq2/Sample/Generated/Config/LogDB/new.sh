#!/bin/bash
if [ $# -lt 5 ]; then
    echo "ERROR: usage ./new.sh %s %s %s %u %s"
    return -1
fi
echo "initbegin!! $2:$3@$1:$4:$5"
mysql -h$1 -u$2 -p$3 -P$4 -D$5 < init.sql
echo "initend!!"
