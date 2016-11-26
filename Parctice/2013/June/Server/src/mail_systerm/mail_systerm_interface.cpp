#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <map>
#include <time.h>
#include "my_time.h"

#include "mailSysterm.h"

#include "mail_systerm_interface.h"

//离线未处理事件
#include "offline_unhandle_event.h"
using namespace std;

extern map<string, MailSysterm*> mail_map;	//tory add 

/** 邮件数据存放路径 added by Tory**/
extern string mail_data_url_T;

// 服务器开启时，先检查邮件数据文件夹是否存在,不存在则创建，出错返回-1，成功返回0
int MailSystermInterface::createMailDir()	
{
	if(access(mail_data_url_T.c_str(), F_OK) < 0)
	{
		if(mkdir(mail_data_url_T.c_str(), 0755) < 0)
		{
			cout<<"@@Tory mkdir error"<<endl;
			return -1;
		}
		cout<<"@@Tory createMailDir success:"<<mail_data_url_T<<endl;
		return 0;
	}
	return 0;
}	
/*
* author: 	Tory
* date	:	2012/9/17 
* 传入参数：heroId 角色ID
* 返回值：	int数值，表示邮件的数目，返回-1表示数据错误
* Description: 角色上线时，从外部文件加载邮件数据，.bin文件为角色正常下线服务器为其保存的邮件数据，.bin.bak文件为服务器异常断开，备份的邮件数据；
			   若服务器异常断开后，不能使用系统发送邮件的功能，否则将导致邮件数据丢失<tory> 2013.3.12
*/
int MailSystermInterface::load_mail_data(string heroId)
{
	FILE *in;
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	
	bool need_rename = true;	//对邮件数据外部文件是否需重命名备份，默认为true
	MailSysterm* m_s = new MailSysterm();

	//检查当前用户是否需要从.bak中恢复邮件数据
	if(access(mail_data_url.c_str(), R_OK) < 0)
	{
		mail_data_url += ".bak";	//mail_data_url改为从.bak中读取数据
		if(access(mail_data_url.c_str(), R_OK) < 0)	
		{
			fprintf(stdout,"no mail_data to read\n", mail_data_url.c_str());
			mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
			cout<<"@@Tory mail_map.size():"<<mail_map.size()<<endl;
			return 0;
		}	
		need_rename = false;
	}
	
	if((in = fopen(mail_data_url.c_str(), "r")) == NULL)
	{
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
		cout<<"@@Tory mail_map.size():"<<mail_map.size()<<endl;
		return -1;
	}

	Mail_Infor mail_infor;
	while(fread((void*)&mail_infor, sizeof(Mail_Infor), 1, in) == 1)
	{
	//	show_mail_infor(mail_infor);
		m_s->load_mail_infor(mail_infor);
	}

	mail_map.insert(map<string, MailSysterm*>::value_type(heroId, m_s));
	
	if(fclose(in) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	}
	
	if(need_rename == true)//邮件数据需重名备份
	{
		string mail_data_url_new = mail_data_url + ".bak";
		if(rename(mail_data_url.c_str(), mail_data_url_new.c_str()) < 0 )
		{
			fprintf(stderr, "rename file %s error!\n", mail_data_url.c_str());
			return -1;
		}
	}	
}

/*
* author: 	Tory
* date	:	2012/9/18 
* 传入参数：heroId, data_type:数据类型 data_len:数据大小（小于2048） data:二进制数据内容
* 返回值：	int行数值，表示邮件的数目，返回-1表示数据错误
* Description: 按角色ID向外部文件写入邮件数据，传入的数据大小不超过2048字节
*/
int MailSystermInterface::create_mail_data(string heroId, int data_type, int data_len, char* data)
{
	//数据太大，存储不成功
	if(data_len > MAIL_INFOR_CONTENT)
	{
		fprintf(stderr, "data_len error\n");
		return -1;
	}
	
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	//如果文件存在，以追加模式打开，如果该文件不存在，则创建
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		return -1;
	}

	Mail_Infor mail_infor;
	mail_infor.mail_time = MY_TV_SEC;	//记录时间
	
	char* uuid = cid();		//must release by caller <tory>
	strncpy(mail_infor.identity, uuid, IDL + 1);	//生成id
	free(uuid); 
		
	mail_infor.data_type = data_type;	//邮件数据类型
	memmove(mail_infor.data, data, MAIL_INFOR_CONTENT);
	
	// memmove(mail_infor.data, data, strlen(data));
	
	//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
	if(fwrite((void*)&mail_infor, sizeof(Mail_Infor), 1, out) != 1)
	{
		fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
		return -1;	
	}

	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	} 
	

}

