#include "dropgoods.h"
#include "money_operator.h"
#include"team.h"
#include"teamManager.h"

using namespace std;
extern map<string,DropList_Configuration*> id_to_dropgoods;
extern map<string,Monster_Inform*>	monTypeId_connect_property;
extern map<string,Hero*> heroId_to_pHero;
extern map<string,Pick*> goods_to_hero; 
extern map<string,Ointment *> id_to_ointment;
extern map<string,Equip_config*> id_to_equip; 
extern map<string,Map_Inform*> mapId_connect_map;
extern list<string> time_flag;
extern list<string> three_flag;
extern map<string, TaskGoodsInfo*> id2taskGoodsInfo;

int cc;  //记录掉落数量
void dropgoods(char* drop_goods_id,DropList_Configuration *droplist)		//掉落物品
{
	int percent=0;
	int drugnum;
	int toolnum;
	int loop;
	int wequipnum;
	int bequipnum; 
	int pequipnum;
	int pkequipnum;
	int oequipnum;
	int drugper=0;
	int drugperdetail=0;
	int toolper=0;
	int toolperdetail=0;
	int wequipper=0;
	int wequipperdetail=0;
	int bequipper=0;
	int bequipperdetail=0;
	int pequipper=0;
	int pequipperdetail=0;
	int pkequipper=0;
	int pkequipperdetail=0;
	int oequipper=0;
	int oequipperdetail=0;
	int randnum;
	int dropper;
	int loopupper;
	int num;
	int interval;
	map<int,string> dropgoodsid;
	map<int,string>::iterator id_it;
	percent=droplist->getpercent();		
	randnum=random_number(1,1000);			//随即1~1000的随机数
	
	if (randnum<=percent)			//随即出来的数满足掉率,则掉落物品
	{
		drugper=droplist->getdrugper();							//drug阶段掉落概率
		toolper=drugper+droplist->gettoolper();					//tool阶段掉落概率
		wequipper=toolper+droplist->getwequipper();				//wequip阶段掉落概率
		bequipper=wequipper+droplist->getbequipper();			//bequip阶段掉落概率
		pequipper=bequipper+droplist->getpequipper();			//pequip阶段掉落概率
		pkequipper=pequipper+droplist->getpkequipper();			//pkequip阶段掉落概率
		oequipper=pkequipper+droplist->getoequipper();			//oequip阶段掉落概率		
		drugnum=droplist->getdrugnum();							//drug阶段掉落的物品数量
		toolnum=droplist->gettoolnum();							//tool阶段掉落的物品数量
		wequipnum=droplist->getwequipnum();						//wequip阶段掉落的物品数量
		bequipnum=droplist->getbequipnum();						//bequip阶段掉落的物品数量
		pequipnum=droplist->getpequipnum();						//pequip阶段掉落的物品数量
		pkequipnum=droplist->getpkequipnum();					//pkequip阶段掉落的物品数量
		oequipnum=droplist->getoequipnum();						//oequip阶段掉落的物品数量
		dropgoodsid=droplist->getdropgoodsid();
		randnum=random_number(1,1000);			//再次随即数字,判断掉落的物品到底为什么道具
		if (randnum<=drugper)				
		{
			if (drugnum==0)					//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{					
				randnum=random_number(1,drugnum);				//随即数,从掉落的物品里随即出任意一个					
			}
		}
		else if (randnum<=toolper)
		{
			if (toolnum==0)				//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				strncpy(drop_goods_id,"0000",15);
			}
			else
			{	
				toolnum+=drugnum;
				randnum=random_number(drugnum,toolnum);		//随即数,从掉落的物品里随即出任意一个									
			}
		}
		else if (randnum<=wequipper)
		{
			if (wequipnum==0)			//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				toolnum+=drugnum;
				wequipnum+=toolnum;
				randnum=random_number(toolnum,wequipnum);		//随即数,从掉落的物品里随即出任意一个	
			}				
		}
		else if (randnum<=bequipper)
		{
			if (bequipnum==0)			//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				wequipnum=drugnum+toolnum+wequipnum;
				bequipnum+=wequipnum;
				randnum=random_number(wequipnum,bequipnum);		//随即数,从掉落的物品里随即出任意一个	
			}					
		}
		else if (randnum<=pequipper)
		{
			if (pequipnum==0)			//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{
				bequipnum=drugnum+toolnum+wequipnum+bequipnum;	
				pequipnum+=bequipnum;
				randnum=random_number(bequipnum,pequipnum);		//随即数,从掉落的物品里随即出任意一个	
			}				
		}			
		else if (randnum<=pkequipper)
		{
			if (pkequipnum==0)			//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{
				pequipnum=drugnum+toolnum+wequipnum+bequipnum+pequipnum;
				pkequipnum+=pequipnum;
				randnum=random_number(pequipnum,pkequipnum);		//随即数,从掉落的物品里随即出任意一个	
			}				
		}					
		else if (randnum<=oequipper)
		{	
			if (oequipnum==0)			//若为0,则退出掉落函数,显示为无任务道具掉落
			{
				sprintf(drop_goods_id,"%s","0000");
			}
			else
			{				
				pkequipnum=drugnum+toolnum+wequipnum+bequipnum+pequipnum+pkequipnum;
				oequipnum+=pkequipnum;
				randnum=random_number(pkequipnum,oequipnum);		//随即数,从掉落的物品里随即出任意一个	
			}
		}	
		randnum=randnum-1;
		id_it=dropgoodsid.find(randnum);
		if (id_it==dropgoodsid.end())
		{
			sprintf(drop_goods_id,"%s","0000");
		} 
		else
		{
			sprintf(drop_goods_id,"%s",(id_it->second).c_str());
		}		
	} 
	else			//随机数不满足掉落概率.则不掉落任何道具
	{
		sprintf(drop_goods_id,"%s","0000");
	}
}

