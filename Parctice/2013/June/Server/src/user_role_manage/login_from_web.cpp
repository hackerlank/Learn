 /***********************************************
* Author: Tory
* date	: 2012.9.29
文件作用：处理flash客户端将web服务器返回的session传递给game server服务器进行游戏
******************************************************/
#include"command_user_role_manage.h"

#include"command_return_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"
//邮件系统操作头文件
#include "mail_systerm_interface.h"
//缓存操作类头文件
#include "my_memcached.h"
//缓存服务器管理类
#include "my_mem_group.h"

#include "read_rsa_key.h"

//用于连接memcached server的操作类对象，全局变量
// extern MyMemcache* mem_operate;
extern MyMemGroup* mem_group;

extern int sock_fd;

extern list<Role*> idle_role_list;
//Tory Add 2012.3.7引用全局变量声明
extern map<int, Role*> fd_to_pRole;
//在线角色容器
extern map<string, Hero*> heroId_to_pHero;                   
static char msg_login_info[1024];	 
void login_from_web(char *buffer)                  
{
	static unsigned streamNum = MY_TV_SEC;		//流水号
    int fd = sock_fd;                         	//登陆的fd
    int len_arg=0;
    int count=6;                            	//buffer里面真正的参数是从第六个开始的
	bool isTempGuest = false;
 	char session_key[400] = {0};				//web服务器返回给flash的session，400字节长
	char zoneIndexStr[32] = {0};				//区号
	int zoneIndex = DEFAULT_DB;
    count++;
	
	cout<<"[BisonShow] There is one member come from web"<<endl;
	cout<<"[BisonShow] There is one member come from web"<<endl;
    
	len_arg = 172; //解析获得session_key   
    if(len_arg > 400)
    {
		cout<<"session key's length isn't fit"<<endl;
		closeConnect(sock_fd);
        return;
    }
	
	UserInform user;//用于解析获取用户注册信息
	
	if (strlen(buffer + count) <= 1)
	{
		memset(user.userName, 0, sizeof(user.userName));
		sprintf(user.userName, "TempGuest%012d", streamNum++);
		isTempGuest = true;
		cout<<"The Role is a temp role from web we would never let it fly!"<<endl;
	} else {
		strncpy(session_key, buffer + count, len_arg);
		
		session_key[len_arg] = '\0';
		
		for(int k = 0; k < len_arg; k++)
		{
			if (session_key[k] == ' ')
			{
				session_key[k] = '+';
			}
		}
		
		int len = 0;
		char decData[400];
		len = len_arg;
		char session[400] = {0};
		Base64_Decode(session, session_key, 172);
		
		len = RSA_public_decrypt(128, (const unsigned char *)session, (unsigned char *)decData, pubKey, RSA_PKCS1_PADDING);
		if(len==-1)
		{
			printf("[BisonWarn] RSA_public_decrypt failed\n");
			char msg[1024] = {0};
			sprintf(msg, "0,1,0");
			send_msg(sock_fd, msg);
			closeConnect(sock_fd);
			return;
		}
		
		
		count += len_arg;
		len_arg = buffer[count++];
		strncpy(zoneIndexStr, buffer + count, len_arg);
		zoneIndex = atoi(zoneIndexStr);
		cout<<"[BisonShow]: the hero login from web is come from "<<zoneIndex<<endl;
		cout<<"[BisonShow]: the hero login from web is come from "<<zoneIndex<<endl;
		
		string temp = decData;
		int pos = 0;
		string oneString;
		int j = 0;
		int time;
		while (!temp.empty())
		{
			pos = temp.find('_');
			if (pos == -1)
			{ 
				//防止最后一个没加"_"
				oneString = temp;
				temp = "";
			} else {
				oneString = temp.substr(0, pos);
				temp = temp.substr(pos + 1);
				
			}
			++j;
			
			if (j == 2)
			{ 
				strncpy(user.userName, oneString.c_str(), oneString.size() + 1);
			}
			if (j == 4)
			{
				time = atoi(oneString.c_str());
			}
		}
			
		int subTime = MY_TV_SEC - time;
		if (subTime < 0)
		{
			subTime = -subTime;
		}
		cout<<"[Bisonshow] the hero away time is "<<subTime<<" MY_TV_SEC is "<<MY_TV_SEC<<" time is"<<time<<endl;
		if (subTime > 86400)
		{
			cout<<"[BisonWarn] the hero is too long away!"<<endl;
			char msg[1024] = {0};
			sprintf(msg, "0,1,0");
			send_msg(sock_fd, msg);
			closeConnect(sock_fd);
			return;
		}
		//strncpy(user.userName, decData+37, MAX_NAME_LEN);
		strncpy(user.passWord, "passwd", MAX_WORD_LEN);

	}
	
	Role *player = NULL;
    int size = 0;
	int where = 0;
    MemRole *memRole = NULL;
	if (!isTempGuest)
	{
		// memRole = (MemRole*)mem_operate->get_mem_data(user.userName, &size);
		memRole = (MemRole*)mem_group->get_data(user.userName, &size, &where, zoneIndex);      //默认从1服登陆,
	}	
    if(memRole != NULL)
    {
		cout<<"-------in user_manage_login,will test memRole data---------"<<endl;
        show_memRole_data(memRole);
		
		if(idle_role_list.size() == 0)
		{
			cout<<"have no idle Role data"<<endl;
			char msg[1024] = {0};
			sprintf(msg, "0,1,0");
			send_msg(sock_fd, msg);
			closeConnect(sock_fd);
			return ;
		}
		Role *player = idle_role_list.front();
		idle_role_list.pop_front();
		player->loadRoleData(memRole, fd, zoneIndex);
	
		pair<map<int, Role*>::iterator, bool> ret;
		ret =  fd_to_pRole.insert(map<int, Role*>::value_type (sock_fd, player));
		if(ret.second == true)
		{
			cout<<"insert Role* to fd_to_pRole success"<<endl;
		} else
		{
			cout<<"insert Role* to fd_to_pRole failure"<<endl;
		} 

        //若当前登陆的玩家已创建角色,追加已创建的角色数据至消息中，并加载所创建的角色的邮件数据至game server中
        int len = 0;
		sprintf(msg_login_info,"0,%d,%d,%s,%d,%d",LOGIN_RETURN_SELF,SUCCESS,user.userName,isTempGuest,memRole->idSize);		
		
        for(int i=0; i < memRole->idSize; i++)
        {
			//取Mem数据；
			len=strlen(msg_login_info);
			// MemHero *mem_data_hero = (MemHero*)mem_operate->get_mem_data(memRole->my_hero_infor_list[i].heroId, &size);
			MemHero *mem_data_hero = (MemHero*)mem_group->get_data(memRole->my_hero_infor_list[i].heroId, &size, &where, zoneIndex);
			cout<<"[Bisonshow:] where is "<<where<<" and zoneIndex is "<<zoneIndex<<" and player get area is "<<player->getArea()<<endl;
			len=strlen(msg_login_info);
			if(mem_data_hero)
			{
				snprintf(msg_login_info+len,1024-len,",%s,%s,%s,%d,%s",memRole->my_hero_infor_list[i].heroId,memRole->my_hero_infor_list[i].nickName,memRole->my_hero_infor_list[i].party,mem_data_hero->level,memRole->my_hero_infor_list[i].photoId);
			}
			else{
				snprintf(msg_login_info+len,1024-len,",%s,%s,%s,%d,%s",memRole->my_hero_infor_list[i].heroId,memRole->my_hero_infor_list[i].nickName,memRole->my_hero_infor_list[i].party,1,memRole->my_hero_infor_list[i].photoId);
			}			
			free(mem_data_hero);
        }
		free(memRole);
		send_msg(sock_fd,msg_login_info);   
		
		cout<<"[XHM MSG] Right msg_login_info:"<<msg_login_info<<endl;
		return;
	} else
    {
        cout<<"get memRole data from server is NULL,will register a new Role"<<endl;
		if(idle_role_list.size() == 0)
		{
			cout<<"have no idle Role data"<<endl;
			char msg[1024] = {0};
			sprintf(msg, "0,1,0");
			send_msg(sock_fd, msg);
			closeConnect(sock_fd);
			return ;
		}
		Role *player = idle_role_list.front();
		idle_role_list.pop_front();

		player->initNewRole(user, sock_fd, zoneIndex);				
	    //将memRole数据存入memcached server
		player->memSet();
		pair<map<int, Role*>::iterator, bool> ret;
		ret =  fd_to_pRole.insert(map<int, Role*>::value_type (sock_fd, player));
		if(ret.second == true)
		{
			cout<<"insert Role* to fd_to_pRole success"<<endl;
		} else
		{
			cout<<"insert Role* to fd_to_pRole failure"<<endl;
		}	

		sprintf(msg_login_info,"0,%d,%d,%s,%d,0",LOGIN_RETURN_SELF,SUCCESS,user.userName,isTempGuest,0);//xhm add;
		send_msg(fd, msg_login_info);	
		cout<<"[XHM MSG] Right msg_login_info:"<<msg_login_info<<endl;
        return;		
    }
		

}

