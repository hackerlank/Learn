#ifndef PET_H
#define PET_H
#include <iostream>

#include <string>

#include"command_other_function_all_over.h"
#include"action.h"
#include"five_elements.h"
#include"hero.h"
#include"pet_config.h"
#include"map_inform.h"
#include"monsterBase.h"
#include"libev.h"
#include "pet_skill.h"
#include"timerContainer.h"
 
using namespace std;
class Bottle;
class Hero;
class MonsterBase;
class Map_Inform;
class PetSkill_Config;
class Pet
{
private:	
	Point nowLocation;								//宠物现在所在的逻辑坐标
	Point nowPix;									//宠物现在所在的像素坐标
		
	int succincting[4];								//正在洗练的属性
	
	int attackSeq;									//攻击序列  判断攻击为何种攻击
	Map_Inform *mapNow;								//宠物所在的地图实例
		
	int attackFlag;
	
	int fightTime;									//上次攻击的时间
	
	/*为方便攻击的计算整合属性,只为方便,不需要存入memcached start*/
	int outHarmTotal;
	int inHarmTotal;
	int outAttackValTotal;
	int inAttackValTotal;
	int hitTotal;
	int critTotal;
	/*为方便攻击的计算整合属性,只为方便,不需要存入memcached end*/
		
	
	int pet_boxIndex;
	
	char masterId[51];		//主人id	
	
	ev_timer moveTimer;
	
	int jingjieEffect;			//进阶道具进阶点;
	
	int routeIndex;
	int routeSize;
	int routeArrUsedIndex;
	int routeArr[1024];
public:	
	
	PetData *petdata;
	Point currPt, endPt, speedPt;		//本次路径搜寻起点与终点
	int speed;							//移动速度
	
	Pet(Pet_Config* pet_config, PetData *_petdata);		//构造函数	
	Pet(PetData* _petdata);
	~Pet(void);
	FiveElem *fiveElem;
	void setHero(Hero *_hero);
	int growNeedExp(void);							//升级所需要的所有经验
	int random(int begin,int end);					//随即begin到end的随机数
	void growExp(int exp,int heroLevel,Hero *hero);		//增加经验
	void levelUp(void);								//宠物升级  属性改变
	int getActive(void);							//获得宠物出战状态
	char* getIdentity(void);			
	char* getId(void);
	char* getNickName(void);
	void setNickName(char* _nickName);
	int getQuality(void);
	int getLevel(void);
	int getGeneration(void);
	int getType(void);
	void setActive(Hero *hero,int _active);					//使宠物出战
	char* getPhotoId(void);
	int getFlag(void);
	void setPet_boxIndex(int _pet_boxIndex);
	int getPet_boxIndex(void);
	
	void timerStop(void);
	void chooseFiveEle(int fd);
	void timerinit(void);
	void saveSuccinctInGameMoney(Hero *hero,int index);
	void saveSuccinctInGold(int index,Hero *hero,int number);
	void succinct(int index);
	int returnValue(int index);
	bool evolution(Hero *hero,int index);							//宠物获得进化点
	void evolutionSuccess(Hero *hero);								//宠物进化	
	bool canEvolutionRefresh(void);
	int getExpNow(void);		
	void setExpNow(int _expNow);				
	Point getLocation(Hero *hero);							//取得玩家周围的宠物应该在的坐标
	Map_Inform* getMapInform(void);
	void  setMapInform(Map_Inform* _map);
	Point getLogicNow(void);
	void setNowPix(Point _nowPix, int flag = 0);
	void setNowLocation(Point _nowLocation);
	int getFightTime(void);
	void setFightTime(int _fightTime);
	void saveTotalProperty(void);
	int getJingjieEffect(void);
	
	//宠物攻击系统 start
	
