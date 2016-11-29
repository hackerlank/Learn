#include "GuildMgr.h"
#include "Tokenizer.h"
#include "Guild.h"
#include "User.h"
#include "UserMgr.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "GuildNameManager.h"
#include "Config.h"
#include "Protocols.h"
#include "ItemProt.h"
#include "Regular.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "SystemMail.h"
#include "SysMsgDefine.h"
#include "RankMgr.h"
#include "Parameter.h"
#include "CenterServerLog.h"
#include "GuildBuilding.h"
#include "GodMonsterMgr.h"
#include "Center2DBGuildC.h"

using namespace NGuildProt;
using namespace NItemProt;
using namespace NVarDefine;

// 初始化
bool CGuildMgr::Init()
{
    _bGuildOpEnable = true;
    _eOpDisableType = eOPDGuildBattle;
#ifdef _DEBUG
    _dwStatueCheckTime = Time::Now() - Time::TheDay() + 30;
    _dwBattleAwardTime = Time::Now() - Time::TheWeek() + 30;
#else
    _dwStatueCheckTime = 19 * 3600;
    _dwBattleAwardTime = 24 * 3600 * 6 + 21 * 3600 + 15 * 60;
#endif
    _dwBattleCleanTime = Time::TheWeek(1);
    _dwGuildExchangedItemCleanTime = Time::TheDay(1);

    return LoadConfig();
}

