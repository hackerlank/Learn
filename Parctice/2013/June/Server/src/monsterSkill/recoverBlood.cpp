/************************************************************
	文件名：recoverBlood.h
	文件作用：定义recoverBlood（Boss回血技能）类的属性和成员
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#include"recoverBlood.h"
#include"cpyAsist.h"
RecoverBlood::RecoverBlood(char *_name,char *_id,int _rank,\
double _relPer,double _angVal,double _cdTime,double _playCd,\
double _hrtRatio,bool _lastSki,double _trigPer,double _recoverPer)\
:SkillBase(_name,_id,_rank,_relPer,_angVal,_cdTime,_playCd,_hrtRatio,\
_lastSki)
{
	recoverPer = _recoverPer;
	trigPer = _trigPer;
	useSkillFlg = false;
}

/*判断生命值是否已经达到额外触发条件*/
bool RecoverBlood::judgeLifePer()
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

/*回血功能*/
bool RecoverBlood::gainBlood(int &bloodChg)
{	
	int lifeUpperVal;
	int lifeVal;	
	bloodChg = -1;
	/*为了定身时调用，不用检查条件*/
	if(!isOverTme || useSkillFlg)
	{
		return false;
	}
	
	/*血值触发，判断发生频率,cd时间判断*/
	if(!judgeLifePer() && !judgeRelPer() )
	{
		cout<<"the relPercent is not meet:"<<id<<endl;
		return false;
	}
	
	lifeUpperVal = owner->getLifeUpperVal();
	lifeVal = owner->getLifeVal();
	bloodChg = lifeUpperVal * recoverPer;
	lifeVal += bloodChg;
		
	/*如果血量超过上限*/
	if(lifeVal >= owner->getLifeUpperVal())
	{
		lifeVal = owner->getLifeUpperVal();
	}	
	
	/*回血*/
	owner->setLifeVal(lifeVal);
	
	
	/*启动技能冷却和播放时间定时器*/
	initCdAndPlayTmer();
	
	useSkillFlg = true;
	return true;
	
}

/*拷贝技能实例*/
SkillBase* RecoverBlood::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();	
	snprintf(instId + strlen(instId),sizeof(instId),"%s%s%s",monId,"_",id);	
	SkillBase *newSkillInst;
	newSkillInst = new RecoverBlood(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,trigPer,recoverPer);
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	return newSkillInst;
}

/*生成技能使用后所发消息*/
void RecoverBlood::formMsg(char *msg_others,int lengStr,int bloodChg,char *_heroId)
{
	if(msg_others == NULL || lengStr <= 0 || bloodChg <= 0)
	{
		cout<<"the skill msg is error:"<<id<<endl;
		return;
	}
	
#if	0
	cout<<"msg_others begin:"<<msg_others<<endl;
	cout<<"msg_others typeId:"<<typeId<<endl;
	cout<<"msg_others strlen(msg_others):"<<strlen(msg_others)<<endl;
	cout<<"msg_others lengStr:"<<lengStr<<endl;
	cout<<"msg_others owner->getIdentity():"<<owner->getIdentity()<<endl;
	cout<<"msg_others owner->getLifeUpperVal():"<<owner->getLifeUpperVal()<<endl;
	cout<<"msg_others owner->getLifeVal():"<<owner->getLifeVal()<<endl;
	cout<<"msg_others owner->getMagicVal():"<<owner->getMagicVal()<<endl;
	cout<<"msg_others owner->getMagicUpperVal():"<<owner->getMagicUpperVal()<<endl;
	cout<<"msg_others bloodChg:"<<bloodChg<<endl;
	cout<<"msg_others playCd:"<<playCd<<endl;
	
#endif	

	cout<<"recover blood begin:"<<typeId<<endl;
	
	snprintf(msg_others,lengStr,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d",\
	26,2,1,typeId,(int)playCd,owner->getIdentity(),owner->getLifeVal(),\
	owner->getLifeUpperVal(),owner->getMagicVal(),owner->getMagicUpperVal(),bloodChg);
	
	cout<<"recover sendMsg:"<<msg_others<<endl;
	
	cout<<"recover blood end:"<<typeId<<endl;
	
#if 0	
	snprintf(msg_others + strlen(msg_others),lengStr - strlen(msg_others),"%d%s%d%s%s%s%s%s%d",\
			MONSTER_SKILL_HEAD,",",MONSTER_SKILL_CHANGE_PRO,",",\
			owner->getIdentity(),",",typeId,",",owner->getLifeVal());	
#endif
}
	
/*使用回血技能技能*/
bool RecoverBlood::useSkill(vector<string> &herId,bool _station)
{
	char msg_recoverBlood[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	int bloodChg;
	/*判断回血技能是否触发*/
	if(gainBlood(bloodChg) && bloodChg > 0)
	{
		/*回血技能使用后，形成消息*/
		formMsg(msg_recoverBlood,sizeof(msg_recoverBlood),bloodChg);
		
		/*回血技能使用后，发送消息*/
		sendMsgNineBox(msg_recoverBlood);
		return true;
	}
	return false;
}

/*析构函数*/
RecoverBlood::~RecoverBlood(void)
{
}

/*宿主死亡时调用*/
void RecoverBlood::ownerDie(void)
{
	SkillBase::ownerDie();
	useSkillFlg = false;
}

	
