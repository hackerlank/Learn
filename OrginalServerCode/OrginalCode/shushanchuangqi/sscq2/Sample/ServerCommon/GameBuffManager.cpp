#include "GameBuffManager.h"
#include "RTime.h"
CGameBuffManager::CGameBuffManager()
{
    _bBufferDirty = false;
}

CGameBuffManager::~CGameBuffManager()
{
}

// 设定指定Buff
EBuffOpResult CGameBuffManager::AddBuff(UINT16 wBuffID)
{
    EBuffOpResult eResult = eBORFailed;
    SBuffCFGEx* pCFG = CGameBuffMgr::Instance().GetBuff(wBuffID);
    if (!pCFG)
        return eResult;
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end()) // 原Buff不存在，新增一个
    {
        SDBBuffInfo sDBBuffInfo;
        sDBBuffInfo.qwRoleID = GetRoleID();
        sDBBuffInfo.qwOwnerID = GetOwnerID();
        sDBBuffInfo.eBuffType = GetBuffType();
        sDBBuffInfo.wBuffID = wBuffID;
        sDBBuffInfo.vecBuffParam = pCFG->_vecParam;
        sDBBuffInfo.vecEffectMapID = pCFG->_vecEffectMapID;
        sDBBuffInfo.eBuffEffectType = (EBuffEffectType)pCFG->_EffectType;
        UINT32 dwNow = Time::Now();

        if (pCFG->_Time)
            sDBBuffInfo.dwBuffTime = dwNow + pCFG->_Time;
        sDBBuffInfo.eBuffState = eBSActived;
        eResult = eBORSuccess;
        _mapInfo.insert(make_pair(wBuffID, sDBBuffInfo));
        SBuffInfo sBuffInfo;
        GetBuffData(wBuffID, sBuffInfo);
        OnBuffChanged(eOpAdd, sBuffInfo);
        UpdateBuff2DB(sDBBuffInfo, eOpAdd);
    }
    else    // 原Buff存在，覆盖新数据
    {
        (it->second).vecBuffParam = pCFG->_vecParam;
        UINT32 dwNow = Time::Now();
        if (pCFG->_Time)
        {
            if (pCFG->_TotalTime)
            {
                if ((it->second).dwBuffTime >= dwNow + pCFG->_TotalTime) // 叠加时间已满
                    return eResult;
                (it->second).dwBuffTime += pCFG->_Time;
                if ((it->second).dwBuffTime > dwNow + pCFG->_TotalTime)
                    (it->second).dwBuffTime = dwNow + pCFG->_TotalTime;
            }
            else
                (it->second).dwBuffTime = dwNow + pCFG->_Time;
        }
        else
            (it->second).dwBuffTime = 0;
        (it->second).eBuffState = eBSActived;
        eResult = eBORSuccess;
        SBuffInfo sBuffInfo;
        GetBuffData(wBuffID, sBuffInfo);
        OnBuffChanged(eOpUpdate, sBuffInfo);
        UpdateBuff2DB(it->second, eOpUpdate);
    }
    for (auto& rID: pCFG->_vecSameBuffID)
    {
        RemoveBuff(rID);
    }
    SetBufferDirty(true);
    return eResult;
}

