#!/bin/sh
##清空并重装数据库

./database.by delete
sleep 5

./database.py install
sleep 5

./database.py updateall
sleep 10

./database.py deletename
sleep 5

./database.py installname


