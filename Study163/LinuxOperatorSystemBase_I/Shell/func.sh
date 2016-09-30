#!/bin/bash

#函数定义1
hello()
{
    echo "fuck you"
}

#函数定义2
function Hello()
{
    echo "Fuck you"
}

function arg()
{
    echo "fuck you $1"
}

#函数调用
hello
Hello
arg fuckyou
