#include "stdafx.h" 
#include "GuildLog.h"
#include "SysMsgDefine.h"

#include "Center2DBGuildC.h"

const char* g_strRank[] =
{
	"无效职位", // eMemberNone = 0,     //无效职位
	"成员", // eMemberNormal,       //成员
	"精英", // eMemberElite,        //精英
	"长老", // eMemberElder,        //长老
	"副帮主", // eMemberViceOwner,    //副帮主
	"帮主", // eMemberOwner,        //帮主
	"最高职位", // eMemberMax           //最高职位
};

const char* g_strBuilding[] =
{
	"无效建筑", // eBuildingNone = 0,   //无效建筑
	"神谕塔", // eBuildingOracle,     //神谕塔
	"仓库", // eBuildingDepot,      //仓库
	"剑阁", // eBuildingSword,      //剑阁
	"商店", // eBuildingStore,      //商店
	"血池", // eBuildingBlood,      //血池
	"最高建筑", // eBuildingMax         //最高建筑
};

const char* g_strWorship[] =
{
	"无效供奉类型", //  eWorshipNone = 0,   //无效供奉类型
	"鲜花供奉", //  eWorshipFlower,     //鲜花供奉
	"朱果供奉", //  eWorshipRedFruit,   //朱果供奉
	"蟠桃供奉", //  eWorshipPeach,      //蟠桃供奉
	"供奉类型最大值", //  eWorshipMax         //供奉类型最大值
};

CGuildLog::CGuildLog():
    _qwInstID(0), _wMsgID(0), _dwTime(0)
{
}

CGuildLog::~CGuildLog()
{
}

bool CGuildLog::GetAllInfo(SGuildLogInfo& rInfo) const
{
    rInfo.qwInstID  = _qwInstID;
    rInfo.eType     = GetType();
    rInfo.wMsgID    = _wMsgID;
    rInfo.vecParam  = _vecParam;
    rInfo.vecString = _vecString;
    rInfo.dwTime    = _dwTime;
    return true;
}

bool CGuildLog::InitFromDB(const SGuildLogInfo& rInfo)
{
    _qwInstID  = rInfo.qwInstID ;
    _wMsgID    = rInfo.wMsgID   ;
    _vecParam  = rInfo.vecParam ;
    _vecString = rInfo.vecString;
    _dwTime    = rInfo.dwTime   ;
    return true;
}

UINT16 CGuildLog::GetID() const
{
    return _wMsgID;
}

bool CGuildLog::FormatParam(UINT16 wMsgID, TVecINT64& rvecParam, TVecString& rvecString)
{
    _qwInstID       = 0;
    _wMsgID         = wMsgID;
    _vecParam       = rvecParam;
    _vecString      = rvecString;
    _dwTime         = time(NULL);
    return true;
}

void CGuildLog::Update2DB(CGuildLogPtr pGuildLog, EDataChange eChangeType, UINT64 qwGuildID)
{
    SGuildLogInfo sLogInfo;
    if (pGuildLog)
    {
        pGuildLog->GetAllInfo(sLogInfo);
        sLogInfo.qwGuildID = qwGuildID;
    }
    string strData;
    COutArchive iar(strData);
    iar << sLogInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(qwGuildID, eGDTLog, eChangeType, strData);
}

CGuildMemberLog:: CGuildMemberLog()
{
}

CGuildMemberLog::~CGuildMemberLog()
{
}

ELogType CGuildMemberLog::GetType() const
{
    return eLogMember;
}

bool CGuildMemberLog::FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName)
{
    bool bVaild = false;
    switch (wMsgID)
    {
        case eMsgGuildJoin:
        case eMsgGuildQuit:
            bVaild = true;
            break;
        default:
            break;
    }
    if (bVaild)
    {
        TVecINT64 vecParam;
        TVecString vecString;
        ostringstream strTmp;
        strTmp << static_cast<UINT32>(byQuality);
        vecString.push_back(strTmp.str());
        vecString.push_back(strName);
        CGuildLog::FormatParam(wMsgID, vecParam, vecString);
    }
    return bVaild;
}

