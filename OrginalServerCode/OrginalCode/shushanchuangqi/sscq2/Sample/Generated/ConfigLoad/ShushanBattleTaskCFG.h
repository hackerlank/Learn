// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShushanBattleTaskCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSHUSHANBATTLETASKLOADER_H
#define _CSHUSHANBATTLETASKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SShushanBattleTaskCFG
{
	/**
	任务ID
	**/
	UINT32	_ID;

	/**
	任务难度
	**/
	UINT8	_Degree;

	/**
	任务荣誉
	**/
	UINT16	_Award;

	/**
	任务层级
	**/
	UINT8	_Gradation;

	/**
	任务描述
	**/
	string	_Tip;
}; // SShushanBattleTaskCFG define end

//data loader for the excel table
class CShushanBattleTaskLoader
{
public:
	std::vector<SShushanBattleTaskCFG*> _vecData;

	~CShushanBattleTaskLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

