/********************************************************************
//	Center Server Source File.
//	File name:	Config.h
//	Created:	2011/06/06	10:00
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
#include "Config.h"
#ifdef _WIN32
class CCenterServerDlg;
#endif

class CNetMgr;
class TiXmlElement;

enum EDBInitType
{
    eDBInitNone = 0,
    eDBInitGUID,        // GUID
    eDBInitArena,       // 斗剑场
    eDBInitGuild,       // 帮派列表
    eDBInitGuildAll,    // 帮派列表
    eDBInitGameVar,     // 服务器全局设置
    eDBInitRank,        // 排行榜数据
    eDBInitAdore,       // 崇拜数据
    eDBUserIDAndName,   // UserIDAndName数据
    eDBNotice,          // 公告数据
    eDBPlatformParam,   // 平台参数
    eDBShip,            //金船信息
    eDBGuildExchangedItem, //帮派兑换物品信息
    eDBInitMax
};

#define DEFAULT_GAME_SVR 1
typedef vector<std::string> TVecString;
class CCenterConfig : public CConfig
{
    friend class CRequestHandler;
    public:
    static CCenterConfig& Instance();
    CCenterConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr), _bAllGameSvrInited(false), _bDBDataInited(false), _bLastInited(false) { }
    void OnDBInited();

    string GetServerName(const string& name);

    void SetInited(EDBInitType eType);
    bool IsDBInited() const { return _bDBDataInited; }
    bool IsSomeInited(EDBInitType eType) const;
    void ReloadTable(const TVecString& vecTable);
    UINT32 GetSvrID();
    bool AllServerIsReady();
    void CheckServerIsReady();
    void OnAllServerReady();
    private:
    virtual bool InitServer();
    virtual void UnInitServer();
    bool InitGame();
    void UnInitGame();
    bool InitGateSvrInfo();

    public:
    bool _bAllGameSvrInited;

    set<EDBInitType> _setDBToBeInited;  // 需要预加载的数据
    bool _bDBDataInited;
    bool _bLastInited;
};

#define Config CCenterConfig::Instance()
