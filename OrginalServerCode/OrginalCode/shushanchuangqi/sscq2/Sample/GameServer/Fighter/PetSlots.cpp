
#include "stdafx.h"
#include "Protocols.h"
#include "PetSlots.h"
#include "UserMgr.h"
#include "FighterMgr.h"
#include "ItemMgr.h"
#include "FormationProtS.h"
#include "GetCondMgr.h"
#include "Player.h"
#include "Map.h"
#include "EventMgr.h"
#include "FighterManager.h"
#include "ProtoCommon.h"
#include "GameServerLog.h"
#include "RankProt.h"
#include "BoostMgr.h"
#include "HeroFighter.h"
#include "Random.h"

using namespace NRankProt;

class PetEnumerate4List : public Enumerator<typename CVecSlots<int, CPetPtr>::value_type>
{
    public:
        typedef CVecSlots<int, CPetPtr>::value_type value_type;

    public:
        PetEnumerate4List(TVecPetDataInfo& vecPets) : vecPets(vecPets) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                CPetPtr& pPet = std::get<2>(*obj);
                vecPets.push_back(SPetDataInfo(pPet->GetID(), pPet->GetSelected(), pPet->GetPetLevel(), pPet->GetPetExp()));
            }
            return true;
        }

    public:
        TVecPetDataInfo& vecPets;
};

void CPetSlots::GetAllPets(TVecPetDataInfo& vecPets)
{
    PetEnumerate4List en(vecPets);
    enumerate(en);
}

class PetEnumerate4Attr : public Enumerator<typename CVecSlots<int, CPetPtr>::value_type>
{
    public:
        typedef CVecSlots<int, CPetPtr>::value_type value_type;

    public:
        PetEnumerate4Attr(TVecFloat& vecAddAttr) : _vecAddAttr(vecAddAttr) {}

        bool operator()(const value_type* obj) const
        {
            if (obj && std::get<1>(*obj))
                std::get<2>(*obj)->AppendAttr(_vecAddAttr);
            return true;
        }

    public:
        TVecFloat& _vecAddAttr;
};

bool CPetSlots::GetAllPetAttr(TVecFloat& vecAddAttr) const
{
    PetEnumerate4Attr en(vecAddAttr);
    enumerate(en);
    return true;
}

const TVecFloat& CPetSlots::GetAttrVec() const
{
    VECATTR_RESET(_vecAttr);
    GetAllPetAttr(_vecAttr);
    return _vecAttr;
}

bool CPetSlots::LoadPet(const SPetDataInfo& sPetDataInfo)
{
    CPetPtr pPet = GetPet(sPetDataInfo.wPetID);
    if (pPet)
        return false;

    SPetCFGEx* pPetCfg = CFighterMgr::GetPetCfg(sPetDataInfo.wPetID);
    if (!pPetCfg)
        return false;

    pPet.reset(new CPet());
    if (!pPet)
        return false;

    if (!pPet->Load(sPetDataInfo))
        return false;

    //等级和经验匹配处理
    if (pPet->GetPetLevel() > 0)
    {
        SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(pPet->GetID(), pPet->GetPetLevel()-1);

        if (pPetLevelCFG && pPetLevelCFG->_LevelUpExp > pPet->GetPetExp())
        {
            pPet->SetPetExp(pPetLevelCFG->_LevelUpExp);
            Update2DB(pPet);
        }
    }

    if (!Set(sPetDataInfo.wPetID, pPet))
        return false;

    if(1 == sPetDataInfo.bySelected)
        _pCurrPet = pPet;

    UpdateGroupAttr();

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(sPetDataInfo.wPetID);
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        //if(pEventMgr)
        //    pEventMgr->OnEvent(eEventType_PetData,vecParam);
    }

    return true;
}