bool CGuildMgr::ReloadTable(const string& strFile)
{
    string strPath;
    if("GuildLevel.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/GuildLevel.xml";

        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadLevelConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    else if("GuildBuilding.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/GuildBuilding.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadBuildingConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    else if("GuildTech.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/GuildTech.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadTechConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    else if("GuildStepAward.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/GuildStepAward.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadGuildBattleAwardConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    else if("XiHeTruck.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/XiHeTruck.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadGuildXiheConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    else if("LingMountainShop.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/LingMountainShop.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadGuildExchangedItemConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }

    return false ;
}
bool CGuildMgr::LoadConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/GuildLevel.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadLevelConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/GuildBuilding.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadBuildingConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/GuildTech.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadTechConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/GuildStepAward.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadGuildBattleAwardConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/XiHeTruck.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadGuildXiheConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/LingMountainShop.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadGuildExchangedItemConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    return true;
}

// 加载帮派兑换物品配置
bool CGuildMgr::LoadGuildExchangedItemConfig(const string& strPath)
{
    _mapLingMountainShopCFG.clear();
    if(!_cLingMountainShopLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    
    for(size_t i=0; i<_cLingMountainShopLoader._vecData.size(); ++i)
    {
        SLingMountainShopCFG* pLingMountainShopCFG = _cLingMountainShopLoader._vecData[i];
        if(!pLingMountainShopCFG)
            continue;
        
        _mapLingMountainShopCFG.insert(std::make_pair(pLingMountainShopCFG->_Id, *pLingMountainShopCFG));
    }

    return true;
}

// 获取帮派兑换物品配置
SLingMountainShopCFG* CGuildMgr::GetGuildExchangedItemConfig(UINT32 dwID)
{
    TMapLingMountainShopCFG::iterator iter = _mapLingMountainShopCFG.find(dwID);
    if (iter != _mapLingMountainShopCFG.end())
        return &iter->second;

    return NULL;
}

// 加载帮派等级配置
bool CGuildMgr::LoadLevelConfig(const string& strPath)
{
    if(!_cLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    return true;
}

// 加载帮派建筑配置
bool CGuildMgr::LoadBuildingConfig(const string& strPath)
{
    _mapBuildingCFG.clear();
    if(!_cBuildingLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }

    for (auto it = _cBuildingLoader._vecData.begin(); it != _cBuildingLoader._vecData.end(); ++it)
    {
        SGuildBuildingCFG* pBuildingCFG = *it;
        TVecPGuildBuildingCFG& rvecPGuildBuildingCFG = _mapBuildingCFG[pBuildingCFG->_ID];
        if (rvecPGuildBuildingCFG.size() < static_cast<size_t>(pBuildingCFG->_Level + 1))
        {
            rvecPGuildBuildingCFG.resize(pBuildingCFG->_Level + 1);
            rvecPGuildBuildingCFG[pBuildingCFG->_Level] = pBuildingCFG;
        }
    }
    
    return true;
}

// 加载帮派科技配置
bool CGuildMgr::LoadTechConfig(const string& strPath)
{
    if(!_cTechLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    for (auto it = _mapTechCFG.begin(); it != _mapTechCFG.end(); ++ it)
    {
        for (size_t i = 0; i < it->second.size(); ++ i)
            delete it->second[i];
    }
    _mapTechCFG.clear();

    for (auto it = _cTechLoader._vecData.begin(); it != _cTechLoader._vecData.end(); ++it)
    {
        SGuildTechCFG* pTechCFG = *it;
        if (pTechCFG->_ID <= eTechNone || pTechCFG->_ID >= eTechMax)
        {
            LOG_CRI << "Tech Failed: " << pTechCFG->_ID << ".";
            return false;
        }
        TVecPGuildTechCFG& rvecPGuildTechCFG = _mapTechCFG[static_cast<ETechType>(pTechCFG->_ID)];
        if (rvecPGuildTechCFG.size() < static_cast<size_t>(pTechCFG->_Level + 1))
        {
            rvecPGuildTechCFG.resize(pTechCFG->_Level + 1);
        }

        SGuildTechCFGEx* pTechCFGEx = rvecPGuildTechCFG[pTechCFG->_Level];
        if (!pTechCFGEx)
            pTechCFGEx = new SGuildTechCFGEx;
        else
        {
            LOG_CRI << "Error! Repeat TechID: " << pTechCFG->_ID << " or TechLevel: " << pTechCFG->_Level;
            return false;
        }
        pTechCFGEx->SetConfig(*pTechCFG);
        pTechCFGEx->_vecFtAttrMod.clear();
        Tokenizer tk(pTechCFGEx->_Attr_ID, ",");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            SFtAttrMod sAttr;
            sAttr._eAttr  = EFighterAttr(atoi(tk[j].c_str()));
            sAttr._fValue = pTechCFGEx->_Value;
            pTechCFGEx->_vecFtAttrMod.push_back(sAttr);
        }
        rvecPGuildTechCFG[pTechCFG->_Level] = pTechCFGEx;
    }
    return true;
}

// 加载帮派战奖励配置
bool CGuildMgr::LoadGuildBattleAwardConfig(const string& strPath)
{
    if(!_cBattleAwardLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    for (auto& rPCfg : _vecBattleAward)
    {
        if (rPCfg)
            delete rPCfg;
    }
    _vecBattleAward.clear();
    for (auto it = _cBattleAwardLoader._vecData.begin(); it != _cBattleAwardLoader._vecData.end(); ++it)
    {
        SGuildStepAwardCFG* pCFG = *it;
        Tokenizer tk(pCFG->_GuildStep, ";");
        UINT32 dwRankMin = 0;
        UINT32 dwRankMax = 0;
        if (tk.size() == 1)
            dwRankMin = dwRankMax = atoi(tk[0].c_str());
        else if (tk.size() == 2)
        {
            dwRankMin = atoi(tk[0].c_str());
            dwRankMax = atoi(tk[1].c_str());
            if (dwRankMin > dwRankMax)
            {
                LOG_CRI << "Wrong GuildStep: " << pCFG->_GuildStep << ".";
                return false;
            }
        }
        for (UINT8 byRank = dwRankMin; byRank < dwRankMax + 1; ++byRank)
        {
            if (_vecBattleAward.size() < static_cast<size_t>(byRank + 1))
                _vecBattleAward.resize(byRank + 1);

            SGuildStepAwardCFGEx* pBattleReward = new(SGuildStepAwardCFGEx);
            pBattleReward->byRank = byRank;
            Tokenizer tk(pCFG->_Award, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer tk2(tk[j], ",");
                if (tk2.size() != 2)
                {
                    LOG_CRI << "Wrong Award: " << tk[j] << ".";
                    return false;
                }
                SItemCount sItemCount(atoi(tk2[0].c_str()), atoi(tk2[1].c_str()));
                pBattleReward->vecItemCount.push_back(sItemCount);
            }
            if (_vecBattleAward[pBattleReward->byRank])
                delete _vecBattleAward[pBattleReward->byRank];
            _vecBattleAward[pBattleReward->byRank] = pBattleReward;
        }
    }
    return true;
}

// 加载羲和神车配置
bool CGuildMgr::LoadGuildXiheConfig(const string& strPath)
{
    if(!_cXiheTruckLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    _mapID2XiHeTruckCFG.clear();

    for(size_t i = 0; i < _cXiheTruckLoader._vecData.size(); ++i)
    {
        SXiHeTruckCFG* pXiHeTruckCFG = _cXiheTruckLoader._vecData[i];
        SXiHeTruckCFGEx& rXiHeTruckCFGEx = _mapID2XiHeTruckCFG[pXiHeTruckCFG->_ID];
        rXiHeTruckCFGEx.SetConfig(*pXiHeTruckCFG);

        Tokenizer tk(rXiHeTruckCFGEx._Award, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
               UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rXiHeTruckCFGEx._vecItemAward.push_back(SItemCount(wItemID, dwItemCount));
            }
        }
        Tokenizer tkc(rXiHeTruckCFGEx._Goods, "|");
        for (size_t j = 0; j < tkc.size(); ++ j)
        {
            Tokenizer yatk(tkc[j], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
               UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rXiHeTruckCFGEx._vecItemCost.push_back(SItemCount(wItemID, dwItemCount));
            }
        }
        Tokenizer tkl(rXiHeTruckCFGEx._Level, ",");
        if (tkl.size() > 1)
        {
            rXiHeTruckCFGEx._byMinLvl = atoi(tkl[0].c_str());
            rXiHeTruckCFGEx._byMaxLvl = atoi(tkl[1].c_str());
        }
        auto it = _mapLevelStr2TruckID.find(rXiHeTruckCFGEx._Level);
        if (it != _mapLevelStr2TruckID.end())
            it->second.push_back(rXiHeTruckCFGEx._ID);
        else
        {
            TVecUINT8 vecUINT8;
            vecUINT8.push_back(rXiHeTruckCFGEx._ID);
            _mapLevelStr2TruckID.insert(make_pair(rXiHeTruckCFGEx._Level, vecUINT8));
        }
    }
    return true;
}

void CGuildMgr::LoadFromDB()
{
    g_Center2DBGuildC.Send_GetGuildPubInfo();
    g_Center2DBGuildC.Send_GetAllGuildInfo();
}

void CGuildMgr::LoadAllGuildExchangedItemFromDB()
{
    g_Center2DBGuildC.Send_GetAllGuildExchangedItem();
}

// 加载公共数据
void CGuildMgr::InitPubInfo(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecPubGuildAllInfo& vecPubGuildAllInfo)
{
    for (auto it = vecPubGuildAllInfo.begin(); it != vecPubGuildAllInfo.end(); ++it)
    {
        const SPubGuildAllInfo& rPubGuildAllInfo = *it;
        const SGuildListInfo& rGuildListInfo = rPubGuildAllInfo.sGuildListInfo;
        CGuildListInfoPtr pGuildListInfo (new CGuildListInfo(rGuildListInfo));
        if (pGuildListInfo)
        {
            if (_mapGuildListInfo.find(pGuildListInfo->GetID()) != _mapGuildListInfo.end())
                LOG_CRI << "InitPubInfo List Info twice: " << pGuildListInfo->GetID() << ".";
            _mapGuildListInfo.insert(make_pair(pGuildListInfo->GetID(), pGuildListInfo));

            CGuildNameManager::Instance().AddGuildName(pGuildListInfo->GetID(), pGuildListInfo->GetName());
            _mapNameIndex.insert(make_pair(pGuildListInfo->GetName(), pGuildListInfo->GetID()));
            _mapOwnerNameIndex.insert(make_pair(pGuildListInfo->GetOwnerName(), pGuildListInfo->GetID()));
        }

        const SDBGuildBattleInfo& rGuildBattleInfo = rPubGuildAllInfo.sGuildBattleInfo;
        if (rGuildBattleInfo.qwGuildID)
            _mapGuildBattleScore[rGuildBattleInfo.qwGuildID] = rGuildBattleInfo.dwScore;
        SOrderListInfo setOrderListInfo(rGuildListInfo.qwGuildID, rGuildListInfo.byLevel, rGuildListInfo.wUserCount);

        auto const& rPair = _setOrderListInfo.insert(setOrderListInfo);

        _mapItOrderInfo[rGuildListInfo.qwGuildID] = rPair.first;

    }
    if (dwCurSize >= dwTotalSize)
    {
        Config.SetInited(eDBInitGuild);
        if (Config.IsSomeInited(eDBInitGuildAll))
            SyncBattleRank();
    }
}

// 帮派登录，加载帮派相关数据
void CGuildMgr::InitGuildInfo(UINT64 qwGuildID, const SDBGuildAllInfo& rData)
{
    if (_mapGuild.find(qwGuildID) != _mapGuild.end())
        LOG_WRN << "Init GUild ID(" << qwGuildID << ") twice.";
    CGuildPtr pGuild(new CGuild(rData.sBaseInfo));
    if (!pGuild)
    {
        LOG_WRN <<  "new CGuild err.";
        return ;
    }
    _mapGuild.insert(make_pair(pGuild->GetID(), pGuild));
     
    TVecUINT8 vecLingShanType = pGuild->GetLingShanType();
    if (vecLingShanType.size() > 0)
        _vecGuidID.push_back(pGuild->GetID());

    for (auto it = rData.vecMemberInfo.begin(); it != rData.vecMemberInfo.end(); ++it)
    {
        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID((*it).sBaseInfo.qwRoleID);
        if (!pGuildUser)
            pGuildUser = CGuildUserMgr::Instance().CreateGuildUser(*it);
        CUserPtr pUser = CUserMgr::GetUserByUserID((*it).sBaseInfo.qwRoleID);
        if (!pGuild->InitUser(pGuildUser))
            LOG_WRN << "Init GuildUser error.";
        else
            pGuildUser->SetGuild(pGuild, true);
        if (pUser)
            pGuildUser->SetUser(pUser);
    }

    //  加载帮派申请数据
    if (_mapGuildApplyCache.find(qwGuildID) != _mapGuildApplyCache.end())
    {
        for(auto it = _mapGuildApplyCache[qwGuildID].begin(); it != _mapGuildApplyCache[qwGuildID].end(); ++it)
            pGuild->AddApplyInfo(*it);
        _mapGuildApplyCache.erase(qwGuildID);
    }

    // 加载帮派权限
    pGuild->InitAuthority(rData.vecAuthority);

    pGuild->InitBuildings(rData.vecBuildingInfo);
    pGuild->InitStatue(rData.sStatueInfo);
    pGuild->InitLog(rData.vecLogInfo);
    pGuild->InitGuildExchangedItemLog(rData.vecLingShanShopBuyLogInfo);

    _mapNameIndex.insert(make_pair(pGuild->GetName(), pGuild->GetID()));
    _mapOwnerNameIndex.insert(make_pair(pGuild->GetOwnerName(), pGuild->GetID()));
}

// 帮派登录，加载帮派相关数据
void CGuildMgr::InitGuildInfo(const SDBGuildAllInfo& rData)
{
    UINT64 qwGuildID = rData.sBaseInfo.qwGuildID;
    InitGuildInfo(qwGuildID, rData);
}

//登录加载帮派兑换物品 
void CGuildMgr::InitGuildExchangedItem(const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem)
{
    for (size_t i=0; i<vecGuildExchangedItem.size(); ++i)
    {
        if (vecGuildExchangedItem[i].qwGuildID > 0
                && vecGuildExchangedItem[i].dwExchangeID > 0
                && vecGuildExchangedItem[i].dwCount > 0)
        {
            CGuildPtr pGuild = GetGuild(vecGuildExchangedItem[i].qwGuildID);
            if(pGuild)
                pGuild->SetGuildExchangedItem(vecGuildExchangedItem[i].dwExchangeID, vecGuildExchangedItem[i].dwCount);
        }
    }

    Config.SetInited(eDBGuildExchangedItem);
}

// 创建帮派
void CGuildMgr::CreateGuild(UINT64 qwRoleID, string strName, ECreateResult& eResult, function<void(UINT8 byRet, CGuildPtr pGuild)> func)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
    {
        eResult = eGCreateFailed;
        return;
    }

    if (pUser->GetLevel() < MIN_GUILD_USER_LEVEL)
    {
        eResult = eGCreateLackOfLevel;
        return;
    }
    
    if (pUser->GetSilver() < CREATE_GUILD_SILVER)
    {
        eResult = eGCreateLackOfGold;
        return;
    }

    if (pUser->GetVIPLevel() < SParamConfig::wGuildBuildVipLimit)
    {
        eResult = eGCreateLackOfVIP;
        return;
    }

    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (pGuildUser && pGuildUser->GetGuild())
    {
        eResult = eGCreateInGuild;
        return;
    }

    eResult = CGuildNameManager::Instance().CheckName(strName);
    if (eResult != eGCreateSuccess)
        return;

    bool bNewUser = false;
    if (!pGuildUser)
    {
        pGuildUser = CGuildUserMgr::Instance().CreateGuildUser(pUser);
        bNewUser = true;
    }

    if (!pGuildUser)
    {
        eResult = eGCreateFailed;
        return;
    }
    CGuildPtr pGuild(new CGuild(pGuildUser, strName));
    if (!pGuild)
    {
        eResult = eGCreateFailed;
        return;
    }
    pGuild->SetQuality(pUser->GetQuality());
    //pGuild->SetPlayerFighterID(pUser->GetPlayerFighterID());
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildDonate, static_cast<UINT8>(EMONEY_SILVER), CREATE_GUILD_SILVER,
            [this, func, pUser, pGuild, pGuildUser, bNewUser, &eResult, strName](UINT8 byError, UINT8 byRet)
            { 
                if (byRet == 0)
                {
                    pGuild->InitBuildings();
                    pGuild->InitStatue();
                    if (!bNewUser)
                        CGuildUser::Update2DB(pGuildUser, eOpDel);
                    pGuildUser->SetGuild(pGuild);
                    pGuildUser->SetRank(eMemberOwner);
                    pGuildUser->ResetDefaultAuthority();
                    pUser->SetGuildUser(pGuildUser);
                    eResult = eGCreateSuccess;
                    _mapGuild.insert(make_pair(pGuild->GetID(), pGuild));
                    CGuild::Update2DB(pGuild, eOpAdd);

                    CGuildUser::Update2DB(pGuildUser, eOpAdd);

                    CGuildNameManager::Instance().AddGuildName(pGuild->GetID(), strName);
                    CGuildListInfoPtr pListInfo(new CGuildListInfo(pGuild));
                    if (pListInfo)
                    {
                        _mapGuildListInfo.insert(make_pair(pGuild->GetID(), pListInfo));
                        CGuildListInfo::Update2DB(pListInfo, eOpAdd);
                    }
                    CGuildMgr::Instance().UpdateOrderListMemberCount(pGuild->GetID(), pGuild->GetLevel(), pGuild->GetMemberCount());
                    _mapNameIndex.insert(make_pair(pGuild->GetName(), pGuild->GetID()));
                    _mapOwnerNameIndex.insert(make_pair(pGuild->GetOwnerName(), pGuild->GetID()));

                    TVecINT32 vecParam;
                    ostringstream strInfo;
                    strInfo << pGuild->GetID();
                    pUser->OnEvent(eEventType_GuildCreation,vecParam, strInfo.str());

                    TVecINT32 vecParam2;
                    vecParam2.push_back(pGuild->GetLevel());
                    ostringstream strInfo2;
                    strInfo2 << pGuild->GetID();
                    pUser->OnEvent(eEventType_GuildJoining,vecParam2, strInfo2.str());
                    //天元神兽活动
                    GodMonsterPtr pMonster = NULL;
                    g_GodMonsterMgr.CreateGuild(pGuild->GetID(),pMonster);
                    if(!pMonster)
                    {
                        LOG_WRN << " GodMonster Create Err.";
                        return;
                    }
                    
                    g_GodMonsterMgr.OnRank(EMonsterRank_2,pGuild->GetID());

                    //LogServer日志
                    SLogOp sLog;
                    sLog.eType = eOpType_Create;
                    sLog.qwGuildID = pGuild->GetID();
                    sLog.byParam = 0;
                    WriteGuildLog(sLog);
                    if(!SyncGuildRankByLevel(pGuild->GetID()))
                    {
                        LOG_WRN << "SynGuildLevel Error";
                    }
                    return func(byRet, pGuild);
                }
                else
                    return func(byRet, NULL);
            });
        
}

bool    CGuildMgr::DisbandGuild(UINT64 qwGuildID)
{
    auto it = _mapGuild.find(qwGuildID);
    if (it == _mapGuild.end())
        return false;
    return DisbandGuild(it->second);
}

bool    CGuildMgr::DisbandGuild(CGuildPtr pGuild)
{
    if (!pGuild)
        return false;
    UINT64 qwGuildID = pGuild->GetID();
    string strName = pGuild->GetName();

    if(!SyncGuildRankByLevel(qwGuildID,true))
    {
        LOG_WRN << " Guild(" <<qwGuildID << ") Faired Sync Error.";
    }
    auto it = _mapGuild.find(qwGuildID);
    if (it != _mapGuild.end())
        _mapGuild.erase(it);
    else
        LOG_CRI << "Disband invalid guild(" << qwGuildID << ").";
    CGuild::Update2DB(NULL, eOpDel, qwGuildID);

    auto it2 = _mapGuildListInfo.find(qwGuildID);
    if (it2 != _mapGuildListInfo.end())
        _mapGuildListInfo.erase(it2);
    else
        LOG_CRI << "Disband invalid guild info(" << qwGuildID << ").";
    CGuildListInfo::Update2DB(NULL, eOpDel, qwGuildID);

    auto it3 = _mapNameIndex.find(strName);
    if (it3 != _mapNameIndex.end())
        _mapNameIndex.erase(it3);
    else
        LOG_CRI << "Disband invalid guild name index(" << qwGuildID << ").";
    CGuildNameManager::Instance().DelGuildName(strName);
    RemoveGuildBattleScore(qwGuildID);
    RemoveOrderList(qwGuildID);

    UINT32 dwID = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterGuildBattleS.SendSvr_GuildDisband(&dwID, 1, qwGuildID);

    return true;
}

bool CGuildMgr::GetListInfo(UINT32 dwFirstRank, UINT32 dwCount, SOtherGuildListInfo& rOtherGuildListInfo, CGuildUserPtr pGuildUser)
{
    const UINT32 DEFAULT_PAGE_COUNT = 10;
    if (!dwCount)
        dwCount = DEFAULT_PAGE_COUNT;
    rOtherGuildListInfo.dwMaxGuildCount = _mapGuildListInfo.size();
    UINT32 dwIndex = dwFirstRank ? dwFirstRank - 1 : 0;
    rOtherGuildListInfo.dwCurGuildCount = dwIndex + 1;
    UINT32 dwCountTmp = 0;
#if 1
    if (_setOrderListInfo.size() <= dwIndex)
        return true;
    TVecUINT64 vecGuildID;
    auto it = _setOrderListInfo.begin();
    advance(it, dwIndex);
    while (dwCountTmp ++ < dwCount)
    {
        if (it == _setOrderListInfo.end())
            break;
        vecGuildID.push_back((*it++).qwGuildID);
    }

    dwCountTmp = 0;
    for (auto& rID : vecGuildID)
    {
        CGuildListInfoPtr pInfo = GetListInfo(rID);
        if (!pInfo)
            continue;
        SGuildListInfo sGuildListInfo;
        pInfo->GetAllInfo(sGuildListInfo);
        rOtherGuildListInfo.vecGuildListInfo.push_back(sGuildListInfo);
        if (++dwCountTmp >= dwCount)
            break;
    }
#else
    for (auto it = _mapGuildListInfo.begin(); it != _mapGuildListInfo.end(); ++it)
    {
        if (!it->second)
            continue;
        if (rOtherGuildListInfo.dwCurGuildCount <= dwIndex)
        {
            ++rOtherGuildListInfo.dwCurGuildCount;
            continue;
        }
        SGuildListInfo sGuildListInfo;
        (it->second)->GetAllInfo(sGuildListInfo);
        rOtherGuildListInfo.vecGuildListInfo.push_back(sGuildListInfo);
        if (++dwCountTmp >= dwCount)
            break;
    }
#endif

    if (pGuildUser)
        pGuildUser->GetApplyGuildID(rOtherGuildListInfo.vecApplyGuildID);
    return true;
}

// 发送加入帮派的申请
bool CGuildMgr::ApplyForGuild(UINT64 qwGuildID, CGuildUserPtr pGuildUser, EApplyResult& eResult, function<void(EApplyResult eResult)> func)
{
    auto it = _mapGuildListInfo.find(qwGuildID);
    if (it == _mapGuildListInfo.end())
    {
        eResult = eGApplyFailed;
        return false;
    }
    if (pGuildUser->GetApplyCount() >= SParamConfig::wGuildApplyNumLimit)
    {
        eResult = eGApplyListFull;
        return false;
    }

    CGuildListInfoPtr pListInfo = it->second;
    auto it2 = _mapGuild.find(qwGuildID);
    if (it2 != _mapGuild.end())
    {
        CGuildPtr pGuild = it2->second;
        if (pGuild->GetMemberCount() >= pGuild->GetMaxMemberCount())
        {
            eResult = eGApplyGuildFull;
            return false;
        }

        eResult = pGuildUser->CreateApplyInfo(qwGuildID, [pGuild, func](CGuildApplyInfoPtr pApplyInfo, EApplyResult eResult)
                {
                    if (eResult == eGApplySuccess && pApplyInfo)
                    {
                        pGuild->AddApplyInfo(pApplyInfo);
                        pGuild->NotifyApplyInfo();
                    }
                    func(eResult);
                });
        if (eResult != eGApplySuccess)
            return false;
    }
    else
    {
        if (pListInfo->GetMemberCount() >= pListInfo->GetMaxMemberCount())
        {
            eResult = eGApplyGuildFull;
            return false;
        }

        eResult = pGuildUser->CreateApplyInfo(qwGuildID, [this, qwGuildID, func](CGuildApplyInfoPtr pApplyInfo, EApplyResult eResult)
                {
                    if (eResult == eGApplySuccess && pApplyInfo)
                    {
                        g_Center2DBGuildC.Send_GuildLogin(qwGuildID);
                        _mapGuildApplyCache[qwGuildID].push_back(pApplyInfo);
                    }
                    func(eResult);
                });
        if (eResult != eGApplySuccess)
            return false;

    }
    
    eResult = eGApplySuccess;
    return true;
}

bool CGuildMgr::RejectApplyForGuild(UINT64 qwRoleID, CGuildApplyInfoPtr pApplyInfo)
{
    if (!pApplyInfo)
        return false;
    _mapGuildApplyRejectCache[qwRoleID].push_back(pApplyInfo);
    CGuildApplyInfo::Update2DB(pApplyInfo, eOpDel);
    return true;
}

bool CGuildMgr::AgreeApplyForGuild(UINT64 qwRoleID, CGuildApplyInfoPtr pApplyInfo)
{
    if (!pApplyInfo)
        return false;
    _mapGuildApplyAgreeCache[qwRoleID].push_back(pApplyInfo);
    CGuildApplyInfo::Update2DB(pApplyInfo, eOpDel);
    return true;
}

CGuildPtr CGuildMgr::GetGuild(UINT64 qwGuildID)
{
    auto it = _mapGuild.find(qwGuildID);
    if (it != _mapGuild.end())
        return it->second;
    return NULL;
}

void CGuildMgr::GuildExchangedBegin(const TVecLingShanShopData vecLingShanShopData)
{
    for (size_t i=0; i<_vecGuidID.size(); i++)
    {
        CGuildPtr pGuild = GetGuild(_vecGuidID[i]);
        if (!pGuild)
            continue;

        pGuild->GuildExchangedItemClean();
    }
    
    _vecGuidID.clear();
    
    for (size_t i=0; i<vecLingShanShopData.size(); i++)
    {
        SLingShanShopData sLingShanShopData = vecLingShanShopData[i];
        CGuildPtr pGuild = GetGuild(sLingShanShopData.qwGuildID);
        if (!pGuild)
            continue;

        pGuild->GuildExchangedItemBegin(sLingShanShopData.vecLingShanType);
        _vecGuidID.push_back(sLingShanShopData.qwGuildID);
    }
}

CGuildListInfoPtr CGuildMgr::GetListInfo(UINT64 qwGuildID)
{
    auto it = _mapGuildListInfo.find(qwGuildID);
    if (it != _mapGuildListInfo.end())
        return it->second;
    return NULL;
}

UINT64 CGuildMgr::GetGuildID(const string& strName) const
{
    auto it = _mapNameIndex.find(strName);
    if (it != _mapNameIndex.end())
        return it->second;
    else
        return 0;
}

void CGuildMgr::GetGuildIDGrep(const string& strName, TVecUINT64& rvecGuildID) const
{
    Regular* pRegex = NULL;
    char szRegex[1024] = {0};
    SNPRINTF(szRegex, sizeof(szRegex)-1, "%s", strName.c_str());
    pRegex = new Regular(szRegex);
    if (pRegex)
    {
        for (auto it = _mapNameIndex.begin(); it != _mapNameIndex.end(); ++it)
        {
            if (pRegex->matchFirst((it->first).c_str()))
                rvecGuildID.push_back(it->second);
        }
    }
    else
    {
        LOG_WRN << "pRegex == NULL.";
        UINT64 qwGuildID = GetGuildID(strName);
        if (qwGuildID)
            rvecGuildID.push_back(qwGuildID);
    }
    if (pRegex)
        delete pRegex;
}

UINT64 CGuildMgr::GetGuildIDByOwnerName(const string& strName) const
{
    auto it = _mapOwnerNameIndex.find(strName);
    if (it != _mapOwnerNameIndex.end())
        return it->second;
    else
        return 0;
}

void CGuildMgr::GetGuildIDByOwnerNameGrep(const string& strName, TVecUINT64& rvecGuildID) const
{
    Regular* pRegex = NULL;
    char szRegex[1024] = {0};
    SNPRINTF(szRegex, sizeof(szRegex)-1, "%s", strName.c_str());
    pRegex = new Regular(szRegex);
    if (pRegex)
    {
        for (auto it = _mapOwnerNameIndex.begin(); it != _mapOwnerNameIndex.end(); ++it)
        {
            if (pRegex->matchFirst((it->first).c_str()))
                rvecGuildID.push_back(it->second);
        }
    }
    else
    {
        LOG_WRN << "pRegex == NULL.";
        UINT64 qwGuildID = GetGuildID(strName);
        if (qwGuildID)
            rvecGuildID.push_back(qwGuildID);
    }
    if (pRegex)
        delete pRegex;
}

void   CGuildMgr::GetGuildIDByBothNameGrep(const string& strName, const string& strOwnerName, TVecUINT64& rvecGuildID) const
{
    TSetUINT64 setNameID;
    Regular* pRegex = NULL;
    char szRegex[1024] = {0};
    SNPRINTF(szRegex, sizeof(szRegex)-1, "%s", strName.c_str());
    pRegex = new Regular(szRegex);
    if (pRegex)
    {
        for (auto it = _mapNameIndex.begin(); it != _mapNameIndex.end(); ++it)
        {
            if (pRegex->matchFirst((it->first).c_str()))
                setNameID.insert(it->second);
        }
    }
    else
    {
        LOG_WRN << "pRegex == NULL.";
        UINT64 qwGuildID = GetGuildID(strName);
        if (qwGuildID)
            setNameID.insert(qwGuildID);
    }
    if (pRegex)
        delete pRegex;

    TSetUINT64 setOwnerNameID;
    pRegex = NULL;
    memset(szRegex, 0 ,sizeof(szRegex));
    SNPRINTF(szRegex, sizeof(szRegex)-1, "%s", strOwnerName.c_str());
    pRegex = new Regular(szRegex);
    if (pRegex)
    {
        for (auto it = _mapOwnerNameIndex.begin(); it != _mapOwnerNameIndex.end(); ++it)
        {
            if (pRegex->matchFirst((it->first).c_str()))
                setOwnerNameID.insert(it->second);
        }
    }
    else
    {
        LOG_WRN << "pRegex == NULL.";
        UINT64 qwGuildID = GetGuildID(strName);
        if (qwGuildID)
            setOwnerNameID.insert(qwGuildID);
    }
    if (pRegex)
        delete pRegex;
    for (auto it = setNameID.begin(); it != setNameID.end(); ++it)
    {
        auto it2 = setOwnerNameID.find(*it);
        if (it2 != setOwnerNameID.end())
            rvecGuildID.push_back(*it);
    }
}

string CGuildMgr::GetAllGuildInfo(const char chSplit)
{
    ostringstream strInfo;
    for (auto it = _mapGuild.begin(); it != _mapGuild.end(); ++it)
    {
        CGuildPtr pGuild = it->second;
        strInfo << pGuild->GetName() << "(" << pGuild->GetID() << ")";
        strInfo << chSplit;
    }
    return strInfo.str();
}

bool CGuildMgr::GetBuildingConfig(UINT8 byID, TVecPGuildBuildingCFG& rvecPGuildBuildingCFG) const
{
    auto it = _mapBuildingCFG.find(byID);
    if (it == _mapBuildingCFG.end())
        return false;
    rvecPGuildBuildingCFG =  it->second;
    return true;
}

bool CGuildMgr::GetTechConfig(ETechType eTechType, TVecPGuildTechCFG& rvecPGuildTechCFG) const
{
    auto it = _mapTechCFG.find(eTechType);
    if (it == _mapTechCFG.end())
        return false;
    rvecPGuildTechCFG =  it->second;
    return true;
}

const SGuildLevelCFG* CGuildMgr::GetLevelConfig(UINT16 wLevel) const
{
    for (auto it = _cLevelLoader._vecData.begin(); it != _cLevelLoader._vecData.end(); ++it)
    {
        if ((*it) && ((*it)->_Level == wLevel))
            return *it;
    }
    return NULL;
}

const SGuildLevelCFG* CGuildMgr::GetStatueConfig(UINT16 wLevel) const
{
    return GetLevelConfig(wLevel);
}

const SGuildLevelCFG*  CGuildMgr::GetStatueConfigByExp(UINT32 dwExp) const
{
    for (auto it = _cLevelLoader._vecData.begin(); it != _cLevelLoader._vecData.end(); ++it)
    {
        if ((*it) && ((*it)->_Exp > dwExp))
            return *it;
    }
    return *(_cLevelLoader._vecData.end() - 1);
}

UINT16 CGuildMgr::GetStatueConfigMaxLeve() const
{
    return _cLevelLoader._vecData.size();
}

/*
 * 供奉方式     消耗                帮派经验    帮贡奖励系数
 * 供奉鲜花     1000银币            10          1
 * 供奉朱果     10仙石              30          3
 * 供奉蟠桃     30仙石              100         10
 */
const UINT32 FLOWER_SILVER = 1000;
const UINT32 RED_FRUIT_GOLD = 10;
const UINT32 PEACH_GOLD    = 30;
UINT32 CGuildMgr::TestWorshipCond(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult) const
{
    if (!pGuildUser)
        return 0;
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (!pUser)
        return 0;
    switch (eType)
    {
        case eWorshipFlower:
            if (pUser->GetSilver() < FLOWER_SILVER)
            {
                eResult = eGSResultLackofSilver;
                return 0;
            }
            else
                return SParamConfig::byGuildShenXiangXianHua;
            break;
        case eWorshipRedFruit:
            if (pUser->GetGold() < RED_FRUIT_GOLD)
            {
                eResult = eGSResultLackofGold;
                return 0;
            }
            else
                return SParamConfig::byGuildShenXiangZhuGuo;
            break;
        case eWorshipPeach:
            if (pUser->GetGold() < PEACH_GOLD)
            {
                eResult = eGSResultLackofGold;
                return 0;
            }
            else
                return SParamConfig::byGuildShenXiangPanTao;
            break;
        default:
            break;
    }
    return 0;
}

UINT32 CGuildMgr::ProcessWorshipCond(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult, function<void(UINT8 byRet)> func, function<void(UINT32 dwContribution, UINT32 dwCost)> func2) const
{
    if (!pGuildUser)
        return 0;
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (!pUser)
        return 0;
    switch (eType)
    {
        case eWorshipFlower:
            if (pUser->GetSilver() < FLOWER_SILVER)
            {
                func2(0, 0);
                eResult = eGSResultLackofSilver;
                return 0;
            }
            else
            {
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildWorship, static_cast<UINT8>(EMONEY_SILVER), FLOWER_SILVER,
                        [func, func2, &eResult](UINT8 byError, UINT8 byRet)
                        { 
                            if (byRet == 0)
                                func2(SParamConfig::byGuildShenXiangXianHuaAward, FLOWER_SILVER);
                            else if (byRet == 1)
                            {
                                eResult = eGSResultLackofSilver;
                            }
                            func(byRet);
                        });
            }
            break;
        case eWorshipRedFruit:
            if (pUser->GetGold() < RED_FRUIT_GOLD)
            {
                func2(0, 0);
                eResult = eGSResultLackofGold;
                return 0;
            }
            else
            {
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildWorship, static_cast<UINT8>(EMONEY_GOLD), RED_FRUIT_GOLD,
                        [func, func2, &eResult](UINT8 byError, UINT8 byRet)
                        { 
                            if (byRet == 0)
                                func2(SParamConfig::byGuildShenXiangZhuGuoAward, RED_FRUIT_GOLD);
                            else if (byRet == 1)
                            {
                                eResult = eGSResultLackofGold;
                            }
                            func(byRet);
                        });
            }
            break;
        case eWorshipPeach:
            if (pUser->GetGold() < PEACH_GOLD)
            {
                func2(0, 0);
                eResult = eGSResultLackofGold;
                return 0;
            }
            else
            {
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildWorship, static_cast<UINT8>(EMONEY_GOLD), PEACH_GOLD,
                        [func, func2, &eResult](UINT8 byError, UINT8 byRet)
                        { 
                            if (byRet == 0)
                                func2(SParamConfig::byGuildShenXiangPanTaoAward, PEACH_GOLD);
                            else if (byRet == 1)
                            {
                                eResult = eGSResultLackofGold;
                            }
                            func(byRet);
                        });
            }
            break;
        default:
            break;
    }
    return 0;
}

void   CGuildMgr::AddBattleScore(UINT64 qwGuildID, UINT32 dwScore, const TVecMemberScore& vecMemberScore)
{
    AddGuildBattleScore(qwGuildID, dwScore);
    AddMemberBattleScore(qwGuildID, vecMemberScore);
}

UINT32 CGuildMgr::GetBattleScore(UINT64 qwGuildID) const
{
    auto it = _mapGuildBattleScore.find(qwGuildID);
    if (it == _mapGuildBattleScore.end())
        return 0;
    else
        return it->second;
}

bool   CGuildMgr::GetBattlePanelInfo(UINT64 qwRoleID, UINT32& rdwSelfScore, UINT32& rdwGuildScore, UINT32& rdwGuildRank) const
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
        return false;
    rdwSelfScore    = pGuildUser->GetBattleScore();
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return false;
    auto it = _mapGuildBattleScore.find(pGuild->GetID());
    if (it != _mapGuildBattleScore.end())
        rdwGuildScore   = it->second;
    auto it2 = _mapGuildBattleRank.find(pGuild->GetID());
    if (it2 != _mapGuildBattleRank.end())
        rdwGuildRank = it2->second;
    LOG_WRN << "dwSelfScore = " << rdwSelfScore << ", dwGuildScore = " << rdwGuildScore << ", dwGuildRank = " << rdwGuildRank << ".";
    return true;
}

