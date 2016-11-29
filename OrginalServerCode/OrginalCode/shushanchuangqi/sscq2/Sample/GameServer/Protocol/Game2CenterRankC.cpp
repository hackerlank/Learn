// =====================================================================================
//
//       Filename:  Game2CenterRankC.cpp
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

#include "Game2CenterRankC.h"
#include "UserMgr.h"
#include "User.h"
#include "Player.h"

CGame2CenterRankC::~CGame2CenterRankC()
{

}

//接收：获取玩家的外观信息
bool CGame2CenterRankC::OnRecv_GetFeature(
        UINT64 qwRoleID, //玩家唯一ID
        shared_func<SGetFeatureAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser)
    {
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (pPlayer)
        {
            fnAck->byError = 0;
            fnAck->strName = pPlayer->GetName();
            fnAck->wLevel = pPlayer->GetLevel();
            fnAck->pFeature = pPlayer->GetAppearFeature();
            return true;
        }
        else
            fnAck->byError = 1;
    }
    else
    {
        CUserMgr::LoadUser(qwRoleID,
                [this, qwRoleID, fnAck](CUserPtr pUser)
                {
                    if (pUser)
                    {
                        CPlayerPtr pPlayer = pUser->GetPlayer();
                        if (pPlayer)
                        {
                            fnAck->strName = pPlayer->GetName();
                            fnAck->wLevel = pPlayer->GetLevel();
                            fnAck->pFeature = pPlayer->GetAppearFeature();
                            fnAck->byError = 0;
                            fnAck(true);
                        }
                        else
                            fnAck(false);
                    }
                    else
                    {
                        fnAck->byError = 1;
                        fnAck(false);
                    }
                });
    }
    return false;
}
