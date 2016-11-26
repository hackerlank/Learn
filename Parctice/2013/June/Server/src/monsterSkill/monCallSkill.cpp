/************************************************************
	文件名：monCallSkill.cpp
	文件作用：定义MonCallSkill（召唤技能）
	作者：chenzhen
	创建日期：2013.05.13
************************************************************/
#include"monCallSkill.h"
MonCallSkill::MonCallSkill(char *_name,char *_id,int _rank,\
double _relPer,double _angVal,double _cdTime,double _playCd,\
double _hrtRatio,bool _lastSki,double _trigPer)\
:SkillBase(_name,_id,_rank,_relPer,_angVal,_cdTime,_playCd,_hrtRatio,\
_lastSki)
{
	trigPer = _trigPer;	
}

/*判断生命值是否已经达到额外触发条件*/
bool MonCallSkill::judgeLifePer()
{
	int lifeUpperVal;
	int lifeVal;
	lifeUpperVal = owner->getLifeUpperVal();
	lifeVal = owner->getLifeVal();
	
	/*判断血量是否满足触发条件*/
	if(1.0 * lifeVal/lifeUpperVal <= trigPer)
	{
		return true;
	}
	return false;
}

/*拷贝技能实例*/
SkillBase* MonCallSkill::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();	
	snprintf(instId + strlen(instId),sizeof(instId),"%s%s%s",monId,"_",id);	
	SkillBase *newSkillInst;
	newSkillInst = new MonCallSkill(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,trigPer);
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	((MonCallSkill *)newSkillInst)->getCallType();
	return newSkillInst;
}
	
/*使用回血技能技能*/
bool MonCallSkill::useSkill(vector<string> &herId,bool _station)
{
	/*为了定身时调用，不用检查条件*/
	if(_station || !isOverTme)
	{
		cout<<"the cd or the dingshen station:"<<id<<endl;
		return false;
	}
	
	/*血值触发，判断发生频率,cd时间判断*/
	if(!judgeLifePer() && !judgeRelPer())
	{
		cout<<"the relPercent is not meet:"<<id<<endl;
		return false;
	}
	
	UseSkillAsist(herId);
	
	initCdAndPlayTmer();
	
	return true;
}

/*析构函数*/
MonCallSkill::~MonCallSkill(void)
{
}

/*宿主死亡时调用*/
void MonCallSkill::ownerDie(void)
{
	SkillBase::ownerDie();
}

//解析召唤类型
void MonCallSkill::getCallType(void)
{
	if(strncmp(typeId,"callTypeT",9) == 0)
	{
		typeFlg = 1;
	}
	else if(strncmp(typeId,"callTypeM",9) == 0)
	{
		typeFlg = 2;
	}
	else if(strncmp(typeId,"callTypeTAM",11) == 0)
	{
		typeFlg = 3;
	}
}

//召唤
void MonCallSkill::UseSkillAsist(const vector<string> &herId)
{
	if(typeFlg == 1)
	{
		owner->callTrap(herId);
	}
	
	else if(typeFlg == 2)
	{
		owner->callMon();
	}
	
	else if(typeFlg == 3)
	{
		owner->callTrap(herId);
		owner->callMon();
	}
}
	
	
	

	
