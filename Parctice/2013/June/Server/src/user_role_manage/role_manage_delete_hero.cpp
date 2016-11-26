#include "command_user_role_manage.h"
#include "wholeDefine.h"
//缓存服务器管理类
#include"hero.h"
#include"set_camp.h"
#include "my_mem_group.h"
extern MyMemGroup* mem_group;
//缓存操作类实例指针，全局变量
// extern MyMemcache* mem_operate;

extern int from; 

extern int sock_fd;

extern int flag_registe_type_exit;

extern map<int, Role*> fd_to_pRole;

extern char server_name[10];
extern map<int,int> campNumber;

void deleteHero(char *buffer)                  
{
	int count=6;                            //buffer里面真正的参数是从第六个开始的
	unsigned char len_arg=0;
	len_arg=buffer[count++];
	char heroId[UUIDL+1] = {0};
	strncpy(heroId,buffer+count,len_arg);
	//删号处理 jolly 2013.4.2
	int size=0;
	int where;
	MemHero *memHero=(MemHero*)mem_group->get_data(heroId, &size, &where,from);
	if (memHero!=NULL)
	{
		int camp=memHero->camp;
		map<int,int>::iterator it;
		it=campNumber.find(camp);
		if (it!=campNumber.end())
		{
			int number=it->second;
			number--;
			if (number<0)
			{
				number=0;
			}
			campNumber.erase(it);
			campNumber.insert(map<int,int>::value_type(camp,number));
			saveCampNumber();
		}
		free(memHero);
	}	
	
	map<int, Role*>::iterator i=fd_to_pRole.find(sock_fd);
	Role *role=i->second;
	// bool isSuccess = mem_operate->delete_mem_data(heroId);
	bool isSuccess = mem_group->delete_data(heroId, from);
	if(isSuccess == true)
	{
		cout<<"delete hero from memcached success!"<<endl;
	}else{
		cout<<"delete hero from memcached failure!"<<endl;
	}
	
	My_hero_infor heroInform=role->getHeroInfor(heroId);
	/*记录删除角色的流水账 jolly 11.14 start*/
	char account_msg[1024]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%s,%s,%d",1,1,server_name,(int)myTime.tv_sec,role->getUserName(),heroInform.heroId,heroInform.nickName,heroInform.party,heroInform.gradeNow);
	write_log(account_msg);	
	/*记录删除角色的流水账 jolly 11.14 end*/
	
	//更新memRole下的角色列表
	role->deleteHero(heroId);
	
	//将memRole数据存入memcached server
    // role->memSet();
    //测试从memcached server中取出的memRole数据 Tory
	// role->show_memRole_data();	
}