
#include "DBRoleBaseTable.h"

void DBRoleBaseTable::InitDataByStr(string& strData)
{
    CInArchive ar(strData);
    ar >> static_cast<RoleBaseInfo &>(*this);
}

bool DBRoleBaseTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    RoleBaseInfo newData;
    ar >> newData;

    DIFF(byLevel);
    DIFF(qwExp);
    if(!newData.strName.empty())
        DIFF(strName);
    else
        LOG_CRI<< "player name empty";
    DIFF(eCareer);
    DIFF(eSex);
    DIFF(wMapID);
    DIFFFLOAT(fX);
    DIFFFLOAT(fY);
    DIFF(byNation);
    DIFF(byGMLvl);
    DIFF(dwTotalRecharge);
    /*
       DIFF(dwLoginTime);
       DIFF(dwOfflineTime);
       DIFF(dwLockExpireTime);
       DIFF(dwForbExpireTime);
       */
    DIFF(dwGold);
    DIFF(dwFreeGold);
    DIFF(dwSilver);
    DIFF(dwCoupon);
    DIFF(dwSoul);
    DIFF(dwPrestige);
    DIFF(dwHonor);
    DIFF(dwPExp);
    DIFF(dwAction);
    DIFF(dwPoten);
    DIFF(dwReiki);
    DIFF(dwDemonSoul);
    DIFF(dwSoulAttack);
    DIFF(dwSoulHp);
    DIFF(dwSoulCritical);
    DIFF(dwSoulCounter);
    DIFF(dwSoulSpeed);
    DIFF(dwSoulDefence);
    DIFF(dwSoulHit);
    DIFF(dwSoulDodge);
    DIFF(dwBTPoint);
    DIFF(szOwnTitle);
    DIFF(szEquipTitle);
    DIFF(byDomain);
    DIFF(byDomainLvl);
    DIFF(byDisplayLvl);
    DIFF(byDomainYear);
    DIFF(szOpenId);
    DIFF(szOpenKey);
    DIFF(qwInvitedID);
    DIFF(byWallow);
    DIFF(qwDgnId);
    DIFF(dwDgnTypeID);
    DIFF(wDgnMapId);
    DIFFFLOAT(fDgnfX);
    DIFFFLOAT(fDgnfY);
    DIFF(dwPendSilver);
    DIFF(dwPendCoupon);
    DIFF(dwPendExp);
    DIFF(dwPendGold);
    DIFF(strSign);
    DIFF(wMood);
    DIFF(dwDemonTowerFloorID);
    DIFF(dwDemonTowerPrizeFloorID);
    DIFF(strGuide);
    DIFF(szIcon);
    DIFF(szIconDel);
    DIFF(szIconActive);
    DIFF(dwPackNextUnlockTime);
    DIFF(dwActivity);
    DIFF(dwStampHuang);
    DIFF(dwStampXuan);
    DIFF(dwStampDi);
    DIFF(dwStampTian);
    DIFF(dwStampXing);
    DIFF(dwStampYue);
    DIFF(dwStampDi2);
    DIFF(dwStampXian);
    DIFF(dwStampSheng);
    DIFF(dwStampFo);
    DIFF(dwLoveHeart);
    DIFF(dwBlueFairyFate);
    DIFF(dwPurpleFairyFate);
    DIFF(dwOrangeFairyFate);
    DIFF(dwDuJieFu);
    DIFF(wAchievementLevel);
    DIFF(dwAchievementAP);
    DIFF(wCollectLevel);
    DIFF(dwCollectAP);
    DIFF(qwSittingPlayer);
    DIFF(dwIndulgeKickTime);
    DIFF(byYDLevel);
    DIFF(dwCreateTime);
    DIFF(strCreateIP);
    DIFF(strLoginIP);
    DIFF(wLastSaveMapID);
    DIFF(fLastSaveX);
    DIFF(fLastSaveY);
    DIFF(szDgnStarAward);
    DIFF(dwLuckyCoupon);


    return !_setChanged.none();
}

