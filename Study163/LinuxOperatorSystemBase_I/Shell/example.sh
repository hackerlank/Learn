#!/bin/bash

#读取一个自然数
read -p "请输入一个大于0的自然数:" base
if [$base -lt 0 ]
then
    echo "输入的数不对"
    exit
fi
#处理和输出
count=0
while [ $count -lt 10 ]
do
    let num=$base%3
    if [ $num -eq 0 ]
    then
        echo "get the num:$base"
        let count++
    fi
    let base++
done

