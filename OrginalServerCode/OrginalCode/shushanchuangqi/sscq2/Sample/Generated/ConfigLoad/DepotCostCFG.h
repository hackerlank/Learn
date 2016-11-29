// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDepotCostCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDEPOTCOSTLOADER_H
#define _CDEPOTCOSTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDepotCostCFG
{
	/**
	待开启格子顺序
	**/
	UINT8	_Idx;

	/**
	开启花费金额
	**/
	UINT8	_Cost;
}; // SDepotCostCFG define end

//data loader for the excel table
class CDepotCostLoader
{
public:
	std::vector<SDepotCostCFG*> _vecData;

	~CDepotCostLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

