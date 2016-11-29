#include "stdafx.h"
#include "PlayerDgn.h"
#include "DungeonMgr.h"
#include "Protocols.h"
#include "MapInfo.h"
#include "MapMgr.h"
//#include "MonsterMgr.h"
#include "User.h"
#include "Player.h"
#include "NPC.h"
#include "Tokenizer.h"
#include "Monster.h"
#include "GameServerLog.h"
#include "Loot.h"  
#include "SysMsgDefine.h"
#include "GameServerSysMail.h"
#include "DemonTowerDgn.h"
#include "VIPMgr.h"
#include "SysMsgDefine.h"
#include "StarsCFG.h"
#include "GUIDMgr.h"

enum EDgnSyncType
{
    eDgnSyncNone,
    eDgnSyncCreate,
    eDgnSyncDestroy,
};

map<UINT64, CDungeonPtr> CDungeonMgr::_mapInst2Dgn;
map<UINT16, SDgnInfo> CDungeonMgr::_mapID2DgnInfo;
map<UINT32,STimesPriceCFG> CDungeonMgr::_mapTimesPriceCFG;
//map<UINT16, SRaidsCFG> CDungeonMgr::_mapID2RaidsCfg;
map<UINT16,StarAward> CDungeonMgr::_mapStarAward;
bool CDungeonMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Dungeon.xml";
    CDungeonLoader oDungeonLoader;
    if(!oDungeonLoader.LoadData(strPath))
    {
        LOG_CRI << "oDungeonLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oDungeonLoader._vecData.size(); ++i)
    {
        SDungeonCFG* pDungeonCFG = oDungeonLoader._vecData[i];
        if(pDungeonCFG->_ID != 0)
        {
            SDgnInfo rDgnInfo(*pDungeonCFG); //= _mapID2DgnInfo[pDungeonCFG->_ID];
            rDgnInfo.oDgnCfg.wDgnID = pDungeonCFG->_ID;
            rDgnInfo.oDgnCfg.byMinLev = (UINT8)pDungeonCFG->_Level;
            rDgnInfo.oDgnCfg.eType = (EDgnType)pDungeonCFG->_TYPE;
            rDgnInfo.oDgnCfg.eSubType = (EDgnSubType)pDungeonCFG->_Type2;
            buf::Tokenizer tk(pDungeonCFG->_Maps, ';');
            for (size_t i = 0 ; i< tk.size();++i)
            {
                //SDgnMapConfig cfg;
                UINT16 wMapID = atoi(tk[i].c_str());
                static SMapInfoPtr pInfo = CMapMgr::GetMapInfo(wMapID);
                if(!pInfo || !pInfo->IsDungeon())
                {
                    LOG_CRI << "MAp Not Dungeon:" << wMapID;
                    return false;
                }
                rDgnInfo.oDgnCfg.vecMap.push_back(wMapID);
            }
            if(rDgnInfo.oDgnCfg.vecMap.empty())
            {
                LOG_CRI << "DGN need Map:ID" <<pDungeonCFG->_ID;

            }
            buf::Tokenizer tkPreDgn(pDungeonCFG->_PreDgns, ';');
            for (size_t i = 0 ; i< tkPreDgn.size();++i)
            {
                UINT16 wPreDgn = atoi(tkPreDgn[i].c_str());
                if(wPreDgn == 0)
                {
                    continue;
                }
                rDgnInfo.oDgnCfg.vecPreDgnID.push_back(wPreDgn);

            }
            buf::Tokenizer tkPassRequire(pDungeonCFG->_PassRequire, '|');
            for(size_t i = 0 ; i< tkPassRequire.size();++i)
            {
                buf::Tokenizer tksubPassRequire(tkPassRequire[i],',');
                TVecUINT16 vecProcess;
                for (size_t j = 0 ; j < tksubPassRequire.size();j++)
                {

                    UINT16 wPassRequire = atoi(tksubPassRequire[j].c_str());
                    if(wPassRequire == 0)
                    {
                        continue;
                    }
                    vecProcess.push_back(wPassRequire);
                }
                if(!vecProcess.empty())
                {
                    rDgnInfo.oDgnCfg.vecProcess.push_back(vecProcess);
                }
            }
            buf::Tokenizer tkStar(pDungeonCFG->_Evaluate, '|');
            for(size_t i = 0 ; i< tkStar.size();++i)
            {
                buf::Tokenizer tksubStar(tkStar[i],',');
                TVecUINT16 vecStar;
                for (size_t j = 0 ; j < tksubStar.size();j++)
                {

                    UINT16 wStar = atoi(tksubStar[j].c_str());
                    if(wStar == 0)
                    {
                        continue;
                    }
                    vecStar.push_back(wStar);
                }
                if(!vecStar.empty())
                {
                    rDgnInfo.oDgnCfg.vecStar.push_back(vecStar);
                }
            }
            buf::Tokenizer tkAttackOrder(pDungeonCFG->_Logic, ';');
            for(size_t i = 0 ; i< tkAttackOrder.size();++i)
            {
                UINT16 wGroupId = atoi(tkAttackOrder[i].c_str());  
                if(wGroupId == 0)
                {
                    continue;
                }
                rDgnInfo.oDgnCfg.vecAttackOrder.push_back(wGroupId);
            }
            buf::Tokenizer tkOutPoint(pDungeonCFG->_OUTPoint, ';');
            if(tkOutPoint.size() != 3 || !tkOutPoint.size() != 0)
            {
                LOG_CRI << "DGN OUT POINT ERR:" <<pDungeonCFG->_ID;
                return false;
            }
            if( tkOutPoint.size() == 3)
            {
                rDgnInfo.oDgnCfg.sOutConfig.wMapId = atoi(tkOutPoint[0].c_str());   
                rDgnInfo.oDgnCfg.sOutConfig.fPosX = atof(tkOutPoint[1].c_str());
                rDgnInfo.oDgnCfg.sOutConfig.fPosY = atof(tkOutPoint[2].c_str());
            }
            buf::Tokenizer tkAward(pDungeonCFG->_AwardLoots, ';');
            for(size_t i = 0 ; i< tkAward.size();++i)
            {
                UINT32 dwLootId = atoi(tkAward[i].c_str());
                rDgnInfo.oDgnCfg.vecAward.push_back(dwLootId);
            }
            rDgnInfo.oDgnCfg.dwLootID = pDungeonCFG->_dwLoots;
            rDgnInfo.oDgnCfg.dwCostLootID = pDungeonCFG->_dwLoots2;
            _mapID2DgnInfo[pDungeonCFG->_ID] = rDgnInfo;
        }
    }
    strPath = Config._strConfigDir + "Conf/Table/TimesPrice.xml";
    CTimesPriceLoader oTimesPriceLoader;
    if(!oTimesPriceLoader.LoadData(strPath))
    {
        LOG_CRI << "ERR Load" << strPath;
        return false;
    }
    for(size_t it =0 ; it != oTimesPriceLoader._vecData.size();it++)
    {
        STimesPriceCFG &rCfg = *(oTimesPriceLoader._vecData[it]);
        if(!_mapTimesPriceCFG.insert(make_pair(rCfg._BoughtTimes,rCfg)).second)
        {
            LOG_CRI << "Repeat Load" << strPath; 
            return false;
        }

    }

    strPath = Config._strConfigDir + "Conf/Table/Stars.xml";
    CStarsLoader oStarsLoader;
    if(!oStarsLoader.LoadData(strPath))
    {
        LOG_CRI << "ERR Load" << strPath; 
        return false;  
    }
    for(size_t it =0 ; it != oStarsLoader._vecData.size();it++)
    {
        SStarsCFG* pCfg = oStarsLoader._vecData[it];
        StarAward ItemAward;
        ItemAward.dwStar = pCfg->_RequiredStars;
        buf::Tokenizer tkAwards(pCfg->_Awards, '|');
        for(size_t i = 0 ; i< tkAwards.size();++i)   
        {
            buf::Tokenizer tk(tkAwards[i], ','); 
            if(tk.size() != 2)
            {
                LOG_CRI << "ERR Load" << strPath <<"for Id  " << pCfg->_PrizeId; 
                return false; 
            }
            UINT16 wItemId = atoi(tk[0].c_str());
            UINT32 dwNum = atoi(tk[1].c_str());
            if(wItemId == 0 || dwNum == 0)
            {
                LOG_CRI << "ERR Load" << strPath <<"for Id  " << pCfg->_PrizeId; 
                return false;

            }
            ItemAward.mapAward[wItemId] = dwNum;
        }
        if(ItemAward.mapAward.empty())
        {
            LOG_CRI << "ERR Load" << strPath <<"for Id  " << pCfg->_PrizeId; 
            return false;

        }
        _mapStarAward[pCfg->_PrizeId] = ItemAward;

    }
    return true;
}

