#pragma once
#include "Game2CenterLog.h"

using namespace NGame2CenterLog;
class CUDPLog;

class CUdpLogger : public enable_shared_from_this<CUdpLogger>
{
public:
	CUdpLogger(UINT32 OPTypeID) : _dwOPTypeID(OPTypeID) { }
	virtual ~CUdpLogger() { }

	virtual void LogMoneyChange(CUDPLog& rInfo, EOpType eType, UINT16 dwFromTo, INT32 dwChanged);
	virtual void LogItemChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice = 0.0f);
	virtual void LogMailAttChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged);

	virtual void LogAddItem( CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice = 0.0f);
	virtual void LogReduceItem( CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice = 0.0f);

	UINT32 _dwOPTypeID;
};

class CNoneUdpLogger : public CUdpLogger
{
public:
	CNoneUdpLogger() : CUdpLogger(0) { }
	~CNoneUdpLogger() { }
	virtual void LogMoneyChange(CUDPLog& rInfo, EOpType eType, UINT16 dwFromTo, INT32 dwChanged) { }
	virtual void LogItemChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice = 0.0f) { }
	virtual void LogMailAttChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged ) { }
};

class CShopUdpLogger : public CUdpLogger
{
public:
	CShopUdpLogger() : CUdpLogger(0) { }
	~CShopUdpLogger() { }
	virtual void LogMoneyChange(CUDPLog& rInfo, EOpType eType, UINT16 dwFromTo, INT32 dwChanged) { }
	virtual void LogAddItem(CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice = 0.0f);
};
