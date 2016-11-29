#include "stdafx.h"
#include "kingnet_analyzer.h"
#include "UDPLog.h"
#include "UserMgr.h"
#include "LogMgr.h"
#include "GuildUserMgr.h"
#include "Protocols.h"
//////////////////////////////////////////////////////////////////////////
//CUDPLog
CUDPLog::CUDPLog(UINT64 qwRoleID, CUserLogger& rLogger) :_qwRoleID(qwRoleID) , _rLogger(rLogger)
{
    CUserPtr pUser = GetUserPtr();
    if(pUser)
        _rLogger.SetUserIP(pUser->GetClientIP().c_str());
}

UINT8 GetQQLv( CUserPtr pUser)
{
    UINT8 byParams = 0;
    const SPlatformParam& rPlatformParam = pUser->GetCurPlatform();
    switch (rPlatformParam.byQQPtType)
    {
        case eQQPtTypeYellow: //黄钻平台
            {
                if(rPlatformParam.bySPType & (1 << ePBBitSuper) )
                    byParams = 60;
                else
                    byParams = 0;
            }
            break;
        case eQQPtTypeBlue: //蓝钻平台
            {
                if(rPlatformParam.bySPType & (1 << ePBBitSuper) )
                    byParams = 50;
                else
                    byParams = 10;
            }
            break;
        case eQQPtTypeRed://红钻/VIP平台
            break;
        default:
            return 0;
            break;
    }
    return rPlatformParam.byQQPtLv + byParams;
}
void CUDPLog::LogMsg_Login(const TVecString& vecStrInfo)
{
    CUserPtr pUser = GetUserPtr();
    if(NULL == pUser)
    {
        LOG_CRI << "UDPLog can not find User";
        return;
    }
    _rLogger.SetUserIP(pUser->GetClientIP().c_str());
    UdpLog(pUser->GetCustomPar1().c_str(), pUser->GetCustomPar2().c_str(), "", "", "", "0", "login");
    return;
    switch(vecStrInfo.size())
    {
        case 1:
            UdpLog(vecStrInfo[0].c_str(), "", "", "", "", "0", "login");
            break;
        case 2:
            UdpLog(vecStrInfo[0].c_str(), vecStrInfo[1].c_str(), "", "", "", "0", "login");
            break;
        default:
            UdpLog("", "", "", "", "", "0", "login");
            break;
    }
}

void CUDPLog::LogMsg_LoginOut(UINT32 dwTime)
{
    CUserPtr pUser = GetUserPtr();
    if(NULL == pUser)
    {
        LOG_CRI << "UDPLog can not find User";
        return;
    }
    UdpLog(pUser->GetCustomPar1().c_str(), pUser->GetCustomPar2().c_str(), "", "", "", NumberToString(dwTime - pUser->GetCurLoginTime()).c_str(), "login");
    //UdpLog("", "", "", "", "", NumberToString(dwTime - pUser->GetLoginTime()).c_str(), "login");
}

void CUDPLog::LogMsg_Refer(const TVecString& vecStrInfo)
{
    switch(vecStrInfo.size())
    {
        case 1:
            UdpLog(vecStrInfo[0].c_str(), "", "", "", "", "0", "refer");
            break;
        case 2:
            UdpLog(vecStrInfo[0].c_str(), vecStrInfo[1].c_str(), "", "", "", "0", "refer");
            break;
        default:
            UdpLog("", "", "", "", "", "0", "refer");
            break;
    }
}

void CUDPLog::LogMsg_Props(EOpType eType, UINT16 wTypeID, INT32 dwChange, float dwPrice)
{
    CUdpLoggerPtr pLogger = CUDPLogMgr::GetCUdpLogger(eType);
    pLogger->LogItemChange(*this, eType, wTypeID, dwChange, dwPrice);
}

void CUDPLog::LogMsg_Pay(string strUdp1, string strUdp2, UINT32 dwGold)
{
    //新充值进入账号的仙石
    UdpLog(strUdp1.c_str(), strUdp2.c_str(), NumberToString(dwGold).c_str(), "1"/*仙石ID*/, "", "pay", "pay");
}

void CUDPLog::LogMsg_Currency(EOpType eType, UINT16 wFromTo, INT32 dwChange)
{
    CUdpLoggerPtr pLogger = CUDPLogMgr::GetCUdpLogger(eType);
    pLogger->LogMoneyChange(*this, eType, wFromTo, dwChange);
}

void CUDPLog::LogMsg_Act(const string& strCategory, const string& strAction, UINT32 count)
{
    UdpLog(strCategory.c_str(), strAction.c_str(), "", "", "", "", "act", count);
}

void CUDPLog::LogMsg_Att(const string& strCategory, const string& strOld, const string& strNew)
{
    UdpLog(strCategory.c_str(), strOld.c_str(), strNew.c_str(), "", "", "", "att");
}

void CUDPLog::LogMsg_Guide(const string& strCategory, const string& strStep)
{
    UdpLog(strCategory.c_str(), strStep.c_str(), "", "", "", "", "guide");
}

