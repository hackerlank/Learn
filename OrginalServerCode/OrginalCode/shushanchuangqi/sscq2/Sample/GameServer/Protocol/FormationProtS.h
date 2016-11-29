
#pragma once
#include "FormationProtSvr.h"

using namespace NFormationProt;

class CFormationProtS : public CFormationProtSvr
{
public:
	//接收：上阵/下阵
	virtual bool OnRecv_FormationUp(
		UINT64 qwInstID, //散仙唯一ID
		INT32 iPos, //目标位置: [0-8]为上阵 <0时为下阵
		shared_func<SFormationUpAck>& fnAck //返回回调函数
	);
    //接收：设置阵形
	virtual bool OnRecv_SetFormation(
		const TVecSLineup& vecSLineup, //阵形列表
		shared_func<SSetFormationAck>& fnAck //返回回调函数
	);

	//接收：取得所有阵灵信息
	virtual bool OnRecv_PetsGet(
		shared_func<SPetsGetAck>& fnAck //返回回调函数
	);
	//接收：激活阵灵
	virtual bool OnRecv_PetsActive(
		UINT16 wPetID, //阵灵ID
		shared_func<SPetsActiveAck>& fnAck //返回回调函数
	);
	//接收：设置阵灵状态
	virtual bool OnRecv_PetsStatus(
		UINT16 wPetID, //阵灵ID
		UINT8 byType, //状态: 1-出战且显示 2-出战隐藏
		shared_func<SPetsStatusAck>& fnAck //返回回调函数
	);
	//接收：阵灵幻化
	virtual bool OnRecv_PetsUpgrade(
		UINT16 wPetID, //阵灵ID
		shared_func<SPetsUpgradeAck>& fnAck //返回回调函数
	);
	//接收：阵灵升级
	virtual bool OnRecv_PetsLevelUp(
		UINT16 wPetID, //阵灵ID
		UINT8 byType, //状态: 1-出战且显示 2-出战隐藏
		shared_func<SPetsLevelUpAck>& fnAck //返回回调函数
	);

	//接收：获取兽魂信息
	virtual bool OnRecv_GetBeastSoul(
		shared_func<SGetBeastSoulAck>& fnAck //返回回调函数
	);

	//接收：升级兽魂
	virtual bool OnRecv_UpgradeBeastSoul(
		NRoleInfoDefine::EBeastSoulType eType, //兽魂种类
		shared_func<SUpgradeBeastSoulAck>& fnAck //返回回调函数
	);

    //接收：阵灵一键升级
	virtual bool OnRecv_QuickPetsLevelUp(
		UINT16 wPetID, //阵灵ID
		shared_func<SQuickPetsLevelUpAck>& fnAck //返回回调函数
	);

private:
};
