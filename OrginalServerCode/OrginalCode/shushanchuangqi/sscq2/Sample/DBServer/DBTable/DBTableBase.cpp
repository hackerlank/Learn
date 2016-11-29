
#include "DBTableBase.h"
#include "DBRoleItemTable.h"
#include "DBRoleBaseTable.h"
#include "DBRoleCittaTable.h"
#include "DBRoleDgnInfo.h"
#include "DBFighterTable.h"
#include "DBRoleTaskInfo.h"
#include "DBRoleSkillTable.h"
#include "DBFighterPassiveSkillTable.h"
#include "DBRoleFriendsTable.h"
#include "DBRoleVarsTable.h"
#include "DBSlotsTable.h"
#include "DBRoleTrumpTable.h"
#include "DBRoleEquipTrumpTable.h"
#include "DBRoleEquipTrumpShuffleTable.h"
#include "DBRoleFashionTable.h"
#include "DBFormationTable.h"
#include "DBPetDataTable.h"
#include "DBRolePetTable.h"
#include "DBBeastSoulTable.h"
#include "DBRoleArena.h"
#include "DBBuffTable.h"
#include "DBSoulSpaceTable.h"
#include "DBRoleGroupTask.h"
#include "DBRoleYaMenTask.h"
#include "DBRoleBubbleTable.h"
#include "DBRoleHorseTable.h"
#include "DBRoleActivityTask.h"
#include "DBRoleTitle.h"
#include "DBRoleAchievementTable.h"
#include "DBRoleCollectionTable.h"
#include "DBRoleAttackedTable.h"
#include "DBExchangedItemTable.h"
#include "DBRoleSweepTable.h"
#include "DBRolePendResInfo.h"
#include "DBRoleXinFaDataTable.h"
#include "DBTripodFireTable.h"
#include "DBRoleLevelPrizeTable.h"
#include "DBRoleYDTable.h"
#include "DBRoleEventTable.h"
#include "DBRoleShopItemTable.h"
#include "DBRoleDayTargetTable.h"
#include "DBTripodLogTable.h"
#include "DBTreasureHuntTable.h"
#include "DBRoleAutoStoreTable.h"
#include "DBRoleBeautyTable.h"
#include "DBRoleBattleArrayTable.h"
#include "DBFighterCombinationTable.h"
#include "DBRoleFightFormationTable.h"
#include "DBRoleFightHeroTable.h"
#include "DBGuardEMeiTable.h"
#include "DBRoleShengLingTable.h"
#include "DBRoleShengLingPrizeTable.h"

#include "DBRoleShipInfo.h"
#include "DBRoleGemstone.h"
TableRowBase::~TableRowBase()
{
}
TableRowBase::eDataState TableRowBase::GetDBState()
{
    return _eDBState;
}

bool TableRowBase::Update(string& strData,bool bIsAdd)
{
    if (bIsAdd && eInInit != _eDBState)
    {
        return false;
    }

    switch (_eDBState)
    {
        case eInInit:
            {
                _eDBState = eNoDB;
                InitDataByStr(strData);
            }
            break;           
        case eNoDB:
            {
                InitDataByStr(strData);
            }
            break;
        case eInDB:
            {
                if (UpdateDataByStr(strData))
                {
                    _eDBState = eInDBUpdate;
                }
            }
            break;
        case eInDBUpdate:
            {
                UpdateDataByStr(strData);
            }
            break;
        default:
            return false;
    }

    return true;
}

bool TableRowBase::IsInDB(void)
{
    return eInDB== _eDBState||eInDBUpdate == _eDBState;
}

bool TableRowBase::HasOP(void)
{
    return _eDBState == eInDBUpdate || _eDBState == eNoDB; 
}

