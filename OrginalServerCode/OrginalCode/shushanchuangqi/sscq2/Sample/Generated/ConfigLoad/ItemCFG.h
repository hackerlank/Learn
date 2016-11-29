// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CITEMLOADER_H
#define _CITEMLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SItemCFG
{
	/**
	道具ID
	**/
	UINT16	_ID;

	/**
	道具名称
	**/
	string	_Name;

	/**
	道具类型
	**/
	UINT16	_Type;

	/**
	使用等级
	**/
	UINT8	_Level;

	/**
	物品等级
	**/
	UINT8	_LevelValue;

	/**
	激活条件
	**/
	UINT16	_Cond;

	/**
	道具品质
	**/
	UINT8	_Quality;

	/**
	堆叠数量
	**/
	UINT16	_Stack;

	/**
	职业要求
	**/
	UINT8	_Job;

	/**
	是否可使用
	**/
	UINT8	_Useable;

	/**
	弹出界面
	**/
	UINT16	_UseableOpen;

	/**
	是否可合成
	**/
	UINT8	_UpgradeAble;

	/**
	弹出界面
	**/
	UINT16	_UpgradeAbleOpen;

	/**
	是否弹出提示
	**/
	UINT8	_Push;

	/**
	出售价格
	**/
	UINT32	_SellPrice;

	/**
	拍卖行最低价
	**/
	UINT32	_ExchangePrice;

	/**
	出售上限
	**/
	UINT16	_Saleup;

	/**
	绑定类型
	**/
	UINT8	_Binding;

	/**
	属性索引
	**/
	UINT16	_AttrIdx_1;

	/**
	属性索引
	**/
	UINT16	_AttrIdx_2;

	/**
	属性索引
	**/
	UINT16	_AttrIdx_3;

	/**
	入鼎值
	**/
	UINT16	_Energy;

	/**
	熔炼值
	**/
	UINT16	_TrumpExp;

	/**
	好感度
	**/
	UINT16	_Goodwill;

	/**
	任务
	**/
	UINT16	_QuestData;

	/**
	引导副本Id
	**/
	UINT16	_GuiDgn;

	/**
	附魔
	**/
	UINT16	_Enchant;

	/**
	限时ID
	**/
	UINT16	_ItemTimeID;

	/**
	模型
	**/
	UINT16	_Model;

	/**
	使用次数
	**/
	UINT8	_UseTimes;

	/**
	宝石等级
	**/
	UINT8	_StoneLevel;

	/**
	宝箱道具类书
	**/
	UINT8	_RequiredPackSpace;

	/**
	宝箱道具个数
	**/
	UINT8	_RequiredPackTypeNum;

	/**
	单人装备互斥
	**/
	string	_EquipConflict;

	/**
	队伍装备互斥
	**/
	string	_EquipConflictTeam;
}; // SItemCFG define end

//data loader for the excel table
class CItemLoader
{
public:
	std::vector<SItemCFG*> _vecData;

	~CItemLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

