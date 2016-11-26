#include "pet.h"
#include"boxAsist.h"
#include"move_asist.h"
#include"attack_wagon.h"
#include"attackBottle.h"
#include"bag_operator.h"
extern struct ev_loop *loops;
extern TimerContainer<Pet*> *petThk;
extern map<string,Pet_Config*> id_to_pet;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Pet*> id_to_activePet;
extern int sock_fd;
extern struct timeval myTime;
extern char g_out_buf[20480];
extern Pet_Xidian pet_xidian;
extern Pet_ZhanLi pet_zhanli[10];

void Pet::pet_attack_monster(MonsterBase *monster)		//攻击怪物
{
	attackSeq++;
	if (attackSeq%4==0)
	{
		int skillIndex=attackSeq/4;		
		if (skillIndex>0)
		{
			if (petdata->petskilldata[skillIndex-1].level==0)
			{
				attactMonster(monster,0.0,1.0,petdata->normalSkill);
			}
			else
			{
				double ratio=(petdata->petskilldata[skillIndex-1].effect)/100;
				if(skillIndex==1||skillIndex==3)
				{
					attactMonster(monster,ratio,1.0,petdata->petskilldata[skillIndex-1].id);
				}
				else
				{
					attactMonsterArrange(monster,ratio,1.0,skillIndex);
				}
			}
		}		
	}
	else
	{	
		attactMonster(monster,0.0,1.0,petdata->normalSkill);
	}
	if (attackSeq==16)
	{
		attackSeq=0;
	}
}

void Pet::pet_attack_hero(Hero *tarHero)				//攻击玩家
{	
	attackSeq++;
	if (attackSeq%4==0)
	{
		int skillIndex=attackSeq/4;		
		if (skillIndex>0)
		{
			if (petdata->petskilldata[skillIndex-1].level==0)
			{
				attactHero(tarHero,0.0,1.0,petdata->normalSkill);
			}
			else
			{
				double ratio=(petdata->petskilldata[skillIndex-1].effect)/100;
				attactHero(tarHero,ratio,1.0,petdata->petskilldata[skillIndex-1].id);
				if(skillIndex==1||skillIndex==3)
				{
					attactHero(tarHero,ratio,1.0,petdata->petskilldata[skillIndex-1].id);
				}
				else
				{
					attactHeroArrange(tarHero,ratio,1.0,skillIndex);
				}
			}
		}		
	}
	else
	{		
		attactHero(tarHero,0.0,1.0,petdata->normalSkill);
	}
	
	if (attackSeq==16)
	{
		attackSeq=0;
	}
}

void Pet::pet_attack_bottle(Bottle *bottInst)				//攻击瓶罐
{	
	if (bottInst==NULL)
	{
		return;
	}
	attackSeq++;
	if (attackSeq%4==0)
	{
		int skillIndex=attackSeq/4;		
		if (skillIndex>0)
		{
			if (petdata->petskilldata[skillIndex-1].level==0)
			{
				petAttackBottle(masterId,petdata->identity,nowPix,"0",bottInst);
			}
			else
			{	
				petAttackBottle(masterId,petdata->identity,nowPix,petdata->petskilldata[skillIndex-1].id,bottInst);
			}
		}
		
	}
	else
	{		
		petAttackBottle(masterId,petdata->identity,nowPix,"0",bottInst);
	}
	
	if (attackSeq==16)
	{
		attackSeq=0;
	}
}

Pet::Pet(Pet_Config* pet_config, PetData *_petdata)
{
	petdata = _petdata;
	char* uuid = cid();
	strncpy(petdata->identity,uuid,sizeof(petdata->identity));	//宠物实例id
	free(uuid);
	if (strlen(pet_config->getId())!=0)
	{
		strncpy(petdata->id,pet_config->getId(),sizeof(petdata->id));																	//宠物id
	}
	else
	{
		cout<<"jolly:pet id error 120 pet.cpp"<<endl;
		strncpy(petdata->id,"0",sizeof(petdata->id));																			//宠物id(对应宠物蛋id)
	}
	if (strlen(pet_config->getNickName())!=0)
	{
		strncpy(petdata->nickName,pet_config->getNickName(),sizeof(petdata->nickName));			//宠物昵称
	}
	else
	{
		strncpy(petdata->nickName,"0",sizeof(pet_config->getNickName()));					//宠物昵称
	}
	petdata->level=pet_config->getLevel();																	//等级
	petdata->outAttackVal=pet_config->getOutAttackVal();														//当前外功攻击
	cout<<"pet_config->getOutAttackVal():"<<pet_config->getOutAttackVal()<<endl;
	cout<<"petdata->outAttackVal:"<<petdata->outAttackVal<<endl;
	petdata->outAttackValRate=pet_config->getOutAttackValRate();												//外功攻击增长值
	petdata->inAttackVal=pet_config->getInAttackVal();														//当前内功攻击
	petdata->inAttackValRate=pet_config->getInAttackValRate();												//内功攻击增长值
	petdata->hit=pet_config->getHit();																		//当前命中
	petdata->hitRate=pet_config->getHitRate();																//命中增长值
	petdata->crit=pet_config->getCrit();																		//当前暴击
	petdata->critRate=pet_config->getCritRate();																//暴击增长值
	petdata->generation=pet_config->getGeneration();															//当前的代数
	petdata->quality=pet_config->getQuality();																//宠物品质
	petdata->type=pet_config->getType();																		//宠物类型
	petdata->range=pet_config->getRange();
	petdata->flag=pet_config->getFlag();																//1代表战宠 2代表骑宠
	petdata->needCount=pet_config->getNeedCount();	
	petdata->needNumber=pet_config->getNeedNumber();
	petdata->expTimes=pet_config->getExpTimes();
	if (strlen(pet_config->getPhotoId())!=0)
	{
		strncpy(petdata->photoId,pet_config->getPhotoId(),sizeof(petdata->photoId));
	}
	else
	{
		cout<<"jolly:pet photo error 166 pet.cpp"<<endl;
		strncpy(petdata->photoId,"0",sizeof(petdata->photoId));
	}
	strncpy(petdata->nextid,pet_config->getNextid(),sizeof(petdata->nextid));
	strncpy(petdata->normalSkill,pet_config->getNormal(),sizeof(petdata->normalSkill));
	strncpy(petdata->nextGenid,pet_config->getNextGenid(),sizeof(petdata->nextGenid));
	cout<<"pet_config->getNextGenid():"<<pet_config->getNextGenid()<<endl;
	cout<<"petdata->nextGenid:"<<petdata->nextGenid<<endl;
	
	petdata->expNow=0;																						//当前经验
	petdata->expAgo=0;																						//上级所需经验
	petdata->expNeed=100;																			//升级所需经验
	petdata->active=0;				//出战为1,休息为0
	petdata->curNumber=0;
	petdata->curCount=0;
	countPower();
	
	fightTime=0;
	
	petdata->curNumber=0;
	attackSeq=0;	
	
	for (int i=0;i<4;i++)
	{
		petdata->succincted[i]=0;
		succincting[i]=0;		
		initSkill(i);
	}
	
	for (int i=0;i<3;i++)
	{
		petdata->expDrag[i]=0;
	}
	petdata->expDrag[0]=5;
	
	mapNow=NULL;
	
	memset(masterId, 0, sizeof (masterId));
		
	saveTotalProperty();	
	routeClear();
	speed = NORMAL_PET_SPEED;
}

