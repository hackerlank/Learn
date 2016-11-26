/*
		文件类型：头文件
		文件名称：role.h
		文件作用：定义Role类，此类即为玩家类
*/

#ifndef ROLE_H
#define ROLE_H
#include"hero.h"
#include"library_head.h"
#include"map_inform.h"
#include"pick.h"
#include"wholeDefine.h"

#include "my_memcached.h"


#if (__GNUC__ >= 3)
#define _BACKWARD_BACKWARD_WARNING_H    // needed for gcc 4.3
#include <ext/hash_map>
#include <ext/hash_set>
#undef _BACKWARD_BACKWARD_WARNING_H
#else
#include <hash_map>
#include <hash_set>
#include <map>
#endif

#if defined(__GNUC__)
using namespace __gnu_cxx;
#endif
struct eqstr
{
    inline bool operator() (const char*s1, const char*s2) const
    {
        return 0 == strcmp(s1, s2);
    }
};
// typedef hash_map<const char*,const char*,hash<const char*>, eqstr> NickName2heroIdHash;
typedef hash_map<const char*,const char*,hash<const char*>, eqstr> NickName2heroIdHash;

class Hero;

class Map_Inform;

using namespace std;

#define ROLETOP 4
typedef struct           //结构体，包含用户名和密码
{
	char userName[MAX_NAME_LEN+1];
	char passWord[MAX_WORD_LEN+1];
}UserInform;  

//用户创建的角色信息，用于角色选择时客户端的面板显示
typedef struct my_hero_infor
{
	char heroId[IDL+1];
	char nickName[MAX_NAME_LEN+1];
	char party[IDL+1];
	char photoId[IDL+1];
	int gradeNow;	//
	
	my_hero_infor(){}
	
	my_hero_infor(char* _heroId, char* _nickName, char* _party, char* _photoId,int _gradeNow=0)
	{
		strncpy(heroId, _heroId, IDL+1);
		strncpy(nickName, _nickName, MAX_NAME_LEN+1);
		strncpy(party, _party, IDL+1);
		strncpy(photoId, _photoId, IDL+1);
		gradeNow=_gradeNow;
	}
}My_hero_infor;

typedef struct
{
	UserInform 	user;
	int idSize;
	My_hero_infor my_hero_infor_list[4];
	char cardId[MAX_WORD_LEN+1];			//新手卡id
}MemRole;

class Role
{
private:
	MemRole*		memRole;			//用于存储值memcached server中的数据
	UserInform 		user;           	//用户资料
	list<My_hero_infor> hero_infor_list;	//已创建的角色信息列表
	
	int 			connect_fd;	        //fd
	bool			isLogin;			//是否登陆标志，true表示已登陆
	string			active_heroId;		//当前活动角色
	Hero			*active_hero;		//当前活动角色指针
	int				where;				//用户数据属于第几区，在用户登陆时初始化
private:	
	void 			inHeroId(void);
public: 
	Role();
	~Role(void){}
	
	void memSet(void);	
	//用于已存在的用户登陆游戏时，从memcached server中提取用户数据至game server中
	void loadRoleData(MemRole *_memRole, int connect_fd, int where);
	//用于未存在的用户登陆游戏时，初始化新的用户数据
	void initNewRole(UserInform &_user, int connect_fd,  int where);
	
	int 	getArea();						//获取当前用户所在服务器的区编号	
	char* 	getUserName(void);  			//获得用户名
	void 	setLoginState(bool _isLogin);	//设置登陆状态
	bool 	getLoginState();				//获得登陆状态
	
	string	getActive_heroId();					//获取当前活动角色ID	
	void	setActive_heroId(string heroId);	//设置当前活动角色ID
	Hero*	getActive_hero();					//获得活动角色指针
	void	setActive_hero(Hero *_active_hero);	//设置活动角色指针
	
	void 	addHeroInfor(My_hero_infor &hero_infor);	//玩家创建新角色成功，通过此函数修改memRole的数据
	
	list<My_hero_infor>& getHero_infor_list();			//获得玩家已创建的角色信息列表
		
	/*	2012.3.22 Tory Add */
	Hero* 	create_hero(char *party, char *nickname, char *heroTypeId);		//创建Hero对象
	void 	deleteHero(char *heroId);

	void	setNickName(char *_nickName,char *heroId);
	
	My_hero_infor getHeroInfor(char *heroId);	
	
	/*激活激活码*/
	bool useCardId(char *cardId);
	
	/*是否已用过激活码*/
	bool isUseCard(void);
	
	//更改用户名
	bool changeUserName(char* newName);
};

void show_memRole_data(MemRole *mem_data_role);	//用于测试从memcached server中获取到的数据是否正确 added by Tory

#endif