// 获得阵灵
CPetPtr CPetSlots::AdoptPet(UINT16 wPetID, bool bUpdate/* = true*/, bool bForce /* = false */)
{
    CPetPtr pPet = GetPet(wPetID);
    if (pPet)
    {
        if (bForce)
            return pPet;
        else
            return NULL;
    }

    SPetCFGEx* pPetCfg = CFighterMgr::GetPetCfg(wPetID);
    if (!pPetCfg)
        return NULL;

    if (bUpdate && !bForce) // XXX: 激活
    {
        if (!CGetCondMgr::Instance().TestCond(_rUser, pPetCfg->_Unlock))
            return NULL;
        if (!CGetCondMgr::Instance().ProcessCond(_rUser, pPetCfg->_Unlock, NLogDataDefine::ItemTo_PetActive))
            return NULL;
    }

    pPet.reset(new CPet());
    if (!pPet)
        return NULL;

    if (!pPet->Init(wPetID))
        return NULL;

    //bool bEmpty = false;
    //if (!GetUsedCount())
        //bEmpty = true;

    if (!Set(wPetID, pPet))
        return NULL;

    UpdateGroupAttr();

    if (bUpdate)
        Update2DB(pPet, eOpAdd);

    _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(wPetID, pPet->GetSelected(), pPet->GetPetLevel(), pPet->GetPetExp()));
    //_dwSpirit += pPetCfg->_UnlockSoul;

    /*if (bUpdate)
      {
      SRolePetInfo sRolePetInfo(_dwExp, _byLevel, _dwSpirit);
      Update2DB(sRolePetInfo, eOpAdd);
      }*/

    /*if (bEmpty && bUpdate)
      ActivePet(pPet, 1, bUpdate);*/


    WritePetLog(pPet->GetID(),0);
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        _rUser.GetTaskPkg().OnAction(*pPlayer,eProcessAction_ActPet, 1);

        //激活阵灵事件
        TVecINT32 vecParam;
        vecParam.push_back(wPetID);
        TVecPetDataInfo vecPets;
        GetAllPets(vecPets);
        vecParam.push_back(vecPets.size());
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
        {
            pEventMgr->OnEvent(eEventType_PetActive, vecParam);
            g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActFormation,pPlayer->GetRoleID(),wPetID);
        } 
        if(pPetCfg && pPet)
        {
            SFighterPropCFGEx* pFighterCfg = CFighterMgr::GetFighterPropCfg(pPetCfg->_FighterProp);
            if(pFighterCfg && pFighterCfg->_Color >= NProtoCommon::ECOLOR_PURPLE)
            {
                NGlobalChatProt::SShowInfo stShow;
                stShow.qwInstID = pPlayer->GetUserID();
                pPet->GetShowInfo(stShow);
                NGlobalChatProt::TVecShowInfo vecShow;
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecShow.push_back(stShow);
                g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPurplePetGet,vecstring,vecShow);
            }
        }

    }

    return pPet;
}

// 阵灵跟随
bool CPetSlots::PetFollow(CPetPtr& pPet, bool bFollow)
{
    if (!pPet)
        return false;

    if (pPet->GetSelected() == 0)
        return false;

    bool bHide = (pPet->GetSelected() == 2);
    bool bChanged = false;
    if (bHide && bFollow)
    {
        bChanged = true;
        pPet->SetSelected(1);
    }
    else if (!bHide && !bFollow)
    {
        bChanged = true;
        pPet->SetSelected(2);
    }

    if (bChanged)
        Update2DB(pPet);

    if (bChanged)
        _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(pPet->GetID(), pPet->GetSelected(), pPet->GetPetLevel(), pPet->GetPetExp()));

    return true;
}

bool CPetSlots::PetFollow(UINT16 wPetID, bool bFollow)
{
    if (!HasObj(wPetID))
        return false;
    CPetPtr& pPet = Get(wPetID);
    return PetFollow(pPet, bFollow);
}

// 选择出战
bool CPetSlots::ActivePet(UINT16 wPetID, UINT8 byType, bool bUpdate/* = true*/)
{
    if (!HasObj(wPetID))
        return false;
    CPetPtr& pPet = Get(wPetID);
    return ActivePet(pPet, byType, bUpdate);
}

