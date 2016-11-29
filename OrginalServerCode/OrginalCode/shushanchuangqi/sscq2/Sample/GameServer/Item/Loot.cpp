#include "stdafx.h"
#include "Loot.h"
#include "Random.h"
#include "UtilFunc.h"
#include "LootsCFG.h"
#include "ItemMgr.h"
#include "Protocols.h"
#include "SysMsgDefine.h"

using namespace NItemProt;

#ifndef LOOT_CHANCE_BASE
#define LOOT_CHANCE_BASE (10000-1)
#endif

static bool ParseLootItem(const std::string& cfg, SLootCell &li)
{
    TVecString item;
    SplitToText(cfg, ";", item);
    if(item.size() < 2)
        return false;

    li.iid = atoi(item[0].c_str());
    if(!li.iid)
        return false;
    li.chance = atoi(item[1].c_str());
    if(item.size() > 2)
    {
        li.count = atoi(item[2].c_str());
        if(item.size() > 3)
        {
            li.bind = (EBindType)(atoi(item[3].c_str()));
            // TODO: 没有对时效性配置的支持
        }
    }
    return true;
}

static bool AddLootItem(const SLootCell&li, std::vector<SItemGenInfo> &items,TVecResource& vecRes)
{
    if(li.iid < LOOT_PACKID_MIN)
    {
       if(li.iid > EMONEY_NONE && li.iid < EMONEY_END)
       {
           SResource stReSource;
           stReSource._eRes = static_cast<EMoneyType>(li.iid);
           stReSource._dwValue = li.count;
           vecRes.push_back(stReSource);

       }
       else
       {
        SItemGenInfo sItemInfo;
        sItemInfo.wItemID = li.iid;
        sItemInfo.dwCount = li.count;
        sItemInfo.eBindType = li.bind;
        items.push_back(sItemInfo);
       }
        return true;
    }
    for(UINT32 i = 0; i < li.count;i++)
    {
        if(!LOOT.Roll(li.iid, items,vecRes))
        {
            return false;
        }
    }
    return true;
}

static bool FetchLootItem( const SLootCell&li, std::vector<SItemGenInfo> &items,TVecResource& vecRes )
{
    if(li.iid < LOOT_PACKID_MIN)
    {
       if(li.iid > EMONEY_NONE && li.iid < EMONEY_END)
       {
           SResource stReSource;
           stReSource._eRes = static_cast<EMoneyType>(li.iid);
           stReSource._dwValue = li.count;
           vecRes.push_back(stReSource);

       }
       else
       {
        SItemGenInfo sItemInfo;
        sItemInfo.wItemID = li.iid;
        sItemInfo.dwCount = li.count;
        sItemInfo.eBindType = li.bind;
        items.push_back(sItemInfo);
       }
        return true;
    }
    return LOOT.FetchAll(li.iid, items,vecRes);
}

bool CLootMgr::Loot::initLootCells( const string& lcfg )
{
    TVecString cfg;
    SplitToText(lcfg, "|", cfg);
    if(!cfg.size())
    {
        LOG_CRI<<"Load Config for Loot "<<_dwLootID<<" failed: empty config: "<<lcfg;
        return false;
    }
    bool shot = false;
    for(size_t i = 0; i < cfg.size(); ++i)
    {
        SLootCell li;
        if(!ParseLootItem(cfg[i], li))
        {
            LOG_CRI<<"Load Config for Loot "<<_dwLootID<<" failed: syntax error: ("<<cfg[i]<<") in "<<lcfg;
            return false;
        }
        _vecCells.push_back(li);
        shot = true;
    }
    return shot;
}

bool CLootMgr::Loot::init(ELootType type, const string& lcfg)
{
    if(lcfg.empty())
    {
        LOG_CRI<<"Load Config for Loot "<<_dwLootID<<" failed: empty config";
        return false;
    }
    _vecCells.clear();
    bool ret = initLootCells(lcfg);
    if(ret)
        this->_eLootType = type;
    return ret;
}

bool CLootMgr::Loot::roll(std::vector<SItemGenInfo>& vecItems,TVecResource& vecRes)
{
    switch(_eLootType)
    {
        case ELOOT_ALL_ABOVE:
            return rollAllAbove(vecItems,vecRes);
        case ELOOT_ONE_FROM_ALL:
            return rollOneFromAll(vecItems,vecRes);
        case ELOOT_EACH_CHANCE:
            return rollEachChance(vecItems,vecRes);
        default:
            break;

    }
    return false;
}

bool CLootMgr::Loot::fetchall( std::vector<SItemGenInfo>& items,TVecResource &vecRes )
{
    for(size_t i = 0; i < _vecCells.size(); ++i)
    {
        const SLootCell& li = _vecCells[i];
        FetchLootItem(li, items,vecRes);
    }
    return true;
}

bool CLootMgr::Loot::rollAllAbove( std::vector<SItemGenInfo>& vecItems,TVecResource& vecRes )
{
    if(!_vecCells.size())
        return false;

    UINT16 chance = CRandom::RandInt(0, LOOT_CHANCE_BASE);
    LOG_DBG<<"chance: "<<chance;
    bool shot = false;
    for(size_t i = 0; i < _vecCells.size(); ++i)
    {
        const SLootCell& li = _vecCells[i];
        if(chance < li.chance)
            if(AddLootItem(li, vecItems,vecRes))
                shot = true;
    }
    return shot;
}

