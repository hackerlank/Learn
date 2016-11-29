#include "stdafx.h"

#include "BattleGSS.h"

#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "MonsterMgr.h"
#include "Monster.h"
#include "Dungeon.h"
#include "PlayerDgn.h"
#include "Battle.h"
#include "GUIDMgr.h"
#include "GameNetMgr.h"
#include "HeroFighter.h"

#ifdef _DEBUG
#include "Directory.h"
#endif

void AttackCreature(CUser& rUser,UINT64 qwDefenseID)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();

    EGUIDType eType =  CGUIDMgr::GetType(qwDefenseID);
    pPlayer->GetWalker().Abort();

    if(eType == GUID_MONSTER) // 怪物
    {
        CMonsterPtr pMonster = CMonsterMgr::GetMonster(qwDefenseID);
        if(pMonster)
            pMonster->FighterToOther(*pPlayer);
        return;
    }
    
    if(eType != GUID_ROLE) 
        return;

    // 攻击具体某个人
    
    TVecBattleFighterPtr vecBattleFighter;
    pPlayer->GetBattleFighterList(vecBattleFighter);
 
    CUserPtr pOtherUser =  CUserMgr::GetUserByUserID(qwDefenseID);
    if(pOtherUser == NULL)
        return ;
    CPlayerPtr pOtherPlayer = pOtherUser->GetPlayer();
    if (!pOtherPlayer)
        return;

    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    vecvecBattleFighter2.resize(1);
    pOtherPlayer->GetBattleFighterList(vecvecBattleFighter2[0]); 

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));

    pBS->PutFighters(1, pOtherPlayer->GetMainFighter()->GetInstID(), pOtherPlayer->GetLevel(), vecvecBattleFighter2[0], pOtherPlayer->GetRoleID());
    pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());

    pBS->PutScene(pPlayer->GetSceneFighter());

    pBS->Start(EBTMonster);

    std::string strReport;
    pBS->GetReport(strReport);

    pPlayer->SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID()));
 
    pPlayer->SetBattleType(EBTINVALID);
}

//接收：请求战斗
void CBattleGSS::OnRecv_BattleReq(
        UINT64 qwDefenseID //防守ID
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return;
    AttackCreature(*pUser,qwDefenseID);
}

//接收：请求战报
void CBattleGSS::OnRecv_BattleReportReq(
        UINT64 qwReportID, //请求战报ID
        UINT64 qwMasterID //视角角色ID
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
        return;
    GetBattleReport(qwReportID, 
            [qwMasterID,pPlayer](string* pstrData)
            {
#ifdef _DEBUG
                CInArchive ar(*pstrData);
                NBattleGS::SBattleReport sReport;
                ar >> sReport;
                CreateDirectory("BattleProtocol");
                ostringstream ostrName;
                ostrName << sReport.qwBattleID << ".xml";
                TiXmlElement* pElement = new TiXmlElement(ostrName.str().c_str());
                if(pElement)
                {
                    if(ToXML(sReport, *pElement))
                    {
                        TiXmlDocument doc;
                        TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
                        if(pDecl)
                        {
                            doc.LinkEndChild(pDecl);
                            doc.LinkEndChild(pElement);
                            ostrName.str("");
                            ostrName << "BattleProtocol/" << sReport.qwBattleID << ".xml";
                            doc.SaveFile(ostrName.str().c_str());
                        }
                    }
                }
#endif
                if (pstrData)
                    pPlayer->SendPkg(g_BattleGSS.BuildPkg_BattleReportData(*pstrData, qwMasterID, 0));
            });
}

void CBattleGSS::OnRecv_FinishBattleReport(
        UINT64 qwReportID //请求战报ID
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
        return;
    pPlayer->CheckLastPend(PendBattle);
    pPlayer->CleanBattleCD();
    pPlayer->OnFighterEnd(); 
    CDungeonPtr pDgn = pPlayer->GetDgn();
    if(pDgn && (pDgn->GetDgnType() == ePlayerDgn || pDgn->GetDgnType() == eGatherDgn))
    {
        CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDgn);
        if(pPlayerDgn)
            pPlayerDgn->PlayerRelive();

    }

}