Pet::Pet(PetData* _petdata)
{
	petdata=_petdata;
	for (int i=0;i<4;i++)
	{
		succincting[i]=0;
	}	
	fightTime=0;
	attackSeq=0;
	saveTotalProperty();
	
	memset(masterId, 0, sizeof (masterId));
	
	routeClear();
	speed = NORMAL_PET_SPEED;

}

Pet::~Pet(void)
{
	cout<<"析构宠物了"<<endl;
	mapNow=NULL;	
	// id_to_activePet.erase(petdata->identity); //added by benliao 2012.1.2 
}

Map_Inform* Pet::getMapInform(void)
{
	return mapNow;
}

Point Pet::getLogicNow(void)
{
	return nowLocation;
}
/*设置主人id*/
void Pet::setMasterId(char *heroId)
{
	strncpy(masterId, heroId, sizeof (masterId));
}

void Pet::saveTotalProperty(void)
{
	outAttackValTotal=petdata->outAttackVal+petdata->succincted[2];
	inAttackValTotal=petdata->inAttackVal+petdata->succincted[3];
	hitTotal=petdata->hit+petdata->succincted[0];
	critTotal=petdata->crit+petdata->succincted[1];
}

int Pet::getJingjieEffect(void)
{
	return jingjieEffect;
}

int Pet::growNeedExp(void)
{
	int _gradeNow=petdata->level+1;
	if(_gradeNow>0&&_gradeNow<11)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*10;
	}
	if(_gradeNow>10&&_gradeNow<21)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*16;
	}
	if(_gradeNow>20&&_gradeNow<31)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*2;
	}
	if(_gradeNow>30&&_gradeNow<41)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*5;
	}
	if(_gradeNow>40&&_gradeNow<51)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*10;
	}
	if(_gradeNow>50&&_gradeNow<61)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*20;
	}
	if(_gradeNow>60&&_gradeNow<71)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*35;
	}
	if(_gradeNow>70&&_gradeNow<81)
	{
		petdata->expNeed=petdata->expAgo+_gradeNow*_gradeNow*_gradeNow*65;
	}
	return petdata->expNeed;
}

int Pet::random(int begin,int end)
{
	// cout<<"begin:"<<begin<<"        end:"<<end<<endl;
	int between=end-begin;
	// cout<<"between:"<<between<<endl;
	int result=rand()%(between+1);
	result+=begin;
	return result;
}

int Pet::getFightTime(void)
{
	return fightTime;
}

void Pet::setFightTime(int _fightTime)
{
	fightTime=_fightTime;
}

void Pet::growExp(int exp,int heroLevel,Hero *hero)						//增加经验
{	
	if (hero==NULL)
	{
		return;
	}
	
	if (heroLevel<=petdata->level)
	{
		return;
	}
	
	
	exp=exp*20;
	petdata->expNow+=exp;
	for (;petdata->expNow>petdata->expNeed;)
	{
		if (petdata->expNeed<=0)
		{
			return;
		}
		

		levelUp();
		
		memset(g_out_buf,0,sizeof(g_out_buf));
		msg_levelUp(g_out_buf,sizeof(g_out_buf),hero->getPetBox()->getActivePetIndex());
		send_msg(hero->getFd(),g_out_buf);
	}
}

void Pet::savePetFiveEle(void)
{
	// petdata->fiveElement.level=fiveElem->getLevel();
	// petdata->fiveElement.element=fiveElem->getElem();
	// petdata->fiveElement.expNow=fiveElem->getExpNow();
	// petdata->fiveElement.expForNext=fiveElem->getExpForNext();
}

