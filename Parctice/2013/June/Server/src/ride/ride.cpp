#include "ride.h"
extern char g_out_buf[20480];
extern map<string,Ride_Config*> id_to_ride;
extern RideSkill_Config rideSkill_config[10];
extern Ride_Special_Skill_Config rideSpecialSkill_config[3];
Ride::Ride(void)
{
	strncpy(ridedata.identity,"0",sizeof(ridedata.identity));
	
	ridedata.level=0;
	
	ridedata.expNow=0;
	
	ridedata.evolutionNow=0;
	
	ridedata.quality=0;
	
	ridedata.expMax=0;
	ridedata.hp=0;
	ridedata.mp=0;
	ridedata.outAttVal=0;
	ridedata.inAttVal=0;
	ridedata.outDefVal=0;
	ridedata.inDefVal=0;
	ridedata.hit=0;
	ridedata.crit=0;
	ridedata.dodge=0;
	ridedata.tenacity=0;
	ridedata.move=0;
	ridedata.evolutionMax=0;
	ridedata.exptimes=0;
	ridedata.cost=10;
	ridedata.finalSkill.stage=-1;
	
	for (int i=0;i<4;i++)
	{
		ridedata.equip[i].flag=0;
	}
	
	for (int i=0;i<10;i++)
	{
		ridedata.skill[i].flag==0;
		strncpy(ridedata.skill[i].id,"0",sizeof(ridedata.skill[i].id));
	}
	
	ridedata.finalSkill.stage=-1;
	for (int i=0;i<3;i++)
	{
		ridedata.finalSkill.flag[i]=-1;
		ridedata.finalSkill.value[i]=-1;
		ridedata.finalSkill.color[i]=-1;
	}
}

Ride::Ride(RideData rideData)
{
	ridedata=rideData;
}

void Ride::createRide(Ride_Config *ride_config,char *id)				//使用坐骑
{
	char identity[40]={0};
	char* uuid = cid();
	strncpy(ridedata.identity,uuid,sizeof(ridedata.identity));
	free(uuid);
	
	strncpy(ridedata.id,id,sizeof(ridedata.id));
	
	ridedata.level=1;
	
	ridedata.finalSkill.stage=-1;
	
	equalAtt(ride_config);
}

RideData Ride::getMemStruct(void)				//取出结构体
{
	return ridedata;
}

int Ride::getExpNow(void)
{
	return ridedata.expNow;
}

int Ride::getExpMax(void)
{
	return ridedata.expMax;
}

char* Ride::getEquipmentIdentity(int index)
{
	return ridedata.equip[index].goodsid;
}

int Ride::getCost(void)
{
	return ridedata.cost;
}

char* Ride::getPhotoId(void)
{
	return ridedata.photoId;
}

int Ride::getMove(void)
{
	return ridedata.move;
}

int Ride::getFinalGrid(void)
{
	return ridedata.finalSkill.gridNumber;
}

int Ride::getFinalSkillStage(void)
{
	return ridedata.finalSkill.stage;
}
	
int Ride::getQuality(void)
{
	return ridedata.quality;
}

char* Ride::getIdentity(void)
{
	return ridedata.identity;
}

char* Ride::getNickName(void)
{
	return ridedata.nickName;
}


int Ride::getLevel(void)
{
	return ridedata.level;
}

int Ride::getRefreshMoney(int number)						//返回刷新最终技能消耗的钱
{
	if (number==0)
	{
		return rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[0];
	}
	else if (number==1)
	{
		return rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[1];
	}
	else if (number==2)
	{
		return rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[2];
	}	
}

