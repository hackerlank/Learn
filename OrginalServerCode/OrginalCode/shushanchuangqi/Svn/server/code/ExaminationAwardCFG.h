// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExaminationAwardCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXAMINATIONAWARDLOADER_H
#define _CEXAMINATIONAWARDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExaminationAwardCFG
{
	/**
	排名区间上
	**/
	UINT16	_RankTop;

	/**
	排名区间下
	**/
	UINT16	_RankBottom;

	/**
	奖励类型
	**/
	UINT16	_PrizeType;

	/**
	奖励
	**/
	string	_GivenItem;
}; // SExaminationAwardCFG define end

//data loader for the excel table
class CExaminationAwardLoader
{
public:
	std::vector<SExaminationAwardCFG*> _vecData;

	~CExaminationAwardLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

