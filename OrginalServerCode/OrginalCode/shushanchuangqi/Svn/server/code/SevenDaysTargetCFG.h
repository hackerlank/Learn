// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevenDaysTargetCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSEVENDAYSTARGETLOADER_H
#define _CSEVENDAYSTARGETLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSevenDaysTargetCFG
{
	/**
	索引ID
	**/
	UINT16	_ID;

	/**
	天数
	**/
	UINT16	_Day;

	/**
	事件ID
	**/
	string	_EventID;

	/**
	目标奖励
	**/
	string	_Award;
}; // SSevenDaysTargetCFG define end

//data loader for the excel table
class CSevenDaysTargetLoader
{
public:
	std::vector<SSevenDaysTargetCFG*> _vecData;

	~CSevenDaysTargetLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