void CUDPLog::UdpLog(const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* type, UINT32 count /* = 1 */)
{
    CUserPtr pUser = GetUserPtr();
    if(NULL == pUser)
    {
        LOG_CRI << "UDPLog can not find User";
        return;
    }

    ostringstream& ostr = CUDPLogMgr::Stream();
    ostr << pUser->GetOpenID() //ouid
        << "|" << pUser->GetUserID() //iuid
        << "|" //birth
        << "|" << (UINT32)pUser->GetSex()//gender
        << "|" //game_friend
        << "|" //form_friend
        << "|" << (UINT32)pUser->GetLevel() //mainrole_level
        << "|" //user_exp
        << "|" << pUser->GetGold()//moneycoin
        << "|" << pUser->GetCoupon()//giftcoin
        << "|" << pUser->GetGuildID()//addi1 帮派id
        << "|" //addi2
        << "|" << 0 //addi3
        << "|" << 0 //addi4
        << "|" << (UINT32)GetQQLv(pUser)//vip_level 
        << "|" //firstintime
        << "|" << Config._wGroup //version or servergroup
        << "|" //country
        << "|" << pUser->GetCurPlatform().byPtType//Config._strPlatFormName//gameform
        << "|" //is_test
        << "|" //email
        ;

    _rLogger.SetUserMsg(ostr.str().c_str());
    int32_t ret = _rLogger.LogMsg(str1, str2, str3, str4, str5, str6, type, count);

    std::ostringstream& ostrLog = CLogMgr::Instance().Stream();
    ostrLog << "Udplog return "<<ret<<":"
        << str1 << "|" << str2 << "|" << str3 << "|" << str4 << "|" << str5 << "|" << str6 << "|" 
        << type << "|" << count << "|" << ostr.str();

    //LOG_INF << ostrLog.str();
    CLogMgr::Instance().LogUdpInfo(ostrLog.str());

    if(CUser::bUdpTest)
    {
        pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(610,BuildStrVec(ostrLog.str())));
        
    }

}


//////////////////////////////////////////////////////////////////////////
//CUDPLogMgr
CUserLogger* CUDPLogMgr::_pGlobalLogger;
TMapID2UDPLog CUDPLogMgr::_mapID2UDPLog;
ostringstream CUDPLogMgr::_oStream;
TMapType2UdpLogger CUDPLogMgr::_mapUdpLogger;

bool CUDPLogMgr::Init()
{
    _pGlobalLogger = new CUserLogger(1);
    _mapUdpLogger.insert(make_pair(eOpTypeGM, CUdpLoggerPtr(new CUdpLogger(0))));
    _mapUdpLogger.insert(make_pair(eOpTypeItemChange, CUdpLoggerPtr(new CUdpLogger(1000000))));
    _mapUdpLogger.insert(make_pair(eOpTypeMoneyChange, CUdpLoggerPtr(new CUdpLogger(1000001))));

    /*
    _mapUdpLogger.insert(make_pair(eOpTypeMail, CUdpLoggerPtr(new CNoneUdpLogger)));
    _mapUdpLogger.insert(make_pair(eOpTypeShop, CUdpLoggerPtr(new CShopUdpLogger)));
       _mapUdpLogger.insert(make_pair(eOpTypeBuyVIP, CUdpLoggerPtr(new CUdpLogger(1000000))));//购买VIP
       _mapUdpLogger.insert(make_pair(eOpTypeBuyAction, CUdpLoggerPtr(new CUdpLogger(1000001))));//购买行动力
       _mapUdpLogger.insert(make_pair(eOpTypeClearCD, CUdpLoggerPtr(new CUdpLogger(1000002))));//清除游戏CD
       _mapUdpLogger.insert(make_pair(eOpTypeMine, CUdpLoggerPtr(new CUdpLogger(1000003))));//购买挖矿次数
       _mapUdpLogger.insert(make_pair(eOpTypeEquipRanLock, CUdpLoggerPtr(new CUdpLogger(1000004))));//洗练装备锁定属性
       _mapUdpLogger.insert(make_pair(eOpTypeFreshChurch, CUdpLoggerPtr(new CUdpLogger(1000005))));//刷新领主任务
       _mapUdpLogger.insert(make_pair(eOpTypeTemple, CUdpLoggerPtr(new CUdpLogger(1000006))));//刷新神殿
       _mapUdpLogger.insert(make_pair(eOpTypeTempleBuy, CUdpLoggerPtr(new CUdpLogger(1000007))));//神殿购买
       _mapUdpLogger.insert(make_pair(eOpTypeValhalla, CUdpLoggerPtr(new CUdpLogger(1000008))));//刷新英灵殿
       _mapUdpLogger.insert(make_pair(eOpTypeFreshCortege, CUdpLoggerPtr(new CUdpLogger(1000009))));//刷新扈从
       _mapUdpLogger.insert(make_pair(eOpTypeRanCortege, CUdpLoggerPtr(new CUdpLogger(1000010))));//扈从洗练
       _mapUdpLogger.insert(make_pair(eOpTypeDonateFamily, CUdpLoggerPtr(new CUdpLogger(1000011))));//家族捐献
       _mapUdpLogger.insert(make_pair(eOpTypeRanEquip, CUdpLoggerPtr(new CUdpLogger(1000012))));//装备洗练
       _mapUdpLogger.insert(make_pair(eOpTypeGiftBox, CUdpLoggerPtr(new CUdpLogger(1000013))));//礼包赠送
       _mapUdpLogger.insert(make_pair(eOpTypeAuctionBidFor, CUdpLoggerPtr(new CUdpLogger(1000014))));//拍卖行竞拍
       _mapUdpLogger.insert(make_pair(eOpTypeExpandStore, CUdpLoggerPtr(new CUdpLogger(1000015))));//扩充包裹
       _mapUdpLogger.insert(make_pair(eOpTypeTask, CUdpLoggerPtr(new CUdpLogger(1000016))));//任务奖励
       _mapUdpLogger.insert(make_pair(eOpTypeSweepCurse, CUdpLoggerPtr(new CUdpLogger(1000017))));//诅咒之塔扫荡加速
       _mapUdpLogger.insert(make_pair(eOpTypeSweepTraining, CUdpLoggerPtr(new CUdpLogger(1000018))));//试炼之塔加速
       _mapUdpLogger.insert(make_pair(eOpTypeChangeGuildName, CUdpLoggerPtr(new CUdpLogger(1000019))));//公会改名
       _mapUdpLogger.insert(make_pair(eOpTypeFamilyFightInspire, CUdpLoggerPtr(new CUdpLogger(1000020))));//家族战激励
       */
    string strPath = Config._strConfigDir + "UDPLog.xml";
    if(_analyzer.Init(strPath.c_str()) != S_OK)
    {
        LOG_CRI << "_analyzer.Init fails! Path: " << strPath;
        return false;
    }
    return true;
}

