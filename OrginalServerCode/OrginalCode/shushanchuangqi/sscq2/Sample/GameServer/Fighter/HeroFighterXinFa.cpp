#include "stdafx.h"
#include "Protocols.h"
#include "HeroFighterXinFa.h"
#include "FighterProt.h"
#include "FighterMgr.h"
#include "HeroFighter.h"
#include "UserMgr.h"
#include "Player.h"
#include "Fighter.h"
#include "SysMsgDefine.h"
#include "GameServerSysMail.h"

CHeroFighterXinFa::CHeroFighterXinFa()
{}

CHeroFighterXinFa::~CHeroFighterXinFa()
{}

void CHeroFighterXinFa::SetUser(const CUserPtr& pUser) 
{
    _pUser = pUser; 
}

CUserPtr CHeroFighterXinFa::GetUser() const 
{
    return _pUser.lock(); 
}

void CHeroFighterXinFa::SetFighter(const CFighterPtr& pFighter)
{
    _pFighter = pFighter; 
}

CFighterPtr CHeroFighterXinFa::GetFighter() const
{
    return _pFighter.lock();
}

void CHeroFighterXinFa::AddXinFaFromDB(UINT32 dwXinFaID, UINT8 byXinFaLvl, int iSlot)
{
    SXinFaInfo xinfaInfo;
    xinfaInfo.dwXinFaID = dwXinFaID;
    xinfaInfo.byXinFaLvl = byXinFaLvl;
    xinfaInfo.iSlot = iSlot;

    TVecFloat vecAttr;
    _LearnedXF.insert(std::make_pair(dwXinFaID, xinfaInfo));
    _LearnedXFAttr.insert(std::make_pair(dwXinFaID, vecAttr));
    _LearnedXFUpdateMark.insert(std::make_pair(dwXinFaID, 0));
    InitXinFaAttr(dwXinFaID);
    GetFighter()->SetDirty(true);
}

void CHeroFighterXinFa::HeroFighterXFInfo(TVecXinFaInfo& vecXinFa) const
{
    CHeroFighterXinFa* temp = const_cast<CHeroFighterXinFa*>(this);
    temp->AllLearnedXFInfo(vecXinFa);
}

void CHeroFighterXinFa::AllLearnedXFInfo(TVecXinFaInfo& vecXinFa)
{
    LearnedXF::iterator it = _LearnedXF.begin();
    for (; it != _LearnedXF.end(); it++)
    {
        SXinFaInfo xinfa;
        xinfa.dwXinFaID = it->second.dwXinFaID;
        xinfa.byXinFaLvl = it->second.byXinFaLvl;
        xinfa.iSlot = it->second.iSlot;
        vecXinFa.push_back(xinfa);
    }
}