void Ride::gainExp(Hero *hero,int exp,int flag)						//获得经验,只有出战坐骑才能获得经验
{
	if (exp<0)
	{
		cout<<"jolly:ridedata gain exp<0"<<endl;
		return;
	}
	
	if (hero==NULL)
	{
		return;
	}
	
	if (ridedata.level>=hero->getLevel())
	{
		return;
	}
	
	if (flag==1)
	{			
		exp=exp*ridedata.exptimes;
	}
	ridedata.expNow+=exp;
	if (ridedata.expNow>=ridedata.expMax)
	{
		char identity[50]={0};
		snprintf(identity,sizeof(identity),"%s%d%d",ridedata.id,ridedata.quality,ridedata.level);
		map<string,Ride_Config*>::iterator it;
		it=id_to_ride.find(identity);
		if (it==id_to_ride.end())
		{
			ridedata.expNow=ridedata.expMax;
			return;
		}
		else
		{
			decreaseAtt(hero);
			minusAtt(it->second);
		}			
		
		ridedata.level++;
		
		snprintf(identity,sizeof(identity),"%s%d%d",ridedata.id,ridedata.quality,ridedata.level);
		it=id_to_ride.find(identity);
		if (it==id_to_ride.end())
		{
			ridedata.expNow=ridedata.expMax;
			return;
		}
		else
		{
			ridedata.expNow-=ridedata.expMax;
			equalAtt(it->second);
			increaseAtt(hero);
			
			memset(g_out_buf,0,sizeof(g_out_buf));
			ride_msg_return(g_out_buf,sizeof(g_out_buf),hero);
			hero->send_msg_att();	
		}
	}
}

void Ride::equalAtt(Ride_Config *ride_config)
{
	strncpy(ridedata.nickName,ride_config->getNickName(),sizeof(ridedata.nickName));
	ridedata.quality=ride_config->getQuality();
	ridedata.expMax=ride_config->getExpMax();
	ridedata.hp+=ride_config->getLifeUpperVal();
	ridedata.mp+=ride_config->getMagicUpperVal();
	ridedata.outAttVal+=ride_config->getOutAttack();
	ridedata.inAttVal+=ride_config->getInAttack();
	ridedata.outDefVal+=ride_config->getOutDef();
	ridedata.inDefVal+=ride_config->getInDef();
	ridedata.hit+=ride_config->getHited();
	ridedata.crit+=ride_config->getCrit();
	ridedata.dodge+=ride_config->getDodge();
	ridedata.tenacity+=ride_config->getTenacity();
	ridedata.move+=ride_config->getMove();
	ridedata.evolutionMax=ride_config->getEvolutionMax();
	ridedata.exptimes=ride_config->getExpTimes();
	strncpy(ridedata.photoId,ride_config->getPhotoId(),sizeof(ridedata.photoId));
	
	for (int i=0;i<10;i++)
	{
		if (ride_config->getSkill(i)==1)
		{
			ridedata.skill[i].flag=1;
			ridedata.skill[i].value=rideSkill_config[i].value;
			ridedata.skill[i].level=rideSkill_config[i].level;
			ridedata.skill[i].levelMax=rideSkill_config[i].levelMax;
			strncpy(ridedata.skill[i].id,rideSkill_config[i].id,sizeof(ridedata.skill[i].id));
		}
		else if (ride_config->getSkill(i)==2)
		{
			ridedata.skill[i].flag=2;
			ridedata.skill[i].value=rideSkill_config[i].value;
			ridedata.skill[i].level=rideSkill_config[i].level;
			ridedata.skill[i].levelMax=rideSkill_config[i].levelMax;
			strncpy(ridedata.skill[i].id,rideSkill_config[i].id,sizeof(ridedata.skill[i].id));
		}
	}
}	

void Ride::minusAtt(Ride_Config *ride_config)
{	
	ridedata.hp-=ride_config->getLifeUpperVal();
	ridedata.mp-=ride_config->getMagicUpperVal();
	ridedata.outAttVal-=ride_config->getOutAttack();
	ridedata.inAttVal-=ride_config->getInAttack();
	ridedata.outDefVal-=ride_config->getOutDef();
	ridedata.inDefVal-=ride_config->getInDef();
	ridedata.hit-=ride_config->getHited();
	ridedata.crit-=ride_config->getCrit();
	ridedata.dodge-=ride_config->getDodge();
	ridedata.tenacity-=ride_config->getTenacity();
	ridedata.move-=ride_config->getMove();
}