bool CLootMgr::Loot::rollOneFromAll( std::vector<SItemGenInfo>& vecItems,TVecResource& vecRes )
{
    if(!_vecCells.size())
        return false;

    UINT16 chance = CRandom::RandInt(0, LOOT_CHANCE_BASE);
    LOG_DBG<<"chance: "<<chance;
    for(size_t i = 0; i < _vecCells.size(); ++i)
    {
        const SLootCell& li = _vecCells[i];
        if(chance < li.chance)
            return AddLootItem(li, vecItems,vecRes);
        else
            chance -= li.chance;
    }
    return false;
}

bool CLootMgr::Loot::rollEachChance( std::vector<SItemGenInfo>& vecItems,TVecResource& vecRes )
{
    if(!_vecCells.size())
        return false;

    bool shot = false;
    for(size_t i = 0; i < _vecCells.size(); ++i)
    {
        const SLootCell& li = _vecCells[i];
        UINT16 chance = CRandom::RandInt(0, LOOT_CHANCE_BASE);
        LOG_DBG<<"chance: "<<chance;
        if(chance < li.chance)
            if(AddLootItem(li, vecItems,vecRes))
                shot = true;
    }
    return shot;
}

bool CLootMgr::Loot::isonefromall()
{
    if(_eLootType != ELOOT_ONE_FROM_ALL)
        return false;
    for(size_t i = 0; i < _vecCells.size(); ++i)
    {
        const SLootCell& li = _vecCells[i];
        if(!LOOT.IsRollOneLoot(li.iid))
            return false;
    }
    return true;
}

bool CLootMgr::Init()
{
    return LoadConfig();
}

bool CLootMgr::LoadConfig(bool bReload)
{
    CLootsLoader lootcfg;
    string strPath = Config._strConfigDir + "Conf/Table/Loots.xml";
    if(!lootcfg.LoadData(strPath))
        return false;
    TLootMap mapLoot;
    LOG_INF << "Loading Loot Config...";
    for(auto p=lootcfg._vecData.begin(),e=lootcfg._vecData.end(); p!=e; ++p)
    {
        const SLootsCFG* cfg = *p;
        if(!AddLootConfig(mapLoot, cfg->_ID, (ELootType)(cfg->_LootType), cfg->_products))
            return false;
    }
    if(!CheckLootConfig(mapLoot))
        return false;
    _oLootMap.swap(mapLoot);
    return true;
}

bool CLootMgr::AddLootConfig( TLootMap& mapLoot, UINT32 id, ELootType type, const string& lcfg )
{
    if(mapLoot.find(id) != mapLoot.end())
    {
        LOG_CRI<<"Load Config for Loot "<<id<<" failed: loot id duplicated";
        return false;
    }
    Loot l(id);
    if(!l.init(type, lcfg))
    {
        LOG_CRI<<"Load Config for Loot "<<id<<" failed";
        return false;
    }
    mapLoot[id] = l;
    return true;
}

bool CLootMgr::CheckRoll( UINT32 id )
{
    return _oLootMap.find(id) != _oLootMap.end();
}

bool CLootMgr::Roll( UINT32 lpid, std::vector<SItemGenInfo>& items,TVecResource &vecRes)
{
    iterator i = _oLootMap.find(lpid);
    if(i == _oLootMap.end())
        return false;
    return i->second.roll(items,vecRes);
}

bool CLootMgr::IsRollOneLoot( UINT32 lpid )
{
    iterator i = _oLootMap.find(lpid);
    if(i == _oLootMap.end())
        return false;
    return i->second.isonefromall();
}

bool CLootMgr::FetchAll( UINT32 lpid, std::vector<SItemGenInfo>& items,TVecResource &vecRes )
{
    iterator i = _oLootMap.find(lpid);
    if(i == _oLootMap.end())
        return false;
    return i->second.fetchall(items,vecRes);
}

bool CLootMgr::CheckLootConfig( TLootMap& mapLoot )
{
    /*for(auto p=mapLoot.begin(),e=mapLoot.end(); p!=e; ++p)
      {
      Loot& loot = p->second;
      for(auto q=loot._vecCells.begin(),ee=loot._vecCells.end(); q!=ee; ++q)
      {
      if(mapLoot.find(q->iid) == mapLoot.end())
      {
      LOG_CRI<<"Config for Loot "<<loot._dwLootID<<" failed: "<<q->iid<<" is not valid loot pack";
      return false;
      }
      }
      }*/
    return true;
}

UINT16 CLootMgr::CheckAndAddItem(UINT32 dwID, CUserPtr pUsr, bool bMsgNotify)
{
    if(NULL == pUsr)
        return 0;
    TVecResource vecRes;
    TVecItemGenInfo vecItems;
    LOOT.Roll(dwID, vecItems,vecRes);
    if(vecItems.empty() && vecRes.empty())       
    {
        return 0;
    }
    CPack& oPack = pUsr->GetPack();
    if(!oPack.CanAddItem(vecItems))
    {
        UINT64 qwUsrID = pUsr->GetUserID();
        g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID, 1 , eMsgPackFullErr);
        return 0;
    }
    oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_VIPAward, true, bMsgNotify);
    CStore::AddResource(*pUsr,vecRes,NLogDataDefine::ItemFrom_VIPAward);
     if(vecItems.empty())
     {
         return 0;
     }
    return vecItems[0].wItemID;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

