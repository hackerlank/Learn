// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSystemConfigCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSYSTEMCONFIGLOADER_H
#define _CSYSTEMCONFIGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSystemConfigCFG
{
	/**
	序号
	**/
	UINT16	_ID;

	/**
	系统名称
	**/
	string	_Name;

	/**
	开启类型
	**/
	UINT8	_Type;

	/**
	配置参数
	**/
	UINT16	_Config;

	/**
	是否屏蔽
	**/
	UINT8	_Block;

	/**
	系统提示图标
	**/
	UINT32	_PreviewICON;

	/**
	提示等级
	**/
	UINT16	_PreviewLv;

	/**
	系统提示描述
	**/
	string	_PreviewDes;

	/**
	系统提示是否屏蔽
	**/
	UINT8	_PreviewBlock;

	/**
	从属的按钮
	**/
	UINT16	_MainButton;
}; // SSystemConfigCFG define end

//data loader for the excel table
class CSystemConfigLoader
{
public:
	std::vector<SSystemConfigCFG*> _vecData;

	~CSystemConfigLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