void getexperience(Hero *hero,MonsterBase* monster)
{
	char* monsterid = monster->getTypeId();	
	int teamnum;
	int experience;
	int monsterlevel;
	int herolevel=hero->getLevel();
	int expTime=monster->getExpTme();	
	vector<string> allTeamPerson;
	
	if(strlen(hero->getTeamerId()) == 0)
	{
		teamnum = 1;
	}
	
	else
	{
			
		TeamManager* teamManger = TeamManager::getManagerInst();
			
		if(!teamManger)
		{
			cout<<"getexperience teamManger is NULL:"<<endl;
			return;
		}	
			
		Team *team = teamManger->getTeamHandle(hero->getTeamerId());
		
		if(!team)
		{
			cout<<"getexperience team is NULL:"<<endl;
			return;
		}
		
		team->getTeamMemberId(allTeamPerson);
		
		teamnum = allTeamPerson.size();
	}
	
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monsterid);
	if (monster_it==monTypeId_connect_property.end())
	{
		cout<<"According to monsterid can't find monster inform (dropGoods)"<<endl;
		return;
	} 
	else
	{
		Monster_Inform* monster=monster_it->second;
		monsterlevel=monster->getrank();
	}
	experience=gExp(teamnum,monsterlevel,herolevel);
	if (experience==0)
	{
		experience=1;
	}
	experience=experience*expTime;
	
	char msg[1024]={'\0'};
	
	if (teamnum==1)
	{		
		hero->setExpNow(experience*hero->memHero->expTimes);
		snprintf(msg,sizeof(msg),"%d,%d,%s,%d,%d,%d",9,GET_EXPERIENCE,monsterid,hero->getExpNow(),monsterlevel,hero->getPetBox()->getActivePetIndex());
		
		//任务更新     by bison
		char monsterId[51];
		sub_str(monsterId, monsterid, 2, 0);
		// if (hero->getTaskState() & TASK_NEED_KILL_MONSTER)
		{
			hero->updateHeroTaskStatus(KILL_TASK_NEED_TYPE, monsterId, monsterlevel);
			hero->updateHeroTaskStatus(KILL_LIMIT_TASK_NEED_TYPE, "-1", monsterlevel);
		}
		if (hero->getPetBox()->getActivePet()!=NULL)
		{
			hero->getPetBox()->getActivePet()->growExp(experience*hero->memHero->expTimes,hero->getLevel(),hero);
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",hero->getPetBox()->getActivePet()->getExpNow());
		}
		else 
		{
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
		}
		
		if (hero->getRide()!=NULL)
		{
			hero->getRide()->gainExp(hero,experience*hero->memHero->expTimes,1);
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d,%d",hero->getRide()->getExpNow(),hero->getRide()->getExpMax());
		}
		else 
		{
			snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
		}
		send_msg(hero->getFd(),msg);
	}
	else
	{		
		if (!allTeamPerson.empty())
		{
			vector<string>::iterator it;
			for (it=allTeamPerson.begin();it!=allTeamPerson.end();it++)
			{			
				memset(msg,'0',sizeof(msg));
				map<string,Hero*>::iterator hero_it;
				hero_it=heroId_to_pHero.find(*it);
				if (hero_it==heroId_to_pHero.end())
				{
					cout<<"this hero is not exist! dropgoods.cpp 439"<<endl;
					continue;
				}
				else
				{
					Hero *teamHero=hero_it->second;
					if (strcmp(hero->getMapId(),teamHero->getMapId())==0)
					{					
						teamHero->setExpNow(experience*teamHero->memHero->expTimes);
						snprintf(msg,sizeof(msg),"%d,%d,%s,%d,%d,%d",9,GET_EXPERIENCE,monsterid,teamHero->getExpNow(),monsterlevel,teamHero->getPetBox()->getActivePetIndex());
						
						//任务更新     by bison
						char monsterId[51];
						sub_str(monsterId, monsterid, 2, 0);
						// if (teamHero->getTaskState() & TASK_NEED_KILL_MONSTER)
						{
							teamHero->updateHeroTaskStatus(KILL_TASK_NEED_TYPE, monsterId, monsterlevel);
							teamHero->updateHeroTaskStatus(KILL_LIMIT_TASK_NEED_TYPE, "-1", monsterlevel);
						}
						if (teamHero->getPetBox()->getActivePet()!=NULL)
						{
							teamHero->getPetBox()->getActivePet()->growExp(experience*teamHero->memHero->expTimes,teamHero->getLevel(),teamHero);
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",teamHero->getPetBox()->getActivePet()->getExpNow());
						}
						else
						{
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
						}
						
						if (teamHero->getRide()!=NULL)
						{
							teamHero->getRide()->gainExp(teamHero,experience*teamHero->memHero->expTimes,1);
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d,%d",teamHero->getRide()->getExpNow(),teamHero->getRide()->getExpMax());
						}
						else
						{
							snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%d",0);
						}
						send_msg(teamHero->getFd(),msg);
					}
					else
					{
						cout<<"this hero is in another map dropgoods.cpp 454"<<endl;
						continue;
					}
				}
			}
		}		
	}	
	
	increaseBoundGameMoney(hero,getmoney(monsterid));
}