bool CPetSlots::ActivePet(CPetPtr& pPet, UINT8 byType, bool bUpdate/* = true*/)
{
    if (!pPet || !_rUser.GetPlayer())
        return false;

    if (byType == 1 || byType == 2) // 1,2
    {
        if ((byType == 1 && pPet->GetSelected() == 1) || (byType == 2 && pPet->GetSelected() == 2))
            return false;

        pPet->SetSelected(byType);

        if (bUpdate && _pCurrPet && _pCurrPet->GetID() != pPet->GetID())
        {
            //原来阵灵设置为不出战
            _pCurrPet->SetSelected(2);
            _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(_pCurrPet->GetID(), 2, 
                        _pCurrPet->GetPetLevel(), _pCurrPet->GetPetExp()));
            Update2DB(_pCurrPet);
        }

        if (!_pCurrPet || (_pCurrPet && _pCurrPet->GetID() != pPet->GetID()))
        {
            //现在阵灵设置为出战,换阵灵出战
            _pCurrPet = pPet;
            _pCurrPet->SetSelected(1);
        }
        if (bUpdate)
        {
            _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(_pCurrPet->GetID(), 
                        _pCurrPet->GetSelected(), _pCurrPet->GetPetLevel(), _pCurrPet->GetPetExp()));
            Update2DB(_pCurrPet);
            if (_rUser.GetPlayer()->GetMap())
                _rUser.GetPlayer()->GetMap()->AppearToSurround(*_rUser.GetPlayer());
        }
    }
    else // 0
    {
        if (!_pCurrPet || pPet->GetSelected() == 0 || _pCurrPet->GetID() != pPet->GetID())
            return false;
        pPet->SetSelected(0);
        if (bUpdate)
        {
            _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(_pCurrPet->GetID(), 0, 
                        _pCurrPet->GetPetLevel(), _pCurrPet->GetPetExp()));
            Update2DB(pPet);
            _pCurrPet = NULL;
            _rUser.GetPlayer()->GetMap()->AppearToSurround(*_rUser.GetPlayer());
        }
    }
    UpdateRankInfo();

    //出战阵灵事件
    if (1 == byType)
    {
        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if(pPlayer)
        {
            TVecINT32 vecParam;
            vecParam.push_back(pPet->GetID());
            CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
            if(pEventMgr)
                pEventMgr->OnEvent(eEventType_PetGetFighting, vecParam);
        }
    }
    return true;
}

// 幻化
bool CPetSlots::PetUpgrade(CPetPtr& pPet)
{
    return true;
}

bool CPetSlots::PetUpgrade(UINT16 wPetID)
{
    return true;
}

// 升级
EFormPetType CPetSlots::PetLevelUp(UINT16 wPetID, UINT8 byType/* = 0*/)
{
    if (!HasObj(wPetID))
        return eFormPetFalied;
    CPetPtr& pPet = Get(wPetID);
    return PetLevelUp(pPet, byType);
}

EFormPetType CPetSlots::PetLevelUp(CPetPtr& pPet, UINT8 byType/* = 0*/)
{
    if (!pPet)
        return eFormPetFalied;

    UINT8 petLevel = pPet->GetPetLevel();
    if(petLevel >= 9)
        return eFormPetFalied;

    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(pPet->GetID(), petLevel);
    if (!pPetLevelCFG)
        return eFormPetFalied;

    /*UINT16 wItemID = 0;
      if (byType == 0)
      wItemID = SParamConfig::wZhuGuoID;
      else
      wItemID = SParamConfig::wPanTaoID;*/

    UINT16 wItemID = pPetLevelCFG->_TrainItem;
    SItemInfo* pItemCfg = CItemMgr::GetItemConfig(wItemID);
    if (!pItemCfg)
        return eFormPetFalied;

    UINT16 wCount = _rUser.GetPack().GetItemCount(wItemID);
    if (wCount < pPetLevelCFG->_TrainItemNum)
        return eFormPetPetLevelItemErr;
    _rUser.GetPack().DelItemByItemID(wItemID, pPetLevelCFG->_TrainItemNum, true, NLogDataDefine::ItemTo_PetLvlUp);

    UINT8 byNum = 1;
#if ON_OFF
    UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
    if (wRand < RANDVALUE_A)
        byNum = 10;
    else if (wRand < RANDVALUE_B)
        byNum = 5;
    else if (wRand < RANDVALUE_C)
        byNum = 2;

    LOG_WRN << "PetLevelUp : " << byNum;
    
    if (TWO_NOTIFY==byNum)
        _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eTwoMultipleCrit));
    else if (FIVE_NOTIFY==byNum)
        _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eFiveMultipleCrit));
    else if(TEN_NOTIFY==byNum)
    {
        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if (pPlayer)
        {
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecstring.push_back(NumberToString(byNum));
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPetLevel, vecstring);
        }

        _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eTenMultipleCrit));
    }
