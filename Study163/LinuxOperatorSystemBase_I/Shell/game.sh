#!/bin/bash
#此游戏为剪刀(J),石头(S),布(B)的游戏

#读取用户输入
function readUserInput()
{
    #赋值命令中间不能有空格
    ret=0
    while [ $ret -eq 0 ]
    do
        echo "请出拳(剪刀(J,j),石头(S,s),布(B,b)"
        read input
        case $input in
            J|j)
                echo "你出的是剪刀"
                ret=1
                break
                ;;
            S|s)
                echo "你出的是石头"
                ret=2
                break
                ;;
            B|b)
                echo "你出的是布"
                ret=3
                break
                ;;
            *)
                echo "你出的是无效拳,请重新出"
                ;;
        esac
    done
    return $ret
}

#电脑随机出拳
function rand()
{
    min=$1
    max=$(($2-min+1))
    num=$(date +%s%N)
    return $(($num%$max+$min))
}

#判断胜负
function judge()
{
    #-1:败 0:平 1:胜(不能返回负数)
    #0:败 1:平 2:胜
    ret=1
    userVal=$1
    rand 1 3
    computerVal=$?
    #cumputerVal=$(($RANDOM%3+1))
    case $computerVal in
        1)
            echo "电脑出的是剪刀"
            ;;
        2) 
            echo "电脑出的是石头"
            ;;
        3)
            echo "电脑出的是布"
            ;;
        *)
            ;;
    esac
    #平局
    if [ $userVal -eq $computerVal ]
    then
        echo "此局为平局"
    elif [ $userVal -lt $computerVal ]
    then
        if [ $userVal -eq 1 ]
        then
            if [ $computerVal -eq 3 ]
            then
                echo "此局胜"
                ret=2
            else
                echo "此局败"
                ret=0
            fi
        else
            echo "此局败"
            ret=0
        fi
    else
        if [ $userVal -eq 3 ]
        then
            if [ $computerVal -eq 1 ]
            then
                echo "此局败"
                ret=0
            else
                echo "此局胜"
                ret=2
            fi
        else
            echo "此局胜"
            ret=2
        fi
    fi
    return $ret
}


#主函数
function main()
{
    #清屏
    clear
    #进入游戏提示
    echo "欢迎来到剪刀,石头,布的游戏"
    #局数
    count=1
    #分数
    sum=0
    while [ $count -le 3 ]
    do
        echo "-----------------------第${count}局开始-------------------"
        readUserInput
        judge $?
        sum=$(($?+$sum))
        echo "-----------------------第${count}局结束-------------------"
        let count++
    done
    sum=$(($sum-3))
    if [ $sum -lt 0 ]
    then
        echo "三局结束,你的最后等分为$sum,输给电脑了"
    elif [ $sum -eq 0 ]
    then
        echo "三局结束,你的最后等分为$sum,平给电脑了"
    else
        echo "三局结束,你的最后等分为$sum,赢了电脑了"
    fi
}
main