EXinFaResult CHeroFighterXinFa::LearnXinFa(UINT32 dwXinFaID)
{
    if (!dwXinFaID || !GetUser() || !GetFighter())
    {
        LOG_CRI << "LearnXinFa_AAA:" << dwXinFaID;
        return eXinFaFailed;
    }

    const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
    if (!xinFaInfo)
    {
        LOG_CRI << "LearnXinFa_BBB:" << "cfg is error";
        return eXinFaFailed;
    }

    int iSlot = CheckXinFaSlot2(dwXinFaID);
    if (0 == iSlot)
    {
        LOG_CRI << "LearnXinFa_CCC:" << iSlot;
        return eXinFaFailed;
    }

    /*if (!CheckXinFaSlot(dwXinFaID, xinFaInfo->_Type))
        return eXinFaFailed;

    if (!CheckSpiritPower(dwXinFaID))
        return eXinFaFailed;*/

    buf::Tokenizer tk(xinFaInfo->_NeedItem, ',');
    if (2 != tk.size())
    {
        LOG_CRI << "LearnXinFa_DDD";
        return eXinFaFailed;
    }

    UINT16 wNeedItemID = atoi(tk[0].c_str());
    UINT16 wNeedCount = atoi(tk[1].c_str());
    UINT16 wCount = GetUser()->GetPack().GetItemCount(wNeedItemID);
    if (wCount < wNeedCount)
    {
        LOG_CRI << "LearnXinFa_EEE:" << wCount << "," << wNeedCount;
        return eXinFaFailed;
    }

    GetUser()->GetPack().DelItemByItemID(wNeedItemID, wNeedCount, true, NLogDataDefine::ItemTo_LearnXinFa);

    SXinFaInfo xinfaInfo;
    xinfaInfo.dwXinFaID = dwXinFaID;
    xinfaInfo.byXinFaLvl = 1;
    xinfaInfo.iSlot = iSlot;

    //散仙心法学习完直接装备,并且不能卸下(每种心法Type对应相应槽位（1-7：主、坎、坤、乾、兑、震、离）
    //xinfaInfo.iSlot = xinFaInfo->_Type;

    TVecFloat vecAttr;
    _LearnedXF.insert(std::make_pair(dwXinFaID, xinfaInfo));
    _LearnedXFAttr.insert(std::make_pair(dwXinFaID, vecAttr));
    _LearnedXFUpdateMark.insert(std::make_pair(dwXinFaID, 0));

    Update2DB(eOpAdd, dwXinFaID);

    GetUser()->SendPkg(g_FighterProtS.BuildPkg_XinFaNotify(GetFighter()->GetInstID(), dwXinFaID, xinfaInfo.byXinFaLvl, xinfaInfo.iSlot));
    
    InitXinFaAttr(dwXinFaID);
    GetFighter()->SetDirty(true);
    
    //记入LogServer日志
    UINT64 qwResult = static_cast<UINT64>(dwXinFaID);
    WriteFighterLog(eOptType_XinFa,0,qwResult,GetFighter()->GetFighterID());
    //事件
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(GetFighter()->GetFighterID());
        vecParam.push_back(dwXinFaID);
        vecParam.push_back(_LearnedXF.size());

        TVecINT32 vecParam2;
        vecParam2.push_back(dwXinFaID);
        vecParam2.push_back(0);
        vecParam2.push_back(1); //默认1级
        LearnedXF::iterator iter = _LearnedXF.begin();
        for (; iter!=_LearnedXF.end(); iter++)
        {
            if( dwXinFaID != iter->second.dwXinFaID)
            {
                vecParam2.push_back(iter->second.byXinFaLvl);
            }
        }

        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
        {
            pEventMgr->OnEvent(eEventType_FighterLearningRecipe, vecParam);
            pEventMgr->OnEvent(eEventType_XinfaLevelUp,vecParam2);
        }
    }

    return eXinFaSucc;
}

EXinFaResult CHeroFighterXinFa::XinFaUpgrade(UINT32 dwXinFaID)
{
    if (!dwXinFaID || !GetUser() || !GetFighter())
        return eXinFaFailed;

    UINT8 curLevel = GetXinFaLevel(dwXinFaID);
    if (curLevel >= SParamConfig::byXinfaMaxLevel)
        return eXinFaFailed;

    const SXinfaEffectCFG* xinFaLevelInfo = CFighterMgr::GetXinFaLevelCfg(dwXinFaID, curLevel);
    if (!xinFaLevelInfo)
        return eXinFaFailed;

    if (EMONEY_NONE != xinFaLevelInfo->_costtype)
    {
        if (!GetUser()->CanSubMoney(EMoneyType(xinFaLevelInfo->_costtype), xinFaLevelInfo->_cost))
            return eXinFaFailed;
    }

    UINT16 wNeedItemID = xinFaLevelInfo->_costtype2;
    UINT16 wNeedCount = xinFaLevelInfo->_cost2;
    UINT16 wCount = GetUser()->GetPack().GetItemCount(xinFaLevelInfo->_costtype2);
    if (wCount < wNeedCount)
        return eXinFaFailed;

    GetUser()->SubMoney(EMONEY_PEXP, xinFaLevelInfo->_cost,NLogDataDefine::ItemTo_HeroXinFaUpgrade);
    GetUser()->GetPack().DelItemByItemID(wNeedItemID, wNeedCount, true, NLogDataDefine::ItemTo_HeroXinFaUpgrade);

    curLevel++;
    SetXinFaLevel(dwXinFaID, curLevel);
    Update2DB(eOpUpdate, dwXinFaID);

    SetDirty(dwXinFaID, true);
    GetFighter()->SetDirty(true);

    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
    {
        GetUser()->SendPkg(g_FighterProtS.BuildPkg_XinFaNotify(GetFighter()->GetInstID(), dwXinFaID, it->second.byXinFaLvl, it->second.iSlot));
    }

#define SETID(var,begin) var=((var&0xFFFFFFFF00000000)|(begin))
#define SETLEVEL(var,end) var=(var|((end)<<32))
     
    //记入LogServer日志
    UINT64 qwResult = 0;
    SETID(qwResult,dwXinFaID);
    UINT64 qwLv = static_cast<UINT64>(curLevel);
    SETLEVEL(qwResult,qwLv);
    WriteFighterLog(eOptType_XinFa,1,qwResult,GetFighter()->GetFighterID());
    //事件
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam2;
        vecParam2.push_back(dwXinFaID);
        vecParam2.push_back(0);   // no param
        vecParam2.push_back(curLevel);

        TVecINT32 vecParam;
        vecParam.push_back(GetFighter()->GetFighterID());
        vecParam.push_back(dwXinFaID);
        LearnedXF::iterator iter = _LearnedXF.begin();
        for (; iter!=_LearnedXF.end(); iter++)
        {
            vecParam.push_back(iter->second.byXinFaLvl);

            if( dwXinFaID != iter->second.dwXinFaID)
            {
                vecParam2.push_back(iter->second.byXinFaLvl);
            }
        }

        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
        {
            pEventMgr->OnEvent(eEventType_FighterRecipeUpgrade, vecParam);
            pEventMgr->OnEvent(eEventType_XinfaLevelUp,vecParam2);
        }
    }

    return eXinFaSucc;
}