void CDungeonMgr::Destroy()
{
    _mapInst2Dgn.clear();
}
void CDungeonMgr::ClearLua()
{
    for(auto iter = _mapID2DgnInfo.begin();iter != _mapID2DgnInfo.end();iter++)
    {
        iter->second.Reset();
    }
}
const SDgnInfo*  CDungeonMgr::GetDgnInfo(UINT16 wDgnID)
{
    auto it = _mapID2DgnInfo.find(wDgnID);
    if(it == _mapID2DgnInfo.end())
    {
        LOG_CRI << "Can't find config for DgnID: " << wDgnID;
        return NULL;
    }
    it->second.LuaInit();
    return &it->second;
}
#if 0
bool CDungeonMgr::CanSelectDgn(const CPlayerPtr& pPlayer, UINT16 wDgnID, UINT16* pMsgID/* = NULL*/)
{
    assert(pPlayer != NULL);
    SDgnConfig* pDgnConfig = GetDgnConfig(wDgnID);
    if(NULL == pDgnConfig)
        return false;
    CUser& rUser = pPlayer->GetUser();
    if(pDgnConfig->wPreDgnID != 0 && !rUser.IsDgnPassed(pDgnConfig->wPreDgnID))
    {
        if(pMsgID != NULL)
            *pMsgID = eMsg_PleasePassPrevDgn;
        return false;
    }
    if(pPlayer->Level() < pDgnConfig->byMinLev)
    {
        if(pMsgID != NULL)
            *pMsgID = eMsg_LessThanDgnLevel;
        return false;
    }
    */
        return true;
}

