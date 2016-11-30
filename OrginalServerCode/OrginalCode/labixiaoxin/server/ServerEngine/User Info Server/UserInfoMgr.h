#pragma once
//处理所有玩家数据

//#include "PhpProxySession.h"
#include "..\Base\Service\BaseAdapter.h"
#include "..\GameBase\Common\GameDefine.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
//#include "ace\Containers.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"   
#include "cppconn/prepared_statement.h"   
#include "cppconn/metadata.h"   
#include "cppconn/exception.h" 

#include "PlayerPoolMgr.h"

#include "TeamRankMgr.h"
#include "PVPSeasonMgr.h"
#include <vector>
#include "../GameBase/Protocol/ControlProtocol.h"
#include <queue>
#include "HonorLevel.h"

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, PublicPlayerInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> CHARACTER_INFO_MAP;
typedef CHARACTER_INFO_MAP::ITERATOR CHARACTER_INFO_MAP_ITERATOR;

using namespace sql;

struct MailType
{
	MailType(ACE_UINT32 cid,ACE_UINT32 mid)
	{
		charact_id = cid;
		mail_id = mid;
	}
	ACE_UINT32 charact_id;
	ACE_UINT32 mail_id;
};

//战斗力更新，更新到数据库，检查是否进入战斗力排行榜，如果进入，直接更新玩家的排名，如果没有进入，根据上次读数据库的时间，大于等于10分钟的情况下，异步请求数据库，把玩家更新到对应的战斗力池
//玩家获取战斗力排名，直接读取，返回，然后根据上次读数据库的时间，大于等于10分钟的情况下，异步请求数据库
//玩家获取积分排名，如果还没有获取过称号和奖励ID，从数据库异步获取上赛季排名，如果已经获取，直接获得，积分排名算法同战斗力
//积分基类（战斗力，积分）
//排行榜基类（战斗力，积分）
//玩家池基类
//所有用户管理类型

#define MAX_ARENA_POOL_NODE 512

class UserInfoMgr : public BaseAdapter
{
public:
	UserInfoMgr(ACE_UINT32 unID);
	virtual ~UserInfoMgr();

	bool init_timer();

	void uninit_timer();

	static void EmailtimerCallback(void *p, long lTimerID);
	void DoEmailtimer();

	//virtual BaseObj *new_child_obj(ACE_UINT32 unID){return new PhpProxySession(unID, this);};

	virtual int deal_msg(MessageInfo &msgInfo);
	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual void obj_fini();
	virtual void obj_timeout();

	int get_user_count(){return m_characterMap.current_size();};

	//void reset_season();

	TeamRankMgr m_teamRankMgr;
	PVPSeasonMgr m_pvpSeasonMgr;
//	Pvp100Group  m_pvp100List[MAX_PVP100_STAGE_COUNT];

	//long m_lTimerID;
	BaseTimerHandler *m_serviceEmailTimerHandler;
public://pvp 排行榜相关
	CHonorLevel m_honorLevel;
	void Init_Honour_Level();//更新数据
	void DoLoadHL(std::vector<HLInfo> & ver);
	void DoClearHL();//一个赛季结束清除数据
	std::map<ACE_UINT32,HLInfo> m_nowHLinfoMap;
	HLInfo GetNowHLinfo(ACE_UINT32 characterID);//得到角色的pvp信息
	void UpdateHLinfo(HLInfo & info);//更新角色的pvp信息
	bool GetHLInfoArrayFromDB(HLInfoArray & _array,ACE_UINT32 characterID);//从数据库获取战斗列表
	bool UpdateHLInfoArrayToDB(const HLInfoArray & _array,ACE_UINT32 characterID);//更新战斗列表到数据库
	void UpdateFightRecordInfoToDB(FightRecordInfo & info,bool isRoobt);//更新一个战绩到数据库
	bool GetFightRecordInfoList(FightRecordInfoList & info,ACE_UINT32& winLost,ACE_UINT32 characterID);
	bool UpdateFightRecordInfoList(FightRecordInfoList & info,ACE_UINT32& winLost,ACE_UINT32 characterID);
public:
	void insert_mail_info(MailInfo& roMailInfo);//添加一个邮件
	PublicPlayerInfo *getFriendInfo(ACE_UINT32 cid);
private:
	CHARACTER_INFO_MAP m_characterMap;

	Connection *m_dbConn;//不能长期持有
	ACE_UINT32 m_db_time_heart;//数据库心跳处理 更新m_dbConn

	PreparedStatement *m_prep_stmt;
	ResultSet *m_db_res;

	ACE_UINT32 m_dwMaxMailID;

	Pvp100ListCfg m_pvp100Cfg;

	void initDBConnection();
	void finiDBConnection();

	void destroy_db_res();

	int deal_client_msg(MessageInfo &msgInfo);

	int readFriendDetailFromDB(PublicPlayerInfo *info);
	void readAllFriendDetailFromDB();

	void init_config();
	void init_team_rank();
	void init_pvp_season();

	void update_team_rank_info(ACE_UINT32 dwCharacterID, PlayerTeamInfo *info);

	void init_mail_list();

	//int get_statistical_data(const ACE_UINT32 dwType);

	void init_gift_bag_code();

	void update_gift_bag_code(const char *strCode, const ACE_UINT32 dwUsed);