EXinFaResult CHeroFighterXinFa::XinFaDisperse(UINT32 dwXinFaID)
{
    return eXinFaFailed;

    UINT32 cost = 0;
    UINT16 dwItemID = 0;
    UINT16 dwItemCount = 0;
    UINT8 curLevel = GetXinFaLevel(dwXinFaID);
    if(1 == curLevel)
        return eXinFaFailed;

    for (UINT8 i=1; i<curLevel; i++)
    {
        const SXinfaEffectCFG* xinFaLevelInfo = CFighterMgr::GetXinFaLevelCfg(dwXinFaID, i);
        if (!xinFaLevelInfo)
            return eXinFaFailed;

        if (EMONEY_PEXP != xinFaLevelInfo->_costtype)
            return eXinFaFailed;

        cost += xinFaLevelInfo->_cost;
        dwItemCount += xinFaLevelInfo->_cost2;
        dwItemID = xinFaLevelInfo->_costtype2;
    }

    if (0 == cost * 60 % 100)
        cost = cost * 60 / 100;
    else
        cost = cost * 60 / 100 + 1;

    if (0 == dwItemCount * 60 % 100)
        dwItemCount = dwItemCount * 60 / 100;
    else
        dwItemCount = dwItemCount * 60 / 100 + 1;
    
    //发送邮件
    TVecItemGenInfo vecItems;

    SItemGenInfo stItemGenA;
    stItemGenA.wItemID = EMONEY_PEXP;
    stItemGenA.dwCount = cost;
    vecItems.push_back(stItemGenA);
    
    SItemGenInfo stItemGenB;
    stItemGenB.wItemID = dwItemID;
    stItemGenB.dwCount = dwItemCount;
    stItemGenB.eBindType = eBindGet;
    vecItems.push_back(stItemGenB);

    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_XINFA_AWARD;

    string strXinFaName = "";
    const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
    if (xinFaInfo)
        strXinFaName = xinFaInfo->_Name;
    stBody.vecParam.push_back(strXinFaName);

    TVecUINT64 vecTargets;
    vecTargets.push_back(GetUser()->GetUserID());
    GameServerSysMail::SendSysMail(TITLE_XINFA_AWARD, TITLE_XINFA_AWARD, stBody, vecTargets, &vecItems);

    SetXinFaLevel(dwXinFaID, 1);
    Update2DB(eOpUpdate, dwXinFaID);
    
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
        GetUser()->SendPkg(g_FighterProtS.BuildPkg_XinFaNotify(GetFighter()->GetInstID(), dwXinFaID, it->second.byXinFaLvl, it->second.iSlot));

    SetDirty(dwXinFaID, true);
    GetFighter()->SetDirty(true);

    return eXinFaSucc;
}