CDungeonPtr CDungeonMgr::CreateDungeon(UINT16 wDgnID)
{
    const SDgnInfo* pDgnInfo = GetDgnInfo(wDgnID);
    if(pDgnInfo == NULL)
        return NULL;
    UINT64 qwInstID = GetNewDgnInstID();
    CDungeonPtr pDungeon(new CDungeon(*pDgnInfo, qwInstID));
    if(pDungeon == NULL)
    {
        LOG_CRI << "pDungeon is NULL!";
        return NULL;
    }
    if(!pDungeon->Init())
    {
        LOG_CRI << "pDungeon->Init fails!";
        return NULL;
    }
    if(!_mapInst2Dgn.insert(make_pair(qwInstID, pDungeon)).second)
    {
        LOG_CRI << "Dungeon already exist! wDgnID: " << wDgnID << ", qwInstID: " << qwInstID;
        return NULL;
    }
    pDungeon->SetCreateTime(time(NULL));
    return pDungeon;
}
#endif
bool CDungeonMgr::CanCreateByDgnType(EDgnType eType)
{
    return eType == ePlayerDgn||eType == eGatherDgn;

}

EDungeonResult CDungeonMgr::PlayerCanCreatePlayerDGN(UINT16 wDgnID, CPlayer& rPlayer,bool bGM)
{   
    if (wDgnID == 1) // 新手副本不判断
        return eDungeonSuccess;
    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo = GetDgnInfo(wDgnID);
    if(NULL != pInfo)
    {
        pDgnConfig = &(pInfo->oDgnCfg);
    }
    if(pDgnConfig == NULL)
    {
        return eDungeonTypeNotExist ;
    }
    //在副本中不可以创建
    if(CMapMgr::IsDgnMap(rPlayer.GetCurMapID()))
    {
        return eDungeonInDgn;
    }
    if(bGM)
        return eDungeonSuccess;
    //等级不够不可以创建
    if(rPlayer.GetLevel() < pDgnConfig->byMinLev)
    {
        return eDungeonLowLevel;
    }
    //副本类型不正确不可以创建
    if(!CanCreateByDgnType(pDgnConfig->eType))
    {
        return eDungeonCreateErrType;
    }
    //前置任务没有完成不可以创建
    if(!rPlayer.GetDgnPkg().IsDgnListPassed(pDgnConfig->vecPreDgnID))
    {
        return eDungeonPreDgnNotFinish;
    }
    //需要的其他条件，如道具等
    RoleDgnInfo* pPlayerDgnInfo  =rPlayer.GetDgnPkg().GetPlayerDgnInfoByType(wDgnID);
    if( NULL == pPlayerDgnInfo || pPlayerDgnInfo->byCost ==0 )
    {
        //TODO:检查扣除
        if(!rPlayer.GetUser().CanSubAction(pDgnConfig->_SpendEnergy))
        {
            return eDungeonPowerErr;
        }
    }
    //TODO:进入时间，及其次数检查
    EDungeonResult eResult =rPlayer.GetDgnPkg().CheckDgnTimes(wDgnID);
    if(eResult != eDungeonSuccess)
    {
        return eResult;
    }

    if(rPlayer.GetUser().GetPack().GetEmptyCount() < pDgnConfig->_PackSize)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgDgnLackPack,BuildStrVec(pDgnConfig->_PackSize)));
        return eDungeonPackEmptyMin;
    }
    //Lua脚本判定不可以进入
    if(pInfo->CheckScriptOnEnterLimit())
    {
        UINT8 byCan = Config.GetScript().Dungeon_OnEnterLimit(wDgnID,rPlayer.GetUser());
        if(byCan <= eDungeonOtherErr)
        {
            EDungeonResult eResult = static_cast<EDungeonResult>(byCan);
            if(eResult != eDungeonSuccess)
            {
                return eResult;
            }
        }
    }

    return eDungeonSuccess;

}