// 设定指定Buff
EBuffOpResult CGameBuffManager::SetBuff(UINT16 wBuffID, const TVecUINT32& vecParam, UINT32 dwBuffTime, bool bInit /* = false */)
{
    EBuffOpResult eResult = eBORFailed;
    SBuffCFGEx* pCFG = CGameBuffMgr::Instance().GetBuff(wBuffID);
    if (!pCFG)
        return eResult;
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end()) // 原Buff不存在，新增一个
    {
        SDBBuffInfo sDBBuffInfo;
        sDBBuffInfo.qwRoleID = GetRoleID();
        sDBBuffInfo.qwOwnerID = GetOwnerID();
        sDBBuffInfo.eBuffType = GetBuffType();
        sDBBuffInfo.wBuffID = wBuffID;
        sDBBuffInfo.vecBuffParam = vecParam;
        sDBBuffInfo.vecEffectMapID = pCFG->_vecEffectMapID;
        sDBBuffInfo.eBuffEffectType = (EBuffEffectType)pCFG->_EffectType;
        sDBBuffInfo.byBattleType    = pCFG->_BattleType;
        UINT32 dwNow = Time::Now();
        if (bInit || !dwBuffTime)
            sDBBuffInfo.dwBuffTime = dwBuffTime;
        else
            sDBBuffInfo.dwBuffTime = dwBuffTime + dwNow;
        sDBBuffInfo.eBuffState = eBSActived;
        _mapInfo.insert(make_pair(wBuffID, sDBBuffInfo));
        if (!bInit)
        {
            SBuffInfo sBuffInfo;
            GetBuffData(wBuffID, sBuffInfo);
            OnBuffChanged(eOpAdd, sBuffInfo);
            UpdateBuff2DB(sDBBuffInfo, eOpAdd);
        }
    }
    else    // 原Buff存在，覆盖新数据
    {
        (it->second).vecBuffParam = vecParam;
        UINT32 dwNow = Time::Now();
        if (bInit)
            (it->second).dwBuffTime = dwBuffTime;
        else
            (it->second).dwBuffTime = dwNow + dwBuffTime;
        (it->second).eBuffState = eBSActived;
        if (!bInit)
        {
            SBuffInfo sBuffInfo;
            GetBuffData(wBuffID, sBuffInfo);
            OnBuffChanged(eOpUpdate, sBuffInfo);
            UpdateBuff2DB(it->second, eOpUpdate);
        }
    }
    eResult = eBORSuccess;
    SetBufferDirty(true);
    return eResult;
}

// 新增指定Buff
EBuffOpResult CGameBuffManager::AddBuff(UINT16 wBuffID, const TVecUINT32& vecParam, UINT32 dwBuffTime)
{
    return SetBuff(wBuffID, vecParam, dwBuffTime, false);
}

// 消除指定Buff
EBuffOpResult CGameBuffManager::RemoveBuff(UINT16 wBuffID)
{
    LOG_CRI<<"MUTLI TEST RemoveBuff BEGIN:"<<wBuffID;
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
    {
        LOG_CRI<<"MUTLI TEST RemoveBuff END:"<<wBuffID;
        return eBORNotExisted;
    }
    SBuffInfo sBuffInfo;
    SDBBuffInfo sDBBuffInfo = it->second;
    EBuffOpResult eRes = GetBuffData(wBuffID, sBuffInfo);
    if (eRes != eBORExisted && eRes != eBOROverdue)
        _mapInfo.erase(it);
    OnBuffChanged(eOpDel, sBuffInfo);
    UpdateBuff2DB(sDBBuffInfo, eOpDel);
    SetBufferDirty(true);
    LOG_CRI<<"MUTLI TEST RemoveBuff END:"<<wBuffID;
    return eBORSuccess;
}

// 暂停指定Buff
EBuffOpResult CGameBuffManager::PauseBuff(UINT16 wBuffID)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORNotExisted;

    UINT32 dwNow = Time::Now();
    if (!CheckBuffTime(it))
        return eBOROverdue;
    if ((it->second).eBuffState == eBSActived)
    {
        if ((it->second).dwBuffTime)
            (it->second).dwBuffTime = (it->second).dwBuffTime - dwNow;
        (it->second).eBuffState = eBSPaused;
        UpdateBuff2DB(it->second, eOpUpdate);
        SetBufferDirty(true);
        return eBORSuccess;
    }
    SetBufferDirty(true);
    return eBORFailed;
}

// 恢复指定Buff
EBuffOpResult CGameBuffManager::ResumeBuff(UINT16 wBuffID)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORNotExisted;

    UINT32 dwNow = Time::Now();
    switch ((it->second).eBuffState)
    {
        case eBSActived:
            if (!CheckBuffTime(it))
                return eBOROverdue;
            else
                return eBORSuccess;
        case eBSPaused:
            (it->second).eBuffState = eBSActived;
            if ((it->second).dwBuffTime)
                (it->second).dwBuffTime += dwNow;
            UpdateBuff2DB(it->second, eOpUpdate);
            return eBORSuccess;
        default:
            break;
    }
    SetBufferDirty(true);
    return eBORFailed;
}

