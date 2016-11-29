#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "TaskMarket.h"
#include "GameServerSysMail.h" 
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "HeroFighter.h"
#include "FighterManager.h"

bool CTaskMarketMgr::Init()
{
    if(!LoadConfig())
    {
        LOG_INF <<" TaskMarket LoadConfig Err.";
        return false;
    }
    return true;
}

bool CTaskMarketMgr::LoadConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/V3Task.xml";
    CV3TaskLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oV3Task.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SV3TaskCFG* pCFG = oLoader._vecData[i];
        STaskCFGExPtr pCFGExPtr(new STaskCFGEx);
        pCFGExPtr->dwTaskID = pCFG->_ID;
        pCFGExPtr->byStep = pCFG->_StepID;
        pCFGExPtr->dwLootID = pCFG->_PrizeID;
        pCFGExPtr->dwCondID = pCFG->_CondID;
        pCFGExPtr->CopyConfig(*pCFG);
        _vecConfig.push_back(pCFGExPtr);
    }

    return true;
}

NPHPProt::ETaskState CTaskMarketMgr::CheckTask(CPlayer &rPlayer, UINT32 dwTaskID, UINT8 byStep,UINT8 byOpt)
{
    UINT64 qwRoleID = rPlayer.GetRoleID();
    STaskMarketKey oKey(qwRoleID,dwTaskID,byStep);
    STaskCFGExPtr pCfg = GetConfig(dwTaskID,byStep);
    UINT32 dwCondID = 0;
    UINT32 dwLootID = 0;
    bool bRet = false;
    if(!pCfg)
    {
        LOG_INF << "pCfg Null.";
        return NPHPProt::eTaskStateOtherErr;
    }
    dwCondID = pCfg->dwCondID;
    dwLootID = pCfg->dwLootID;
    if(!dwCondID)
    {
        LOG_INF << " dwCondID 0.";
        return NPHPProt::eTaskStateOtherErr;
    }
    switch(byOpt)
    {
        case NPHPProt::eTaskOptComplete:
            {
                bRet = CheckCond(rPlayer,dwCondID);
                if(!bRet)
                {
                    LOG_INF <<"qwRoleID("<<rPlayer.GetRoleID() <<" not complete taskID("<<dwTaskID<<").";
                    return NPHPProt::eTaskStateNoComp;
                }
            }
            break;
        case NPHPProt::eTaskOptCompAndReward:
            {
                bRet = CheckCond(rPlayer,dwCondID);
                if(!bRet)
                {
                    LOG_INF <<"qwRoleID("<<rPlayer.GetRoleID() <<" not complete taskID("<<dwTaskID<<").";
                    return NPHPProt::eTaskStateNoComp;
                }
                if(dwLootID == 0)
                {
                    LOG_INF <<" dwLootID 0.";
                    return NPHPProt::eTaskStateOtherErr;
                }
                if(_setTmp.count(oKey))
                {
                    LOG_CRI <<"TakePrize twice!";
                    return NPHPProt::eTaskStateSended;
                }
                if(!SendMail(rPlayer,dwLootID,oKey))
                {
                    LOG_INF <<"SendMail Err.";
                    return NPHPProt::eTaskStateSendErr;
                }
            }
            break;
        case NPHPProt::eTaskOptReward:
            {
                if(dwLootID == 0)
                {
                    LOG_INF <<" dwLootID 0.";
                    return NPHPProt::eTaskStateOtherErr;
                }
                if(_setTmp.count(oKey))
                {
                    LOG_CRI <<"TakePrize twice!";
                    return NPHPProt::eTaskStateSended;
                }
                if(!SendMail(rPlayer,dwLootID,oKey))
                {
                    LOG_INF <<" SendMail Err.";
                    return NPHPProt::eTaskStateSendErr;
                }
            }
            break;
        default:
            return NPHPProt::eTaskStateOtherErr;
    }
    return NPHPProt::eTaskStateSuc;
}

