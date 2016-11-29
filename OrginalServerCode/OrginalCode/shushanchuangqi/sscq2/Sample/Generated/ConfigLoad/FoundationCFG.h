// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFoundationCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFOUNDATIONLOADER_H
#define _CFOUNDATIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFoundationCFG
{
	/**
	类型
	**/
	UINT8	_Uid;

	/**
	名称
	**/
	string	_Type;

	/**
	花费
	**/
	UINT32	_Spend;

	/**
	等级
	**/
	string	_Level;

	/**
	返利比
	**/
	string	_Rebate;

	/**
	奖励
	**/
	string	_Reward;
}; // SFoundationCFG define end

//data loader for the excel table
class CFoundationLoader
{
public:
	std::vector<SFoundationCFG*> _vecData;

	~CFoundationLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

