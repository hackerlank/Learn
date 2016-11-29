/********************************************************************
//	Database Server Source File.
//	File name:	DBMgr.cpp
//	Created:	2011/06/03	15:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#include "stdafx.h"

bool CDBMgr::Init()
{
    if(!CBaseDBMgr::Init())
        return false;
    char Startsql[4096] = {0};
    string strStart = "createforstart.sh";
    CConfig* pConfig = CConfig::GetConfig();
    if(!pConfig)
    {
        LOG_CRI << "Config IS NULL";
        return false;
    }
    LOG_CRI << "DO createforstart.sh";
    snprintf(Startsql, sizeof(Startsql),
            "cd %s && if [ -f %s ]; then chmod +x %s && ./%s %s %s %s %u %s ; fi && cd -",
            pConfig->_strSqlDir.c_str(), strStart.c_str(), strStart.c_str(), strStart.c_str(),
            pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort, pConfig->_strDBName.c_str());
    int ret = system(Startsql);
    if (ret)
    {
        LOG_CRI << "Error execute sql script: " << Startsql << " result: " << ret;
        return false;
    }
    else
        LOG_INF << "Success execute sql script: " << Startsql << " result: " << ret;
    
    map<EQueryType, UINT8> mapType2Count;
    mapType2Count.insert(make_pair(eQueryNormal, 4));
    return CBaseDBMgr::Start(mapType2Count);
}

bool CDBMgr::InitDataBase(mysqlpp::Query& query)
{
#if 0 
    time_t tCurTime = time(NULL);
    tm tmCurTime;
    localtime_s(&tmCurTime, &tCurTime);
    _wYear = tmCurTime.tm_year;
    _wMonth = tmCurTime.tm_mon;
#endif
    CheckData();
    query << "SET NAMES UTF8;";
    query.execute();
    return true;
}

void CDBMgr::CheckData()
{   
    UINT16 wYear;
    UINT16 wMonth;
    time_t tCurTime = time(NULL);
    tm tmCurTime;
    localtime_s(&tmCurTime, &tCurTime);
    wYear = tmCurTime.tm_year+1900;
    wMonth = tmCurTime.tm_mon+1;
    if (wYear != _wYear || wMonth != _wMonth)
    {
        _wYear = wYear;
        _wMonth = wMonth;
        _strData.clear();
        //LOG_CRI << wYear <<":"<< wMonth;
        //ResetDataBase();
    }
}

const string& CDBMgr::GetTimeStr()
{
    if (_strData.empty())
    {
        char _szbuf[0x100];
        sprintf_s(_szbuf, "%04u%02u", _wYear , _wMonth );

        _strData = _szbuf;
    }

    return _strData;
}
#if 0
void CDBMgr::ResetDataBase()
{
    CConfig* pConfig = CConfig::GetConfig();
    try {
        mysqlpp::Connection con(NULL, pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort);
        {
            mysqlpp::NoExceptions ne(con);
            if(!con.select_db(pConfig->_strDBName))
            {
                // Database doesn't exist yet, so create and select it.
                if(!con.create_db(pConfig->_strDBName) || !con.select_db(pConfig->_strDBName))
                {
                    LOG_CRI << "Error creating DB: " << con.error();
                    return;
                }
            }
        }
        mysqlpp::Query query = con.query();
        // TODO: if have
        //NTable::InitTable(query);
    }
    catch(const mysqlpp::BadQuery& er)
    {
        // Handle any query errors
        LOG_CRI << "Query error: " << er.what();
        return;
    }
    catch(const mysqlpp::BadConversion& er)
    {
        // Handle bad conversions
        LOG_CRI << "Conversion error: " << er.what() <<
            "\tretrieved data size: " << er.retrieved <<
            ", actual size: " << er.actual_size;
        return;
    }
    catch(const mysqlpp::Exception& er)
    {
        // Catch-all for any other MySQL++ exceptions
        LOG_CRI << "Error: " << er.what();
        return;
    }
}
#endif

void CDBMgr::WriteDgnLogToDB(const SDgnLog &rDgn)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblDgnLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(qwDgnInsID, wDgnType, eOpType, qwUserID,LogTime) VALUES " << "(";
    sql << (mysqlpp::sql_bigint_unsigned)rDgn.qwDgnInsID;
    sql << "," << (mysqlpp::sql_smallint_unsigned)rDgn.wDgnType; 
    sql << "," << (mysqlpp::sql_tinyint_unsigned)rDgn.eOpType;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rDgn.qwUserID;
    sql << "," << "NOW()";
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteRegisterLogToDB(const SRegisterLog &rReg)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblRegisterLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, player_name, reg_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rReg.serverId;

    sql << "," << (mysqlpp::sql_bigint_unsigned)rReg.playerId; 
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rReg.playerName;
    sql << "," << (mysqlpp::sql_int_unsigned)time(NULL);
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteLoginLogToDB(const SLoginLog &rReg)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "REPLACE INTO tblLoginLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << " VAlUES (";
    sql << (mysqlpp::sql_int_unsigned)rReg.serverId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rReg.playerId; 
    sql << "," << (mysqlpp::sql_int_unsigned)rReg.loginTime;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rReg.loginIp;
    sql << "," << (mysqlpp::sql_int_unsigned)rReg.logoutTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteItemCoursesLogToDB(const SItemCoursesLog &rIC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblItemCoursesLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, strOpen_id, qwInst_id, item_id, item_num, from_to, from_toStr, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rIC.serverId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rIC.playerId; 
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rIC.strOpenId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rIC.qwInstId; 
    sql << "," << (mysqlpp::sql_int_unsigned)rIC.itemId;
    sql << "," << (mysqlpp::sql_int_unsigned)rIC.itemNum;
    sql << "," << (mysqlpp::sql_smallint_unsigned)rIC.fromto;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rIC.fromtoStr;
    sql << "," << (mysqlpp::sql_int_unsigned)rIC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteMoneyCoursesLogToDB(const SMoneyCoursesLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblMoneyCoursesLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, strOpen_id, money_id, money_num, total_num, from_to, from_toStr, happened_time, bIsFreeGold) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.serverId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.playerId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.strOpenId;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.moneyType;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.moneyNum;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.totalNum;
    sql << "," << (mysqlpp::sql_smallint_unsigned)rMC.fromto;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.fromtoStr;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.bIsFreeGold;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}
void CDBMgr::WriteDujieLogToDB(const SDujieLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblDujieLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, fighter_id, fighter_name, period_name, happened_time,fighter_exp) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwPlayerId;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wFighterId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sFighterName;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sPeriodName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << "," <<(mysqlpp::sql_int_unsigned)rMC.dwExp;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WritePetLogToDB(const SPetLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblPetLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, pet_name, opt_type, pet_level, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwPlayerId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byOpType;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteFashionLogToDB(const SFashionLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblFashionLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, fashion_id, fashion_name, fashion_level, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteFighterLogToDB(const SFighterLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblFighterLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, fighter_id, fighter_name, fighter_level, fighter_quality, opt_type, opt_detail, opt_result, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wFighterId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wLevel;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byQuality;
    sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.eOptType;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwType;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwResult;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteHorseLogToDB(const SHorseLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblHorseLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, horse_name, horse_id, horse_level, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwID;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteBeautyLogToDB(const SBeautyLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblBeautyLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, beauty_name, beauty_id, beauty_level, beauty_exp,happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wID;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwExp;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteTrumpLogToDB(const STrumpLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblTrumpLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, trump_name, trump_id, trump_skillid, trump_level,happened_time,trump_exp) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.wID;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwSkillId;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwExp;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteEquipLogToDB(const SEquipLog &rMC)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblEquipLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(server_id, player_id, equip_name, equip_id, equip_level, happened_time) VALUES " << "(";
    sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwUserId;
    sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwID;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwLevel;
    sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteGuildLogToDB(const SGuildLog &rMC)
{
    UINT8 byOptType = rMC.byOptType;
    if(byOptType == 1) //1表示插入操作，其余都是更新
    {
        mysqlpp::SQLStream sql(NULL);
        sql << "INSERT INTO tblGuildLog";
        sql << "(server_id, guild_id, guild_name, guild_level, member_count, guild_money, happened_time,tower_level, store_level";
        sql << ", hourse_level, guild_score" ;
        sql << ") VAlUES (";
        sql << (mysqlpp::sql_int_unsigned)rMC.dwServerId;
        sql << "," << (mysqlpp::sql_bigint_unsigned)rMC.qwGuildId;
        sql << "," << mysqlpp::quote << (mysqlpp::sql_char)rMC.sName;
        sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byLevel;
        sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwCount;
        sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwMoney;
        sql << "," << (mysqlpp::sql_int_unsigned)rMC.happenedTime;
        sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byTowerLvl;
        sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byStoreLvl;
        sql << "," << (mysqlpp::sql_tinyint_unsigned)rMC.byHourseLvl;
        sql << "," << (mysqlpp::sql_int_unsigned)rMC.dwScore;
        sql << ");";
        LOG_CRI << "sql = " <<sql.str();
        DoModifyQuery(sql.str(),NULL,NULL);
    }else
    {
        UpdateGuildLogToDB(rMC);
    }
}

void CDBMgr::UpdateGuildLogToDB(const SGuildLog &rMC)
{
    UINT8 byType = rMC.byOptParam; 
    mysqlpp::SQLStream sql(NULL);
    sql << "UPDATE tblGuildLog SET ";
    switch(byType)
    {
        case 1:  //修改人数
            {
                sql <<" member_count = ";
                sql << (mysqlpp::sql_int_unsigned)rMC.dwCount;
            }
            break;
        case 2: //加钱
            {
                sql <<" guild_money = ";
                sql << (mysqlpp::sql_int_unsigned)rMC.dwMoney;
            }
            break;
        case 3: //帮派积分
            {
                sql <<" guild_score = ";
                sql << (mysqlpp::sql_int_unsigned)rMC.dwScore;
            }
            break;
        case 4: //升级神谕塔
            {
                sql <<"tower_level =";
                sql << (mysqlpp::sql_tinyint_unsigned)rMC.byTowerLvl;
            }
            break;
        case 5: //升级仓库
            {
                sql <<"store_level =";
                sql << (mysqlpp::sql_tinyint_unsigned)rMC.byStoreLvl;
            }
            break;
        case 6: //升级hourse
            {
                sql <<"hourse_level =";
                sql << (mysqlpp::sql_tinyint_unsigned)rMC.byHourseLvl;
            }
            break;
        default:
            break;
    }
    sql <<" WHERE server_id = "<<(mysqlpp::sql_int_unsigned)rMC.dwServerId;
    sql <<" AND guild_id = "<<(mysqlpp::sql_bigint_unsigned)rMC.qwGuildId;
    DoModifyQuery(sql.str(),NULL,NULL);
}
void CDBMgr::WriteMailLogToDB(const SMailLog& rMail)
{
    if(rMail.byState == 0)//insert
    {
        mysqlpp::SQLStream sql(NULL); 
        sql <<"INSERT INTO tblmaillog(server_id,player_id,mail_id,mail_type,mail_title,mail_text,mail_item,mail_state,mail_rev_time,mail_del_time) VALUES (";
        sql << (mysqlpp::sql_int_unsigned)rMail.dwServerId;
        sql <<"," <<(mysqlpp::sql_bigint_unsigned)rMail.qwPlayerId;
        sql <<"," <<(mysqlpp::sql_bigint_unsigned)rMail.qwMailId;
        sql <<"," << (mysqlpp::sql_tinyint_unsigned)rMail.byType;
        sql <<"," << mysqlpp::quote << (mysqlpp::sql_char)rMail.strTitle;
        sql <<"," << mysqlpp::quote << (mysqlpp::sql_char)rMail.strText;
        sql <<"," << mysqlpp::quote << (mysqlpp::sql_char)rMail.strAttach;
        sql <<"," << (mysqlpp::sql_tinyint_unsigned)rMail.byState;
        sql <<"," << (mysqlpp::sql_int_unsigned)rMail.dwRevTime;
        sql <<"," << (mysqlpp::sql_int_unsigned)rMail.dwDelTime;
        sql << ");"; 
        DoModifyQuery(sql.str(),NULL,NULL);  
    }
    else if(rMail.byState == 1)//update mail_state,mail_rev_time
    {
        mysqlpp::SQLStream sql(NULL);
        sql << "UPDATE tblmaillog SET mail_state = ";
        sql <<(mysqlpp::sql_tinyint_unsigned)rMail.byState;
        sql << " , mail_rev_time = ";
        sql << (mysqlpp::sql_int_unsigned)rMail.dwRevTime;
        sql <<"  WHERE player_id = ";
        sql << (mysqlpp::sql_bigint_unsigned)rMail.qwPlayerId;
        sql <<" AND mail_id = ";
        sql <<(mysqlpp::sql_bigint_unsigned)rMail.qwMailId; 
        sql <<" ;";
        DoModifyQuery(sql.str(),NULL,NULL); 



    }
    else if(rMail.byState == 2 || rMail.byState== 3)//update mail_state,mail_del_time
    {
        mysqlpp::SQLStream sql(NULL);
        sql << "UPDATE tblmaillog SET mail_state = ";
        sql <<(mysqlpp::sql_tinyint_unsigned)rMail.byState;
        sql << " , mail_del_time = ";
        sql << (mysqlpp::sql_int_unsigned)rMail.dwDelTime;
        sql <<"  WHERE player_id = ";
        sql << (mysqlpp::sql_bigint_unsigned)rMail.qwPlayerId;
        sql <<" AND mail_id = ";
        sql <<(mysqlpp::sql_bigint_unsigned)rMail.qwMailId; 
        sql <<" ;";
        DoModifyQuery(sql.str(),NULL,NULL); 
    }
}
void CDBMgr::WriteSendMoneyLogToDB(const SSendMoneyLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblSendMoneyLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byMoneyType,";
    sql << "dwMoneyValue,";
    sql << "strReason,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName << ",";
    sql << (UINT16)rLog.byStatus << ",";
    sql << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byMoneyType;
    sql << "," << rLog.dwMoneyValue;
    sql << "," << rLog.strReason;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::writeSendItemLogToDB(const SSendItemLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblSendItemLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "strTitle,";
    sql << "strBody,";
    sql << "strItemList,";
    sql << "strReason,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.strTitle;
    sql << "," << rLog.strBody;
    sql << "," << rLog.strItemList;
    sql << "," << rLog.strReason;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}

void CDBMgr::WriteMailOpLogToDB(const SMailOpLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblMailOpLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byMailOpType,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byMailOpType;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteForbiddenLogToDB(const SForbiddenLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblForbiddenLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byOpType,";
    sql << "dwForbidTime,";
    sql << "strReason,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byOpType;
    sql << "," << rLog.dwForbidTime;
    sql << "," << rLog.strReason;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteForbiddenChatLogToDB(const SForbiddenChatLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblForbiddenChatLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byOpType,";
    sql << "dwForbidTime,";
    sql << "strReason,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byOpType;
    sql << "," << rLog.dwForbidTime;
    sql << "," << rLog.strReason;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteGlobalSendItemLogToDB(const SGlobalSendItemLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblGlobalSendItemLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "dwGold,";
    sql << "dwCoupon,";
    sql << "dwSliver,";
    sql << "dwHonor,";
    sql << "strItemList,";
    sql << "strReason,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.dwGold;
    sql << "," << rLog.dwCoupon;
    sql << "," << rLog.dwSliver;
    sql << "," << rLog.dwHonor;
    sql << "," << rLog.strItemList;
    sql << "," << rLog.strReason;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);
}
void CDBMgr::WriteQuesOptLogToDB(const SQuesOptLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblQuesOptLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byOpType,";
    sql << "wQuestType,";
    sql << "strQuestName,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byOpType;
    sql << "," << rLog.wQuestType;
    sql << "," << rLog.strQuestName;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteSendMailLogToDB(const SSendMailLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblSendMailLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "strTitel,";
    sql << "strBody,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.strTitel;
    sql << "," << rLog.strBody;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteVIPSendLogToDB(const SVIPSendLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblVIPSendLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "dwVIPLevel,";
    sql << "strBody,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.dwVIPLevel;
    sql << "," << rLog.strBody;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteActivityOpenLogToDB(const SActivityOpenLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblActivityOpenLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "strActivityName,";
    sql << "dwBeginTime,";
    sql << "dwEndTime,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.strActivityName;
    sql << "," << rLog.dwBeginTime;
    sql << "," << rLog.dwEndTime;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);

}
void CDBMgr::WriteDiscountItemLogToDB(const SDiscountItemLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblDiscountItemLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "dwBeginTime,";
    sql << "dwEndTime,";
    sql << "strItemList,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << rLog.dwBeginTime;
    sql << "," << rLog.dwEndTime;
    sql << "," << rLog.strItemList;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);


}
void CDBMgr::WriteLevelChangeLogToDB(const SLevelChangeLog& rLog)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "INSERT INTO tblLevelChangeLog_";
    sql << _wYear;
    sql << "_";
    sql << _wMonth;
    sql << "(strSendName,"; 
    sql << "byStatus,";
    sql << "dwServerId,";
    sql << "qwUserId,";
    sql << "byLevel,";
    sql << "dwOpTime)";
    sql << " VALUES " << "(";
    sql << rLog.strSendName;
    sql << "," << (UINT16)rLog.byStatus;
    sql << "," << rLog.dwServerId;
    sql << "," << rLog.qwUserId;
    sql << "," << (UINT16)rLog.byLevel;
    sql << "," << rLog.dwOpTime;
    sql << ");";
    DoModifyQuery(sql.str(),NULL,NULL);


}

