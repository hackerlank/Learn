/********************************************************************
//	Database Server Source File.
//	File name:	Config.cpp
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

#ifdef __GNUG__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "tinyxml.h"
#include "UtilFunc.h"
#include "ServerID.h"
#include "GlobalDefine.h"
#include "Directory.h"
#include "Random.h"
#include "Config.h"
#include "NetMgr.h"
#include "RTime.h"

bool SConfigInfo::GetDefaultAddress(const string& strHostName, string& strAddr)
{
    auto itHost = mapHost2TypeAddr.find(strHostName);
    if(itHost == mapHost2TypeAddr.end())
        return false;
    auto rMapType2Addr = itHost->second;
    auto itType = rMapType2Addr.find(1);
    if(itType == rMapType2Addr.end())
        return false;
    strAddr = itType->second;
    return true;
}

bool SConfigInfo::GetAllAddress(const string& strHostName, map<UINT8, string>& mapType2Addr)
{
    auto itHost = mapHost2TypeAddr.find(strHostName);
    if(itHost == mapHost2TypeAddr.end())
        return false;
    mapType2Addr = itHost->second;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////

CConfig* CConfig::_pConfig;

bool CConfig::Init()
{
    CRandom::ResetSeed();

    if(!GetCurDirectory(_strCurDir))
        return false;

    _strConfigDir = _strCurDir + "Config/";
    _strDataDir = _strConfigDir + "GameData/";
    CreateDirectory(_strDataDir);

    if(!InitConfig())
        return false;

    if(!InitLog())
        return false;

    if(!_rNetMgr.Init())
    {
        LOG_CRI << "CNetMgr::Init fails!";
        return false;
    }

    if(!InitServer())
    {
        LOG_CRI << "InitServer fails!";
        return false;
    }

    if(!StartListen())
    {
        LOG_CRI << "StartListen fails!";
        return false;
    }

    _rNetMgr.FinishInit();
    _bInited = true;
    return true;
}

void CConfig::UnInit()
{
    _bInited = false;
    g_oLog.Stop();
    _rNetMgr.Shutdown();
    UnInitServer();
}

bool CConfig::ParseConfigInfo(TiXmlElement* pElemRoot, SConfigInfo& rConfigInfo)
{
    TiXmlElement* pElemHostList = pElemRoot->FirstChildElement("HostList");
    if(pElemHostList == NULL)
        return false;
    TiXmlElement* pElemHost = pElemHostList->FirstChildElement("Host");
    while(pElemHost != NULL)
    {
        string strHostName;
        const char* pName = pElemHost->Attribute("name");
        if(pName != NULL)
            strHostName = pName;
        else
            strHostName = DEFAULT_HOST_NAME;
        TiXmlElement* pElemAddress = pElemHost->FirstChildElement("Address");
        while(pElemAddress != NULL)
        {
            UINT8 byType = 1;
            const char* pType = pElemAddress->Attribute("type");
            if(pType != NULL)
                byType = (UINT8)atoi(pType);
            const char* pIP = pElemAddress->Attribute("ip");
            if(pIP == NULL)
                return false;
            rConfigInfo.mapHost2TypeAddr[strHostName][byType] = pIP;
            pElemAddress = pElemAddress->NextSiblingElement("Address");
        }
        pElemHost = pElemHost->NextSiblingElement("Host");
    }

    TiXmlElement* pElemControlClient = pElemRoot->FirstChildElement("ControlClient");
    if(pElemControlClient != NULL)
    {
        TiXmlElement* pElemAddress = pElemControlClient->FirstChildElement("Address");
        while(pElemAddress != NULL)
        {
            const char* pIP = pElemAddress->Attribute("ip");
            if(pIP == NULL)
                return false;
            _setControlAddr.insert(pIP);
            pElemAddress = pElemAddress->NextSiblingElement("Address");
        }
    }

    TiXmlElement* pElemAddrMap = pElemRoot->FirstChildElement("AddrMap");
    if(pElemAddrMap != NULL)
    {
        TiXmlElement* pElemInAddr = pElemAddrMap->FirstChildElement("InAddr");
        while(pElemInAddr != NULL)
        {
            const char* pIP = pElemInAddr->Attribute("ip");
            if(pIP == NULL)
                return false;
            _setInAddr.insert(inet_addr(pIP));
            pElemInAddr = pElemInAddr->NextSiblingElement("InAddr");
        }
        TiXmlElement* pElemOutAddr = pElemAddrMap->FirstChildElement("OutAddr");
        while(pElemOutAddr != NULL)
        {
            const char* pIP = pElemOutAddr->Attribute("ip");
            if(pIP == NULL)
                return false;
            const char* pMap = pElemOutAddr->Attribute("map");
            if(pMap == NULL)
                return false;
            _mapOutAddr.insert(make_pair(pIP, pMap));
            pElemOutAddr = pElemOutAddr->NextSiblingElement("OutAddr");
        }
    }

    TiXmlElement* pElemServerGroup = pElemRoot->FirstChildElement("ServerGroup");
    if(pElemServerGroup == NULL)
        return false;

    const char* pGroup = pElemServerGroup->Attribute("group");
    if(pGroup == NULL)
        return false;
    rConfigInfo.wGroup = (UINT16)atoi(pGroup);

    const char* pPortBase = pElemServerGroup->Attribute("portbase");
    if(pPortBase == NULL)
        return false;
    UINT16 wPortBase = (UINT16)atoi(pPortBase);

    const char* pKey = pElemServerGroup->Attribute("key");
    if(pKey == NULL)
        return false;
    rConfigInfo.dwKey = (UINT32)atoi(pKey);

    TiXmlElement* pElemSvr = pElemServerGroup->FirstChildElement();
    while(pElemSvr != NULL)
    {
        const char* pSvrName = pElemSvr->Value();
        if(pSvrName == NULL)
            return false;
        EHostType eHostType = GetServerType(pSvrName);
        if(eHostType == eHostNone)
            return false;

        UINT8 byIndex = 1;
        const char* pIndex = pElemSvr->Attribute("idx");
        if(pIndex != NULL)
        {
            byIndex = (UINT8)atoi(pIndex);
            if(byIndex == 0)
                return false;
        }

        SServerConfig& rSvrConf = rConfigInfo.mapSvr2Conf[eHostType][byIndex];
        rSvrConf.byIndex = byIndex;
        const char* pListen = pElemSvr->Attribute("listen");
        if(pListen == NULL)
            return false;
        rSvrConf.wListenPort = wPortBase + (UINT16)atoi(pListen);

        const char* pDBName = pElemSvr->Attribute("db");
        if(pDBName!= NULL)
            rSvrConf.strDBName = pDBName;

        const char* pHostName = pElemSvr->Attribute("host");
        if(pHostName!= NULL)
            rSvrConf.strHostName = pHostName;
        else
            rSvrConf.strHostName = DEFAULT_HOST_NAME;

        const char* pShowClient = pElemSvr->Attribute("showclient");
        if(pShowClient!= NULL && strcmp(pShowClient, "true") == 0)
            rSvrConf.bShowClient = true;

        const char* pConsole = pElemSvr->Attribute("console");
        if(pConsole != NULL && strcmp(pConsole, "true") == 0)
            rSvrConf.bOpenConsole = true;

        pElemSvr = pElemSvr->NextSiblingElement();
    }

    TiXmlElement* pElemConnect = pElemRoot->FirstChildElement("Connect");
    if(pElemConnect == NULL)
        return false;

    pElemSvr = pElemConnect->FirstChildElement();
    while(pElemSvr != NULL)
    {
        const char* pSvrName = pElemSvr->Value();
        if(pSvrName == NULL)
            return false;
        EHostType eHostType = GetServerType(pSvrName);
        if(eHostType == eHostNone)
            return false;

        TiXmlElement* pElemTarget = pElemSvr->FirstChildElement();
        while(pElemTarget != NULL)
        {
            const char* pTargetName = pElemTarget->Value();
            if(pTargetName == NULL)
                return false;
            EHostType eTargetType = GetServerType(pTargetName);
            if(eTargetType == eHostNone)
                return false;
            rConfigInfo.mapSvrConnect.insert(make_pair(eHostType, eTargetType));
            rConfigInfo.mapSvrListen.insert(make_pair(eTargetType, eHostType));
            pElemTarget = pElemTarget->NextSiblingElement();
        }
        pElemSvr = pElemSvr->NextSiblingElement();
    }

    TiXmlElement* pElemDatabaseList = pElemRoot->FirstChildElement("DatabaseList");
    if(pElemDatabaseList == NULL)
        return false;

    TiXmlElement* pElemDataBase = pElemDatabaseList->FirstChildElement("Database");
    while(pElemDataBase != NULL)
    {
        const char* pName = pElemDataBase->Attribute("name");
        if(pName == NULL)
            return false;

        SDataBase oDataBase;
        const char* pIP = pElemDataBase->Attribute("ip");
        if(pIP == NULL)
            return false;
        oDataBase.strAddr = pIP;

        const char* pPort = pElemDataBase->Attribute("port");
        if(pPort == NULL)
            return false;
        oDataBase.wPort = (UINT16)atoi(pPort);
        if(oDataBase.wPort == 0)
            return false;

        const char* pDB = pElemDataBase->Attribute("db");
        if(pDB == NULL)
            return false;
        oDataBase.strName = pDB;

        const char* pUser = pElemDataBase->Attribute("user");
        if(pUser == NULL)
            return false;
        oDataBase.strUser = pUser;

        const char* pPasswd = pElemDataBase->Attribute("passwd");
        if(pPasswd == NULL)
            return false;
        oDataBase.strPassword = pPasswd;

        const char* pPath = pElemDataBase->Attribute("sqldir");
        if(pPath == NULL)
            return false;
        oDataBase.strSqlDir = pPath;

        const char* pInit = pElemDataBase->Attribute("init");
        if(pPath == NULL)
            return false;
        oDataBase.strSqlInit = pInit;

        const char* pOnce = pElemDataBase->Attribute("once");
        if(pOnce == NULL)
            return false;
        oDataBase.strSqlOnce = pOnce;

        rConfigInfo.mapName2DataBase.insert(make_pair(pName, oDataBase));
        pElemDataBase = pElemDataBase->NextSiblingElement("Database");
    }

    {
        TiXmlElement* pScript = pElemRoot->FirstChildElement("Script");
        if(pScript == NULL)
            return false;

        const char* pScripts = pScript->Attribute("scripts");
        if(pScripts == NULL)
            return false;
        _strScripts = pScripts;

        const char* pMain = pScript->Attribute("main");
        if(pMain == NULL)
            return false;
        _strScriptMain = pMain;
    }

    if (!InitServerConfig(pElemRoot))
        return false;

    return true;
}

bool CConfig::ParseConfig(const string& strConfFile, SConfigInfo& rConfigInfo)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strConfFile.c_str(), TIXML_ENCODING_UTF8))
        return false;

    TiXmlElement* pElemRoot = doc.RootElement();
    if(pElemRoot == NULL)
        return false;

    if(!ParseConfigInfo(pElemRoot, rConfigInfo))
        return false;

    _wGroup = rConfigInfo.wGroup;
#ifdef _WIN32
    if(_pServerDlg != NULL)
        _pServerDlg->ShowGroupID(_wGroup);
#endif

    _dwGroupKey = rConfigInfo.dwKey;

    TiXmlElement* pElemLog = pElemRoot->FirstChildElement("Log");
    if(pElemLog == NULL)
        return false;

#ifdef _WIN32
    const char* pPath = pElemLog->Attribute("windows");
    if(pPath == NULL)
        return false;
    _strLogDir = pPath;
    _strLogDir += "\\" + _strSvrName;
#else
    const char* pPath = pElemLog->Attribute("linux");
    if(pPath == NULL)
        return false;
    _strLogDir = pPath;
    _strLogDir += "/" + _strSvrName;
#endif

    const char* pConsole = pElemLog->Attribute("console");
    if(pConsole != NULL && strcmp(pConsole, "true") == 0)
        _bOpenConsole = true;

    TiXmlElement* pElemGameLog = pElemRoot->FirstChildElement("GameLog");
    if(pElemGameLog != NULL)
    {
#ifdef _WIN32
        pPath = pElemGameLog->Attribute("windows");
        if(pPath == NULL)
            return false;
        _strGameLogDir = pPath;
        _strGameLogDir += "\\" + _strSvrName;
#else
        pPath = pElemGameLog->Attribute("linux");
        if(pPath == NULL)
            return false;
        _strGameLogDir = pPath;
        _strGameLogDir += "/" + _strSvrName;
#endif
        const char* pSaveDB = pElemGameLog->Attribute("db");
        if(pSaveDB != NULL && strcmp(pSaveDB, "true") == 0)
            _bLogSaveDB = true;
    }

    TiXmlElement* pElemPipe = pElemRoot->FirstChildElement("Pipe");
    if(pElemPipe == NULL)
        return false;
    const char* pPipePath = pElemPipe->Attribute("path");
    if(pPipePath == NULL)
        return false;
    _strPipeDir = pPipePath;

    TiXmlElement* pElemGM = pElemRoot->FirstChildElement("GM");
    if(pElemGM == NULL)
        return false;
    const char* pOpen = pElemGM->Attribute("open");
    if(pOpen != NULL && strcmp(pOpen, "true") == 0)
        _bAllIsGM = true;

    TiXmlElement* pElemBorn = pElemRoot->FirstChildElement("Born");
    if(pElemBorn == NULL)
        return false;
    const char* pDgn = pElemBorn->Attribute("dgn");
    if(pDgn != NULL)
        _wBornDgnID = (UINT16)atoi(pDgn);
    const char* pIndex = pElemBorn->Attribute("idx");
    if(pIndex != NULL)
        SplitToNumber(pIndex, "-", _vecBornIdx);

    TiXmlElement* pElemUserData = pElemRoot->FirstChildElement("UserData");
    if(pElemUserData == NULL)
        return false;
    const char* pVersion = pElemUserData->Attribute("version");
    if(pVersion != NULL)
        _wUsrDataVersion = (UINT16)atoi(pVersion);

    TiXmlElement* pElemPlatForm = pElemRoot->FirstChildElement("PlatForm");
    if(pElemPlatForm != NULL)
    {
        const char* pName = pElemPlatForm->Attribute("name");
        if(pName == NULL)
            return false;
        _strPlatFormName = pName;
        const char* pID = pElemPlatForm->Attribute("id");
        if(pID == NULL)
            return false;
        _wPlatFormID = (UINT16)atoi(pID);
    }
    else
    {
        LOG_CRI << "ServerConfig.xml has no PlatForm config!";
    }
    TiXmlElement* pElemBattle = pElemRoot->FirstChildElement("Battle");
    if(pElemBattle != NULL)
    {
        const char* pBattleReportDir = pElemBattle->Attribute("BattleReportDir");
        if(pBattleReportDir != NULL)
        {
            _strBattleReportDir = string(pBattleReportDir);
        }
        else
        {
            LOG_CRI <<"ServerConfig.xml has no BattleReportDir";
            return false;
        }
    }
    else
    {
        LOG_CRI <<"ServerConfig.xml has no BattleReportDir";
        return false;
    }
    TiXmlElement* pCrypt = pElemRoot->FirstChildElement("Crypt");
    if(pCrypt == NULL)
    {
        LOG_CRI << "Need Crypt";
        return false;
    }
    const char* pKey1 = pCrypt->Attribute("key1");
    const char* pKey2 = pCrypt->Attribute("key2");
    if(pKey1 == NULL || pKey2 == NULL)
    {
        LOG_CRI << "Need Crypt key1 key2";
        return false;
    }
    _strLoginKey1 = pKey1;
    _strLoginKey2 = pKey2;
    TiXmlElement* pRepeatTask = pElemRoot->FirstChildElement("RepeatTask");
    if(pRepeatTask != NULL)
    {
        const char* pTask = pRepeatTask->Attribute("type");
        if(pTask != NULL)
        {
            vector<UINT8> vecTask;
            SplitToNumber(pTask, ",", vecTask);
            for(size_t sz = 0; sz != vecTask.size(); sz++)
            {
                _setRepeatTask.insert(vecTask[sz]);
            }
        }
    }
    TiXmlElement* pOpenServer = pElemRoot->FirstChildElement("OpenServer");
    if (!pOpenServer)
    {
        LOG_CRI << "Need OpenServer Time!";
        return false;
    }
    const char* pYear  = pOpenServer->Attribute("Year");
    const char* pMonth = pOpenServer->Attribute("Month");
    const char* pDay   = pOpenServer->Attribute("Day");
    if(!pYear || !pMonth || !pDay)
    {
        LOG_CRI << "Need OpenServer Time! Year Month Day NULL";
        return false;
    }
    else
    {
        UINT32 dwYear  = (UINT32)atoi(pYear);
        UINT32 dwMonth = (UINT32)atoi(pMonth);
        UINT32 dwDay   = (UINT32)atoi(pDay);
        if (dwYear < 2015 || !dwMonth || dwMonth > 12 || !dwDay || dwDay > 31)
        {
            LOG_CRI << "OpenServer Time Error! Year:" << dwYear << " Month:" << dwMonth << " Day:" << dwDay;
            return false;
        }
        _dwOpenServerTime = Time::MkTime(dwYear, dwMonth, dwDay);
    }

    /********** 充值相关内容 begin **********/
    TiXmlElement* pElemTokenServer = pElemRoot->FirstChildElement("TokenServer");
    if(pElemTokenServer == NULL)
    {
        LOG_CRI << "Need Set TokenServer IP and Port !";
        return false;
    }
    TiXmlElement* pToken = pElemTokenServer->FirstChildElement("Address");
    while(pToken != NULL)
    {
        const char* pIP   = pToken->Attribute("ip");
        const char* pPort = pToken->Attribute("port");
        STokenServer oTokenServer;
        if(pIP != NULL && pPort != NULL)
        {
            oTokenServer.strAddr = pIP;
            oTokenServer.wPort   = (UINT16)atoi(pPort);
            _vecTokenServer.push_back(oTokenServer);
        }
        pToken = pToken->NextSiblingElement("Address");
    }
    TiXmlElement* pRecharge = pElemRoot->FirstChildElement("Recharge");
    if(pRecharge == NULL)
    {
        LOG_CRI << "Need Set Recharge url !";
        return false;
    }
    const char* pUrl = pRecharge->Attribute("url");
    if (pUrl != NULL)
        _strRechargeUrl = pUrl;
    /********** 充值相关内容 end **********/

    return true;
}