bool CTaskMarketMgr::SendMail(CPlayer& rPlayer,UINT32 dwLootID,STaskMarketKey& oKey)
{
    TVecUINT64 vecUserID;
    UINT64 qwRoleID = rPlayer.GetRoleID();
    if(qwRoleID)
        vecUserID.push_back(qwRoleID);
    else
    {
        LOG_INF <<"qwRoleID 0";
        return false;
    }
    _setTmp.insert(oKey); //临时记录玩家领奖数据，防止重复领奖操作
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwLootID, vecItems,vecRes);
    for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
    {
        SItemGenInfo tepInfo;
        SResource &rRes = *it;
        tepInfo.wItemID = rRes._eRes;
        tepInfo.dwCount = rRes._dwValue;
        vecItems.push_back(tepInfo);

    }
    if(!vecItems.empty())
    {

       NMailProt::SysMailSendTxt stBody;
       stBody.dwstrMsgID = BODY_TASKMARKET_ACT;
       // stBody.vecParam.push_back(NumberToString(pPlayer->dwNo));
       GameServerSysMail::SendSysMail(SEND_TASKMARKET_ACT, TITLE_TASKMARKET_ACT, stBody, vecUserID, &vecItems);
    }
    return true;
}
//策划新需求，先添加功能
#if 0
UINT32 CTaskMarketMgr::GetTaksID(const string& strTask)
{
    UINT32 dwTaskID = 0;
    for(auto it=_vecConfig.begin(); it!=_vecConfig.end(); ++it)
    {
        STaskCFGExPtr& p = *it;
        if(strTask.compare(p->_StrTaskID))
        {
            dwTaskID = p->dwTaskID;
            break;
        }
    }
    return dwTaskID;
}
#endif
STaskCFGExPtr CTaskMarketMgr::GetConfig(UINT32 dwTaskID, UINT8 byStep)
{
    for(auto it=_vecConfig.begin(); it!=_vecConfig.end(); ++it)
    {
        STaskCFGExPtr& p = *it;
        if(dwTaskID == p->dwTaskID && byStep == p->byStep)
            return p;
    }
    return NULL;
}

bool CTaskMarketMgr::CheckCond(CPlayer& rPlayer, UINT32 dwCondID)
{
    bool bRet = false;
    CGameVar& rVar = rPlayer.GetUserPtr()->GetVars();
    UINT32 dwTmp;
    switch(dwCondID)
    {
        case eTaskCond15Tower:
            {
                dwTmp = rPlayer.GetTopDemonFloorID();  
                if(dwTmp >= 15)
                    bRet = true;  
            }
            break;
        case eTaskCondDuoBao:
            {
                dwTmp = rVar.GetVar(NVarDefine::ePlayerVarZhanQi);
                if(dwTmp)
                    bRet = true;
            }
        case eTaskCondDujie:
            {
                CHeroFighterPtr pMainFighter = rPlayer.GetMainFighter();
                if(pMainFighter && pMainFighter->GetDujieLevel() >= 21)
                    bRet = true;
            }
            break;
        case eTaskCondLevel42:
            {
                if(rPlayer.GetLevel() >= 42)
                    bRet = true;
            }
            break;
        case eTaskCond5Fighter:
            {
                CFighterManagerPtr pMgr =  rPlayer.GetFighterManager();
                if(!pMgr)
                    break;
                TVecFighterPtr rvecFighters;
                pMgr->GetAllFighters(rvecFighters);
                if(rvecFighters.size() >= 5)
                    bRet = true;
            }
            break;
        case eTaskCondFighter107:
                bRet = rPlayer.HasFighter(107);
            break;
        case eTaskCondGuild:
            {
                if(rPlayer.GetGuildLevel() >= 1)
                    bRet = true;
            }
            break;
        case eTaskCondEquip:
            {
                if(rPlayer.GetUserPtr()->GetVars().GetVar(NVarDefine::ePlayerVarCuiTiCount) >= 7)
                    bRet = true;
            }
            break;
        case eTaskCondTeamDungon:
           {
                CDungeonPkg& rDgnPkg = rPlayer.GetDgnPkg();
                bRet = rDgnPkg.IsDgnPassed(4001);
            }
            break;

        default:
            break;
    }
    return bRet;
}



/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

