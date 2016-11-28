// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEventCenterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEVENTCENTERLOADER_H
#define _CEVENTCENTERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEventCenterCFG
{
	/**
	事件id
	**/
	UINT32	_EventInstID;

	/**
	事件类型
	**/
	UINT32	_EventType;

	/**
	GetCondID
	**/
	UINT16	_GetCondType;

	/**
	参数1类型
	**/
	UINT16	_OpType1;

	/**
	参数2类型
	**/
	UINT16	_OpType2;

	/**
	特殊类型
	**/
	UINT16	_OpVecType;

	/**
	事件参数1
	**/
	UINT32	_ParamLimit1;

	/**
	事件参数2
	**/
	UINT32	_ParamLimit2;

	/**
	特殊类型参数
	**/
	string	_VecParamLimit;
}; // SEventCenterCFG define end

//data loader for the excel table
class CEventCenterLoader
{
public:
	std::vector<SEventCenterCFG*> _vecData;

	~CEventCenterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

