/*
        文件类型：实现文件
        文件名称：role.cpp
        文件作用：实现类Role里面的成员函数
*/
#include"role.h"
#include"other_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"			
//所有工具函数的头文件
#include"command_other_function_all_over.h"	
#include"hero_configuration.h"
#include<iostream>
#include<map>
#include"command_user_role_manage.h"
#include"skill.h"
#include"skill_configuration.h"
#include"hero_help.h"
#include"user_role_manage_growup.h"
#include"bottle.h"
#include"trap.h"
#include"monsterBase.h"
#include"heroCpyRecord.h"
#include"boxAsist.h"

//缓存操作类
#include "my_memcached.h"
//缓存服务器管理类
#include "my_mem_group.h"

extern MyMemGroup* mem_group;
//缓存操作类实例指针，全局变量
// extern MyMemcache* mem_operate;

//引用声明，Hero ID索引Hero对象指针的map容器，管理所有已初始化的Hero对象
extern map<string, Hero*> heroId_to_pHero;

extern map<string,Skill_Configuration*>id_to_skill;

extern map<string,Pick*> goods_to_hero;

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;

extern NickName2heroIdHash heroNameCheckHash;

extern char server_name[10];

Role::Role()
{
	strncpy(user.userName, "unknow", MAX_NAME_LEN+1);
	strncpy(user.passWord, "unknow", MAX_WORD_LEN+1);
	
    connect_fd = -1;  				//fd
    isLogin = false;               	//是否登陆标志，true表示已登陆				
    active_hero = NULL;             //当前活动角色指针
	
    memRole = (MemRole*)malloc(sizeof(MemRole));
    if(memRole == NULL)
    {
        printf("exit from Role(),cause out of memory" );
        exit(1);
    }
	
    memRole->user = user;
    memRole->idSize = 0;
	
	memset(memRole->cardId,'\0',sizeof(memRole->cardId));
}

//用于未存在的用户登陆游戏时，初始化新的用户数据
void Role::initNewRole(UserInform &_user, int _connect_fd, int _where)
{
    user = _user;
	where = _where;
    this->connect_fd = _connect_fd;  //fd
    isLogin = true;                 //是否登陆标志，true表示已登陆				
    active_hero = NULL;             //当前活动角色指针
	
    memRole->user = user;
    memRole->idSize = 0;
	hero_infor_list.clear();	//tory modify 2013.1.30
}

/**************************************
* Author:	Tory
* Date	:	2012.10.13
* Amend :	
* Description：用于已存在的用户登陆时，从memcached server中提取用户数据至game server中
***************************************/
void Role::loadRoleData(MemRole *_memRole, int _connect_fd, int _where)
{
	memmove(memRole, _memRole, sizeof(MemRole));
	user = memRole->user;           //用户资料
    
	where = _where;
    this->connect_fd = _connect_fd;  //fd
    isLogin = true;                 //是否登陆标志，true表示已登陆				
    active_hero = NULL;             //当前活动角色指针	

    //将玩家下所有角色信息导入game server中的hero_infor_list容器中
	if(memRole->idSize > 4 || memRole->idSize < 0)	//tory add 2012.12.18
	{
		memRole->idSize = 0;		
	}
	
	hero_infor_list.clear();	//tory modify 2013.1.30
	int i = 0;
    for(i; i < memRole->idSize&&i < 4; i++)	//tory modify 2012.12.25
    {        
		hero_infor_list.push_back(memRole->my_hero_infor_list[i]);  
    }

}

/*
* Author:	Cookie
* Date	:	2012.9.12
* Amend :	Tory 工具函数
* Description：需要向memcached server中存储memRole数据时调用
*/
void Role::memSet(void)
{
    // bool isSuccess = mem_operate->set_mem_data(user.userName, (char*)memRole, (int)sizeof(MemRole));
    // if(isSuccess == true)
    // {
        // cout<<"set memRole into memcached server success"<<endl;
    // } else
    // {
        // cout<<"set memRole into memcached server failure"<<endl;
    // }
	
	bool isSuccess = mem_group->set_data(user.userName, (char*)memRole, (int)sizeof(MemRole), Role::where);
    if(isSuccess == true)
    {
        cout<<"set memRole into memcached server success"<<endl;
    } else
    {
        cout<<"set memRole into memcached server failure"<<endl;
    }

}

