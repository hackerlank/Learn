#ifndef MONSTERBOSS_H
#define MONSTERBOSS_H
//#include"monsterBase.h"
#include"monsterBase.h"
#include"map_inform.h"
class Map_Inform;
class MonsterBoss : public MonsterBase
{
private:
	char *mapId;        //对应地图的id   Evan add
	char *nickName;     //对应怪物的昵称（一种类型的怪只有一个昵称）
	char *typeId;        //怪物类型
	char *identity;     //id
	int  lifeUpperVal;  //生命上限值
	int  lifeVal;        //当前生命值
	int  magicUpperVal;  //魔法上限值   Evan add
	int  magicVal;       //当前魔法值   Evan add
	Point pt;           //当前坐标点（地图像像素点）
	int attack;         //攻击力
	int eat;            //损耗
	int life_station;   //生死状态,用于判断何时该销毁对象	
	Point born_pt;         //出生点
	ev_timer *think_timer;
	int walk_ranage;      //走路范围
	int attack_range;
	Map_Inform *map_now;      //所在地图指针
	Astar *astar;

	char *photoId;	         //图片id
	Point logic_pt;          //当前逻辑点	
	vector<string> skill_list;   //技能列表
	list<HatVal> enmityValues;    //仇恨列表
	
	char* perHerId;           // 正在追击的目标id
	Point perLstPt;           //上一次的寻路终点(逻辑），减少重复寻路   
	list<Point>selfWay;         //自己巡逻路线
	Point goWaPt;              //第一次去追目标离开自己的巡逻点	
	list<Point>::iterator pt_it ;    //自己每次巡逻终点处
	
	int hatRge;               //仇恨范围
	
	string selfMsg;          //刷怪时的信息
	
	Point endFinPt;         //巡逻终点
	
	
	list<Point>runWay;     //逃跑路线
	Point mapOutPt;        //地图的出点，boss怪用于逃跑
	list<Point>::iterator runPt_it ;    //自己逃跑终点处
	int flgRun;            //逃跑标志
private:
	void getSlfRd(Point endpt);
	void sentMsg(set<string> &id_box,string &msg_perHero,string &msg_others);
	void schRge(void);
	Hero* getHero(char *heroId);
	void monfdWay(Point end);
	void getRdPt(string &msg_others);
	void attPerHero(string &msg_perHero,string &msg_others,Hero *perHero);
	
	void die(void);
	
	
	
public :
	MonsterBoss(char *_mapId,char *_typeId,char *_nickName,char *_identity, int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal, Point _pt, int _attack, int _eat,int _walk_ranage,int _attack_range,char *_photoId,Point logicPt,Map_Inform *_map);
	void initTimer(void);
	void attackHero(void);	
	~MonsterBoss(void);
	
	MonsterBase* copyMon(MonsterBase* newMon,Map_Inform *_mapNow);
	void setMap(Map_Inform* _map);
	
	virtual void response(void);  
	void thinkCallBack(struct ev_loop *loop,ev_timer *time,int revents);
	
	virtual char* getPhotoId(void);
	virtual void setPhotoId(char *_photoId);
	
	virtual int getAttackRange(void);
	virtual int getWalkRange(void);
	
	virtual Map_Inform* getMap(void);
	virtual char *getNickName(void);
	virtual char *getMapId(void);
//	virtual char *getTypeId(void);
	virtual char *getIdentity(void);	
	virtual void setLifeUpperVal(int _lifeUpperVal);
	virtual int getLifeUpperVal(void); //获得生命上限值 
	virtual void setMagicUpperVal(int _magicUpperVal); 
	virtual int getMagicUpperVal(void);   //获得魔法上限值	
	virtual void setLifeVal(int _lifeVal);   //修改当前生命值	
	virtual int getLifeVal(void);
	virtual void setMagicVal(int _magicVal); //修改当前魔法值 
	virtual int getMagicVal(void);
   	virtual Point getLocation(void);      //获得当前位置
   	virtual void setLocation(Point _pt);  //修改当前位置
	virtual void setAttack(int _attack);   //修改攻击力
	virtual int getAttack(void);           //获得攻击力	
	virtual int getEaten(void);            //获得当前损耗值
	virtual void setEaten(int _eat);       //修改损耗值	
	virtual int getLifeStation(void);    //获得生死状态
	virtual void setLifeStation(int _life);  //修改生死状态
	virtual Point getBornPoint(void);
	
	virtual void setLogicPt(Point _logice_pt);
	virtual Point getLogicPt(void);
	virtual void pushSkillId(char *skillId);
	virtual vector<string>& getSkillList(void);
	virtual void chageEny(char *_perHerId);
	virtual list<HatVal>& getEnmityValues(void) ;
	virtual void InpushEnmityValues(HatVal &hatva);
	virtual HatVal* getOneEnmityValues(void);
	virtual void dropOneEnmityValues(HatVal &hatva);
	
	virtual void brushMon(void);

	virtual void formBshMsg(void);
	virtual string& getBshMsg(void);
	
	
	
private:	
	void escape(void);
	void getRunWayPt(string &msg_others);
	
	
};
#endif


