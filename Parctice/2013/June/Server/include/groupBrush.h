/************************************************************
	文件名：groupBrush.h
	文件作用：定义GroupBrush的属性和函数
	作者：chenzhen
	创建日期：2012.07.06
************************************************************/

#ifndef GROUP_BRUSH_H
#define GROUP_BRUSH_H
#include<string>
#include"data_structure_struct.h"
using namespace std;
class GroupBrush
{
	string groupId;           //批次id
	double generRatio;        //普通怪所占比例
	double eliteRatio;        //精英怪所占比例
	double activeRatio;       //主动怪所占比例	
	double passRatio;         //被动怪所占比例
	double patRatio;          //巡逻怪所占比例
	bool randFlg;             //boss怪是否随机涮出
	int bossNum;              //BOSS如果随机涮出，则数量
	public:
	GroupBrush(char *_groupId,double _generRatio,\
			  double _eliteRatio,bool _randFlg,\
			  int _bossNum,double _activeRatio,\
			  double _passRatio,double _patRatio);			 
	
	/*获得批次id*/
	char* getGroupId(void);
	
	/*获得普通怪比例*/
	double getGenerRatio(void);
	
	/*获得精英怪比例*/
	double getEliteRatio(void);
	
	/*获得主动怪比例*/
	double getActiveRatio(void);
	
	/*获得被动怪比例*/
	double getPassRatio(void);
	
	/*获得巡逻怪比例*/
	double getPatRatio(void);
	
	/*获得boss是否随机涮出*/
	bool getRandFlg(void);
	
	/*获得boss随机数量*/
	int getBossNum(void);
	
	/*获得普通怪数量*/
	int getGenerNum(int _sum);
	
	/*获得精英怪数量*/
	int getEliteNum(int _sum);
	
	/*获得主动怪数量*/
	int getActiveNum(int _sum);
	
	/*获得被动怪数量*/
	int getPassNum(int _sum);
	
	/*获得巡逻怪数量*/
	int getPatNum(int _sum);
	
	/*获得批次怪物组合数量*/
	MonGroNum getMonGroNum(int _sum);
	
	/*复制函数*/
	GroupBrush* CopyGroBru(void);
	
	/*析构函数*/
	~GroupBrush(void);
};
#endif
	
	