void   CGuildMgr::AddGuildBattleScore(UINT64 qwGuildID, UINT32 dwScore)
{
    _mapGuildBattleScore[qwGuildID] += dwScore;

    string strData;
    SDBGuildBattleInfo sDBGuildBattleInfo;
    sDBGuildBattleInfo.qwGuildID = qwGuildID;
    sDBGuildBattleInfo.dwScore = _mapGuildBattleScore[qwGuildID];
    COutArchive iar(strData);
    iar << sDBGuildBattleInfo;

    g_Center2DBGuildC.Send_GuildPubDataUpdate(qwGuildID, eGPDTBattleInfo, eOpUpdate, strData);

    UpdateOrderListBattleScore(qwGuildID);
}

void CGuildMgr::RemoveGuildBattleScore(UINT64 qwGuildID)
{
    auto it = _mapGuildBattleScore.find(qwGuildID);
    if (it == _mapGuildBattleScore.end())
        return;
    _mapGuildBattleScore.erase(it);
    SyncBattleRank();
    
    UpdateOrderListBattleScore(qwGuildID);

    TVecRankInfo vecRankInfo;
    SGRBattleInfoPtr pInfo (new SGRBattleInfo);
    pInfo->qwGuildID = qwGuildID;
    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    CRankMgr::Instance().DeleteRankInfo(qwGuildID, eRTGuildBattle, vecRankInfo);
}

