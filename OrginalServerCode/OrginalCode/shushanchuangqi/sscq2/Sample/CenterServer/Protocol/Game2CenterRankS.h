// =====================================================================================
//
//       Filename:  Game2CenterRankS.h
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

#ifndef GAME_2_CENTER_RANK_S_H
#define GAME_2_CENTER_RANK_S_H

#include "Game2CenterRankSvr.h"

using namespace NGame2CenterRank;

class CGame2CenterRankS: public CGame2CenterRankSvr
{
    public:
        virtual ~CGame2CenterRankS();

        //接收：更新排名信息
        virtual void OnRecv_UpdateRankInfo(
                NRankProt::ERankType eType, //更新类型
                UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
                const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
                );

        //接收：更新所有待更新的等级信息
        virtual void OnRecv_UpdateAllLevelInfo(
                const TVecUINT64& vecRoleID, //玩家ID
                const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
                );

};

#endif //#ifndef GAME_2_CENTER_RANK_S_H