/*
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description：玩家创建新角色时，将新创建的角色ID同时放入game_server 的heroId_set和memRole中
*/
void Role::addHeroInfor(My_hero_infor &hero_infor)
{
    if(Role::memRole->idSize >= ROLETOP)
    {
        return;
    } else
    {
		//将新创建的角色
        switch(Role::memRole->idSize)	
        {
        case 0:
            memRole->my_hero_infor_list[0] = hero_infor;
            cout<<"100000000000 "<<endl;
            break;
        case 1:
            memRole->my_hero_infor_list[1] = hero_infor;
			cout<<"200000000000 "<<endl;
            break;
        case 2:	
            memRole->my_hero_infor_list[2] = hero_infor;
            cout<<"300000000000 "<<endl;
            break;
        case 3:	
			memRole->my_hero_infor_list[3] = hero_infor;
            cout<<"400000000000 "<<endl;
            break;
        default :
            cout<<"wrong in role.cpp:153"<<endl;
            break;
        }
    
		Role::memRole->idSize++ ;  

    }
}


/*
* Author:	Tory
* Date	:	2012.9.12
* Description：将heroId对应的memHero数据从memcached server删除后，更新memRole中的角色列表
*/
void Role::deleteHero(char *heroId)
{
	if(heroId==NULL || strlen(heroId)==0)
	{
		return;
	}
	
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		//找到要删除角色的id在memRole.my_hero_infor_list下标，跳出循环	
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{
			break;			
		}
	}	
	// 从要删除的角色下标索引开始，将这以后的角色信息依次往前移动：这个逻辑貌似在考验智力……囧tory
	if(index < 4)
	{
		memRole->idSize--;//如果删除第四个角色，仅仅是把idsize减去1，我还以为下面memRole->my_hero_infor_list[index+1]会越界。
		for(index; index < memRole->idSize; index++)
		{
			memRole->my_hero_infor_list[index] = memRole->my_hero_infor_list[index+1];		
		}
	}

	if(hero_infor_list.size()<=0)	//xhm add 2012.12.25
	{
		return;
	}
	
	list<My_hero_infor>::iterator iter = hero_infor_list.begin();//tory modify 2012.12.25
	for(iter; iter != hero_infor_list.end(); iter++)
	{
		My_hero_infor my_hero_infor = *iter;
		if(strcmp(heroId, my_hero_infor.heroId) == 0)	
		{
			hero_infor_list.erase(iter);
			
			// NickName2heroIdHash::iterator sameNameiter = heroNameCheckHash.find(my_hero_infor.nickName);
			// if(sameNameiter != heroNameCheckHash.end())
			// {
				// heroNameCheckHash.erase(sameNameiter);
			// }	
			
			/**
				*删除用户名对应的heroId，有疑问RTX xhm，不要删除！
			*/
			// bool erase_name_inspeciton = mem_operate_nickname_inspection->delete_mem_data(my_hero_infor.nickName);
			// if(!erase_name_inspeciton)
			// {
				// puts("[XHM WARNING] mem_operate_nickname_inspection delete_mem_data nickname ERROR.");
			// }
			break;
		}
	}
	
	
	/********************* add start xhm *****************	
	//hashmap同名检查修改；请不要删除。
	if(strcmp(heroId,memRole->role4)==0)
    {
		NickName2heroIdHash::iterator nameiter = heroNameCheckHash.find(memRole->nickName4);
		if(nameiter != heroNameCheckHash.end())
		{
			heroNameCheckHash.erase(nameiter);	
		}
    }
	
	/********************* add end xhm *****************/

	//memRole数据已更新，将更新后的数据推送至memcached server
	memSet();	
}

char* Role::getUserName(void)
{
    return user.userName; 
}


//获得玩家已创建的角色信息列表
list<My_hero_infor>& Role::getHero_infor_list()
{
	return hero_infor_list;
} 

void Role::setLoginState(bool _isLogin)     //设置登陆状态
{
    isLogin = _isLogin;
}
bool Role::getLoginState()                  //获得登陆状态
{
    return isLogin;
}

string  Role::getActive_heroId()            //获取当前活动角色ID
{
    return active_heroId;
}
void    Role::setActive_heroId(string heroId)//设置当前活动角色ID
{
    active_heroId = heroId;
}

//设置活动角色指针
void Role::setActive_hero(Hero *_active_hero)                
{
    active_hero = _active_hero;
}

//获得活动角色指针
Hero*   Role::getActive_hero()              
{
    return active_hero;
}

