// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGodMonsterLimitPrizeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGODMONSTERLIMITPRIZELOADER_H
#define _CGODMONSTERLIMITPRIZELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGodMonsterLimitPrizeCFG
{
	/**
	限购礼包ID
	**/
	UINT16	_ID;

	/**
	当前价格
	**/
	UINT16	_CurPrice;

	/**
	折扣
	**/
	float	_Discount;

	/**
	原价
	**/
	UINT16	_OrigPrice;

	/**
	礼包描述
	**/
	string	_Desc;

	/**
	条件
	**/
	UINT8	_Cond;

	/**
	限购数量
	**/
	UINT8	_Num;

	/**
	帮派贡献
	**/
	UINT32	_Devote;

	/**
	礼包内容
	**/
	string	_Content;
}; // SGodMonsterLimitPrizeCFG define end

//data loader for the excel table
class CGodMonsterLimitPrizeLoader
{
public:
	std::vector<SGodMonsterLimitPrizeCFG*> _vecData;

	~CGodMonsterLimitPrizeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

