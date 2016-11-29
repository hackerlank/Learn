#!/bin/bash
#H,U,P,PT,DBD will be exported by server
if [ $# -lt 5 ]; then
    echo "ERROR: usage ./new.sh %s %s %s %u %s"
    return -1
fi

echo "initbegin!! $2:$3@$1:$4:$5"
touch .newdbaction

#XXX: 新建立库需要这个检查
function TEST()
{
    ret=$?
    echo "ret :"$ret
    if [ $ret -gt 0 ]; then
        exit $ret
    fi
}

mysql -h$1 -u$2 -p$3 -P$4 -D$5 < init.sql;TEST

rm -f .newdbaction
echo "initend success!!"
