#pragma once
#include "RoleEventSvr.h"

using namespace NRoleEvent;

class CRoleEventS : public CRoleEventSvr
{
    public:

        /////////////////////以下的接收函数需要重载/////////////////////
#if 0
        //接收：玩家角色数据加载完毕，进入地图
        virtual void OnRecv_RoleLoadDataOver(
                UINT8 bySuc //玩家加载数据结果，0表示ok
                ) ;
#endif
    //接收：获取角色面板信息
    virtual bool OnRecv_GetRoleSpecInfo(
        shared_func<SGetRoleSpecInfoAck>& fnAck //返回回调函数
    );
	//接收：取得散仙列表
	virtual bool OnRecv_GetFighters(
		shared_func<SGetFightersAck>& fnAck //返回回调函数
	);
	//接收：存储新手引导信息
	virtual bool OnRecv_StoreGuide(
		const std::string& strGuide, //引导步骤信息
		shared_func<SStoreGuideAck>& fnAck //返回回调函数
	);
	//接收：获取角色Buff信息
	virtual bool OnRecv_GetRoleBuffInfo(
		shared_func<SGetRoleBuffInfoAck>& fnAck //返回回调函数
	);

};
