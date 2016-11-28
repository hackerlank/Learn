// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingMountainCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLINGMOUNTAINLOADER_H
#define _CLINGMOUNTAINLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLingMountainCFG
{
	/**
	灵山编号
	**/
	UINT8	_ID;

	/**
	灵山名称
	**/
	string	_Goods;

	/**
	奖励
	**/
	string	_Award;
}; // SLingMountainCFG define end

//data loader for the excel table
class CLingMountainLoader
{
public:
	std::vector<SLingMountainCFG*> _vecData;

	~CLingMountainLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