void Pet::levelUp(void)							//宠物升级 属性改变
{
	petdata->level++;
	petdata->outAttackVal+=petdata->outAttackValRate;
	petdata->inAttackVal+=petdata->inAttackValRate;
	petdata->hit+=petdata->hitRate;
	petdata->crit+=petdata->critRate;
	petdata->expNow-=petdata->expNeed;
	petdata->expAgo=petdata->expNeed;
	petdata->expNeed=growNeedExp();	
}

int Pet::getActive(void)						//获得宠物出战状态
{
	return petdata->active;
}

char* Pet::getIdentity(void)
{
	return petdata->identity;
}

char* Pet::getId(void)
{
	return petdata->id;
}	

char* Pet::getNickName(void)
{
	cout<<"petdata->nickName:"<<petdata->nickName<<endl;
	return petdata->nickName;
}

void  Pet::setMapInform(Map_Inform* _map)
{
	mapNow=_map;
}

int Pet::getQuality(void)
{
	return petdata->quality;
}

int Pet::getLevel(void)
{
	return petdata->level;
}

int Pet::getGeneration(void)
{
	return petdata->generation;
}
int Pet::getType(void)
{
	return petdata->type;
}

char* Pet::getPhotoId(void)
{
	return petdata->photoId;
}

void Pet::setPet_boxIndex(int _pet_boxIndex)
{
	pet_boxIndex=_pet_boxIndex;
}

int Pet::getPet_boxIndex(void)
{
	return pet_boxIndex;
}

int Pet::getFlag(void)
{
	return petdata->flag;
}

void Pet::setActive(Hero *hero,int _active)							//使宠物出战	
{
	petdata->active=_active;
	strncpy(masterId, hero->getIdentity(), sizeof (masterId));
	if (petdata->active==1)
	{	
		
		routeClear();
		speed = NORMAL_PET_SPEED;
		id_to_activePet.insert(map<string,Pet*>::value_type(petdata->identity,this));	
	}
	else 
	{	
		routeClear();
		speed = NORMAL_PET_SPEED;
		send_msg_downLine(hero);
		// stopMoveTimer();
	}
}

void Pet::succinct(int index)
{
	for (int i=0;i<4;i++)
	{
		if (i==0)
		{
			if (petdata->succincted[i]==0)
			{
				succincting[i]=random(1,pet_xidian.hit.max);
			}
			else
			{
				succincting[i]=random(pet_xidian.hit.min,pet_xidian.hit.max);
			}
			
			if (succincting[i]==0)
			{
				succincting[i]=random(pet_xidian.hit.min,0);
			}
		}
		else if (i==1)
		{
			if (petdata->succincted[i]==0)
			{
				succincting[i]=random(1,pet_xidian.crit.max);
			}
			else
			{
				succincting[i]=random(pet_xidian.crit.min,pet_xidian.crit.max);
			}
			
			if (succincting[i]==0)
			{
				succincting[i]=random(pet_xidian.crit.min,0);
			}
		}
		else if (i==2)
		{
			if (petdata->succincted[i]==0)
			{
				succincting[i]=random(1,pet_xidian.outAttVal.max);
			}
			else
			{
				succincting[i]=random(pet_xidian.outAttVal.min,pet_xidian.outAttVal.max);
			}
			
			if (succincting[i]==0)
			{
				succincting[i]=random(pet_xidian.outAttVal.min,0);
			}
		}
		else if (i==3)
		{
			if (petdata->succincted[i]==0)
			{
				succincting[i]=random(1,pet_xidian.inAttVal.max);
			}
			else
			{
				succincting[i]=random(pet_xidian.inAttVal.min,pet_xidian.inAttVal.max);
			}
			
			if (succincting[i]==0)
			{
				succincting[i]=random(pet_xidian.inAttVal.min,0);
			}
		}
	}	
}

