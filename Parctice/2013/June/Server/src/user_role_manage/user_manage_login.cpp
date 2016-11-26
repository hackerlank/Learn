#include"command_user_role_manage.h"
#include "hero.h"
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

#include"dictionary_asist.h"
//缓存操作类实例指针，全局变量
// extern MyMemcache* mem_operate;

extern MyMemGroup* mem_group;

extern int sock_fd;

extern list<Role*> idle_role_list;

//Tory Add 2012.3.7全局变量声明
extern map<int, Role*> fd_to_pRole;

//引用声明，Hero ID索引Hero对象指针的map容器，管理所有已初始化的Hero对象
extern map<string, Hero*> heroId_to_pHero;
extern map<int, Message_Receive>   message_queue;
extern set<string> innerIPSet;
extern int from;
static char msg_login_info[1024];

string getPhotoId(string party)
{
    string photoId = "H";
    photoId +=party;
    photoId +="00101";          //按角色等级选择图片组
    return photoId;
}


/*      
函数：void loginUser(char *buffer)        
作用：登陆函数，处理登陆命令
参数：buffer：注册命令字符串
返回值：void
*/
void loginUser(char *buffer)                  
{
	bool isTempGuest = false;							//是否为临时用户
    int fd = sock_fd;                       			//登陆的fd
    unsigned char len_arg=0;
    int count=6;                            //buffer里面真正的参数是从第六个开始的
   
    //解析获得用户名
    len_arg=buffer[count++];   
    if(len_arg>MAX_NAME_LEN)
    {
		sprintf(msg_login_info,"0,%d,%d,0,0",LOGIN_RETURN_SELF,FAILED);//xhm add;
        send_msg(fd, msg_login_info);		
        return;
    }	
	UserInform user;                        
	memset(user.userName, 0, MAX_NAME_LEN);
    strncpy(user.userName,buffer+count,len_arg);
    count+=len_arg; 

	//名字里有禁闭的标点符号，错误代码：3（NAME_ILLEGAL_FAILED）
	int userNameLen = strlen(user.userName);
	if (userNameLen == 21 && strncmp(user.userName, "TempGuest", 9))
	{
		isTempGuest = true;
	}
	
	int k = 0;
	for (k; k < userNameLen; k++)
	{
		if (user.userName[k] == ' '
			|| user.userName[k] == '\t'
			|| user.userName[k] == '\r'
			|| user.userName[k] == '\n'
			|| user.userName[k] == '\f')
		{
			sprintf(msg_login_info,"0,%d,%d,%s,%d,0",LOGIN_RETURN_SELF,FAILED,user.userName,isTempGuest, 0);//xhm add;
			send_msg(fd, msg_login_info);	
			return;
		}
	}

    //解析获得密码
    len_arg=buffer[count++];    
    strncpy(user.passWord,buffer+count,len_arg);
    user.passWord[len_arg]='\0';
    count+=len_arg;
	from = user.passWord[0]-'0';
  	// printf("userName:%s\t",user.userName);
    printf("Tory, the user come from:%d\n",from); 
	
    Role *player = NULL;
    int size = 0;
	int where = 0;	//memRole数据来源在第几区

    MemRole *memRole = (MemRole*)mem_group->get_data(user.userName, &size,&where,from);	
	// cout<<"@@Tory the data is come from:"<<where<<endl;	
	if(memRole != NULL)
    {	
		cout<<"-------in user_manage_login,will test memRole data---------"<<endl;
        show_memRole_data(memRole);
		
		if(idle_role_list.size() == 0)
		{
			cout<<"have no idle Role data"<<endl;
			free(memRole);
			return ;
		}
		Role *player = idle_role_list.front();
		idle_role_list.pop_front();		
        player->loadRoleData(memRole, fd, from);		
		pair<map<int, Role*>::iterator, bool> ret;
		ret =  fd_to_pRole.insert(map<int, Role*>::value_type (sock_fd, player));
		if(ret.second == true)
		{
			cout<<"user_manage_login::insert Role* to fd_to_pRole success"<<endl;
		} else
		{
			cout<<"user_manage_login::insert Role* to fd_to_pRole failure"<<endl;
		} 
		
        //若当前登陆的玩家已创建角色,追加已创建的角色数据至消息中，并加载所创建的角色的邮件数据至game server中
        int len = 0;
		sprintf(msg_login_info,"0,%d,%d,%s,%d,%d",LOGIN_RETURN_SELF,SUCCESS,user.userName, isTempGuest, memRole->idSize);
        for(int i = 0; i < memRole->idSize; i++)
        {
			len=strlen(msg_login_info);
			string myHeroId = memRole->my_hero_infor_list[i].heroId;
			
			int size = 0;
			// MemHero *mem_data_hero = (MemHero*)mem_operate->get_mem_data(myHeroId, &size);
			
			MemHero *mem_data_hero = (MemHero*)mem_group->get_data(myHeroId, &size, &where, player->getArea());
			if(mem_data_hero)
			{
				// msg_body += intTostring(mem_data_hero->level);
				
				snprintf(msg_login_info+len,1024-len,",%s,%s,%s,%d,%s",memRole->my_hero_infor_list[i].heroId,memRole->my_hero_infor_list[i].nickName,memRole->my_hero_infor_list[i].party,mem_data_hero->level,memRole->my_hero_infor_list[i].photoId);
			}
			else{
				snprintf(msg_login_info+len,1024-len,",%s,%s,%s,%d,%s",memRole->my_hero_infor_list[i].heroId,memRole->my_hero_infor_list[i].nickName,memRole->my_hero_infor_list[i].party,1,memRole->my_hero_infor_list[i].photoId);
			} 
			
			free(mem_data_hero);
        }
		free(memRole);	
		send_msg(sock_fd,msg_login_info);   
    } else
    {
        cout<<"get memRole data from server is failure,will init a new Role"<<endl;
		if(idle_role_list.size() == 0)
		{
			cout<<"have no idle Role data"<<endl;
			return ;
		}
		Role *player = idle_role_list.front();
		idle_role_list.pop_front();

		player->initNewRole(user, sock_fd, from);
		
		//将memRole数据存入memcached server
		player->memSet();

		pair<map<int, Role*>::iterator, bool> ret;
		ret =  fd_to_pRole.insert(map<int, Role*>::value_type (sock_fd, player));
		if(ret.second == true)
		{
			cout<<"user_manage_login::insert Role* to fd_to_pRole success"<<endl;
		} else
		{
			cout<<"user_manage_login::insert Role* to fd_to_pRole failure"<<endl;
		}
	
		sprintf(msg_login_info,"0,%d,%d,%s,%d,0",LOGIN_RETURN_SELF,SUCCESS,user.userName,isTempGuest,0);//xhm add;
		send_msg(fd, msg_login_info);	
        return;		
    }
}
