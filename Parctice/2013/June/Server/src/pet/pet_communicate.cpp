#include "pet_communicate.h"
#include "my_time.h"
#include "dictionary_asist.h"
#include "money_operator.h"
extern map<string,PetSkill_Config*> id_to_petSkill;
extern map<string, Hero*> heroId_to_pHero;
extern struct timeval myTime;
extern map<string,Pet*> id_to_activePet;
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern Pet_Xidian pet_xidian;
extern map<string,Goods_Config*> id_to_dj;

using namespace std;

void petEvolution(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(int flag);
	MSG_CHAR(char* identity);
	MSG_INT(int index);
	MSG_CHAR(char *goodsid);
	MSG_INT(int bagIndex);
	
	cout<<"10,3,"<<flag<<","<<identity<<","<<index<<","<<goodsid<<","<<bagIndex<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index的有效性
	{
		return;
	}
	if (pet_box->verification(index,identity)==false)
	{
		return;
	}
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	if (flag!=3)
	{
		if (!bag->test(bagIndex,goodsid))
		{
			cout<<"bagIndex and goodsid is not suit"<<endl;
			return;
		}
	}	
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	Pet *pet=pet_box->getPet(index);
	if (pet==NULL)
	{
		cout<<"According to the index can't find pet in pet_communicate 33"<<endl;
	}
	else
	{
		if (flag==1)	//刷新资质
		{
			if (pet->getQuality()==5)
			{
				msg_error(g_out_buf,65);
				send_msg(pg_hero->getFd(),g_out_buf);			
			}
			else
			{			
				if (pet->canEvolutionRefresh())
				{
					if (useBoundGameMoney(pg_hero,20000))		//使用金币 
					{
						if (useBagGoods(pg_hero,goodsid,bagIndex,1)==0)
						{							
							if (pet->evolution(pg_hero,index))
							{
								pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
								send_msg(pg_hero->getFd(),g_out_buf);	
								memset(g_out_buf,0,sizeof(g_out_buf));
								
								snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s,%s",10,23,pet->getIdentity(),pet->getQuality(),pet->getPhotoId(),pet->getNickName());
								pet->sendMsgBox(g_out_buf);
								
								pg_hero->updataSingleTarget(2,3);
								if (pet->getQuality()==4)
								{
									pg_hero->updataSingleTarget(5,4);
								}
								
								char info[1024]={'\0'};
								snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s",7,SYSTEM_WARN,"xf005",2,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,2,pet->getNickName(),pet->getId(),pet->getIdentity(),pg_hero->getIdentity());
								map<string, Hero*>::iterator it_hero;

								for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
								{
									if (it_hero->second!=NULL)
									{						
										send_msg(it_hero->second->getFd(),info);
									}
								}							
							}	
							pg_hero->updataSingleTarget(2,3);									
						}
						else 
						{
							increaseBoundGameMoney(pg_hero,20000);
						}
					}
					else
					{
						msg_error(g_out_buf,1);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
				}		
				else
				{
					msg_error(g_out_buf,65);
					send_msg(pg_hero->getFd(),g_out_buf);
				}
			}
		}	
		else if (flag==3)
		{
			pet->msg_evolution(g_out_buf,sizeof(g_out_buf),index);
			send_msg(pg_hero->getFd(),g_out_buf);
		}	
	}
}

void petSuccinct(char* buffer)
{	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(int flag);
	MSG_CHAR(char *identity)
	MSG_INT(int index);
	
	cout<<"10,4,"<<flag<<","<<identity<<","<<index<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	if (!pet_box->verification(index,identity))
	{
		return;
	}
	
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index的有效性
	{
		return;
	}	

	Pet *pet=pet_box->getPet(index);
	if(pet == NULL)//tory add 2012,12,28
	{
		return;
	}
	if (flag==1)			//使用洗练
	{
		if (useBoundGameMoney(pg_hero,pet_xidian.cost))			//判断是否成功的使用了金币
		{
			pet->succinct(index);
			memset(g_out_buf,0,sizeof(g_out_buf));
			pet->send_msg_succinctInfo(g_out_buf,sizeof(g_out_buf),index);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
		else
		{
			cout<<"have no money!!! pet_communicate.cpp 98"<<endl;
		}
	}
	else if (flag==2)		//普通保存
	{
		pet->saveSuccinctInGameMoney(pg_hero,index);
		memset(g_out_buf,0,sizeof(g_out_buf));
		pet->send_msg_succinctInfo(g_out_buf,sizeof(g_out_buf),index);
		send_msg(pg_hero->getFd(),g_out_buf);
		pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==3)			//使用元宝保存
	{	
		int number;
		
		MSG_INT(number);
		// cout<<number<<endl;
		if (number<0||number>3)
		{
			return;
		}
		if (pet->canGoldSaveSuccinct(number))
		{
			if (useBoundGold(pg_hero,2))			//判断是否成功使用元宝
			{
				pet->saveSuccinctInGold(number,pg_hero,index);
				memset(g_out_buf,0,sizeof(g_out_buf));
				pet->send_msg_succinctInfo(g_out_buf,sizeof(g_out_buf),index);
				send_msg(pg_hero->getFd(),g_out_buf);
				pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			else
			{
				cout<<"use money error in pet_communicate 133"<<endl;
			}	
		}
		else
		{
			msg_error(g_out_buf,94);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}	
	else if (flag==4)		//初次点击宠物洗练面板请求数据
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		pet->send_msg_succinctInfo(g_out_buf,sizeof(g_out_buf),index);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		cout<<"jolly:flag is error  the flag is ;"<<flag<<endl;
	}
}

void petStatus(char* buffer)
{

	int index;
	
	int flag;		//标志
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag);
	MSG_INT(index);
	MSG_CHAR(char *identity);
	
	cout<<"10,0,"<<flag<<","<<index<<","<<identity<<endl;	
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index的有效性
	{
		return;
	}	

	memset(g_out_buf,0,sizeof(g_out_buf));
	if (pet_box->verification(index,identity))
	{
		Pet *pet=pet_box->getPet(index);		
		if (pet==NULL)
		{
			cout<<"According to the index can't find pet in pet_communicate 189"<<endl;
		}
		else
		{
			if (flag==1)			//宠物出战
			{
				int activeIndex=pet_box->getActivePetIndex();
				// cout<<"activeIndex is "<<activeIndex<<endl;
				if (index==activeIndex)
				{
					cout<<"jollyTest:This pet is already active"<<endl;
				}
				else
				{
					if (activeIndex!=-1)
					{
						Pet *activePet=pet_box->getActivePet();
						if (activePet==NULL)
						{
							cout<<"jolly:------------------------error 217 pet_communicate"<<endl;
						}
						else
						{					
							// cout<<"------------223---------------"<<endl;
							activePet->setActive(pg_hero,0);						
							// pet->send_msg_downLine(pg_hero);
						}
					}
					pet_box->setActivePetIndex(index);
					pet->setActive(pg_hero,1);
					pet->send_msg_active(pg_hero);
					pet->send_msg_chuzhan(g_out_buf,sizeof(g_out_buf),index);
					send_msg(pg_hero->getFd(),g_out_buf);
				} 
			}
			else if (flag==2)		//宠物召回
			{
				pet_box->setActivePetIndex(-1);
				pg_hero->memSet();
				pet->setActive(pg_hero,0);									
				// pet->send_msg_downLine(pg_hero);
				pet->send_msg_zhaohui(g_out_buf,sizeof(g_out_buf),index);
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			else if (flag==3)		//宠物放生
			{
				if (index==pet_box->getActivePetIndex())
				{
					pet->setActive(pg_hero,0);					
					pet->send_msg_downLine(pg_hero);
					pet_box->setActivePetIndex(-1);
					if (pet_box->deletePet(index))
					{
						//delete pet;			
					}
					else
					{
						cout<<"jolly:delete pet error in pet_communicate 249"<<endl;
					}
				}
				else
				{
					if (pet_box->deletePet(index))
					{
						//delete pet;			
					}
					else
					{
						cout<<"jolly:delete pet error in pet_communicate 249"<<endl;
					}
				}
				pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
				pg_hero->memSet();
			}
		}
	}
	else
	{
		msg_error(g_out_buf,115);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void petSkillHandle(char *buffer)
{
	
	int index;
	
	char *identity;		//宠物实例id
	
	int skill_index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);				//宠物索引
	MSG_CHAR(identity);			//宠物实例id
	MSG_INT(skill_index);		//学习的技能索引
	
	cout<<"10,8,"<<index<<","<<identity<<","<<skill_index<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		cout<<"pet_box is null is pet_communicate.cpp 255"<<endl;
		return;
	}
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index的有效性
	{
		cout<<"pet index is error in pet_communicate 361"<<endl;
		return;
	}	
	if (skill_index<0||skill_index>3)			//判断skill_index的有效性
	{
		cout<<"skill index is error in pet_communicate 366"<<endl;
		return;
	}
	
	if (pet_box->verification(index,identity))		//验证宠物索引和宠物是否相同
	{
		Pet *pet=pet_box->getPet(index);			//根据索引取得宠物实例
		if (pet==NULL)				//根据宠物索引取不到宠物
		{
			cout<<"According to the index can't find the pet"<<endl;
		}
		else			
		{	
			int flag=pet->judgeSkillLearn(skill_index);
			cout<<"flag:"<<flag<<endl;
			if (flag==1)			//标志为1 学习技能
			{
				Bag *bag=pg_hero->getBag();
				if (bag==NULL)
				{
					cout<<"hero bag is null in pet_communicate 385"<<endl;
					return;
				}

				char goodsid1[20]={0};
				char goodsid2[20]={0};
				strncpy(goodsid1,"b_cl_139_100",sizeof(goodsid1));
				strncpy(goodsid2,"f_cl_139_100",sizeof(goodsid2));
				int number1=bag->getGoodsNum(goodsid1);
				int needNumber=pet->getSkillNeedNumber(skill_index);
				cout<<"1111111111111111111111111111"<<endl;
				if (number1>=needNumber)
				{
					cout<<"22222222222222222222222222222"<<endl;
					if (useBagGoods(pg_hero,goodsid1,needNumber)==0)
					{
						cout<<"33333333333333333333333333333"<<endl;
						pet->learnSkill(skill_index);
						pet->msg_learnSkill_success(g_out_buf,skill_index,index,sizeof(g_out_buf),pg_hero->memHero->petSkillNumber);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
					else 
					{
						cout<<"4444444444444444444444444444"<<endl;
						msg_error(g_out_buf,135);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
				}
				else
				{
					cout<<"5555555555555555555555555555555555555"<<endl;
					int number2=bag->getGoodsNum(goodsid2);
					if (number1+number2>=needNumber)
					{
						cout<<"666666666666666666666666666666666"<<endl;
						if (number1==0)
						{	
							if (useBagGoods(pg_hero,goodsid2,needNumber)==0)
							{
								pet->learnSkill(skill_index);
							pet->msg_learnSkill_success(g_out_buf,skill_index,index,sizeof(g_out_buf),pg_hero->memHero->petSkillNumber);
							send_msg(pg_hero->getFd(),g_out_buf);
							}
						}
						else if (useBagGoods(pg_hero,goodsid1,number1)==0&&useBagGoods(pg_hero,goodsid2,needNumber-number1)==0)
						{
							cout<<"77777777777777777777777777777777"<<endl;
							pet->learnSkill(skill_index);
							pet->msg_learnSkill_success(g_out_buf,skill_index,index,sizeof(g_out_buf),pg_hero->memHero->petSkillNumber);
							send_msg(pg_hero->getFd(),g_out_buf);
						}
					}
					else
					{							
						msg_error(g_out_buf,135);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
				}				
			}
			else if (flag==2)			//标志位2,升级技能
			{
			
				cout<<"888888888888888888888888888"<<endl;
				if (pet->getSkillFlag(skill_index)==0)//通过技能索引,找到技能实例
				{
					msg_error(g_out_buf,9);							
					send_msg(pg_hero->getFd(),g_out_buf);
				}
				else
				{
					cout<<"9999999999999999999999"<<endl;
					if (pet->getLevel()<pet->getSkillLimit(skill_index))
					{
						msg_error(g_out_buf,0);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
					else if (pet->getSkillLevel(skill_index)==pet->getMaxLimit(skill_index))
					{
						msg_error(g_out_buf,23);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
					else if (pet->getSkillNeedCount(skill_index)>pg_hero->memHero->petSkillNumber)
					{
						msg_error(g_out_buf,136);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
					else
					{		
						cout<<"000000000000000000000000000000"<<endl;
						pg_hero->memHero->petSkillNumber-=pet->getSkillNeedCount(skill_index);
						pet->skillLevelUp(pg_hero,skill_index);				//调用宠物技能升级函数
						// pet->msg_skill_levelUp(g_out_buf,skill_index,sizeof(g_out_buf));
						// send_msg(pg_hero->getFd(),g_out_buf);	
						pet->msg_learnSkill_success(g_out_buf,skill_index,index,sizeof(g_out_buf),pg_hero->memHero->petSkillNumber);
						send_msg(pg_hero->getFd(),g_out_buf);
						
						if (pet->isFourSkillMax())
						{
							pg_hero->updataSingleTarget(7,1);
						}
					}
				}
			}
		}
	}
	else
	{
		cout<<"pet verify is error in pet_communicate 460"<<endl;
	}
}
void petModifyName(char *buffer)
{
	
	int index;
	
	char *identity;			//宠物实例id
	
	char *name;			//宠物修改的名字
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	MSG_CHAR(identity);
	MSG_CHAR(name);
	MSG_INT(int indexBag)
	MSG_CHAR(char *goodsid)
	
	cout<<"10,6,"<<index<<","<<identity<<","<<name<<","<<indexBag<<","<<goodsid<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index的有效性
	{
		return;
	}	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	if (bag->test(indexBag,goodsid))	
	{
		Pet *pet=pet_box->getPet(index);// 通过宠物的索引找到宠物的实例	
		if (pet==NULL)
		{
			cout<<"According to the index can't find the pet pet_communicate.cpp 472"<<endl;
		}
		else
		{
			if (strlen(name) < 1 || strlen(name) > 18)
			{
				msg_error(g_out_buf,47);//名字长度
			}
			else
			{
				//名字中含非法字符
				if (isHaveIllSymbol(name) == 1)
				{
					msg_error(g_out_buf,46);
				}
				else
				{
					if (isHaveDirtyWords(name) == 1)
					{
						//名字中含有敏感
						msg_error(g_out_buf,48);
					}
					else
					{
						if (strcmp(goodsid,"f_cl_127_100")==0||strcmp(goodsid,"b_cl_127_100")==0)
						{
							if (useBagGoods(pg_hero,goodsid,indexBag,1)==0)
							{									
								pet->setNickName(name);		//修改宠物的名字
								// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s",10,PET_NAME,pet->getIdentity(),index,name);								
								snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s,%s",10,23,pet->getIdentity(),pet->getQuality(),pet->getPhotoId(),pet->getNickName());
								pet->sendMsgBox(g_out_buf);
								return;
							}
						}	
						else
						{
							return;
						}
					}				
				}				
			}
			send_msg(pg_hero->getFd(),g_out_buf);			
		}
	}
	
}

void petRequst(char *buffer)
{
	int flag;				//标志
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag);
	
	cout<<"10,5,"<<flag<<endl;;
		
	Pet_Box *pet_box=pg_hero->getPetBox();	
	if (pet_box==NULL)
	{cout<<"-------------605----------------"<<endl;
		return;
	}
	if (flag==1)		//标志为1 发送宠物栏信息
	{
		pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==2)		//标志为2 发送选择的宠物的详细信息
	{
		
		int index;
		
		MSG_INT(index);
		
		cout<<","<<index<<endl;
		
		int pet_number=pet_box->getNumber();			//取得当前的宠物数量
		if (index>pet_number)
		{
			cout<<"According to the index can't find pet pet_communicate.cpp 531"<<endl;
		}
		else
		{		
			Pet *pet=pet_box->getPet(index);		//通过宠物索引找到宠物实例
			if (pet==NULL)
			{
				cout<<"jolly:this index has no pet"<<endl;
			}
			else
			{				
				pet->msg_return_pet(g_out_buf,index,sizeof(g_out_buf),pg_hero->memHero->petSkillNumber,0);			//调用宠物下的详细信息的函数进行发送
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}	
	}
	else if (flag==3)
	{		
		cout<<"-------------643----------------"<<endl;
		/*jolly  宠物还原 10.13*/
		int pet_index=pet_box->getActivePetIndex();
		if (pet_index==-1)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",10,8,0);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
		}
		Pet *pet=pet_box->getPet(pet_index);
		if (pet!=NULL)
		{
			pet->setActive(pg_hero,1);
			pet->send_msg_active(pg_hero);
			pet_box->setActivePetIndex(pet_index);

		}
		else
		{
			pet_box->setActivePetIndex(-1);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",10,8,0);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"jolly:no active pet online pet_communicate 631 "<<endl;
		}
	}
}

//宠物战斗解析 10,9
void petFight(char *buffer)
{		
	char *identity;		//被攻击者实例id
	Point piexPt;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(identity);
	MSG_INT(piexPt._x);
	MSG_INT(piexPt._y);
	MSG_INT(int flag)
	
	cout<<"pet Fight:"<<endl;
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}

	Pet *pet=pet_box->getActivePet();			//找到该hero的出战宠物实例
	if (pet==NULL)
	{
		cout<<"This pg_hero has no active pet pet_communicate.cpp 629"<<endl;
	}
	else
	{
		cout<<"PetpiexPt._x:"<<piexPt._x<<endl;
		cout<<"PetpiexPt._y:"<<piexPt._y<<endl;
		
		Map_Inform *mapNow=pg_hero->getMap();					//取得玩家所在的地图实例
		if (mapNow==NULL)
		{
			return;
		}
		pet->setMapInform(mapNow);
		pet->setNowPix(piexPt);
		pet->setMasterId(pg_hero->getIdentity());
		int fightTime=pet->getFightTime();
		int nowTime=myTime.tv_sec;
		if ((nowTime-fightTime)>=1)
		{
			if (pet->isInRank(piexPt))
			{
				if (flag==0)					//如果被攻击的是怪物
				{
					 MonsterBase *monster = mapNow->getMonsterObj(identity);			//通过怪物实例id,查找在该地图上的怪物实例
					 if (monster==NULL)
					 {
						cout<<"jolly:Accoding to the monsterid can't find monsterBase pet_communicate 639"<<endl;
					 }
					 else
					 {
						cout<<"attack monster ing"<<endl;
						if (monster->getLifeVal()<=0)
						{
							pg_hero->send_msg_attackFailed();						
						}
						else
						{
							pet->pet_attack_monster(monster);
						}
					 }		
				}
				else if (flag==1)			//如果被攻击的是人物
				{
					map<string, Hero*>::iterator it;
					it=heroId_to_pHero.find(identity);
					if (it==heroId_to_pHero.end())
					{
						cout<<"jolly:Accoding to the identity can't find pg_hero pet_communicate 655"<<endl;
					}
					else
					{
						Hero *tarHero=it->second;
						if (tarHero->getLifeVal()<=0)
						{
							pg_hero->send_msg_attackFailed();
						}
						else
						{
							pet->pet_attack_hero(tarHero);
						}							
					}
				}
				else if (flag==2)			//如果被攻击的是打击物
				{														
					Bottle *bottInst = mapNow->getBotInst(identity);
					
					if(bottInst == NULL)
					{
						cout<<"the bottInst is NULL:"<<identity<<endl;
					}
					else
					{
						pet->pet_attack_bottle(bottInst);
					}							
				}
			}
			else
			{										
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,ENTER_QUIT_FIGHT,FAILED);
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			pet->setFightTime(nowTime);
		}
		else
		{
			cout<<"jolly:pet attack frequency is too quick"<<endl;
		}
	}	
}

void petSkillReturn(char *buffer)
{	
	int index;	
		
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	
	cout<<"10,10,"<<index<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	int nowNum=pet_box->getNumber();
	if (index<0||index>nowNum)			//判断index1的有效性
	{
		return;
	}	
	
	Pet *pet=pet_box->getPet(index);
	if (pet!=NULL)
	{		
		pet->msg_skill_inform(g_out_buf,index,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void petBoxNum(char *buffer)
{
	pg_hero->getPetBox()->msg_maxNumber(g_out_buf,sizeof(g_out_buf));
	send_msg(pg_hero->getFd(),g_out_buf);
}

void petJingjie(char *buffer)			//宠物进阶
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)			//为1道具进阶 为2吃宠物  为3是进阶宠物 为4是信息请求 为5为吃多个
	MSG_CHAR(char *identity)
	MSG_INT(int petIndex);
	MSG_INT(int index)
	MSG_CHAR_END(char *goodsid)
	
	cout<<"10,12,"<<flag<<","<<identity<<","<<petIndex<<","<<index<<","<<goodsid<<endl;
	
	Pet_Box *pet_box=pg_hero->getPetBox();
	if (pet_box==NULL)
	{
		cout<<"pet_box is null in pet_communicate 819"<<endl;
		return;
	}
	if (!pet_box->verification(petIndex,identity))
	{
		cout<<"pet_box verification error in pet_communicate.cpp 823"<<endl;
		return;
	}
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		cout<<"bag is null in pet_communicate.cpp 828"<<endl;
		return;
	}
	Pet *pet=pet_box->getPet(petIndex);
	if (pet==NULL)
	{
		cout<<"pet is null in pet_communicate 836"<<endl;
		return;
	}
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (!pet->judgeJingJie()&&(flag==1||flag==2||flag==5))
	{
		msg_error(g_out_buf,25);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (flag==1)
	{
		if (strcmp(goodsid,"f_cl_103_100")==0||strcmp(goodsid,"b_cl_103_100")==0)
		{				
			if (bag->test(index,goodsid))
			{
				if (useBagGoods(pg_hero,goodsid,index,1)==0)
				{
					pet->increaseJingJie(pet->getJingjieEffect());
					pet->send_msg_jingJieNum(g_out_buf,sizeof(g_out_buf),petIndex);
					send_msg(pg_hero->getFd(),g_out_buf);
					
					pg_hero->updataSingleTarget(2,2);
				}
			}
		}
		else
		{
			cout<<"goodsid is not suit"<<endl;
		}
	}
	else if (flag==2)
	{
		if (petIndex==index)
		{
			return;
		}
		
		if (!pet_box->verification(index,goodsid))
		{
			return;
		}
		Pet *_pet=pet_box->getPet(index);
		if (_pet==NULL)
		{
			return;
		}
		int number=_pet->getEvolutionNumber();
		pet->increaseJingJie(number);
		pet->send_msg_jingJiePet(g_out_buf,sizeof(g_out_buf),petIndex);
		send_msg(pg_hero->getFd(),g_out_buf);
		
		cout<<"index:"<<index<<endl;
		cout<<"pet_box->getActivePetIndex():"<<pet_box->getActivePetIndex()<<endl;
		if (index==pet_box->getActivePetIndex())
		{
			_pet->setActive(pg_hero,0);					
			// _pet->send_msg_downLine(pg_hero);
			pet_box->setActivePetIndex(-1);
			cout<<"pet_box->getActivePetIndex():"<<pet_box->getActivePetIndex()<<endl;
			if (pet_box->deletePet(index))
			{
				//delete _pet;			
			}
			else
			{
				cout<<"jolly:delete pet error in pet_communicate 249"<<endl;
			}
		}
		else
		{
			if (pet_box->deletePet(index))
			{
				//delete _pet;			
			}
			else
			{
				cout<<"jolly:delete pet error in pet_communicate 249"<<endl;
			}
		}
		pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
		pg_hero->updataSingleTarget(2,2);
	}
	else if (flag==3)
	{
		if (pet->petJingJie())
		{
			if (petIndex==pet_box->getActivePetIndex())
			{				
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%s,%s",10,23,pet->getIdentity(),pet->getQuality(),pet->getPhotoId(),pet->getNickName());			
				pet->sendMsgBox(g_out_buf);
				pg_hero->send_msg_att();
			}	
			pet->send_msg_jingJieNum(g_out_buf,sizeof(g_out_buf),petIndex);
			send_msg(pg_hero->getFd(),g_out_buf);		
			pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);
			
			char info[1024]={'\0'};
			snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s",7,SYSTEM_WARN,"xf006",2,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,2,pet->getNickName(),pet->getId(),pet->getIdentity(),pg_hero->getIdentity());
			map<string, Hero*>::iterator it_hero;

			for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
			{
				if (it_hero->second!=NULL)
				{						
					send_msg(it_hero->second->getFd(),info);
				}
			}
			
			//武林目标更新
			pg_hero->updataSingleTarget(3,7);
		}
		else
		{
			msg_error(g_out_buf,137);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}
	else if (flag==4)
	{
		pet->send_msg_jingJie(g_out_buf,sizeof(g_out_buf),petIndex);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==5)
	{
		Bag *bag=pg_hero->getBag();
		if (bag==NULL)
		{
			return;
		}
		int number=pet->judgeUseNumber(index);
		if (number==0)
		{
			return;
		}
		
		cout<<"number:"<<number<<endl;
		int maxNum1=bag->getGoodsNum("b_cl_103_100");
		int maxNum2=bag->getGoodsNum("f_cl_103_100");
		if ((maxNum1+maxNum2)<number)
		{
			msg_error(g_out_buf,134);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"Have no such much goods and goodsid is "<<goodsid<<endl;
			return;
		}
		
		if (maxNum1==0)
		{
			if (useBagGoods(pg_hero,"f_cl_103_100",number)==0)
			{
				pet->increaseJingJie(pet->getJingjieEffect()*number);
				pet->send_msg_jingJieNum(g_out_buf,sizeof(g_out_buf),petIndex);
				send_msg(pg_hero->getFd(),g_out_buf);
			}			
		}
		else
		{
			int remainNumber=useBagGoods(pg_hero,"b_cl_103_100",number);
			if (remainNumber!=0)
			{
				useBagGoods(pg_hero,"f_cl_103_100",remainNumber);
			}	
			pet->increaseJingJie(pet->getJingjieEffect()*number);
			pet->send_msg_jingJieNum(g_out_buf,sizeof(g_out_buf),petIndex);
			send_msg(pg_hero->getFd(),g_out_buf);
		}	
		pg_hero->updataSingleTarget(2,2);		
	}
	else if (flag==6)
	{
		if (!pet_box->verification(index,goodsid))
		{
			cout<<"the index and the petidentity is not suit pet_communicate.cpp 1021"<<endl;
			return;
		}
		
		Pet *_pet=pet_box->getPet(index);
		if (_pet==NULL)
		{
			cout<<"_pet is null in pet_communicate.cpp 1027"<<endl;
			return;
		}
		
		_pet->send_msg_fuchong(g_out_buf,sizeof(g_out_buf),index);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		cout<<"msg is error in pet_communicate 1831"<<endl;
	}
}