#endif
    UINT32 petExp = (pPet->GetPetExp()) + (pPetLevelCFG->_TrainExp) * byNum;
    pPet->SetPetExp(petExp);
    _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_PetUp);

    if (petExp >= pPetLevelCFG->_LevelUpExp)
    {
        petLevel++;
        pPet->SetPetLevel(petLevel);
        pPet->SetPetSkill();
        pPet->SetDirty(true);
        UpdateGroupAttr();
    }

    _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(pPet->GetID(), pPet->GetSelected(), 
                pPet->GetPetLevel(), pPet->GetPetExp()));
    Update2DB(pPet);

    WritePetLog(pPet->GetID(),1); //1 代表升级
    //阵灵升级事件
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pPet->GetID());
        vecParam.push_back(pPet->GetPetLevel());
        TVecPetDataInfo vecPets;
        GetAllPets(vecPets);
        for (size_t i=0; i<vecPets.size(); ++i)
        {
            vecParam.push_back(vecPets[i].byLevel);
        }
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_PetUpgrade,vecParam);
        if(pPet->GetPetLevel() >= 9)
        {
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            pPet->GetShowInfo(stShow);
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPetTop,vecstring,vecShow);
        }

        _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialPetLvl);
    }

    /*if (!wCount)
      return eFormPetPetLevelItemErr;
      _rUser.GetPack().DelItemByItemID(wItemID, 1, true, NLogDataDefine::ItemTo_PetLvlUp);

      _dwExp += pItemCfg->oItemCfg._TrumpExp;
      bool r = CFighterMgr::PetTestLevelUp(_byLevel, _dwExp);
      if (r)
      {
    // TODO:
    }

    SRolePetInfo sRolePetInfo(_dwExp, _byLevel, _dwSpirit);
    _rUser.SendPkg(g_FormationProtS.BuildPkg_RolePetNotify(sRolePetInfo));
    Update2DB(sRolePetInfo);*/

    return eFormPetSucc;
}

void CPetSlots::WritePetLog(UINT16 wID,UINT8 byOpType)
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(!pPlayer)
        return ;
    SPetCFGEx* pPet = CFighterMgr::GetPetCfg(wID);
    if(!pPet)
        return;
    CPetPtr& pPetPtr = Get(wID);
    if (!pPetPtr)
        return ;
    NLogDataDefine::SPetLogPtr ptrLog(new NLogDataDefine::SPetLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SPetLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwPlayerId  = pPlayer->GetRoleID();
    rLog.sName       = pPet->_Name;
    rLog.byOpType    = byOpType; 
    rLog.wLevel      = pPetPtr->GetPetLevel();
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

//一键升级
EFormPetType CPetSlots::QuickPetLevelUp(UINT16 wPetID)
{
    if (!HasObj(wPetID))
        return eFormPetFalied;

    CPetPtr& pPet = Get(wPetID);
    if (!pPet)
        return eFormPetFalied;

    UINT8 petLevel = pPet->GetPetLevel();
    if(petLevel >= 9)
        return eFormPetFalied;

    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(pPet->GetID(), petLevel);
    if (!pPetLevelCFG)
        return eFormPetFalied;

    UINT16 wItemID = pPetLevelCFG->_TrainItem;
    SItemInfo* pItemCfg = CItemMgr::GetItemConfig(wItemID);
    if (!pItemCfg)
        return eFormPetFalied;
    UINT16 wTrainItemNum = pPetLevelCFG->_TrainItemNum;
    UINT16 wTrainExp = pPetLevelCFG->_TrainExp;

    UINT16 wCount = 0;
    UINT32 addPetExp = 0;
    UINT16 wNeedCount = wTrainItemNum;
    UINT32 petCurExp = pPet->GetPetExp();
    UINT16 wTimes = 0;
    UINT16 wTimesA = 0;
    UINT16 wTimesB = 0;
    UINT16 wTimesC = 0;

    while ((pPetLevelCFG->_LevelUpExp > (addPetExp + petCurExp)) && (_rUser.GetPack().GetItemCount(wItemID) >= wNeedCount))
    {
        UINT8 byNum = 1;
#if ON_OFF
        UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
        if (wRand < RANDVALUE_A)
        {
            byNum = 10;
            wTimesA++;
        }
        else if (wRand < RANDVALUE_B)
        {
            byNum = 5;
            wTimesB++;
        }
        else if (wRand < RANDVALUE_C)
        {
            byNum = 2;
            wTimesC++;
        }

        LOG_WRN << "QuickPetLevelUp : " << byNum;

        if (TWO_NOTIFY==byNum)
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eTwoMultipleCrit));
        else if (FIVE_NOTIFY==byNum)
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eFiveMultipleCrit));
        else if(TEN_NOTIFY==byNum)
        {
            CPlayerPtr pPlayer = _rUser.GetPlayer();
            if (pPlayer)
            {
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(byNum));
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPetLevel, vecstring);
            }
        
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(ePetCrit, eTenMultipleCrit));
        }