bool CConfig::ParseCrossConfig(const string& strConfFile, SConfigInfo& rConfigInfo)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strConfFile.c_str(), TIXML_ENCODING_UTF8))
        return false;

    TiXmlElement* pElemRoot = doc.RootElement();
    if(pElemRoot == NULL)
        return false;

    if(!ParseConfigInfo(pElemRoot, rConfigInfo))
        return false;

    _wCrossGroup = rConfigInfo.wGroup;
    _dwCrossGroupKey = rConfigInfo.dwKey;
    return true;
}

bool CConfig::InitConfig()
{
#if 0
    string strFolder;
    if(!GetCurDirectory(strFolder, false))
        return false;

    _byIndex = 1;
    auto it = find_if(strFolder.begin(), strFolder.end(), [](char c){ return ::isdigit(c); });
    if(it != strFolder.end())
    {
        string strNumber(it, strFolder.end());
        _byIndex = (UINT8)atoi(strNumber.c_str());
        if(_byIndex == 0)
            return false;
        _strSvrName.assign(strFolder.begin(), it);
    }
    else
    {
        _strSvrName = strFolder;
    }
#else
    string strFile;
    if(!GetCurFileName(strFile))  //For : GameServer*D.1
        return false;

    _byIndex = 1;
    auto it = find_if(strFile.begin(), strFile.end(), [](char c){ return ::isdigit(c); });
    if(it != strFile.end())
    {
        auto dotit = find_if(strFile.begin(), strFile.end(), [](char c){ return c == '.'; });
        if (dotit == strFile.end() || (dotit != strFile.end() && dotit > it))
        {
            string strNumber(it, strFile.end());
            _byIndex = (UINT8)atoi(strNumber.c_str());
            if(_byIndex == 0)
                return false;
        }
    }
    _strSvrName = strFile;
#endif
#ifdef _WIN32
    if(_pServerDlg != NULL)
        _pServerDlg->ShowGameIndex(_byIndex);
#endif
    _eSvrType = GetServerType(_strSvrName.c_str());
    if(_eSvrType == eHostNone)
    {
        cerr << "Unknown Server Folder: " << _strSvrName << endl;
        return false;
    }
    _strShortName = GetServerShortName(_eSvrType);
    _bIsCrossServer = false;
    unique_ptr<SConfigInfo> pCrossInfo;
    string strConfFile = _strConfigDir + "ServerConfig.xml";
    if(FileExists(strConfFile))
    {
        if(!ParseConfig(strConfFile, _oConfigInfo))
        {
            cerr << "ParseConfig fails! File: " << strConfFile << endl;
            return false;
        }
    }
    else
    {
        _bIsCrossServer = true;
    }

    string strCrossFile = _strConfigDir + "CrossConfig.xml";
    if(FileExists(strCrossFile))
    {
        if(_bIsCrossServer)
        {
            if(!ParseConfig(strCrossFile, _oConfigInfo))
            {
                cerr << "ParseConfig fails! File: " << strCrossFile << endl;
                return false;
            }
            _wCrossGroup = _wGroup;
            _dwCrossGroupKey = _dwGroupKey;
        }
        else
        {
            pCrossInfo.reset(new SConfigInfo);
            if(pCrossInfo == NULL)
                return false;
            if(!ParseCrossConfig(strCrossFile, *pCrossInfo))
            {
                cerr << "ParseCrossConfig fails! File: " << strCrossFile << endl;
                return false;
            }
        }
    }
    else if(_bIsCrossServer)
    {
        LOG_CRI << "Can't find CrossConfig.xml!";
        return false;
    }

    for(auto itCon = _oConfigInfo.mapSvrConnect.lower_bound(_eSvrType), itUB = _oConfigInfo.mapSvrConnect.upper_bound(_eSvrType); itCon != itUB; ++itCon)
    {
        EHostType ePeerType = itCon->second;
        auto itSvr = _oConfigInfo.mapSvr2Conf.find(ePeerType);
        if(itSvr == _oConfigInfo.mapSvr2Conf.end())
            return false;
        map<UINT8, SServerConfig>& rMapConfig = itSvr->second;
        for(auto itConf = rMapConfig.begin(); itConf != rMapConfig.end(); ++itConf)
        {
            SServerConfig& rSvrConf = itConf->second;
            string strAddr;
            if(!_oConfigInfo.GetDefaultAddress(rSvrConf.strHostName, strAddr))
                return false;
            UINT32 dwSvrID = ::GetServerID(_wGroup, ePeerType, rSvrConf.byIndex);
            SConnect conn =	{ strAddr, rSvrConf.wListenPort, eStateClosed };
            _mapID2Conn.insert(make_pair(dwSvrID, conn)); //和谁建立了连接
        }
    }
    if(pCrossInfo != NULL)
    {
        for(auto itCon = pCrossInfo->mapSvrConnect.lower_bound(_eSvrType), itUB = pCrossInfo->mapSvrConnect.upper_bound(_eSvrType); itCon != itUB; ++itCon)
        {
            EHostType eHostType = itCon->first;
            EHostType ePeerType = itCon->second;
            auto itSvr = pCrossInfo->mapSvr2Conf.find(eHostType);
            if(itSvr != pCrossInfo->mapSvr2Conf.end())
                continue;
            itSvr = pCrossInfo->mapSvr2Conf.find(ePeerType);
            if(itSvr == pCrossInfo->mapSvr2Conf.end())
                return false;
            map<UINT8, SServerConfig>& rMapConfig = itSvr->second;
            for(auto itConf = rMapConfig.begin(); itConf != rMapConfig.end(); ++itConf)
            {
                SServerConfig& rSvrConf = itConf->second;
                string strAddr;
                if(!pCrossInfo->GetDefaultAddress(rSvrConf.strHostName, strAddr))
                    return false;
                UINT32 dwSvrID = ::GetServerID(pCrossInfo->wGroup, ePeerType, rSvrConf.byIndex);
                SConnect conn =	{ strAddr, rSvrConf.wListenPort, eStateClosed };
                _mapID2Conn.insert(make_pair(dwSvrID, conn));
            }
        }
        auto it = pCrossInfo->mapSvr2Conf.find(eHostGame);
        if(it != pCrossInfo->mapSvr2Conf.end())
            _byCrossGameSvrCount = (UINT8)it->second.size();
    }

    for(auto itListen = _oConfigInfo.mapSvrListen.lower_bound(_eSvrType), itUB = _oConfigInfo.mapSvrListen.upper_bound(_eSvrType); itListen != itUB; ++itListen)
    {
        EHostType ePeerType = itListen->second; //监听的谁的连接
        if(_bIsCrossServer)
        {
            _mapValidAddr.insert(make_pair(ePeerType, ""));
            continue;
        }
        auto itSvr = _oConfigInfo.mapSvr2Conf.find(ePeerType);
        if(itSvr == _oConfigInfo.mapSvr2Conf.end())
            return false;
        map<UINT8, SServerConfig>& rMapConfig = itSvr->second;
        set<string> setAddr;
        for(auto itConf = rMapConfig.begin(); itConf != rMapConfig.end(); ++itConf)
        {
            SServerConfig& rSvrConf = itConf->second;
            string strAddr;
            if(!_oConfigInfo.GetDefaultAddress(rSvrConf.strHostName, strAddr))
                return false;
            UINT32 dwSvrID = ::GetServerID(_wGroup, ePeerType, rSvrConf.byIndex);
            SAccept acc = { strAddr, 0, eStateClosed };
            _mapID2Acc.insert(make_pair(dwSvrID, acc)); 
            setAddr.insert(strAddr);
        }
        for(auto itAddr = setAddr.begin(); itAddr != setAddr.end(); ++itAddr)
            _mapValidAddr.insert(make_pair(ePeerType, *itAddr));//谁和自己建立了连接 

    }

    auto itSvr = _oConfigInfo.mapSvr2Conf.find(_eSvrType);
    if(itSvr == _oConfigInfo.mapSvr2Conf.end())
        return false;
    map<UINT8, SServerConfig>& rMapConfig = itSvr->second;
    _byCount = (UINT8)rMapConfig.size();
    auto itIndex = rMapConfig.find(_byIndex);
    if(itIndex == rMapConfig.end())
        return false;
    SServerConfig& rSvrConfig = itIndex->second;
    vector<string> vecAddr;
    NetInterface::GetLocalAddress(vecAddr);
    string strAddr;
    if(!_oConfigInfo.GetDefaultAddress(rSvrConfig.strHostName, strAddr))
        return false;
    switch(_eSvrType)
    {
        case eHostLogin:
        case eHostGate:
            if(!_oConfigInfo.GetAllAddress(rSvrConfig.strHostName, _mapType2Addr))
                return false;
            for(auto itType = _mapType2Addr.begin(); itType != _mapType2Addr.end(); ++itType)
            {
                UINT8 byType = itType->first;
                string& strAddr = itType->second;
                if(byType != 0)
                    _mapAddr2Type.insert(make_pair(inet_addr(strAddr.c_str()), byType));
            }
            break;
        case eHostGame:
            if(!_oConfigInfo.GetAllAddress(rSvrConfig.strHostName, _mapType2Addr))
                return false;
            if(!_vecBornIdx.empty() && _vecBornIdx.back() > _byCount)
                return false;
            break;
        case eHostCenter:
            if(!_oConfigInfo.GetAllAddress(rSvrConfig.strHostName, _mapType2Addr))
                return false;
            for(auto strAddr : _setControlAddr)
                _mapValidAddr.insert(make_pair(eHostControl, strAddr));
            break;
        default:
            break;
    }
    /*
       if(find_if(vecAddr.begin(), vecAddr.end(), [&strAddr](const string& strAddr_){ return strAddr_ == strAddr; }) == vecAddr.end())
       return false;
       */
    _wListenPort = rSvrConfig.wListenPort;
#ifdef _WIN32
    _pServerDlg->ShowListenPort(_wListenPort);
#endif
    _bShowClient = rSvrConfig.bShowClient;

    if(!rSvrConfig.strDBName.empty())
    {
        auto itName = _oConfigInfo.mapName2DataBase.find(rSvrConfig.strDBName);
        if(itName == _oConfigInfo.mapName2DataBase.end())
            return false;
        SDataBase& rDataBase = itName->second;
        _strSqlDir = rDataBase.strSqlDir;
        _strSqlInit = rDataBase.strSqlInit;
        _strSqlOnce = rDataBase.strSqlOnce;
        _strDBAddr = rDataBase.strAddr;
        _wDBPort = rDataBase.wPort;
        _strDBName = rDataBase.strName;
        _strDBUser = rDataBase.strUser;
        _strDBPassword = rDataBase.strPassword;
    }

    if(_bOpenConsole || rSvrConfig.bOpenConsole)
        g_oLog.OpenConsole();

    return true;
}

