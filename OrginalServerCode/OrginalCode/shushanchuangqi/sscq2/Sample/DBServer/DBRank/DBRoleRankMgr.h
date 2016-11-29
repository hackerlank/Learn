// =====================================================================================
//
//       Filename:  DBRoleRankMgr.h
//
//    Description:  排行榜数据管理
//                  崇拜数据管理
//
//        Version:  1.0
//        Created:  09/05/2014 02:04:41 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_ROLE_RANK_MGR_H
#define DB_ROLE_RANK_MGR_H

#include "stdafx.h"

#include <Singleton.h>
#include <queue>

#include "RankProt.h"

using namespace NRankProt;
using namespace NProtoCommon;

class CDBRoleRankData;

class CDBRoleRankMgr : public Singleton<CDBRoleRankMgr>
{
    public:
        virtual ~CDBRoleRankMgr();
        CDBRoleRankDataPtr GetRankData(UINT64 qwRoleID);
        CDBRoleAdoreDataPtr GetAdoreData(UINT64 qwRoleID);

        void LoadAllRankData();
        void LoadRankData(UINT64 qwRoleID, function<void(CDBRoleRankDataPtr, ERankResult)> funcLoaded);
        void LoadAdoreData(UINT64 qwRoleID, function<void(CDBRoleAdoreDataPtr, EAdoreResult)> funcLoaded);
        void CheckRankState(CDBRoleRankDataPtr pData);
        void SaveRank(bool bIsAll);
        void SendDataToCenter(UINT32 dwTotalPage, UINT32 dwTotalSize, const TVecRankInfo& vecDBRoleRankAllInfo);

        void RankDataOperate(UINT64 qwInstID, ERankType eDataType, EDataChange eUpdateType, const std::string& strData);

        void GetAllInfo(TVecRankInfo& rvecInfo, CDBRoleRankDataPtr pRankData);
        void GetAllInfo(TVecDBAdoreInfo& rvecInfo, CDBRoleAdoreDataPtr pRankData);

        void AdoreDataOperate(UINT64 qwInstID, EDataChange eUpdateType, const std::string& strData);
        void LoadAllAdoreData();
        void CheckAdoreState(CDBRoleAdoreDataPtr pData);
        void SaveAdore(bool bIsAll);
        bool SendAdoreDataToCenter(UINT32 dwTotalPage, UINT32 dwTotalSize, TVecDBAdoreInfo& vecDBAdoreInfo);

    private:
        bool AddRankData       (CDBRoleRankDataPtr pRankData);
        bool AddRankDataCache  (CDBRoleRankDataPtr pRankData);

        void CreateRank(UINT64 qwRoleID, ERankType eDataType, const std::string& strData, function<void(CDBRoleRankDataPtr, ERankResult)> cb);
        void DoCreateRank(CDBRoleRankDataPtr pRankData, ERankType eDataType, const string& strData, function<void(CDBRoleRankDataPtr, ERankResult)> cb );

        void QueryRankData(UINT32 dwPageSize,QueryFun queryfun);

        bool AddAdoreData      (CDBRoleAdoreDataPtr pAdoreData);
        bool AddAdoreDataCache (CDBRoleAdoreDataPtr pAdoreData);

        void CreateAdore(UINT64 qwRoleID, const std::string& strData, function<void(CDBRoleAdoreDataPtr, EAdoreResult)> cb);
        void DoCreateAdore(CDBRoleAdoreDataPtr pAdoreData, const string& strData, function<void(CDBRoleAdoreDataPtr, EAdoreResult)> cb );

        void QueryAdoreData(UINT32 dwPageSize,QueryFun queryfun);


    private:
        map<UINT64, CDBRoleRankDataPtr>    _mapRoleRankData;
        map<UINT64, CDBRoleRankDataPtr>    _mapRoleRankDataCache;

        map<UINT64, CDBRoleAdoreDataPtr>   _mapRoleAdoreData;
        map<UINT64, CDBRoleAdoreDataPtr>   _mapRoleAdoreDataCache;

        queue<CDBRoleRankDataPtr>          _queueUpdate;
        queue<CDBRoleAdoreDataPtr>         _queueRoleAdoreUpdate;
};

#endif // #ifndef DB_ROLE_RANK_MGR_H
