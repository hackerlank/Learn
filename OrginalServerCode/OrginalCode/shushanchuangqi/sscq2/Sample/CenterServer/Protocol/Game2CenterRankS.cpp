// =====================================================================================
//
//       Filename:  Game2CenterRankS.cpp
//
//    Description:  排行榜内部交互
//
//        Version:  1.0
//        Created:  09/04/2014 03:25:52 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================


#include "Game2CenterRankS.h"
#include "RankProt.h"
#include "RankMgr.h"

using namespace NRankProt;

CGame2CenterRankS::~CGame2CenterRankS()
{
}

//接收：更新排名信息
void CGame2CenterRankS::OnRecv_UpdateRankInfo(
        NRankProt::ERankType eType, //更新类型
        UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
        const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
        ) 
{
    CRankMgr::Instance().UpdateRankInfo(qwInstID, eType, vecRankInfo);
}

//接收：更新所有待更新的等级信息
void CGame2CenterRankS::OnRecv_UpdateAllLevelInfo(
        const TVecUINT64& vecRoleID, //玩家ID
        const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
        )
{
    TVecRankInfo vecRankInfo2;
    vecRankInfo2.resize(1);
    auto it = vecRoleID.begin();
    auto it2 = vecRankInfo.begin();
    while(it != vecRoleID.end() && it2 != vecRankInfo.end())
    {
        vecRankInfo2[0] = *it2;
        CRankMgr::Instance().UpdateRankInfo(*it, eRTLevel, vecRankInfo2);
        ++it;
        ++it2;
    }
}
