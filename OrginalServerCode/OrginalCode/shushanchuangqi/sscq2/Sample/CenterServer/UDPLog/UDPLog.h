#pragma once
#include "UdpLogger.h"

class CUser;
class CUserLogger;

class CUDPLog : public enable_shared_from_this<CUDPLog>
{
public:
	CUDPLog(UINT64 qwRoleID, CUserLogger& rLogger);
	~CUDPLog() { }
	DEF_NEW_DELETE(CUDPLog);
	void LogMsg_Login(const TVecString& vecStrInfo);
	void LogMsg_LoginOut(UINT32 dwTime);
	void LogMsg_Refer(const TVecString& vecStrInfo);
	void LogMsg_Props(EOpType eType, UINT16 wTypeID, INT32 dwChange, float dwPrice);
    void LogMsg_Pay(string strUdp1, string strUdp2, UINT32 dwGold);
	void LogMsg_Currency(EOpType eType, UINT16 wFromTo, INT32 dwChange);
	void LogMsg_Act(const string& strCategory, const string& strAction, UINT32 count = 1);
	void LogMsg_Att(const string& strCategory, const string& strOld, const string& strNew);
	void LogMsg_Guide(const string& strCategory, const string& strStep);

	void UdpLog( const char* str1, const char* str2, const char* str3, const char* str4,
		const char* str5, const char* str6, const char* type, UINT32 count = 1);
	CUserPtr GetUserPtr();
    CUserLogger& GetLogger() { return _rLogger; }
protected:
	UINT64 _qwRoleID;
	CUserLogger& _rLogger;
};

typedef std::map<UINT64, CUDPLogPtr> TMapID2UDPLog;
typedef std::map<EOpType, CUdpLoggerPtr> TMapType2UdpLogger;

class CUDPLogMgr
{
public:
	static bool Init();
	static void Destroy();
	static void DestroyUsrUDPLog(UINT64 qwUsrID);
	static CUserLogger* GetUserLogger(UINT64 qwUsrID);
	static CUDPLogPtr GetUDPLog(CUser& rUser);
	static ostringstream& Stream();
	static void UdpLog(const char* str1, const char* str2, const char* str3, const char* str4,
		const char* str5, const char* str6, const char* type, UINT32 count = 1);
	static CUdpLoggerPtr GetCUdpLogger(EOpType eType);
	static void TimerCheck(time_t tNow);
private:
	static TMapID2UDPLog _mapID2UDPLog;
	static ostringstream _oStream;
	static CUserLogger* _pGlobalLogger; //ser
	static TMapType2UdpLogger _mapUdpLogger;
};
