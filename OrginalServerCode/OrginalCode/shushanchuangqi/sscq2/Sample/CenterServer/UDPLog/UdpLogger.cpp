#include "stdafx.h"
#include "UdpLogger.h"
#include "UDPLog.h"

void CUdpLogger::LogMoneyChange(CUDPLog& rInfo, EOpType eType, UINT16 dwFromTo, INT32 dwChanged)
{
    /*
	if(dwChanged > 0 || eOpTypeGM == eType)
	{
		const char* pType = "free";
		const char* pszAction = "add";
		if(dwChanged < 0)
			pszAction = "sub";
		rInfo.UdpLog( pType, NumberToString(abs(dwChanged)).c_str(), NumberToString(dwOPID).c_str(), pszAction, "", "", "currency");
	}
	else if(dwChanged <= 0) //礼金消耗 dwChanged == 0
	{
		string id = NumberToString(_dwOPTypeID);
		string price = NumberToString(abs(dwChanged));
		rInfo.UdpLog( "add", "1", id.c_str(), price.c_str(), "0", "", "props", 1);
		rInfo.UdpLog( "sub", "1", id.c_str(), price.c_str(), "0", "", "props", 1);
	}
    */
    string id = "GN_" + NumberToString(dwFromTo);
    //功能货币改成1
    rInfo.UdpLog( "add", "1", id.c_str(), NumberToString(abs(dwChanged)).c_str(), "0", "", "props", 1);
    //rInfo.UdpLog( "add", "1", id.c_str(), "0", "0", "", "props", abs(dwChanged));
}

void CUdpLogger::LogItemChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice /*= 0*/ )
{
	if(nChanged > 0)
		LogAddItem(rInfo, eType, wTypeID, nChanged, dwPrice);
	else if(nChanged < 0)
		LogReduceItem(rInfo, eType, wTypeID, -nChanged, dwPrice);
}

void CUdpLogger::LogMailAttChange(CUDPLog& rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged)
{
	if(nChanged > 0)
		LogAddItem(rInfo, eType, wTypeID, nChanged);
	else if(nChanged < 0)
		LogReduceItem(rInfo, eType, wTypeID, -nChanged);
}

void CUdpLogger::LogAddItem(CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice /*= 0*/)
{
	//rInfo.UdpLog("add", "1", NumberToString(wTypeID).c_str(), NumberToString(dwPrice).c_str(), "0", "", "props", nChanged);
    char priceBuf[10] = { 0 };
    sprintf(priceBuf, "%.2f", dwPrice);
	rInfo.UdpLog("add", "1", NumberToString(wTypeID).c_str(), priceBuf, "0", "", "props", nChanged);
}

void CUdpLogger::LogReduceItem(CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice /*= 0*/)
{
	//rInfo.UdpLog("sub", "1", NumberToString(wTypeID).c_str(), NumberToString(dwPrice).c_str(), "0", "", "props", nChanged);
    char priceBuf[10] = { 0 };
    sprintf(priceBuf, "%.2f", dwPrice);
	rInfo.UdpLog("sub", "1", NumberToString(wTypeID).c_str(), priceBuf, "0", "", "props", nChanged);
}

void CShopUdpLogger::LogAddItem(CUDPLog &rInfo, EOpType eType, UINT16 wTypeID, INT32 nChanged, float dwPrice /*= 0*/)
{
	if(nChanged == 0)
		return;

	rInfo.UdpLog( "add", "1", NumberToString(wTypeID).c_str(), NumberToString(dwPrice / nChanged).c_str(), "0", "", "props", nChanged);
}