void TableRowBase::DumpToDBOther(DumpFun dumpfun)
{
    if (!HasOP())
    {
        return dumpfun(UNKNOWNERR);
    }

    string sqlstr;
    if (_eDBState == eNoDB)
    {
        GetInsertSqlStr(sqlstr);
    }
    else
    {
        if (!GetUpdateSqlStr(sqlstr))
        {
            return dumpfun(UNKNOWNERR);
        }
    }

    _eDBState = eInDB;
    ResetChange();                
    CDBMgr::Instance().DoModifyQuery(sqlstr,NULL, [dumpfun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes) {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
        dumpfun(byRet);
    });
}

void TableRowBase::DumpToDBGuild(DumpFun dumpfun)
{
    if (!HasOP())
    {
        return dumpfun(UNKNOWNERR);
    }

    string sqlstr;
    if (_eDBState == eNoDB)
    {
        GetInsertSqlStr(sqlstr);
    }
    else
    {
        if (!GetUpdateSqlStr(sqlstr))
        {
            return dumpfun(UNKNOWNERR);
        }
    }

    _eDBState = eInDB;
    ResetChange();                
    LOG_DBG << "DumpToDBGuild: " << sqlstr;
    CDBMgr::Instance().DoGuildModifyQuery(sqlstr,NULL, [dumpfun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes) {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
        dumpfun(byRet);
    });
}

void TableRowBase::DumpToDBRank(DumpFun dumpfun)
{
    if (!HasOP())
    {
        return dumpfun(UNKNOWNERR);
    }

    string sqlstr;
    if (_eDBState == eNoDB)
    {
        GetInsertSqlStr(sqlstr);
    }
    else
    {
        if (!GetUpdateSqlStr(sqlstr))
        {
            return dumpfun(UNKNOWNERR);
        }
    }

    _eDBState = eInDB;
    ResetChange();                
    LOG_DBG << "DumpToDBRank: " << sqlstr;
    CDBMgr::Instance().DoRankModifyQuery(sqlstr,NULL, [dumpfun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes) {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
        dumpfun(byRet);
    });
}


void TableRowBase::DumpToDB(UINT8 byLine,DumpFun dumpfun)
{
    if (!HasOP())
    {
        return dumpfun(UNKNOWNERR);
    }

    string sqlstr;
    if (_eDBState == eNoDB)
    {
        GetInsertSqlStr(sqlstr);
    }
    else
    {
        if (!GetUpdateSqlStr(sqlstr))
        {
            return dumpfun(UNKNOWNERR);
        }
    }

    _eDBState = eInDB;
    ResetChange();
    CDBMgr::Instance().DoRoleModifyQuery(sqlstr,byLine, [dumpfun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes) {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
        dumpfun(byRet);
    });
}

void  TableRowBase::InitDataByDBRow(const mysqlpp::Row &row)//利用查询初始化
{
    _eDBState = eInDB;
}