/*
* author: 	Tory
* date	:	2012/9/18 
* 传入参数：heroId, data_type:邮件数据类型（data_type 0：收件；data_type 1发件） data_len:数据大小（小于2048） data:数据内容
* 返回值：	int型数值，表示邮件的数目，返回-1表示数据错误
* describe: 向在线角色的MailSysterm添加邮件（data_type 0：收件；data_type 1发件），同时将邮件数据写入.bak文件，防止服务器意外断开来不及保存新的邮件内容至.bin中
* 
*/
int MailSystermInterface::add_mail_data(Hero* myHero, int data_type, int data_len, Mail_Txt* m_t)
{
	//数据太大，存储不成功
	if(data_len > MAIL_INFOR_CONTENT || myHero == NULL)
	{
		fprintf(stderr, "data_len error or myHero is NULL\n");
		return -1;
	}
	
	string heroId = myHero->getIdentity();
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		fprintf(stderr, "data_len error\n");
		return -1;
	}
	MailSysterm* m_s = iter->second;
	
	Mail_Infor mail_infor;
	mail_infor.mail_time = MY_TV_SEC;	//记录时间
	
	char* uuid = cid();		//must release by caller <tory>
	strncpy(mail_infor.identity, uuid, IDL+1);	//生成Mail_Infor id
	free(uuid); 
		
	mail_infor.data_type = data_type;	//邮件数据类型（data_type 0：收件；data_type 1发件）
	memmove(mail_infor.data, (void*)m_t, data_len);
	
	/* 先将新的邮件数据加载进game_server进程的内存 */
	if(!m_s->load_mail_infor(mail_infor))	
	{
		fprintf(stderr, "load_mail_infor error\n");
		return -1;
	}	
	// fprintf(stderr, "load_mail_infor to game_server success\n");
	
	/* 再打开外部文件，将新的邮件数据写入至以.bak为后缀的外部文件中，防止服务器意外断开，导致新的game_server中的邮件丢失  2013.3.12 tory*/
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//" + heroId;
	mail_data_url += ".bin.bak";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	//如果文件存在，以追加模式打开，如果该文件不存在，则创建
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){
		fprintf(stderr, "fopen file %s to read error!\n", mail_data_url.c_str());
		return -1;
	}
		
	//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
	if(fwrite((void*)&mail_infor, sizeof(Mail_Infor), 1, out) != 1)
	{
		fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
		return -1;	
	}

	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return -1;
	}
	
	
	/*向在线角色的收件箱中添加邮件成功，且保存至外部文件成功，将新的邮件以17,5发送给收件人 */
 	if(data_type == 0)
	{
		time_t seconds = mail_infor.mail_time;//邮件的生成时间
		struct tm *tmp = localtime(&seconds);	
			
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 17, 5, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%02d-%02d", mail_infor.identity, m_t->nickName,m_t->theme,tmp->tm_mon + 1,tmp->tm_mday);
		cout<<"@@Tory 100000 recevier message:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
	}
	/*向自己的发件箱添加邮件成功，且保存至外部文件成功，将收件箱的邮件以17,3,1返回给自己 */
	if(data_type == 1)
	{
		time_t seconds = mail_infor.mail_time;//邮件的生成时间
		struct tm *tmp = localtime(&seconds);	
			
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 17, 3, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%02d-%02d", mail_infor.identity, m_t->nickName,m_t->theme,tmp->tm_mon + 1,tmp->tm_mday);
		cout<<"@@Tory 200000 recevier message:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
	}
	return 0;	

}

/*
* author: 	Tory
* date	:	2012/9/18 
* @@heroId: 角色ID
* 返回值：	出错返回-1，成功返回0
* Description: 按角色ID从game server的mail_map中获得个人邮件数据，处理角色下线期间受到的邮件
*/
int MailSystermInterface::handle_mail_data(string heroId)		
{
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())
		return -1;
	
	MailSysterm* m_s = iter->second;
	m_s->mail_handle(heroId);

}

//以下三个函数用于测试邮件数据 Tory
void show_mail_infor(Mail_Infor &mail_infor)
{
	//将时间（秒）转换成本地格式，如：2012-09-22 15:22:17
	time_t seconds =  mail_infor.mail_time;
	struct tm *tmp = localtime(&seconds);	
//	printf("%d-%02d-%02d %02d:%02d:%02d\n",	tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	char url[50] = {0};
	sprintf(url,"mail%d_%d_%d.txt",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
//	printf("mail_infor.data_type:%d\n", mail_infor.data_type);
//	printf("mail_infor.data:%s\n", mail_infor.data);
	show_mail_data(mail_infor.data, url);
}

int show_mail_data(char* data, char *outfile)
{
	FILE *out;
	if((out = fopen(outfile, "w+")) == NULL){
		fprintf(stderr, "fopen file %s error!\n", outfile);
		return -1;
	//	exit(EXIT_FAILURE);
	}
 	fprintf(out, "test HeroData isRead:%d\n", ((Mail_Txt*)data)->isRead);
	fprintf(out, "test HeroData nickName:%s\n", ((Mail_Txt*)data)->nickName);
	fprintf(out, "test HeroData theme:%s\n", ((Mail_Txt*)data)->theme);
	fprintf(out, "test HeroData content:%s\n", ((Mail_Txt*)data)->content);fprintf(out, "test HeroData money:%d\n", ((Mail_Txt*)data)->money);fprintf(out, "test HeroData gamegold:%d\n", ((Mail_Txt*)data)->gamegold);
	fprintf(out, "test HeroData good1_id:%s\n", ((Mail_Txt*)data)->good1_id);
	fprintf(out, "test HeroData good1_num:%d\n", ((Mail_Txt*)data)->good1_num);
	fprintf(out, "test HeroData good2_id:%s\n", ((Mail_Txt*)data)->good2_id);
	fprintf(out, "test HeroData good2_num:%d\n", ((Mail_Txt*)data)->good2_num);
	fprintf(out, "test HeroData good3_id:%s\n", ((Mail_Txt*)data)->good3_id);
	fprintf(out, "test HeroData good3_num:%d\n", ((Mail_Txt*)data)->good3_num);
	fprintf(out, "test HeroData good4_id:%s\n", ((Mail_Txt*)data)->good4_id);
	fprintf(out, "test HeroData good4_num:%d\n", ((Mail_Txt*)data)->good4_num);		

	if(fclose(out) != 0){
		fprintf(stderr, "fclose file error!\n");
		return -1;	
	//	exit(EXIT_FAILURE);
	} 	

	return 0;

}
