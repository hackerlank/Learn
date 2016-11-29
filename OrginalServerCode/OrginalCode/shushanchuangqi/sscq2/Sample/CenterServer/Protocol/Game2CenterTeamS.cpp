#include "Protocols.h"
#include "UserMgr.h"
#include "UserInfoMgr.h"
#include "SystemMail.h"
#include "Game2CenterTeamS.h"
#include "TeamMananger.h"
#include "ArenaManager.h"

CGame2CenterTeamS g_Game2CenterTeamS;

//接收：同步队伍成员
void CGame2CenterTeamS::OnRecv_SynTeamFighter(
        UINT64 qwUsrID, //帐号ID
        const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
        )
{
    //更新斗剑
    for(auto pos = vecFighter.begin();pos != vecFighter.end();pos ++)
    {
        TeamFighterPtr pSubFighter = *(pos);
        if(pSubFighter->GetClassType() != eType_CommonFighter)
        {
            continue;
        }
        CommonFighterPtr pSubCommon = dynamic_pointer_cast<CommonFighter>(pSubFighter);
        if(pSubCommon == NULL)
        {
            LOG_CRI<<"TransERR";
            continue;
        }
        if(pSubCommon->pFeature != NULL  && pSubCommon->pFeature->GetClassType() == NBattleGS::eType_SPlayerFeature)
        {
            NBattleGS::SPlayerFeaturePtr pFeature = dynamic_pointer_cast<NBattleGS::SPlayerFeature>(pSubCommon->pFeature);
            if(pFeature)
            {
                SArenaPlayerData * pPlayer = CArenaManager::GetPlayer(qwUsrID);
                if(pPlayer)
                {
                    pPlayer->stFighter.stAppear  = *pFeature;
                }
            }
        }

    }
    CMemInfo *pMember = g_TeamManager.GetRoleInfoByID(qwUsrID);
    if(pMember == NULL)
    {
        return ;
    }
    bool bUpdate = false;
    TVecTeamFighter& rvecFighters = pMember->GetFighters();
    for(auto it = vecFighter.begin();it != vecFighter.end() ;it++)
    {
        TeamFighterPtr pFighter = *(it);
        switch(pFighter->GetClassType())
        {
            case eType_CommonFighter://普通将
                {
                    CommonFighterPtr pCommon = dynamic_pointer_cast<CommonFighter>(pFighter);
                    if(pCommon == NULL)
                    {
                        LOG_CRI<<"TransERR";
                        continue;
                    }
                    for(auto pos = rvecFighters.begin();pos != rvecFighters.end();pos ++)
                    {
                        TeamFighterPtr pSubFighter = *(pos);
                        if(pSubFighter->GetClassType() != eType_CommonFighter)
                        {
                            continue;
                        }
                        CommonFighterPtr pSubCommon = dynamic_pointer_cast<CommonFighter>(pSubFighter);
                        if(pSubCommon == NULL)
                        {
                            LOG_CRI<<"TransERR";
                            continue;
                        }
                        if(pSubCommon->qwInstID != pCommon->qwInstID)
                        {
                            continue;
                        }
                        pSubCommon->byLevel = pCommon->byLevel;
                        pSubCommon->pFeature = pCommon->pFeature;
                        pSubCommon->dwFighterPower = pCommon->dwFighterPower;
                        bUpdate =true;
                        break;
                    }
                }
                break;
            case eType_BeautyFighter://美女
                {
                    BeautyFighterPtr pBeauty = dynamic_pointer_cast<BeautyFighter>(pFighter);
                    if(pBeauty == NULL)
                    {
                        LOG_CRI << "TransERR";
                        continue;
                    }
                    for(auto pos = rvecFighters.begin();pos != rvecFighters.end();pos ++)
                    {
                        TeamFighterPtr pSubFighter = *(pos);
                        if(pSubFighter->GetClassType() != eType_BeautyFighter)
                            continue;
                        BeautyFighterPtr pSubBeauty = dynamic_pointer_cast<BeautyFighter>(pSubFighter);
                        if(pSubBeauty == NULL)
                        {
                            LOG_CRI<<"TransERR";
                            continue;
                        }
                        if(pSubBeauty->wFighterID != pBeauty->wFighterID)
                            continue;
                        pSubBeauty->byPos           = pBeauty->byPos;
                        pSubBeauty->pFeature        = pBeauty->pFeature;
                        pSubBeauty->dwFighterPower  = pBeauty->dwFighterPower;

                        bUpdate =true;
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }
    if(bUpdate)
        g_TeamManager.NoticeTeamInfo(pMember->GetTeamID());
}

//接收：同步增加阵灵,如果原来有阵灵，替换
void CGame2CenterTeamS::OnRecv_SynTeamAddBeauty(
        UINT64 qwUsrID, //帐号ID
        const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
        ) 
{
    CMemInfo *pMember = g_TeamManager.GetRoleInfoByID(qwUsrID);
    if(pMember == NULL)
        return ;

    bool bUpdate = false;
    bool bAdd = true;
    BeautyFighterPtr pBeauty;
    for(auto& pFighter : vecFighter)
    {
        switch(pFighter->GetClassType())
        {
            case eType_BeautyFighter://阵灵
                {
                    pBeauty = dynamic_pointer_cast<BeautyFighter>(pFighter);

                    // 寻找是否是替换
                    for(auto & pBF : pMember->GetFighters())
                    {
                        if(pBF->GetClassType() != eType_BeautyFighter)
                            continue;
                        BeautyFighterPtr pSubBeauty = dynamic_pointer_cast<BeautyFighter>(pBF);

                        pSubBeauty->wFighterID      = pBeauty->wFighterID;
                        pSubBeauty->pFeature        = pBeauty->pFeature;
                        pSubBeauty->dwFighterPower  = pBeauty->dwFighterPower;
                        pSubBeauty->byPos           = pBeauty->byPos;

                        bUpdate = true;
                        bAdd = false;
                        break;
                    }
                }
                break;
            default:
                break;
        }
        if(!bAdd)
            break;
    }

    if(bAdd && pBeauty)
    {
        BeautyFighterPtr pSubBeauty(new BeautyFighter());
        pSubBeauty->pFeature        = pBeauty->pFeature;
        pSubBeauty->dwFighterPower  = pBeauty->dwFighterPower;
        pSubBeauty->wFighterID      = pBeauty->wFighterID;
        pSubBeauty->byPos           = pBeauty->byPos;
        pMember->GetFighters().push_back(pSubBeauty);

        //设置美女
        CTeamInfo* pTeam = g_TeamManager.GetTeamInfoByID(pMember->GetTeamID());
        if(NULL == pTeam)
        {
            LOG_CRI << "Can not Find Team!";
            return ;
        }
        if(pTeam->GetBeautyOwer() == 0 && pTeam->GetLeaderID() == qwUsrID)
            pTeam->SetBeautyOwer(qwUsrID);

        bUpdate = true;
    }

    if(bUpdate)
        g_TeamManager.NoticeTeamInfo(pMember->GetTeamID());
}

//接收：同步删除美女
void CGame2CenterTeamS::OnRecv_SynTeamDelBeauty(
        UINT64 qwUsrID //帐号ID
        ) 
{
    CMemInfo *pMember = g_TeamManager.GetRoleInfoByID(qwUsrID);
    if(pMember == NULL)
        return ;

    bool bUpdate = false;
    TVecTeamFighter& rvecFighters = pMember->GetFighters();
    for(auto pos = rvecFighters.begin();pos != rvecFighters.end();pos ++)
    {
        TeamFighterPtr pSubFighter = *(pos);
        if(pSubFighter->GetClassType() != eType_BeautyFighter)
            continue;
        rvecFighters.erase(pos);
        bUpdate =true;
        break;
    }
    //设置美女
    CTeamInfo* pTeam = g_TeamManager.GetTeamInfoByID(pMember->GetTeamID());
    if(NULL == pTeam)
    {
        LOG_CRI << "Can not Find Team!";
        return ;
    }

    if(pTeam->GetBeautyOwer() == qwUsrID)
    {
        pTeam->SetBeautyOwer(0);
        bUpdate =true;
    }

    if(bUpdate)
        g_TeamManager.NoticeTeamInfo(pMember->GetTeamID());
}

//接收：同步奖励系数
void CGame2CenterTeamS::OnRecv_SynRewardRate(
        UINT32 dwRewardRate //奖励系数万分比
        )
{
    g_TeamManager.SetRewardRate(dwRewardRate);
}