int getmoney(char* monster_typeid)	//杀死怪获得的金钱
{
	int gold;
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monster_typeid);
	if (monster_it==monTypeId_connect_property.end())
	{
		cout<<"!!!!!!!!!!!!!!no monster!!!!!!!!!!!!!gold"<<endl;
	} 
	else
	{
		Monster_Inform *monster;
		monster=monster_it->second;		
		gold=monster->gold;
		int moneyTime=monster->monyTme;
		gold=gold*moneyTime;
		return gold;
	}
}

vector<Point> drop_location(Point monsterPoint,int number,Map_Inform *dropmap)	//掉落位置判定
{	
	Point tempPoint=monsterPoint;
	vector<Point> dropPoint;
	dropPoint.clear();
	if (dropmap==NULL)
	{
		return dropPoint;
	}
	int usedNumber;
	int randNumber;
	cout<<"monsterPoint: x: "<<monsterPoint._x<<" y: "<<monsterPoint._y<<endl;
	// //srand(MY_TV_USEC);
	int locationRandomx;
	int locationRandomy;
	for (int i=0;i<number;i++)
	{		
		locationRandomx=random_number(0,128);			//随即出像素点x坐标	
		locationRandomy=random_number(0,64);			//随即出像素点x坐标	
		
		monsterPoint._x=monsterPoint._x+locationRandomx-64;
		monsterPoint._y=monsterPoint._y+locationRandomy-32;
		
		int digst=dropmap->getBaseDigst();
		Point temp=MapExchangeLogical(monsterPoint);
		Point logPoint;
		logPoint._x=temp._x;
		logPoint._y=temp._y+digst;
		
		//判断是否是障碍点.若是则重新随即
		if (!dropmap->judgeLogPtHind(logPoint))
		{
			cout<<"jolly:this point is hind point in dropgoods 382"<<endl;
			monsterPoint=tempPoint;
		}
		dropPoint.push_back(monsterPoint);
	}	
	cout<<"dropPoint: x:"<<monsterPoint._x<<" y: "<<monsterPoint._y<<endl;
	return dropPoint;
}