bool CHeroFighterXinFa::IsXinFa(UINT32 dwXinFaID)
{
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it == _LearnedXF.end())
        return false;

    return true;
}

bool CHeroFighterXinFa::CheckXinFaSlot(UINT32 dwXinFaID, UINT8 type)
{
    //检测该心法是否已学
    if (IsXinFa(dwXinFaID))
        return false;

    SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(GetFighter()->GetFighterID());
    if (!pFighterCFG)
        return false;

    //检测心法ID是否正确
    bool mark = false;
    for (size_t i=0; i<pFighterCFG->_vecXinFaID.size(); i++)
    {
        if (dwXinFaID == pFighterCFG->_vecXinFaID[i])
        {
            mark = true;
            break;
        }
    }        
    if (!mark)
        return false;
    
    //检测心法槽 是否开启
    bool markA = false;

    //TODO
    if (!markA)
        return false;

    return true;
}

int CHeroFighterXinFa::CheckXinFaSlot2(UINT32 dwXinFaID)
{
    //检测该心法是否已学
    if (IsXinFa(dwXinFaID))
        return 0;

    SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(GetFighter()->GetFighterID());
    if (!pFighterCFG)
        return 0;

    //检测心法ID是否正确
    for (size_t i=0; i<pFighterCFG->_vecXinFaID.size(); i++)
    {
        if (dwXinFaID == pFighterCFG->_vecXinFaID[i])
            return (i+1);
    }

    return 0;
}

bool CHeroFighterXinFa::CheckSpiritPower(UINT32 dwXinFaID)
{
    UINT32 dwLearnedXinFaSpiritPower = 0;
    LearnedXF::iterator it = _LearnedXF.begin();
    for (; it!=_LearnedXF.end(); it++)
    {
        if (it->second.dwXinFaID)
        {
            const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(it->second.dwXinFaID);
            if (xinFaInfo)
                dwLearnedXinFaSpiritPower += xinFaInfo->_Limit;
        }
    }

    if (GetFighter()->GetSpiritPower() > dwLearnedXinFaSpiritPower)
    {
        const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
        if (xinFaInfo)
            if (GetFighter()->GetSpiritPower() - dwLearnedXinFaSpiritPower >= xinFaInfo->_Limit)
                return true;
    }

    return false;
}

int CHeroFighterXinFa::GetXinFaSlot(UINT32 dwXinFaID)
{
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
        return it->second.iSlot;

    return 0;
}

void CHeroFighterXinFa::SetXinFaSlot(UINT32 dwXinFaID, int iSlot)
{
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
        it->second.iSlot = iSlot;

    return;
}

UINT8 CHeroFighterXinFa::GetXinFaLevel(UINT32 dwXinFaID)
{
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
        return it->second.byXinFaLvl;

    return 0;
}

void CHeroFighterXinFa::SetXinFaLevel(UINT32 dwXinFaID, UINT8 byXinFaLevel)
{
    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
        it->second.byXinFaLvl = byXinFaLevel;

    return;
}

void CHeroFighterXinFa::Update2DB(EDataChange eDataChange, UINT32 dwXinFaID)
{
    UINT64 qwUserID = 0;
    UINT64 qwFighterID = 0;

    if (GetUser())
        qwUserID = GetUser()->GetUserID();

    if (GetFighter())
        qwFighterID = GetFighter()->GetInstID();

    if (!qwUserID || !qwFighterID || !dwXinFaID)
        return;

    /*const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
    if (!xinFaInfo)
        return;

    //散仙心法学习完直接装备,并且不能卸下(每种心法Type对应相应槽位（1-7：主、坎、坤、乾、兑、震、离）
    int iSlot = xinFaInfo->_Type;
    if (iSlot < 1 || iSlot > 7)
        return;*/

    string strData;
    COutArchive iar(strData);
    SXinFaDBInfo oXinFaDBInfo;

    memset(&oXinFaDBInfo, 0x00, sizeof(oXinFaDBInfo));
    oXinFaDBInfo.qwRoleID = qwUserID;
    oXinFaDBInfo.qwOwnerID = qwFighterID;
    oXinFaDBInfo.dwXinFaID = dwXinFaID;
    oXinFaDBInfo.byXinFaLvl = GetXinFaLevel(dwXinFaID);
    oXinFaDBInfo.iSlot = GetXinFaSlot(dwXinFaID);

    iar << oXinFaDBInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eTypeXinFaInfo, eDataChange, strData);
}

