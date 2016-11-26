#include"unEnemy.h"
#include"bossSkiThk.h"
#include"user_role_manage_assist.h"
#include"monsterBase.h"
#include"cpyAsist.h"
UnEnemy::UnEnemy(char *_name,char *_id,int _rank,double _relPer,\
double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
bool _lastSki,double _lastTime):SkillBase(_name,_id,_rank,_relPer,\
_angVal,_cdTime,_playCd,_hrtRatio,_lastSki)
{
	lastTime = _lastTime;
}

/*生成技能使用后所发消息,主要是无敌技能用*/
void UnEnemy::formMsg(char *msg_others,int lengStr,char *_heroId)
{
	if(msg_others == NULL || lengStr <= 0)
	{
		cout<<"the skill msg is error:"<<id<<endl;
	}
	snprintf(msg_others,lengStr,"%d,%d,%d,%s,%s,%d,%d,%f",\
			FIGHT_FRIST_HEAD,FIGHT_SECOND_BUFF,OPEN_BUFF,\
			typeId,_heroId,12,0,lastTime);
}
/*使用技能*/
bool UnEnemy::useSkill(vector<string> &herId,bool _station)
{
	char msg_others[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	/*为了定身时调用，不用检查条件*/
	if(!isOverTme || herId.empty())
	{
		cout<<"the cd or the herId is empty:"<<id<<endl;
		return false;
	}
	
	/*判断发生频率,cd时间判断*/
	if(!judgeRelPer())
	{
		cout<<"the  relPercent is not meet:"<<id<<endl;
		return false;
	}
		
	/*无敌技能消息生成*/
	formMsg(msg_others,sizeof(msg_others));
		
	/*消息群发*/
	sendMsgNineBox(msg_others);

	/*设置无敌状态值*/
	owner->setUnEnemySta(true);
	
	/*启动技能冷却和播放时间定时器*/
	initCdAndPlayTmer();
	
	/*先暂停，后重启，覆盖*/
	stopThk();
	
	initTimer();
	
	return true;	
}

/*计时器初始化函数*/
void UnEnemy::initTimer(void)
{	
	ext_ev_timer_init(&think_timer,monSkiUnEnemyCalBack,lastTime,0,this);
	ev_timer_start(loops,&think_timer);		
}

/*计时器暂停函数*/
void UnEnemy::stopThk(void)
{
	ev_timer_stop(loops,&think_timer);
}

/*无敌持续时间处理*/
void UnEnemy::recoverUnEnemySki(void)
{
	if(owner == NULL || !owner->getUnEnemySta())
	{
		return;
	}	
	
	owner->setUnEnemySta(false);		
}

/*拷贝技能实例*/
SkillBase* UnEnemy::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	SkillBase *newSkillInst;
	if(_owner == NULL)
	{
		return NULL;
	}
	monId = _owner->getIdentity();
	snprintf(instId,sizeof(instId),"%s%s%s",monId,"_",id);	
	
	newSkillInst = new UnEnemy(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki,lastTime);
	
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	return newSkillInst;
}

/*宿主死亡时调用*/
void UnEnemy::ownerDie(void)
{
	stopThk();
	
	if(owner != NULL)
	{
		owner->setUnEnemySta(false);
	}
	SkillBase::ownerDie();
}

UnEnemy::~UnEnemy(void)
{
	stopThk();
}