#endif
        addPetExp += (wTrainExp * byNum);
        wCount += wTrainItemNum;
        wNeedCount += wTrainItemNum;
        wTimes++;
    }

    LOG_WRN << "QuickPetLevelUp Num : " << wTimes;
    LOG_WRN << "QuickPetLevelUp NumA : " << wTimesA;
    LOG_WRN << "QuickPetLevelUp NumB : " << wTimesB;
    LOG_WRN << "QuickPetLevelUp NumC : " << wTimesC;

    if (0 == wCount && _rUser.GetPack().GetItemCount(wItemID) < wCount)
        return eFormPetPetLevelItemErr;
    _rUser.GetPack().DelItemByItemID(wItemID, wCount, true, NLogDataDefine::ItemTo_PetLvlUp);

    UINT32 petExp = petCurExp + addPetExp;
    pPet->SetPetExp(petExp);
    for(auto it =0; it != wTimes;it++)
    {
        _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_PetUp);
    }

    if (petExp >= pPetLevelCFG->_LevelUpExp)
    {
        petLevel++;
        pPet->SetPetLevel(petLevel);
        pPet->SetPetSkill();
        pPet->SetDirty(true);
        UpdateGroupAttr();
    }

    _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(pPet->GetID(), pPet->GetSelected(), 
                pPet->GetPetLevel(), pPet->GetPetExp()));
    Update2DB(pPet);

    WritePetLog(pPet->GetID(),1); //1 代表升级

    //阵灵升级事件
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pPet->GetID());
        vecParam.push_back(pPet->GetPetLevel());
        TVecPetDataInfo vecPets;
        GetAllPets(vecPets);
        for (size_t i=0; i<vecPets.size(); ++i)
        {
            vecParam.push_back(vecPets[i].byLevel);
        }
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_PetUpgrade,vecParam);
        if(pPet->GetPetLevel() >= 9)
        {
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            pPet->GetShowInfo(stShow);
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPetTop,vecstring,vecShow);
        }
        
        _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialPetLvl);
    }

    return eFormPetSucc;
}

void CPetSlots::UpdateGroupAttr()
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
        if(pFighterManager)
        {
            pFighterManager->SetDirty(eAttrGpPet);
        }
    }
    UpdateRankInfo();
}

bool CPetSlots::GetBattleFighters(std::vector<IBattleFighterPtr>& vecBattleFighter)
{
    if (_pCurrPet && _pCurrPet->GetSelected() == 1) // XXX: 1-出战且显示
    {
        /*TVecFloat vecAddAttr;
          GetAllPetAttr(vecAddAttr);*/

        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if (NULL == pPlayer)
            return false;

        CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
        if (NULL == pMainFighter)
            return false;

        TVecFloat vecAddAttr = pMainFighter->GetAttrVec();
        IBattleFighterPtr pBattleFighter = _pCurrPet->ToBattleFighter(vecAddAttr);
        if (pBattleFighter)
        {
            vecBattleFighter.push_back(pBattleFighter);
            return true;
        }
    }
    return false;
}

void CPetSlots::Update2DB(SRolePetInfo& sRolePetInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << sRolePetInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypeRolePetInfo, eDataChange, strData);
}