CPlayerDgnPtr CDungeonMgr::CreatePlayerDungeon(UINT16 wDgnID, CPlayer& rPlayer,EDungeonResult &eResult,bool bGM)
{
    CPlayerDgnPtr pPlayerDgn = NULL;
    do
    {
        const SDgnInfo* pDgnInfo = GetDgnInfo(wDgnID);
        if(pDgnInfo == NULL)
        {
            eResult = eDungeonTypeNotExist;
            break;
        }
        eResult = PlayerCanCreatePlayerDGN(wDgnID,rPlayer,bGM);
        if(eDungeonSuccess !=  eResult)
        {
            break;
        }
        rPlayer.GetUser().SubAction(pDgnInfo->oDgnCfg._SpendEnergy);
        UINT64 qwInstID = GetNewDgnInstID();
        pPlayerDgn = CPlayerDgnPtr(new CPlayerDgn(*pDgnInfo, qwInstID, ToThisPtr(rPlayer)));
        if(pPlayerDgn == NULL)
        {
            eResult = eDungeonOtherErr; 
            LOG_CRI << "pDungeon is NULL!";
            break;
        }
        UINT16 wMapID = 0;
        if(wDgnID == 1)
        {
            wMapID = rPlayer.GetDgnMapID();
        }
        if(!pPlayerDgn->Init(wMapID))
        {
            eResult = eDungeonOtherErr; 
            LOG_CRI << "pPlayerDgn->Init fails!";
            break;
        }
        if(!_mapInst2Dgn.insert(make_pair(qwInstID, pPlayerDgn)).second)
        {
            LOG_CRI << "Dungeon already exist! wDgnID: " << wDgnID << ", qwInstID: " << qwInstID;
            eResult = eDungeonOtherErr; 
            break;
        }
        else
        {
            //LOG_INF << "Create CreatePlayerDungeon" << "Type :" << wDgnID <<"ID : "<< qwInstID;
        }
    }while(0);
    if(NULL != pPlayerDgn && eResult == eDungeonSuccess )
    {
        SDgnLogPtr ptrLog(new SDgnLog());
        if(NULL == ptrLog)
            return NULL;
        NLogDataDefine::SDgnLog& rLog = *ptrLog;

        rLog.wDgnType = wDgnID;
        rLog.qwDgnInsID = pPlayerDgn->GetDgnInstID();
        rLog.qwUserID =  rPlayer.GetUser().GetUserID();
        rLog.eOpType = NLogDataDefine::EDgnOpType_CREATE;

        CGameServerLog::LogToDB(ptrLog);

        pPlayerDgn->SetCreateTime(time(NULL));
        return pPlayerDgn;
    }
    return NULL;
}