void Ride::decreaseAtt(Hero *hero)							//去掉坐骑给人物加的属性
{
	if (hero==NULL)
	{
		return;
	}
	
	hero->memHero->basicHeroData.lifeUpperVal-=getHp();
	hero->memHero->basicHeroData.magicUpperVal-=getMp();
	hero->memHero->basicHeroData.outattack-=getOutAttVal();
	hero->memHero->basicHeroData.inattack-=getInAttVal();
	hero->memHero->basicHeroData.outdefense-=getOutDefVal();
	hero->memHero->basicHeroData.indefense-=getInDefVal();
	hero->memHero->basicHeroData.hited-=getHit();
	hero->memHero->basicHeroData.crit-=getCrit();
	hero->memHero->basicHeroData.dodge-=getDodge();
	hero->memHero->basicHeroData.tenacity-=getTenacity();
	
}

void Ride::increaseAtt(Hero *hero)							//加上坐骑给人物加的属性
{
	if (hero==NULL)
	{
		return;
	}
	
	hero->memHero->basicHeroData.lifeUpperVal+=getHp();
	hero->memHero->basicHeroData.magicUpperVal+=getMp();
	hero->memHero->basicHeroData.outattack+=getOutAttVal();
	hero->memHero->basicHeroData.inattack+=getInAttVal();
	hero->memHero->basicHeroData.outdefense+=getOutDefVal();
	hero->memHero->basicHeroData.indefense+=getInDefVal();
	hero->memHero->basicHeroData.hited+=getHit();
	hero->memHero->basicHeroData.crit+=getCrit();
	hero->memHero->basicHeroData.dodge+=getDodge();
	hero->memHero->basicHeroData.tenacity+=getTenacity();
}


