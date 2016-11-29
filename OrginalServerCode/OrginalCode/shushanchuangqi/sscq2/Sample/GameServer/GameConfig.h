/********************************************************************
//	Game Server Source File.
//	File name:	Config.h
//	Created:	2011/05/30	10:00
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

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#pragma once
#include "Config.h"
#include "Script/GameScript.h"
#ifdef _WIN32
class CGameServerDlg;
#endif
#ifndef DEFAULT_GAME_SVR
#define DEFAULT_GAME_SVR 1
#endif
#ifndef DEFAULT_MAP
#define DEFAULT_MAP 1
#endif


class CNetMgr;
class TiXmlElement;

enum EDBInitType
{
    eDBInitNone = 0,
    eDBInitGUID,            // GUID
    eDBInitNewGuildBattle,  // 新帮派战
    eDBInitMax
};
typedef vector<std::string> TVecString;
class CGameConfig : public CConfig
{
	friend class CRequestHandler;
public:
	static CGameConfig& Instance();
	CGameConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr),_bAllConnect(false) { }

	//virtual void OnAllEstablished() override;
	void OnDBInited();
	void OnCenterInited();

    CGameScript& GetScript() { return _oScript; }
// 检测某个地图是否应在该GameServer上
    bool CheckMapInServer(UINT32 dwMapId);
    virtual bool InitServerConfig(TiXmlElement* pServer);

    void SetInited(EDBInitType eType);
    bool IsDBInited() const { return _bDBDataInited; }

    void ReloadTable(const TVecString& vecTable);
private:
	virtual bool InitServer() override;
	virtual void UnInitServer() override;
	//virtual void OnClose(ISocket& rSocket) override;
	bool InitGame();
	void UnInitGame();
    bool InitScript(int flag = 0);
private:
    CGameScript _oScript;
    map<UINT16, UINT8> _mapID2GameSvrIdx;

    set<EDBInitType> _setDBToBeInited;  // 需要预加载的数据
    bool _bDBDataInited;
    bool _bAllConnect;
};

#define Config CGameConfig::Instance()
#define SCRIPT Config.GetScript()

#endif // #ifndef GAME_CONFIG_H