CDemonTowerDgnPtr CDungeonMgr::CreateDemonTowerDgn(UINT16 wDgnID, CPlayer& rPlayer,EDungeonResult &eResult)
{
    CDemonTowerDgnPtr pDemonTowerDgn = NULL;
    const SDgnInfo* pDgnInfo = GetDgnInfo(wDgnID);
    if(pDgnInfo == NULL)
    {
        eResult = eDungeonTypeNotExist;
        return NULL;
    }

    //创建条件判断

    const SDgnConfig&  rDgnConfig = pDgnInfo->oDgnCfg;
    //等级不够不可以创建 
    if(rPlayer.GetLevel() < rDgnConfig.byMinLev)
    {
        eResult = eDungeonLowLevel;
        return NULL;
    }


    if(rPlayer.GetDemonTowerInstID())
    {
        auto itr =  _mapInst2Dgn.find(rPlayer.GetDemonTowerInstID());
        if(itr != _mapInst2Dgn.end())
        {
            if(itr->second->GetDgnType() != eDemonTowerDgn)
            {
                return NULL;
            }

            eResult = eDungeonSuccess;
            pDemonTowerDgn = dynamic_pointer_cast<CDemonTowerDgn>(itr->second);
            return pDemonTowerDgn;
        }
    }

    //在副本中不可以创建                        
    if(CMapMgr::IsDgnMap(rPlayer.GetCurMapID()))
    {                                           
        eResult = eDungeonInDgn;
        return NULL;                   
    }

    UINT64 qwInstID = GetNewDgnInstID();

    pDemonTowerDgn = CDemonTowerDgnPtr(new CDemonTowerDgn(*pDgnInfo, qwInstID, ToThisPtr(rPlayer)));
    if( pDemonTowerDgn == NULL)
    {
        eResult = eDungeonOtherErr; 
        LOG_CRI << "pDungeon is NULL!";
        return NULL;
    }

    if(!pDemonTowerDgn->Init())
    {
        eResult = eDungeonOtherErr; 
        LOG_CRI << "pPlayerDgn->Init fails!";
        return NULL;
    }
    if(!_mapInst2Dgn.insert(make_pair(qwInstID, pDemonTowerDgn)).second)
    {
        LOG_CRI << "Dungeon already exist! wDgnID: " << wDgnID << ", qwInstID: " << qwInstID;
        eResult = eDungeonOtherErr; 
        return NULL;
    }
    else
    {
        //LOG_INF << "Create CreatePlayerDungeon" << "Type :" << wDgnID <<"ID : "<< qwInstID;
    }


    eResult = eDungeonSuccess;

    pDemonTowerDgn->SetCreateTime(time(NULL));

    rPlayer.SetDemonTowerInstID(qwInstID);

    //副本log
    SDgnLogPtr ptrLog(new SDgnLog());
    if(NULL == ptrLog)
        return NULL;
    NLogDataDefine::SDgnLog& rLog = *ptrLog;

    rLog.wDgnType = wDgnID;
    rLog.qwDgnInsID = pDemonTowerDgn->GetDgnInstID();
    rLog.qwUserID =  rPlayer.GetUser().GetUserID();
    rLog.eOpType = NLogDataDefine::EDgnOpType_CREATE;

    CGameServerLog::LogToDB(ptrLog);

    return pDemonTowerDgn;
}

void CDungeonMgr::DestroyDungeon(const CDungeonPtr& pDungeon)
{
    assert(pDungeon != NULL);
    UINT64 qwInstID = pDungeon->GetDgnInstID();
    if(_mapInst2Dgn.erase(qwInstID) < 0)
        LOG_CRI << "Can't find Dungeon! InstID: " << qwInstID;
    pDungeon->OnEnd();
    //DungeonLog.LogDungeon(*pDungeon, eDungeonLog_End);
}

void CDungeonMgr::DestroyDungeon(UINT64 qwInstID)
{
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon != NULL)
    {
        DestroyDungeon(pDungeon);
        //LOG_INF << "DestroyDungeon qwInstID" << qwInstID;
    }
}

CDungeonPtr CDungeonMgr::GetDungeon(UINT64 qwInstID)
{
    auto it = _mapInst2Dgn.find(qwInstID);
    if(it != _mapInst2Dgn.end())
        return it->second;
    return NULL;
}

CGameMapPtr CDungeonMgr::GetDungeonMap(UINT64 qwInstID)
{
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon != NULL)
        return pDungeon->GetCurMap();
    return NULL;
}

UINT64 CDungeonMgr::GetNewDgnInstID()
{
    return GET_GUID(GUID_DGN);
}

bool CDungeonMgr::PlayerEnterDungeon(CPlayer& rPlayer, UINT64 qwInstID, SPoint* pPoint /*= NULL*/)
{
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon == NULL)
        return false;
    return pDungeon->PlayerEnter(rPlayer, pPoint);
}

bool CDungeonMgr::PlayerReEnterDungeon(CPlayer& rPlayer, UINT64 qwInstID, SPoint& rPoint)
{
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon == NULL)
        return false;
    /*
       if((UINT32)pDungeon->GetCreateTime() != rPlayer.GetDgnCreateTime())
       return false;
       */
    return pDungeon->PlayerReEnter(rPlayer, rPoint);
}

void CDungeonMgr::PlayerDungeonKillAll(CPlayer& rPlayer)
{
    UINT64 qwInstID = rPlayer.GetDgnInstID();
    if(0 == qwInstID)
    {

        return ;
    }
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon == NULL)
    {
        return ;
    }
    pDungeon->PlayerKillAll(rPlayer);
}

EDungeonResult CDungeonMgr::PlayerLeaveDungeon(CPlayer& rPlayer)
{
    /* TODO
       if(rPlayer.GetFightInfo().HasFight())
       return false;
       */
    UINT64 qwInstID = rPlayer.GetDgnInstID();
    if(0 == qwInstID)
    {

        LOG_CRI << "qwInstID is 0! qwUsrID: " << rPlayer.GetUserID();
        return eDungeonOutDgn;
    }
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon == NULL)
    {
        LOG_CRI << "Can't find Dungeon! qwInstID: " << qwInstID;
        return eDungeonInsNotExist;
    }

    pDungeon->PlayerLeave(rPlayer);
    LOG_DBG << "leave dungeon" << pDungeon->GetDgnInstID() << " type " << pDungeon->GetDgnConfig().eType;

    return eDungeonSuccess;
}