bool Ride::ifFull(void)										//判断人物是否有坐骑了 有坐骑返回true 没有返回false
{	
	if (strcmp(ridedata.identity,"0")==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Ride::judgeEquipWear(int index)						//判断坐骑是否穿了装备
{
	if (index<0||index>=4)
	{
		return false;
	}
	if (ridedata.equip[index].flag==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ride::wearEquip(Equipment *equipment,int index)			//坐骑穿装备,改变坐骑数据
{	
	if (equipment==NULL)
	{
		return;
	}
	
	strncpy(ridedata.equip[index].goodsid,equipment->getentityid(),sizeof(ridedata.equip[index].goodsid));
	strncpy(ridedata.equip[index].typeId,equipment->getid(),sizeof(ridedata.equip[index].typeId));
	ridedata.equip[index].flag=1;
	
	ridedata.hp+=equipment->getlife();
	ridedata.mp+=equipment->getMagic();
	ridedata.outAttVal+=equipment->getoutattack();
	ridedata.inAttVal+=equipment->getinattack();
	ridedata.outDefVal+=equipment->getoutdefence();
	ridedata.inDefVal+=equipment->getindefence();
	ridedata.hit+=equipment->gethit();
	ridedata.crit+=equipment->getcrit();
	ridedata.dodge+=equipment->getdodge();
	ridedata.tenacity+=equipment->gettenacity();
	ridedata.move+=equipment->getMove();
}

void Ride::takeOffEquip(Equipment *equipment,int index)		//坐骑脱装备,改变坐骑数据
{
	if (equipment==NULL)
	{
		return;
	}
	
	strncpy(ridedata.equip[index].goodsid,"0",sizeof(ridedata.equip[index].goodsid));
	strncpy(ridedata.equip[index].typeId,"0",sizeof(ridedata.equip[index].typeId));
	ridedata.equip[index].flag=0;
	
	ridedata.hp-=equipment->getlife();
	ridedata.mp-=equipment->getMagic();
	ridedata.outAttVal-=equipment->getoutattack();
	ridedata.inAttVal-=equipment->getinattack();
	ridedata.outDefVal-=equipment->getoutdefence();
	ridedata.inDefVal-=equipment->getindefence();
	ridedata.hit-=equipment->gethit();
	ridedata.crit-=equipment->getcrit();
	ridedata.dodge-=equipment->getdodge();
	ridedata.tenacity-=equipment->gettenacity();
	ridedata.move-=equipment->getMove();
}

bool Ride::evolutionIncrease(int number,Hero *hero)						//坐骑获得进阶点,可以进阶返回true,不能进阶返回false
{
	if (hero==NULL)
	{
		cout<<"hero is null in ridedata.cpp 414"<<endl;
		return false;
	}

	ridedata.evolutionNow+=number;
	if (ridedata.evolutionNow>=ridedata.evolutionMax)
	{
		//进阶点达到最大,进化
		ridedata.evolutionNow-=ridedata.evolutionMax;
		char id[30]={0};
		map<string,Ride_Config*>::iterator it_before;
		map<string,Ride_Config*>::iterator it_after;
		snprintf(id,sizeof(id),"%s%d%d",ridedata.id,ridedata.quality,ridedata.level);
		it_before=id_to_ride.find(id);
		if (it_before==id_to_ride.end())
		{
			cout<<"jolly:ridedata quality:"<<ridedata.quality<<"  level:"<<ridedata.level<<"  id:"<<id<<endl;			
			return false;
		}
				
		ridedata.quality++;
		ridedata.id[11]=ridedata.id[11]+1;
		snprintf(id,sizeof(id),"%s%d%d",ridedata.id,ridedata.quality,ridedata.level);
		it_after=id_to_ride.find(id);
		if (it_after==id_to_ride.end())
		{
			cout<<"jolly:ridedata quality:"<<ridedata.quality<<"level:"<<ridedata.level<<"id:"<<id<<endl;
			return false;
		}

		decreaseAtt(hero);
		minusAtt(it_before->second);
		equalAtt(it_after->second);


		if (ridedata.quality==7)
		{
			//进阶到最大值 学习终极技能
			learnFinalSkill();
			finalSkillEffect();
		}			
		increaseAtt(hero);
			
		return true;		
	}
	else
	{
		return false;
	}
}

void Ride::initCost(void)									//初始化坐骑进阶花费元宝
{
	ridedata.cost=10;
}

void Ride::evolutionIncreaseCost(void)						//坐骑进阶使用元宝累增
{
	ridedata.cost+=2;
}

int Ride::getHp(void)
{
	if (ridedata.skill[0].flag==1)
	{
		return ridedata.hp*(100+ridedata.skill[0].value)/100;
	}
	else
	{
		return ridedata.hp;
	}
}

int Ride::getMp(void)
{
	if (ridedata.skill[1].flag==1)
	{
		return ridedata.mp*(100+ridedata.skill[1].value)/100;
	}
	else
	{
		return ridedata.mp;
	}	
}

int Ride::getOutAttVal(void)
{
	if (ridedata.skill[2].flag==1)
	{
		return ridedata.outAttVal*(100+ridedata.skill[2].value)/100;
	}
	else
	{
		return ridedata.outAttVal;
	}		
}

int Ride::getInAttVal(void)
{
	if (ridedata.skill[3].flag==1)
	{
		return ridedata.inAttVal*(100+ridedata.skill[3].value)/100;
	}
	else
	{
		return ridedata.inAttVal;
	}
}

int Ride::getInDefVal(void)
{
	if (ridedata.skill[5].flag==1)
	{
		return ridedata.inDefVal*(100+ridedata.skill[5].value)/100;
	}
	else
	{
		return ridedata.inDefVal;
	}	
}

int Ride::getOutDefVal(void)
{
	if (ridedata.skill[4].flag==1)
	{
		return ridedata.outDefVal*(100+ridedata.skill[4].value)/100;
	}
	else
	{
		return ridedata.outDefVal;
	}		
}

int Ride::getHit(void)
{
	if (ridedata.skill[6].flag==1)
	{
		return ridedata.hit*(100+ridedata.skill[6].value)/100;
	}
	else
	{
		return ridedata.hit;
	}	
}

int Ride::getCrit(void)
{
	if (ridedata.skill[7].flag==1)
	{
		return ridedata.crit*(100+ridedata.skill[7].value)/100;
	}
	else
	{
		return ridedata.crit;
	}
}

int Ride::getDodge(void)
{
	if (ridedata.skill[8].flag==1)
	{
		return ridedata.dodge*(100+ridedata.skill[8].value)/100;
	}
	else
	{
		return ridedata.dodge;
	}	
}

int Ride::getTenacity(void)
{
	if (ridedata.skill[9].flag==1)
	{
		return ridedata.tenacity*(100+ridedata.skill[9].value)/100;
	}
	else
	{
		return ridedata.tenacity;
	}		
}

void Ride::refreshSkill(vector<int> flag,Hero *hero)		//洗炼技能
{
	if (hero==NULL)
	{
		return;
	}

	decreaseAtt(hero);
	finalSkilldisapear();
	
	int randomFlag;
	for (int j=0;j<ridedata.finalSkill.gridNumber;j++)
	{
		if (flag[j]==0)				//0代表没有锁定,1代表锁定了
		{
			randomFlag=random_number(1,1000);
			for (int i=0;i<30;i++)
			{
				if (randomFlag<rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].rate)
				{
					ridedata.finalSkill.flag[j]=rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].flag;
					ridedata.finalSkill.color[j]=rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].color;
					ridedata.finalSkill.value[j]=random_number(rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].min,rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].max);
					break;
				}
			}
		}		
	}
	
	finalSkillEffect();
	increaseAtt(hero);
}

