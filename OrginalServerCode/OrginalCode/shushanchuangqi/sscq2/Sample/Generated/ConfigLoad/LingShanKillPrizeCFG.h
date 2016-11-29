// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanKillPrizeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLINGSHANKILLPRIZELOADER_H
#define _CLINGSHANKILLPRIZELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLingShanKillPrizeCFG
{
	/**
	胜利次数
	**/
	UINT16	_Kills;

	/**
	奖励随缘值
	**/
	UINT16	_SuiYuan;
}; // SLingShanKillPrizeCFG define end

//data loader for the excel table
class CLingShanKillPrizeLoader
{
public:
	std::vector<SLingShanKillPrizeCFG*> _vecData;

	~CLingShanKillPrizeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