TVecFloat CHeroFighterXinFa::GetHeroFighterXinFaAttr() const
{
    TVecFloat vecAttr;
    LearnedXF::const_iterator it = _LearnedXF.begin();
    for (; it!=_LearnedXF.end(); it++)
    {
        if (it->second.dwXinFaID)
        {
            CHeroFighterXinFa* temp = const_cast<CHeroFighterXinFa*>(this);
            temp->AppendAttr(it->second.dwXinFaID, vecAttr);
        }
    }

    return vecAttr;
}

void CHeroFighterXinFa::InitXinFaAttr(UINT32 dwXinFaID)
{
    const SXinfaEffectCFG* pXinFaLevelCFG = CFighterMgr::GetXinFaLevelCfg(dwXinFaID, GetXinFaLevel(dwXinFaID));
    if (!pXinFaLevelCFG)
        return;

    LearnedXFAttr::iterator it = _LearnedXFAttr.find(dwXinFaID);
    if (it == _LearnedXFAttr.end())
        return;

    VECATTR_RESET(it->second);
    PHYATK_SET(it->second, pXinFaLevelCFG);
    MGCATK_SET(it->second, pXinFaLevelCFG);
    PHYDEF_SET(it->second, pXinFaLevelCFG);
    MGCDEF_SET(it->second, pXinFaLevelCFG);
    PHYRDC_SET(it->second, pXinFaLevelCFG);
    MGCRDC_SET(it->second, pXinFaLevelCFG);
    MAXHP_SET(it->second, pXinFaLevelCFG);
    SPEED_SET(it->second, pXinFaLevelCFG);
    HIT_SET(it->second, pXinFaLevelCFG);
    HITRATE_SET(it->second, pXinFaLevelCFG);
    DODGE_SET(it->second, pXinFaLevelCFG);
    DODGERATE_SET(it->second, pXinFaLevelCFG);
    CRITICAL_SET(it->second, pXinFaLevelCFG);
    CRTRATE_SET(it->second, pXinFaLevelCFG);
    ANTICRITCAL_SET(it->second, pXinFaLevelCFG);
    ANTICRTRATE_SET(it->second, pXinFaLevelCFG);
    BLOCK_SET(it->second, pXinFaLevelCFG);
    BLOCKRATE_SET(it->second, pXinFaLevelCFG);
    PIERCE_SET(it->second, pXinFaLevelCFG);
    PIERCERATE_SET(it->second, pXinFaLevelCFG);
    COUNTER_SET(it->second, pXinFaLevelCFG);
    COUNTERRATE_SET(it->second, pXinFaLevelCFG);
    RESIST_SET(it->second, pXinFaLevelCFG);
    RESISTRATE_SET(it->second, pXinFaLevelCFG);
    INITAURA_SET(it->second, pXinFaLevelCFG);
    MAXAURA_SET(it->second, pXinFaLevelCFG);
    CRIEXTRAADD_SET(it->second, pXinFaLevelCFG);
    CRIEXTRARDC_SET(it->second, pXinFaLevelCFG);
    METALATK_SET(it->second, pXinFaLevelCFG);
    WOODATK_SET(it->second, pXinFaLevelCFG);
    WATERATK_SET(it->second, pXinFaLevelCFG);
    FIREATK_SET(it->second, pXinFaLevelCFG);
    EARTHATK_SET(it->second, pXinFaLevelCFG);
    METALDEF_SET(it->second, pXinFaLevelCFG);
    WOODDEF_SET(it->second, pXinFaLevelCFG);
    WATERDEF_SET(it->second, pXinFaLevelCFG);
    FIREDEF_SET(it->second, pXinFaLevelCFG);
    EARTHDEF_SET(it->second, pXinFaLevelCFG);
    PHYATK_PER_SET(it->second, pXinFaLevelCFG);
    MGCATK_PER_SET(it->second, pXinFaLevelCFG);
    PHYDEF_PER_SET(it->second, pXinFaLevelCFG);
    MGCDEF_PER_SET(it->second, pXinFaLevelCFG);
    MAXHP_PER_SET(it->second, pXinFaLevelCFG);
    SPEED_PER_SET(it->second, pXinFaLevelCFG);
    HIT_PER_SET(it->second, pXinFaLevelCFG);
    DODGE_PER_SET(it->second, pXinFaLevelCFG);
    CRITICAL_PER_SET(it->second, pXinFaLevelCFG);
    ANTICRITCAL_PER_SET(it->second, pXinFaLevelCFG);
    BLOCK_PER_SET(it->second, pXinFaLevelCFG);
    PIERCE_PER_SET(it->second, pXinFaLevelCFG);
    COUNTER_PER_SET(it->second, pXinFaLevelCFG);
    RESIST_PER_SET(it->second, pXinFaLevelCFG);
    ANTIEFFECT_SET(it->second, pXinFaLevelCFG);
}