void Ride::learnFinalSkill(void)								//刚到7阶学习最终技能
{
	int randomFlag;
	ridedata.finalSkill.stage=0;
	ridedata.finalSkill.gridNumber=1;
	ridedata.finalSkill.number=0;
	ridedata.finalSkill.numberMax=rideSpecialSkill_config[ridedata.finalSkill.stage].number;
	ridedata.finalSkill.refreshNumber=rideSpecialSkill_config[ridedata.finalSkill.stage].freeNumber;
	for (int j=0;j<ridedata.finalSkill.gridNumber;j++)
	{
		randomFlag=random_number(1,1000);
		for (int i=0;i<30;i++)
		{
			if (randomFlag<rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].rate)
			{
				ridedata.finalSkill.flag[j]=rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].flag;
				ridedata.finalSkill.color[j]=rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].color;
				ridedata.finalSkill.value[j]=random_number(rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].min,rideSpecialSkill_config[ridedata.finalSkill.stage].skill[i].max);
				break;
			}
		}
	}		
}

void Ride::openOneSkillGrid(void)							//开启最终技能的孔
{
	ridedata.finalSkill.gridNumber++;
}

void Ride::finalSkillEffect(void)							//最终技能触发效果
{
	for (int i=0;i<ridedata.finalSkill.gridNumber;i++)
	{
		if (ridedata.finalSkill.flag[i]==0)
		{
			ridedata.outDefVal+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==1)
		{
			ridedata.inDefVal+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==2)
		{
			ridedata.outAttVal+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==3)
		{
			ridedata.inAttVal+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==4)
		{
			ridedata.hp+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==5)
		{
			ridedata.mp+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==6)
		{
			ridedata.hit+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==7)
		{
			ridedata.crit+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==8)
		{
			ridedata.dodge+=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==9)
		{
			ridedata.tenacity+=ridedata.finalSkill.value[i];
		}
	}
}