void   CGuildMgr::AddMemberBattleScore(UINT64 qwGuildID, const TVecMemberScore& vecMemberScore)
{
    for (auto& rMemberScore:vecMemberScore)
    {
        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(rMemberScore.qwRoleID);
        if (pGuildUser)
            pGuildUser->AddBattleScore(rMemberScore.dwScore);
        else
            LOG_WRN << "No GuildUser find: " << rMemberScore.qwRoleID << ".";
    }
}

struct SGuildRank
{
    SGuildRank(UINT32 dwScore, UINT64 qwGuildID, UINT16 wLevel):
        dwScore(dwScore), qwGuildID(qwGuildID), wLevel(wLevel)
    { }

    UINT32 dwScore;
    UINT64 qwGuildID;
    UINT16 wLevel;
    bool operator < (const SGuildRank& rRank) const
    {
        if (qwGuildID == rRank.qwGuildID)
            return false;
        if (dwScore == rRank.dwScore)
        {
            if (wLevel == rRank.wLevel)
                return qwGuildID > rRank.qwGuildID;
            else
                return wLevel > rRank.wLevel;
        }
        else
            return dwScore > rRank.dwScore;
    }
};

void   CGuildMgr::SyncBattleRank()
{
    set<SGuildRank> setRank;
    for (auto& rPair:_mapGuildBattleScore)
    {
        if (!rPair.first)
            continue;
        auto it = _mapGuild.find(rPair.first);
        if (it == _mapGuild.end() || !it->second)
        {
            LOG_CRI << "Wrong Guild(" << rPair.first << ").";
            continue;
        }
        CGuildPtr pGuild = it->second;

        SGuildRank sRank(rPair.second, rPair.first, pGuild->GetLevel());
        setRank.insert(sRank);
        pGuild->UpdateRankInfo(rPair.second);

        /*
        TVecRankInfo vecRankInfo;
        SGRBattleInfoPtr pInfo (new SGRBattleInfo);
        pInfo->dwValue = rPair.second;
        pInfo->qwGuildID = pGuild->GetID();
        pInfo->strGuildName = pGuild->GetName();
        pInfo->strName = pGuild->GetOwnerName();
        pInfo->qwRoleID = pGuild->GetOwnerID();
        pInfo->wLevel = pGuild->GetLevel();
        pInfo->dwBattleScore = rPair.second;
        pInfo->byQuality = pGuild->GetQuality();
        pInfo->wPlayerFighterID = pGuild->GetPlayerFighterID();
        vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
        CRankMgr::Instance().UpdateRankInfo(rPair.first, eRTGuildBattle, vecRankInfo);
        */
    }
    _mapGuildBattleRank.clear();
    UINT32 dwRank = 1;
    for (auto it = setRank.begin(); it != setRank.end(); ++it, ++dwRank)
    {
        LOG_DBG << "Guild(" << (*it).qwGuildID << "): " << dwRank << ".";
        _mapGuildBattleRank[(*it).qwGuildID] = dwRank;
    }
}

