// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShuShanLunJianExpCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSHUSHANLUNJIANEXPLOADER_H
#define _CSHUSHANLUNJIANEXPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SShuShanLunJianExpCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	经验奖励
	**/
	UINT32	_ExpAward;
}; // SShuShanLunJianExpCFG define end

//data loader for the excel table
class CShuShanLunJianExpLoader
{
public:
	std::vector<SShuShanLunJianExpCFG*> _vecData;

	~CShuShanLunJianExpLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

