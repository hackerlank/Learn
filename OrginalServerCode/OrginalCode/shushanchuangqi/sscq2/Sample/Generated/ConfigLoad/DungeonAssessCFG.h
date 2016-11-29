// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDungeonAssessCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDUNGEONASSESSLOADER_H
#define _CDUNGEONASSESSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDungeonAssessCFG
{
	/**
	编号
	**/
	UINT16	_ID;

	/**
	评价描述
	**/
	string	_Describe;

	/**
	评价类型
	**/
	UINT8	_Type;

	/**
	评价参数
	**/
	string	_TypePara;
}; // SDungeonAssessCFG define end

//data loader for the excel table
class CDungeonAssessLoader
{
public:
	std::vector<SDungeonAssessCFG*> _vecData;

	~CDungeonAssessLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

