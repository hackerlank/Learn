// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromotePointCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPROMOTEPOINTLOADER_H
#define _CPROMOTEPOINTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPromotePointCFG
{
	/**
	序列号
	**/
	UINT8	_ID;

	/**
	名称
	**/
	string	_Name;

	/**
	推荐度
	**/
	UINT8	_Star;

	/**
	跳转限制
	**/
	UINT16	_SkipLimit;
}; // SPromotePointCFG define end

//data loader for the excel table
class CPromotePointLoader
{
public:
	std::vector<SPromotePointCFG*> _vecData;

	~CPromotePointLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

