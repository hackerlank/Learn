// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildSpotCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDSPOTLOADER_H
#define _CGUILDSPOTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildSpotCFG
{
	/**
	据点编号
	**/
	UINT8	_Id;

	/**
	据点名字
	**/
	string	_Name;

	/**
	积分
	**/
	UINT8	_Score;

	/**
	最大人数
	**/
	UINT8	_MaxNum;

	/**
	地图ID
	**/
	UINT32	_MapId;
}; // SGuildSpotCFG define end

//data loader for the excel table
class CGuildSpotLoader
{
public:
	std::vector<SGuildSpotCFG*> _vecData;

	~CGuildSpotLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

