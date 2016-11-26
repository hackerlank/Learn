#ifndef BOTTLE_H
#define BOTTLE_H
#include"libev.h"
#include<set>
#include<string>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
const int TYPEBOTTLE = 2;

using namespace std;
class Hero;
class Map_Inform;
class Bottle
{
	char id[SHOR_MID_VALUE_LENGTH + 1];	              //实例id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //类型id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //图片id
	char name[SHOR_MID_VALUE_LENGTH + 1];              //名称
	int lifeVal;              //生命值
	int lifeValUpper;         //生命上限值
	int hurt;                  //每次伤害
	char bornMsg[IN_VIEW_LENGTH + 1];           //出生信息
	char outMsg[OUT_VIEW_LENGTH + 1];		      //下线消息
	Point logicPt;            //逻辑坐标
	Point pt;                 //像素坐标
	Map_Inform *map_now;         
	static int count;
	bool bruOut;
	ev_timer think_timer;    //计时器
	
	int brushStyle;          //刷出模式  
	double bloodPre;     //打破者回血
	double magicPre;    //打破者回蓝
	
	char dropStage[SHOR_MID_VALUE_LENGTH + 1];       //掉落阶段
	size_t dropNum;           //掉多少件
public:
	Bottle(char *_typeId,int _lifeVal,int _hurt,int _brushStyle,double bloodPre,double magicPre,char *_name,size_t dropNum,char* _dropStage,char *_photoId);
	
	/*生成刷出信息*/
	void formBornMsg(void);
	
	/*获得id*/
	char* getId(void);
	
	/*生成下线信息*/
	void formOutMsg(void);
	
	/*获得玩家实例指针*/
	Hero* getHero(char *heroId);
	
	/*设置地图实例指针*/
	void setMap(Map_Inform *_map_now);
	
	/*获得逻辑坐标点*/
	Point getLogicPt(void);

	/*复制瓶罐*/
	Bottle* copyBottle(char *_mapId);
	
	/*获得瓶罐id*/
	char* getBottleId(void);
	
	/*设置实例id*/
	void setInstId(char *_id);
	
	/*刷出瓶罐*/
	void brushMsg(void);
	
	/*瓶罐从地图消亡*/
	void disperMsg(void);
	
	/*设置像素坐标*/
	void setPiexPt(Point _pt);

	/*析构函数*/
	~Bottle(void);
	
	/*复制瓶罐<重载函数，在读取地图配置文件里面用>*/
	Bottle* copyBottle(Point _pt);
	
	/*获得瓶罐的生命值*/
	int getLifeVal(void);
	
	/*设置瓶罐的生命值*/
	void setLifeVal(int _lifeVal);
	
	/*获得上线消息*/
	char* getBronMsg(void);
	
	/*获得下线信息*/
	char* getOutMsg(void);
	
	/*获得像素坐标*/
	Point getPiexPt(void);
	
	/*设置瓶罐的生命值*/
	void beAttack(const char* attackId);
	
	/*获得瓶罐伤害值*/
	int getHurt(void);
	
	/*打碎后再次刷出判断*/
	bool isAlive(void);
	
	/*打碎后消息发送*/
	bool sendDieMsg(void);	
	
	/*已打碎打碎标志*/
	bool dieOutFlg(void);
	
	/*已打碎打碎标志*/
	bool aliveFlg(void);
	
	/*取地图实例指针*/
	Map_Inform* getMap(void);
	
	/*取类型id*/
	char* getTypeId(void);
	
	/*获得刷出模式值*/
	int getBrushStyle(void);
	
	/*重置瓶罐属性*/
	void initBot(void);
	
	//获取血上限
	int getLifeUpperVal();
	
	/*打碎者回血的百分比*/
	double getBloodPre(void);
	
	/*打碎者回蓝的百分比*/
	double getMagicPre(void);
	
	const char* getDropStage(void) const;
	
};
#endif
