#ifndef DB_GUILD_MGR_H
#define DB_GUILD_MGR_H

#include "stdafx.h"

#include <Singleton.h>
#include <queue>

#include "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

class CDBGuildData;

const UINT32 DEFAULT_GUILD_HIGH_MARK = 100;
const UINT32 DEFAULT_GUILD_LOW_MARK = 20;


class CDBGuildMgr : public Singleton<CDBGuildMgr>
{
    public:
        virtual ~CDBGuildMgr();
        CDBGuildDataPtr GetGuildData(UINT64 qwGuildID);

        void UserLoginGuild(UINT64 qwRoleID);
        void LoginGuild(UINT64 qwGuildID, UINT64 qwRoleID);

        void LoadAllGuildData();
        void LoadGuildData(UINT64 qwGuildID, function<void(CDBGuildDataPtr, EGuildResult)> funcLoaded);
        void LoadIdleGuildUserData(UINT64 qwRoleID, function<void(CDBGuildDataPtr, EGuildResult)> funcLoaded);
        bool CheckGuildState(CDBGuildDataPtr pData, bool bIsUpdate);
        void SaveGuild(bool bIsAll);
        bool SendDataToCenter(CDBGuildData& rGuildData);
        bool SendDataToCenter(UINT32 dwTotalPage, UINT32 dwTotalSize, const TVecDBGuildAllInfo& vecDBGuildAllInfo);
        bool SendUserDataToCenter(CDBGuildData& rGuildData, UINT64 qwRoleID);

        void GuildDataOperate(UINT64 qwGuildID, EGuildDataType eDataType, EDataChange eUpdateType, const std::string& strData);

        bool EnterGame(CDBGuildData& rGuildData);
        void GetAllInfo(SDBGuildAllInfo &rInfo,CDBGuildData& rGuildData);

        void SendAllGuildWorshipInfo();

        void DumpToDB(bool bForBit);

    private:

        void GuildListInfoDataOperate(UINT64 qwGuildID, EDataChange eUpdateType, const std::string& strData);
        bool AddGuildData       (CDBGuildDataPtr pGuildData);
        bool AddGuildDataCache  (CDBGuildDataPtr pGuildData);
        void EraseGuildDataCache(CDBGuildDataPtr pGuildData);

        void CreateGuild(UINT64 qwGuildID, EGuildDataType eDataType, const std::string& strData, function<void(CDBGuildDataPtr, EGuildResult)> cb);
        void DoCreateGuild(bool bNew, CDBGuildDataPtr pGuildData, EGuildDataType eDataType, const string& strData, function<void(CDBGuildDataPtr, EGuildResult)> cb );

        void DelGuildData(CDBGuildDataPtr pGuildData);

        void CleanIdleGuild();
        void QueryData(UINT32 dwPageSize,QueryFun queryfun);

    private:
        map<UINT64, CDBGuildDataPtr>    _mapGuildData;
        map<UINT64, CDBGuildDataPtr>    _mapGuildDataCache;
        queue<CDBGuildDataPtr>          _queueUpdate;
        queue<CDBGuildDataPtr>          _queueOffLine;
        map<UINT64, UINT32>             _mapIdleGuildTime; //<qwGuildID, dwLeaveTimeStamp>
};

#endif // #ifndef DB_GUILD_MGR_H
