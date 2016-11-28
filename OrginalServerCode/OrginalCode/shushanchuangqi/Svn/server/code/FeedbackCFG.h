// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFeedbackCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFEEDBACKLOADER_H
#define _CFEEDBACKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFeedbackCFG
{
	/**
	号码
	**/
	UINT16	_Id;

	/**
	开始时间
	**/
	UINT16	_BgDay;

	/**
	结束时间
	**/
	UINT16	_EndDay;

	/**
	类型
	**/
	UINT16	_Type;

	/**
	品质
	**/
	UINT8	_Quality;

	/**
	条件参数
	**/
	UINT16	_Term;

	/**
	固定奖励
	**/
	string	_Award;

	/**
	随机奖励
	**/
	string	_Random1;

	/**
	链接界面
	**/
	string	_Link;
}; // SFeedbackCFG define end

//data loader for the excel table
class CFeedbackLoader
{
public:
	std::vector<SFeedbackCFG*> _vecData;

	~CFeedbackLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

