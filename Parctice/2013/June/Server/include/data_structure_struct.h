/*
		文件类型：头文件
		文件名称：data_structure_struct.h
		文件作用：其中包含一些自定义数据类型
*/

#ifndef DATA_STRUCTURE_STRUCT
#define DATA_STRUCTURE_STRUCT
#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#include<vector>
#include<set>
#include"wholeDefine.h"
#include"other_define_data.h"
using namespace std;
   
typedef struct Point       //结构体，包含横纵坐标
{
	int _x;
	int _y;
	Point(int x=0,int y=0)
	{
		_x=x;
		_y=y;
	}
	bool operator < (const Point &newPoint) const
	{
		return (_x < newPoint._x) || ((_x == newPoint._x) && (_y < newPoint._y));
	}
	bool operator == (const Point &newPoint) const
	{
		return (_x == newPoint._x && _y == newPoint._y);
	}
}Point;         
typedef struct HatVal   //仇恨值结构
{
	char id[SHOR_MID_VALUE_LENGTH + 1];
	double value;
	HatVal(char *_id,double _values)
	{
		memset(id,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(id,_id,strlen(_id));
		value = _values;
	} 
	
	HatVal(const HatVal& hatVal)
	{
		memset(id,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(id,hatVal.id,strlen(hatVal.id));
		value = hatVal.value;
	} 
	HatVal& operator= (const HatVal& hatVal)
	{
		memset(id,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(id,hatVal.id,strlen(hatVal.id));
		value = hatVal.value;
		return *this;
	} 
	
		
}HatVal;


typedef struct ManMonSkiTme          //怪物buffer技能结构
{
	vector< set<string> > herIdVec;
	ManMonSkiTme(void)
	{
		herIdVec.clear();
	}   
	void init(void)
	{
		herIdVec.clear();
		{
			std::vector< set<string> > tmp;   
			herIdVec.swap(tmp);
		}
	}
	void input(set<string> &herId)
	{
		herIdVec.push_back(herId);
	}
	void output(set<string> &herId)
	{
		if(herIdVec.empty())
		{
			return;
		}
		herId = herIdVec.back();
		herIdVec.pop_back();
	}	
	bool isEmpty()
	{
		if(herIdVec.empty())
		{
			return true;
		}
		return false;
	}
}ManMonSkiTme;

typedef struct CtrlHerId   //怪物buffer技能结构
{
	char id[SHOR_MID_VALUE_LENGTH + 1];
	clock_t startTme;
	CtrlHerId(char *_id)
	{
		memset(id,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(id,_id,strlen(_id));
		startTme = clock();
	}   
}CtrlHerId;

struct FunCmp
{
	bool operator()(const CtrlHerId &her1,const CtrlHerId &her2) const
	{
		if(strcmp(her1.id,her2.id) != 0)
		{
			return true;
		}
		return false;
	}
};


typedef struct{
	char goodsid[40];
	int num;
	int type;
}Trade_Goods;

typedef struct CpyTyCtn
{
	char id[SHOR_MID_VALUE_LENGTH + 1];
	int sum;      
	CpyTyCtn(char *_id)
	{
		memset(id,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(id,_id,strlen(_id));
		sum = 0;
	}
}CpyTyCtn;		
typedef void (*FUN)(char *buffer);        //指向一类的函数的指针

/* 任务完成条件类型  --added by bison */
typedef struct need_S {
	int type;        //需求类型 决定任务类型
	char id[51];       //完成任务需求的东西
	int num;         //需求的数量
	
	need_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
	}
}need_t;

/* 任务奖励类型 --added by bison */
typedef struct give_S {
	int type;        //奖励类型
	char id[51];       //奖励物品id
	int num;         //奖励数量
	
	give_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
	}
}give_t;   

/* 任务触发类型 */
//need give touch 目前的情况可以合成一个，但是暂时不合并，以备以后需要扩展
typedef struct touch_S {
	int type;				//触发类型 暂时没考虑到其用途，方便以后扩展
	char pretask[51];			//前置任务id
	int num;				//待以后扩展使用
	touch_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(pretask, _id, strlen(_id) + 1);
		num = _num;
	}
}touch_t;

typedef struct WearEquip_T{
	char goodsid[40];
	char typeId[15];
	int flag;			//该位置是否有装备,0为没有,1为有
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator = (const WearEquip_T &data)
	{
		memcpy(goodsid,data.goodsid,sizeof(goodsid));
		flag=data.flag;
		memcpy(typeId,data.typeId,sizeof(typeId));
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
	WearEquip_T()
	{
		memcpy(goodsid,"0",sizeof(goodsid));
		memcpy(typeId,"0",sizeof(typeId));
		flag=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void initEquip(void)
	{
		// cout<<"111111111111111111111111111111"<<endl;
		memcpy(goodsid,"0",sizeof(goodsid));
		memcpy(typeId,"0",sizeof(typeId));
		flag=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
}WearEquipData;
//接受任务时可能会给道具或变身
typedef struct recv_S {
	int type;				//接受类型
	char id[51];				//道具id
	int num;				//道具数量
	recv_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
	}
}recv_t;

/* 任务状态信息 -- added by bison */
typedef struct taskStatus_S {
	int type;       //任务类型
	char id[51];      //任务需要物品的id
	int num;        //任务需求物品数量
	int value;      //任务需求物品当前数量
	
	taskStatus_S(int _type, char* _id, int _num, int _value)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
		value = _value;
	}
	
	//使用need构造status
	taskStatus_S(need_t *need, int _value)
	{
		type = need->type;
		strncpy(id, need->id, strlen(need->id) + 1);
		num = need->num;
		value = _value;
	}
}taskStatus_T;

//副本难度等级值
typedef enum{
	NORMAL_LEVEL,
	MIDDLE_LEVEL,
	HARD_LEVEL
}ECTYPE_CLASS_T;

typedef struct jumpId_2_infor{
string jumpId;     			//当前跳转点ID；
string mapId;        		//目标地图的mapID;
Point  nowPt;        	 	//当前地图的pt；
Point  targetPt;     		//标地图的pt;
int	   levelLowerLimit;		//跳转点等级下限制；
int    levelUpperLimit;		//地图跳转点等级上限值；
int	   campEntFlag;			//不加正营是否可跳转标记值；
jumpId_2_infor(string _jumpId,string _mapId,Point _nowPt,Point _targetPt,int _levelLowerLimit,int _levelUpperLimit,int _campEntFlag)
 {
    jumpId=_jumpId;
    mapId=_mapId;
    nowPt=_nowPt;	
	targetPt=_targetPt;
	levelLowerLimit=_levelLowerLimit;
	levelUpperLimit=_levelUpperLimit;
	campEntFlag=_campEntFlag;
  }
}jumpId_infor;

typedef struct{
	long boundGold,gold,boundGameMoney,gameMoney,accGold;
	bool moneyFlag,goldFlag;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
}moneyData;


typedef struct EquipmentBase_T{
	int life,magic,inattack,outattack,indefence,outdefence,crit,hit,dodge,tenacity;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	EquipmentBase_T()
	{
		life=0;
		magic=0;
		inattack=0;
		outattack=0;
		indefence=0;
		outdefence=0;
		crit=0;
		hit=0;
		dodge=0;
		tenacity=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator =(const EquipmentBase_T &data)
	{
		life=data.life;
		magic=data.magic;
		inattack=data.inattack;
		outattack=data.outattack;
		indefence=data.indefence;
		outdefence=data.outdefence;
		crit=data.crit;
		hit=data.hit;
		dodge=data.dodge;
		tenacity=data.tenacity;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}EquipmentBase;

typedef struct EquipmentKaiRen_T{
	int crit,hit,dodge,tenacity,kaiRenLevel,kaiRenCost;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	EquipmentKaiRen_T()
	{
		crit=0;
		hit=0;
		dodge=0;
		tenacity=0;
		kaiRenLevel=0;
		kaiRenCost=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator =(const EquipmentKaiRen_T &data)
	{
		crit=data.crit;
		hit=data.hit;
		dodge=data.dodge;
		tenacity=data.tenacity;
		kaiRenLevel=data.kaiRenLevel;
		kaiRenCost=data.kaiRenCost;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}EquipmentKaiRen;

typedef struct EquipmentRongLian_T{
	int life,magic,inattack,outattack,indefence,outdefence,rongLianLevel,rongLianLucky,rongLianCost;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	EquipmentRongLian_T()
	{
		life=0;
		magic=0;
		inattack=0;
		outattack=0;
		indefence=0;
		outdefence=0;
		rongLianLevel=0;
		rongLianLucky=0;
		rongLianCost=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator =(const EquipmentRongLian_T &data)
	{
		life=data.life;
		magic=data.magic;
		inattack=data.inattack;
		outattack=data.outattack;
		indefence=data.indefence;
		outdefence=data.outdefence;
		rongLianLevel=data.rongLianLevel;
		rongLianLucky=data.rongLianLucky;
		rongLianCost=data.rongLianCost;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}EquipmentRongLian;

typedef struct EqupmentDiamon_T{
	int life,magic,inattack,outattack,indefence,outdefence,crit,hit,dodge,tenacity;	
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	EqupmentDiamon_T()
	{
		life=0;
		magic=0;
		inattack=0;
		outattack=0;
		indefence=0;
		outdefence=0;
		crit=0;
		hit=0;
		dodge=0;
		tenacity=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator =(const EqupmentDiamon_T &data)
	{
		life=data.life;
		magic=data.magic;
		inattack=data.inattack;
		outattack=data.outattack;
		indefence=data.indefence;
		outdefence=data.outdefence;
		crit=data.crit;
		hit=data.hit;
		dodge=data.dodge;
		tenacity=data.tenacity;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}EqupmentDiamon;

typedef struct EquipmentData_T{
	char entityid[40],id[10],name[40],party[10],suit_id[10],xq_bs[100],photoId[10];
	int grade,rank,type,suit_type,durability,durabilityLimit,price,gold,goldBound,priceBound,sellPrice,bound,holeNumber,isbag,time,beginTime,move,fourDiamonNumber,attrNumber,isWear;
	EquipmentBase equipmentBase;
	EquipmentKaiRen equipmentKaiRen;
	EquipmentRongLian equipmentRongLian;
	EqupmentDiamon equpmentDiamon;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const EquipmentData_T &data)
	{
		memcpy(entityid,data.entityid,sizeof(entityid));
		memcpy(id,data.id,sizeof(id));
		memcpy(name,data.name,sizeof(name));
		memcpy(party,data.party,sizeof(party));
		memcpy(suit_id,data.suit_id,sizeof(suit_id));
		memcpy(xq_bs,data.xq_bs,sizeof(xq_bs));
		memcpy(photoId,data.photoId,sizeof(photoId));
		grade=data.grade;
		rank=data.rank;
		type=data.type;
		suit_type=data.suit_type;
		durability=data.durability;
		durabilityLimit=data.durabilityLimit;
		price=data.price;
		gold=data.gold;
		goldBound=data.goldBound;
		priceBound=data.priceBound;
		sellPrice=data.sellPrice;
		bound=data.bound;
		holeNumber=data.holeNumber;
		isbag=data.isbag;
		time=data.time;
		beginTime=data.beginTime;	
		move=data.move;
		fourDiamonNumber=data.fourDiamonNumber;
		attrNumber=data.attrNumber;
		isWear=data.isWear;
		
		equipmentBase=data.equipmentBase;
		equipmentKaiRen=data.equipmentKaiRen;
		equipmentRongLian=data.equipmentRongLian;
		equpmentDiamon=data.equpmentDiamon;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}EquipmentData;

typedef struct BagGoodsData_T{
	char goodsid[40];
	int num;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	BagGoodsData_T(void)
	{
		strncpy(goodsid,"0",sizeof(goodsid));
		num=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value6));
		strncpy(value8,"0",sizeof(value6));
	}
	void operator =(const BagGoodsData_T &data)
	{
		memcpy(goodsid,data.goodsid,sizeof(goodsid));
		num=data.num;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}BagGoodsData;

typedef struct BagData_T{
	int bagnum,expandNeedGold;
	BagGoodsData baggoodsdata[216];
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const BagData_T &data)
	{
		bagnum=data.bagnum;
		expandNeedGold=data.expandNeedGold;
		memcpy(baggoodsdata,data.baggoodsdata,sizeof(baggoodsdata));
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}BagData;


/*刷怪数量分布*/
typedef struct MonGroNum
{
	int sum;                   //怪物总数
	int generNum;        //普通怪数量
	int eliteNum;        //精英怪数量
	int activeNum;       //主动怪数量
	int passNum;         //被动怪数量
	int patNum;          //巡逻怪数量
	int bossNum;              //BOSS数量
	MonGroNum(int _sum,int _generNum,int _eliteNum,int _bossNum,\
			  int _passNum = 0,int _activeNum = 0,int _patNum = 0)
	{
		sum = _sum;
		generNum = _generNum;
		eliteNum = _eliteNum;
		activeNum = _activeNum;
		passNum = _passNum;
		patNum = _patNum;
		bossNum = _bossNum;
	}
	MonGroNum(void)
	{
		sum = 0;
		generNum = 0;
		eliteNum = 0;
		activeNum = 0;
		passNum = 0;
		patNum = 0;
		bossNum = 0;
	}
	void initMonGroNum(void)
	{
		sum = 0;
		generNum = 0;
		eliteNum = 0;
		activeNum = 0;
		passNum = 0;
		patNum = 0;
		bossNum = 0;
	}
	
}MonGroNum;	

typedef struct Goods_Inform_S{									//物品信息结构体
	char goodsid[40];												//物品id
	int number;			
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];	
	Goods_Inform_S(void)
	{
		strncpy(goodsid,"0",sizeof(goodsid));
		number=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator =(const Goods_Inform_S &data)
	{
		memcpy(goodsid,data.goodsid,sizeof(goodsid));
		number=data.number;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}Goods_Inform;	


typedef struct WarehouseData_T{
	Goods_Inform goods_inform[288];
	int gridNum,expandNeedGold;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const WarehouseData_T &data)
	{
		memcpy(goods_inform,data.goods_inform,sizeof(goods_inform));
		gridNum=data.gridNum;
		expandNeedGold=data.expandNeedGold;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}WarehouseData;


typedef struct PetSkillData_T{
	char identity[40],id[20];
	int flag,effect,increaseRatio,limit,addLimit,maxLimit,needNumber,level,needCount,addNeedCount,range;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	PetSkillData_T(void)
	{
		strncpy(identity,"0",sizeof(identity));
		strncpy(id,"0",sizeof(id));
		flag=0;
		effect=0;
		increaseRatio=0;
		limit=0;
		addLimit=0;
		maxLimit=0;
		needNumber=0;
		needCount=0;
		addNeedCount=0;
		range=0;
		level=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	
	void operator = (const PetSkillData_T &data)
	{
		strncpy(identity,data.identity,sizeof(identity));
		strncpy(id,data.id,sizeof(id));
		flag=data.flag;
		effect=data.effect;
		increaseRatio=data.increaseRatio;
		limit=data.limit;
		addLimit=data.addLimit;
		maxLimit=data.maxLimit;
		needNumber=data.needNumber;
		level=data.level;
		needCount=data.needCount;
		addNeedCount=data.addNeedCount;
		range=data.range;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}PetSkillData;

typedef struct FiveElementData_S
{
	int level;
	int element;
	int expNow;
	int expForNext;
}FiveElementData;


typedef struct PetData_T{
	char identity[40],id[20],nickName[40],photoId[20];
	int level,needNumber,needCount,expTimes,inHarmRate,outAttackVal,outAttackValRate,inAttackVal,inAttackValRate,hit,hitRate,crit,critRate,curNumber,curCount,power,hungryValDecreaseRate,happyVal,happyValIncrease,happyValDecrease,happyValDecreaseRate,type,range,generation,expNow,expNeed,expAgo,active,sex,quality,maxHappy,maxHungry,nowEvolution,maxEvolution,succincted[6],expDrag[3],flag,normalDistance;
	PetSkillData petskilldata[14];
	char normalSkill[50];				//宠物普通攻击 技能id
	char nextid[50];
	char nextGenid[50];
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	// void operator =(const PetData_T &data)
	// {
		// strncpy(identity, data.identity, sizeof(identity));
		// strncpy(id, data.id, sizeof(id));
		// strncpy(nickName, data.nickName, sizeof(nickName));
		// strncpy(photoId, data.photoId, sizeof(photoId));
		// level=data.level;
		// needNumber=data.needNumber;
		// needCount=data.needCount;
		// expTimes=data.expTimes;
		// inHarmRate=data.inHarmRate;
		// outAttackVal=data.outAttackVal;
		// outAttackValRate=data.outAttackValRate;
		// inAttackVal=data.inAttackVal;
		// inAttackValRate=data.inAttackValRate;
		// hit=data.hit;
		// hitRate=data.hitRate;
		// crit=data.crit;
		// critRate=data.critRate;
		// curNumber=data.curNumber;
		// curCount=data.curCount;
		// power=data.power;
		// hungryValDecreaseRate=data.hungryValDecreaseRate;
		// happyVal=data.happyVal;
		// happyValIncrease=data.happyValIncrease;
		// happyValDecrease=data.happyValDecrease;
		// happyValDecreaseRate=data.happyValDecreaseRate;
		// type=data.type;
		// range=data.range;
		// generation=data.generation;
		// expNow=data.expNow;
		// expNeed=data.expNeed;
		// expAgo=data.expAgo;
		// active=data.active;
		// sex=data.sex;
		// quality=data.quality;
		// maxHappy=data.maxHappy;
		// maxHungry=data.maxHungry;
		// nowEvolution=data.nowEvolution;
		// maxEvolution=data.maxEvolution;	
		// memcpy(succincted, data.succincted, sizeof(succincted));
		// memcpy(expDrag, data.expDrag, sizeof(expDrag));
		// flag=data.flag;
		// normalDistance=data.normalDistance;
		// memcpy(petskilldata, data.petskilldata, sizeof(petskilldata));	
		// strncpy(normalSkill,data.normalSkill,sizeof(normalSkill));
		// strncpy(nextid,data.nextid,sizeof(nextid));
		// strncpy(nextGenid,data.nextGenid,sizeof(nextGenid));
		
		// value1=data.value1;
		// value2=data.value2;
		// value3=data.value3;
		// value4=data.value4;
		// value5=data.value5;
		// memcpy(value6,data.value6,sizeof(value6));
		// memcpy(value7,data.value7,sizeof(value7));
		// memcpy(value8,data.value8,sizeof(value8));
	// }	
}PetData;

typedef struct Pet_BoxDataNew_T{
	PetData petdata[20];
	int number,maxNumber,index;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const Pet_BoxDataNew_T &data)
	{
		memcpy(petdata, data.petdata, sizeof(petdata));
		number=data.number;
		maxNumber=data.maxNumber;;
		index=data.index;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}Pet_BoxDataNew;

typedef struct pitchTerm_data{
	Point pt1;//对角点
	Point pt2;//对角点
}PitchTerm;

//有关角色好友基本信息；
typedef struct FriendInfo_S{
	char heroName[HERO_MAME_LEN-4];	//好友名字；
	int friend_grd_limit;			//好友度增加限制，每天只能增加的次数(交易)，送鲜花无限次增长；
	char party[PARTY_LEN];			//好友门派；
	int grad;						//好友等级；	
	int friendLevel;				//好友度；
	size_t vipLevel;                   //vip等级
	int campFlg;                       //阵营标志
private:
	
	Point locationPt;                //坐标
	
	int values1;                    //预留
	int values2;
	int values3;
	int values4;
	int values5;
	char mapId[50];                //地图id

public:
	FriendInfo_S(char* _heroName=NULL,char*  _party=NULL,int _grad=0,int _friendLevel=0,size_t _vipLevel = 0,int _campFlg = -1,char _friend_grd_limit=5)
	{
		init();
		
		if(_heroName)
		{
			memcpy(heroName,_heroName,strlen(_heroName));
			heroName[strlen(_heroName)]='\0';
		}else{
			memset(heroName,'\0',sizeof(heroName));
		}
		
		if(_party)
		{
			memcpy(party,_party,strlen(_party));
			party[strlen(_party)]='\0';
		}else{
			memset(party,'\0',sizeof(party));
		}
		
		if(_grad <= 0)
			grad=1;
		else	
			grad=_grad;
		
		if(_friendLevel <= 0)
			friendLevel=1;
		else
			friendLevel=_friendLevel;
			
		friend_grd_limit=_friend_grd_limit;
		
		vipLevel = _vipLevel;
		
		campFlg = _campFlg;
	}

private:
	void init()
	{
		values1 = 0;
		values2 = 0;
		values3 = 0;
		values4 = 0;
		values5 = 0;
		
		locationPt._x = 0;
		locationPt._y = 0;
		memset(mapId,'\0',sizeof(mapId));
	}
		
}FriendInfo_T;

typedef struct MemFriendInfo_S{
	char myFriendID[MAX_FRIEND_COUNTS][HERO_ID_LEN];
	FriendInfo_T myFriendInfo[MAX_FRIEND_COUNTS];
	char myBlackListID[MAX_FRIEND_COUNTS][HERO_ID_LEN];	
	FriendInfo_T myBlackListInfo[MAX_FRIEND_COUNTS];	
	
	MemFriendInfo_S()
	{
		for(int row = 0;row < MAX_FRIEND_COUNTS;row++)
		{
			memset(myFriendID[0],'\0',sizeof(myFriendID[0]));
			memset(myBlackListID[0],'\0',sizeof(myBlackListID[0]));	
		}
	}
}MemFriend_T;

typedef struct MapType_S{
	string guidWarMapId;
	string campWarMapId;
	string campSenceMapId;
	string mainCityMapId;
	string mainCityMapId2;		//南京主城；
	string towerDefMapId;		//塔防；
	string campResWarMapId;
}MapType_T;


typedef struct MysteriousGoodsData_T{
	char goodsid[15];
	int money,flag;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const MysteriousGoodsData_T &data)
	{
		memcpy(goodsid,data.goodsid,sizeof(goodsid));		
		money=data.money;		
		flag=data.flag;
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
	MysteriousGoodsData_T()
	{
		strncpy(goodsid,"0",sizeof(goodsid));
		money=0;
		flag=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
}MysteriousGoodsData;

typedef struct MysteriousBussinessData_T {
	MysteriousGoodsData mysteriousgoodsdata[10];
	int beginTime,refreshMoney,flag;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator =(const MysteriousBussinessData_T &data)
	{
		memcpy(mysteriousgoodsdata,data.mysteriousgoodsdata,sizeof(mysteriousgoodsdata));			
		beginTime=data.beginTime;	
		refreshMoney=data.refreshMoney;	
		flag=data.flag;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}MysteriousBussinessData;

typedef struct MidasTouchReward_T{
	int money[6];
	int popularity[6];
	int percent;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
}MidasTouchReward;

typedef struct MidasTouchNumber_T{
	MidasTouchReward midasTouch[6];
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
}MidasTouchNumber;

typedef struct MidasTouchData_T{
	int value[6];
	int refreshNum;
	int luckyRefreshNum;
	int luckyRefreshMoney;
	int money;
	int popularity;
	int flag;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	MidasTouchData_T()
	{
		for (int i=0;i<6;i++)
		{
			value[i]=0;
		}
		refreshNum=10;
		luckyRefreshNum=10;
		luckyRefreshMoney=5;
		money=0;
		popularity=0;
		flag=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const MidasTouchData_T &data)
	{
		memcpy(value,data.value,sizeof(value));
		refreshNum=data.refreshNum;
		luckyRefreshNum=data.luckyRefreshNum;
		luckyRefreshMoney=data.luckyRefreshMoney;
		money=data.money;
		popularity=data.popularity;
		flag=data.flag;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}MidasTouchData;

typedef struct OnlineRewarData_T{
	char stage[20];		//现在领取的阶段
	int totalTime;		//总时间
	int startTime;			//下线前已经过的时间
	int rewardMoney;		//奖励金币
	int rewardGold;			//奖励元宝
	char goodsid[20];		//奖励道具
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	OnlineRewarData_T()
	{
		strncpy(stage,"p11",sizeof(stage));
		totalTime=0;
		startTime=0;
		rewardMoney=0;
		rewardGold=0;
		memset(goodsid,'\0',sizeof(goodsid));
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const OnlineRewarData_T &data)
	{
		memcpy(goodsid,data.goodsid,sizeof(goodsid));
		memcpy(stage,data.stage,sizeof(stage));
		totalTime=data.totalTime;
		startTime=data.startTime;
		rewardMoney=data.rewardMoney;
		rewardGold=data.rewardGold;
		
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}OnlineRewarData;


typedef struct AvtiveCode
{
	string activeCodeId;
	string goodsId;
	string userName;
	bool isUse;
	AvtiveCode(char *_activeCodeId,char *_goodsId = NULL,char *_userNme = NULL)
	{
		activeCodeId = _activeCodeId;
		if(_goodsId)
		{
			goodsId = _goodsId;
		}
		if(_userNme)
		{
			userName = _userNme;
		}
		isUse = false; 
	}
	
	bool operator < (const AvtiveCode &activeCode) const
	{
		if(activeCodeId.compare(activeCode.activeCodeId) == -1)
		{
			return true;
		}
		return false;
	}
	
	bool operator == (const AvtiveCode &activeCode) const
	{
		if(activeCodeId.compare(activeCode.activeCodeId) == 0)
		{
			return true;
		}
		return false;
	}
	bool getIsUse(void)
	{
		return isUse;
	}
	
	void setIsUse(bool _isUse)
	{
		isUse = _isUse;
	}
	
	bool useCodeId(char *_userNme)
	{
		if(_userNme == NULL)
		{
			return false;
		}
		
		if(userName.empty())
		{
			userName = _userNme;
			return true;
		}
		if(strcmp(userName.c_str(),_userNme) == 0)
		{
			return true;
		}
		return false;
	}
	
		
		
		
}AvtiveCode;

typedef struct RewardFactor_T{
	int dazuoFactor;
	int lixianFactor;
	int lianxuFactor;
}RewardFactor;

typedef struct FestivalGoods_T{
	int num;		//匹配的数量
	char goods[6][20];
	char rewardGoods[20];
}FestivalGoods;
	

typedef struct HappyMapRewardItem_S
{
	int ExpFactor[11];
	int MonFactor[11];
} HappyMapRewardItem_T;

typedef struct HappyMapReward_S
{
	HappyMapRewardItem_T rewardLevel[200];
} HappyMapReward_T;

typedef struct TimeActiveDouble_T
{
	int beginYear;
	int beginMouth;
	int beginDay;
	int beginHour;
	int endYear;
	int endMouth;
	int endDay;
	int endHour;
}TimeActiveDouble;

typedef struct ActiveDouble_T
{
	TimeActiveDouble shengyan;	
	TimeActiveDouble daguai;	
	TimeActiveDouble yabiao;	
}ActiveDouble;

typedef struct RideSkill_Config_T{
	char id[20];
	int value;
	int level;
	int levelMax;	
	RideSkill_Config_T(void)
	{
		memset(id,0,sizeof(id));
		strncpy(id,"0",sizeof(id));
		value=0;
		level=0;
		levelMax=0;
	}
	void operator = (const RideSkill_Config_T &data)
	{
		strncpy(id,data.id,sizeof(id));
		value=data.value;
		level=data.level;
		levelMax=data.levelMax;
	}
}RideSkill_Config;

typedef struct RideSkill_T{
	char id[20];
	int flag;			//判断此技能是否学习 未学习为0,已学习为1
	int value;
	int level;
	int levelMax;	
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	RideSkill_T(void)
	{
		strncpy(id,"0",sizeof(id));
		flag=0;
		value=0;
		level=0;
		levelMax=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const RideSkill_T &data)
	{
		strncpy(id,data.id,sizeof(id));
		flag=data.flag;
		value=data.value;
		level=data.level;
		levelMax=data.levelMax;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}RideSkill;

typedef struct Ride_Final_Skill_T{
	int stage;
	int gridNumber;
	int flag[3];
	int value[3];
	int color[3];
	int number;
	int numberMax;
	int refreshNumber;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	Ride_Final_Skill_T(void)
	{
		stage=-1;
		gridNumber=1;
		flag[0]=0;
		flag[1]=0;
		flag[2]=0;
		value[0]=0;
		value[1]=0;
		value[2]=0;
		color[0]=0;
		color[1]=0;
		color[2]=0;
		number=0;
		numberMax=0;
		refreshNumber=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const Ride_Final_Skill_T &data)
	{
		memcpy(flag,data.flag,sizeof(flag));
		memcpy(value,data.value,sizeof(value));
		memcpy(color,data.color,sizeof(color));
		gridNumber=data.gridNumber;
		stage=data.stage;
		number=data.number;
		numberMax=data.numberMax;
		refreshNumber=data.refreshNumber;
		
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}Ride_Final_Skill;

typedef struct RideData_T{
	char identity[40],id[20],photoId[20],nickName[50];
	int level,exptimes,hp,mp,outAttVal,inAttVal,outDefVal,inDefVal,hit,crit,dodge,tenacity,move,expMax,expNow,evolutionMax,evolutionNow,power,quality,cost;
	WearEquipData equip[10];
	RideSkill skill[20];
	Ride_Final_Skill finalSkill;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	RideData_T(void)
	{
		strncpy(identity,"0",sizeof(identity));
		memset(id,0,sizeof(id));
		memset(photoId,0,sizeof(photoId));
		memset(nickName,0,sizeof(nickName));
		level=0;
		exptimes=0;
		hp=0;
		mp=0;
		outAttVal=0;
		inAttVal=0;
		outDefVal=0;
		inDefVal=0;
		hit=0;
		crit=0;
		dodge=0;
		tenacity=0;
		move=0;
		expMax=0;
		expNow=0;
		evolutionMax=0;
		evolutionNow=0;
		power=0;
		quality=0;
		cost=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const RideData_T &data)
	{
		memcpy(equip,data.equip,sizeof(equip));
		memcpy(identity,data.identity,sizeof(identity));
		memcpy(id,data.id,sizeof(id));
		memcpy(photoId,data.photoId,sizeof(photoId));
		memcpy(skill,data.skill,sizeof(skill));
		memcpy(nickName,data.nickName,sizeof(nickName));
		finalSkill=data.finalSkill;
		level=data.level;
		exptimes=data.exptimes;
		hp=data.hp;
		mp=data.mp;
		outAttVal=data.outAttVal;
		inAttVal=data.inAttVal;
		outDefVal=data.outDefVal;
		inDefVal=data.inDefVal;
		hit=data.hit;
		crit=data.crit;
		dodge=data.dodge;
		tenacity=data.tenacity;
		move=data.move;
		expMax=data.expMax;
		expNow=data.expNow;
		evolutionMax=data.evolutionMax;
		evolutionNow=data.evolutionNow;
		power=data.power;
		quality=data.quality;
		cost=data.cost;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}RideData;

typedef struct CampNumberData_T{
	int number0;
	int number1;
	int number2;
	
	CampNumberData_T(void)
	{
		number0=0;
		number1=0;
		number2=0;
	}
}CampNumberData;

typedef struct VIPRewardData_T{
	int recharge;
	int store;
	int warehouse;
	int flyTimes;
	int callTimes;
	int lixianTimes;
	char bagId[20];
	int lianxuTimes;
	int monTimes;
	int dazuoTimes;
	int guildTimes;
	int muscleTimes;
	int buyTimes;
	int midasTimes;
	int remidasTimes;
	int fubenRate;
	int refreshTimes;
	int freshNumber;
	int zuoqiFresh;
	int zuoqiNumber;
	int zuoqiRate;
	int rongLianRate;
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	VIPRewardData_T(void)
	{
		recharge=0;
		store=0;
		warehouse=0;
		flyTimes=0;
		callTimes=0;
		lixianTimes=0;
		memset(bagId,0,sizeof(bagId));
		lianxuTimes=0;
		monTimes=0;
		dazuoTimes=0;
		guildTimes=0;
		muscleTimes=0;
		buyTimes=0;
		midasTimes=0;
		remidasTimes=0;
		fubenRate=0;
		refreshTimes=0;
		freshNumber=0;
		zuoqiFresh=0;
		zuoqiNumber=0;
		zuoqiRate=0;
		rongLianRate=0;
	}
}VIPRewardData;

typedef struct VipDailyData_T{
	int stage;
	int recharge;
	int store;
	int warehouse;
	int flyTimes;
	int callTimes;
	int lixianTimes;
	char bagId[20];
	int lianxuTimes;
	int monTimes;
	int dazuoTimes;
	int guildTimes;
	int muscleTimes;
	int buyTimes;
	int midasTimes;
	int remidasTimes;
	int fubenRate;
	int refreshTimes;
	int freshNumber;
	int zuoqiFresh;
	int zuoqiNumber;
	int zuoqiRate;
	int rongLianRate;
	int receiveFlag;				//是否领取过vip奖励的标志 0为未领取 1为已领取
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	VipDailyData_T(void)
	{
		stage=0;
		recharge=0;
		store=0;
		warehouse=0;
		flyTimes=0;
		callTimes=0;
		lixianTimes=0;
		memset(bagId,0,sizeof(bagId));
		lianxuTimes=0;
		monTimes=0;
		dazuoTimes=0;
		guildTimes=0;
		muscleTimes=0;
		buyTimes=0;
		midasTimes=0;
		remidasTimes=0;
		fubenRate=0;
		refreshTimes=0;
		freshNumber=0;
		zuoqiFresh=0;
		zuoqiNumber=0;
		zuoqiRate=0;
		rongLianRate=0;
		receiveFlag=0;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}
	void operator = (const VipDailyData_T &data)
	{
		stage=data.stage;
		memcpy(bagId,data.bagId,sizeof(bagId));
		recharge=data.recharge;
		store=data.store;
		warehouse=data.warehouse;
		flyTimes=data.flyTimes;
		callTimes=data.callTimes;
		lixianTimes=data.lixianTimes;
		lianxuTimes=data.lianxuTimes;
		monTimes=data.monTimes;
		dazuoTimes=data.dazuoTimes;
		guildTimes=data.guildTimes;
		muscleTimes=data.muscleTimes;
		buyTimes=data.buyTimes;
		midasTimes=data.midasTimes;
		remidasTimes=data.remidasTimes;
		fubenRate=data.fubenRate;
		refreshTimes=data.refreshTimes;
		freshNumber=data.freshNumber;
		zuoqiFresh=data.zuoqiFresh;
		zuoqiNumber=data.zuoqiNumber;
		zuoqiRate=data.zuoqiRate;
		rongLianRate=data.rongLianRate;
		receiveFlag=data.receiveFlag;
		
		value1=data.value1;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
	}
}VipDailyData;


typedef struct DeskPt
{
	Point dishPt;
	bool  isDished;      //为真则不能用
	
	DeskPt(Point dishPt)
	{
		dishPt = dishPt;
		isDished = false;
	}
	
	bool operator < (const DeskPt &newDishPt) const
	{
		return dishPt < newDishPt.dishPt;
	}
	bool operator == (const DeskPt &newDishPt) const
	{
		return dishPt == newDishPt.dishPt;
	}
	
}DeskPt;


typedef struct Location_S
{
	char mapId[51];
	Point pixelPt;
	Location_S(){};
	Location_S(char *_mapId, Point pt)
	{
		strncpy(mapId, _mapId, sizeof(mapId));
		pixelPt = pt;
	}
	
	int distance(char* _mapId, Point pt)
	{
		if (strcmp(mapId, _mapId) != 0)
		{
			return MAX_DISTANCE_IN_MAP;
		}
		
		return sqrt((pt._x - pixelPt._x) * (pt._x - pixelPt._x) + (pt._y - pixelPt._y) * (pt._y - pixelPt._y));
	}
} Location_T;
typedef struct Special_Detail_T{
	int flag;
	int rate;
	int freeRate;
	int min;
	int max;
	int color;
}Special_Detail;

typedef struct Ride_Special_Skill_Config_T{
	Special_Detail skill[30];
	int number;
	int freeNumber;
	int openCost[2];
	int refreshCost[3];
}Ride_Special_Skill_Config;

typedef struct Pet_ZhanLi_T{
	int max;
	int number;
}Pet_ZhanLi;

typedef struct Pet_Range_T{
	int min;
	int max;
}Pet_Range;

typedef struct Pet_Xidian_T{
	int cost;
	int charge;
	Pet_Range outAttVal;
	Pet_Range inAttVal;
	Pet_Range hit;
	Pet_Range crit;
}Pet_Xidian;

typedef struct Equip_Operator_T{
	int rongLianPer;
	int rongLianAdd;
	int kaiRenAdd;
}Equip_Operator;

typedef struct LevelReward_T{
	int level;
	int repeat;
	int number;
	char goodsid[1024];
}LevelRewardData;

typedef struct RankRewardData_T{
	char heroRank[3][20];
	char petRank[3][20];
	char rideRank[3][20];
}RankReward;

typedef struct EveryDaySignReward_T{
	int day;
	char goodsid[20];
	int number;
}EveryDaySignRewardData;

typedef struct WuLinTargeItemtConfig_T{
	char goodsid[20];
	int number;
}WuLinTargeItemtConfig;

typedef struct WuLinTargetConfig_T{
	WuLinTargeItemtConfig wuLinTargeItemtConfig[50];
	char goodsid[20];
	int number;
	int totalNumber;
}WuLinTargetConfig;

#endif