	void update_season();

	void update_player_pvp_info(PublicPlayerInfo *player);

	int set_name(SQLString str, char *dest, int len);

	ACE_UINT32 m_unDealID;

	//ACE_UINT32 m_arenaPoolCount[MAX_ARENA_COUNT];
	//ArenaPoolNode *m_arenaPoolList[MAX_ARENA_COUNT][MAX_ARENA_POOL_NODE];
	
	PublicPlayerInfo *alloc_character_detail();

	int update_db_connection();
	//Connection *create_db_connection();


	int get_random_player_in_guidance(PublicPlayerInfo *list[], int iLevel, int nCount,bool bFlag = false);

	int get_special_player(PublicPlayerInfo *list[],ACE_UINT32 unMapID);//特殊

	//CharacterPool m_characterPool;
	PlayerPoolMgr m_levelPool;
	PlayerPoolMgr m_teamRankPool;
	PlayerPoolMgr m_pvpRankPool;

	
	void update_mail_info(MailInfo& roMailInfo);//更新邮件
	void delete_mail_info(ACE_UINT32 dwCharacterID, ACE_UINT32 dwMailID);//删除邮件
	bool Get_mail_info(MailInfo& roMailInfo, ACE_UINT32 dwCharacterID, ACE_UINT32 dwMailID);//查找邮件
	int get_reward_from_email(ACE_UINT32 dwCharacterID, MailInfo& roMailInfo, ACE_UINT32 dwReadMailRequestSN);
	
	void insert_gift_bag_code(AdminGiftBagCode &stCode);

	ACE_UINT32 get_character_id_list(ACE_UINT32 unCurrentID, ACE_UINT32 unMaxCount, ACE_UINT32 *dest);

	bool is_pvp_team_valid(PublicPlayerInfo *info);
	void update_pvp_pool(PublicPlayerInfo *info);

	void init_team_rank_pvp100();
	int get_pvp100_rank(ACE_UINT32 point);
	static ACE_UINT32 m_unPhpProxyID;
	ACE_UINT32 m_unCurrentTime;

	int LoadStatistics(const ACE_UINT32 dwType, const char *strDate,ACE_UINT32 * paramList);//统计
	//gm 工具
	int Set_GM_info( GMInfo *request);//设置GM数据
	int Delete_GM_Info(ACE_UINT32 dwtype);//删除一个类型的数据
	void Init_GM_Info();//更新系统公告
	int Get_GM_info(MsgGMRequest * request,MsgGMRsponse & response);
	void Deal_recharge_vip_result(OrderInfo *request);
	void GetProductList(ACE_UINT32 unCharacterID,ProductList & list);
	void UpdateProductList(ACE_UINT32 unCharacterID,ACE_UINT32 unProductID,ProductList & list);
	bool GetVipInfo(ACE_UINT32 unCharacterID,VipInfo & vip);//更新vip阔值
	void UpdateVipInfo(ACE_UINT32 unCharacterID,ACE_UINT32 unMoney,VipInfo & vip);//更新vip阔值到数据库
	void UpdateVip(VipInfo & vip);//更新vip阔值
	void SendMonthCard(MsgSendMonthCardRequest * request);
private:
	static int get_pool_id(ACE_UINT32 unPoolType, PublicPlayerInfo *playerInfo);
	//void add_2_pvp_rank_pool(PublicPlayerInfo *playerInfo);
	//void update_pvp_rank(PublicPlayerInfo *playerInfo);

	void request_rank_from_db();
	int fill_leaderboard_info(PVPTeamInfo *dest, PublicPlayerInfo *list[], ACE_UINT32 unCount, bool isPVPTeam,ACE_INT32 unPage);
	void deal_admin_op( MsgAdminOPRequest * param1, ObjAdr& srcAdr );

	void deal_admin_buffer_op(MsgAdminOPBufferRequest *pRequest, ObjAdr &strAdr);
	int get_all_reward_from_email( ACE_UINT32 dwCharacterID, ACE_UINT32 dwGetAllMailRewardRequestSN );
	ACE_UINT32 m_unCurrentRankUpdateID;
	bool m_bRankUpdateDone;
	bool m_bProcessGetRank;

	std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> > m_mapCharacter2Mail;

	//ACE_Double_Linked_List<ACE_DLList_Node> m_arenaPoolList[MAX_ARENA_COUNT];

	//ACE_UINT32 m_unGlobleGiftBagCodeCount;
	//GiftBagCodeDBItem m_globleGiftBagCodeList[MAX_GLOBLE_GIFT_BAG_CODE_COUNT];
	std::map<std::string, GiftBagCodeInfo> m_mapGiftBagCodeInfo;
	std::map<ACE_UINT32, std::vector<GMInfo>> m_mapSysGMInfo;//系统GM推送信息
	std::queue<GMInfo> m_queUserGMInfo;//炫耀信息，不需要存入数据库

	ACE_Recursive_Thread_Mutex m_mutex;

	void update_BS_info(BadgeShuxingS& infos,ACE_UINT32 unCharacterID);//更新徽章属性
	void Get_BS_info(BadgeShuxingS& infos,ACE_UINT32 unCharacterID);//得到徽章属性
	void CheckSetupMax(PublicPlayerInfo *info);
};