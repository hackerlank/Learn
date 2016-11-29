#pragma once
#include "TitleProtSvr.h"
using namespace NTitleProt;

class CTitleProtS : public CTitleProtSvr
{
public:
    //接收：得到当前所有称号
	virtual bool OnRecv_GetAllTitle(
		shared_func<SGetAllTitleAck>& fnAck //返回回调函数
	) ;
	//接收：装备称号
	virtual bool OnRecv_EquipTitle(
		UINT16 wId, //称号ID
		UINT8 byPos, //装备位置,0表示任意位置
		shared_func<SEquipTitleAck>& fnAck //返回回调函数
	) ;
public:
	void SendSysMsgIDNotify(ETitleResult eResult);
};
