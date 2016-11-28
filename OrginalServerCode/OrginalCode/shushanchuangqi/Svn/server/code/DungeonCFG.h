// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDungeonCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDUNGEONLOADER_H
#define _CDUNGEONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDungeonCFG
{
	/**
	编号
	**/
	UINT16	_ID;

	/**
	副本名称
	**/
	string	_NAME;

	/**
	副本序列
	**/
	UINT16	_Position;

	/**
	副本类型
	**/
	UINT8	_TYPE;

	/**
	副本类型名称
	**/
	string	_TYPENAME;

	/**
	等级限制
	**/
	UINT8	_Level;

	/**
	副本开启限制
	**/
	string	_PreDgns;

	/**
	进入消耗体力
	**/
	UINT32	_SpendEnergy;

	/**
	副本通关条件
	**/
	string	_PassRequire;

	/**
	地图编号序列
	**/
	string	_Maps;

	/**
	副本逻辑
	**/
	string	_Logic;

	/**
	副本评价
	**/
	string	_Evaluate;

	/**
	传出后位置
	**/
	string	_OUTPoint;

	/**
	进入副本包裹空格
	**/
	UINT8	_PackSize;

	/**
	抽奖掉落ID
	**/
	string	_AwardLoots;

	/**
	通关经验
	**/
	UINT32	_dwExp;

	/**
	通关修为
	**/
	UINT32	_dwPExp;

	/**
	通关掉落ID
	**/
	UINT32	_dwLoots;

	/**
	付费掉落Id2
	**/
	UINT32	_dwLoots2;

	/**
	付费掉落Id3
	**/
	UINT32	_dwLoots3;

	/**
	加速扫荡所需仙石
	**/
	UINT32	_dwSweepingCoin;

	/**
	扫荡时间（单位秒）
	**/
	UINT32	_dwSweepingTime;

	/**
	副本切页
	**/
	UINT32	_ECTYPE_PAGE;

	/**
	切页内位置
	**/
	UINT32	_PAGE_POS;

	/**
	关卡的物品掉落预览
	**/
	string	_ItemDrop;

	/**
	组队副本最小人数
	**/
	UINT32	_Min;

	/**
	组队副本最大人数
	**/
	UINT32	_Max;

	/**
	是否可以扫荡
	**/
	UINT8	_IsSweeping;

	/**
	是否隐藏
	**/
	UINT8	_Hide;

	/**
	是否隐藏退出按钮
	**/
	UINT8	_HideBtn;

	/**
	副本类型2
	**/
	UINT8	_Type2;

	/**
	副本出现条件
	**/
	UINT32	_AppearCondId;

	/**
	特殊道具展示
	**/
	UINT32	_SpeiceAward;
}; // SDungeonCFG define end

//data loader for the excel table
class CDungeonLoader
{
public:
	std::vector<SDungeonCFG*> _vecData;

	~CDungeonLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

