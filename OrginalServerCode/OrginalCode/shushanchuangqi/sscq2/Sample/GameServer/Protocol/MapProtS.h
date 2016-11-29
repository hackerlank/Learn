#pragma once
#include "MapProtSvr.h"

using namespace NMapProt;

class CPlayer;
class CMapProtS : public CMapProtSvr
{
    public:
        //接收：角色移动请求
        virtual void OnRecv_PlayerMoveReq(
                UINT16 wMapID, //地图ID
                const TVecPosition& vecPosition //移动位置列表
                );

        //接收：角色停止移动
        virtual void OnRecv_PlayerStopReq(
                UINT16 wMapID, //地图ID
                const SPosition& StopPos //停止点
                );

        //接收：获取玩家的外观信息
        virtual bool OnRecv_GetPlayerAppear(
                UINT64 qwUserID, //目标玩家ID
                shared_func<SGetPlayerAppearAck>& fnAck //返回回调函数
                );

        //接收：请求跳地图
        virtual bool OnRecv_JumpMap(
                UINT16 wMapID, //地图ID
                UINT8 byIndex, //地图序号,255表示任意地图
                shared_func<SJumpMapAck>& fnAck //返回回调函数
                );

        //接收：请求地图负载
        virtual bool OnRecv_GetMapOverLoad(
                UINT16 wMapID, //地图ID
                shared_func<SGetMapOverLoadAck>& fnAck //返回回调函数
                );




        ////////////////////////////////////////////////////////////////////////
        void NotifyPlayerAppear(TVecUINT64& rVecUsrID, CPlayer& rPlayer, bool bBorn);
        void NotifyCreatureDisappear(TVecUINT64& rVecUsrID, CCreature& rCreature, bool bFade);
        void NotifySurroundAppear(CPlayer& rPlayer, set<CBaseObjPtr>& rSetObj);
        void NotifySurroundDisappear(CPlayer& rPlayer, set<CBaseObjPtr>& rSetObj);
        void NotifyCreatureMove(CPlayer& rPlayer, CCreature& rCreature);

        void NotifyUserEnterMap(CPlayer& rPlayer,CGameMapPtr pMap);
        void NotifyNpcAppear(TVecUINT64& rVecUsrID, CNpc& rNpc, bool bBorn);
        void NotifyMonsterAppear(TVecUINT64& rVecUsrID, CMonster& rMonster, bool bBorn);
        void NotifyMonsterChange(TVecUINT64& rVecUsrID, CMonster& rMonster);


        void NotifySwitcherAppear(TVecUINT64& rVecUsrID, CSwitcher& rSwitcher, bool bBorn);
        void NotifySwitcherDisappear(TVecUINT64& rVecUsrID, CSwitcher& rSwitcher, bool bFade);

        void NotifyBlockerAppear(TVecUINT64& rVecUsrID, CBlocker& rBlocker, bool bBorn);
        void NotifyBlockerDisappear(TVecUINT64& rVecUsrID, CBlocker& rBlocker, bool bFade);
        void NotifyGatherAppear(TVecUINT64& rVecUsrID, IGather& rGather, bool bBorn);
        void NotifyGatherDisappear(TVecUINT64& rVecUsrID, IGather& rGather, bool bFade);
        void NotifyGatherChange(TVecUINT64& rVecUsrID, IGather& rGather);

        void NotifyAreaAppear(TVecUINT64& rVecUsrID, CMapArea& rMapArea);
        void NotifyAreaDisappear(TVecUINT64& rVecUsrID, CMapArea& rMapArea);

};
