// =====================================================================================
//
//       Filename:  DBRankTableBase.h
//
//    Description:  排行榜基本表类型
//
//        Version:  1.0
//        Created:  09/05/2014 01:24:25 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_RANK_TABLE_BASE_H
#define DB_RANK_TABLE_BASE_H

#include "stdafx.h"

#include "DBTableBase.h"

#include "RankProt.h"
using namespace NRankProt;
using namespace NProtoCommon;
class CTableManagerBaseForRoleRank
{
    public:
        CTableManagerBaseForRoleRank();
        virtual ~CTableManagerBaseForRoleRank();

        //查询
        virtual void QueryDataByRoleID(UINT64 qwRankID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData, UINT64 qwRankID = 0) = 0;
        //更新，增加
        virtual void Update(string& strData, EDataChange eUpdateType) = 0;
        //获得原始数据
        virtual void GetAllInfo(TVecRankInfo& rvecInfo) = 0;
        //更新放入数据库
        virtual void  DumpToDBRank(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static CTableManagerBaseForRoleRank* CreateManager(ERankType eType, UINT64 qwRankID);
        static void DestroyManager(CTableManagerBaseForRoleRank* pManager);

        ERankType GetDataType() { return _eType; }
        CTableManagerBaseForRoleRank(ERankType etype, UINT64 qwRankID) : _eType(etype), _qwRoleID(qwRankID) {}

    private:
        ERankType _eType;

    protected:
        UINT64 _qwRoleID;
};

class CTableManagerBaseForGuildRank
{
    public:
        CTableManagerBaseForGuildRank();
        virtual ~CTableManagerBaseForGuildRank();
            
        //查询
        virtual void QueryDataByRankID(UINT64 qwRankID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData, UINT64 qwRankID = 0) = 0;
        //更新，增加
        virtual void Update(string& strData, EDataChange eUpdateType) = 0;
        //获得原始数据
        virtual void GetAllInfo(TVecRankInfo& rvecInfo) = 0;
        //更新放入数据库
        virtual void  DumpToDBRank(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static CTableManagerBaseForGuildRank* CreateManager(ERankType eType, UINT64 qwRankID);
        static void DestroyManager(CTableManagerBaseForGuildRank* pManager);

        ERankType GetDataType() { return _eType; }
        CTableManagerBaseForGuildRank(ERankType etype, UINT64 qwRankID) : _eType(etype), _qwRankID(qwRankID) {}

    private:
        ERankType _eType;

    protected:
        UINT64 _qwRankID;
};

class CTableManagerBaseForRoleAdore
{
    public:
        CTableManagerBaseForRoleAdore();
        virtual ~CTableManagerBaseForRoleAdore();
            
        //查询
        virtual void QueryDataByRoleID(UINT64 qwRoleID, QueryFun fun) = 0;//返回查询的结果数量
        //删除
        virtual void DelData(string& strData, UINT64 qwRoleID = 0) = 0;
        //更新，增加
        virtual void Update(string& strData, EDataChange eUpdateType) = 0;
        //获得原始数据
        virtual void GetAllInfo(TVecRankInfo& rvecInfo) = 0;
        //更新放入数据库
        virtual void  DumpToDBRank(ManagerUpdateFun fun) = 0;
        virtual UINT32 GetUpdataNum() = 0; 

        static CTableManagerBaseForRoleAdore* CreateManager(UINT64 qwRoleID);
        static void DestroyManager(CTableManagerBaseForRoleAdore* pManager);

        CTableManagerBaseForRoleAdore(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}

    protected:
        UINT64 _qwRoleID;

};

#endif // #ifndef DB_RANK_TABLE_BASE_H