// 延长Buff效果值
EBuffOpResult CGameBuffManager::ExtendBuffValue(UINT16 wBuffID, UINT32 dwParam, UINT8 byIndex /* = 0 */)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORNotExisted;

    if (!CheckBuffTime(it))
        return eBOROverdue;

    switch ((it->second).eBuffState)
    {
        case eBSActived:
        case eBSPaused:
            (it->second).vecBuffParam.resize(byIndex + 1);
            (it->second).vecBuffParam[byIndex] += dwParam;
            UpdateBuff2DB(it->second, eOpUpdate);
            return eBORSuccess;
        default:
            break;
    }
    return eBORFailed;
}

// 延长Buff持续时间
EBuffOpResult CGameBuffManager::ExtendBuffTime(UINT16 wBuffID, UINT32 dwBuffTime)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORNotExisted;

    if (!CheckBuffTime(it))
        return eBOROverdue;

    switch ((it->second).eBuffState)
    {
        case eBSActived:
        case eBSPaused:
            (it->second).dwBuffTime += dwBuffTime;
            UpdateBuff2DB(it->second, eOpUpdate);
            return eBORSuccess;
        default:
            break;
    }
    return eBORFailed;
}

// 获取Buff的详细信息
EBuffOpResult CGameBuffManager::GetDBBuffData(UINT16 wBuffID, SDBBuffInfo& rDBBuffInfo)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORExisted;

    if (!CheckBuffTime(it))
        return eBOROverdue;

    UINT32 dwNow = Time::Now();
    rDBBuffInfo = it->second;
    if ((it->second).dwBuffTime)
        rDBBuffInfo.dwBuffTime = (it->second).dwBuffTime - dwNow;

    switch((it->second).eBuffState)
    {
        case eBSActived:
            return eBORSuccess;
        case eBSPaused:
            return eBORPaused;
        default:
            break;
    }
    return eBORFailed;
}

// 获取Buff的详细信息
EBuffOpResult CGameBuffManager::GetBuffData(UINT16 wBuffID, SBuffInfo& rBuffInfo)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return eBORExisted;

    UINT32 dwNow = Time::Now();

    if (!CheckBuffTime(it))
        return eBOROverdue;

    rBuffInfo.qwRoleID      = (it->second).qwRoleID; //对应玩家ID
    rBuffInfo.qwOwnerID     = (it->second).qwOwnerID; //所属实例ID(Role/Fighter/...
    rBuffInfo.wBuffID       = (it->second).wBuffID; //Buff种类
    rBuffInfo.eBuffState    = (it->second).eBuffState; //Buff当前状态
    switch((it->second).eBuffEffectType)
    {
        case eBETAttr:
            if ((it->second).vecBuffParam.size() >= 1)
                rBuffInfo.dwBuffCount   = (it->second).vecBuffParam[1]; //Buff叠加层数
            break;
        default:
            break;
    }
    rBuffInfo.vecBuffData = it->second.vecBuffParam;
    if ((it->second).dwBuffTime)
        rBuffInfo.dwBuffTime = (it->second).dwBuffTime - dwNow; //Buff失效时间

    switch((it->second).eBuffState)
    {
        case eBSActived:
            return eBORSuccess;
        case eBSPaused:
            return eBORPaused;
        default:
            break;
    }
    return eBORFailed;
}

EBuffOpResult CGameBuffManager::GetAllBuffData(TVecUINT16& rvecBuffID, TVecBuffInfo& rvecBuffInfo)
{
    EBuffOpResult eResult = eBORSuccess;
    for (auto it = _mapInfo.begin(); it != _mapInfo.end();)
    {
        UINT16 wBuffID = it->first;
        ++it;
        SBuffInfo sBuffInfo;
        EBuffOpResult eResult = GetBuffData(wBuffID, sBuffInfo);
        if (eResult != eBOROverdue)
        {
            rvecBuffID.push_back(wBuffID);
            rvecBuffInfo.push_back(sBuffInfo);
        }
    }
    return eResult;
}

