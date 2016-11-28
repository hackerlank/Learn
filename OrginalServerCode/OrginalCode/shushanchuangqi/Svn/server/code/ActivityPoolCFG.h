// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityPoolCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYPOOLLOADER_H
#define _CACTIVITYPOOLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityPoolCFG
{
	/**
	ID
	**/
	UINT16	_VIPLevel;

	/**
	宝箱ID
	**/
	UINT32	_LootID;
}; // SActivityPoolCFG define end

//data loader for the excel table
class CActivityPoolLoader
{
public:
	std::vector<SActivityPoolCFG*> _vecData;

	~CActivityPoolLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

