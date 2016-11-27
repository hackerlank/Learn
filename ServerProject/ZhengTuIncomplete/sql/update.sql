-- 数据库升级脚本，每次出版本时需要维护根新脚本内容
-- database.py脚本的update参数文件
#chenzhen 2015-03-11
alter table SERVERLIST add 'PORT' int(10) unsigned NOT NULL default '0'; 
alter table SERVERLIST add 'OUTPORT' int(10) unsigned NOT NULL default '0'; 
alter table SERVERLIST add 'TYPE' int(10) unsigned NOT NULL default '0'; 
alter table SERVERLIST add 'NAME' VARCHAR(20);
alter table SERVERLIST add 'IP' VARCHAR(20);
alter table SERVERLIST add 'OUTIP' VARCHAR(20);
