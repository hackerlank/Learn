// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarsCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTARSLOADER_H
#define _CSTARSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStarsCFG
{
	/**
	奖励Id
	**/
	UINT16	_PrizeId;

	/**
	需要星级
	**/
	UINT32	_RequiredStars;

	/**
	奖励
	**/
	string	_Awards;
}; // SStarsCFG define end

//data loader for the excel table
class CStarsLoader
{
public:
	std::vector<SStarsCFG*> _vecData;

	~CStarsLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