void DBRoleBaseTable::Login()
{ 
    UPCOLSet(dwLoginTime);
    dwLoginTime = time(NULL);
    _eDBState = eInDBUpdate;
}

void  DBRoleBaseTable::LoginOff()
{
    UPCOLSet(dwOfflineTime);
    dwOfflineTime = time(NULL);
    _eDBState = eInDBUpdate;
}
void DBRoleBaseTable::Freeze(UINT32 dwTimer)//封号
{
    if(dwLockExpireTime == dwTimer)
        return ;
    UPCOLSet(dwLockExpireTime);
    dwLockExpireTime = dwTimer;
    _eDBState = eInDBUpdate;
}

void DBRoleBaseTable::ForbitChat(UINT32 dwTimer)//禁言
{
    if(dwForbExpireTime == dwTimer)
        return ;
    UPCOLSet(dwForbExpireTime);
    dwForbExpireTime = dwTimer;
    _eDBState = eInDBUpdate;
}

void DBRoleBaseTable::UpdateLoginIP(const string& strIP)
{
    if(strLoginIP == strIP)
        return;
    UPCOLSet(strLoginIP);
    strLoginIP = strIP;
    _eDBState = eInDBUpdate;
}

void DBRoleBaseTableManager::Login()
{
    _RoleData.Login();

}
void DBRoleBaseTableManager::LoginOff()
{
    _RoleData.LoginOff();
}
void DBRoleBaseTableManager::Freeze(UINT32 dwTimer)//封号
{
    _RoleData.Freeze(dwTimer);
}
void DBRoleBaseTableManager::ForbitChat(UINT32 dwTimer)//禁言
{
    _RoleData.ForbitChat(dwTimer);
}
UINT32 DBRoleBaseTableManager::GetFreezeTimer()
{
    return _RoleData.dwLockExpireTime;
}
UINT32 DBRoleBaseTableManager::GetForbitChatTimer()
{
    return _RoleData.dwForbExpireTime;
}

void DBRoleBaseTableManager::UpdateLoginIP(const string& strLoginIP)
{
    return _RoleData.UpdateLoginIP(strLoginIP);
}

bool DBRoleBaseTable::GetInsertSqlStr(string& sqlstr)
{
    // TODO: 这个地方考虑写入存储过程
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblroledata (qwRoleID, strName, byLevel, qwExp, eCareer,eSex, wMapId, fX, fY, dwCreateTime, strCreateIP, qwInvitedID) VALUES " << "(";
    sql << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)strName;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    sql << "," << (mysqlpp::sql_bigint_unsigned)qwExp;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)eCareer;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)eSex;
    sql << "," << (mysqlpp::sql_smallint_unsigned)wMapID; 
    sql << "," << (mysqlpp::sql_float)fX; 
    sql << "," << (mysqlpp::sql_float)fY;
    sql << "," << (mysqlpp::sql_int_unsigned)dwCreateTime; 
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)strCreateIP;
    sql << "," << (mysqlpp::sql_int_unsigned)qwInvitedID;
    sql << ");";

    sqlstr = sql.str();
    return true;
}