void temp_guest_change_name(char* buffer)
{
	char *newUserName;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(newUserName);
	cout<<"temp_guest_change_name::::DDDDDDDDDDDDDDDDD "<<newUserName<<endl;
	char oldUserName[51] = {0};
	strncpy(oldUserName, pg_role->getUserName(), sizeof(oldUserName));
	int ret = 0;
	char msg[400] = {0};
	if (strlen(oldUserName) != 21 || strncmp(oldUserName, "TempGuest", 9) != 0)
	{
		//不是临时用户，账号不能改名
		ret = 1;
		sprintf(msg, "0,2,%d", ret);
		send_msg(sock_fd, msg);
		return;
	}
	
	int size = 0;
	int where = 0;
	// MemRole *memRole = (MemRole*)mem_operate->get_mem_data(oldUserName, &size);
	MemRole *memRole = (MemRole*)mem_group->get_data(oldUserName, &size, &where, DEFAULT_DB);
	if (memRole == NULL)
	{
		ret = 2;
		//缓存中未有玩家账号信息
		sprintf(msg, "0,2,%d", ret);
		send_msg(sock_fd, msg);
		return;
	}
	
	// MemRole *testMemRole = (MemRole*)mem_operate->get_mem_data(newUserName, &size);
	MemRole *testMemRole = (MemRole*)mem_group->get_data(newUserName, &size, &where, DEFAULT_DB);
	if (testMemRole != NULL)
	{
		ret = 3;
		//新改用户名已经被使用
		sprintf(msg, "0,2,%d", ret);
		send_msg(sock_fd, msg);
		free(testMemRole);
		return;
	}
	
	free(memRole);
	pg_role->changeUserName(newUserName);
	// mem_operate->delete_mem_data(oldUserName);
	mem_group->delete_data(oldUserName, DEFAULT_DB);
	sprintf(msg, "0,2,0");
	send_msg(sock_fd, msg);
}