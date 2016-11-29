// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEquipTrumpSlotCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEQUIPTRUMPSLOTLOADER_H
#define _CEQUIPTRUMPSLOTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEquipTrumpSlotCFG
{
	/**
	法宝ID
	**/
	UINT8	_SlotId;

	/**
	法宝坑位类型
	**/
	UINT8	_EquipTrumpType;

	/**
	解锁渡劫等级
	**/
	UINT16	_UnlockDujieLevel;

	/**
	是否不开放
	**/
	UINT8	_Lock;
}; // SEquipTrumpSlotCFG define end

//data loader for the excel table
class CEquipTrumpSlotLoader
{
public:
	std::vector<SEquipTrumpSlotCFG*> _vecData;

	~CEquipTrumpSlotLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

