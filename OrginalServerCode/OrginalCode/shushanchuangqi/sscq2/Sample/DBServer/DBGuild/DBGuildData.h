#ifndef DB_GUILD_DATA_H
#define DB_GUILD_DATA_H

#include <bitset>
#include <Center2DBComm.h>
#include <GuildProt.h>

#include "DBGuildTableBase.h"
#include "GuildProt.h"

using namespace NCenter2DBComm;
using namespace NGuildProt;

// 帮派属性 ：　帮派数据状态
enum EGuildState
{
    eGuildNone,
    eGuildBusy,		    //帮派有人在线||有活动
    eGuildIdle,         //帮派没人在线&&没活动
    eGuildMax
};

const UINT32 DEFAULT_GUILD_LIVE_TIME = 15 * 60;

enum EGuildUpdateStatus
{
    DATAUPDATE_NONE,//无数据更新
    DATAUPDATA_WILL,//有数据更新
};

// 帮派数据信息
class CDBGuildData :  public CPoolObj<CDBGuildData>
{
    // 构造函数
    public:
        CDBGuildData(UINT64 qwGuildID);
        virtual ~CDBGuildData();

    public: 
        map<EGuildDataType,CTableManagerBaseForGuild*> _mapDataManager;

        EGuildUpdateStatus GetUpdateStatus() const;
        void SetUpdateStatus(EGuildUpdateStatus eStatus);

        bool HasUpdateNum();
        UINT32 UpdateNum();
        CTableManagerBaseForGuild* GetDataManagerByType(EGuildDataType etype);
        EGuildState GetGuildState();
        void SetGuildState(EGuildState eGuildState);

        UINT64 GetGuildID() const;

        UINT32 GetNowUpdate() const;
        void   SetNowUpdate(UINT32 dwNowUpdate);
        void   AddNowUpdate(UINT32 dwNowUpdate = 1);

    private:
        void SaveGuild(bool bIsAll);

    private:
        UINT64 _qwGuildID;
        EGuildState _eGuildState;
        UINT32 _dwNowUpdate;   
        EGuildUpdateStatus _eUpdateDataStatus;    
};

class CDBPubGuildData : public CPoolObj<CDBPubGuildData>
{
    // 构造函数
    public:
        CDBPubGuildData(UINT64 qwGuildID);
        virtual ~CDBPubGuildData();

    public: 
        EGuildUpdateStatus GetUpdateStatus() const;
        void SetUpdateStatus(EGuildUpdateStatus eStatus);
        map<EGuildPubDataType, CTableManagerBaseForGuildPub*> _mapDataManager;

        bool HasUpdateNum();
        UINT32 UpdateNum();
        CTableManagerBaseForGuildPub* GetDataManagerByType(EGuildPubDataType etype);
        EGuildState GetGuildState();
        void SetGuildState(EGuildState eGuildState);

        UINT64 GetGuildID() const;

        UINT32 GetNowUpdate() const;
        void   SetNowUpdate(UINT32 dwNowUpdate);
        void   AddNowUpdate(UINT32 dwNowUpdate = 1);

    private:
        void SaveGuild(bool bIsAll);

    private:
        EGuildState _eGuildState;
        UINT32 _dwNowUpdate;   
        EGuildUpdateStatus _eUpdateDataStatus;    
        UINT64 _qwGuildID;
};

#endif // #ifndef DB_GUILD_DATA_H