void CHeroFighterXinFa::RebuildAttr(UINT32 dwXinFaID)
{
    if (IsDirty(dwXinFaID))
    {
        InitXinFaAttr(dwXinFaID);
        SetDirty(dwXinFaID, false);
    }

    return;
}

void CHeroFighterXinFa::AppendAttr(UINT32 dwXinFaID, TVecFloat& vecAttr)
{
    if (IsDirty(dwXinFaID))
        RebuildAttr(dwXinFaID);

    LearnedXFAttr::iterator it = _LearnedXFAttr.find(dwXinFaID);
    if (it != _LearnedXFAttr.end())
        vecAttr += it->second;
    
    return;
}

void CHeroFighterXinFa::SetDirty(UINT32 dwXinFaID, bool mark)
{
    LearnedXFUpdateMark::iterator it = _LearnedXFUpdateMark.find(dwXinFaID);
    if (it == _LearnedXFUpdateMark.end())
        return;
    
    if (mark)
        it->second = 1;
    else
        it->second = 0;

    return;
}

bool CHeroFighterXinFa::IsDirty(UINT32 dwXinFaID)
{
    LearnedXFUpdateMark::iterator it = _LearnedXFUpdateMark.find(dwXinFaID);
    if (it == _LearnedXFUpdateMark.end())
        return false;

    if (!it->second)
        return false;

    return true;
}

/*************GM****************/
bool CHeroFighterXinFa::GMLearnXinFa(UINT32 dwXinFaID)
{
    if (!dwXinFaID || !GetUser() || !GetFighter())
        return false;

    const SXinfaCFG* xinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
    if (!xinFaInfo)
        return false;

    int iSlot = CheckXinFaSlot2(dwXinFaID);
    if (0 == iSlot)
        return false;

    /*if (!CheckXinFaSlot(dwXinFaID, xinFaInfo->_Type))
        return false;

    if (!CheckSpiritPower(dwXinFaID))
        return false;*/

    SXinFaInfo xinfaInfo;
    xinfaInfo.dwXinFaID = dwXinFaID;
    xinfaInfo.byXinFaLvl = 1;
    xinfaInfo.iSlot = iSlot;
    //散仙心法学习完直接装备,并且不能卸下(每种心法Type对应相应槽位（1-7：主、坎、坤、乾、兑、震、离）
    //xinfaInfo.iSlot = xinFaInfo->_Type;

    TVecFloat vecAttr;
    _LearnedXF.insert(std::make_pair(dwXinFaID, xinfaInfo));
    _LearnedXFAttr.insert(std::make_pair(dwXinFaID, vecAttr));
    _LearnedXFUpdateMark.insert(std::make_pair(dwXinFaID, 0));

    Update2DB(eOpAdd, dwXinFaID);

    GetUser()->SendPkg(g_FighterProtS.BuildPkg_XinFaNotify(GetFighter()->GetInstID(), dwXinFaID, xinfaInfo.byXinFaLvl, xinfaInfo.iSlot));
    
    InitXinFaAttr(dwXinFaID);
    GetFighter()->SetDirty(true);

    return true;
}