EDungeonResult CDungeonMgr::PlayerFinishDungeon(CPlayer& rPlayer)
{
    /* TODO
       if(rPlayer.GetFightInfo().HasFight())
       return false;
       */
    UINT64 qwInstID = rPlayer.GetDgnInstID();
    if(0 == qwInstID)
    {

        LOG_CRI << "qwInstID is 0! qwUsrID: " << rPlayer.GetUserID();
        return eDungeonOutDgn;
    }
    CDungeonPtr pDungeon = GetDungeon(qwInstID);
    if(pDungeon == NULL)
    {
        LOG_CRI << "Can't find Dungeon! qwInstID: " << qwInstID;
        return eDungeonInsNotExist;
    }

    pDungeon->FinishDgn(rPlayer);
    LOG_DBG << "Finish dungeon" << pDungeon->GetDgnInstID() << " type " << pDungeon->GetDgnConfig().eType;

    return eDungeonSuccess;
}
EDungeonResult CDungeonMgr::PlayerEnterNewDungeon(CPlayer& rPlayer, UINT16 wDgnID,const SPoint* pPoint /*= NULL*/,bool bGM /*= false*/)
{
    EDungeonResult eResult;
    if(rPlayer.GetActionManager().CanAddAction(eACTION_DGN) != eACTION_NONE)
    {
        return eDungeonBusy;
    }
    CPlayerDgnPtr pDgn = CreatePlayerDungeon(wDgnID, rPlayer,eResult,bGM);
    if(pDgn != NULL)
    {
        //DungeonLog.LogDungeon(*pDgn, eDungeonLog_Begin);
        if(!pDgn->PlayerEnter(rPlayer, pPoint))
        {
            eResult = eDungeonOtherErr; 
            LOG_CRI << "PlayerEnter eDungeonOtherErr.";
        }
        else
        {
            rPlayer.GetUser().GetTaskPkg().DoCaseForDgn(wDgnID);
        }

    }
    return eResult;
}

void CDungeonMgr::TimerCheck(time_t tNow)
{
    for(auto it = _mapInst2Dgn.begin(); it != _mapInst2Dgn.end();)
    {
        CDungeonPtr pDungeon = it->second;
        ++it;

        pDungeon->OnTimer(tNow);
        if(pDungeon->CanDestroy(tNow))
        {
            LOG_DBG << "Dungeon is over, Destroy:" << pDungeon->GetDgnInstID();
            pDungeon->ClearDungeon();
            LOG_CRI << "Ggn ref :" << pDungeon.use_count();
            DestroyDungeon(pDungeon);
            LOG_CRI << "Ggn ref :" << pDungeon.use_count();
        }
    }
    static UINT32 _dwLastCheckSizeTimer = 0;
    if(tNow >_dwLastCheckSizeTimer + 600)
    {
        LOG_INF <<  "Dungeon size is " << _mapInst2Dgn.size() << " Player size is " << (CUserMgr::GetUsrMap()).size();
        _dwLastCheckSizeTimer = tNow;
    }
}

void CDungeonMgr::NotifyPlayerWait(CPlayer& rPlayer)
{
    // TODO
    //rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsg_WaitOtherRoomPlayer));
}


bool CDungeonMgr::Sweeping(CPlayer& rPlayer, UINT16 wDgnID, UINT8 byOptions)
{

    //CDungeonMgr::CleanDGN(wDgnID,rPlayer);
    return true;
}

