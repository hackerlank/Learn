/*
* Filename: mail_systerm_communicate.h
* Authof:	Tory
* Date:		2012.9.17 
* Description: 用于客户端发邮件、收邮件、删邮件的功能
*/
#ifndef MAIL_SYSTERM_COMMUNICATE_
#define MAIL_SYSTERM_COMMUNICATE_

#include <string>
#include <iostream>
#include "mail_systerm_interface.h"
using namespace std;

class MailSystermCommunicate
{
public:
	
	static void get_mail_txt_list(char* buffer);		//客户端请求按面板页码获取邮件列表信息
		
	static void get_mail_content(char* buffer);			//获取单封邮件的内容
		
	static void send_mail(char* buffer);				//发送邮件 evan add 2012.9.24
		
	static void info_mail_all(char* buffer);			//请求当前玩家所有邮件的数量 evan add 2012.9.25
		
	static void mail_goods_receive(char *buffer);		//附件内物品的接受 evan 2012.9.25	in mail_systerm_send.cpp		

};
#endif







