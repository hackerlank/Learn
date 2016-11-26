/****************************************************************
* Filename: mail_systerm_interface.h
* Authof:	Tory
* Date:		2012.9.17 
* Description: 邮件系统头文件，用于构建邮件数据的自定义结构类型，
			   邮件外部文件读取和生成，邮件数据的加载和处理函数实现
*****************************************************************/
#ifndef MAIL_SYSTERM_INTERFACE_
#define MAIL_SYSTERM_INTERFACE_

#define MAIL_INFOR_CONTENT	2048		//邮件所含内容最大长度
#define MAIL_THEME_SIZE		50			//邮件主题最大长度，50字节
#define MAIL_CONTENT_SIZE	900			//文本邮件内容长度,客户端可接受长度为444字节

#include <string>
#include <list>
#include "libev.h"
#include "wholeDefine.h"
using namespace std;


//文本邮件，邮件内容最大900个字节（290个汉字）,收件人最长昵称最大16个字节（5个中文），主题最长32个字节（10个中文）；结构体Mail_Txt总计1040个字节
typedef struct mail_txt
{
	char	mail_id[50];					//this mail_id is useless <tory>
	char	isRead;							//是否已读(0:收件箱邮件已读，1：收件箱邮件未读；2：该邮件为发件箱中邮件)
	char	nickName[50];					//发件人昵称
	char 	theme[MAIL_THEME_SIZE];			//邮件主题
	char	content[MAIL_CONTENT_SIZE];		//邮件内容
	int     money;							//附件金钱数
	int     gamegold;						//附件元宝数目
	char	good1_id[15];					//附件内第一件物品的Id
    int     good1_num;					 	//附件内第一件物品的数目
	char    good2_id[15];					//附件内第二件物品的Id
	int     good2_num;						//附件内第二件物品的数目
	char    good3_id[15];					//附件内第三件物品的Id
	int 	good3_num;						//附件内第三件物品的数目
	char	good4_id[15];					//附件内第四件物品的Id
	int		good4_num;						//附件内第四件物品的数目
	mail_txt();
	mail_txt(char* _nickName, char* _theme, char* _content)
	{
		isRead = 1;			//默认为未读
		money = 0;			//默认金钱为0
		gamegold = 0;		//默认金币为0
				
		if((int)strlen(_nickName) < 50)		strncpy(nickName, _nickName, 50);
		else	memset(nickName, 0,50);
		if((int)strlen(_theme) < MAIL_THEME_SIZE-1)		strncpy(theme, _theme, MAIL_THEME_SIZE);
		else	memset(theme, 0, MAIL_THEME_SIZE);
		if((int)strlen(_content) < MAIL_CONTENT_SIZE-1)		strncpy(content, _content, MAIL_CONTENT_SIZE);
		else	memset(content, 0, MAIL_CONTENT_SIZE);
		
		good1_num = 0;
		good2_num = 0;
		good3_num = 0;
		good4_num = 0;	//物品数目为0
		memset(good1_id, 0,15);
		memset(good2_id, 0,15);
		memset(good3_id, 0,15);
		memset(good4_id, 0,15);
	}
}Mail_Txt;

//邮件系统处理需用到的数据结构，用于存储从外部文件中读取的邮件信息
typedef struct mail_infor
{
	int 	mail_time;					//邮件的生成时间，linux时间；暂用4字节整型存储
	char 	identity[IDL];				//id
	int		data_type;					//邮件数据的操作类型（0：收到的邮件 1：发送的邮件 2：下线消息处理）
	char	data[MAIL_INFOR_CONTENT];	//邮件内容,最长字节2048
	mail_infor()
	{
		mail_time = 0;
		data_type = 0;
		memset(identity,'\0',sizeof(identity));
		memset(data, 0, MAIL_INFOR_CONTENT);
	}	
}Mail_Infor;


//邮件列表，用于储存到game server中的角色邮件列表数据
typedef struct mail_list
{
	int unhandle_message_size;				//未处理消息数目
	Mail_Infor mail_unhandle_message[100];	//以邮件形式表示的未处理消息
	
	int mail_list_size;						//收到的文本邮件数目
	Mail_Infor mail_txt_infor[100];			//角色收件箱邮件内容	
	
	int mail_send_size;						//发送的文本邮件数目
	Mail_Infor mail_send_infor[100];		//发件箱
}Mail_list;

class MailSystermInterface
{
	public:
		static int createMailDir();
	
		static int load_mail_data(string heroId);		//按角色ID从外部文件加载相应的邮件数据至game server中,返回值表示邮件的数目，返回-1表示数据错误
	
		static int create_mail_data(string heroId, int data_type, int data_len, char* data);
		
		static int handle_mail_data(string heroId);		//解析邮件内容，分析邮件处理方式
				
		static int add_mail_data(Hero* myHero, int data_type, int data_len, Mail_Txt* );	//向在线角色添加邮件（data_type 0：收件；data_type 1发件）
};	

//以下结构体用于mail_systerm_test.cpp中测试邮件系统接口，在游戏代码中，请不要调用 Tory
typedef struct user_infor
{
	int 	id;
	char	name[16];
	user_infor(int _id, char* _name)
	{
		id = _id;
		strncpy(name, _name, 16);
	}
}User_Infor;

//用于mail_systerm_test.cpp中测试邮件系统接口，游戏代码中请勿调用 Tory
int show_mail_data(char* data, char *outfile);

void show_mail_infor(Mail_Infor &mail_infor);

void show_mail_list(Mail_list &mail_list);
#endif
