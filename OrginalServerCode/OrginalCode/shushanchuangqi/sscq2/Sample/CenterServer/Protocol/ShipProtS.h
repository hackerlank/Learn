
#pragma once
#include "ShipProtSvr.h"
using namespace NShipProt;

class CShipProtS : public CShipProtSvr
{
    public:
        //接收：获取自己显示信息
        virtual void OnRecv_GetShipSelfView(
                ) ;

        //接收：获取所有金船显示信息
        virtual bool OnRecv_GetShipList(
                shared_func<SGetShipListAck>& fnAck //返回回调函数
                ) ;

        //接收：不再关注列表
        virtual void OnRecv_DelList(
                ) ;

        //接收：获取某条船的信息
        virtual bool OnRecv_GetShipInfo(
                UINT64 qwInsID, //金船唯一ID
                shared_func<SGetShipInfoAck>& fnAck //返回回调函数
                ) ;

        //接收：获取历史信息
        virtual void OnRecv_GetShipReport(
                ) ;

        //接收：雇佣船只,开始运船
        virtual bool OnRecv_OpenShip(
                shared_func<SOpenShipAck>& fnAck //返回回调函数
                ) ;

        //接收：购买运船次数
        virtual bool OnRecv_BuyOpenShipTimes(
                shared_func<SBuyOpenShipTimesAck>& fnAck //返回回调函数
                ) ;

        //接收：购买抢劫次数
        virtual bool OnRecv_BuyRoBShipTimes(
                shared_func<SBuyRoBShipTimesAck>& fnAck //返回回调函数
                ) ;
        //接收：购买刷新次数
        virtual bool OnRecv_BuyReflushShipTimes(
                shared_func<SBuyReflushShipTimesAck>& fnAck //返回回调函数
                ) ;

        //接收：刷新船只
        virtual bool OnRecv_ReFlushShip(
                UINT8 byVip, //0,表示非vip ,非0表示vip
                shared_func<SReFlushShipAck>& fnAck //返回回调函数
                ) ;

        //接收：邀请护送船只
        virtual bool OnRecv_InViteFriend(
                UINT64 qwFriend, //好友
                shared_func<SInViteFriendAck>& fnAck //返回回调函数
                ) ;

        //接收：回应邀请护送船只
        virtual bool OnRecv_InViteOtherAgree(
                UINT8 bySuc, //0,同意，1拒绝
                UINT64 qwFriend, //好友
                UINT32 dwCode, //验证码
                shared_func<SInViteOtherAgreeAck>& fnAck //返回回调函数
                ) ;

        //接收：船主踢出护送者
        virtual bool OnRecv_FireDefense(
                UINT64 qwFriend, //好友
                shared_func<SFireDefenseAck>& fnAck //返回回调函数
                ) ;

        //接收：打劫船只
        virtual bool OnRecv_DoRoBShip(
                UINT64 qwInsID, //金船唯一ID
                shared_func<SDoRoBShipAck>& fnAck //返回回调函数
                ) ;
        //接收：返抢
        virtual bool OnRecv_DoGrapShip(
                UINT64 qwShipID, //金船唯一ID
                UINT64 qwRoBID, //打劫者ID
                shared_func<SDoGrapShipAck>& fnAck //返回回调函数
                );
        //接收：一键完成运送
        virtual bool OnRecv_FinishShipOneKey(
                shared_func<SFinishShipOneKeyAck>& fnAck //返回回调函数
                ) ;

    public:
        void SendSysMsgIDNotify(EShipResult eResult,UINT64 qwRoleId);
};
