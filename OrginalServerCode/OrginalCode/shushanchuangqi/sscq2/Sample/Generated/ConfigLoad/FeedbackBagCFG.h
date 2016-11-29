// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFeedbackBagCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFEEDBACKBAGLOADER_H
#define _CFEEDBACKBAGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFeedbackBagCFG
{
	/**
	类型
	**/
	UINT16	_Type;

	/**
	开始时间
	**/
	UINT16	_BgDay;

	/**
	结束时间
	**/
	UINT16	_EndDay;

	/**
	原价
	**/
	UINT16	_OldCost;

	/**
	现价
	**/
	UINT16	_NewCost;

	/**
	奖励
	**/
	string	_Award;

	/**
	限购次数
	**/
	UINT16	_BuyNum;
}; // SFeedbackBagCFG define end

//data loader for the excel table
class CFeedbackBagLoader
{
public:
	std::vector<SFeedbackBagCFG*> _vecData;

	~CFeedbackBagLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