UINT32 CGuildMgr::GetBattleRank(UINT64 qwRoleID) const
{
    auto it = _mapGuildBattleRank.find(qwRoleID);
    if (it != _mapGuildBattleRank.end())
        return it->second;
    else
        return 0;

}

void CGuildMgr::InitGuildRankByLevel()
{
    _setGuildRankByLevel.clear();
    if(_mapGuild.size() == 0)
    {
        LOG_CRI <<" _mapGuild size (0) after InitFromDB.";
    }
    for (auto& rPair:_mapGuild)
    {
        if (!rPair.first)
            continue;
        
        auto it = _mapGuild.find(rPair.first);
        if (it == _mapGuild.end() || !it->second)
        {
            LOG_CRI << "Wrong Guild(" << rPair.first << ").";
            continue;
        }
        CGuildPtr pGuild = it->second;

        SGuildStatueInfo sStatueInfo ;
        if(!pGuild->GetStatueInfo(sStatueInfo))
        {
            LOG_CRI << " GetStatueInfo Error.";
            continue;
        }
        UINT32 dwExp = sStatueInfo.dwExp;
        UINT32 dwTime = sStatueInfo.dwTime;
        SGuildRankByLevel sRank(rPair.first, pGuild->GetLevel(),dwTime,dwExp);
        if(_setGuildRankByLevel.count(sRank))
        {
            LOG_INF << " Guild(" << rPair.first<<" ) Init twice.";
            continue;
        }
        _setGuildRankByLevel.insert(sRank);
    }
}

