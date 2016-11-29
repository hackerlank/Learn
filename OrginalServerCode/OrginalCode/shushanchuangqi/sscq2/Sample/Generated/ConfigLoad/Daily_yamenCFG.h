// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_yamenCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_YAMENLOADER_H
#define _CDAILY_YAMENLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_yamenCFG
{
	/**
	侠义等级
	**/
	UINT16	_Level;

	/**
	需要的侠义点
	**/
	UINT16	_Cost;

	/**
	宝箱ID
	**/
	UINT16	_Retrun;

	/**
	称号
	**/
	string	_Title;

	/**
	升级任务
	**/
	UINT16	_Task;

	/**
	经验加成
	**/
	UINT16	_Exp;
}; // SDaily_yamenCFG define end

//data loader for the excel table
class CDaily_yamenLoader
{
public:
	std::vector<SDaily_yamenCFG*> _vecData;

	~CDaily_yamenLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

