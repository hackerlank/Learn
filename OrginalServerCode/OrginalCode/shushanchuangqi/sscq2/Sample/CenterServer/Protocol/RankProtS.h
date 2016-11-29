// =====================================================================================
//
//       Filename:  RankProtS.h
//
//    Description:  排名协议处理类
//
//        Version:  1.0
//        Created:  09/04/2014 10:47:05 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef RANK_PROT_S_H
#define RANK_PROT_S_H

#include "RankProtSvr.h"

using namespace NRankProt;

class CRankProtS : public CRankProtSvr
{
    public:
        virtual ~CRankProtS();

        //接收：获取排行榜数据
        virtual bool OnRecv_GetRankInfo(
                ERankType eType, //排行榜类型
                UINT32 dwIndex, //排名索引
                UINT32 dwCount, //排名个数
                shared_func<SGetRankInfoAck>& fnAck //返回回调函数
                );
        //接收：获得崇拜数量
        virtual bool OnRecv_GetAdoreCount(
                UINT64 qwRoleID, //玩家ID
                shared_func<SGetAdoreCountAck>& fnAck //返回回调函数
                );
        //接收：崇拜玩家
        virtual bool OnRecv_AdorePlayer(
                UINT64 qwRoleID, //玩家ID
                shared_func<SAdorePlayerAck>& fnAck //返回回调函数
                );
        //接收：获得玩家外观信息
        virtual bool OnRecv_GetPlayerFeature(
                UINT64 qwRoleID, //玩家ID
                shared_func<SGetPlayerFeatureAck>& fnAck //返回回调函数
                );
};

#endif // #ifndef RANK_PROT_S_H

