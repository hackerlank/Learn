/********************************************************************
//	Server Common Source File.
//	File name:	Config.h
//	Created:	2012/12/14	15:00
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
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "Interface.h"

using namespace std;

#define DEFAULT_HOST_NAME "default"

#ifdef _WIN32
class IServerDlg
{
public:
	virtual void AddToList(ISocket& rSocket) = 0;
	virtual void RefreshList() = 0;
	virtual void DelFromList(ISocket& rSocket) = 0;

	virtual void RefreshCount() = 0;
	virtual void ShowGameIndex(UINT8 byIndex) = 0;
	virtual void ShowListenPort(UINT16 wPort) = 0;
	virtual void ShowClientCount(UINT16 wCount) = 0;
	virtual void ShowGroupID(UINT16 wGroup) = 0;
};
#endif

//单个服务器配置
struct SServerConfig
{
	UINT8 byIndex;			//编号
	UINT16 wListenPort;		//监听端口
	string strDBName;		//使用的数据库引用名
	string strHostName;		//所在的物理机名
	bool bShowClient;		//是否显示客户端连接
	bool bOpenConsole;		//是否在控制台打印日志

	SServerConfig() : byIndex(0), wListenPort(0), bShowClient(false), bOpenConsole(false) { }
};

//数据库配置
struct SDataBase
{
	string strAddr;			//地址
	UINT16 wPort;			//端口
	string strName;			//数据库名
	string strUser;			//帐号
	string strPassword;		//密码
    string strSqlDir;       //数据库脚本目录
    string strSqlInit;      //数据库初始化脚本
    string strSqlOnce;      //数据库更新后只执行一次脚本

	SDataBase() : wPort(0) { }
};

struct SConfigInfo
{
	UINT16 wGroup; //服务器组编号
	UINT32 dwKey; //服务器组密码
	map<EHostType, map<UINT8, SServerConfig>> mapSvr2Conf;	//多个服务器的配置
	map<string, SDataBase> mapName2DataBase;				//多个数据库的配置
	multimap<EHostType, EHostType> mapSvrConnect;			//服务器发起连接的配置
	multimap<EHostType, EHostType> mapSvrListen;			//服务器的监听配置
	map<string, map<UINT8, string>> mapHost2TypeAddr;		//服务器地址类型配置

	SConfigInfo() : wGroup(0) { }
	bool GetDefaultAddress(const string& strHostName, string& strAddr);
	bool GetAllAddress(const string& strHostName, map<UINT8, string>& mapType2Addr);
};

class TiXmlElement;

class CNetMgr;

class CConfig
{
	friend class CRequestHandler;
public:
	bool Init();
	void UnInit();
	bool InitConfig();
	bool StartListen();
	bool InitLog();
	void Shutdown();

	virtual bool InitServer() { return true; }
	virtual void UnInitServer() { }
	virtual bool OnAccept(ISocket& rSocket);
	virtual void OnConnect(ISocket& rSocket, bool bSucceed);
	virtual void OnClose(ISocket& rSocket);
	virtual void OnAllEstablished() { }
	virtual void GetExtraInfo(string& strInfo) { }
	virtual void LoadUserData() { }
    virtual bool InitServerConfig(TiXmlElement* pServer);
	virtual void StoreUserData() { }
	virtual void CloseAllServer(UINT32 dwRemTime) { }

	bool ParseConfig(const string& strConfFile, SConfigInfo& rConfigInfo);
	bool TimerCheckInit();
	void ConnectPeers();
	UINT32 GetServerID() const;
	void GetAllServerTypes(map<EHostType, bool>& mapSvrType);
	UINT8 GetAddrType(ULONG ulAddr);
	bool GetAddrByType(UINT8 byType, string& strAddr);

	bool IsAllEstablished();

#ifdef _WIN32
	void SetServerDialog(IServerDlg* pServerDlg);
	void ShowPlayerCount(UINT16 wCount);
#endif

	static CConfig* GetConfig() { return _pConfig; }

protected:
	CConfig(CNetMgr& rNetMgr) : _eSvrType(eHostNone), _bInited(false), _bLogSaveDB(false), _wGroup(0), _byIndex(0),
		_byCount(0), _dwGroupKey(0), _wCrossGroup(0), _dwCrossGroupKey(0), _byCrossGameSvrCount(0), _wListenPort(0),
		_bShowClient(false), _bIsCrossServer(false), _wDBPort(0), _bOpenConsole(false), _bAllIsGM(false), _wBornDgnID(0),
		_wUsrDataVersion(0), _wPlatFormID(0), _dwCompressThreshold(0), _dwOpenServerTime(0), _rNetMgr(rNetMgr)
	{
#ifdef _WIN32
		_pServerDlg = NULL;
#endif
		_pConfig = this;
	}

	bool ParseConfigInfo(TiXmlElement* pElemRoot, SConfigInfo& rConfigInfo);
	bool ParseCrossConfig(const string& strConfFile, SConfigInfo& rConfigInfo);
 public:
    bool CheckTaskCanRepeat(UINT8 byType);
public:
	EHostType _eSvrType;	//服务器的主机类型
	string _strSvrName;		//服务器的名称
	string _strShortName;	//服务器的简写
	bool _bInited;			//服务器是否已初始化
	string _strCurDir;		//服务器可执行文件所在的目录
	string _strDataDir;		//数据文件保存的目录
	string _strConfigDir;	//配置文件所在的目录
	string _strLogDir;		//服务器日志保存的目录
	string _strGameLogDir;	//游戏日志保存的目录
	bool _bLogSaveDB;		//游戏日志是否保存在数据库中
	UINT16 _wGroup;			//服务器组号(区号)
	UINT8 _byIndex;			//本服务器在同类型服务器中的编号
	UINT8 _byCount;			//同类型服务器的总数
	UINT32 _dwGroupKey;		//组内连接的密码
	UINT16 _wCrossGroup;	//跨服服务器组号
	UINT32 _dwCrossGroupKey;	//夸父服务器连接密码
	UINT8 _byCrossGameSvrCount;		//跨服服务器GameServer数量

	UINT16 _wListenPort;	//监听端口
	bool _bShowClient;		//是否显示客户端连接
	bool _bIsCrossServer;	//是否为跨服服务器
	map<UINT8, string> _mapType2Addr;	//地址类型到字符串的映射
	map<ULONG, UINT8> _mapAddr2Type;	//地址数值到类型的映射

	string _strDBAddr;		//MySQL的地址
	UINT16 _wDBPort;		//MySQL的端口号
	string _strDBName;		//数据库的名称
	string _strDBUser;		//数据库的帐号
	string _strDBPassword;	//数据库的密码

	string _strPipeDir;		//服务器控制管道所在路径
	bool _bOpenConsole;		//是否将服务器日志输出到控制台
	bool _bAllIsGM;			//是否所有用户都是GM帐号
	UINT16 _wBornDgnID;			//玩家出生所在副本编号
	UINT16 _wUsrDataVersion;	//玩家的数据版本号
	vector<UINT8> _vecBornIdx;	//玩家出生的GameServer列表

	set<ULONG> _setInAddr;	//映射地址入口
	map<string, string> _mapOutAddr; //映射地址出口
	set<string> _setControlAddr; //控制端地址

	SConfigInfo _oConfigInfo; //所有的Server配置

	string _strPlatFormName;	//数据中心平台名称
	UINT16 _wPlatFormID;		//数据中心平台ID
	UINT32 _dwCompressThreshold;	//发给客户端的数据压缩阈值

    string _strSqlDir;          //服务器数据库脚本
    string _strSqlInit;         //服务器数据库初始化脚本名
    string _strSqlOnce;         //服务器更新时只执行一次的脚本，用于对数据库的更新

    string _strScripts;         //脚本目录
    string _strScriptMain;      //脚本系统的主文件
    string _strBattleReportDir; //战报保存目录
    string  _strLoginKey1;
    string  _strLoginKey2;
    set<UINT8> _setRepeatTask;
    UINT32 _dwOpenServerTime;   //开服时间

    /********** 充值相关内容 begin **********/
    //充值所用token IP与Port
	struct STokenServer
	{
		string strAddr;
		UINT16 wPort;
	};
    vector<STokenServer> _vecTokenServer;
    std::string _strRechargeUrl;
    /********** 充值相关内容 end **********/

protected:
	CNetMgr& _rNetMgr;

#ifdef _WIN32
	IServerDlg* _pServerDlg;
#endif

	enum EConnState
	{
		eStateClosed,
		eStateEstablishing,
		eStateEstablished
	};

	struct SConnect
	{
		string strAddr;
		UINT16 wPort;
		EConnState eState;
	};
	map<UINT32, SConnect> _mapID2Conn;		//Connect的服务器信息

	struct SAccept
	{
		string strAddr;
		UINT16 wPort;
		EConnState eState;
	};
	map<UINT32, SAccept> _mapID2Acc;		//Accept的服务器信息

	multimap<EHostType, string> _mapValidAddr;	//合法的Accept服务器地址

	static CConfig* _pConfig;
};