void Ride::finalSkilldisapear(void)							//最终技能消失效果
{
	for (int i=0;i<ridedata.finalSkill.gridNumber;i++)
	{
		if (ridedata.finalSkill.flag[i]==0)
		{
			ridedata.outDefVal-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==1)
		{
			ridedata.inDefVal-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==2)
		{
			ridedata.outAttVal-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==3)
		{
			ridedata.inAttVal-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==4)
		{
			ridedata.hp-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==5)
		{
			ridedata.mp-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==6)
		{
			ridedata.hit-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==7)
		{
			ridedata.crit-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==8)
		{
			ridedata.dodge-=ridedata.finalSkill.value[i];
		}
		else if (ridedata.finalSkill.flag[i]==9)
		{
			ridedata.tenacity-=ridedata.finalSkill.value[i];
		}
	}
}

int Ride::countPower(void)									//算坐骑战力
{
	ridedata.power=0.01*getHp()+0.01*getMp()+0.5*getOutAttVal()+0.5*getInAttVal()+0.2*getOutDefVal()+0.2*getInDefVal()+4*getHit()+4*getCrit()+3*getDodge()+3*getTenacity();
	return ridedata.power;
}

void Ride::ride_msg_return(char *msg,int len,Hero *hero)
{
	if (msg==NULL||hero==NULL)
	{
		return;
	}
	 
	if (ifFull())
	{	
		snprintf(msg,len,"%d,%d,%d,%s,%s",30,0,1,ridedata.identity,ridedata.id);
		for (int i=0;i<4;i++)
		{
			if (ridedata.equip[i].flag==1)
			{
				snprintf(msg+strlen(msg),len-strlen(msg),",%d,%s,%s",i,ridedata.equip[i].goodsid,ridedata.equip[i].typeId);				
			}
			else
			{
				snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d",i,0,0);
			}
		}
		
		for (int i=0;i<10;i++)
		{
			snprintf(msg+strlen(msg),len-strlen(msg),",%d,%s",ridedata.skill[i].flag,ridedata.skill[i].id);
		}
		
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",countPower(),ridedata.level,ridedata.expNow,ridedata.expMax,getHp(),getMp(),getOutAttVal(),getInAttVal(),getOutDefVal(),getInDefVal(),getHit(),getCrit(),getDodge(),getTenacity(),ridedata.move,ridedata.finalSkill.stage);
	}
	else
	{
		snprintf(msg,len,"%d,%d,%d",30,0,0);
	}
}

void Ride::ride_wear_equip(char *msg,int len,int index,char *identity,char *id)				//坐骑穿装备返回
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",30,1,1,index,identity,id,getHp(),getMp(),getOutAttVal(),getInAttVal(),getOutDefVal(),getInDefVal(),getHit(),getCrit(),getDodge(),getTenacity(),ridedata.move,countPower());
}

void Ride::ride_takeoff_equip(char *msg,int len,int index,char *identity,char *id)			//坐骑脱装备返回
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",30,1,2,index,identity,id,getHp(),getMp(),getOutAttVal(),getInAttVal(),getOutDefVal(),getInDefVal(),getHit(),getCrit(),getDodge(),getTenacity(),ridedata.move,countPower());
}

void Ride::ride_evolution_return(char *msg,int len,int number)			//坐骑进阶信息返回
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%d,%d,%d",30,2,ridedata.evolutionNow,ridedata.evolutionMax,number,ridedata.cost);
}

void Ride::ride_finalSkill_return(char *msg,int len)				//坐骑洗炼技能,信息返回
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d",30,3,ridedata.finalSkill.refreshNumber,ridedata.finalSkill.gridNumber,rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[0],rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[1],rideSpecialSkill_config[ridedata.finalSkill.stage].refreshCost[2]);
	
	for (int i=0;i<3;i++)
	{
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d",ridedata.finalSkill.flag[i],ridedata.finalSkill.value[i],ridedata.finalSkill.color[i]);
	}
}