
//	Database Server Source File.
//	File name:	DBMgr.h
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
/*********************************************************************/

#pragma once
#include "BaseDBMgr.h"
#include "DBConfig.h"
#include "Singleton.h"

class CDBMgr : public CBaseDBMgr, public StaticSingleton<CDBMgr>
{
public:
    using StaticSingleton::Instance;
    CDBMgr(){}
    virtual ~CDBMgr() {}
    bool Init();
    virtual bool InitDataBase(mysqlpp::Query& query) override;
    void InitData(mysqlpp::Query& query);
public:
    bool DoRoleModifyQuery(const string& strSQL,UINT8 byLine, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoRoleSelectQuery(const string& strSQL, UINT8 byLine, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);
   public:
    UINT8 GetFreeLine();
    void  FreeLine(UINT8 byLine);
  private:
    EQueryType GetTypeByLine(UINT8 byLine); 
    UINT32 _arrayRoleLine[eQuerySaveMax-eQuerySave0];
 

};
