// =====================================================================================
//
//       Filename:  DBRankTableBase.cpp
//
//    Description:  排行榜基本表类型
//
//        Version:  1.0
//        Created:  09/05/2014 01:24:50 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================
#include "DBRankTableBase.h"

#include "DBRankBattlePointTable.h"
#include "DBRankFormationTable.h"
#include "DBRankHeroFighterTable.h"
#include "DBRankTrumpTable.h"
#include "DBRankLevelTable.h"

CTableManagerBaseForRoleRank::CTableManagerBaseForRoleRank()
{
}

CTableManagerBaseForRoleRank::~CTableManagerBaseForRoleRank()
{
}

CTableManagerBaseForRoleRank* CTableManagerBaseForRoleRank::CreateManager(ERankType eType,UINT64 qwRankID)
{
    switch (eType)
    {
        case eRTBattlePoint: //总战力榜
            return new CDBRankBattlePointTableManager(qwRankID);
        case eRTLevel:
            return new CDBRankLevelTableManager(qwRankID);
        case eRTFormation: //阵灵榜
            return new CDBRankFormationTableManager(qwRankID);
        case eRTHeroFighter: //散仙榜
            return new CDBRankHeroFighterTableManager(qwRankID);
        case eRTTrump: //法宝榜
            return new CDBRankTrumpTableManager(qwRankID);
        default:
            LOG_CRI << "Invalid ERankType: " << static_cast<UINT32>(eType) << ".";
            return NULL;
    }
    return NULL;
}

void CTableManagerBaseForRoleRank::DestroyManager(CTableManagerBaseForRoleRank* pManager)
{
    if (NULL != pManager)
    {
        delete pManager;
        pManager = NULL;
    }
}

CTableManagerBaseForGuildRank::CTableManagerBaseForGuildRank()
{
}

CTableManagerBaseForGuildRank::~CTableManagerBaseForGuildRank()
{
}

CTableManagerBaseForGuildRank* CTableManagerBaseForGuildRank::CreateManager(ERankType eType, UINT64 qwRankID)
{
    switch (eType)
    {
        default:
            LOG_CRI << "Invalid EPubRankDataType: " << static_cast<UINT32>(eType) << ".";
            return NULL;
    }
    return NULL;
}

void CTableManagerBaseForGuildRank::DestroyManager(CTableManagerBaseForGuildRank* pManager)
{
    if (NULL != pManager)
    {
        delete pManager;
        pManager = NULL;
    }
}

