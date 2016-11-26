#include "set_camp.h"
#include"command_other_function_all_over.h"
#include "bootAssignment.h"
#include "data_structure_struct.h"
#include"bag_operator.h"
#include "my_mem_group.h"

using namespace std;
extern int g_msg_len;
extern Hero* pg_hero;
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;
extern map<int,int> campNumber;
extern MyMemGroup* mem_group;
void setCamp(char *buffer){
	int fd=sock_fd;                   			 	
	char msg_body[50];
	
	MSG_BEGIN(buffer, g_msg_len);	
	MSG_CHAR(char* hero_id);
	MSG_CHAR_END(char* campType);

	if(pg_hero->getCamp() >= 0 && pg_hero->getCamp() < 3)
	{
		cout<<"pg_hero->getCamp():"<<pg_hero->getCamp()<<endl;
		sprintf(msg_body,"11,6,10,%d",FAILED);
	    send_msg(fd, msg_body);
	    return;
	}

	map<int,int>::iterator it;
	int suggestCamp=0;
	int campHero=0;
	if (!campNumber.empty())
	{
		campHero=campNumber.begin()->second;
	}
	for (it=campNumber.begin();it!=campNumber.end();++it)
	{
		if (it->second<campHero)
		{
			campHero=it->second;
			suggestCamp=it->first;
		}
	}
	
	int index=atoi(campType);
	
	if(index>= 0 && index < 3)
		pg_hero->setCamp(index);	
	else
		index=-1;
	
	sprintf(msg_body,"11,6,%s,%d",hero_id,index);	
	
	
	Map_Inform *map_now;
	Nbox* box;
	
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);	
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
		
	box->getStaInSrcVec(obj);
	box->sentBoxMsg(msg_body);	
	
	// send_msg(fd,msg_body);
	
	if (index >= 0 && index < 3)
	 {
		// 更新加阵营任务成功
		char *campArgument="camp";
		pg_hero->updateHeroTaskStatus(JOIN_CAMP_TASK_NEED_TYPE, campArgument, 1);
		if (suggestCamp==index)			//选择的阵营是推荐阵营
		{
			saveGoodsInBag(pg_hero,"b_dj_120_132",1);
			it=campNumber.find(index);
			if (it!=campNumber.end())
			{
				int number=it->second;
				number++;
				campNumber.erase(it);
				campNumber.insert(map<int,int>::value_type(index,number));		
				saveCampNumber();
			}
		}
		pg_hero->updataSingleTarget(0,5);
	 }
	
}

void saveCampNumber(void)
{
	char identity[50]={0};
	strncpy(identity,"d5w1cswefd8584s2xc4s8mh5u_1",sizeof(identity));
	CampNumberData *campData;
	if (!campNumber.empty())
	{
		map<int,int>::iterator it;
		it=campNumber.begin();
		campData->number0=it->second;
		it++;
		campData->number1=it->second;
		it++;
		campData->number2=it->second;
	}
	bool isSuccess = mem_group->set_data(identity, (char*)campData, (int)sizeof(CampNumberData), 1);
    if(isSuccess == true)
    {
        cout<<"set campData into memcached server success"<<endl;
    } 
	else
    {
        cout<<"set campData into memcached server failure"<<endl;
    }
}

void initCampNumber(void)
{
	char identity[50]={0};
	strncpy(identity,"d5w1cswefd8584s2xc4s8mh5u_1",sizeof(identity));
	int size;
	int where;
	CampNumberData *newCampData = (CampNumberData*)mem_group->get_data(identity, &size, &where, 1);
    if (newCampData!=NULL)
	{
		campNumber.insert(map<int,int>::value_type(0,newCampData->number0));
		campNumber.insert(map<int,int>::value_type(1,newCampData->number1));
		campNumber.insert(map<int,int>::value_type(2,newCampData->number2));
		free(newCampData);
	}
	else
	{
		campNumber.insert(map<int,int>::value_type(0,0));
		campNumber.insert(map<int,int>::value_type(1,0));
		campNumber.insert(map<int,int>::value_type(2,0));
		cout<<"---------------------------------"<<endl;
		cout<<"jolly:Get CampData Error"<<endl;
		cout<<"---------------------------------"<<endl;
	}
}