int monstertype(MonsterBase *hit)
{	
	char* kind=hit->getKind();
	cout<<"monster kind is "<<kind<<endl;
	int loop=1;
	if (strcmp(kind,"Boss")==0)
	{
		loop=8;
	}
	else
	{
		loop=1;
	}
	cout<<"monster loop is "<<loop<<endl;
	return loop;
}

void monsterDropGoods(char *heroId,MonsterBase *monster)			//打怪掉落
{	
	char* monster_typeid=monster->getTypeId();			//通过MonsterBase 找Monster_Inform,真哥不把stage存在通过MonsterBase下,找起来蛋疼
	map<string,Monster_Inform*>::iterator monster_it;
	monster_it=monTypeId_connect_property.find(monster_typeid);
	Monster_Inform *monster_inform = NULL;
	if (monster_it==monTypeId_connect_property.end())				//找不到找Monster_Inform,返回
	{
		cout<<"jolly:According to the monsterid can't find the monster inform dropGoods.cpp 647"<<endl;
		return;
	}
	else
	{		
		monster_inform=monster_it->second;
		char* stage=monster_inform->getstage();				//取怪物的掉落阶段
				int bound=0;					//绑定状态/*活动boss没有所有者*/
		if(strcmp(monster->getType(),"ActiveBossMon") == 0)
		{			
			bound=2;
		}
		saveInPick(heroId,monster->getMap(),monstertype(monster),stage,monster->getLocation(),bound,0);
	}
}
	