bool CGuildMgr::SyncGuildRankByLevel(UINT64 qwGuildID,bool bFair)
{
    auto it = _mapGuild.find(qwGuildID);
    if (it == _mapGuild.end() || !it->second)
    {
        LOG_CRI << "Wrong Guild(" << qwGuildID << ").";
        return false;
    }
    CGuildPtr pGuild = it->second;

    SGuildStatueInfo sStatueInfo ;
    if(!pGuild->GetStatueInfo(sStatueInfo))
    {
        LOG_CRI << " GetStatueInfo Error.";
        return false;
    }
    UINT32 dwE = sStatueInfo.dwExp;
    UINT32 dwT = sStatueInfo.dwTime;
    LOG_INF << "GuildID("<<qwGuildID <<"),Exp(" <<dwE<<"),Time("<<dwT<<").";
    SGuildRankByLevel sRank(qwGuildID, pGuild->GetLevel(),dwT,dwE);
    for(auto & oIt : _setGuildRankByLevel)
    {
        auto oTmp = oIt;
        if(oTmp.qwGuildID == qwGuildID)
        {
            _setGuildRankByLevel.erase(oTmp);
        }

    }

    if(!bFair) //不是解散
    {
        _setGuildRankByLevel.insert(sRank);
        LOG_INF << "Guild("<<qwGuildID<<")| NewLevel("<<pGuild->GetLevel()<<") Insert Suc.";
    }

    return true;
}