void CGameBuffManager::TimerCheck(time_t tNow)
{
    TSetUINT16 setBuffToRemoved;
    for (auto it  = _mapInfo.begin(); it != _mapInfo.end(); ++it)
    {
        if ((it->second).eBuffState == eBSActived)
        {
            UINT32 dwNow = Time::Now();
            if ((it->second).dwBuffTime && dwNow >= (it->second).dwBuffTime) // 该Buff已经过期
            {
                (it->second).eBuffState = eBSOverdue;
                (it->second).dwBuffTime = dwNow - (it->second).dwBuffTime;    // Time值的为已经过期的时间长度
                setBuffToRemoved.insert(it->first);
            }
        }
    }
    for (auto it = setBuffToRemoved.begin(); it != setBuffToRemoved.end(); ++it)
    {
        RemoveBuff(*it);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CGameBuffMgr::Init(const string& strDir)
{
    string strPath = strDir + "Conf/Table/Buff.xml";
    CBuffLoader cLoader;
    if(!cLoader.LoadData(strPath))
    {
        LOG_CRI << "CGameBuffManager.LoadData fails! Path: " << strPath;
        return false;
    }
    for (auto it = _mapCFG.begin(); it != _mapCFG.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    _mapCFG.clear();
    for (auto it = cLoader._vecData.begin(); it != cLoader._vecData.end(); ++it)
    {
        SBuffCFGEx* pCFGEX = new (SBuffCFGEx);
        if (!pCFGEX)
            return false;
        pCFGEX->SetConfig(**it);
        _mapCFG.insert(make_pair(pCFGEX->_ID, pCFGEX));
    }
    return true;
}

SBuffCFGEx* CGameBuffMgr::GetBuff(UINT16 wBuffID)
{
    auto it = _mapCFG.find(wBuffID);
    if (it == _mapCFG.end())
        return NULL;
    else
        return it->second;
}

void CGameBuffMgr::TimerCheck(time_t tNow)
{
    for (auto it = _mapID2BuffManager.begin(); it != _mapID2BuffManager.end(); ++it)
    {
        (it->second)->TimerCheck(tNow);
    }
}

void CGameBuffMgr::AddBuffManager(UINT64 qwInstID, CGameBuffManager* pBuffManager)
{
    //_mapID2BuffManager[qwInstID] = pBuffManager;
    if(qwInstID == 0)
    {
        LOG_CRI << "ERR Insert AddBuffManager" << qwInstID;
        return ;
    }
    if(!(_mapID2BuffManager.insert(make_pair(qwInstID, pBuffManager)).second))
    {
        LOG_CRI << "ERR Insert AddBuffManager" << qwInstID;
    }
    else
    {
        LOG_CRI << "Insert CGameBuffMgr " << qwInstID; 
    }


}

void CGameBuffMgr::RemoveBuffManager(UINT64 qwInstID)
{
    if(qwInstID == 0)
    {
        return ;
    }
    auto it = _mapID2BuffManager.find(qwInstID);
    if (it != _mapID2BuffManager.end())
    {
        //LOG_CRI << "Remove  CGameBuffMgr  " << qwInstID; 
        _mapID2BuffManager.erase(it);
    }
    else
    {
        LOG_CRI << "ERR Remove AddBuffManager" << qwInstID; 

    }
}

bool CGameBuffManager::HasBuff(UINT16 wBuffID) const
{
    const_cast<CGameBuffManager&>(*this).CheckBuffTime(wBuffID);
    return  _mapInfo.find(wBuffID) != _mapInfo.end();
}

bool CGameBuffManager::CheckBuffTime(UINT16 wBuffID)
{
    auto it = _mapInfo.find(wBuffID);
    if (it == _mapInfo.end())
        return false;
    return CheckBuffTime(it);
}

bool CGameBuffManager::CheckBuffTime(MapInfo::iterator it)
{
    if ((it->second).eBuffState == eBSActived)
    {
        UINT32 dwNow = Time::Now();
        if ((it->second).dwBuffTime && dwNow >= (it->second).dwBuffTime) // 该Buff已经过期
        {
            (it->second).eBuffState = eBSOverdue;
            (it->second).dwBuffTime = dwNow - (it->second).dwBuffTime;    // Time值的为已经过期的时间长度
            RemoveBuff((it->second).wBuffID);
            return false;
        }
    }
    return true;
}