void saveInPick(char* heroId,Map_Inform *dropmap,int loop,char *stage,Point deadPoint,int bound,int accountFlag)
{			
	if (dropmap==NULL)
	{
		return;
	}
	
	char* uuid=cid();				//掉落实例id,一个怪一个
	char flag[40]={'\0'};
	strncpy(flag,uuid,sizeof(flag));
	free(uuid);
	int count=0;					//掉落数量
	
	char pt_flag[15]={'\0'};		//用于保存pick实例中的k-v对的key
	char goodsid[8][20];			//最多掉8件道具,每个道具的id长度不会超过20;目前写死
	int i;
	
	char temp[20]={0};
	
	Pick *pick = NULL;
	
	memset(g_out_buf,0,sizeof(g_out_buf));	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s",9,0,heroId,bound,flag);		

	map<string,DropList_Configuration*>::iterator it;	
	it=id_to_dropgoods.find(stage);	
	if (it==id_to_dropgoods.end())			//找不到掉落列表 返回
	{
		cout<<"have no stage! and stage is:: "<<stage<<endl;
		return;
	}
	else
	{
		DropList_Configuration *droplist=it->second;
		for (i=0;i<loop;i++)
		{				
			dropgoods(temp,droplist);
			if (strcmp(temp,"0000")!=0)					//当返回的不是0000,代表掉落了物品,所以统计++
			{
				// cout<<"goodsid["<<i<<"]:"<<goodsid[i]<<endl;
				strncpy(goodsid[count],temp,sizeof(goodsid[count]));
				count++;
			}
			if(i==7&&count<4)									//若i可以=7了,代表这个怪是boss,然而boss必须掉落4个,所以若是统计小于4了,则多循环一次
			{
				i--;
			}
		}
		if (count==0)				//没有掉落物品,返回
		{
			cout<<"count==0"<<endl;
			return;
		}
		else
		{
			vector<Point> pt=drop_location(deadPoint,count,dropmap);
			if (pt.size()==0)
			{
				cout<<"pt.size()==0"<<endl;
				return;
			}
			
			pick=new Pick(flag,heroId,count,dropmap,bound,deadPoint);
			for (i=0;i<count;i++)
			{		
				cout<<"11111111111111111111111111111111111111"<<endl;
				snprintf(pt_flag,sizeof(pt_flag),",%d,%d",pt[i]._x,pt[i]._y);					//合成ptflag
				snprintf(g_out_buf+strlen(g_out_buf), sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d,%s", pt[i]._x, pt[i]._y, goodsid[i]);
				pick->insertDropGoods(pt_flag,goodsid[i]);				//每个掉落物品都插入到pick中			
			}							
			cout<<"g_out_buf:"<<g_out_buf<<endl;
			dropmap->insertDropInst(pick);
			send_msg_dropGoods(g_out_buf,flag,dropmap);
		}			
	}
}

void dropTaskGoods(Hero *attack, MonsterBase *hit)
{
	if (attack==NULL)
	{
		return;
	}
	char* monsterid=hit->getTypeId();
	char monid[100] = {0};
	if (strncmp(monsterid,"MP",2)==0)
	{
		strncpy(monid,monsterid+2,strlen(monsterid)-2);
	}
	// cout<<"bison bison bison bison bison bison bison bison bison"<<endl;
	// cout<<"bison bison identity:"<<attack->getIdentity()<<endl;
	list<Task*> map_task=attack->getAccepted_Task_List();
	if (!map_task.empty())
	{
		// cout<<"bison 11111111111111111"<<endl;
		list<Task*>::iterator task_it;
		for (task_it=map_task.begin();task_it!=map_task.end();task_it++)
		{
			Task* task=(*task_it);
			char* task_goods=task->getTaskGoods();
			if (task_goods != NULL)
			{
				// cout<<"[BisonTest drop task goods] taskgoods is "<<task_goods<<endl;
				map<string, TaskGoodsInfo*>::iterator task_goods_it;
				task_goods_it=id2taskGoodsInfo.find(task_goods);
				if (task_goods_it!=id2taskGoodsInfo.end())
				{
					// cout<<"bison 222222222222222222222"<<endl;
					TaskGoodsInfo* task_goods_info=task_goods_it->second;
					//modified by bison
					if (task_goods_info->isMonsterDrop(monid) && task_goods_info->dropTaskGoodsOk())
					{
						// cout<<"bison 3333333333333333333333333"<<endl;
						Bag* bag=attack->getBag();
						//Modified by bison
						if (saveGoodsInBag(attack,task_goods,1))
						{
							// cout<<"bison 4444444444444444444444444444444"<<endl;
							attack->updateHeroTaskStatus(COLLECT_TASK_NEED_TYPE, task_goods);
						}
					}
				}
			}
		}
	}	
}


//打碎瓶罐掉落
void dropTaskGoods(Hero *attack, Bottle *hit)
{
	if (attack==NULL)
	{
		return;
	}
	char* bottleid=hit->getTypeId();
	char botid[100] = {0};
	
	// cout<<"bison bison bison bison bison bison bison bison bison"<<endl;
	// cout<<"bison bison identity:"<<attack->getIdentity()<<endl;
	list<Task*> map_task=attack->getAccepted_Task_List();
	if (!map_task.empty())
	{
		// cout<<"bison 11111111111111111"<<endl;
		list<Task*>::iterator task_it;
		for (task_it=map_task.begin();task_it!=map_task.end();task_it++)
		{
			Task* task=(*task_it);
			char* task_goods=task->getTaskGoods();
			if (task_goods != NULL)
			{
				// cout<<"[BisonTest drop task goods] taskgoods is "<<task_goods<<endl;
				map<string, TaskGoodsInfo*>::iterator task_goods_it;
				task_goods_it=id2taskGoodsInfo.find(task_goods);
				if (task_goods_it!=id2taskGoodsInfo.end())
				{
					// cout<<"bison 222222222222222222222"<<endl;
					TaskGoodsInfo* task_goods_info=task_goods_it->second;
					//modified by bison
					if (task_goods_info->isMonsterDrop(bottleid) && task_goods_info->dropTaskGoodsOk())
					{
						// cout<<"bison 3333333333333333333333333"<<endl;
						Bag* bag=attack->getBag();
						//Modified by bison
						if (saveGoodsInBag(attack,task_goods,1))
						{
							// cout<<"bison 4444444444444444444444444444444"<<endl;
							attack->updateHeroTaskStatus(COLLECT_TASK_NEED_TYPE, task_goods);
						}
					}
				}
			}
		}
	}	
}

void send_msg_dropGoods(char* msg,char *flag,Map_Inform *map_now)
{	
	if(map_now == NULL||msg==NULL||flag==NULL)
	{
		cout<<"send_msg_dropGoods error   dropGoods.cpp"<<endl;
		return;
	}
	
	Nbox *box;		////////////////////////////////////////掉落插入九宫格///////////////////////
	box=map_now->getBox();  
	if(box == NULL)
	{
		cout<<"box null  dropGoods.cpp"<<endl;
		return;
	}
	
	StyObj obj(flag,PICK_STYLE_TYPE);	
	map_now->insertID(obj);		
	box->getStaInSrcVec(obj);
	cout<<"here in send_msg_dropgoods"<<endl;
	cout<<"msg:"<<msg<<endl;
	box->sentBoxMsg(msg);	
	cout<<"end in send_msg_dropgoods"<<endl;
}