/*
* Author: tory
* Date	: 2012.
  @ party:客户端发送过来的门派，为门派+A(坑爹的A)
  @ nickName:昵称
  @ heroTypeId：暂时无实际意义，方便日后扩展
*/
Hero* Role::create_hero(char *party, char *nickname, char *heroTypeId)        
{
    if(hero_infor_list.size() > 4)//xhm add warning msg;
	{
		cout<<"[XHM WARNING] The hero_infor_list.size():"<<hero_infor_list.size()<<endl;	
		return NULL;  //判断玩家创建的角色数目是否已到上限	
	}

	party[1] = '\0';	//客户端发过来的门派格式：门派+A,如华山则为：HA,坑爹，需将A去掉！！！
	cout<<"@@Tory 1000000 party:"<<party<<endl;
	Hero *myHero = new Hero(nickname, party, Role::where);
	
    //新创建完角色，玩家数据memRole中有重要修改，需更新memcached server中的memRole； Tory add
	char photoId[IDL] = {"HM00101"};	//H-->Hero，M-->Party，00101-->冗余数据
	photoId[1] = *party;

	My_hero_infor heroInfor(myHero->getIdentity(), nickname, party, photoId);
	hero_infor_list.push_back(heroInfor);
	Role::addHeroInfor(heroInfor);
    return myHero;	
}

My_hero_infor Role::getHeroInfor(char *heroId)
{
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{			//找到要删除角色的id在memRole.my_hero_infor_list下标，跳出循环	
			return my_hero_infor;
		}
	}
}


void	Role::setNickName(char *_nickName,char *heroId)
{
	if (_nickName==NULL||heroId==NULL)
	{
		return;
	}
	int index = 0;
	for(index; index < memRole->idSize; index++)
	{
		My_hero_infor my_hero_infor = memRole->my_hero_infor_list[index];
		if(strcmp(heroId, my_hero_infor.heroId) == 0)
		{					
			// cout<<"heroInfor.nickName before is "<<heroInfor.nickName<<endl;
			strncpy(memRole->my_hero_infor_list[index].nickName, _nickName, MAX_NAME_LEN+1);
			// cout<<"heroInfor.nickName after  is "<<heroInfor.nickName<<endl;
		}
	}
	memSet();
}

/*角色激活激活码*/
bool Role::useCardId(char *cardId)
{
	if(cardId == NULL || strlen(cardId) == 0)
	{
		cout<<"the card of argument cardId is NULL or empty:"<<endl;
		return false;
	}
	if(strlen(memRole->cardId) == 0)
	{
		strncpy(memRole->cardId,cardId,strlen(cardId));
		return true;
	}
	if(strcmp(memRole->cardId,cardId) == 0)
	{
		return true;
	}
	return false;
}

/*是否已用过激活码*/
bool Role::isUseCard(void)
{
	if(strlen(memRole->cardId) == 0)
	{
		return false;
	}
	return true;
}


//更改用户名
bool Role::changeUserName(char* newName)
{
	char log_msg[1024] = {0};
	
	//当有临时用户改名时，写一条日志
	sprintf(log_msg,"20,0,%s,%ld,%s,%s", server_name, MY_TV_SEC, user.userName, newName);
	write_log(log_msg);	
	strncpy(user.userName, newName, MAX_NAME_LEN+1);
	memRole->user = user;
	// cout<<"memRole's user name is "<<memRole->user.userName<<endl;
	int size = hero_infor_list.size();
	list<My_hero_infor>::iterator it_info = hero_infor_list.begin();
	for (int i = 0; i < size; i++, it_info++)
	{
		memRole->my_hero_infor_list[i] = *it_info;
	}
	
	memSet();
	
	// int size1 = 0;
	
	// MemRole *testMemRole = (MemRole*)mem_operate->get_mem_data(newName, &size1);
	// if (testMemRole == NULL)
	// {
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
		// cout<<"333333333333333333333333333333333333333333333333"<<endl;
	// } else {
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"4444444444444444444444444444444444444444444444444444"<<endl;
		// cout<<"userName is "<<testMemRole->user.userName<<endl;
	// }
	return true;
}

/* 获取当前用户所在服务器的区编号	 */
int Role::getArea()
{
	return where;
}

/*
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description：用于测试从memcached server中取出的memRole数据是否正确
*/
void show_memRole_data(MemRole *mem_data_role)
{
    if(mem_data_role != NULL)
    {
        cout<<"username:"<<mem_data_role->user.userName<<endl;
        cout<<"heroId list Size:"<<mem_data_role->idSize<<endl;

        int i = 0;
        for(i; i < mem_data_role->idSize; i++)
        {
			cout<<"************hero_infor:"<<i+1<<"  *****"<<endl;			
			printf("test my_hero_infor heroId:%s\n", mem_data_role->my_hero_infor_list[i].heroId);
			printf("test my_hero_infor nickName:%s\n", mem_data_role->my_hero_infor_list[i].nickName);
			printf("test my_hero_infor party:%s\n", mem_data_role->my_hero_infor_list[i].party);
			printf("test my_hero_infor photoId:%s\n", mem_data_role->my_hero_infor_list[i].photoId);
        }
    } 
}