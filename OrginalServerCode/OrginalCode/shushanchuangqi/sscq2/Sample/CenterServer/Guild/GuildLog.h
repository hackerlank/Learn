#ifndef GUILD_LOG_H
#define GUILD_LOG_H

#include  "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

extern const char* g_strRank[];
extern const char* g_strBuilding[];
extern const char* g_strWorship[];

class CGuildLog
{
    public:
        CGuildLog();
        virtual ~CGuildLog();

        virtual ELogType GetType() const = 0;

        UINT16 GetID() const;

        bool GetAllInfo(SGuildLogInfo& rInfo) const;

        bool InitFromDB(const SGuildLogInfo& rInfo);

        static void Update2DB(CGuildLogPtr pGuildLog, EDataChange eChangeType, UINT64 qwGuild);

    protected:
        virtual bool FormatParam(UINT16 wMsgID, TVecINT64& rvecParam, TVecString& rvecString);

    private:
        UINT64      _qwInstID;
        UINT16      _wMsgID;
        TVecINT64   _vecParam;
        TVecString  _vecString;
        UINT32      _dwTime;
};

class CGuildMemberLog : public CGuildLog
{
    public:
        CGuildMemberLog();
        virtual ~CGuildMemberLog();

        virtual ELogType GetType() const;

        bool FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName);
        bool FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName, UINT8 byQuality2, string strName2);
        bool FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName, UINT8 byQuality2, string strName2, EMemberRank eRank);
};

class CGuildBuildingLog : public CGuildLog
{
    public:
        CGuildBuildingLog();
        virtual ~CGuildBuildingLog();

        virtual ELogType GetType() const;

        //建筑升级信息：仓库升级到了7级
        bool FormatParam(EBuildingType eType, UINT16 wLevel);
};

class CGuildDonateLog : public CGuildLog
{
    public:
        CGuildDonateLog();
        virtual ~CGuildDonateLog();

        virtual ELogType GetType() const;

        //捐献信息：XXX捐献了XXX银币
        bool FormatParam(UINT8 byQuality, string strName, UINT32 dwMoney);
};

class CGuildStatueLog : public CGuildLog
{
    public:
        CGuildStatueLog();
        virtual ~CGuildStatueLog();

        virtual ELogType GetType() const;

        //神像供奉信息：XXX消耗1000银币用鲜花供奉了帮派神像
        bool FormatParam(UINT8 byQuality, string strName, EWorshipType eType, UINT32 dwMoney);
};

#endif // #ifndef GUILD_LOG_H
