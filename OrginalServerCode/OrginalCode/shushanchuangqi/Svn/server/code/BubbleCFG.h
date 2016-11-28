// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBubbleCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBUBBLELOADER_H
#define _CBUBBLELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBubbleCFG
{
	/**
	气泡ID
	**/
	UINT16	_wID;

	/**
	气泡文字变量id
	**/
	UINT16	_wMessageID;

	/**
	优先级
	**/
	UINT8	_byPriority;

	/**
	回应类型
	**/
	UINT8	_byResponeType;

	/**
	覆盖规则ID
	**/
	UINT16	_wGroupID;

	/**
	覆盖规则类型
	**/
	UINT16	_wGroupType;

	/**
	离线保留
	**/
	UINT8	_byOfflineEnable;

	/**
	追溯，（tip内容，离线保留与否，覆盖与否），tip出现需要引用的参数，请用英文字符，出现中文格杀勿论，比如 { 要用英文的
	**/
	string	_description;
}; // SBubbleCFG define end

//data loader for the excel table
class CBubbleLoader
{
public:
	std::vector<SBubbleCFG*> _vecData;

	~CBubbleLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

