#ifndef BASE_SUB_SERVICE_H
#define BASE_SUB_SERVICE_H

#include <map>
#include "baseNetService.h"
#include "protol/protolCmd.h"
class SuperClient;

#pragma pack(1)
enum NetType
{
	NetType_near  = 0,      //近程路由
	NetType_far   = 1,      //远程路由
	if_CTC        = 2,      //电信
	if_CNC        = 3,      //网通
};
struct GameZone
{
	union
	{
		DWORD id;
		struct
		{
			WORD zone;
			WORD game;
		};
	};
	GameZone()
	{
		id = 0;
	}
	GameZone( const GameZone &gameZone )
	{
		id = gameZone.id;
	}
	GameZone& operator= ( const GameZone &gameZone )
	{
		id = gameZone.id;
		return *this;
	}
	bool operator== ( const GameZone &gameZone )
	{
		return id == gameZone.id;
	}
};
enum GameType
{
	GameType_Zhengtu_Normal   = 1,  //征途
	GameType_Zhengtu_Sichuan  = 2,  //征途四川专区
	GameType_Titan_Normal     = 4,  //巨人
};
struct ZoneInfo
{
	union
	{
		DWORD zoneID;
		struct
		{
			//游戏分区编号
			WORD zone;
			//游戏种类编号
			WORD game;
		};
	};
	//区名
	BYTE zoneName[MAX_NAMESIZE];
	//开区时间
	DWORD createDate;
	//合区后的id
	DWORD destZoneID;
	ZoneInfo()
	{
		bzero( this, sizeof( *this ) );
	}
};
#pragma pack()

class SubNetService : public NetService
{
	public:
		virtual ~SubNetService();
		virtual void startUpOver();

		/// @brief 相应管理服务器设置服务器信息
		void setServerInfo(const Cmd::Server::ResponseStartServerCmd *cmd);
		const ServerEntry* getServerEntryByType(const DWORD serverType);
		bool doCmd();
	#if 0
		virtual bool msgParse_SuperServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_FLServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_ChatServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_NameServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_GMServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_MonitorServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_GuildServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_UserServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParseLogin(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_InfoServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
		virtual bool msgParse_RoleServer(const Cmd::NullCmd *ptNullCmd,const DWORD len);
	#endif
		bool sendCmdToSuperServer(const void *cmd,const DWORD len);
		bool broadCmdToFLServer(const void *cmd,const DWORD len);
		bool sendCmdToFLServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToUserServer(const void *cmd,const DWORD len);
	#if 0
		bool sendCmdToUserServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToGuildServer(const void *cmd,const DWORD len);
		bool sendCmdToGuildServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToChatServer(const void *cmd,const DWORD len);
		bool sendCmdToChatServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToNameServer(const void *cmd,const DWORD len);
		bool sendCmdToNameServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToGMServer(const void *cmd,const DWORD len);
		bool sendCmdToGMServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToMonitorServer(const void *cmd,const DWORD len);
		bool sendCmdToMonitorServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToInfoServer(const void *cmd,const DWORD len);
		bool sendCmdToInfoServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToRoleServer(const void *cmd,const DWORD len);
		bool sendCmdToRoleServer(const WORD serverID,const void *cmd,const DWORD len);
		bool broadCmdToGMServer(const void *cmd,const DWORD len);
		bool sendCmdToGMServer(const WORD serverID,const void *cmd,const DWORD len);
		const DWORD getServerEntrySizeByServerType(const DWORD serverType);
		virtual void addNewServer(const DWORD serverID);
		const ServerEntry* getServerEntry(const DWORD serverID);
		const ServerEntry* getServerEntryByType(const DWORD serverType);
		const ServerEntry* getNextServerEntryByType(const DWORD serverType);
		virtual void checkServerEntry();
		const GameZone &getZoneID() const
		{
			return m_gameZone;
		}
		void setZoneID(const GameZone &gameZone);
		const std::string &getZoneName() const
		{
			return m_zoneName;
		}
		void setZoneName(const char *zoneName)
		{
			m_zoneName = zoneName;
		}
		const WORD getNetType() const
		{
			return m_netType;
		}
		void setNetType(const WORD netType)
		{
			m_netType = netType;
		}
	#endif
	public:
		static SubNetService &getInstance()
		{
			return Service::getInstance<SubNetService>();
		}
		void startUpOK()
		{
		}
		bool m_startUp;
	
	protected:
		SubNetService(const std::string &name,const DWORD type);
		bool init();
		bool validate();
		void final();
		WORD m_serverID;
		DWORD m_serverType;
		char m_serverName[MAX_NAMESIZE];
		char m_ip[MAX_IP_LENGTH];
		WORD m_port;
		//服务器外网地址，也就是防火墙地址
		char m_outIP[MAX_IP_LENGTH];
		//服务器外网端口，也就是映射到防火墙的端口
		WORD m_outPort;
		// 网络路由类型
		WORD m_netType;
		Mutex m_lock;
		std::deque<ServerEntry> m_serverList;
	public:
	#if 0
		bool broadSuperCmdToGatewayByGuildServer(const void *cmd,const int len);
		bool broadSuperCmdToGatewayByGuildServer(const DWORD zoneID,const void *cmd,const int len);
		bool sendSuperCmdToGatewayByGuildServer(const DWORD zoneID,const WORD serverID,const void *cmd,const int len);
	#endif
	public:
		typedef std::map<DWORD,ZoneInfo> ZoneInfoMap;
		typedef ZoneInfoMap::iterator ZoneInfoIter;
		ZoneInfoMap m_zoneInfo;
	private:
		GameZone m_gameZone;
		std::string m_zoneName;
		WORD m_superPort;
		char m_superIP[MAX_IP_LENGTH];
		SuperClient *m_superClient;
		Timer m_monitorTimer;
		DWORD m_generation;
	public:
		bool addServerEntry(const ServerEntry &entry);
		const ServerEntry* getServerEntry(const DWORD serverID);

		const WORD getServerID() const
		{
			return m_serverID;
		}
		const DWORD getServerType() const
		{
			return m_serverType;
		}
		const char* getIP() const
		{
			return m_ip;
		}
};

#endif

		
