/************************************************************
	文件名：statuaryBase.h
	文件作用：定义StatuaryBase类
	作者：chenzhen
	创建日期：2013.03.01
************************************************************/

#ifndef STATUARY_BASE_H
#define STATUARY_BASE_H
#include"wholeDefine.h"
#include"data_structure_struct.h"
#include<string>
#include<map>
#include"statuaryHero.h"
using namespace std;

class StatuaryBase
{
	char vocation[SHOR_MID_VALUE_LENGTH + 1];      //职业id
	map<string,string>limitToPhotoId;                 //限制map，键为int型，值为对应图片id
	Point piexPt;                                  //像素坐标
	char mapId[SHOR_MID_VALUE_LENGTH + 1];             //地图id
	int lastSeconds;                               //持续时间	
	
	public:
	
	StatuaryBase(char* _vocation,map<string,string> &_limitToPhotoId,Point _piexPt,char* _mapId);
	
	/*获得职业id*/
	char* getVocation(void);
	
	/*获得地图id*/
	char* getMapId(void);
	
	/*获得像素点*/
	Point getPiexPt(void);
	
	/*根据参数require获得相对应的图片id*/
	char* getPhotoId(char* require);
	
	/*角色赢得雕像*/
	MemStatuaryHero* winStatuary(void* memHero,char* titleId);
	
	/*根据参数require获得相对应的图片id,测试用的*/
	char* testGetPhotoId(char* require);
};
#endif
