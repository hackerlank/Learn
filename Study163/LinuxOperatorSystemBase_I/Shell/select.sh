#!/bin/bash
#选择分支练习
#测试参数是否有可执行权限,如果有,输出ok,否则输出fail
test -x $1 && echo "$1 ok" || echo "fail"

#if 后面的中括号前后必须要有空格,否则会报错
if [ -x $1 ]
then
    echo "$1 is executable"
elif [ -x $2 ]
then
    echo "$1 is not executable but $2 is executable"
else
    echo "$1 and $2 is not executable"
fi

#赋值符号中间不能有空格
val=$3
case $val in
    a)
        echo "val is A"
        ;;
    b)
        echo "val is B"
        ;;
    *)
        echo "val is other"
        ;;
esac

#-le:小于或者等于
#let val++ 等同于val += 1
while [ $val -le 10 ]
do
    echo "val : $val"
    let val++
done

until [ $val -le 10 ]
do
    echo "until :$val"
    let val--
done

for val in a b c d e
do
    echo "val : $val"
done
