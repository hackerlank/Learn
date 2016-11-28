// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFormationCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFORMATIONLOADER_H
#define _CFORMATIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFormationCFG
{
	/**
	阵形ID
	**/
	UINT16	_ID;

	/**
	阵形名称
	**/
	string	_Name;

	/**
	位置编号
	**/
	string	_Position;

	/**
	解锁条件说明
	**/
	UINT32	_Unlock;

	/**
	激活奖励
	**/
	UINT16	_AttrIdx_1;
}; // SFormationCFG define end

//data loader for the excel table
class CFormationLoader
{
public:
	std::vector<SFormationCFG*> _vecData;

	~CFormationLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