	/*获得普通攻击值*/
	int countAttPerGenMonster(MonsterBase *monster);
	/*计算暴击率*/
	int countCritPerMonster(MonsterBase *monster);
	/*计算命中率*/
	int countHitPerMonster(MonsterBase *monster);
	/*计算伤害值，技能也可以用*/
	int countAttValMonster(MonsterBase *monster,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	/*宠物攻击怪物判定*/
	void attactMonster(MonsterBase *monster,double skiHrtRatio,double _cdTime,char* skill_id);
	/*宠物群攻判定*/
	void attactMonsterArrange(MonsterBase *monster,double skiHrtRatio,double _cdTime,int index);
	/*发送攻击信息*/
	void sendAttactMsgMonster(MonsterBase *monster,int attack,char* skill_id);
	
	/*获得普通攻击值*/
	int countAttPerGenHero(Hero *hero);
	/*计算命中率*/
	int countHitPerHero(Hero *hero);
	/*计算暴击率*/
	int countCritPerHero(Hero *hero);
	/*计算伤害值，技能也可以用*/
	int countAttValHero(Hero *hero,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	/*宠物玩家怪物判定*/
	void attactHero(Hero *hero,double skiHrtRatio,double _cdTime,char* skill_id);
	/*宠物群攻判定*/
	void attactHeroArrange(Hero* hero,double skiHrtRatio,double _cdTime,int index);
	/*发送攻击信息*/
	void sendAttactMsgHero(Hero *hero,int attack,char* skill_id);
	
	//宠物攻击系统 end

	void ThkChaseMonster(MonsterBase *monster);
	
	void attack(void);
	void attackHeroOrMonster(char* identity,double ratio,char* skill_id);
	void ThkMove(Hero *_hero);
	int chase(char *msg_others,Point &wayPt);
	
	bool setLogicPt(list<Point> &wayPtList,int stopPos);
	
	void attackTarMonster(char* attackIdentity);
	void attackTarHero(char* attackIdentity);

	void pet_attack_monster(MonsterBase *monster);		//攻击怪物
	void pet_attack_hero(Hero *tarHero);				//攻击玩家
	void pet_attack_bottle(Bottle *bottInst);				//攻击瓶罐
	
	/*宠物技能系统 start*/
	//判断该索引的技能是否已经学习,没学返回true;已经学习了 返回false
	bool isSkillLearn(int index);
	/*宠物技能系统 end*/
	
	//获得宠物攻击范围
	int getAttackRange(void);
		
	void saveInstruct(void);
	
	// PetSkill* getPet_Skill(int index);
	
	bool canGoldSaveSuccinct(int index);
	
	void msg_levelUp(char* msg,int len,int _index);
	void msg_active(char* msg,int len);
	void msg_downline(char* msg,int len);
	void msg_learnSkill_success(char *msg,int index,int i,int len,int skillNumber);
	void msg_skill_inform(char* msg,int index,int len);
	void msg_skill_levelUp(char* msg,int index,int len);
	void msg_return_pet(char* msg,int _index,int len,int skillNumber,int flag);
	void msg_evolution_success(char *msg,int len,int index);
	void msg_evolution(char *msg,int len,int index);
	void send_pet_attr(char *msg,int len);	
	void send_msg_active(Hero *hero);
	void send_msg_downLine(Hero *hero);
	void send_msg_succinctInfo(char *msg,int len,int index);
	void send_msg_jingJie(char *msg,int len,int index);
	void send_msg_jingJieNum(char *msg,int len,int index);
	void send_msg_jingJiePet(char *msg,int len,int index);
	void send_msg_fuchong(char *msg,int len,int index);
	void send_msg_chuzhan(char *msg,int len,int index);
	void send_msg_zhaohui(char *msg,int len,int index);
	
	PetData getStruct(void);
	
	/*宠物场景跳转*/
	bool enter_scene(Hero *hero);
	
	/*宠物退出场景*/
	bool quit_scene(Hero *hero);	
	
	int expDrugUsedNum(int _num);
	void setexpDrugUsedNum(int _index,int _num);
		
	void savePetFiveEle(void);
	
	/*宠物技能相关 start*/
	void initSkill(int _index);
	void learnSkill(int _index);
	bool skillLevelUp(Hero *hero,int _index);												//宠物技能升级
	void increaseEffect(Hero *hero,int _index);										//技能属性增长
	int getAttRatio(int _index);											//获得攻击比率
	char* getSkillId(int _index);												//获得技能id
	char* getSkillIdentity(int _index);
	void saveInStruct(int _index);
	PetSkillData getStruct(int _index);
	int getSkillLevel(int _index);
	int getSkillFlag(int _index);
	int getMaxLimit(int _index);
	int getSkillNeedNumber(int _index);
	int getSkillNeedCount(int _index);
	int getSkillLimit(int _index);
	int judgeSkillLearn(int _index);
	/*宠物技能相关 end*/
	
	/*获得宠物像素坐标*/
	Point getPiexPt(void);
	
	/*获得主人id*/
	char* getMasterId(void);
	/*设置主人id*/
	void setMasterId(char *heroId);
	
	/*判断宠物经验是否已满*/
	bool topLevel(void);
	
	//计算宠物战力
	int getOutAtt(void);
	int getInAtt(void);
	int getHit(void);
	int getCrit(void);
	void stopMoveTimer();
	void startMoveTimer();
	
	//判断宠物攻击距离是否够
	bool isInRank(Point pt);
	
	//计算宠物战力
	int countPower(void);
	//判断是否可以进阶
	bool judgeJingJie(void);
	//宠物进阶相关
	void increaseJingJie(int number);	
	//返回宠物的价值进阶点
	int getEvolutionNumber(void);
	//宠物进阶
	bool petJingJie(void);
	//试用多个进阶道具的时候判断需不需要那么多,返回使用的数量
	int judgeUseNumber(int number);
	
	//向九宫格发送信息
	void sendMsgBox(char *msg);
	
	//判断宠物是否4个技能全部满级
	bool isFourSkillMax(void);
	
	
	void pushOneRoutePt(int x, int y);
	bool popOneRoutePt(Point &pt);
	void routeClear(); 
	int getRouteIndex();
	int getRouteSize();
	void viewRouteMsg(char* routeMsg);
	
	//宠物强制下线
	void petDownLine(void);
};
#endif