bool CDungeonMgr::IsBornDungeon(UINT16 wDgnID)
{
    if(wDgnID == 0)
        return false;
    return wDgnID == Config._wBornDgnID;
}
EDungeonResult CDungeonMgr::TestCanSweeping(UINT16 wDgnID,CPlayer& rPlayer,UINT16 wCount)
{
    const SDgnInfo* pDgnInfo = GetDgnInfo(wDgnID);
    if(pDgnInfo == NULL)
    {
        return eDungeonTypeNotExist;
    }
    if(!rPlayer.CheckIconIsOpen(CleanIcon))
    {
        return eDungeonTypeNotExist; 
    }
    const SDgnConfig* pDgnConfig = &(pDgnInfo->oDgnCfg);
    //if(rPlayer.GetUser().GetPack().GetEmptyCount() < pDgnConfig->_PackSize * wCount)
    //仅判断当前次是否包满
    if(rPlayer.GetUser().GetPack().GetEmptyCount() < pDgnConfig->_PackSize * 1) 
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eDgnLackingPackage,BuildStrVec(pDgnConfig->_PackSize)));
        return eDungeonPackEmptyMin;
    }

    /*去掉副本限制
      if(CMapMgr::IsDgnMap(rPlayer.GetCurMapID()))
      {
      return eDungeonInDgn;
      }
      */

    //副本类型不正确不可以创建
    if(!CanCreateByDgnType(pDgnConfig->eType))
    {
        return eDungeonCreateErrType;
    }
    RoleDgnInfo* pPlayerDgnInfo  =rPlayer.GetDgnPkg().GetPlayerDgnInfoByType(wDgnID);
    if( NULL == pPlayerDgnInfo || pPlayerDgnInfo->dwCompleteTimes ==0 )
    {
        return eDungeonNotFinish;
    }
    if(!rPlayer.GetUser().CanSubAction(pDgnInfo->oDgnCfg._SpendEnergy*wCount))
    {
        return eDungeonPowerErr;
    }
    return rPlayer.GetDgnPkg().CheckDgnTimes(wDgnID);

}
EDungeonResult CDungeonMgr::CleanDGN(UINT16 wDgnID,CPlayer& rPlayer,std::vector<SItemGenInfo>* pvecItems ,TVecResource * pvecRes)
{
    EDungeonResult result = TestCanSweeping(wDgnID,rPlayer);

    if(result != eDungeonSuccess)
    {
        return result;
    }
    //开始扫荡
    const SDgnInfo* pDgnInfo = GetDgnInfo(wDgnID);
    if(pDgnInfo == NULL)
    {
        return eDungeonTypeNotExist;
    }
    //判断体力
    if(!rPlayer.GetUser().CanSubAction(pDgnInfo->oDgnCfg._SpendEnergy))
    {
        return eDungeonPowerErr;
    }
    //收集所有怪
    RoleDgnInfo* pPlayerDgnInfo  =rPlayer.GetDgnPkg().GetPlayerDgnInfoByType(wDgnID);
    if( NULL == pPlayerDgnInfo || pPlayerDgnInfo->dwCompleteTimes ==0 )
    {
        LOG_CRI<<"DGN ERR:No DGN ReCord";
        return eDungeonNotFinish;
    }
    rPlayer.GetUser().SubAction(pDgnInfo->oDgnCfg._SpendEnergy);
    for(auto iter = pDgnInfo->oDgnCfg.vecAttackOrder.begin();iter != pDgnInfo->oDgnCfg.vecAttackOrder.end();iter++)
    {
        CMonster::DropToPlayer(*iter,rPlayer,false,pvecItems,pvecRes);
    }
    //副本奖励
    CDungeonMgr::AwardToPlayer(*pDgnInfo,pPlayerDgnInfo->wMinTurns,rPlayer,false,pvecItems,pvecRes);
    return eDungeonSuccess;
}

