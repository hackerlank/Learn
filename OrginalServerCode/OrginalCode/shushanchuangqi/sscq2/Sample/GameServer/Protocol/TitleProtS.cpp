#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "TitleProtS.h"
#include "GameNetMgr.h"

//接收：得到当前所有称号
bool CTitleProtS::OnRecv_GetAllTitle(
        shared_func<SGetAllTitleAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->GetTitlePkg().GetAllTitle(fnAck->vecTitle);
    return true;

}
//接收：装备称号
bool CTitleProtS::OnRecv_EquipTitle(
        UINT16 wId, //称号ID
        UINT8 byPos, //装备位置,0表示任意位置
        shared_func<SEquipTitleAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    UINT8 byCurPos =0;
    fnAck->eResult = pPlayer->GetTitlePkg().EquipTitle(wId,byPos,byCurPos);
    fnAck->wId = wId;
    fnAck->byPos = byCurPos;
    if(fnAck->eResult != eTitleSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;

}


void CTitleProtS::SendSysMsgIDNotify(ETitleResult  eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eTitleVIPLevel: //VIP等级不足
            {
                eMsgID = eMsgVIPLevelTooLow;
            }
            break;

        case eTitleNoHas : //该称号没有获得
            {
                eMsgID = eMsgTitleNoGet;
            }
            break;
        case eTitleErrOther: //其它错误
            eMsgID = eMsgTaskErrOther;
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