void CUDPLogMgr::Destroy()
{
    _mapID2UDPLog.clear();
    _analyzer.Destroy();
    if(NULL != _pGlobalLogger)
    {
        delete _pGlobalLogger;
        _pGlobalLogger = NULL;
    }
    _mapUdpLogger.clear();
}

void CUDPLogMgr::DestroyUsrUDPLog(UINT64 qwUsrID)
{
    _mapID2UDPLog.erase(qwUsrID);
    _analyzer.DestoryInstance(NumberToString(qwUsrID).c_str());
}

CUserLogger* CUDPLogMgr::GetUserLogger(UINT64 qwUsrID)
{
    return _analyzer.GetInstance(NumberToString(qwUsrID).c_str());
}

CUDPLogPtr CUDPLogMgr::GetUDPLog(CUser& rUser)
{
    UINT64 qwUsrID = rUser.GetUserID();
    auto it = _mapID2UDPLog.find(qwUsrID);
    if(it != _mapID2UDPLog.end())
    {
        if(it->second->GetUserPtr() == NULL)
        {
            _mapID2UDPLog.erase(qwUsrID);
        }
        else
        {
            return it->second;
        }
    }
    CUserLogger* pUserLogger = GetUserLogger(qwUsrID);
    if(NULL == pUserLogger)
        return NULL;

    CUDPLogPtr pUDPLog(new CUDPLog(qwUsrID, *pUserLogger));
    if(NULL == pUDPLog)
        return NULL;

    _mapID2UDPLog.insert(make_pair(qwUsrID, pUDPLog));
    return pUDPLog;
}

ostringstream& CUDPLogMgr::Stream()
{
    _oStream.clear();
    _oStream.str("");
    return _oStream;
}

void CUDPLogMgr::UdpLog(const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* type, UINT32 count)
{
    // 发送有关UDPlog的数据
    if(_pGlobalLogger != NULL)
    {
        int32_t ret = _pGlobalLogger->LogMsg(str1, str2, str3, str4, str5, str6, type, count);

        std::ostringstream& ostrLog = CLogMgr::Instance().Stream();
        ostrLog << "Udplog return "<< ret <<":"
            << str1 << "|" << str2 << "|" << str3 << "|" << str4 << "|" << str5 << "|" << str6 << "|" 
            << type << "|" << count << "|";

        LOG_INF << ostrLog.str();
        CLogMgr::Instance().LogUdpInfo(ostrLog.str());
    }
}

CUdpLoggerPtr CUDPLogMgr::GetCUdpLogger(EOpType eType)
{
    auto it = _mapUdpLogger.find(eType);
    if(it != _mapUdpLogger.end())
        return it->second;

    return NULL;
}

void CUDPLogMgr::TimerCheck(time_t tNow)
{
    UINT16 wCount = CUserMgr::GetActiveUserCount();
    CUDPLogMgr::UdpLog("pcu", NumberToString(Config._wGroup).c_str(), NumberToString((UINT32)tNow).c_str(), NumberToString(wCount).c_str(), "", "", "ser");
}

CUserPtr CUDPLog::GetUserPtr()
{
    return CUserMgr::GetUserByUserID(_qwRoleID);
}
