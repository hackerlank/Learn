// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildStepAwardCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDSTEPAWARDLOADER_H
#define _CGUILDSTEPAWARDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildStepAwardCFG
{
	/**
	奖励等级
	**/
	UINT8	_AwardLevel;

	/**
	帮派排名
	**/
	string	_GuildStep;

	/**
	奖励道具
	**/
	string	_Award;
}; // SGuildStepAwardCFG define end

//data loader for the excel table
class CGuildStepAwardLoader
{
public:
	std::vector<SGuildStepAwardCFG*> _vecData;

	~CGuildStepAwardLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

