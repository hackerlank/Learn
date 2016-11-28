// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPBaseCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CVIPBASELOADER_H
#define _CVIPBASELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SVIPBaseCFG
{
	/**
	类型ID
	**/
	UINT8	_ID;

	/**
	有效天数
	**/
	UINT32	_Days;

	/**
	花费仙石
	**/
	UINT32	_NeedGold;

	/**
	描述
	**/
	string	_Desc;

	/**
	促销奖励
	**/
	UINT16	_Promotion;

	/**
	赠送奖励
	**/
	UINT16	_Give;
}; // SVIPBaseCFG define end

//data loader for the excel table
class CVIPBaseLoader
{
public:
	std::vector<SVIPBaseCFG*> _vecData;

	~CVIPBaseLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

