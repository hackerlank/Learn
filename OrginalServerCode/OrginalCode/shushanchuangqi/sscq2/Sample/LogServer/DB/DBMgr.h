/********************************************************************
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
*********************************************************************/

#pragma once
#include "BaseDBMgr.h"
#include "Singleton.h"
#include "LogDataDefine.h"
using namespace NLogDataDefine;
class CDBMgr : public CBaseDBMgr, public StaticSingleton<CDBMgr>
{
public:
	using StaticSingleton::Instance;
	CDBMgr() : _wYear(0), _wMonth(0) { }
	bool Init();
	virtual bool InitDataBase(mysqlpp::Query& query) override;
	const string& GetTimeStr();
	void CheckData();
public://writeLOG
    void WriteDgnLogToDB(const SDgnLog &rDgn);
    void WriteRegisterLogToDB(const SRegisterLog &rReg);
    void WriteLoginLogToDB(const SLoginLog &rReg);
    void WriteItemCoursesLogToDB(const SItemCoursesLog &rIC);
    void WriteMoneyCoursesLogToDB(const SMoneyCoursesLog &rMC);
    void WriteDujieLogToDB(const SDujieLog &rMC);
    void WriteFashionLogToDB(const SFashionLog &rMC);
    void WriteFighterLogToDB(const SFighterLog &rMC);
    void WriteHorseLogToDB(const SHorseLog &rMC);
    void WriteTrumpLogToDB(const STrumpLog &rMC);
    void WriteEquipLogToDB(const SEquipLog &rMC);
    void WriteGuildLogToDB(const SGuildLog &rMC);
    void UpdateGuildLogToDB(const SGuildLog &rMC);
    void WriteMailLogToDB(const SMailLog& rMail);
    void WritePetLogToDB(const SPetLog &rMC);
    void WriteBeautyLogToDB(const SBeautyLog &rMC);

    void WriteSendMoneyLogToDB(const SSendMoneyLog& rLog);
    void writeSendItemLogToDB(const SSendItemLog& rLog);
    void WriteMailOpLogToDB(const SMailOpLog& rLog);
    void WriteForbiddenLogToDB(const SForbiddenLog& rLog);
    void WriteForbiddenChatLogToDB(const SForbiddenChatLog& rLog);
    void WriteGlobalSendItemLogToDB(const SGlobalSendItemLog& rLog);
    void WriteQuesOptLogToDB(const SQuesOptLog& rLog);
    void WriteSendMailLogToDB(const SSendMailLog& rLog);
    void WriteVIPSendLogToDB(const SVIPSendLog& rLog);
    void WriteActivityOpenLogToDB(const SActivityOpenLog& rLog);
    void WriteDiscountItemLogToDB(const SDiscountItemLog& rLog);
    void WriteLevelChangeLogToDB(const SLevelChangeLog& rLog);
private:
   //	void ResetDataBase();
	
	UINT16 _wYear;
	UINT16 _wMonth;
	string _strData;
};