UINT64 CGuildMgr::GetFirstGuildByLevel()
{
    if(!_setGuildRankByLevel.size())
    {
        LOG_INF << " _setGuildRankByLevel size 0";
        return 0;
    }
    auto oIt = _setGuildRankByLevel.begin();
    return (*oIt).qwGuildID;
}

UINT32 CGuildMgr::GetRankForLevel(UINT64 &qwGuildID)
{
    UINT32 dwRank = 0;
    if(!qwGuildID)
    {
        LOG_INF << " qwGuildID is 0.";
        return dwRank;
    }

    auto it = _mapGuild.find(qwGuildID);
    if (it == _mapGuild.end() || !it->second)
    {
        LOG_CRI << "Wrong Guild(" << qwGuildID << ").";
        return dwRank;
    }
    CGuildPtr pGuild = it->second;

    if(!pGuild)
    {
        LOG_CRI << "Wrong Guild(" << qwGuildID << ").";
        return dwRank;
    }
    for(auto & oIt : _setGuildRankByLevel)
    {
        dwRank ++;
        if(oIt.qwGuildID == qwGuildID)
        {
            return dwRank; 
        }
    }
    LOG_INF <<"dwRank="<<dwRank<<"| setSize="<<_setGuildRankByLevel.size();
    if(dwRank == _setGuildRankByLevel.size())
        dwRank = 0;
    return dwRank;
}

bool CGuildMgr::GetGuildLevelRank(std::set<SGuildRankByLevel> &setRank)
{
    if(_setGuildRankByLevel.size() == 0)
    {
        LOG_INF << " _setGuildRankByLevel size is 0";
        return false;
    }
    setRank.insert(_setGuildRankByLevel.begin(),_setGuildRankByLevel.end());
    return true;
}

bool CGuildMgr::IsGuildOpEnable() const
{
    return _bGuildOpEnable;
}

void CGuildMgr::SetGuildOpEnable(bool bEnable, EOpDisableType eType)
{
    _bGuildOpEnable = bEnable;
    _eOpDisableType = eType;
}

CGuildMgr::EOpDisableType CGuildMgr::GetOpDisableType() const
{
    return _eOpDisableType;
}

void CGuildMgr::TimeCheck(time_t tNow)
{
    time_t tCheckTime = Time::TheDay() + _dwStatueCheckTime;
    if (tNow >= tCheckTime)
    {
        if(!g_CenterGameVar.GetVar(NVarDefine::eSystemVarGuildStatue))
        {
            //g_Center2DBGuildC.Send_GuildStatueReward();
            for (auto it = _mapGuild.begin(); it != _mapGuild.end(); ++it)
            {
                CGuildPtr pGuild = it->second;
                if (pGuild)
                    pGuild->StatueReward();
            }

            g_CenterGameVar.SetVar(NVarDefine::eSystemVarGuildStatue, 1);
        }
    }

    if (tNow >= _dwBattleCleanTime)
    {
        for (auto& rPair : _mapGuildBattleScore)
        {
            string strData;
            SDBGuildBattleInfo sDBGuildBattleInfo;
            sDBGuildBattleInfo.qwGuildID = rPair.first;
            sDBGuildBattleInfo.dwScore = rPair.second;
            COutArchive iar(strData);
            iar << sDBGuildBattleInfo;
            g_Center2DBGuildC.Send_GuildPubDataUpdate(rPair.first, eGPDTBattleInfo, eOpDel, strData);

            rPair.second = 0;
            UpdateOrderListBattleScore(rPair.first);
        }
        _mapGuildBattleRank.clear();
        _mapGuildBattleScore.clear();
        _dwBattleCleanTime = Time::TheWeek(1);
    }
    tCheckTime = Time::TheWeek() + _dwBattleAwardTime;
    if (tNow >= tCheckTime)
    {
        if(!g_CenterGameVar.GetVar(NVarDefine::eSystemVarGuildBattleAward))
        {
            for (auto it = _mapGuild.begin(); it != _mapGuild.end(); ++it)
            {
                CGuildPtr pGuild = it->second;
                if (pGuild)
                    pGuild->BattleReward();
            }

            g_CenterGameVar.SetVar(NVarDefine::eSystemVarGuildBattleAward, 1);
        }
    }
    
    if (tNow >= _dwGuildExchangedItemCleanTime)
    {
        for (auto it = _mapGuild.begin(); it != _mapGuild.end(); ++it)
        {
            CGuildPtr pGuild = it->second;
            if (pGuild)
                pGuild->GuildExchangedItemZeroClean();
        }
        _dwGuildExchangedItemCleanTime = Time::TheDay(1);
    }
}

