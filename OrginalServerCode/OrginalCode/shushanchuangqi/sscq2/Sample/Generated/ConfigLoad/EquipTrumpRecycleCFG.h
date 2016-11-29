// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEquipTrumpRecycleCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEQUIPTRUMPRECYCLELOADER_H
#define _CEQUIPTRUMPRECYCLELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEquipTrumpRecycleCFG
{
	/**
	法宝ID
	**/
	UINT16	_EquipTrumpId;

	/**
	强化等级
	**/
	UINT8	_Level;

	/**
	分解掉落
	**/
	UINT32	_LootId;

	/**
	可能掉落
	**/
	string	_DropPreview;
}; // SEquipTrumpRecycleCFG define end

//data loader for the excel table
class CEquipTrumpRecycleLoader
{
public:
	std::vector<SEquipTrumpRecycleCFG*> _vecData;

	~CEquipTrumpRecycleLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

