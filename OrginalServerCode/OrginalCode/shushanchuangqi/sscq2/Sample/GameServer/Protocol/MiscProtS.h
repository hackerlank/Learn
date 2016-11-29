#pragma once

#include "MiscProtSvr.h"

#include "stdafx.h"

using namespace NMiscProt;

class CMiscProtS : public CMiscProtSvr
{
    public:
        //接收：设置防沉迷状态
        virtual void OnRecv_SetIndulge(
                bool bIndulge //设置防沉迷状态
                );
        
        //接收：设置防沉迷收益率
        virtual void OnRecv_SetIndulgeRate(
                UINT32 dwIndulgeRate //设置防沉迷收益率
                );

        //接收：购买体力
        virtual bool OnRecv_BuyAction(
                shared_func<SBuyActionAck>& fnAck //返回回调函数
                );

        //接收：获取购买体力次数
        virtual bool OnRecv_GetBuyActionCount(
                shared_func<SGetBuyActionCountAck>& fnAck //返回回调函数
                );

        //接收：获取体力buff数值
        virtual void OnRecv_GetActionBuff(
                );

        //接收：发送udplog
        virtual void OnRecv_SendUdpLog(
                const std::string& strParam1, //参数1
                const std::string& strParam2 //参数2
                );


        //接收：获取货币基础数值
        virtual bool OnRecv_GetMoneyList(
                shared_func<SGetMoneyListAck>& fnAck //返回回调函数
                );

        //接收：领取体力buff
        virtual void OnRecv_TakeActionBuff(
                );

        //接收：客户端黑屏Log
        virtual void OnRecv_ClientBlankScreenLog(
                const std::string& strParam1 //参数1
                );
        //接收：天赐宝箱
        virtual void OnRecv_OnEnter(
                );

        //接收：获得回合数和活动状态
        virtual void OnRecv_GetRount(
                );

        //接收：玩家抽奖
        virtual bool OnRecv_Draw(
                shared_func<SDrawAck>& fnAck //返回回调函数
                );

        //接收：客户端通知动画播放完毕
        virtual void OnRecv_DrawRet(
                );

        //接收：同步客户端玩家抽奖
        virtual void OnRecv_SendLottery(
                UINT32 dwTotalNum, //总的抽奖信息条数
                UINT32 dwSelfNum //自己的抽奖信息条数
                );
        //接收：获取每日冲值奖励
        virtual bool OnRecv_GetEveryDayRechargeAward(
                shared_func<SGetEveryDayRechargeAwardAck>& fnAck //返回回调函数
                ); 

            //接收：获取每日冲值金额
            virtual bool OnRecv_GetEveryDayRecharge(
                    shared_func<SGetEveryDayRechargeAck>& fnAck //返回回调函数
                    ) ;

            //接收：分宝岩购买活动
            virtual bool OnRecv_BuyFenbaoyan(
                    UINT16 wNum, //购买数量
                    shared_func<SBuyFenbaoyanAck>& fnAck //返回回调函数
                    );
           //接收：分宝岩购买活动时间
          virtual bool OnRecv_FenbaoyanTime(
                  shared_func<SFenbaoyanTimeAck>& fnAck //返回回调函数
                  );
};
extern CMiscProtS g_MiscProtS;