void CPetSlots::Update2DB(CPetPtr& pPet, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    SPetDataInfo oPetDataInfo;
    oPetDataInfo.wPetID = pPet->GetID();
    oPetDataInfo.bySelected = pPet->GetSelected();
    oPetDataInfo.byLevel = pPet->GetPetLevel();
    oPetDataInfo.dwExp = pPet->GetPetExp();
    iar << oPetDataInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypePetDataInfo, eDataChange, strData);
}

UINT32 CPetSlots::GetPetBattlePoint() const
{
    UINT32 dwBattlePoint = 0;

    TVecUINT32 vecSkillsID;
    CPetPtr pPet = GetCurrPet();
    if (pPet && pPet->GetSelected() == 1)
        pPet->GetAllSkillID(vecSkillsID);
    dwBattlePoint += BattlePointCalucator.CalcAttrBattlePoint(GetAttrVec());
    dwBattlePoint += BattlePointCalucator.CalcSkillBattlePoint(vecSkillsID);
    return dwBattlePoint;
}

void CPetSlots::UpdateRankInfo() const
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if (!pPlayer || pPlayer->GetLevel() < SParamConfig::wRankLevelLimit3)
        return;
    CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
    if (!pMainFighter)
        return;
    UINT32 dwBattlePoint = GetPetBattlePoint();
    if (!dwBattlePoint)
        return;
    TVecRankInfo vecRankInfo;
    SRRFormationInfoPtr pInfo (new SRRFormationInfo);
    pInfo->dwValue = dwBattlePoint;
    pInfo->dwUpdateTime = Time::Now();
    pInfo->qwRoleID = pPlayer->GetRoleID();
    pInfo->strName = pPlayer->GetName();
    pInfo->strGuildName = pPlayer->GetGuildName();
    pInfo->wPlayerFighterID = pMainFighter->GetID();
    pInfo->byQuality = pMainFighter->GetColor();
    pInfo->vecPlatforms = _rUser.GetPlatformParam();
    pInfo->byVIPLevel = _rUser.GetVIPLevel();
    CPetPtr pPet = GetCurrPet();
    if (pPet && pPet->GetSelected() == 1)
        pInfo->wID = pPet->GetID();
    else
        return;
    pInfo->dwBattlePoint = dwBattlePoint;

    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    g_Game2CenterRankC.Send_UpdateRankInfo(eRTFormation, pPlayer->GetRoleID(), vecRankInfo);
}

// ===  FUNCTION  ======================================================================
//         Name:  SuperBoostObjects
//  Description:  阵灵们变得超级牛逼
// =====================================================================================
void CPetSlots::SuperBoostObjects ()
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();

    const TVecUINT16& rvecPetID = CBoostMgr::Instance().GetPetID();
    for (auto rID : rvecPetID)
    {
        CPetPtr pPet = AdoptPet(rID, true, true);
        if (pPet)
        {
            pPet->Super();
            _rUser.SendPkg(g_FormationProtS.BuildPkg_PetDataNotify(pPet->GetID(), 
                        pPet->GetSelected(), pPet->GetPetLevel(), pPet->GetPetExp()));
            Update2DB(pPet);
            if(pPet->GetPetLevel() >= 9)
            {
                NGlobalChatProt::SShowInfo stShow;
                stShow.qwInstID = pPlayer->GetUserID();
                pPet->GetShowInfo(stShow);
                NGlobalChatProt::TVecShowInfo vecShow;
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecShow.push_back(stShow);
                g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL, 0, eMsgPetTop, vecstring, vecShow);
            }
        }
    }
    //阵灵升级事件
    if(pPlayer)
    {
        TVecPetDataInfo vecPets;
        GetAllPets(vecPets);
        for (auto& rPet0 : vecPets)
        {
            TVecINT32 vecParam;
            vecParam.push_back(rPet0.wPetID);
            vecParam.push_back(rPet0.byLevel);
            for (auto& rPet : vecPets)
            {
                vecParam.push_back(rPet.byLevel);
            }
            CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
            if(pEventMgr)
                pEventMgr->OnEvent(eEventType_PetUpgrade,vecParam);
        }

    }
    UpdateGroupAttr();
}		// -----  end of function SuperBoostObjects  ----- //

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

