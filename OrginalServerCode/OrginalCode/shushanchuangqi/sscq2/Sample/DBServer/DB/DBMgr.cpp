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
#include "DBEvent.h"

bool CDBMgr::Init()
{
    if(!CBaseDBMgr::Init())
        return false;
    map<EQueryType, UINT8> mapType2Count;
    mapType2Count.insert(make_pair(eQueryNormal, 2));
    for(int i = eQuerySave0;i < eQuerySaveMax ;i++)
    {
        mapType2Count.insert(make_pair(EQueryType(i), 1)); 
    }
    mapType2Count.insert(make_pair(eQueryMail, 1));
    mapType2Count.insert(make_pair(eQueryArena, 1));
    mapType2Count.insert(make_pair(eQueryGuild, 1));
    mapType2Count.insert(make_pair(eQueryRank, 1));
    mapType2Count.insert(make_pair(eQueryRecharge, 1));
    memset(_arrayRoleLine,0,sizeof(_arrayRoleLine));
    return CBaseDBMgr::Start(mapType2Count);
}

bool CDBMgr::InitDataBase(mysqlpp::Query& query)
{
    query << "SET NAMES UTF8;";
    query.execute();
    return true;
}


void CDBMgr::InitData(mysqlpp::Query& query)
{}
bool CDBMgr::DoRoleModifyQuery(const string& strSQL,UINT8 byLine, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{

    CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, NULL,fnOnSimpResult));
    if(pModifyDBEvt == NULL || byLine >= eQuerySaveMax-eQuerySave0 ) 
        return false; 
    LOG_INF << "by Line :"<< byLine;
    PushQueryEvt(GetTypeByLine(byLine), pModifyDBEvt);
    return true;
}

bool CDBMgr::DoRoleSelectQuery(const string& strSQL, UINT8 byLine, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
    CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, NULL,fnOnDataResult));
    if(pSelectDBEvt == NULL|| byLine >= eQuerySaveMax-eQuerySave0) 
        return false;   
    //LOG_INF << "by Line :"<< byLine;
    PushQueryEvt(GetTypeByLine(byLine), pSelectDBEvt); 
    return true;
}

UINT8 CDBMgr::GetFreeLine()
{
    UINT32 dwMinNum = _arrayRoleLine[0];
    UINT8  byFreeLine = 0;
    for (int i = 1; i < eQuerySaveMax-eQuerySave0 ;i++)
    {
        if(_arrayRoleLine[i] < dwMinNum)
        {
            dwMinNum = _arrayRoleLine[i];
            byFreeLine = i;
        }
    }
    _arrayRoleLine[byFreeLine]++;
    //LOG_CRI << "Use Line:" << byFreeLine;
    return byFreeLine;
}

void  CDBMgr::FreeLine(UINT8 byLine)
{
    if(byLine >= eQuerySaveMax-eQuerySave0 ||_arrayRoleLine[byLine] == 0)
    {
        LOG_CRI <<"ERR LINE";
        return ;
    }
    _arrayRoleLine[byLine]--;
}

EQueryType CDBMgr::GetTypeByLine(UINT8 byLine)
{
    if(byLine >= eQuerySaveMax-eQuerySave0)
    {
        return eQuerySave0;
    }
    return EQueryType(eQuerySave0+byLine);
}
