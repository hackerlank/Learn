#ifndef DB_GUILD_TABLE_BASE_H
#define DB_GUILD_TABLE_BASE_H

#include "stdafx.h"

#include "DBTableBase.h"

#include "GuildProt.h"
using namespace NGuildProt;
using namespace NProtoCommon;
class CTableManagerBaseForGuild
{
    public:
        CTableManagerBaseForGuild();
        virtual ~CTableManagerBaseForGuild();

        //查询
        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData, UINT64 qwGuildID = 0) = 0;
        //更新，增加
        virtual void Update(string& strData, EDataChange eUpdateType) = 0;
        //获得原始数据
        virtual void GetAllInfo(SDBGuildAllInfo& rData) = 0;
        //更新放入数据库
        virtual void  DumpToDBGuild(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static CTableManagerBaseForGuild* CreateManager(EGuildDataType eType, UINT64 qwGuildID);
        static void DestroyManager(CTableManagerBaseForGuild* pManager);

        EGuildDataType GetDataType() { return _eType; }
        CTableManagerBaseForGuild(EGuildDataType etype, UINT64 qwGuildID) : _eType(etype), _qwGuildID(qwGuildID) {}

    private:
        EGuildDataType _eType;

    protected:
        UINT64 _qwGuildID;
};

class CTableManagerBaseForGuildPub
{
    public:
        CTableManagerBaseForGuildPub();
        virtual ~CTableManagerBaseForGuildPub();
            
        //查询
        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData, UINT64 qwGuildID = 0) = 0;
        //更新，增加
        virtual void Update(string& strData, EDataChange eUpdateType) = 0;
        //获得原始数据
        virtual void GetAllInfo(SPubGuildAllInfo& rData) = 0;
        //更新放入数据库
        virtual void  DumpToDBGuild(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static CTableManagerBaseForGuildPub* CreateManager(EGuildPubDataType eType, UINT64 qwGuildID);
        static void DestroyManager(CTableManagerBaseForGuildPub* pManager);

        EGuildPubDataType GetDataType() { return _eType; }
        CTableManagerBaseForGuildPub(EGuildPubDataType etype, UINT64 qwGuildID) : _eType(etype), _qwGuildID(qwGuildID) {}

    private:
        EGuildPubDataType _eType;

    protected:
        UINT64 _qwGuildID;
};

#endif