bool CHeroFighterXinFa::GMXinFaUpgrade(UINT32 dwXinFaID)
{
    if (!dwXinFaID || !GetUser() || !GetFighter())
        return false;

    UINT8 curLevel = GetXinFaLevel(dwXinFaID);
    if (curLevel >= SParamConfig::byXinfaMaxLevel)
        return false;

    SetXinFaLevel(dwXinFaID, SParamConfig::byXinfaMaxLevel);
    Update2DB(eOpUpdate, dwXinFaID);

    SetDirty(dwXinFaID, true);
    GetFighter()->SetDirty(true);

    LearnedXF::iterator it = _LearnedXF.find(dwXinFaID);
    if (it != _LearnedXF.end())
    {
        GetUser()->SendPkg(g_FighterProtS.BuildPkg_XinFaNotify(GetFighter()->GetInstID(), dwXinFaID, it->second.byXinFaLvl, it->second.iSlot));
    }

    return true;
}

void CHeroFighterXinFa::WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID)
{
    CFighterPtr pFighter = GetFighter();
    if(!pFighter)
        return ;
    NLogDataDefine::SFighterLogPtr ptrLog(new NLogDataDefine::SFighterLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SFighterLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = GetUser()->GetRoleID();
    rLog.wFighterId  = wID;
    rLog.sName       = pFighter->GetName();
    rLog.wLevel      = pFighter->GetLevel();
    rLog.byQuality   = pFighter->GetColor();
    rLog.eOptType    = eType;
    rLog.dwType      = dwDetail;
    rLog.qwResult    = qwResult;
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

void CHeroFighterXinFa::FighterXinFaDismiss(TVecItemGenInfo& vecItems)
{
    TVecXinFaInfo vecXinFaInfo;
    HeroFighterXFInfo(vecXinFaInfo);
    SItemGenInfo stItemXinFa1;
    stItemXinFa1.eBindType = eBindGet;
    for (size_t i = 0; i < vecXinFaInfo.size(); ++ i)
    {
        UINT32 dwXinFaID = vecXinFaInfo[i].dwXinFaID;
        const SXinfaCFG* pXinFaInfo = CFighterMgr::GetXinFaCfg(dwXinFaID);
        if (pXinFaInfo)
        {
            buf::Tokenizer tk(pXinFaInfo->_NeedItem, ',');
            if (tk.size() >= 2)
            {
                SItemGenInfo stItemXinFa;
                stItemXinFa.wItemID = atoi(tk[0].c_str());
                stItemXinFa.dwCount = atoi(tk[1].c_str());
                stItemXinFa.eBindType = eBindGet;
                if (stItemXinFa.wItemID && stItemXinFa.dwCount)
                    vecItems.push_back(stItemXinFa);
            }
        }
        SItemGenInfo stItemXinFa2;
        stItemXinFa2.eBindType = eBindGet;
        for (int j = 0; j < vecXinFaInfo[i].byXinFaLvl; ++ j)
        {
            const SXinfaEffectCFG* pXinFaLevelInfo = CFighterMgr::GetXinFaLevelCfg(dwXinFaID, j);
            if (!pXinFaLevelInfo)
                continue;
            stItemXinFa1.wItemID = pXinFaLevelInfo->_costtype;
            stItemXinFa1.dwCount += pXinFaLevelInfo->_cost;
            stItemXinFa2.wItemID = pXinFaLevelInfo->_costtype2;
            stItemXinFa2.dwCount += pXinFaLevelInfo->_cost2;
        }
        if (stItemXinFa2.wItemID && stItemXinFa2.dwCount)
            vecItems.push_back(stItemXinFa2);

        Update2DB(eOpDel, dwXinFaID);
        _LearnedXF.erase(dwXinFaID);
        _LearnedXFAttr.erase(dwXinFaID);
        _LearnedXFUpdateMark.erase(dwXinFaID);
    }
    if (stItemXinFa1.wItemID && stItemXinFa1.dwCount)
        vecItems.push_back(stItemXinFa1);
}

