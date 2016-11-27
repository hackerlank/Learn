#启动数据库
/etc/init.d/mysqld start

#mysql用户名和密码
root root

#操作数据库
mysql -uroot -p

#增加运行权限
chmod +x ./test.py

#生成tags文件
ctags -R

#数据库插入语句
insert into links values('jerichen','gdsz');

#查看端口
netstat -apn | grep 8000
