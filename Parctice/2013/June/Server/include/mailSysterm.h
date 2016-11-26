/*
* Authof:	Tory
* Date:		2012.12.19 
* Description: 邮件系统	,		   
*/
#ifndef _MAIL_SYS_H
#define _MAIL_SYS_H

#include "mail_systerm_interface.h"
#include <list>
using namespace std;
class MailSysterm
{
private:
	map<string, Mail_Infor*> 	mail_Inbox;		//收件箱
	map<string, Mail_Infor*> 	mail_Outbox;	//发件箱	
	map<string, Mail_Infor*> 	mail_Unhandlebox;	//下线未处理消息
	int new_mail;		//新邮件数据
public:
	MailSysterm();
	~MailSysterm();		//角色下线时，将角色对应的邮件数据释放掉
	
	bool load_mail_infor(Mail_Infor& mail_infor);	//将单个邮件外部数据加载到MailSysterm对象中管理
	void load_mail_list(Mail_list& mail_list);		//将整个角色的邮件数据全部加载到MailSysterm对象中管理
	void mail_handle(string);	//处理邮件数据
	bool delet_mail_infor(int type, string mail_id);//删除邮件内容
	bool save_mail_data(string heroId);	//角色下线时，保存邮件数据
	
	bool get_mail_list(Hero* myHero, int type);
	bool get_mail_content(Hero* myHero, int type, string mail_id);
	
	bool getMailListNum(Hero* myHero); //describe:返回邮件系统中，收/发件箱的邮件数目
	bool mail_goods_receive(Hero* myHero, string mail_id);
};

bool time_compare(const Mail_Infor* first, const Mail_Infor* second); //自定义list比较函数，用于list排序比较
#endif
