/************************************************************
	文件名：bruMonInfor.h
	文件作用：类BruMonInfor类的属性和方法
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#ifndef BRUSHMONSTERINFORM_H
#define BRUSHMONSTERINFORM_H
#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;
class BruMonInfor
{
private:
	string typeId;                 //怪物类型id
	int brushed_count;             //已涮出怪物数量
	int sum;                       //总数
	int alive_count;               //现存活怪物数量
	set<string>liveMonId;         //此类型已经刷出且存活的的怪的id
	set<string>bushMonId;         //此类型还没有刷出的怪的id
	set<string>dieMonId;          //此类型的已经死的id
public:
	BruMonInfor(char *_typeId,int _brushed_count,int _sum,int _alive_count);
	
	/*获得此类型现存活的怪的id集合*/
	set<string>& getLivMonId(void);
	
	/*获得此类型即将涮出怪的id集合*/
	set<string>& getBushMonId(void);
	
	
	set<string>& getDieMonId(void);
	
	/*获得此类型怪物id*/
	char* getTyId(void);
	
	/*获得此类型怪物待涮出数目*/
	int getBrshCnt(void);
	
	/*获得此类型怪物总数目*/
	int getSumCnt(void);
	
	/*得到活着的怪的数目*/
	int getLivCnt(void);
	
	/*设置将要刷怪的数目*/
	void setBrshCnt(int _num);
	
	/*设置总怪的数目*/	
	void setSumCnt(int _num);
	
	/*设置活着的怪的数目*/
	void setLivCnt(int _num);
	
	/*把死亡的怪的id放入死亡容器中(在怪物死亡函数里面调用）*/
	void InputDieId(char *monId);
	
	/*把活着的怪的id放入存活容器中*/
	void InputLiveId(char *monLivId);
	
	/*把要死亡容器的id放入刷怪容器中*/
	void exchage(void);
	
	/*把要即将要刷的怪的id放入参数vector中*/
	void outBruMonId(vector<string> &bruId,int _num = 0);
	
	/*把刚刷好的的怪的id（即参数vector）放入存活容器中，//重载InputLiveId函数*/
	void InputLiveId(vector<string> &bruId);   
	
	~BruMonInfor(void);
	
	/*把要刷怪的id放入刷怪容器中*/
	void InputBruId(char *monId);
	
	/*把要刷怪的id放入刷怪容器中(主要在地图配置文件里面调用）*/
	void inputBruId(char* monBruId);  
	
	/*取出所有即将涮出的怪物id*/
	void outBruMonIdAll(vector<string>& bruId);          //一次性把一个类型的怪全刷出来的
	
	/*测试打印死亡容器内容*/
	void testPrintDie(void);
	
	/*测试打印存活容器内容*/
	void testPrintLive(void);
	
	/*测试打印将要涮出容器内容*/
	void testPrintBush(void);
	
	/*把以存活怪物放进待刷容器中*/
	void exchageLve(void);
	
	/*复原brush*/
	void initBrush(void);
	
	
	/*设置存活容器*/
	void setLiveMonId(set<string> &_liveMonId);
	
	/*设置死亡容器*/
	void setDieMonId(set<string> &_dieMonId);
	
	/*设置刷怪容器*/
	void setBushMonId(set<string> &_bushMonId);
	
	/*设置刷怪容器*/
	BruMonInfor* copyMonBru(void);
	
	/*单插入存活容器中*/
	void inputOneLve(char* monLivId);
	
	
};
#endif
	
	

	