bool CConfig::StartListen()
{
    bool bIsClient = false;
    if(_eSvrType == eHostLogin || _eSvrType == eHostGate)
        bIsClient = true;
    if(!CNetMgr::GetNetMgr()->ListenOnPort(_wListenPort, LISTEN_BACKLOG, bIsClient))
        return false;
    return true;
}

bool CConfig::InitLog()
{
    if(!CreateDirectory(_strLogDir))
        return false;
    string strShortName = GetServerShortName(_eSvrType);
    if(_byIndex > 1)
        strShortName += NumberToString(_byIndex);
    if(!g_oLog.OpenLog(_strLogDir, strShortName))
        return false;
    g_oLog.SetSvrID(GetServerID());
    return g_oLog.Start();
}

void CConfig::Shutdown()
{
#ifdef _WIN32
    if(_pServerDlg != NULL)
        _pServerDlg->Close();
#else
    CConfig* pConfig = this;
    _rNetMgr.ExecUserLogic([pConfig]()->bool{
            CThread thrd;
            thrd.Start([pConfig](){
                pConfig->UnInit();
                cout << "Server: " + pConfig->_strSvrName + " exited successfully" << endl;
                exit(0);
                });
            return false;
            });
#endif
}

bool CConfig::TimerCheckInit()
{
    ConnectPeers();
    return true;
}

