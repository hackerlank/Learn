// =====================================================================================
//
//       Filename:  Game2CenterRankC.h
//
//    Description:  排行榜内部通讯协议
//
//        Version:  1.0
//        Created:  09/04/2014 03:31:47 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GAME_2_CENTER_RANK_C_H
#define GAME_2_CENTER_RANK_C_H

#include "Game2CenterRankClt.h"

using namespace NGame2CenterRank;

class CGame2CenterRankC: public CGame2CenterRankClt
{
    public:
        virtual ~CGame2CenterRankC();

        //接收：获取玩家的外观信息
        virtual bool OnRecv_GetFeature(
                UINT64 qwRoleID, //玩家唯一ID
                shared_func<SGetFeatureAck>& fnAck //返回回调函数
                );

};

#endif // #ifndef GAME_2_CENTER_RANK_C_H

