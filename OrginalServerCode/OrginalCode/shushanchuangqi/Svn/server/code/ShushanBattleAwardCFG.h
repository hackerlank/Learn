// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShushanBattleAwardCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSHUSHANBATTLEAWARDLOADER_H
#define _CSHUSHANBATTLEAWARDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SShushanBattleAwardCFG
{
	/**
	荣誉等级
	**/
	UINT8	_HonorLevel;

	/**
	荣誉值
	**/
	UINT32	_Honor;

	/**
	奖励道具
	**/
	string	_Award;
}; // SShushanBattleAwardCFG define end

//data loader for the excel table
class CShushanBattleAwardLoader
{
public:
	std::vector<SShushanBattleAwardCFG*> _vecData;

	~CShushanBattleAwardLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