bool CGuildMemberLog::FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName, UINT8 byQuality2, string strName2)
{
    bool bVaild = false;
    switch (wMsgID)
    {
        case eMsgGuildKick:
        case eMsgGuildGiveOwner:
        case eMsgGuildImpeachSuccess:
        case eMsgGuildImpeachFailed:
            bVaild = true;
            break;
        default:
            break;
    }
    if (bVaild)
    {
        TVecINT64 vecParam;
        TVecString vecString;
        ostringstream strTmp;
        strTmp << static_cast<UINT32>(byQuality);
        vecString.push_back(strTmp.str());
        vecString.push_back(strName);
        strTmp.str("");
        strTmp << static_cast<UINT32>(byQuality2);
        vecString.push_back(strTmp.str());
        vecString.push_back(strName2);
        CGuildLog::FormatParam(wMsgID, vecParam, vecString);
    }
    return bVaild;
}

bool CGuildMemberLog::FormatParam(UINT16 wMsgID, UINT8 byQuality, string strName, UINT8 byQuality2, string strName2, EMemberRank eRank)
{
    bool bVaild = false;
    switch (wMsgID)
    {
        case eMsgGuildImprove:
        case eMsgGuildDemote:
            bVaild = true;
            break;
        default:
            break;
    }
    if (bVaild)
    {
        TVecINT64 vecParam;
        TVecString vecString;
        ostringstream strTmp;
        strTmp << static_cast<UINT32>(byQuality);
        vecString.push_back(strTmp.str());
        vecString.push_back(strName);
        strTmp.str("");
        strTmp << static_cast<UINT32>(byQuality2);
        vecString.push_back(strTmp.str());
        vecString.push_back(strName2);
        vecString.push_back(g_strRank[static_cast<INT32>(eRank)]);
        CGuildLog::FormatParam(wMsgID, vecParam, vecString);
    }
    return bVaild;
}


CGuildBuildingLog:: CGuildBuildingLog()
{
}

CGuildBuildingLog::~CGuildBuildingLog()
{
}

ELogType CGuildBuildingLog::GetType() const
{
    return eLogBuilding;
}

bool CGuildBuildingLog::FormatParam(EBuildingType eType, UINT16 wLevel)
{
    TVecINT64 vecParam;
    TVecString vecString;
    vecString.push_back(g_strBuilding[static_cast<INT32>(eType)]);
    ostringstream strTmp;
    strTmp << wLevel;
    vecString.push_back(strTmp.str());
    CGuildLog::FormatParam(eMsgGuildBuildingUpgrade, vecParam, vecString);
    return true;
}

CGuildDonateLog::CGuildDonateLog()
{
}

CGuildDonateLog::~CGuildDonateLog()
{
}

ELogType CGuildDonateLog::GetType() const
{
    return eLogDonate;
}

bool CGuildDonateLog::FormatParam(UINT8 byQuality, string strName, UINT32 dwMoney)
{
    TVecINT64 vecParam;
    TVecString vecString;
    ostringstream strTmp;
    strTmp << static_cast<UINT32>(byQuality);
    vecString.push_back(strTmp.str());
    vecString.push_back(strName);
    strTmp.str("");
    strTmp << dwMoney;
    vecString.push_back(strTmp.str());
    CGuildLog::FormatParam(eMsgGuildDonate, vecParam, vecString);
    return true;
}

CGuildStatueLog::CGuildStatueLog()
{
}

CGuildStatueLog::~CGuildStatueLog()
{
}

ELogType CGuildStatueLog::GetType() const
{
    return eLogStatue;
}

bool CGuildStatueLog::FormatParam(UINT8 byQuality, string strName, EWorshipType eType, UINT32 dwMoney)
{
    TVecINT64 vecParam;
    TVecString vecString;
    ostringstream strTmp;
    strTmp << static_cast<UINT32>(byQuality);
    vecString.push_back(strTmp.str());
    vecString.push_back(strName);
    strTmp.str("");
    strTmp << static_cast<INT32>(eType);
    vecString.push_back(g_strWorship[static_cast<INT32>(eType)]);
    strTmp.str("");
    strTmp << static_cast<INT32>(dwMoney);
    vecString.push_back(strTmp.str());
    CGuildLog::FormatParam(eMsgGuildStatue, vecParam, vecString);
    return true;
}
