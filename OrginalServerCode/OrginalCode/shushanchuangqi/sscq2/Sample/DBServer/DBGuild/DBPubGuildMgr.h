#ifndef DB_PUB_GUILD_MGR_H
#define DB_PUB_GUILD_MGR_H

#include "stdafx.h"

#include <Singleton.h>
#include <queue>

#include "GuildProt.h"

class CDBPubGuildData;

using namespace NGuildProt;
using namespace NProtoCommon;

class CDBPubGuildMgr    : public Singleton<CDBPubGuildMgr>
{
    public:
        virtual ~CDBPubGuildMgr();
        CDBPubGuildDataPtr GetPubGuildData(UINT64 qwGuildID);

        void GetAllData(UINT32 dwPageSize);

        void LoadPubGuildData   (UINT64 qwGuildID, function<void(CDBPubGuildDataPtr, EGuildResult)> funcLoaded);
        void DeletePubGuildData (UINT64 qwGuildID,  function<void(CDBPubGuildDataPtr, EGuildResult)> funcLoaded);
        bool CheckGuildState(CDBPubGuildDataPtr pData, bool bIsUpdate);
        void SavePubGuild(bool bIsAll);

        void TimerCheck(time_t tNow);

        void DataOperate(UINT64 qwGuildID, EGuildPubDataType eDataType, EDataChange eUpdateType, const std::string& strData);

        bool AddLoadOrCreate(UINT64 qwGuildID);
        void RemoveLoadOrCreate(UINT64 qwGuildID);
        void GetAllInfo(SPubGuildAllInfo &rInfo,CDBPubGuildDataPtr pGuildData);

        bool SendDataToCenter(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecPubGuildAllInfo& vecPubGuildAllInfo);

        void DumpToDB(bool bForBit);

    private:

        bool AddPubGuildData       (CDBPubGuildDataPtr pGuildData);

        void CreatePubGuild(UINT64 qwGuildID, EGuildPubDataType eDataType, const std::string& strData, function<void(CDBPubGuildDataPtr, EGuildResult)> cb);
        void DoCreatePubGuild(CDBPubGuildDataPtr pGuildData, EGuildPubDataType eDataType, const string& strData, function<void(CDBPubGuildDataPtr, EGuildResult)> cb );

        void DelPubGuildData(CDBPubGuildDataPtr pGuildData);

        void QueryData(UINT32 dwPageSize,QueryFun queryfun);

    private:
        queue<CDBPubGuildDataPtr>         _queueUpdate;
        queue<CDBPubGuildDataPtr>         _queueOffLine;
        set<UINT64>                     _setLoadOrCreate;
        map<UINT64, CDBPubGuildDataPtr>   _mapPubGuildData;
};

#endif // #define DB_PUB_GUILD_MGR_H
