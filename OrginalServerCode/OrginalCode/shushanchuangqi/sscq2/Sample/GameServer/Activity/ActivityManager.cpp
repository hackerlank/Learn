#include "ActivityManager.h"
#include "ActivityCFG.h"
#include "ActivityPointCFG.h"
#include "ActivityPoolCFG.h"
#include "Random.h"
#include "Tokenizer.h"
CActivityManager g_CActivityManager;

extern void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem);

bool CActivityManager::MakeAwardKey(const NActivityProt::SActivityAward &rAward,UINT64 &qwKey)
{
 //策划要求，取消VIP
#if 0
    if(rAward.byId >= byVIPBit)
    {
        LOG_CRI <<"rAward.byId > 16";
        return false;
    }
    if(rAward.byVIP != 0 && rAward.byVIP != 1)
    {
        LOG_CRI <<"rAward.byVIP != 0 && rAward.byVIP != 1";
        return false;
    }
    qwKey =  1 << (rAward.byId+rAward.byVIP*byVIPBit);
#endif 
     qwKey =  1 << rAward.byId;
    return true;
}


bool CActivityManager::Init()
{
    CActivityLoader oActivityLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Activity.xml";
    if(!oActivityLoader.LoadData(strPath))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(auto iter = oActivityLoader._vecData.begin(); iter != oActivityLoader._vecData.end();iter++)
    {
        SActivityCFG* pCfg = *(iter);
        ActivityAward sAward;
        NActivityProt::SActivityAward sKey; //每日活力奖励
        sKey.byId = pCfg->_ID;
        sKey.byVIP = 0;
        if(!MakeAwardKey(sKey,sAward.qwKey))
        { 
            LOG_CRI << "Key err";
            return false;
        }
        sAward.wActivity = pCfg->_Activity;
        sAward.byVIPLevel = 0;
        sAward.dwLootId = pCfg->_LootID;   
        if(!_mapActivityAward.insert(make_pair(sAward.qwKey,sAward)).second)
        {
            LOG_CRI <<"Activity repeat key";
            return false;
        }
#if 0 //策划要求取消
        sKey.byVIP = 1;
        if(!MakeAwardKey(sKey,sAward.qwKey))
        { 
            LOG_CRI << "Key err";
            return false;
        }
        sAward.wActivity = pCfg->_Activity;
        sAward.byVIPLevel = pCfg->_VIPLevel;
        sAward.dwLootId = pCfg->_VIPLootID;   
        if(!_mapActivityAward.insert(make_pair(sAward.qwKey,sAward)).second)
        {
            LOG_CRI <<"Activity repeat key";
            return false;
        }
#endif
    }

    CActivityPointLoader oActivityPointLoader;
    strPath = Config._strConfigDir + "Conf/Table/ActivityPoint.xml";
    if(!oActivityPointLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(auto iter = oActivityPointLoader._vecData.begin(); iter != oActivityPointLoader._vecData.end();iter++)
    {
        SActivityPointCFG* pCfg = *(iter);
        SActivityPointCFGEx Cfg;
        Cfg.wEventId = static_cast<UINT16>(pCfg->_Type);
        Cfg.wMinLevel = pCfg ->_Level;
        buf::Tokenizer tkMaxTimes(pCfg ->_MaxTimes, '|');
        for (size_t i = 0 ; i< tkMaxTimes.size();++i)
        {
            Cfg.vecMaxTimes.push_back(atoi(tkMaxTimes[i].c_str()));

        }
        Cfg.wActivity = pCfg->_GetActivity;
        Cfg._Share    = pCfg->_Share;
        GetItemFromString(Cfg._vecSharePrize,pCfg->_ShareAwardId);
        if(!_mapActivityPoint.insert(make_pair(Cfg.wEventId,Cfg)).second)
        {
            LOG_CRI << "Repeat Type For ActivityPoint, Type:" << Cfg.wEventId << " ID:" << pCfg->_ID;
            return false;
        }
    }
    CActivityPoolLoader oActivityPoolLoader;
    strPath = Config._strConfigDir + "Conf/Table/ActivityPool.xml";
    if(!oActivityPoolLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(auto iter = oActivityPoolLoader._vecData.begin(); iter != oActivityPoolLoader._vecData.end();iter++)
    {
        SActivityPoolCFG *pCfg = *(iter);
        if(!_mapVipActivityPool.insert(make_pair(pCfg->_VIPLevel,pCfg->_LootID)).second)
        {
            LOG_CRI << "Repeat  ActivityPool ";
        }
    }

    return true;
}

bool CActivityManager::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("Activity.xml" == strFile)
    {
        CActivityLoader oActivityLoader;
        strPath = Config._strConfigDir + "Conf/Table/Activity.xml";
        if(!oActivityLoader.LoadData(strPath))
        {
            LOG_CRI << "Load " << strPath << "ERR";
            return false;
        }
        for(auto iter = oActivityLoader._vecData.begin(); iter != oActivityLoader._vecData.end();iter++)
        {
            SActivityCFG* pCfg = *(iter);
            ActivityAward sAward;
            NActivityProt::SActivityAward sKey;
            sKey.byId = pCfg->_ID;
            sKey.byVIP = 0;
            if(!MakeAwardKey(sKey,sAward.qwKey))
            { 
                LOG_CRI << "Key err";
                return false;
            }
            sAward.wActivity = pCfg->_Activity;
            sAward.byVIPLevel = 0;
            sAward.dwLootId = pCfg->_LootID;   
            if(!_mapActivityAward.insert(make_pair(sAward.qwKey,sAward)).second)
            {
                LOG_CRI <<"Activity repeat key";
                return false;
            }
            sKey.byVIP = 1;
            if(!MakeAwardKey(sKey,sAward.qwKey))
            { 
                LOG_CRI << "Key err";
                return false;
            }
            sAward.wActivity = pCfg->_Activity;
            sAward.byVIPLevel = pCfg->_VIPLevel;
            sAward.dwLootId = pCfg->_VIPLootID;   
            if(!_mapActivityAward.insert(make_pair(sAward.qwKey,sAward)).second)
            {
                LOG_CRI <<"Activity repeat key";
                return false;
            }
        }
    }else if("ActivityPoint.xml" == strFile)
    {
        CActivityPointLoader oActivityPointLoader;
        strPath = Config._strConfigDir + "Conf/Table/ActivityPoint.xml";
        if(!oActivityPointLoader.LoadData((strPath)))
        {
            LOG_CRI << "Load " << strPath << "ERR";   
            return false;
        }
        for(auto iter = oActivityPointLoader._vecData.begin(); iter != oActivityPointLoader._vecData.end();iter++)
        {
            SActivityPointCFG* pCfg = *(iter);
            SActivityPointCFGEx Cfg;
            Cfg.wEventId = static_cast<UINT16>(pCfg->_Type);
            buf::Tokenizer tkMaxTimes(pCfg ->_MaxTimes, ',');
            for (size_t i = 0 ; i< tkMaxTimes.size();++i)
            {
                Cfg.vecMaxTimes.push_back(atoi(tkMaxTimes[i].c_str()));

            }
            Cfg.wMinLevel = pCfg ->_Level;
            Cfg.wActivity = pCfg->_GetActivity;
            if(!_mapActivityPoint.insert(make_pair(Cfg.wEventId,Cfg)).second)
            {
                LOG_CRI << "Repeat Type For ActivityPoint";
                return false;
            }
        }
    }else if("ActivityPool.xml" == strFile)
    {
        CActivityPoolLoader oActivityPoolLoader;
        strPath = Config._strConfigDir + "Conf/Table/ActivityPool.xml";
        if(!oActivityPoolLoader.LoadData((strPath)))
        {
            LOG_CRI << "Load " << strPath << "ERR";   
            return false;
        }
        for(auto iter = oActivityPoolLoader._vecData.begin(); iter != oActivityPoolLoader._vecData.end();iter++)
        {
            SActivityPoolCFG *pCfg = *(iter);
            if(!_mapVipActivityPool.insert(make_pair(pCfg->_VIPLevel,pCfg->_LootID)).second)
            {
                LOG_CRI << "Repeat  ActivityPool ";
            }
        }
    }

    return true;
}

const ActivityAward* CActivityManager::GetAward(UINT64 qwKey)
{
    auto it = _mapActivityAward.find(qwKey);
    if(it == _mapActivityAward.end())
    {
        return NULL;
    }
    return &(it->second);
}

void CActivityManager::GetActivityAward(NActivityProt::TVecActivityAward &vecAward,UINT64 qwData)
{
    for(auto it = _mapActivityAward.begin();it != _mapActivityAward.end();it++)
    {
        UINT64 qwKey = it->first;
        if( (qwData & qwKey) > 0)
        {
            UINT8 byBit = log(double(qwKey))/log(double(2)) + 0.5f;
            NActivityProt::SActivityAward sAward;
            if(byBit >=  byVIPBit)
            {
                sAward.byVIP = 1;
                sAward.byId = byBit - byVIPBit;
            }
            else
            {
                sAward.byVIP = 0;
                sAward.byId  = byBit;
            }
            vecAward.push_back(sAward);
        }
    }

}

const SActivityPointCFGEx * CActivityManager::GetActivityPoint(UINT16 wEventId)
{
    auto it =  _mapActivityPoint.find(wEventId);
    if(it == _mapActivityPoint.end())
    {
        return NULL;
    }
    return &(it->second);
}

UINT32 CActivityManager::GetLootIdByVip(UINT16 wVipLevel)
{
    auto it = _mapVipActivityPool.find(wVipLevel);
    if(it == _mapVipActivityPool.end())
    {
        return 0;
    }
    return it->second;
}

void CActivityManager::GetRandomActivityPoint(UINT8 byNum,vector<UINT16>&rvec)
{
    vector<UINT16> vecType;
    for(auto it = _mapActivityPoint.begin(); it != _mapActivityPoint.end();it++)
    {
        vecType.push_back(it->first);
    }
    UINT8 byCur =0;
    while(byCur < byNum && !vecType.empty())
    {
        byCur++;
        size_t Index = CRandom::RandInt(0,vecType.size()-1);
        rvec.push_back(vecType[Index]);
        vecType.erase(vecType.begin()+Index);
    }
}

void CActivityManager::GetAllActivityPoint(vector<UINT16>&rvec)
{
    for(auto it = _mapActivityPoint.begin(); it != _mapActivityPoint.end();it++)
    {
        rvec.push_back(it->first);
    }

}

UINT8 SActivityPointCFGEx::GetMaxTimesByVip(UINT8 byVipLevel) const
{
    if(vecMaxTimes.empty())
    {
        return 0;
    }
    if(byVipLevel  > vecMaxTimes.size())
    {
        return vecMaxTimes[vecMaxTimes.size() -1];
    }
    return vecMaxTimes[byVipLevel];
}

