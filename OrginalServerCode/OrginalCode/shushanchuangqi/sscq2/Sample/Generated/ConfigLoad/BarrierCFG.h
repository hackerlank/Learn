// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBarrierCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBARRIERLOADER_H
#define _CBARRIERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBarrierCFG
{
	/**
	ID
	**/
	UINT16	_ConditionID;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	条件1
	**/
	string	_Condition_1;

	/**
	条件2
	**/
	string	_Condition_2;

	/**
	条件3
	**/
	string	_Condition_3;

	/**
	条件4
	**/
	string	_Condition_4;

	/**
	条件5
	**/
	string	_Condition_5;
}; // SBarrierCFG define end

//data loader for the excel table
class CBarrierLoader
{
public:
	std::vector<SBarrierCFG*> _vecData;

	~CBarrierLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

