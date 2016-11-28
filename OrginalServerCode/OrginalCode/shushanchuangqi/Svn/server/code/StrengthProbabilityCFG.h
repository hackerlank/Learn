// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStrengthProbabilityCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTRENGTHPROBABILITYLOADER_H
#define _CSTRENGTHPROBABILITYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStrengthProbabilityCFG
{
	/**
	索引ID
	**/
	UINT16	_ID;

	/**
	强化级数
	**/
	UINT16	_Level;

	/**
	品质颜色
	**/
	UINT8	_Color;

	/**
	真金概率
	**/
	UINT32	_Probability1;

	/**
	精金概率
	**/
	UINT32	_Probability2;

	/**
	精金保护概率（祝福）
	**/
	UINT16	_Protect2;
}; // SStrengthProbabilityCFG define end

//data loader for the excel table
class CStrengthProbabilityLoader
{
public:
	std::vector<SStrengthProbabilityCFG*> _vecData;

	~CStrengthProbabilityLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

