// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEveryDayRechargeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEVERYDAYRECHARGELOADER_H
#define _CEVERYDAYRECHARGELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEveryDayRechargeCFG
{
	/**
	类型
	**/
	UINT16	_ID;

	/**
	日期
	**/
	string	_Time;

	/**
	额度
	**/
	UINT16	_Limit;

	/**
	奖励
	**/
	string	_Reward;
}; // SEveryDayRechargeCFG define end

//data loader for the excel table
class CEveryDayRechargeLoader
{
public:
	std::vector<SEveryDayRechargeCFG*> _vecData;

	~CEveryDayRechargeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

