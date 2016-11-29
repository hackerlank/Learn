// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SIconAppearCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CICONAPPEARLOADER_H
#define _CICONAPPEARLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SIconAppearCFG
{
	/**
	IOCN出现顺序ID
	**/
	UINT16	_ID;

	/**
	ICON名称
	**/
	string	_Name;

	/**
	触发类型
	**/
	UINT8	_Type;

	/**
	触发参数
	**/
	string	_Parameter;

	/**
	充值开启
	**/
	UINT8	_RechageOpen;

	/**
	弹出界面
	**/
	string	_data;

	/**
	是否属于活动
	**/
	UINT8	_IsActivity;

	/**
	活动id
	**/
	UINT32	_activityID;

	/**
	不满足条件提示
	**/
	string	_tips;

	/**
	描述
	**/
	string	_Des;

	/**
	冲突功能
	**/
	string	_Clusion;

	/**
	共存功能
	**/
	string	_Coexist;

	/**
	是否全屏
	**/
	UINT8	_FullScn;
}; // SIconAppearCFG define end

//data loader for the excel table
class CIconAppearLoader
{
public:
	std::vector<SIconAppearCFG*> _vecData;

	~CIconAppearLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