// XXX: 这个函数没有任何地方调用了
bool CGuildMgr::StatueReward(const TVecGSWorshipInfo& rvecInfo)
{
    LOG_WRN << "rvecInfo.size() = " << rvecInfo.size() << ".";
    for (auto it = rvecInfo.begin(); it != rvecInfo.end(); ++it)
    {
        LOG_WRN << "ID = " << (*it).qwGuildID << ".";
        LOG_WRN << "byWorshipCount = " << static_cast<UINT32>((*it).byWorshipCount) << ".";
        UINT8 byWorshipCount = (*it).byWorshipCount;
        if (!byWorshipCount)
            continue;
        UINT16 wCount1 = byWorshipCount * 100;
        UINT16 wCount2 = byWorshipCount * 100;
        CSystemMail sysMail;
        for (auto it2 = (*it).vecMemberID.begin(); it2 != (*it).vecMemberID.end(); ++it2)
        {
            LOG_WRN << "RoleID = " << (*it2) << ".";
            sysMail.AddTarget(*it2);
            sysMail.SetSender("系统");
            sysMail.SetSubject("神像");


            SItemAttachmentPtr pItem(new SItemAttachment());

            SMailItemInfo stAttach;
            stAttach.wItemID = 2;
            stAttach.wCount = wCount1;
            pItem->vecItemInfo.push_back(stAttach);

            stAttach.wItemID = 29;
            stAttach.wCount = wCount2;
            pItem->vecItemInfo.push_back(stAttach);
            sysMail.SetBody(SysMailSendTxt(50, BuildStrVec(byWorshipCount, wCount1, wCount2)));

            sysMail.AddItemInfo(pItem->vecItemInfo);
        }
        if (!(*it).vecMemberID.empty())
            sysMail.Send();
    }
    return true;
}

const SGuildStepAwardCFGEx* CGuildMgr::GetBattleAward(UINT16 wLevel) const
{
    if (wLevel >= _vecBattleAward.size())
    {
        if (_vecBattleAward.empty())
            return NULL;
        else
            return _vecBattleAward[0];
    }
    return _vecBattleAward[wLevel];
}

void CGuildMgr::WriteGuildLog(SLogOp &sLog)
{
    UINT64 qwID = sLog.qwGuildID;
    ELogOpType eType = sLog.eType;
    CGuildPtr pGuild = GetGuild(qwID);
    if(!pGuild)
        return;
    CGuildBuildingOwnerPtr pBuild = pGuild->GetBuildingOwner();
    if(!pBuild)
        return;
    NLogDataDefine::SGuildLogPtr ptrLog(new NLogDataDefine::SGuildLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SGuildLog& rLog = *ptrLog;
    UINT32 dwTime = time(NULL);
    rLog.dwServerId = Config._wGroup;
    rLog.qwGuildId  = qwID;
    rLog.sName      = pGuild->GetName();
    rLog.byLevel    = pGuild->GetLevel();
    rLog.dwCount    = pGuild->GetMemberCount();
    rLog.dwMoney    = pGuild->GetMoney();
    rLog.dwScore    = pGuild->GetBattleScore();
    rLog.byTowerLvl  = pBuild->GetLevel(eBuildingOracle);
    rLog.byStoreLvl  = pBuild->GetLevel(eBuildingStore);
    rLog.byHourseLvl = pBuild->GetLevel(eBuildingSword);
    rLog.happenedTime   = dwTime;
    switch(eType)
    {
#define CASE(eType,byValue1,byValue2) \
        case eType: { \
                       rLog.byOptType = byValue1; \
                       rLog.byOptParam = byValue2; \
                    } \
                    break; 
        CASE(eOpType_Create,1,0);
        CASE(eOpType_Apply,2,1);
        CASE(eOpType_Donate ,2,2);
        CASE(eOpType_Score,2,3);
        CASE(eOpType_Tower,2,4);
        CASE(eOpType_Store,2,5);
        CASE(eOpType_Hourse,2,6);
    }
    CCenterServerLog::LogToDB(ptrLog);
}

SXiHeTruckCFGEx* CGuildMgr::GetXiHeTruckCfg(UINT8 byTruckID)
{
    auto it = _mapID2XiHeTruckCFG.find(byTruckID);
    if (it != _mapID2XiHeTruckCFG.end())
        return &it->second;
    return NULL;
}

void CGuildMgr::GetTruckIDRandom(UINT8 byLevel, TVecUINT8& vecIDs) const
{
    vecIDs.clear();
    TVecUINT8 vecTmpID;
    for (auto it = _mapID2XiHeTruckCFG.begin(); it != _mapID2XiHeTruckCFG.end(); ++ it)
    {
        if (byLevel && it->second._byMinLvl <= byLevel && it->second._byMaxLvl >= byLevel)
            vecTmpID.push_back(it->first);
    }
    size_t size = vecTmpID.size();
    for (int i = 0; i < 2; ++ i)
    {
        if (!size)
            continue;
        UINT8 byIdx = CRandom::RandInt(0, size-1);
        vecIDs.push_back(vecTmpID[byIdx]);
    }
    string strKey = "0,0";
    auto it = _mapLevelStr2TruckID.find(strKey);
    if (it != _mapLevelStr2TruckID.end())
    {
        size_t size = it->second.size();
        int i = 8 - vecIDs.size();
        for (; i > 0; -- i)
        {
            if (!size)
                continue;
            UINT8 byIdx = CRandom::RandInt(0, size-1);
            vecIDs.push_back(it->second[byIdx]);
        }
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  UpdateOrderListMemberCount
//  Description:  
// =====================================================================================
void CGuildMgr::UpdateOrderListMemberCount(UINT64 qwGuildID, UINT16 wLevel, UINT16 wMemberCount)
{
    SOrderListInfo sInfo(qwGuildID, wLevel, wMemberCount);
    auto it = _mapItOrderInfo.find(qwGuildID);
    if (it != _mapItOrderInfo.end())
        _setOrderListInfo.erase (it->second);
    auto const& rPair = _setOrderListInfo.insert (sInfo);
    _mapItOrderInfo[qwGuildID] = rPair.first;

    LOG_WRN << "UpdateOrderListMemberCount: " << qwGuildID << ", " << wLevel << ", " << wMemberCount << ";";
}		// -----  end of function UpdateOrderListMemberCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateOrderListBattleScore
//  Description:  
// =====================================================================================
void CGuildMgr::UpdateOrderListBattleScore(UINT64 qwGuildID)
{
    // XXX: 这里不和帮派战分数有关，不需要更新排名了
    return;

    UINT32 dwBattleScore = 0;
    auto it = _mapGuildBattleScore.find(qwGuildID);
    if (it != _mapGuildBattleScore.end())
        dwBattleScore = it->second;

    UINT16 wMemberCount = 0;
    CGuildListInfoPtr pList = GetListInfo(qwGuildID);
    if (pList)
        wMemberCount = pList->GetMemberCount();
    SOrderListInfo sInfo(qwGuildID, dwBattleScore,  wMemberCount);
    _setOrderListInfo.erase (sInfo);
    _setOrderListInfo.insert (sInfo);
    LOG_WRN << "UpdateOrderListBattleScore: " << qwGuildID << ", " << dwBattleScore << ", " << wMemberCount << ";";
}		// -----  end of function UpdateOrderListBattleScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemoveOrderList
//  Description:  移除排序的帮派
// =====================================================================================
void CGuildMgr::RemoveOrderList (UINT64 qwGuildID)
{
    auto it = _mapItOrderInfo.find(qwGuildID);
    if (it != _mapItOrderInfo.end())
    {
        _setOrderListInfo.erase (it->second);
        _mapItOrderInfo.erase(it);
    }
}		// -----  end of function RemoveOrderList  ----- //
