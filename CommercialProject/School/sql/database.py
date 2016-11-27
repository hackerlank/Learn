#!/usr/bin/python2
# -*- coding:utf-8 -*-
import os,re,sys
updateFile = "update.sql"
startsqlFile = "start.sql"
ingore = ["SERVERLIST"]
help = "使用方法（新手慎用) [install,delete,update,updateall,reset,deletename,installname,serverlist,startsql],\n \
		install:   安装数据库，install.sql中的操作\n\
		delete:    删除除ingore表的其他所有表\n \
		update:    执行最近的一次更新操作（最近的注释＃行之后的操作）\n \
		updateall: 执行update.sql中所有的更新操作\n\
		reset:     清空除ingore表其他的所有数据库记录\n \
		deletename: 清空NAMESERVER记录 \n \
		installname: 创建NAMESERVER记录\n \
		serverlist: serverlist专用命令\n \
		startsql:  启动时需要执行的一些sql语句"
database = ["127.0.0.1","root","root","flyer"]
namedatabase = ["127.0.0.1","root","root","nameServer"]

server = [database]
nameserver = [namedatabase]

def dropMark(str):
	str = re.sub("#.*\n","",str)
	str = re.sub("--.*\n","",str)
	str = re.sub("/\*.*\*/","",str)
	return str
#-----------------------------------
def doCmd(str):
	str = dropMark(str);
	str = str.replace("\n","")
	str = str.replace("\t","")
	str = str.replace("'","")
	splitcmd = str.split(";")
	for zone in server:
		for index in range(len(zone)):
			if(index < 3):
				continue
			for sql in splitcmd:
				if(sql == "" or sql.isspace()):
					continue
				cmd = 'mysql -u '+ zone[1] +' -p' +zone[2] + ' -h' + zone[0] + ' -e' + '\"' + "use " + zone[index] + ";" + sql + ";" + '\"'
				#--print cmd
				#--print "\n"
				os.system(cmd)
#------------------------------------
def doNameCmd(str):
	str = dropMark(str)
	str = str.replace("\n","")
	str = str.replace("\t","")
	str = str.replace("'","")
	splitcmd = str.split(";")
	for zone in nameserver:
		for index in range(len(zone)):
			if(index < 3):
				continue
			for sql in splitcmd:
				if(sql =="" or sql.isspace()):
					continue
				cmd = 'mysql -u ' + zone[1] + ' -p' + zone[2] + ' -h ' + zone[0] + ' -e ' + '\"' + "use " + zone[index] + ";" + sql + ";" + '\"'
				print cmd
				print "\n"
				os.system(cmd)

#--------------------------------------------
def updateDatabase():
	update = open(updateFile,"r")
	text = ""
	for line in update:
		text += line
	text = text[text.rfind("#"):]
	doCmd(text)

#-------------------------------------------
def updateAllDatabase():
	update = open(updateFile,"r")
	text = ""
	for line in update:
		if(line.find("#") != -1):
			continue
		if(line.find(";") == -1):
			text += line
		else:
			text += line
			doCmd(text)
			text = ""

#----------------------------------------------
def installDatabase():
	install = open(installFile,"r")
	text = ""
	for line in install:
		if(line.find(";") == -1):
			text += line
		else:
			text += line
			doCmd(text)
			text = ""

#----------------------------------------------
def installNameDatabase():
	install = open(nameserverFile,"r")
	text = ""
	for line in install:
		if(line.find(";") == -1):
			text += line
		else:
			text += line
			doNameCmd(text)
			text = ""

#---------------------------------------------
def deleteDatabase():
	delete = open(installFile,"r")
	text = ""
	for line in delete:
		if(line.find("CREATE TABLE") != -1):
			table = re.compile("'.*'").search(line).group(0)
			table = table.replace("'","")
			if(table in ingore):
				continue
			text = "DROP TABLE IF EXISTS " + table + ";"
			doCmd(text)


#-------------------------------------------
def deleteNameDatabase():
	delete = open(nameserverFile,"r")
	text = ""
	for line in delete:
		if(line.find("CREATE TABLE") != -1):
			table = re.compile("'.*'").search(line).group(0)
			table = table.replace("'","")
			if(table in ingore):
				continue
			text = "DROP TABLE IF EXISTS " + table + ";"
			doNameCmd(text)

#--------------------------------------------
def startSQL():
	start = open(startsqlFile,"r")
	text = ""
	for line in start:
		if(line.find("#") != -1):
			continue
		if(line.find(";") == -1):
			text += line
		else:
			text += line
			doCmd(text)
			text = ""

#-------------------------------------------
def serverListSQL():
	start = open(serverListFile,"r")
	text = ""
	for line in start:
		if(line.find("#") != -1):
			continue
		if(line.find(";") == -1):
			text += line
		else:
			text += line
			doCmd(text)
			text = ""


#---------------------------------------------
def reset():
	reset = open(installFile,"r")
	text = ""
	for line in reset:
		if(line.find("CREATE TABLE") != -1):
			table = re.compile("'.*'").search(line).group(0)
			table = table.replace("'","")
			if(table in ingore):
				continue
			text = "TRUNCATE TABLE" + table + ";"
			doCmd(text)

#--------------------------------------------
if __name__ == "__main__":
	if len(sys.argv) != 2:
		print help
	elif sys.argv[1] == "update":
		updateDatabase()
	elif sys.argv[1] == "reset":
		reset()
	elif sys.argv[1] == "install":
		installDatabase()
	elif sys.argv[1] == "delete":
		deleteDatabase()
	elif sys.argv[1] == "updateall":
		updateAllDatabase()
	elif sys.argv[1] == "startsql":
		startSQL()
	elif sys.argv[1] == "installname":
		installNameDatabase()
	elif sys.argv[1] == "deletename":
		deleteNameDatabase()
	elif sys.argv[1] == "serverlist":
		serverListSQL()
	else:
		doCmd(sys.argv[1])