void CConfig::ConnectPeers()
{
    for(auto it = _mapID2Conn.begin(); it != _mapID2Conn.end(); ++it)
    {
        UINT32 dwSvrID = it->first;
        EHostType ePeerType = GetServerType(dwSvrID);
        SConnect& rConn = it->second;
        if(rConn.eState == eStateClosed)
        {
            if(CNetMgr::GetNetMgr()->Connect(rConn.strAddr.c_str(), rConn.wPort, dwSvrID, ePeerType))
                rConn.eState = eStateEstablishing;
        }
    }
}

bool CConfig::OnAccept(ISocket& rSocket)
{
    EHostType ePeerType = rSocket.GetPeerType();
    bool bValid = false;
    string strPeerAddr = rSocket.GetPeerAddrStr();
    if(rSocket.GetSessionKey() == _dwGroupKey)
    {
        bValid = true;
    }
    else
    {
        LOG_INF << "Peer SessionKey is Wrong: " << rSocket.GetSessionKey();
        for(auto it = _mapValidAddr.lower_bound(ePeerType), itUB = _mapValidAddr.upper_bound(ePeerType); it != itUB; ++it)
        {
            string& rStrAddr = it->second;
            if(rStrAddr == strPeerAddr)
            {
                bValid = true;
                break;
            }
        }
    }
    if(!bValid)
    {
        LOG_INF << "Peer address is not allowed: " << strPeerAddr;
        return false;
    }
    if(_bIsCrossServer || ePeerType == eHostControl)
    {
        SAccept oAcc = { rSocket.GetPeerAddrStr(), rSocket.GetPeerPort(), eStateEstablished };
        if(_mapID2Acc.insert(make_pair(rSocket.GetPeerID(), oAcc)).second)
        {
#ifdef _WIN32
            if(_pServerDlg != NULL)
                _pServerDlg->AddToList(rSocket);
#endif
            return true;
        }
        LOG_CRI << "Duplicate accept! PeerID: " << rSocket.GetPeerID() << ", Peer Type: " << GetServerName(rSocket.GetPeerType()) << ", PeerAddr: " << strPeerAddr;
        return false;
    }
    auto it = _mapID2Acc.find(rSocket.GetPeerID());
    if(it == _mapID2Acc.end())
    {
        LOG_CRI << "Can't find Server: " << GetServerInfo(rSocket.GetPeerID());
        return false;
    }
    SAccept& rAccept = it->second;
    if(rAccept.strAddr != rSocket.GetPeerAddrStr())
    {
        LOG_CRI << "Address is not equal! Peer Server: " << GetServerInfo(rSocket.GetPeerID());
        return false;
    }
    if(rAccept.eState == eStateEstablished)
    {
        LOG_CRI << "Peer Server has already been accepted: " << GetServerInfo(rSocket.GetPeerID());
        return false;
    }
    rAccept.wPort = rSocket.GetPeerPort();
    rAccept.eState = eStateEstablished;
#ifdef _WIN32
    if(_pServerDlg != NULL)
        _pServerDlg->AddToList(rSocket);
#endif
    if(IsAllEstablished())
        OnAllEstablished();
    return true;
}

