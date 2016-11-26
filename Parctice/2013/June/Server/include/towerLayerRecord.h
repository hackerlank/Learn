/************************************************************
	文件名：towerLayerRecord.h
	文件作用：TowerLayerRecord类的方法和属性的申明
	作者：chenzhen
	创建日期：2012.09.11
************************************************************/
#ifndef TOWER_LAYER_RECORD_H
#define TOWER_LAYER_RECORD_H
#include"other_define_data.h"
#include"wholeDefine.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<string>
#include<list>
#include<map>
#include<set>

class Hero;
using namespace std;

/*塔面板数据初始化头命令*/
#define TOWER_F 33
#define TOWER_S 1

/*层面板数据初始化头命令*/
#define LAYER_F 33
#define LAYER_S 2

typedef struct TowerRecordAsist
{
	char Id[LITTLE_MID_VALUE_LENGTH + 1];
	int flg;
	
	TowerRecordAsist(char *_Id = NULL,int _flg = 0)
	{
		memset(Id,'\0',sizeof(Id));
		if(_Id)
		{
			strncpy(Id,_Id,strlen(_Id));
		}
		flg = _flg;
	}
	
	TowerRecordAsist(const TowerRecordAsist &towerAsist)
	{
		memset(Id,'\0',sizeof(Id));
		strncpy(Id,towerAsist.Id,strlen(towerAsist.Id));
		flg = towerAsist.flg;
	}
	
	TowerRecordAsist& operator= (const TowerRecordAsist &towerAsist)
	{
		memset(Id,'\0',sizeof(Id));
		strncpy(Id,towerAsist.Id,strlen(towerAsist.Id));
		flg = towerAsist.flg;
		return *this;
	}
		
}TowerRecordAsist;


class TowerLayerRecord
{
	map<string,TowerRecordAsist> towerMap;             //塔状态管理
	
	map<string,TowerRecordAsist> layerMap;         //每一层塔里面层次管理
	
	char towerMsg[LONG_MID_VALUE_LENGTH + 1];          //塔开启消息
	
	char layerMsg[LONG_MID_VALUE_LENGTH + 1];          //层开启消息
	
	char nowTowerId[LITTLE_MID_VALUE_LENGTH + 1];      //当前开启塔id
	
	char nowLayerId[LITTLE_MID_VALUE_LENGTH + 1];      //当前开启层id
	
	Hero* owner;                                       //主人
	
	set<string> swapLayerId;                           //扫荡层集合
	
	bool isSwap;                                       //没有扫荡，则为假，否则为真
	
	public:
	
	/*默认第一层塔的第一层开启*/
	TowerLayerRecord(Hero* _owner);
	
	/*打过层之后开通下一层函数*/
	void changeLayerId(void);
	
	/*判断是否为当前塔*/
	bool isRightTower(char *towerId);
	
	/*判断层是否开启*/
	bool isRightLayer(char *layerId);
	
	/*析构函数*/
	~TowerLayerRecord(void);
	
	/*获得塔的开启消息*/
	char* getTowerMsg(void);
	
	/*获得层的开启消息*/
	char* getLayerMsg(void);
	
	/*弹出扫荡奖励面板*/
	void beginSwapOutReward(void);
	
	/*领取扫荡奖励*/
	void endSwapOutReward(void);
	
	/*刷新层标志的数据*/
	void brushLayerFlg(void);
	
	/*判断是否有必要刷新如果为真，表示可以刷新，否则，表示没必要刷新*/
	bool isShouldBrushLayer(void);

	private:
	
	/*生成塔面板消息*/
	void initTwoerMsg(void);
	
	/*生成层面板消息*/
	void initLayerMsg(bool _isCanBuy = false);
	
	/*更改当前塔的id*/
	bool changeTowerId(void);
	
	/*跨塔时初始化层的数据*/
	void initLayerFlg(void);
	
	/*生成面板消息*/
	void initMsg(void);		
	
	/*初始化黑木崖塔的数据*/
	void initTwoerMap(void);
	
	/*初始化黑木崖层的数据*/
	void initLayerMap(void);	
	
	/*往memcached存东西*/
	void storeData(void);
	
	/*求获得的扫荡集合*/
	void bornSwapOutRewardSet(void);
	
	/*初始化层是否可以进入*/
	void initLayerCanFlg(void);
	
	/*更改每层标志缓存数据*/
	void chgLayerFlg(char *layerId,int flag);
	
	/*跨塔时更改层标志的数据*/
	void coverChgeLayerFlg(void);
	
	/*打完最后一层，最后一个塔后，控制那个刷新按钮*/
	void lastLayer(void);
};

/*测试黑木崖读取配置是否正确*/
void testTowerLayerConf(void);

void testTowerLayerConfAsist(map<string,string> &conf);

#endif
	
	