bool Pet::canGoldSaveSuccinct(int index)
{
	int max=returnValue(index);
	if (petdata->succincted[index]==max)
	{
		return false;
	}
	else
	{
		if (succincting[index]!=0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Pet::saveSuccinctInGold(int index,Hero *hero,int number)
{	
	if (hero==NULL)
	{
		return;
	}

	petdata->succincted[index]=petdata->succincted[index]+succincting[index];
	succincting[index]=0;
	int max=returnValue(index);
	if (petdata->succincted[index]>max)
	{
		petdata->succincted[index]=max;
	}	
	else if (petdata->succincted[index]<0)
	{
		petdata->succincted[index]=0;
	}
	saveTotalProperty();
	succincting[index]=0;	
}

void Pet::saveSuccinctInGameMoney(Hero *hero,int index)
{
	if (hero==NULL)
	{
		return;
	}
	for (int i=0;i<4;i++)
	{
		petdata->succincted[i]=petdata->succincted[i]+succincting[i];
		succincting[i]=0;
		int max=returnValue(i);
		if (petdata->succincted[i]>max)
		{
			petdata->succincted[i]=max;
		}
		else if (petdata->succincted[i]<0)
		{
			petdata->succincted[i]=0;
		}		
	}
	// cout<<"pet petdata->succincted is::"<<g_out_buf<<endl;
	saveTotalProperty();
}

int Pet::returnValue(int index)
{
	if (index==0)
	{
		return petdata->hit;
	}
	else if (index==1)
	{
		return petdata->crit;
	}
	else if (index==2)
	{
		return petdata->outAttackVal;
	}
	else if (index==3)
	{
		return petdata->inAttackVal;
	}
}

bool Pet::evolution(Hero *hero,int index)
{
	if (hero==NULL)
	{
		return false;
	}
	int randomNum;		
	randomNum=random(0,5);
	int evoNum;
	if (randomNum<3)
	{
		evoNum=1;
	}
	else if (randomNum==5)
	{
		evoNum=2;
	}
	else
	{
		evoNum=3;
	}
	petdata->curNumber+=evoNum;
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (petdata->curNumber>=petdata->needNumber)
	{
		petdata->curNumber-=petdata->needNumber;
		evolutionSuccess(hero);
		msg_evolution(g_out_buf,sizeof(g_out_buf),index);
		send_msg(hero->getFd(),g_out_buf);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d,%d",10,PET_EVOLUTION,petdata->identity,index,evoNum,petdata->curNumber,petdata->needNumber);
		send_msg(hero->getFd(),g_out_buf);
		return true;
	}	
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d,%d",10,PET_EVOLUTION,petdata->identity,index,evoNum,petdata->curNumber,petdata->needNumber);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
}
	

void Pet::msg_evolution_success(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d",10,PET_EVOLUTION_RETURN,petdata->identity,index,petdata->id,petdata->quality,\
	petdata->curNumber,petdata->needNumber,getHit(),getCrit(),getOutAtt(),getInAtt());
}

void Pet::send_msg_succinctInfo(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",10,PET_SUCCINCT_FIRST,petdata->identity,petdata->id,index,petdata->quality,petdata->succincted[2],petdata->outAttackVal,succincting[2],petdata->succincted[3],petdata->inAttackVal,succincting[3],petdata->succincted[1],petdata->crit,succincting[1],petdata->succincted[0],petdata->hit,succincting[0],pet_xidian.cost);
}

void Pet::send_msg_jingJie(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	int nextGeneration;
	if (petdata->needCount==0)
	{
		nextGeneration=0;
	}
	else
	{
		nextGeneration=petdata->generation+1;
	}
	snprintf(msg,len,"%d,%d,%s,%s,%d,%d,%d,%d",10,PET_JINGJIE,petdata->identity,petdata->id,index,petdata->quality,petdata->generation,nextGeneration);
	map<string,Pet_Config*>::iterator it;
	it=id_to_pet.find(petdata->nextGenid);
	if (it==id_to_pet.end())
	{
		cout<<"pet nextJingjieId:"<<petdata->nextGenid<<endl;
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d,%d,%d,%d,%d,%d",getOutAtt(),0,getInAtt(),0,getCrit(),0,getHit(),0);
	}
	else
	{
		int outAtt=it->second->getOutAttackVal()+it->second->getOutAttackValRate()*(petdata->level-1)-petdata->outAttackVal;
		int inAtt=it->second->getInAttackVal()+it->second->getInAttackValRate()*(petdata->level-1)-petdata->inAttackVal;
		int crit=it->second->getCrit()+it->second->getCritRate()*(petdata->level-1)-petdata->crit;
		int hit=it->second->getHit()+it->second->getHitRate()*(petdata->level-1)-petdata->hit;
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d,%d,%d,%d,%d,%d",getOutAtt(),outAtt,getInAtt(),inAtt,getCrit(),crit,getHit(),hit);
	}
	jingjieEffect=goodsReturnInt("f_cl_103_100",0);
	snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%s,%d",petdata->curCount,petdata->needCount,"f_cl_103_100",jingjieEffect);
}

bool Pet::canEvolutionRefresh(void)
{
	if (petdata->needNumber==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Pet::evolutionSuccess(Hero *hero)
{	
	if (hero==NULL)
	{
		return;
	}	
	petdata->quality++;
	map<string,Pet_Config*>::iterator pet_it;		
	pet_it=id_to_pet.find(petdata->nextid);
	if (pet_it==id_to_pet.end())
	{
		cout<<"According to petId can't find the pet_config in pet.cpp"<<endl;
		return;
	}
	else
	{	
		Pet_Config *pet_config=pet_it->second;
		petdata->outAttackValRate=pet_config->getOutAttackValRate();
		petdata->inAttackValRate=pet_config->getInAttackValRate();
		petdata->hitRate=pet_config->getHitRate();
		petdata->critRate=pet_config->getCritRate();
		petdata->needNumber=pet_config->getNeedNumber();
		
		cout<<"petdata->level:"<<petdata->level<<endl;
		cout<<"petdata->nickName:"<<petdata->nickName<<endl;
		petdata->outAttackVal=pet_config->getOutAttackVal()+petdata->outAttackValRate*(petdata->level-1);
		petdata->inAttackVal=pet_config->getInAttackVal()+petdata->inAttackValRate*(petdata->level-1);
		petdata->hit=pet_config->getHit()+petdata->hitRate*(petdata->level-1);
		petdata->crit=pet_config->getCrit()+petdata->critRate*(petdata->level-1);
		
		petdata->quality=pet_config->getQuality();
		
		
		strncpy(petdata->nextGenid,pet_config->getNextGenid(),sizeof(petdata->nextGenid));
		strncpy(petdata->nextid,pet_config->getNextid(),sizeof(petdata->nextid));
		strncpy(petdata->id,pet_config->getId(),sizeof(petdata->id));	
		strncpy(petdata->photoId,pet_config->getPhotoId(),sizeof(petdata->photoId));
		
		saveTotalProperty();
	}	
}

void Pet::msg_evolution(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	int nextQuality;
	if (petdata->needNumber==0)
	{
		nextQuality=-1;
	}
	else 
	{
		nextQuality=petdata->quality+1;
	}
	snprintf(msg,len,"%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d",10,PET_EVOLUTION_MSG,index,petdata->identity,petdata->id,petdata->quality,nextQuality,getOutAtt(),getInAtt(),getCrit(),getHit());
	map<string,Pet_Config*>::iterator it;
	it=id_to_pet.find(petdata->nextid);
	if (it==id_to_pet.end())
	{
		cout<<"pet nextZiZhiId:"<<petdata->nextid<<endl;
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d,%d",0,0,0,0);
	}
	else
	{
		int outAtt=it->second->getOutAttackVal()+it->second->getOutAttackValRate()*(petdata->level-1)-petdata->outAttackVal;
		int inAtt=it->second->getInAttackVal()+it->second->getInAttackValRate()*(petdata->level-1)-petdata->inAttackVal;
		int crit=it->second->getCrit()+it->second->getCritRate()*(petdata->level-1)-petdata->crit;
		int hit=it->second->getHit()+it->second->getHitRate()*(petdata->level-1)-petdata->hit;
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%d,%d",outAtt,inAtt,crit,hit);
	}
	snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%s,%d",petdata->curNumber,petdata->needNumber,"f_cl_124_100",20000);
}

int Pet::getExpNow(void)
{
	return petdata->expNow;
}

void Pet::setExpNow(int _expNow)
{
	petdata->expNow=_expNow;
}

Point Pet::getLocation(Hero *hero)
{
	Point heroLocation=hero->getLogPt();
	Point _nowLocation;
	int randomNum=random(0,7);
	if (randomNum==0)
	{
		_nowLocation._x=heroLocation._x+2;
	}
	else if(randomNum==1)
	{
		_nowLocation._x=heroLocation._x+2;
		_nowLocation._y=heroLocation._y+2;
	}
	else if(randomNum==2)
	{
		_nowLocation._y=heroLocation._y+2;
	}
	else if(randomNum==3)
	{
		_nowLocation._x=heroLocation._x-2;
		_nowLocation._y=heroLocation._y+2;
	}	
	else if(randomNum==4)
	{		
		_nowLocation._x=heroLocation._x-2;
	}
	else if(randomNum==5)
	{
		_nowLocation._y=heroLocation._y-2;
	}
	else if(randomNum==6)
	{
		_nowLocation._x=heroLocation._x-2;
		_nowLocation._y=heroLocation._y-2;
	}
	else if(randomNum==7)
	{
		_nowLocation._x=heroLocation._x+2;
		_nowLocation._y=heroLocation._y-2;
	}
	return _nowLocation;
}
	
void Pet::send_pet_attr(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,",%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",\
	petdata->identity,petdata->id,petdata->nickName,petdata->level,petdata->quality,petdata->expNow,petdata->expNeed,getHit(),getCrit(),getOutAtt(),getInAtt(),petdata->hit,petdata->crit,petdata->outAttackVal,petdata->inAttackVal);
}

void Pet::msg_return_pet(char *msg,int _index,int len,int skillNumber,int flag)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d",10,PET_USE,_index,petdata->flag,petdata->identity,petdata->id,petdata->nickName,petdata->level,petdata->quality,petdata->generation,petdata->expNow,petdata->expNeed,getHit(),getCrit(),getOutAtt(),getInAtt(),petdata->hit,petdata->crit,petdata->outAttackVal,petdata->inAttackVal,petdata->curNumber,petdata->needNumber,petdata->type,petdata->power,"f_cl_139_100",skillNumber,4);
	
	for (int i=0;i<4;i++)
	{
		snprintf(msg+strlen(msg),len-strlen(msg),",%s,%d,%d,%d,%d",petdata->petskilldata[i].id,petdata->petskilldata[i].level,petdata->petskilldata[i].limit,petdata->petskilldata[i].needNumber,petdata->petskilldata[i].needCount);
	}		
	
	snprintf(msg+strlen(msg),len-strlen(msg),",%d",flag);
}

void Pet::msg_active(char *msg,int len)
{	
	if (msg==NULL)
	{
		return;
	}
	//强制保护，没得办法，总是出错。benliao 2013.1.1
	petdata->identity[sizeof(petdata->identity)-1]=0;
	petdata->id[sizeof(petdata->id)-1]=0;
	petdata->nickName[sizeof(petdata->nickName)-1]=0;
	petdata->photoId[sizeof(petdata->photoId)-1]=0;
	memset(msg, 0, len);
	snprintf(msg,len,"%d,%d,%s,%s,%s,%d,%d,%d,%s,%s,%d",10,PET_ACTIVE,petdata->identity,petdata->id,petdata->nickName,\
	petdata->level,nowPix._x,nowPix._y,masterId,petdata->photoId,petdata->quality);
}

void Pet::send_msg_active(Hero *hero)																	///////////////宠物出战,向九宫格内玩家发送消息
{
	if (hero==NULL)
	{
		cout<<"jolly:Hero is null pet.cpp 1061"<<endl;
		return;
	}
	strncpy(masterId, hero->getIdentity(), sizeof masterId);
	
	mapNow=hero->getMap();
		
	if (mapNow==NULL)
	{
		cout<<"Pet map is null"<<endl;
		return;
	}
	
	nowLocation=hero->getLogPt();
	
	Point heroPix;
	heroPix = hero->getLocation();
	nowPix = heroPix;
	// startMoveTimer();
	msg_active(g_out_buf,sizeof(g_out_buf));
	
	StyObj obj(petdata->identity,PET_STYLE_TYPE);
	
    mapNow->insertID(obj); 
	
    Nbox *box = mapNow->getBox();   	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(g_out_buf);
}

void Pet::send_msg_chuzhan(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%s,%d",10,PET_CHUZHAN,1,petdata->identity,index);
}

void Pet::send_msg_zhaohui(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%d,%s,%d",10,PET_CHUZHAN,0,petdata->identity,index);
}

void Pet::msg_downline(char *msg,int len)
{		
	if (msg==NULL)
	{
		return;
	}
	if(petdata == 0) return;

	memset(msg, 0, len);		
	snprintf(msg,len-1,"%d,%d,%s,%d",2,DOWN_LINE,petdata->identity,1);
}

void Pet::send_msg_downLine(Hero *hero)															/////////宠物休息,向九宫格内的玩家发送消息
{
	StyObj obj(petdata->identity,PET_STYLE_TYPE);
	
	
	if (hero==NULL)
	{
		cout<<"jolly:hero is null pet_1134"<<endl;
		return;
	}
	
	mapNow=hero->getMap();
	if (mapNow==NULL)
	{
		cout<<"jolly:mapnow is null pet 1141"<<endl;
		return ;
	}		
	
	//发给玩家自己的信息
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s",10,PET_DOWNLINE,petdata->identity);
	send_msg(hero->getFd(),g_out_buf);

	//发给九宫格内其他玩家的信息
	char msg_others[100]={'\0'};
	msg_downline(msg_others,sizeof(msg_others));
	
    Nbox *box = mapNow->getBox();    	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(msg_others);

	// cout<<"--------------------Pet deleteId begin-------------------"<<endl;
	mapNow->deleteID(obj);  
	// cout<<"--------------------Pet deleteId end-------------------"<<endl;
	
	map<string,Pet*>::iterator it;
	
	cout<<"id_to_activePet.size():"<<id_to_activePet.size()<<endl;
	it=id_to_activePet.find(petdata->identity);
	
	if (it==id_to_activePet.end())
	{
		cout<<"error-------------------------------------pet.cpp 771"<<endl;
		return;
	}
	else
	{
		// removePassiveSkill(hero);
		id_to_activePet.erase(it);	
	}
}

//宠物强制下线
void Pet::petDownLine(void)
{
	StyObj obj(petdata->identity,PET_STYLE_TYPE);

	if (mapNow==NULL)
	{
		cout<<"jolly:mapnow is null pet 1141"<<endl;
		return ;
	}		

	//发给九宫格内其他玩家的信息
	memset(g_out_buf,0,sizeof(g_out_buf));
	msg_downline(g_out_buf,sizeof(g_out_buf));
	
    Nbox *box = mapNow->getBox();    	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(g_out_buf);

	// cout<<"--------------------Pet deleteId begin-------------------"<<endl;
	mapNow->deleteID(obj);  
	// cout<<"--------------------Pet deleteId end-------------------"<<endl;
	
	map<string,Pet*>::iterator it;
	
	// cout<<"id_to_activePet.size():"<<id_to_activePet.size()<<endl;
	it=id_to_activePet.find(petdata->identity);
	
	if (it==id_to_activePet.end())
	{
		cout<<"error-------------------------------------pet.cpp 771"<<endl;
		return;
	}
	else
	{
		// removePassiveSkill(hero);
		id_to_activePet.erase(it);	
	}
}

void Pet::msg_levelUp(char *msg,int len,int _index)
{	
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%d,%s,%s,%s,%d,%d,%d,%d,%d",10,PET_LEVEL_UP,_index,petdata->flag,petdata->identity,petdata->id,petdata->nickName,petdata->level,petdata->quality,petdata->generation,petdata->type,petdata->power);
}

//判断该索引的技能是否已经学习,没学返回true;已经学习了 返回false
bool Pet::isSkillLearn(int index)
{
	if (petdata->petskilldata[index-1].flag==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Pet::setNickName(char* _nickName)
{
	memset(petdata->nickName,'\0',sizeof(petdata->nickName));
	strncpy(petdata->nickName,_nickName,sizeof(petdata->nickName));
}

void Pet::setNowPix(Point _nowPix, int flag)
{
	if(mapNow==0) return; //added by benliao 2013.1.9
	if (flag == 0)
	{
		routeClear();
		currPt = endPt = _nowPix;
	}
	nowPix=_nowPix;
	int digst=mapNow->getBaseDigst();
	Point temp=MapExchangeLogical(nowPix);
	nowLocation._x=temp._x;
	nowLocation._y=temp._y+digst;
}
	
void Pet::setNowLocation(Point _nowLocation)
{
	nowLocation=_nowLocation;
	int digst=mapNow->getBaseDigst();
	Point temp=nowLocation;
	temp._y -= digst;
	nowPix = LogicalExchangeMap(temp);	
}

//获得宠物攻击范围
int Pet::getAttackRange(void)
{
	return petdata->range;
}

PetData Pet::getStruct(void)
{	
	// savePetFiveEle();
	return *petdata;
}

/*宠物场景跳转*/
bool Pet::enter_scene(Hero *hero)
{
	Nbox *box;
	
	map<string,StyObj> nbox_id_set;
	
	
	if(hero == NULL)
	{
		return false;
	}
	mapNow = hero->getMap();
	
	if(mapNow == NULL)
	{
		return false;
	}
	box = mapNow->getBox();
	
	if(box == NULL)
	{
		return false;
	}
	
	
	
	strncpy(masterId, hero->getIdentity(), sizeof masterId);
	
	setNowPix(hero->getLocation());
	
	/*将identity插入地图信息容器中管理*/	
	
	StyObj obj(petdata->identity,PET_STYLE_TYPE);
	
    mapNow->insertID(obj);  
	           
    msg_active(g_out_buf,sizeof(g_out_buf));
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(g_out_buf);
	// cout<<"mapId:"<<mapNow->getMapId()<<endl;
	// cout<<"g_out_buf:"<<g_out_buf<<endl;
	return true;
}
	
/*宠物退出场景*/
bool Pet::quit_scene(Hero *hero)
{
	Nbox *box;
	
	if(hero == NULL)
	{
		return false;
	}
	mapNow = hero->getMap();
	
	if(mapNow == NULL)
	{
		return false;
	} 
	              
   	msg_downline(g_out_buf,sizeof(g_out_buf));   
	box = mapNow->getBox();
	if(box == NULL)
	{
		return false;
	}
		
	StyObj obj(petdata->identity,PET_STYLE_TYPE);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(g_out_buf);
	
	mapNow->deleteID(obj);  
	
	return true;
}

int Pet::expDrugUsedNum(int _num)
{
	return petdata->expDrag[_num];
}

void Pet::setexpDrugUsedNum(int _index,int _num)
{
	petdata->expDrag[_index]=_num;
}

void Pet::msg_learnSkill_success(char *msg,int index,int i,int len,int skillNumber)
{	
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%d,%d,%d,%s,%d,%d,%d,%d",10,PET_SKILL_LEARN,petdata->identity,i,skillNumber,index,petdata->petskilldata[index].id,petdata->petskilldata[index].level,petdata->petskilldata[index].limit,petdata->petskilldata[index].needNumber,petdata->petskilldata[index].needCount);
}

void Pet::msg_skill_inform(char *msg,int index,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%d,%d",10,PET_SKILL_INFORM,petdata->identity,index,4);
	
	for (int i=0;i<4;i++)
	{
		if (petdata->petskilldata[i].level==0)
		{
				snprintf(msg+strlen(msg),len-strlen(msg),",%s%d%d,%d,%d,%d,%d","b_dj_115_10",i+1,petdata->type,-1,0,0,0);
		}
		else
		{
			snprintf(msg+strlen(msg),len-strlen(msg),",%s,%d,%d",petdata->petskilldata[i].id,petdata->petskilldata[i].level,petdata->petskilldata[i].limit,petdata->petskilldata[i].needNumber,petdata->petskilldata[i].needCount);
		}
	}	
}

void Pet::msg_skill_levelUp(char *msg,int index,int len)
{		
	if (msg==NULL)
	{
		return;
	}
	if (petdata->petskilldata[index-1].flag==0)
	{
		cout<<"jolly:According to the skill index can't find the skill 1562"<<endl;
		return;
	}
	else
	{
		snprintf(msg,len,"%d,%d,%s,%d,%s,%d,%d,%d",10,PET_SKILL,petdata->identity,index,petdata->petskilldata[index-1].id,petdata->petskilldata[index-1].level,petdata->expNow,\
		petdata->petskilldata[index-1].limit);
	}
}
	
/*获得宠物像素坐标*/
Point Pet::getPiexPt(void)
{
	return nowPix;
}

/*获得主人id*/
char* Pet::getMasterId(void)
{
	return masterId;
}
	
bool Pet::topLevel(void)
{
	if (petdata->expNow>=petdata->expNeed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Pet::getOutAtt(void)
{
	return (petdata->outAttackVal+petdata->succincted[2]);
}

int Pet::getInAtt(void)
{
	return (petdata->inAttackVal+petdata->succincted[3]);
}

int Pet::getHit(void)
{
	return (petdata->hit+petdata->succincted[0]);
}

int Pet::getCrit(void)
{
	return (petdata->crit+petdata->succincted[1]);
}

void Pet::startMoveTimer()
{
	// speed = NORMAL_PET_SPEED;
	// routeClear();
	// currPt = endPt = nowPix;
	// speedPt._x = 0; speedPt._y = 0;
	// ext_ev_timer_init(&moveTimer, pet_move_cb, 0.5, 0, this);
	// ev_timer_start(loops, &moveTimer);
}

void Pet::stopMoveTimer()
{
	// ev_timer_stop(loops, &moveTimer);
}

bool Pet::isInRank(Point pt)
{	
	nowLocation = getPiexPt();
	int deltaX = pt._x - nowLocation._x;
	int deltaY = pt._y - nowLocation._y;
	int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (petdata->range<distance)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//计算宠物战力
int Pet::countPower(void)
{
	petdata->power=0.5*getOutAtt()+0.5*getInAtt()+4*getHit()+4*getCrit();
	return petdata->power;
}

//判断是否可以进阶
bool Pet::judgeJingJie(void)
{
	if (petdata->needCount==0)
	{
		return false;
	}
	else if (petdata->curCount==petdata->needCount)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//宠物进阶相关
void Pet::increaseJingJie(int number)
{
	petdata->curCount+=number;
	if (petdata->curCount>=petdata->needCount)
	{
		petdata->curCount=petdata->needCount;
	}
}

void Pet::send_msg_jingJieNum(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return; 
	}
	
	snprintf(msg,len,"%d,%d,%s,%s,%d,%d,%d",10,PET_JINGJIE_NUM,petdata->identity,petdata->id,index,petdata->curCount,petdata->needCount);
}

void Pet::send_msg_jingJiePet(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return; 
	}
	
	snprintf(msg,len,"%d,%d,%s,%s,%d,%d,%d",10,PET_FEED_PET,petdata->identity,petdata->id,index,petdata->curCount,petdata->needCount);
}

void Pet::send_msg_fuchong(char *msg,int len,int index)
{
	if (msg==NULL)
	{
		return;
	}
	
	snprintf(msg,len,"%d,%d,%s,%s,%d,%s,%d,%d,%d",10,PET_FUCHONG,petdata->identity,petdata->id,index,petdata->nickName,petdata->level,countPower(),getEvolutionNumber());
}
	
//返回宠物的价值进阶点
int Pet::getEvolutionNumber(void)
{
	for (int i=0;i<10;i++)
	{
		if (petdata->power<pet_zhanli[i].max)
		{
			return pet_zhanli[i].number;
		}
	}
	return pet_zhanli[9].number;
}

//宠物进阶
bool Pet::petJingJie(void)
{	
	cout<<"petdata->nickName1:"<<petdata->nickName<<endl;
	if (petdata->curCount==petdata->needCount)
	{
		petdata->generation++;
		map<string,Pet_Config*>::iterator pet_it;		
		pet_it=id_to_pet.find(petdata->nextGenid);
		if (pet_it==id_to_pet.end())
		{
			cout<<"According to petId can't find the pet_config in pet.cpp"<<endl;
			petdata->generation--;
			return false;
		}
		else
		{	
			cout<<"petdata->nickName2:"<<petdata->nickName<<endl;
			Pet_Config *pet_config=pet_it->second;
			petdata->outAttackValRate=pet_config->getOutAttackValRate();
			petdata->inAttackValRate=pet_config->getInAttackValRate();
			petdata->hitRate=pet_config->getHitRate();
			petdata->critRate=pet_config->getCritRate();
			
			petdata->outAttackVal=pet_config->getOutAttackVal()+petdata->outAttackValRate*(petdata->level-1);
			petdata->inAttackVal=pet_config->getInAttackVal()+petdata->inAttackValRate*(petdata->level-1);
			petdata->hit=pet_config->getHit()+petdata->hitRate*(petdata->level-1);
			petdata->crit=pet_config->getCrit()+petdata->critRate*(petdata->level-1);
			
			strncpy(petdata->nextGenid,pet_config->getNextGenid(),sizeof(petdata->nextGenid));
			strncpy(petdata->nextid,pet_config->getNextid(),sizeof(petdata->nextid));
			strncpy(petdata->id,pet_config->getId(),sizeof(petdata->id));		
			strncpy(petdata->photoId,pet_config->getPhotoId(),sizeof(petdata->photoId));	
			petdata->needNumber=pet_config->getNeedNumber();
			petdata->needCount=pet_config->getNeedCount();
			cout<<"petdata->nickName2:"<<petdata->nickName<<endl;
			petdata->curCount=0;
			
			saveTotalProperty();
			cout<<"petdata->nickName3:"<<petdata->nickName<<endl;
		}	
	}
	else
	{
		return false;
	}
}

//试用多个进阶道具的时候判断需不需要那么多,返回使用的数量
int Pet::judgeUseNumber(int number)
{
	int gainNumber=jingjieEffect*number;
	if (petdata->curCount+gainNumber>petdata->needCount)
	{
		int temp=(petdata->needCount-petdata->curCount)%jingjieEffect;
		if (temp==0)
		{
			return (petdata->needCount-petdata->curCount)/jingjieEffect;
		}
		else
		{
			return (petdata->needCount-petdata->curCount)/jingjieEffect+1;
		}	
	}
	else
	{
		return number;
	}
}

//向九宫格发送信息
void Pet::sendMsgBox(char *msg)
{
	if (mapNow==NULL)
	{
		return;
	}
	
	StyObj obj(petdata->identity,PET_STYLE_TYPE);

	Nbox *box = mapNow->getBox();   	
	if(box == 0){
		return;
	}

	box->getStaInSrcVec(obj);

	box->sentBoxMsg(msg);
}

//判断宠物是否4个技能全部满级
bool Pet::isFourSkillMax(void)
{
	int flag=0;
	for (int i=0;i<4;i++)
	{
		if (petdata->petskilldata[i].level==20)
		{
			flag++;
		}
	}	
	if (flag==4)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Pet::pushOneRoutePt(int x, int y)
{
	if (routeArrUsedIndex >= (sizeof(routeArr) / 8) - 1)
	{
		return;
	}
	if(routeArrUsedIndex>511)
	{
		return;
	}
	routeArr[2 * routeArrUsedIndex] = x;
	routeArr[2 * routeArrUsedIndex + 1] = y;
	routeArrUsedIndex++;
	routeSize++;
}

bool Pet::popOneRoutePt(Point &pt)
{
	cout<<"routeIndex is "<<routeIndex<<" and routeArrUseIndex is "<<routeArrUsedIndex<<" routeSize is "<<routeSize<<endl;
	if(routeIndex>511)
	{
		return false;
	}
	if (routeIndex < routeArrUsedIndex)
	{
		pt._x = routeArr[2 * routeIndex];
		pt._y = routeArr[2 * routeIndex + 1];
		routeIndex++;
		routeSize--;
		return true;
	}
	else
	{
		return false;
	}
}

void Pet::routeClear()
{
	for (int i = 0; i < 1024; i++)
	{
		routeArr[i] = 0;
	}
	
	routeArrUsedIndex = 0;
	routeIndex = 0; 
	routeSize = 0;
}

int Pet::getRouteIndex()
{
	return routeIndex;
}

int Pet::getRouteSize()
{
	return routeSize;
}

void Pet::viewRouteMsg(char* routeMsg)
{
	int tempIndex = routeIndex;
	for (tempIndex; tempIndex < routeArrUsedIndex; tempIndex++)
	{
		if (tempIndex>511)
		{
			cout<<"viewRouteMsg error 11111"<<endl;
			return;
		}
		if (strlen(routeMsg)>4000)
		{
			cout<<"viewRouteMsg error 222222"<<endl;
			return;
		}
		sprintf(routeMsg + strlen(routeMsg), ",%d,%d", routeArr[2 * tempIndex], routeArr[2 * tempIndex + 1]);
	}
}
