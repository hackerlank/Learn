#include "stdafx.h"
#include "ChatProtS.h"
#include "Chat.h"
#include "User.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "Bubble.h"
#include "GameServerSysMail.h"
#include "Parameter.h" 
#include "Loot.h"
#include "Game2CenterCommC.h"
#include "GameNetMgr.h"

extern CGame2CenterCommC g_Game2CenterCommC;
//接收：聊天
void CChatProtS::OnRecv_Chat(
        NGlobalChatProt::EChannelType eChannelType, //通道类型
        const std::string& strInfo, //聊天信息
        const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return;
    UINT64 qwUsrID = pUser->GetUserID();
    //if(CUsrForbidMgr::IsForbidTalk(qwUsrID))
    // TODO:
    // if (pUser->GetForb() && )
    {
        g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID, 1, eMsgSysChatForbid);
        return;
    }
    CChat::Chat(*pUser, eChannelType, strInfo, vecShowInfo);
}

/*
//接收：聊天展示
bool CChatProtS::OnRecv_ChatShowItem(
UINT64 qwRoleID, //角色ID(0:自己)
UINT64 qwInstID, //道具ID
shared_func<SChatShowItemAck>& fnAck //返回回调函数
)
{
// TODO:
CUserPtr pUser;
if(!NetMgr.GetCurUser(&pUser))
return;
if (!qwRoleID)
qwRoleID = pUser->GetUserID();
switch(CGUIDMgr::GetType(qwInstID))
{
case GUID_HERO :
{
CPlayerPtr pPlayer = pUser->GetPlayer();
CFighterManagerPtr& pFighterManagerPtr = pPlayer->GetFighterManager();
CFighterPtr pFighter = GetFighterByInstID(qwInstID);
if (!pFighter)
fnAck->eResult = eChatNotExist;
}
break;
case GUID_ITEM :
break;
case GUID_EQUIP:
break;
}
return fnAck->eResult == eChatSucceed;
}
*/

//接收：气泡信息获取
bool CChatProtS::OnRecv_BubbleGet(
        shared_func<SBubbleGetAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CBubbleOwnerPtr pBubbleOnwer = pUser->GetBubbleOwner();
    if (pBubbleOnwer)
        return pBubbleOnwer->GetAllInfo(fnAck->vecBubbleInfo);
    return false;
}

// 接收：气泡回应
bool CChatProtS::OnRecv_BubbleRespond(
        UINT16 wIndex, //气泡对应位置
        const TVecINT64& vecParam, //整型变量
        const TVecString& vecString, //字符串型变量
        shared_func<SBubbleRespondAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CBubbleOwnerPtr pBubbleOnwer = pUser->GetBubbleOwner();
    if (pBubbleOnwer)
    {
        if (pBubbleOnwer->Respond(wIndex, vecParam, vecString))
        {
            fnAck->eResult = eBRSuccess;
            return true;
        }
        else
            pBubbleOnwer->NotifyAllInfo();
    }
    else
    {
        fnAck->eResult = eBRFailed;
        return false;
    }
    return true;
}

//接收：邀请平台好友成功
void CChatProtS::OnRecv_InviteSuc(
        UINT64 qwRoleID //被邀请人
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return ;

    //好友邀请发送center
    pUser->SendCenterSvrPkg(g_Game2CenterCommC.BuildPkg_InviteFriend(pUser->GetUserID(),qwRoleID));

    if(pUser->GetVars().GetVar(NVarDefine::ePlayerGetInvite) > 0)
        return;
    pUser->GetVars().SetVar(NVarDefine::ePlayerGetInvite,1);
    //发送鼓励邮件
    std::vector<SItemGenInfo> vecMailInfo;
    TVecResource vecRes;
    UINT32 dwDropId = SParamConfig::wInventFriendsGoods; //(*iter);
    LOOT.Roll(dwDropId, vecMailInfo,vecRes);
    for(auto it = vecRes.begin();it != vecRes.end();++it)
    {
        SItemGenInfo tepInfo;
        SResource &rRes = *it;
        tepInfo.wItemID = rRes._eRes;
        tepInfo.dwCount = rRes._dwValue;
        vecMailInfo.push_back(tepInfo);
    }
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_INVITE_SUC;
    TVecUINT64 vecTargets;
    vecTargets.push_back(pUser->GetUserID());
    GameServerSysMail::SendSysMail(SNED_INVITE_SUC,TITLE_INVITE_SUC,stBody,vecTargets,&vecMailInfo);

}


