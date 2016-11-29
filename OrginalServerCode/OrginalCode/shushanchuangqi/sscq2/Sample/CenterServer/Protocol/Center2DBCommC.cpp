#include "stdafx.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "ArenaManager.h"
#include "GuildMgr.h"
#include "GuildUserMgr.h"
#include "GuildUser.h"
#include "RankMgr.h"
#include "TripodManager.h"
#include "GuildXiheManager.h"
#include "PHPProtS.h"
#include "ShipManager.h"
#include "GodMonsterMgr.h"

/////////////////////////////////////////////////////////////////////////////

void CCenter2DBCommC::TimerCheck()
{
    if(!_bDBInited)
        Send_GetStatus([this](UINT8 byRet_ //0为成功，1为失败，2为超时
                    ){
            if(byRet_ == 0)
            {
                if(!_bDBInited)
                {
                    _bDBInited = true;
                    Config.OnDBInited();
                }

                if(!_bTimerClosed)
                {
                    _bTimerClosed = true;
                    if(!NetInterface::CloseTimer(CTimerMgr::Instance().GetInitTimer()))
                        LOG_CRI << "CloseTimer fails!";
                }
            }
        });
}
//接收：返回所有玩家ID和名字
void CCenter2DBCommC::OnRecv_SendAllUserIDAndName(
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	)
{
    g_PHPProtS.RecvAllUserIDAndName(dwTotalSize, vecUserIDAndName); 
}

//接收：返回所有公告
void CCenter2DBCommC::OnRecv_SendAllNotice(
		const NPHPProt::TVecNotice& vecNotice //公告内容
	)
{
    g_PHPProtS.RecvAllNotice(vecNotice); 
}

//接收：返回请求斗剑信息
void CCenter2DBCommC::OnRecv_SendAllArena(
        UINT32 dwPageSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NArenaGS::TVecArenaPlayerData& vecSendData //更新信息
        )
{
    CArenaManager::RecieveDBData(dwPageSize,dwTotalSize,vecSendData);
}

//接收：返回请求帮派供奉人数
void CCenter2DBCommC::OnRecv_RankInitNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NRankProt::TVecRankInfo& vecRankInfo //更新信息
        )
{
    CRankMgr::Instance().InitRankFromDB(vecRankInfo);
    if (dwCurSize >= dwTotalSize)
    {
        Config.SetInited(eDBInitRank);
        if (Config.IsSomeInited(eDBPlatformParam))
            CRankMgr::Instance().UpdatePlatform();
    }

}
//接收：返回请求崇拜数据
void CCenter2DBCommC::OnRecv_AdoreInitNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
        )
{
    if (dwCurSize >= dwTotalSize)
        Config.SetInited(eDBInitAdore);
    CRankMgr::Instance().InitAdoreFromDB(vecAdoreInfo);
}

//接收：返回所有九疑鼎信息
void CCenter2DBCommC::OnRecv_SendAllTripod(
        UINT32 dwPageSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NTripodProt::TVecTripodData& vecSendData //更新信息
        )
{
    TripodManager.RecieveDBData(dwPageSize, dwTotalSize, vecSendData);
}

//接收：返回所有九疑鼎信息
void CCenter2DBCommC::OnRecv_SendAllTripodHelper(
    UINT32 dwPageSize, //已发送条数
    UINT32 dwTotalSize, //总条数
    const NTripodProt::TVecTripodHelp& vecSendData //更新信息
        )
{
    TripodManager.RecieveDBData(dwPageSize, dwTotalSize, vecSendData);
}

//接收：返回所有九疑鼎的动态信息
void CCenter2DBCommC::OnRecv_SendAllTripodLog(
        UINT32 dwPageSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NTripodProt::TVecTripodLog& vecSendData //更新信息
        )
{
    TripodManager.RecieveDBData(dwPageSize, dwTotalSize, vecSendData);
}

//接收：平台参数加载返回
void CCenter2DBCommC::OnRecv_PlatformParamInfoNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
        const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
        )
{
    CUserMgr::InitPlatformParam(dwCurSize, dwTotalSize, vecRoleID, vecPlatformParam);
    if (dwCurSize >= dwTotalSize)
    {
        Config.SetInited(eDBPlatformParam);
        if (Config.IsSomeInited(eDBInitRank))
            CRankMgr::Instance().UpdatePlatform();
    }
}
//接收：返回查询结果
void CCenter2DBCommC::OnRecv_SendResult2Cent(
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	)
{
    const UINT8 byLevel = sCond.byLevel;
    if(byLevel <= 0)
        return;
    TVecUINT64 vecRoleID = sResult.vecPlayerID;
    TSetUINT64 setRoleID;
    for(auto &it : vecRoleID)
    {
        setRoleID.insert(it);
    }
    //CUserMgr::SetRoleIDs(byLevel,setRoleID);
}

void CCenter2DBCommC::OnRecv_SendAllShip(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
	) 
{
    g_ShipManager.ReciveDBShip(dwPageSize,dwTotalSize,vecSendDate);
}

//接收：返回机器人天梯排行信息
void CCenter2DBCommC::OnRecv_SendAllRobot(
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	) 
{

    CArenaManager::OnRecv_SendAllRobot(vecRobot);

}


