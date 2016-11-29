// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCollectionLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOLLECTIONLEVELLOADER_H
#define _CCOLLECTIONLEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCollectionLevelCFG
{
	/**
	收藏等级
	**/
	UINT16	_ID;

	/**
	需要收藏点
	**/
	UINT16	_Point;

	/**
	奖励类型
	**/
	UINT16	_AwardType;

	/**
	奖励参数
	**/
	UINT16	_AwardPara;

	/**
	累计属性奖励ID
	**/
	UINT16	_PropAward;
}; // SCollectionLevelCFG define end

//data loader for the excel table
class CCollectionLevelLoader
{
public:
	std::vector<SCollectionLevelCFG*> _vecData;

	~CCollectionLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