TableManagerBaseForRole* TableManagerBaseForRole::CreateManager(EDataType eType,UINT64 qwRoleID,UINT8 byDBLine)
{
    switch (eType)
    {
#define NEW_MGR(T,M)                    \
        case T:                         \
            {                           \
                return new M(qwRoleID,byDBLine); \
            }                           \
            break

        NEW_MGR(eTypeRoleBaseInfo, DBRoleBaseTableManager);
        NEW_MGR(eTypeItemInfo, CDBRoleItemTableManager);
        NEW_MGR(eTypePlayerDgn, DBRoleDgnTableManager);
        NEW_MGR(eTypeCittaInfo, DBRoleCittaTableManager);
        NEW_MGR(eTypeFighterInfo, CDBFighterTableManager);
        NEW_MGR(eTypeTaskInfo, DBRoleTaskTableManager);
        NEW_MGR(eTypeSkillInfo, CDBRoleSkillTableManager);
        NEW_MGR(eTypePassiveSkillInfo, CDBFighterPassiveSkillTableManager);
        NEW_MGR(eTypeFriendInfo, CDBRoleFriendsTableManager);
        NEW_MGR(eTypeVarInfo, CDBRoleVarsTableManager);
        NEW_MGR(eTypeSlotsInfo, DBSlotsTableManager);
        NEW_MGR(eTypeTrumpInfo, DBRoleTrumpTableManager);
        NEW_MGR(eTypeEquipTrumpInfo, DBRoleEquipTrumpTableManager);
        NEW_MGR(eTypeEquipTrumpShuffleInfo, DBRoleEquipTrumpShuffleTableManager);
        NEW_MGR(eTypeFashionInfo, CDBRoleFashionTableManager);
        NEW_MGR(eTypeFormationInfo, CDBFormationTableManager);
        NEW_MGR(eTypePetDataInfo, CDBPetDataTableManager);
        NEW_MGR(eTypeRolePetInfo, CDBRolePetTableManager);
        NEW_MGR(eTypeBeastSoulInfo, CDBBeastSoulTableManager);
        NEW_MGR(eTypeArena,  CDBRoleArenaManager);
        NEW_MGR(eTypeBuffInfo,  CDBBuffTableManager);
        NEW_MGR(eTypeSoulSpaceInfo,CDBSoulSpaceTableManager);
        NEW_MGR(eTypeGroupTask,CDBRoleGroupTaskTableManager);
        NEW_MGR(eTypeYaMenTask,CDBRoleYaMenTaskTableManager);
        NEW_MGR(eTypeBubbleInfo,CDBRoleBubbleTableManager);
        NEW_MGR(eTypeHorseDBInfo,CDBRoleHorseDBTableManager);
        NEW_MGR(eTypeActivityTask,DBRoleActivityTaskTableManager);
        NEW_MGR(eTypeTitle,DBRoleTitleTableManager);
        NEW_MGR(eTypeAchievementInfo,CDBRoleAchievementTableManager);
        NEW_MGR(eTypeCollectionInfo,CDBRoleCollectionTableManager);
        NEW_MGR(eTypeAttacked,CDBRoleAttackedTableManager);
        NEW_MGR(eTypeExchangedItem,CDBRoleExchangedItemTableManager);
        NEW_MGR(eTypeSweep,CDBRoleSweepTableManager);
        NEW_MGR(eTypePendRes,DBRolePendResTableManager);
        NEW_MGR(eTypeXinFaInfo, CDBRoleXinFaDataTableManager);
        NEW_MGR(eTypeTripodFireInfo, CDBTripodFireTableManager);
        NEW_MGR(eTypeLevelPrize, CDBRoleLevelPrizeTableManager);
        NEW_MGR(eTypeYelloDiamond, CDBRoleYDTableManager);
        NEW_MGR(eTypeEventInfo,CDBRoleEventTableManager);
        NEW_MGR(eTypeBuyItemLimit,CDBRoleShopItemTableManager);
        NEW_MGR(eTypeDayTarget,CDBRoleDayTargetTableManager);
        NEW_MGR(eTypeAutoStore,CDBRoleAutoStoreTableManager);
        NEW_MGR(eTypeBattleArray,CDBRoleBattleArrayTableManager);
        NEW_MGR(eTypeFighterComination, CDBFighterCombinationTableManager);
        NEW_MGR(eTypeTH, CDBTreasureHuntTableManager);
        NEW_MGR(eTypeBeauty, CDBRoleBeautyTableManager);
        NEW_MGR(eTypeFightFormation, CDBRoleFightFormationTableManager);
        NEW_MGR(eTypeFightHero, CDBRoleFightHeroTableManager);
        NEW_MGR(eTypeShip, DBRoleShipTableManager);
        NEW_MGR(eTypeGuardEMei, CDBGuardEMeiTableManager);
        NEW_MGR(eTypeGemstone, CDBRoleGemstoneTableManager);
        NEW_MGR(eTypeShengLing, CDBRoleShengLingTableManager);
        NEW_MGR(eTypeShengLingPrize, CDBRoleShengLingPrizeTableManager);

        default:
            return NULL;
    }
    return NULL;
}

void TableManagerBaseForRole::DestroyManager(TableManagerBaseForRole* pManager)
{
    if (NULL != pManager)
    {
        delete pManager;
        pManager = NULL;
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