bool DBRoleBaseTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;

    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroledata SET";

    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_UBIGINT_SAME(qwExp);
    UPDATE_STRING_CHAR_SAME(strName);
    UPDATE_UTINYINT_SAME(eCareer);
    UPDATE_UTINYINT_SAME(eSex);
    UPDATE_USMALLINT_SAME(wMapID);
    UPDATE_FLOAT_SAME(fX);
    UPDATE_FLOAT_SAME(fY);
    UPDATE_UTINYINT_SAME(byNation);
    UPDATE_UTINYINT_SAME(byGMLvl);
    UPDATE_UINT_SAME(dwTotalRecharge);
    UPDATE_UINT_SAME(dwLoginTime);
    UPDATE_UINT_SAME(dwOfflineTime);
    UPDATE_UINT_SAME(dwLockExpireTime);
    UPDATE_UINT_SAME(dwForbExpireTime);
    UPDATE_UINT_SAME(dwGold);
    UPDATE_UINT_SAME(dwFreeGold);
    UPDATE_UINT_SAME(dwSilver);
    UPDATE_UINT_SAME(dwCoupon);
    UPDATE_UINT_SAME(dwSoul);
    UPDATE_UINT_SAME(dwPrestige);
    UPDATE_UINT_SAME(dwHonor);
    UPDATE_UINT_SAME(dwPExp);
    UPDATE_UINT_SAME(dwAction);
    UPDATE_UINT_SAME(dwPoten);
    UPDATE_UINT_SAME(dwReiki);
    UPDATE_UINT_SAME(dwDemonSoul);
    UPDATE_UINT_SAME(dwSoulAttack);
    UPDATE_UINT_SAME(dwSoulHp);
    UPDATE_UINT_SAME(dwSoulCritical);
    UPDATE_UINT_SAME(dwSoulCounter);
    UPDATE_UINT_SAME(dwSoulSpeed);
    UPDATE_UINT_SAME(dwSoulDefence);
    UPDATE_UINT_SAME(dwSoulHit);
    UPDATE_UINT_SAME(dwSoulDodge);
    UPDATE_UINT_SAME(dwBTPoint);
    UPDATE_STRING_CHAR_SAME(szOwnTitle);
    UPDATE_STRING_CHAR_SAME(szEquipTitle);
    UPDATE_UTINYINT_SAME(byDomain);
    UPDATE_UTINYINT_SAME(byDomainLvl);
    UPDATE_UTINYINT_SAME(byDisplayLvl);
    UPDATE_UTINYINT_SAME(byDomainYear);
    UPDATE_STRING_CHAR_SAME(szOpenId);
    UPDATE_STRING_CHAR_SAME(szOpenKey);
    UPDATE_UBIGINT_SAME(qwInvitedID);
    UPDATE_UTINYINT_SAME(byWallow);
    UPDATE_UBIGINT_SAME(qwDgnId);
    UPDATE_UINT_SAME(dwDgnTypeID);
    UPDATE_USMALLINT_SAME(wDgnMapId);
    UPDATE_FLOAT_SAME(fDgnfX);
    UPDATE_FLOAT_SAME(fDgnfY);
    UPDATE_UINT_SAME(dwPendSilver);
    UPDATE_UINT_SAME(dwPendCoupon);
    UPDATE_UINT_SAME(dwPendExp);
    UPDATE_UINT_SAME(dwPendGold);
    UPDATE_STRING_CHAR_SAME(strSign);
    UPDATE_USMALLINT_SAME(wMood);
    UPDATE_UINT_SAME(dwDemonTowerFloorID);
    UPDATE_UINT_SAME(dwDemonTowerPrizeFloorID);
    UPDATE_STRING_CHAR_SAME(strGuide);
    UPDATE_STRING_CHAR_SAME(szIcon);
    UPDATE_STRING_CHAR_SAME(szIconDel);
    UPDATE_STRING_CHAR_SAME(szIconActive);
    UPDATE_UINT_SAME(dwPackNextUnlockTime);
    UPDATE_UINT_SAME(dwActivity);
    UPDATE_UINT_SAME(dwStampHuang);
    UPDATE_UINT_SAME(dwStampXuan);
    UPDATE_UINT_SAME(dwStampDi);
    UPDATE_UINT_SAME(dwStampTian);
    UPDATE_UINT_SAME(dwStampXing);
    UPDATE_UINT_SAME(dwStampYue);
    UPDATE_UINT_SAME(dwStampDi2);
    UPDATE_UINT_SAME(dwStampXian);
    UPDATE_UINT_SAME(dwStampSheng);
    UPDATE_UINT_SAME(dwStampFo);
    UPDATE_UINT_SAME(dwLoveHeart);
    UPDATE_UINT_SAME(dwBlueFairyFate);
    UPDATE_UINT_SAME(dwPurpleFairyFate);
    UPDATE_UINT_SAME(dwOrangeFairyFate);
    UPDATE_UINT_SAME(dwDuJieFu);
    UPDATE_UINT_SAME(wAchievementLevel);
    UPDATE_UINT_SAME(dwAchievementAP);
    UPDATE_UINT_SAME(wCollectLevel);
    UPDATE_UINT_SAME(dwCollectAP);
    UPDATE_UBIGINT_SAME(qwSittingPlayer);
    UPDATE_UINT_SAME(dwIndulgeKickTime);
    UPDATE_UTINYINT_SAME(byYDLevel);
    UPDATE_UINT_SAME(dwCreateTime);
    UPDATE_STRING_CHAR_SAME(strCreateIP);
    UPDATE_STRING_CHAR_SAME(strLoginIP);
    UPDATE_USMALLINT_SAME(wLastSaveMapID);
    UPDATE_FLOAT_SAME(fLastSaveX);
    UPDATE_FLOAT_SAME(fLastSaveY);
    UPDATE_STRING_CHAR_SAME(szDgnStarAward);
    UPDATE_UINT_SAME(dwLuckyCoupon);



    ostr << " WHERE qwRoleID=" << _qwRoleID << ";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleBaseTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleBaseTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UTINYINT_SAME(byLevel);
    GET_UBIGINT_SAME(qwExp);
    GET_STRING_CHAR_SAME(strName);
    UINT8 byCareer;
    GET_UTINYINT(eCareer, byCareer);
    eCareer = static_cast<NProtoCommon::ECareerType>(byCareer);
    UINT8 bySex;
    GET_UTINYINT(eSex, bySex);
    eSex = static_cast<NProtoCommon::ESexType>(bySex);
    GET_USMALLINT_SAME(wMapID);
    GET_FLOAT_SAME(fX);
    GET_FLOAT_SAME(fY);
    GET_UTINYINT_SAME(byNation);
    GET_UTINYINT_SAME(byGMLvl);
    GET_UINT_SAME(dwTotalRecharge);
    GET_UINT_SAME(dwLoginTime);
    GET_UINT_SAME(dwOfflineTime);
    GET_UINT_SAME(dwLockExpireTime);
    GET_UINT_SAME(dwForbExpireTime);
    GET_UINT_SAME(dwGold);
    GET_UINT_SAME(dwFreeGold);
    GET_UINT_SAME(dwSilver);
    GET_UINT_SAME(dwCoupon);
    GET_UINT_SAME(dwSoul);
    GET_UINT_SAME(dwPrestige);
    GET_UINT_SAME(dwHonor);
    GET_UINT_SAME(dwPExp);
    GET_UINT_SAME(dwAction);
    GET_UINT_SAME(dwPoten);
    GET_UINT_SAME(dwReiki);
    GET_UINT_SAME(dwDemonSoul);
    GET_UINT_SAME(dwSoulAttack);
    GET_UINT_SAME(dwSoulHp);
    GET_UINT_SAME(dwSoulCritical);
    GET_UINT_SAME(dwSoulCounter);
    GET_UINT_SAME(dwSoulSpeed);
    GET_UINT_SAME(dwSoulDefence);
    GET_UINT_SAME(dwSoulHit);
    GET_UINT_SAME(dwSoulDodge);
    GET_UINT_SAME(dwBTPoint);
    GET_STRING_CHAR_SAME(szOwnTitle);
    GET_STRING_CHAR_SAME(szEquipTitle);
    GET_UTINYINT_SAME(byDomain);
    GET_UTINYINT_SAME(byDomainLvl);
    GET_UTINYINT_SAME(byDisplayLvl);
    GET_UTINYINT_SAME(byDomainYear);
    GET_STRING_CHAR_SAME(szOpenId);
    GET_STRING_CHAR_SAME(szOpenKey);
    GET_UBIGINT_SAME(qwInvitedID);
    GET_UTINYINT_SAME(byWallow);
    GET_UBIGINT_SAME(qwDgnId);
    GET_UINT_SAME(dwDgnTypeID);
    GET_USMALLINT_SAME(wDgnMapId);
    GET_FLOAT_SAME(fDgnfX);
    GET_FLOAT_SAME(fDgnfY);
    GET_UINT_SAME(dwPendSilver);
    GET_UINT_SAME(dwPendCoupon);
    GET_UINT_SAME(dwPendExp);
    GET_UINT_SAME(dwPendGold);
    GET_STRING_CHAR_SAME(strSign);
    GET_USMALLINT_SAME(wMood);
    GET_UINT_SAME(dwDemonTowerFloorID);
    GET_UINT_SAME(dwDemonTowerPrizeFloorID);
    GET_STRING_CHAR_SAME(strGuide);
    GET_STRING_CHAR_SAME(szIcon);
    GET_STRING_CHAR_SAME(szIconDel);
    GET_STRING_CHAR_SAME(szIconActive); 
    GET_UINT_SAME(dwPackNextUnlockTime);
    GET_UINT_SAME(dwActivity);
    GET_UINT_SAME(dwStampHuang);
    GET_UINT_SAME(dwStampXuan);
    GET_UINT_SAME(dwStampDi);
    GET_UINT_SAME(dwStampTian);
    GET_UINT_SAME(dwStampXing);
    GET_UINT_SAME(dwStampYue);
    GET_UINT_SAME(dwStampDi2);
    GET_UINT_SAME(dwStampXian);
    GET_UINT_SAME(dwStampSheng);
    GET_UINT_SAME(dwStampFo);
    GET_UINT_SAME(dwLoveHeart);
    GET_UINT_SAME(dwBlueFairyFate);
    GET_UINT_SAME(dwPurpleFairyFate);
    GET_UINT_SAME(dwOrangeFairyFate);
    GET_UINT_SAME(dwDuJieFu);
    GET_UINT_SAME(wAchievementLevel);
    GET_UINT_SAME(dwAchievementAP);
    GET_UINT_SAME(wCollectLevel);
    GET_UINT_SAME(dwCollectAP);
    GET_UBIGINT_SAME(qwSittingPlayer);
    GET_UINT_SAME(dwIndulgeKickTime)
        GET_UTINYINT_SAME(byYDLevel);
    GET_UINT_SAME(dwCreateTime);
    GET_STRING_CHAR_SAME(strCreateIP);
    GET_STRING_CHAR_SAME(strLoginIP);
    GET_USMALLINT_SAME(wLastSaveMapID);
    GET_FLOAT_SAME(fLastSaveX);
    GET_FLOAT_SAME(fLastSaveY);
    GET_STRING_CHAR_SAME(szDgnStarAward);  
    TableRowBase::InitDataByDBRow(rRow);
    GET_UINT_SAME(dwLuckyCoupon);
}

void DBRoleBaseTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "SELECT * FROM tblroledata WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroledata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0 && dataRes.size()==1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            _RoleData.InitDataByDBRow(rRow);;
            }
            queryfun(byRet,ncount);
            });
}

void  DBRoleBaseTableManager::Update(string& strData, bool bIsAdd)
{
    _RoleData.Update(strData, bIsAdd);
}

void DBRoleBaseTableManager::GetALLInfo(RoleDataInfo & rData)
{
    rData.stBaseInfo = static_cast<RoleBaseInfo &>(_RoleData);
}

void DBRoleBaseTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _RoleData.DumpToDB(_byLine,[fun,this](INT8 byRet) {
            fun(1,byRet == 0 ? 0:1);
            });
}

UINT32 DBRoleBaseTableManager::GetUpdataNum()
{
    return _RoleData.HasOP() ? 1:0;
}