void CConfig::OnConnect(ISocket& rSocket, bool bSucceed)
{
    UINT32 dwSvrID = rSocket.GetPeerID();
    auto it = _mapID2Conn.find(dwSvrID);
    if(it == _mapID2Conn.end())
    {
        LOG_CRI << "Can't find Server: " << GetServerInfo(dwSvrID);
        return;
    }
    SConnect& rConnect = it->second;
    if(bSucceed)
    {
        rConnect.eState = eStateEstablished;
#ifdef _WIN32
        if(bSucceed && _pServerDlg != NULL)
            _pServerDlg->AddToList(rSocket);
#endif
#ifdef _DEBUG
        LOG_CRI << "Connect succeed " << rSocket.GetPeerName() << ".";
#endif
    }
    else
    {
        rConnect.eState = eStateClosed;
    }
    if(IsAllEstablished())
        OnAllEstablished();
}

void CConfig::OnClose(ISocket& rSocket)
{
#ifdef _WIN32
    if(_pServerDlg != NULL)
        _pServerDlg->DelFromList(rSocket);
#endif
    EHostType ePeerType = rSocket.GetPeerType();
    UINT32 dwSvrID = rSocket.GetPeerID();
    if(_bIsCrossServer || ePeerType == eHostControl)
    {
        if(_mapID2Acc.erase(dwSvrID) < 1)
            LOG_CRI << "Can't find Server! PeerID: " << dwSvrID << ", Peer Type: " << GetServerName(rSocket.GetPeerType()) << ", PeerAddr: " << rSocket.GetPeerAddrStr();
        return;
    }
    UINT8 byCount = 0;
    auto itCon = _mapID2Conn.find(dwSvrID);
    if(itCon != _mapID2Conn.end())
    {
        SConnect& rCon = itCon->second;
        rCon.eState = eStateClosed;
        ++byCount;
    }
    auto itAcc = _mapID2Acc.find(dwSvrID);
    if(itAcc != _mapID2Acc.end())
    {
        SAccept& rAcc = itAcc->second;
        rAcc.eState = eStateClosed;
        ++byCount;
    }
    if(byCount > 1)
        LOG_CRI << "Connect and Accept the same Server: " << GetServerInfo(dwSvrID);
}

