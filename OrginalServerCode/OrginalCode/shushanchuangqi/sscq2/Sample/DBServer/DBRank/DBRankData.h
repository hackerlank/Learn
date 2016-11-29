// =====================================================================================
//
//       Filename:  DBRankData.h
//
//    Description:  排行榜数据
//
//        Version:  1.0
//        Created:  09/05/2014 02:04:04 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_RANK_DATA_H
#define DB_RANK_DATA_H

#include "stdafx.h"

#include <Center2DBComm.h>
#include <RankProt.h>

#include "DBRankTableBase.h"
#include "DBRoleAdoreTable.h"

using namespace NCenter2DBComm;
using namespace NRankProt;

enum ERankUpdateStatus
{
    DATAUPDATE_NONE,//无数据更新
    DATAUPDATA_WILL,//有数据更新
};

class CDBRankData
{
    // 构造函数
    public:
        CDBRankData(UINT64 qwInstID);
        virtual ~CDBRankData();

    public: 
        ERankUpdateStatus GetUpdateStatus() const;
        void SetUpdateStatus(ERankUpdateStatus eStatus);

        virtual bool HasUpdateNum(ERankType eType) = 0;
        virtual bool HasUpdateNum() = 0;
        virtual UINT32 UpdateNum() = 0;

        UINT64 GetInstID() const;

        UINT32 GetNowUpdate() const;
        void   SetNowUpdate(UINT32 dwNowUpdate);
        void   AddNowUpdate(UINT32 dwNowUpdate = 1);

        bool IsLoaded(ERankType eType) const;
        void SetLoaded(ERankType eType);

    protected:
        void SaveRank(bool bIsAll);

    protected:
        ERankUpdateStatus _eUpdateDataStatus;    
        UINT64 _qwInstID;
};

// 个人排名数据信息
class CDBRoleRankData : public CDBRankData, public CPoolObj<CDBRoleRankData>
{
    // 构造函数
    public:
        CDBRoleRankData(UINT64 qwInstID);
        virtual ~CDBRoleRankData();

        virtual bool HasUpdateNum(ERankType eType);
        virtual bool HasUpdateNum();
        virtual UINT32 UpdateNum();

        UINT64 GetRoleID() const;

    public: 
        map<ERankType,CTableManagerBaseForRoleRank*> _mapDataManager;

        CTableManagerBaseForRoleRank* GetDataManagerByType(ERankType etype);
};

// 帮派排名数据信息
class CDBGuildRankData : public CDBRankData, public CPoolObj<CDBGuildRankData>
{
    // 构造函数
    public:
        CDBGuildRankData(UINT64 qwInstID);
        virtual ~CDBGuildRankData();

        virtual bool HasUpdateNum(ERankType eType);
        virtual bool HasUpdateNum();
        virtual UINT32 UpdateNum();

    public: 
        map<ERankType, CTableManagerBaseForGuildRank*> _mapDataManager;

        CTableManagerBaseForGuildRank* GetDataManagerByType(ERankType etype);
};

class CDBRoleAdoreData : public CPoolObj<CDBRoleAdoreData>
{
    // 构造函数
    public:
        CDBRoleAdoreData(UINT64 qwInstID);
        virtual ~CDBRoleAdoreData();

        virtual bool HasUpdateNum();
        virtual UINT32 UpdateNum();

        ERankUpdateStatus GetUpdateStatus() const;
        void SetUpdateStatus(ERankUpdateStatus eStatus);

        CDBRoleAdoreTableManager* _pDataManager;

        UINT64 GetRoleID() const;

    private: 
        ERankUpdateStatus _eUpdateDataStatus;    
        UINT64 _qwRoleID;
};

#endif // #ifndef DB_RANK_DATA_H
