// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevenConsumeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSEVENCONSUMELOADER_H
#define _CSEVENCONSUMELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSevenConsumeCFG
{
	/**
	类型
	**/
	UINT16	_ID;

	/**
	额度
	**/
	UINT16	_Limit;

	/**
	奖励
	**/
	string	_Reward;
}; // SSevenConsumeCFG define end

//data loader for the excel table
class CSevenConsumeLoader
{
public:
	std::vector<SSevenConsumeCFG*> _vecData;

	~CSevenConsumeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