UINT32 CConfig::GetServerID() const
{
    return ::GetServerID(_wGroup, _eSvrType, _byIndex);
}

void CConfig::GetAllServerTypes(map<EHostType, bool>& mapSvrType)
{
    for(auto it = _mapValidAddr.begin(); it != _mapValidAddr.end(); ++it)
        mapSvrType.insert(make_pair(it->first, true));

    for(auto it = _mapID2Conn.begin(); it != _mapID2Conn.end(); ++it)
        mapSvrType.insert(make_pair(GetServerType(it->first), false));
}

UINT8 CConfig::GetAddrType(ULONG ulAddr)
{
    auto it = _mapAddr2Type.find(ulAddr);
    if(it != _mapAddr2Type.end())
        return it->second;
    return 0;
}

bool CConfig::GetAddrByType(UINT8 byType, string& strAddr)
{
    auto it = _mapType2Addr.find(byType);
    if(it == _mapType2Addr.end())
        return false;
    strAddr = it->second;
    return true;
}

bool CConfig::IsAllEstablished()
{
    for(auto it = _mapID2Conn.begin(); it != _mapID2Conn.end(); ++it)
    {
        SConnect& rConn = it->second;
        if(rConn.eState != eStateEstablished)
            return false;
    }
    for(auto it = _mapID2Acc.begin(); it != _mapID2Acc.end(); ++it)
    {
        SAccept& rAcc = it->second;
        if(rAcc.eState != eStateEstablished)
            return false;
    }
    return true;
}

bool CConfig::InitServerConfig(TiXmlElement* /*pServer*/)
{
    return true;
}

#ifdef _WIN32
void CConfig::SetServerDialog(IServerDlg* pServerDlg)
{
    _pServerDlg = pServerDlg;
}

void CConfig::ShowPlayerCount(UINT16 wCount)
{
    if(_pServerDlg != NULL)
        _pServerDlg->ShowClientCount(wCount);
}
#endif
bool CConfig::CheckTaskCanRepeat(UINT8 byType)
{
    if(_setRepeatTask.empty())
        return false ;
    return _setRepeatTask.find(byType) != _setRepeatTask.end();
}