// 获取奖励
void CDungeonMgr::AwardToPlayer(const SDgnInfo& rDgnInfo,UINT8 byStar,CPlayer& rPlayer,bool bIsAppend,std::vector<SItemGenInfo> *pvecItems,TVecResource* pvecRes, UINT32 dwRewardRate /* = 10000 */)
{
    UINT32 dwDropId = GetAwardLootId(rDgnInfo,rPlayer.GetDgnPkg().CompleteDgnIsCost(rDgnInfo.oDgnCfg.wDgnID)); 
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwDropId, vecItems,vecRes);

    for (auto& rItem : vecItems)
    {
        rItem.dwCount = rItem.dwCount * (dwRewardRate / 10000.0f);
    }

    for (auto& rRes : vecRes)
    {
        rRes._dwValue = rRes._dwValue * (dwRewardRate / 10000.0f);
    }

    if(!vecItems.empty())
    {
        CPack& oPack = rPlayer.GetUser().GetPack();
        if(!oPack.CanAddItem(vecItems))//包裹放不进
        {
            rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
            //发送邮件
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_DGNPASS;
            stBody.vecParam.push_back(rDgnInfo.oDgnCfg._NAME);
            TVecUINT64 vecTargets;
            vecTargets.push_back(rPlayer.GetUser().GetUserID());
            GameServerSysMail::SendSysMail(SEND_DGNPASS,TITLE_DGNPASS,stBody,vecTargets,&vecItems);
        }
        else
        {
            oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_EDgn, true, !bIsAppend);
        }
    }

    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rPlayer.GetUser().GetVIPLevel());
    if(rDgnInfo.oDgnCfg._dwExp > 0)     // 副本经验值
    {
        SResource stRes;
        stRes._eRes = EMONEY_EXP;
        stRes._dwValue = static_cast<UINT32>(rDgnInfo.oDgnCfg._dwExp * (dwRewardRate / 10000.0f));
        if (rDgnInfo.oDgnCfg.eType != eTeamDgn &&  rDgnInfo.oDgnCfg.eSubType != eSubLiXian)
        {
            if(pCfgVip && pCfgVip->_Level > 0)
                stRes._dwValue *= pCfgVip->_CopyFinishRewardC/100.0;
            else if (rPlayer.GetUser().HasTempVIPPrivilege())
                stRes._dwValue *= 1.12f;
        }
        vecRes.push_back(stRes);
    }
    if(rDgnInfo.oDgnCfg._dwPExp > 0)    // 副本修为:改银币
    {
        SResource stRes;
        stRes._eRes = EMONEY_SILVER;
        stRes._dwValue = static_cast<UINT32>(rDgnInfo.oDgnCfg._dwPExp * (dwRewardRate / 10000.0f));
        if(pCfgVip && rDgnInfo.oDgnCfg.eType != eTeamDgn && rDgnInfo.oDgnCfg.eSubType != eSubLiXian)
            stRes._dwValue *= pCfgVip->_CopyFinishRewardC/100.0; 

        vecRes.push_back(stRes);
    }

    // 副本星级
    UINT8 byGetStar = 0;
    RoleDgnInfo* pPlayerDgnInfo  =rPlayer.GetDgnPkg().GetPlayerDgnInfoByType(rDgnInfo.oDgnCfg.wDgnID);
    if( NULL == pPlayerDgnInfo)
    {
        byGetStar = byStar;
    }
    else if(pPlayerDgnInfo->wMinTurns < byStar)
    {
        byGetStar = byStar - pPlayerDgnInfo->wMinTurns;
    }
    if( byGetStar > 0)
    {
        SResource stRes;
        stRes._eRes = EMONEY_REIKI;
        stRes._dwValue = byGetStar;
        vecRes.push_back(stRes);
        TVecINT32 vecData;
        vecData.push_back(byGetStar);
        rPlayer.GetEventMgr()->OnEvent(eEventType_DungeonStarGet,vecData);
    }

    if(!vecRes.empty() && !bIsAppend)
    {
        CStore::AddResource(rPlayer.GetUser(),vecRes,NLogDataDefine::ItemFrom_EDgn);
    }
    if( NULL != pvecItems)
    {
        for(auto rItem : vecItems)
        {
            pvecItems->push_back(rItem);
        }
    }
    if(NULL != pvecRes)
    {
        for(auto rRes : vecRes)
        {
            pvecRes->push_back(rRes);
        }
    }
}


UINT32 CDungeonMgr::GetAwardLootId(const SDgnInfo& rDgnInfo,bool bCost)
{
    if(!bCost)
        return rDgnInfo.oDgnCfg.dwLootID;
    return rDgnInfo.oDgnCfg.dwCostLootID;
}

UINT32 CDungeonMgr::GetHeroDgnPrice(UINT32 dwTimes)
{
    if(_mapTimesPriceCFG.empty())
    {
        return 0;
    }
    auto it = _mapTimesPriceCFG.find(dwTimes);
    if(it != _mapTimesPriceCFG.end())
    {
        return it->second._HeroDungeon;
    }
    return (_mapTimesPriceCFG.rbegin())->second._HeroDungeon; 
}

UINT32 CDungeonMgr::GetLiXianDgnPrice(UINT32 dwTimes)
{
    if(_mapTimesPriceCFG.empty())
    {
        return 0;
    }
    auto it = _mapTimesPriceCFG.find(dwTimes);
    if(it != _mapTimesPriceCFG.end())
    {
        return it->second._AdventureDungeon;
    }
    return (_mapTimesPriceCFG.rbegin())->second._AdventureDungeon; 
}

UINT32 CDungeonMgr::GetMoneyTreePrice(UINT32 dwTimes)
{
    if(_mapTimesPriceCFG.empty())
    {
        return 0;
    }
    auto it = _mapTimesPriceCFG.find(dwTimes);
    if(it != _mapTimesPriceCFG.end())
    {
        return it->second._MoneyTree;
    }
    return (_mapTimesPriceCFG.rbegin())->second._MoneyTree; 
}

const StarAward * CDungeonMgr::GetAwardByID(UINT16 wStarID)
{
    auto iter =  _mapStarAward.find(wStarID);
    if(iter == _mapStarAward.end())
    {
        return NULL;
    }
    return &(iter->second);
}
