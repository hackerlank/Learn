#include "UserInfoMgr.h"
#include "json\json.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"
#include "..\GameBase\Common\GameDefine.h"
#include "..\Base\Service\ServiceConfigMgr.h"
//#include "..\GameBase\res\ArenaConfig.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\DB Server\DBHandler.h"
#include "InfoDBMgr.h"

//char friendMsgBuff[4096];

#define LOAD_ALL_COUNT_PER_QUERY 1000

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif
#include <Windows.h>
#include "../Base/Service/BaseService.h"
#include "../GameBase/Protocol/DBProtocol.h"
#include "../DB Server/ConnectionPool.h"
#include "../GameBase/res/VipRes.h"
#include "../GameBase/res/ItemResMgr.h"
#include "DBLogMgr.h"


ACE_UINT32 UserInfoMgr::m_unPhpProxyID = OBJ_ID_NONE;

UserInfoMgr::UserInfoMgr(ACE_UINT32 unID)
:BaseAdapter(unID)
{
	m_db_time_heart = 0;
	//m_unMaxChild = 0;
	m_dbConn = NULL;
	m_prep_stmt = NULL;
	m_db_res = NULL;

	m_levelPool.m_unPoolType = PLAYER_POOL_TYPE_LEVEL;
	m_teamRankPool.m_unPoolType = PLAYER_POOL_TYPE_TEAM_RANK;
	m_pvpRankPool.m_unPoolType = PLAYER_POOL_TYPE_PVP_RANK;

	m_levelPool.init(64);
	m_teamRankPool.init(64);
	m_pvpRankPool.init(16);

	//ACE_OS::memset(m_arenaPoolCount, 0, sizeof(ACE_UINT32) * MAX_ARENA_COUNT);

	if(m_unPhpProxyID == 0)
	{
		m_unPhpProxyID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test Php Proxy");
	}

	m_bRankUpdateDone = false;
	m_unCurrentRankUpdateID = 0;
	m_serviceEmailTimerHandler = NULL;
	m_honorLevel.SetSuper(this);
}

UserInfoMgr::~UserInfoMgr()
{
	CHARACTER_INFO_MAP_ITERATOR iter(m_characterMap);
	PublicPlayerInfo *tmp;

	for(iter = m_characterMap.begin(); iter != m_characterMap.end(); iter++)
	{
		tmp = (*iter).int_id_;

		if(tmp == NULL)
		{
			continue;
		}

		//delete tmp->poolNode;
	}
	uninit_timer();
}

bool UserInfoMgr::init_timer()
{
	if (m_serviceEmailTimerHandler == NULL)
	{
		if ((m_serviceEmailTimerHandler = TIMER_MGR_INSTANCE::instance()->registerTimer(this, EmailtimerCallback, NULL, ACE_Time_Value(5, 0), ACE_Time_Value(60, 0))) == NULL)
		{
			return false;
		}
	}
	return true;
}

void UserInfoMgr::uninit_timer()
{
	if(m_serviceEmailTimerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_serviceEmailTimerHandler->m_lTimerID);
		delete m_serviceEmailTimerHandler;
		m_serviceEmailTimerHandler = NULL;
	}
}

void UserInfoMgr::EmailtimerCallback(void *p, long lTimerID)
{
	UserInfoMgr *pMgr = static_cast<UserInfoMgr *>(p);
	if (pMgr != NULL)
	{
		pMgr->DoEmailtimer();
	}
}
//static int _n = 0;
void UserInfoMgr::DoEmailtimer()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
 	printf("-----DoEmailtimer\n");
	std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.begin();
	std::vector<std::pair<ACE_UINT32, ACE_UINT32> > vecDeleteMailID;
	std::map<ACE_UINT32, MailInfo>::iterator it1;
	for(;it != m_mapCharacter2Mail.end();)
	{
		for(it1 = it->second.begin(); it1 != it->second.end();)
		{
			if((it1->second.m_dwReadDate == 0 && it1->second.m_dwTimeoutDate != 0 && it1->second.m_dwTimeoutDate + MAIL_TIME_OUT <= GameUtils::get_utc()) ||
				(it1->second.m_dwReadDate != 0 && it1->second.m_dwReadDate + (24 * 3600) <= GameUtils::get_utc()))
			{
				if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_DELETED) == 0)
				{
					vecDeleteMailID.push_back(std::make_pair(it->first, it1->second.m_dwID));
					it1 = it->second.erase(it1);
				}
				else
					++it1;
			}
			else
			{
				++it1;
			}
		}
		if (it->second.empty())
		{
			it = m_mapCharacter2Mail.erase(it);
		}
		else
		{
			++it;
		}
	}

	for(std::vector<std::pair<ACE_UINT32, ACE_UINT32> >::iterator itVec = vecDeleteMailID.begin();
		itVec != vecDeleteMailID.end(); itVec++)
	{
		delete_mail_info(itVec->first, itVec->second);
		m_mapCharacter2Mail[itVec->first].erase(itVec->second);
	}

	//pvp 赛季排行榜回调
	m_honorLevel.DoOnTimerOut();

	//新服战力排行榜
	if (m_teamRankMgr.DoLAActionTimeCallBack())//有更新了
	{
		std::vector<MailInfo> ver;
		m_teamRankMgr.GetMailItems(ver);
		for (int i=0;i<ver.size();i++)
			insert_mail_info(ver.at(i));
		
	}
	//----------------------------end

	//---------------数据库连接 心跳处理
	m_db_time_heart ++;
	if (m_db_time_heart >= 60*2)//两个小时不处理
	{
		printf("---------db connection time out\n ");
		finiDBConnection();
		initDBConnection();
		m_db_time_heart = 0;
	}
	//------------------------
}

int UserInfoMgr::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	initDBConnection();

	//readAllFriendFromDB();
	init_config();

	init_team_rank();
	init_pvp_season();

	init_mail_list();

	init_gift_bag_code();

	Init_GM_Info();//gm 推送

	init_team_rank_pvp100(); //added by jinpan for pvp100
	readAllFriendDetailFromDB();

	Init_Honour_Level();//pvp 竞技场排行榜

	init_timer();




	
	return BaseAdapter::obj_init(arg, unArgLen);
}

void UserInfoMgr::obj_fini()
{
	finiDBConnection();
	BaseAdapter::obj_fini();
}

void UserInfoMgr::obj_timeout()
{
	m_unCurrentTime = GameUtils::get_utc();
	update_season();
	request_rank_from_db();
}

int UserInfoMgr::deal_msg(MessageInfo &msgInfo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	m_db_time_heart = 0;//心跳处理

	if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) != 0)
	{
		m_unDealID = msgInfo.s_head->srcAdr.unObjID;

		if(deal_client_msg(msgInfo) == 0)
		{

		}
		else
		{
			//send_fail_msg(-1);
			/*
			PhpEndPoint *endpoint = (PhpEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

			if(endpoint != NULL)
			{
			//close connection
			}
			*/
		}

		return 0;
	}
	else
	{
		if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
		{
			m_unCurrentTime = GameUtils::get_utc();

			update_season();

			switch(msgInfo.m_head->unType)
			{
			case MSG_DB_LOG_INFO_REQUEST://日志请求 写入
				{
					MsgDBLogInfoRequest *request = (MsgDBLogInfoRequest*)msgInfo.body;
					DB_LOG_MGR_INSTANCE::instance()->write_db_log(request->logInfoItem,request->unCount);
				}
				break;
			case MSG_GET_CHARACTER_ID_LIST_REQUEST:
				{
					MsgGetCharacterIDListRequest *body = (MsgGetCharacterIDListRequest *)msgInfo.body;

					MsgGetCharacterIDListResponse *response = (MsgGetCharacterIDListResponse *)public_send_buff;
					response->unCount = this->get_character_id_list(body->unCurrentID, body->unMaxCount, response->list);

					int size = sizeof(MsgGetCharacterIDListResponse) + response->unCount * sizeof(ACE_UINT32);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_ID_LIST_RESPONSE, (char *)response, size, msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_UPDATE_STAR_COUNT_REQUEST:
				{
					MsgUpdateStarCount *body = (MsgUpdateStarCount*)msgInfo.body;
					std::map<ACE_UINT32, int>::iterator it = m_teamRankMgr.m_PlayerID2StarCount.find(body->m_dwCharacterID);
					PublicPlayerInfo *playerif = getFriendInfo(body->m_dwCharacterID);
					if(playerif)
					{
						playerif->highestTeamInfo.unStarCount += body->m_dwStarAdded;
						bool bNeedSort = false;
						if(it == m_teamRankMgr.m_PlayerID2StarCount.end())
						{
							if((!m_teamRankMgr.m_PlayerSortedByStar.empty()) && playerif->highestTeamInfo.unStarCount > m_teamRankMgr.m_PlayerSortedByStar.begin()->first)
							{
								std::map<int, std::set<ACE_UINT32> >::iterator it1 = m_teamRankMgr.m_PlayerSortedByStar.begin();
								if (it1 != m_teamRankMgr.m_PlayerSortedByStar.end())
								{
									m_teamRankMgr.m_PlayerID2StarCount.erase(*it1->second.begin());
									it1->second.erase(it1->second.begin());
									if(it1->second.empty())
										m_teamRankMgr.m_PlayerSortedByStar.erase(it1);
								}
								bNeedSort = true;
							}
						}
						else
						{
							std::map<int, std::set<ACE_UINT32> >::iterator it1 = m_teamRankMgr.m_PlayerSortedByStar.find(it->second);
							if (it1 != m_teamRankMgr.m_PlayerSortedByStar.end())
							{
								it1->second.erase(body->m_dwCharacterID);
								if(it1->second.empty())
									m_teamRankMgr.m_PlayerSortedByStar.erase(it1);
							}
							bNeedSort = true;
						}
						if(bNeedSort)
						{
							m_teamRankMgr.m_PlayerSortedByStar[playerif->highestTeamInfo.unStarCount].insert(body->m_dwCharacterID);
							m_teamRankMgr.m_PlayerID2StarCount[body->m_dwCharacterID] = playerif->highestTeamInfo.unStarCount;
						}
						update_team_rank_info(body->m_dwCharacterID, &playerif->highestTeamInfo);
					}
				}
				break;
			case MSG_CHARACTER_INFO_UPDATE_REQUEST:
				{
					MsgCharacterInfoUpdateRequest *body = (MsgCharacterInfoUpdateRequest *)msgInfo.body;

					PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
					if(info != NULL)
					{
						//info->unLevel = body->unLevel;
						info->characterInfo.pveTeam = body->teamInfo;

						if(info->characterInfo.pveTeam.unPoint != info->highestTeamInfo.unPoint)
						{
							//update 2 db
							/*
							InfoDBUpdateTeamRank command;
							command.unCharacterID = body->unCharacterID;
							command.unPoint = body->teamInfo.unPoint;
							command.teamInfo = body->teamInfo;

							INFO_DB_MGR_INSTANCE::instance()->add_command(&command, sizeof(InfoDBUpdateTeamRank));
							*/

							ACE_UINT32 unOldPoint = info->highestTeamInfo.unPoint;
							info->highestTeamInfo = info->characterInfo.pveTeam;
							//m_teamRankPool.move(get_pool_id(PLAYER_POOL_TYPE_TEAM_RANK, info), info);
							update_pvp_pool(info);

							m_teamRankMgr.update(info, unOldPoint);
							//m_teamRankMgr.update(info->characterInfo.unItemID, info->highestTeamInfo.unPoint, &info->highestTeamInfo);
						}

						//ACE_OS::memcpy(info->equipmentList, body->equipmentList, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
						//ACE_OS::memcpy(info->propertyList, body->propertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
						//info->unSkillID = body->unSkillID;
					}
				}
				break;
			case MSG_CHARACTER_NAME_UPDATE_REQUEST:
				{
					MsgCharacterNameUpdateRequest *body = (MsgCharacterNameUpdateRequest *)msgInfo.body;
					PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
					if(info != NULL)
					{
						ACE_OS::memcpy(info->characterInfo.name, body->name, MAX_CHARACTER_LENGTH);
						info->characterInfo.name[MAX_CHARACTER_LENGTH] = '\0';
					}
				}
				break;
			case MSG_DB_GM_REQUEST://GM推送请求
				{
					MsgGMRequest *body = (MsgGMRequest*)msgInfo.body;
					MsgGMRsponse response;

					Get_GM_info(body,response);
					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_GM_RESPONSE, (char *)&response, sizeof(MsgGMRsponse), OBJ_ID_NONE, ADAPTER_MAP_MGR, msgInfo.s_head->srcAdr.unObjID);
				}
				break;
			case MSG_DB_GM_ADD_REQUEST://添加一个炫耀信息
				{
					MsgGMAddRequest *body = (MsgGMAddRequest*)msgInfo.body;

					Set_GM_info(&body->gm);
				}break;
			case MSG_CHARACTER_LEVEL_UPDATE_REQUEST:
				{
					MsgCharacterLevelUpdateRequest *body = (MsgCharacterLevelUpdateRequest *)msgInfo.body;
					PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
					if(info != NULL)
					{
						//printf("user[%d] level update = %d\n", body->unCharacterID, body->unLevel);
						info->characterInfo.unLevel = body->unLevel;

						m_levelPool.move(get_pool_id(PLAYER_POOL_TYPE_LEVEL, info), info);
					}
				}
				break;
			case MSG_CHARACTER_VIP_UPDATE_REQUEST:
				{
					MsgCharacterVipUpdateRequest *body = (MsgCharacterVipUpdateRequest *)msgInfo.body;
					PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
					if(info != NULL)
					{
						info->characterInfo.unVipLevel = body->unVipLevel;
					}
				}
				break;
			case MSG_FIND_CHARACTER_REQUEST:
				{
					MsgFindCharacterRequest *body = (MsgFindCharacterRequest *)msgInfo.body;

					MsgFindCharacterResponse response;


					ACE_OS::memset(&response, 0, sizeof(MsgFindCharacterResponse));

					response.unSN = body->unSN;
					response.nResult = ERROR_MSG_OBJ_NULL;

					PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
					if(info != NULL)
					{
						ACE_OS::memcpy(&response.info, &info->characterInfo, sizeof(CharacterInfoExt));
						response.nResult = 0;
					}

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_FIND_CHARACTER_RESPONSE, (char *)&response, sizeof(MsgFindCharacterResponse), msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_GET_CHARACTER_DETAIL_REQUEST:
				{
					MsgGetCharacterDetailRequest *body = (MsgGetCharacterDetailRequest *)msgInfo.body;

					//char send_buff[4096];
					MsgGetCharacterDetailResponse *response = (MsgGetCharacterDetailResponse *)public_send_buff;
					response->unType = body->unType;
					//response->unCount= body->unCount;
					response->unCount = 0;
					int i;
					PublicPlayerInfo *info;
					for(i = 0;i < body->unCount;i ++)
					{
						info = this->getFriendInfo(body->list[i]);
						if(info == NULL)
						{
							break;
						}

						ACE_OS::memcpy(&response->list[i], &info->characterInfo, sizeof(CharacterInfoExt));

						response->unCount ++;
					}

					int size = sizeof(MsgGetCharacterDetailResponse) + (response->unCount-1) * sizeof(CharacterInfoExt);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_DETAIL_RESPONSE, (char *)response, size, msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_ENTER_MAP_QUERY_CHARACTER_REQUEST:
				{
					MsgEnterMapQueryCharacterRequest *body = (MsgEnterMapQueryCharacterRequest *)msgInfo.body;

					MsgEnterMapQueryCharacterResponse response;
					response.nResult = -1;
					response.unSN = body->unSN;
					response.unMapID = body->unMapID;
					response.specialMap = body->specialMap;
					response.unMultEnergy = body->unMultEnergy;//xxj 2015/04/21  11:35:29 多倍体力


					if (body->unMultEnergy > 0)//多倍体力正常
					{
						PublicPlayerInfo *info = this->getFriendInfo(body->unCharacterID);
						if(info != NULL)
						{
							response.nResult = 0;
							ACE_OS::memcpy(&response.info, &info->characterInfo, sizeof(CharacterInfoExt));
						}
					}

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ENTER_MAP_QUERY_CHARACTER_RESPONSE, (char *)&response, sizeof(MsgEnterMapQueryCharacterResponse), msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_READ_MAIL_REQUEST:
				{
					MsgReadMailRequest *body = (MsgReadMailRequest *)msgInfo.body;
					MsgReadMailResponse *response = (MsgReadMailResponse*)public_send_buff;
					response->nResult = -1;
					bool bFind = false;
					if(body != NULL)
					{
						response->unSN = body->unSN;

						std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(msgInfo.s_head->srcAdr.unObjID);
						if(it != m_mapCharacter2Mail.end())
						{
							std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.find(body->m_dwMailID);
							if(it1 != it->second.end())
							{
								if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) == 0)
								{
									if(it1->second.m_aMailAttachment[0].m_dwItemID != 0)
									{
										if(get_reward_from_email(it1->second.m_dwCharacterID, it1->second, body->unSN) != 0)
											sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgReadMailResponse), msgInfo.s_head->srcAdr);
										return 0;
									}
									it1->second.m_dwFlag |= MAIL_FLAG_HAVE_READ;
									it1->second.m_dwReadDate = GameUtils::get_utc();
									response->m_dwReadDate = it1->second.m_dwReadDate;
									response->nResult = 0;
									update_mail_info(it1->second);
								}
								response->nResult = 0;
								bFind = true;
							}
						}

						if(!bFind)
						{
							std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it2 = m_mapCharacter2Mail.find(0);//查找广播邮件
							if(it2 != m_mapCharacter2Mail.end())
							{
								std::map<ACE_UINT32, MailInfo>::iterator it1 = it2->second.find(body->m_dwMailID);
								if(it1 != it2->second.end())
								{
									if(it1->second.m_aMailAttachment[0].m_dwItemID != 0)
									{
										if(get_reward_from_email(msgInfo.s_head->srcAdr.unObjID, it1->second, body->unSN) != 0)
											sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgReadMailResponse), msgInfo.s_head->srcAdr);
										return 0;
									}
									MailInfo oMailInfo = it1->second;
									oMailInfo.m_dwFlag |= MAIL_FLAG_PUBLIC_MAIL;
									oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_READ;
									if(oMailInfo.m_aMailAttachment[0].m_dwItemID != 0)
										oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_DELETED;
									oMailInfo.m_dwReadDate = GameUtils::get_utc();
									oMailInfo.m_dwIDinTable = it1->second.m_dwID;
									oMailInfo.m_dwCharacterID = msgInfo.s_head->srcAdr.unObjID;
									insert_mail_info(oMailInfo);
									response->m_dwReadDate = oMailInfo.m_dwReadDate;
									response->nResult = 0;
								}
							}
						}

						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgReadMailResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_GET_REWARD_FROM_MAIL_RESPONSE:
				{
					MsgGetRewardFromMailResponse *body = (MsgGetRewardFromMailResponse *)msgInfo.body;
					MsgReadMailResponse *response = (MsgReadMailResponse*)public_send_buff;
					response->nResult = -1;
					bool bFind = false;
					if(body != NULL)
					{
						response->unSN = body->m_dwReadMailRequestSN;

						std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(body->m_dwCharacterID);
						if(it != m_mapCharacter2Mail.end())
						{
							std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.find(body->m_dwMailID);
							if(it1 != it->second.end())
							{
								if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) == 0)
								{
									//it1->second.m_dwFlag |= MAIL_FLAG_HAVE_READ;
									//it1->second.m_dwsecondReadDate = GameUtils::get_utc();
									//update_mail_info(it1->);
									response->m_dwReadDate = GameUtils::get_utc();
									response->nResult = 0;
									delete_mail_info(body->m_dwCharacterID, body->m_dwMailID);
									m_mapCharacter2Mail[body->m_dwCharacterID].erase(body->m_dwMailID);
								}
								bFind = true;
							}
						}

						if(!bFind)
						{
							std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it2 = m_mapCharacter2Mail.find(0);
							if(it2 != m_mapCharacter2Mail.end())
							{
								std::map<ACE_UINT32, MailInfo>::iterator it1 = it2->second.find(body->m_dwMailID);
								if(it1 != it2->second.end())
								{
									MailInfo oMailInfo = it1->second;
									oMailInfo.m_dwFlag |= MAIL_FLAG_PUBLIC_MAIL;
									oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_READ;
									if(oMailInfo.m_aMailAttachment[0].m_dwItemID != 0)
										oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_DELETED;
									oMailInfo.m_dwReadDate = GameUtils::get_utc();
									oMailInfo.m_dwIDinTable = it1->second.m_dwID;
									oMailInfo.m_dwCharacterID = body->m_dwCharacterID;
									insert_mail_info(oMailInfo);
									response->nResult = 0;
									response->m_dwNewMailID = oMailInfo.m_dwID;
									response->m_dwReadDate = oMailInfo.m_dwReadDate;
								}
							}
						}

						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgReadMailResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_GET_MAIL_LIST_REQUEST:
				{
					MsgGetMailListRequest *body = (MsgGetMailListRequest *)msgInfo.body;
					MsgGetMailListResponse *response = (MsgGetMailListResponse*)public_send_buff;
					ZeroVar(public_send_buff,sizeof(public_send_buff));
					response->StartIndex = 0;
					response->unCount = 0;
					if(body != NULL)
					{
						response->unSN = body->unSN;

						std::map<ACE_UINT32, MailInfo*> setPublicMails;
						std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(msgInfo.s_head->srcAdr.unObjID);
						if(it != m_mapCharacter2Mail.end())
						{
							for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
							{
								if((it1->second.m_dwFlag & MAIL_FLAG_PUBLIC_MAIL) != 0)
								{
									setPublicMails[it1->second.m_dwIDinTable] = &it1->second;
								}
								else
								{
									response->list[response->unCount++] = it1->second;
								}		
							}
						}
						it = m_mapCharacter2Mail.find(0);
						if(it != m_mapCharacter2Mail.end())
						{
							for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
							{
								std::map<ACE_UINT32, MailInfo*>::iterator it2 = setPublicMails.find(it1->first);
								if(it2 != setPublicMails.end())
								{
									if((it2->second->m_dwFlag & MAIL_FLAG_HAVE_DELETED) == 0)
									{
										MailInfo &roPublicMailInfo = response->list[response->unCount++];
										roPublicMailInfo = it1->second;
										roPublicMailInfo.m_dwFlag = it2->second->m_dwFlag;
										roPublicMailInfo.m_dwReadDate = it2->second->m_dwReadDate;
									}
									setPublicMails.erase(it2);
								}
								else
								{
									MailInfo &roPublicMailInfo = response->list[response->unCount++];
									roPublicMailInfo = it1->second;
								}
							}
						}

						std::vector<MailType> verDel;
						for(std::map<ACE_UINT32, MailInfo*>::iterator it2 = setPublicMails.begin(); it2 != setPublicMails.end(); it2++)
						{
							delete_mail_info(msgInfo.s_head->srcAdr.unObjID, it2->second->m_dwID);
							verDel.push_back(MailType(msgInfo.s_head->srcAdr.unObjID, it2->second->m_dwID));
						}

						for (std::vector<MailType>::const_iterator c_it = verDel.begin();c_it != verDel.end();c_it++)//删除邮件
							m_mapCharacter2Mail[c_it->charact_id].erase(c_it->mail_id);

						int size = sizeof(MsgGetMailListResponse) + response->unCount * sizeof(MailInfo);
						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_MAIL_LIST_RESPONSE, (char *)response, size, msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_DELETE_READ_MAIL_REQUEST:
				{
					MsgDeleteReadMailRequest *body = (MsgDeleteReadMailRequest *)msgInfo.body;
					MsgDeleteReadMailResponse *response = (MsgDeleteReadMailResponse*)public_send_buff;
					response->nResult = -1;
					if(body != NULL)
					{
						response->unSN = body->unSN;

						std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(msgInfo.s_head->srcAdr.unObjID);
						if(it != m_mapCharacter2Mail.end())
						{
							std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.find(body->m_dwMailID);
							if(it1 != it->second.end())
							{
								if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) != 0)
								{
									response->nResult = 0;
									if((it1->second.m_dwFlag & MAIL_FLAG_PUBLIC_MAIL) != 0)
									{
										MailInfo oMailInfo = it1->second;
										oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_DELETED;
										update_mail_info(oMailInfo);
									}
									else
									{
										delete_mail_info(msgInfo.s_head->srcAdr.unObjID, body->m_dwMailID);
										m_mapCharacter2Mail[msgInfo.s_head->srcAdr.unObjID].erase(body->m_dwMailID);
									}
								}
							}
						}
						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DELETE_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgDeleteReadMailResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_GET_ALL_MAIL_REWARD_REQUEST:
				{
					MsgGetAllMailRewardRequest *body = (MsgGetAllMailRewardRequest*)msgInfo.body;
					if(get_all_reward_from_email(msgInfo.s_head->srcAdr.unObjID, body->unSN) != 0)
					{
						MsgGetAllMailRewardResponse *response = (MsgGetAllMailRewardResponse*)public_send_buff;
						response->nResult = -1;
						sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_ALL_MAIL_REWARD_RESPONSE, (char *)response, sizeof(MsgGetAllMailRewardResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_GET_ALL_MAIL_REWARD_TO_MAP_SERVER_RESPONSE:
				{
					MsgGetAllMailRewardToMapServerResponse *body = (MsgGetAllMailRewardToMapServerResponse *)msgInfo.body;
					MsgGetAllMailRewardResponse *response = (MsgGetAllMailRewardResponse*)public_send_buff;

					response->nResult = -1;

					if(body != NULL)
					{
						response->nResult = body->nResult;
						response->unSN = body->m_dwGetAllMailRewardRequestSN;
						if(body->nResult == 0)
						{
							std::map<ACE_UINT32, MailInfo*> setPublicMails;
							std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(body->m_dwCharacterID);
							if(it != m_mapCharacter2Mail.end())
							{
								std::vector<MailType> verDel;

								for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin();
									it1 != it->second.end();)
								{
									std::map<ACE_UINT32, MailInfo>::iterator it2 = it1++;
									if((it2->second.m_dwFlag & MAIL_FLAG_PUBLIC_MAIL) != 0)
									{
										setPublicMails[it2->second.m_dwIDinTable] = &it2->second;
										continue;
									}
									if(it2->second.m_aMailAttachment[0].m_dwItemID == 0)
									{
										continue;
									}
									if((it2->second.m_dwFlag & MAIL_FLAG_HAVE_READ) != 0 ||
										(it2->second.m_dwFlag & MAIL_FLAG_HAVE_DELETED) != 0)
									{
										continue;
									}

									delete_mail_info(body->m_dwCharacterID, it2->first);
									verDel.push_back(MailType(body->m_dwCharacterID, it2->first));
								}

								for (std::vector<MailType>::const_iterator c_it = verDel.begin();c_it != verDel.end();c_it++)//删除邮件
									m_mapCharacter2Mail[c_it->charact_id].erase(c_it->mail_id);
							}

							std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it2 = m_mapCharacter2Mail.find(0);
							if(it2 != m_mapCharacter2Mail.end())
							{
								for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it2->second.begin();
									it1 != it2->second.end(); it1++)
								{
									std::map<ACE_UINT32, MailInfo*>::iterator it3 = setPublicMails.find(it1->first);
									if(it1->second.m_aMailAttachment[0].m_dwItemID == 0 || (it3 != setPublicMails.end() && 
										((it3->second->m_dwFlag & MAIL_FLAG_HAVE_READ) != 0 ||
										(it3->second->m_dwFlag & MAIL_FLAG_HAVE_DELETED) != 0)))
									{
										continue;
									}
									if(it3 == setPublicMails.end())
									{
										MailInfo oMailInfo = it1->second;
										oMailInfo.m_dwFlag |= MAIL_FLAG_PUBLIC_MAIL;
										oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_READ;
										if(oMailInfo.m_aMailAttachment[0].m_dwItemID != 0)
											oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_DELETED;
										oMailInfo.m_dwReadDate = GameUtils::get_utc();
										oMailInfo.m_dwIDinTable = it1->second.m_dwID;
										oMailInfo.m_dwCharacterID = body->m_dwCharacterID;
										insert_mail_info(oMailInfo);
									}
								}
							}
						}

						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_ALL_MAIL_REWARD_RESPONSE, (char *)response, sizeof(MsgGetAllMailRewardResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_DELETE_ALL_READ_MAIL_REQUEST:
				{
					MsgDeleteAllReadMailRequest *body = (MsgDeleteAllReadMailRequest *)msgInfo.body;
					MsgDeleteAllReadMailResponse *response = (MsgDeleteAllReadMailResponse*)public_send_buff;
					response->nResult = 0;
					if(body != NULL)
					{
						response->unSN = body->unSN;

						std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(msgInfo.s_head->srcAdr.unObjID);
						if(it != m_mapCharacter2Mail.end())
						{
							std::vector<MailType> verDel;
							std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin();
							for(; it1 != it->second.end(); it1++)
							{
								if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) != 0)
								{
									if((it1->second.m_dwFlag & MAIL_FLAG_PUBLIC_MAIL) != 0)
									{
										MailInfo oMailInfo = it1->second;
										oMailInfo.m_dwFlag |= MAIL_FLAG_HAVE_DELETED;
										update_mail_info(oMailInfo);
									}
									else
									{
										delete_mail_info(msgInfo.s_head->srcAdr.unObjID, it1->first);
										verDel.push_back(MailType(msgInfo.s_head->srcAdr.unObjID, it1->first));
									}
								}
							}

							for (std::vector<MailType>::const_iterator c_it = verDel.begin();c_it != verDel.end();c_it++)//删除邮件
								m_mapCharacter2Mail[c_it->charact_id].erase(c_it->mail_id);
						}
						this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DELETE_ALL_READ_MAIL_RESPONSE, (char *)response, sizeof(MsgDeleteAllReadMailResponse), msgInfo.s_head->srcAdr);
					}
				}
				break;
			case MSG_SEND_MONTH_CARD:
				{
					MsgSendMonthCardRequest *body = (MsgSendMonthCardRequest *)msgInfo.body;
					SendMonthCard(body);
				}
				break;
			case MSG_ADMIN_OP_RECHARGE_REQUEST:
				{
					Deal_recharge_vip_result((OrderInfo *)msgInfo.body);
				}break;
			case MSG_ADD_FRIENDSHIP_MAIL_REQUEST:
				{
					MsgAddFriendshipMailRequest *body = (MsgAddFriendshipMailRequest *)msgInfo.body;
					MailInfo oMailInfo;
					oMailInfo.m_dwIDinTable = FRIENDSHIP_MAIL_TEMPLATE_ID;
					oMailInfo.m_dwCharacterID = body->m_dwCharacterID;
					oMailInfo.m_dwTimeoutDate = GameUtils::get_utc();
					oMailInfo.m_aMailAttachment[0].m_dwItemID = RES_CURRENCY_FRIENDSHIP;
					oMailInfo.m_aMailAttachment[0].m_dwItemCount = body->m_dwAddFriendship;

					wchar_t *pstrUtf16_1 = L"你被";
					wchar_t *pstrUtf16_2_1 = L"陌生人";
					wchar_t *pstrUtf16_2_2 = L"好友";
					wchar_t *pstrUtf16_3 = L"邀请助战，获得友情点奖励。";
					char rstrUtf8_1[16];
					char rstrUtf8_2[16];
					char rstrUtf8_3[64];
					int dwLen = -1;
					int iDestLen1 = 0, iDestLen2 = 0, iDestLen3 = 0;
					iDestLen1 = WideCharToMultiByte(CP_UTF8, 0, pstrUtf16_1, dwLen, &rstrUtf8_1[0], 16, NULL, NULL);
					if (body->m_dwAssistFlag == 1)
					{
						iDestLen2 = WideCharToMultiByte(CP_UTF8, 0, pstrUtf16_2_1, dwLen, &rstrUtf8_2[0], 16, NULL, NULL);
					}
					else if (body->m_dwAssistFlag == 2)
					{
						iDestLen2 = WideCharToMultiByte(CP_UTF8, 0, pstrUtf16_2_2, dwLen, &rstrUtf8_2[0], 16, NULL, NULL);
					}
					iDestLen3 = WideCharToMultiByte(CP_UTF8, 0, pstrUtf16_3, dwLen, &rstrUtf8_3[0], 64, NULL, NULL);
					strcpy(oMailInfo.m_strBody, rstrUtf8_1);
					strcat(oMailInfo.m_strBody, rstrUtf8_2);
					strcat(oMailInfo.m_strBody, body->m_strName);
					strcat(oMailInfo.m_strBody, rstrUtf8_3);
					insert_mail_info(oMailInfo);
				}break;
			case MSG_ADMIN_OP_REQUEST:
				{
					deal_admin_op((MsgAdminOPRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_USER_INFO_ADD_MAIL://添加邮件
				{
					MailInfo * oMailInfo = (MailInfo *)msgInfo.body;
					insert_mail_info(*oMailInfo);
				}break;
			case MSG_ADMIN_OP_BUFFER_REQUEST:
				{
					deal_admin_buffer_op((MsgAdminOPBufferRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
				}break;
			case MSG_GET_RANDOM_CHARACTER_REQUEST://获得助战队友
				{

					MsgGetRandomCharacterRequest *body = (MsgGetRandomCharacterRequest *)msgInfo.body;

					//char send_buff[4096];
					MsgGetRandomCharacterResponse *response = (MsgGetRandomCharacterResponse *)public_send_buff;
					response->nResult = 0;
					response->unSN = body->unSN;
					response->unCount = 0;

					PublicPlayerInfo *playerInfo = getFriendInfo(msgInfo.s_head->srcAdr.unObjID);

					PublicPlayerInfo *list[MAX_RANDOM_CHARACTER];
					memset(list,0,sizeof(list));

					if(playerInfo != NULL)
					{
						ACE_INT32 unCount = 0;
						if (body->unGuidanceFlag & 0x1)//新手引导标记位，第1位助战引导
						{
							unCount = get_special_player(list,body->unMapID);
							if (unCount == 0)
							{
								unCount = m_levelPool.get_random_player(get_pool_id(PLAYER_POOL_TYPE_LEVEL, playerInfo), MAX_RANDOM_FRIEND, list, MAX_RANDOM_FRIEND);
								if (unCount > MAX_RANDOM_CHARACTER)
									unCount = MAX_RANDOM_CHARACTER;

								for (int i=0;i<body->unCount;++i)
								{
									for (int j=0;j<unCount;++j)
									{
										if (list[j] != NULL && list[j]->characterInfo.unItemID == body->oFriendIDList[i])
										{
											body->oFriendIDList[i] = body->oFriendIDList[--body->unCount];
											list[j] = NULL;
										}
									}
								}
								for (int i = 0;i<unCount;++i)
								{
									if (list[i] == NULL )
									{
										list[i] = list[--unCount];
									}
									else if(list[i]->characterInfo.unItemID == playerInfo->characterInfo.unItemID)
									{
										list[i] = list[--unCount];
									}
								}
								if (unCount < 6)
								{
									unCount += get_random_player_in_guidance(&list[unCount], playerInfo->characterInfo.unLevel, 6-unCount,body->unMapID);
								}
							}
						}
						else
						{
							unCount = get_random_player_in_guidance(list, playerInfo->characterInfo.unLevel, 2, true);
						}

						if (unCount > MAX_RANDOM_CHARACTER)
							unCount = MAX_RANDOM_CHARACTER;

						int j = 0;
						for(int i = 0;i < unCount;i ++)
						{

							if(list[i]){
								ACE_OS::memcpy(&response->list[j], &list[i]->characterInfo, sizeof(CharacterInfoExt));
								j = j+1;
							}
						}
						response->unCount = j;
					}

					/*
					if(m_characterPool.m_unCount > 0)
					{

					int i;
					PublicPlayerInfo *info;
					int length = m_characterPool.m_unCount;
					for(i = 0;i < MAX_RANDOM_CHARACTER;i ++)
					{
					//int idx = ACE_OS::rand() % m_characterPool.m_unCount;

					if(length <= 0)
					{
					break;
					}

					int idx;

					idx = ACE_OS::rand() % length;

					response->list[i].unItemID = m_characterPool.get_character(idx);

					m_characterPool.swap(idx, length - 1);

					info = this->getFriendInfo(response->list[i].unItemID);
					if(info == NULL)
					{
					break;
					}

					ACE_OS::memcpy(&response->list[i], &info->characterInfo, sizeof(CharacterInfoExt));

					response->unCount ++;

					length --;
					}
					}
					*/

					int size = sizeof(MsgGetRandomCharacterResponse) + (response->unCount-1) * sizeof(CharacterInfoExt);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_RANDOM_CHARACTER_RESPONSE, (char *)response, size, msgInfo.s_head->srcAdr);
				}
				break;

			case MSG_START_PVP_REQUEST:
				{
					/*
					MsgStartPVPRequest *body = (MsgStartPVPRequest *)msgInfo.body;

					MsgStartPVPResponse response;

					ACE_OS::memset(&response, 0, sizeof(MsgStartPVPResponse));
					response.nResult = 0;
					response.unSN = body->unSN;
					response.unStatus = PVP_STATUS_NORMAL;

					PublicPlayerInfo *opponent = NULL;

					if(body->unFriendID == 0)
					{
						//get opponent
						response.pvpType = PVP_TYPE_SEASON;

						PublicPlayerInfo *playerInfo = getFriendInfo(msgInfo.s_head->srcAdr.unObjID);

						if(playerInfo != NULL)
						{
							int nPoolID = get_pool_id(PLAYER_POOL_TYPE_PVP_RANK, playerInfo);

							int c = m_pvpRankPool.pool_size(nPoolID);
							PublicPlayerInfo *list[2];

							if(c >= 100)
							{
								c = m_pvpRankPool.get_random_player(nPoolID, 100, list, 2);
							}
							else
							{
								c = m_teamRankPool.get_random_player(get_pool_id(PLAYER_POOL_TYPE_TEAM_RANK, playerInfo), 100, list, 2);
							}

							int idx = -1;

							int i;

							for(i = 0;i < c;i ++)
							{
								if(list[i]->characterInfo.unItemID != playerInfo->characterInfo.unItemID)
								{
									idx = i;
									break;
								}
							}

							if(idx != -1)
							{
								opponent = list[idx];
							}
						}
					}
					else
					{
						response.pvpType = PVP_TYPE_FRIEND;
						opponent = getFriendInfo(body->unFriendID);
					}

					if(opponent != NULL)
					{
						if(opponent->characterInfo.pvpTeam.unCount < MAX_PLAYER_SELECTED_COUNT)
						{
							response.nResult = -1;
						}
						else
						{
							response.opponent = opponent->characterInfo;
						}
						//response.opponent.teamInfo = opponent->pvpTeamInfo;
					}
					else
					{
						response.nResult = -1;
					}
					
					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_START_PVP_RESPONSE, (char *)&response, sizeof(MsgStartPVPResponse), msgInfo.s_head->srcAdr);
					*/
				}
				break;
			case MSG_UPDATE_PLAYER_RANK_INFO_REQUEST:
				{
// 					MsgUpdatePlayerRankInfoRequest *body = (MsgUpdatePlayerRankInfoRequest *)msgInfo.body;
// 
// 					PublicPlayerInfo *player = this->getFriendInfo(body->unCharacterID);
// 
// 					MsgUpdatePlayerRankInfoResponse response;
// 					ACE_OS::memset(&response, 0, sizeof(MsgUpdatePlayerRankInfoResponse));
// 
// 					//update_player_pvp_info(player);
// 
// 					if(player != NULL)
// 					{
// 						//从player获得积分更新
// 
// 						if(body->dscore != 0)
// 						{
// 							ACE_UINT32 unOldScore = player->pvpRankInfo.unScore;
// 							if(body->dscore < 0)
// 							{
// 								int t = -body->dscore;
// 
// 								if(player->pvpRankInfo.unScore <= t)
// 								{
// 									player->pvpRankInfo.unScore = 0;
// 								}
// 								else
// 								{
// 									player->pvpRankInfo.unScore -= t;
// 								}
// 							}
// 							else
// 							{
// 								player->pvpRankInfo.unScore += body->dscore;
// 								player->pvpRankInfo.unWin ++;
// 							}
// 							player->pvpRankInfo.unAll ++;
// 
// 							if(unOldScore != player->pvpRankInfo.unScore || player->pvpRankInfo.unAll == 1)
// 							{
// 								//update 2 db
// 								InfoDBUpdateScore command;
// 								command.unAll = player->pvpRankInfo.unAll;
// 								command.unCharacterID = player->characterInfo.unItemID;
// 								command.unScore = player->pvpRankInfo.unScore;
// 								command.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
// 								command.unWin = player->pvpRankInfo.unWin;
// 
// 								INFO_DB_MGR_INSTANCE::instance()->add_command(&command, sizeof(InfoDBUpdateScore));
// 							}
// 
// 							/*
// 							//update 2 leaderboard
// 							int tmp_order = m_pvpSeasonMgr.update_leaderboard(player);
// 
// 							if(tmp_order != 0)
// 							{
// 							//get the order player from db
// 							}
// 							*/
// 						}
// 
// 						//get the new order
// 
// 						if(player->pvpRankInfo.unAll > 0)
// 						{
// 							//get new order from db
// 							InfoDBGetPlayerInfoByID command;
// 							command.unCharacterID = player->characterInfo.unItemID;
// 							command.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
// 
// 							INFO_DB_MGR_INSTANCE::instance()->add_command(&command, sizeof(InfoDBGetPlayerInfoByID));
// 						}
// 
// 						response.rankInfo = player->pvpRankInfo;
// 					}
// 					response.unTotalCount = m_pvpSeasonMgr.m_unTotalCount;
// 
// 					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_UPDATE_PLAYER_RANK_INFO_RESPONSE, (char *)&response, sizeof(MsgUpdatePlayerRankInfoResponse), msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_UPDATE_PVP_TEAM_INFO_REQUEST:
				{
					MsgUpdatePVPTeamInfoRequest *body = (MsgUpdatePVPTeamInfoRequest *)msgInfo.body;

					PublicPlayerInfo *player = this->getFriendInfo(body->unCharacterID);

					if(player != NULL)
					{
						//player->pvpTeamInfo =body->teamInfo;
						//player->characterInfo.pvpTeam = body->teamInfo;

						update_pvp_pool(player);
					}
				}
				break;
			case MSG_PLAYER_PVP_RANK_RESPONSE:
				{
					MsgPlayerPVPRankResponse *body = (MsgPlayerPVPRankResponse *)msgInfo.body;

					if(body->unSeasonID == m_pvpSeasonMgr.m_unCurrentSeasonID)
					{
						PublicPlayerInfo *player = this->getFriendInfo(body->unCharacterID);

						m_bProcessGetRank = false;

						if(player != NULL)
						{
							player->pvpRankInfo.unRank = body->unRank;

							//next
							m_unCurrentRankUpdateID = body->unCharacterID;
							request_rank_from_db();

							update_pvp_pool(player);
						}
						else
						{
							m_bRankUpdateDone = true;

							m_pvpSeasonMgr.m_unRankUpdateFlag = 1;

							InfoDBUpdateConfigTable configCommand;
							configCommand.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
							configCommand.unRankUpdateFlag = m_pvpSeasonMgr.m_unRankUpdateFlag;
							INFO_DB_MGR_INSTANCE::instance()->add_command(&configCommand, sizeof(InfoDBUpdateConfigTable));
						}
					}
				}
				break;
			case MSG_PLAYER_PVP_ORDER_RESPONSE:
				{
					MsgPlayerPVPOrderResponse *body = (MsgPlayerPVPOrderResponse *)msgInfo.body;

					if(body->unSeasonID == m_pvpSeasonMgr.m_unCurrentSeasonID)
					{
						PublicPlayerInfo *player = this->getFriendInfo(body->unCharacterID);

						if(player != NULL)
						{
							int old = player->pvpRankInfo.nOrder;
							player->pvpRankInfo.nOrder = body->nOrder;

							m_pvpSeasonMgr.update_leaderboard(player, old);
						} 
					}
				}
				break;
			case MSG_GET_PVP_LEADERBOARD_REQUEST:
				{
					MsgGetPVPLeaderboardRequest *body = (MsgGetPVPLeaderboardRequest *)msgInfo.body;

					MsgGetPVPLeaderboardResponse *response = (MsgGetPVPLeaderboardResponse *)public_send_buff;
					response->unMaxPage = 0;
					response->unPage = body->unPage;
					response->nResult = 0;
					response->unSN = body->unSN;
					response->unCount = 0;
					int i;
					int c;
					PublicPlayerInfo *player;
					switch(body->unType)
					{
					case PVP_LEADERBOARD_FRIEND:
						c = 0;
						PublicPlayerInfo *tmp_list[MAX_FRIEND_COUNT];
						for(i = 0;i < body->unCount;i ++)
						{
							player = this->getFriendInfo(body->list[i]);
							if(player == NULL)
							{
								continue;
							}
							tmp_list[c] = player;
							c ++;
						}
						response->unMaxPage = (c + MAX_TEM_PAGE_COUNT -1)/MAX_TEM_PAGE_COUNT;
						response->unCount = fill_leaderboard_info(response->list, tmp_list, c, true,body->unPage);
						break;
					case PVP_LEADERBOARD_SCORE:
						response->unMaxPage = (m_pvpSeasonMgr.m_unCount + MAX_TEM_PAGE_COUNT -1)/MAX_TEM_PAGE_COUNT;
						response->unCount = fill_leaderboard_info(response->list, m_pvpSeasonMgr.m_list, m_pvpSeasonMgr.m_unCount, true,body->unPage);
						break;
					case PVP_LEADERBOARD_TEAM_POINT:
						response->unMaxPage = (m_teamRankMgr.m_unCount + MAX_TEM_PAGE_COUNT -1)/MAX_TEM_PAGE_COUNT;
						response->unCount = fill_leaderboard_info(response->list, m_teamRankMgr.m_list, m_teamRankMgr.m_unCount, false,body->unPage);
						break;
					case PVP_LEADERBOARD_STAR_COUNT:
						int i = 0;
						for(std::map<int, std::set<ACE_UINT32> >::reverse_iterator it = m_teamRankMgr.m_PlayerSortedByStar.rbegin();
							it != m_teamRankMgr.m_PlayerSortedByStar.rend(); it++)
						{
							for(std::set<ACE_UINT32>::iterator it1 = it->second.begin();
								it1 != it->second.end(); it1++)
							{
								PublicPlayerInfo *playerif = getFriendInfo(*it1);
								response->list[i].unItemID = playerif->characterInfo.unItemID;
								response->list[i].unLevel = playerif->characterInfo.unLevel;
								ACE_OS::memcpy(response->list[i].name, playerif->characterInfo.name, MAX_CHARACTER_LENGTH + 1);

								response->list[i].unScore = playerif->pvpRankInfo.unScore;
								response->list[i].unWin = playerif->pvpRankInfo.unWin;
								response->list[i].unAll = playerif->pvpRankInfo.unAll;
								response->list[i].unRankID = playerif->pvpRankInfo.unRank;
								response->list[i].teamInfo = playerif->highestTeamInfo;
								i++;
							}
						}
						response->unMaxPage = 1;
						response->unCount = i;
						break;
					}

					int size = sizeof(MsgGetPVPLeaderboardResponse) + sizeof(PVPTeamInfo) * (response->unCount - 1);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_PVP_LEADERBOARD_RESPONSE, (char *)response, size, msgInfo.s_head->srcAdr);
				}
				break;
			case MSG_CONVERT_GIFT_BAG_CODE_REQUEST:
				{
					MsgConvertGiftBagCodeRequest *body = (MsgConvertGiftBagCodeRequest *)msgInfo.body;
					std::map<std::string, GiftBagCodeInfo>::iterator itInfo = m_mapGiftBagCodeInfo.find(body->m_strGiftBagCode);
					MsgConvertGiftBagCodeUserInfoRequest oRequest;
					oRequest.unSN = body->unSN;
					oRequest.m_dwGiftBagType = 0;
					oRequest.m_dwCodeType = 0;
					//oRequest.m_dwCharacterID = msgInfo.s_head->srcAdr.unObjID;
					ACE_OS::memcpy(oRequest.m_strCode, body->m_strGiftBagCode, MAX_GIFT_BAG_CODE_LENGTH);
					oRequest.m_nResult = ERROR_MSG_RES;
					if (itInfo != m_mapGiftBagCodeInfo.end())
					{
						oRequest.m_nResult = (itInfo->second.unCodeType == GIFT_BAG_CODE_ONCE) && itInfo->second.byUsed ? ERROR_MSG_GOT : 0;
						oRequest.m_dwGiftBagType = itInfo->second.unGiftBagType;
						oRequest.m_dwCodeType = itInfo->second.unCodeType;
					}
					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CONVERT_GIFT_BAG_CODE_USER_INFO_REQUEST, (char *)&oRequest, sizeof(MsgConvertGiftBagCodeUserInfoRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, msgInfo.s_head->srcAdr.unObjID);
				}
				break;
			case MSG_UPDATE_USER_INFO_GIFT_BAG_CODE:
				{
					MsgUpdateUserInfoGiftBagCodeRequest *body = (MsgUpdateUserInfoGiftBagCodeRequest *)msgInfo.body;
					update_gift_bag_code(body->m_strCode, body->m_dwUsed);
				}break;
			case MSG_GET_CHARACTER_INFO_REQUEST:
				{
					MsgGetCharacterInfoRequest *body = (MsgGetCharacterInfoRequest *)msgInfo.body;
					MsgGetCharacterInfoResponse response;
					ZeroVar(response);
					response.nResult = ERROR_MSG_FIND;
					response.unSN = body->unSN;

					PublicPlayerInfo *playerInfo = getFriendInfo(body->unCharacterID);
					if (playerInfo)
					{
						response.nResult = 0;
						response.info = playerInfo->characterInfo;
					}

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_INFO_RESPONSE, (char *)&response, sizeof(MsgGetCharacterInfoResponse), msgInfo.s_head->srcAdr);
				}break;
			case MSG_DB_UPDATE_PVP_INFO://更新pvp值
				{
					MsgDBUpdatePVPInfoResquestEx * body = (MsgDBUpdatePVPInfoResquestEx *)msgInfo.body;
					//UpdateHLinfo(body->info);
				}break;
			case MSG_GET_PVP_INFO_REQUEST:
				{
					MsgDBUpdatePVPInfoResquestEx * body = (MsgDBUpdatePVPInfoResquestEx *)msgInfo.body;
					HLInfo info =  GetNowHLinfo(body->info.m_characterID);//得到角色的pvp信息
					MsgGetPVPInfoResponse response;
					response.unSN = body->unSN;
					response.info.nhonour = info.m_honour;
					response.info.nhonourRank = -1;
					response.nResult = (info.m_characterID==0)?-1:0;
					if (response.nResult ==0 && !info.isRobt)
						response.info.nhonourRank = m_honorLevel.GetRanking(info.m_honour);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_PVP_INFO_RESPONSE, (char *)&response, sizeof(MsgGetPVPInfoResponse), msgInfo.s_head->srcAdr);
				}break;
			case MSG_PVP_ENTER_FIGHT_REQUEST:
				{
					MsgPVPEnterFightRequest * body = (MsgPVPEnterFightRequest *)msgInfo.body;
					MsgPVPEnterFightResponse response;
					ZeroVar(response);
					response.unSN = body->unSN;
					response.nResult = ERROR_MSG_FIND;
					response.isReFreash = body->isReFreash;
					bool isNeedFind = false;

					if (body->isReFreash == 0)//不需要刷新
					{
						if(GetHLInfoArrayFromDB(response._array,body->m_characterID))//查找老信息
						{
							if (response._array.uncount > 0)//找到了
							{
								response.nResult = 0;
								isNeedFind = false;
							}
							else
								isNeedFind = true;	
						}
						else
							isNeedFind = true;
					}
					else
						isNeedFind = true;

					if (isNeedFind)
					{
						HLInfo info = GetNowHLinfo(body->m_characterID);

						if (info.m_characterID != 0)
						{
							if (info.m_honour<0)//防止晚入
								info.m_honour = GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig.init_honor;

							if(m_honorLevel.ChoiceFightRoole(info,response._array,body->quitList))
							{
								response.nResult = 0;
								UpdateHLInfoArrayToDB(response._array,body->m_characterID);
							}
							else
								response.nResult = ERROR_MSG_PARAMETER;
						}
					}

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PVP_ENTER_FIGHT_RESPONSE, (char *)&response, sizeof(MsgPVPEnterFightResponse), msgInfo.s_head->srcAdr);
				}break;
			case MSG_PVP_GET_ORDER_REQUEST:
				{
					MsgBaseRequest * body = (MsgBaseRequest *)msgInfo.body;
					MsgPVPGetOrderResponse response;
					ZeroVar(response);
					response.unSN = body->unSN;
					response.nResult = 0;
					response.unCount = 0;
					for (int i=0;i<m_honorLevel.m_unCount && i<MAX_HONOUR_LEVEL_COUNT;i++)
					{
						PublicPlayerInfo * p = getFriendInfo(m_honorLevel.m_list[i].m_characterID);
						if (p)
						{
							response.userInfoArray[response.unCount].m_userID = p->characterInfo.unItemID;
							response.userInfoArray[response.unCount].m_roleHeadID = p->characterInfo.pveTeam.playerList[0].unItemID;
							response.userInfoArray[response.unCount].m_unStep = p->characterInfo.pveTeam.playerList[0].unStep;
							std::memcpy(response.userInfoArray[response.unCount].name,p->characterInfo.name,MAX_CHARACTER_LENGTH + 1);
							response.userInfoArray[response.unCount].m_honour = m_honorLevel.m_list[i].m_honour;
							response.unCount++;
						}
					}
					
					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PVP_GET_ORDER_RESPONSE, (char *)&response, sizeof(MsgPVPGetOrderResponse), msgInfo.s_head->srcAdr);
				}break;
			case MSG_PVP_ACCOUNTS_RESPONSE:
				{
					FightRecordInfoEx * body = (FightRecordInfoEx *)msgInfo.body;
					if (body->info.isWin > 0)//赢了
					{
						HLInfo info = GetNowHLinfo(body->info.from.m_characterID);//进攻方
						if (info.m_characterID > 0)
						{
							ACE_INT32 oldHonour = info.m_honour;
							info.m_honour += body->info.score;
							m_honorLevel.update(info,oldHonour);//更新
							UpdateHLinfo(info);
						}

						if (!body->isRoobt)//非机器人
						{
							info = GetNowHLinfo(body->info.to.m_characterID);//防守方
							if (info.m_characterID > 0)
							{
								ACE_INT32 oldHonour = info.m_honour;
								info.m_honour -= body->info.score;
								if(info.m_honour < 0)
									info.m_honour = 0;
								m_honorLevel.update(info,oldHonour);//更新
								UpdateHLinfo(info);
							}
						}
					}
					else//输了
					{
						HLInfo info = GetNowHLinfo(body->info.from.m_characterID);//进攻方
						if(info.m_honour == -1)//第一次参加//
						{
							ACE_INT32 oldHonour = body->info.from.m_honour;
							info.m_honour = body->info.from.m_honour;
							m_honorLevel.update(info,oldHonour);//更新
							UpdateHLinfo(info);
						}
					}

					//更新战绩到数据库
					UpdateFightRecordInfoToDB(body->info,body->isRoobt);
				}break;
			case  MSG_PVP_GET_FightRecordInfo_REQUEST://获取战绩
				{
					MsgPVPFightRecordInfoRequest * body = (MsgPVPFightRecordInfoRequest *)msgInfo.body;
					MsgPVPFightRecordInfoResponse response;
					ZeroVar(response);
					response.unSN = body->unSN;
					response.nResult = 0;
					GetFightRecordInfoList(response.info,response.pvpinfo.unWinLost,body->m_characterID);

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PVP_GET_FightRecordInfo_RESPONSE, (char *)&response, sizeof(MsgPVPFightRecordInfoResponse), msgInfo.s_head->srcAdr);
				}break;
			case MSG_Update_badge_info_REQUESTE:
				{
					MsgUpdateBadgeInfoRequest * body = (MsgUpdateBadgeInfoRequest *)msgInfo.body;
					update_BS_info(body->bsInfos,body->unCharacterID);
				}break;
			case MSG_Get_badge_info_REQUESTE:
				{
					MsgGetBadgeInfoRequest * body = (MsgGetBadgeInfoRequest *)msgInfo.body;
					MsgGetBadgeInfoResponse response;
					ZeroVar(response);
					response.unSN = body->unSN;
					response.nResult = 0;
					response.unCharacterID = body->unCharacterID;
					Get_BS_info(response.bsInfos,body->unCharacterID);
					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_Get_badge_info_RESPONSE, (char *)&response, sizeof(MsgGetBadgeInfoResponse), msgInfo.s_head->srcAdr);
				}break;
			}

		}
	}

	return 0;
}



void UserInfoMgr::initDBConnection()
{
	if(m_dbConn != NULL)
	{
		return;
	}

	m_db_time_heart = 0;
	m_dbConn = InfoDBMgr::create_db_connection();
}

void UserInfoMgr::finiDBConnection()
{
	if(m_dbConn == NULL)
	{
		return;
	}
	try
	{
		m_dbConn->close();
	}
	catch (SQLException &e)
	{

	}

	delete m_dbConn;
	m_dbConn = NULL;
	m_db_time_heart = 0;
}

void UserInfoMgr::destroy_db_res()
{
	if(m_db_res != NULL)
	{
		try
		{
			m_db_res->close();
		}
		catch(SQLException& e) 
		{
		}

		delete m_db_res;
		m_db_res = NULL;
	}

	if(m_prep_stmt != NULL)
	{
		try
		{
			m_prep_stmt->close();
		}
		catch(SQLException& e) 
		{
			printf("fuck !!!!\n");
		}

		delete m_prep_stmt;
		m_prep_stmt = NULL;
	}
}

int UserInfoMgr::update_db_connection()
{
	if(m_dbConn != NULL)
	{
		if(m_dbConn->isClosed())
		{
			delete m_dbConn;

			m_dbConn = NULL;
		}
		else
		{
			return 0;
		}
	}

	m_dbConn = InfoDBMgr::create_db_connection();
	if(m_dbConn == NULL)
	{
		return -1;
	}

	return 0;
}
// 
// Connection *UserInfoMgr::create_db_connection()
// {
// 	Connection *ret = NULL;
// 	Driver *driver;
// 	try
// 	{
// 		driver = get_driver_instance();
// 
// 		if(driver == NULL)
// 		{
// 			return ret;
// 		}
// 
// 		DatabaseInfo *dbInfo = &SERVICE_CONFIG_MGR_INSTANCE::instance()->m_dbInfo;
// 
// 		/* create a database connection using the Driver */  
// 		ret = driver->connect(dbInfo->host, dbInfo->user, dbInfo->password);
// 
// 		if(ret == NULL)
// 		{
// 			return ret;
// 		}
// 
// 		/* turn off the autocommit */
// 		ret -> setAutoCommit(0);
// 		ret -> setSchema(dbInfo->name);
// 	}
// 	catch (SQLException &e)
// 	{
// 		printf("sql error:%s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
// 		if(ret != NULL)
// 		{
// 			try
// 			{
// 				ret->close();
// 			}
// 			catch (SQLException &e)
// 			{
// 
// 			}
// 
// 			delete ret;
// 		}
// 
// 		ret = NULL;
// 	}
// 
// 	return ret;
// }

int UserInfoMgr::deal_client_msg(MessageInfo &msgInfo)
{
	return 0;
}

int UserInfoMgr::get_random_player_in_guidance(PublicPlayerInfo *list[], int iLevel, int nCount,bool bFlag)
{
	std::map<ACE_UINT32, std::pair<std::vector<ACE_UINT32>, std::vector<PublicPlayerInfo *> > > &oRobotTeamConfig = GAME_CONFIG_INSTANCE::instance()->m_oLevelRobotTeam;
	std::map<ACE_UINT32, std::pair<std::vector<ACE_UINT32>, std::vector<PublicPlayerInfo *> > >::iterator itMap = oRobotTeamConfig.find(iLevel);
	if (itMap == oRobotTeamConfig.end())
	{
		return 0;
	}
	std::vector<ACE_UINT32> &seed = itMap->second.first;
	std::vector<PublicPlayerInfo *> &conInfo = itMap->second.second;
	if (bFlag)
	{
		switch (iLevel)
		{
		case 1:
			{
				if (conInfo.size() < 8)
				{
					return 0;
				}
				list[0] = conInfo[0];
				return 1;
			}//break;
		case 2:
			{
				if (conInfo.size() < 8)
				{
					return 0;
				}
				list[0] = conInfo[4];
				itMap = oRobotTeamConfig.find(1);
				if (itMap == oRobotTeamConfig.end() || itMap->second.second.size() < 8)
				{
					return 0;
				}
				list[1] = itMap->second.second[4];
				return 2;
			}break;
		case 3:
			{
				if (conInfo.size() < 8)
				{
					return 0;
				}
				list[0] = conInfo[7];
				itMap = oRobotTeamConfig.find(2);
				if (itMap == oRobotTeamConfig.end() || itMap->second.second.size() < 8)
				{
					return 0;
				}
				list[1] = itMap->second.second[7];
				return 2;
			}break;
		case 6:
			{
				if (conInfo.size() < 8)
				{
					return 0;
				}
				list[0] = conInfo[5];
				itMap = oRobotTeamConfig.find(5);
				if (itMap == oRobotTeamConfig.end() || itMap->second.second.size() < 8)
				{
					return 0;
				}
				list[1] = itMap->second.second[5];
				return 2;
			}break;
		}
	}

	if (itMap->second.second.size() < nCount)
	{
		return 0;
	}

	int iRemain = itMap->second.first.size();
	int i=0;
	int iRandom = 0;
	for (;i<nCount;++i)
	{
		iRandom = ACE_OS::rand() % iRemain;
		seed[--iRemain]^= seed[iRandom];
		seed[iRandom]^= seed[iRemain];
		seed[iRemain]^= seed[iRandom];
		list[i] = conInfo[seed[iRemain]];
	}
	return i;

}


PublicPlayerInfo *UserInfoMgr::getFriendInfo(ACE_UINT32 cid)
{
	PublicPlayerInfo *info;
	if(m_characterMap.find(cid, info) == 0)
	{
		update_player_pvp_info(info);
		Get_BS_info(info->characterInfo.badgeShuxing,info->characterInfo.unItemID);
		return info;	
	}
	std::map<ACE_UINT32, PublicPlayerInfo *>::iterator itMap = GAME_CONFIG_INSTANCE::instance()->m_oRobotTeam.find(cid);
	if (itMap != GAME_CONFIG_INSTANCE::instance()->m_oRobotTeam.end())
	{
		return itMap->second;
	}

	info = this->alloc_character_detail();
	info->characterInfo.unItemID = cid;

	if(info != NULL)
	{
		//read from db
		if(readFriendDetailFromDB(info) == 0)
		{

		}
		else
		{
			delete info;
			info = NULL;
		}
		//update pool
	}

	if(info != NULL)
	{
		m_characterMap.bind(cid, info);

		update_player_pvp_info(info);
		//m_levelPool.add(get_pool_id(PLAYER_POOL_TYPE_LEVEL, info), info);
		m_levelPool.move(get_pool_id(PLAYER_POOL_TYPE_LEVEL, info), info);
		update_pvp_pool(info);
		//m_teamRankPool.add(get_pool_id(PLAYER_POOL_TYPE_TEAM_RANK, info), info);
		//m_characterPool.add_character(cid);
		Get_BS_info(info->characterInfo.badgeShuxing,info->characterInfo.unItemID);
	}

	return info;
}


int UserInfoMgr::readFriendDetailFromDB(PublicPlayerInfo *info)
{
	if(update_db_connection() == -1)
	{
		return -1;
	}
	int ret = -1;
	bool flag = false;
	try
	{
		/*
		m_prep_stmt = m_dbConn->prepareStatement("select character_tbl.name, character_tbl.level,character_tbl.vip_level,character_tmp_tbl.team_info from character_tbl,character_tmp_tbl where character_tbl.character_id=? and character_tbl.character_id=character_tmp_tbl.character_id and character_tbl.level > 0");
		if(m_prep_stmt == NULL)
		{
			return -1;
		}
		m_prep_stmt->setInt(1, info->characterInfo.unItemID);
		m_db_res = m_prep_stmt->executeQuery();
		int c = 0;
		std::istream *stream;
		if(m_db_res != NULL)
		{
		if(m_db_res->next())
		{
		info->characterInfo.unLevel = m_db_res->getInt("level");
		info->characterInfo.unVipLevel = m_db_res->getUInt("vip_level");
		set_name(m_db_res->getString("name"), info->characterInfo.name, MAX_CHARACTER_LENGTH);

		stream = m_db_res->getBlob("team_info");
		stream->read((char *)&info->characterInfo.teamInfo, sizeof(PlayerTeamInfo));


		ret = 0;
		}
		}

		destroy_db_res();
		*/

		m_prep_stmt = m_dbConn->prepareStatement("select name,level,vip_level from character_tbl where character_id=? and level > 0");
		if(m_prep_stmt == NULL)
		{
			return -1;
		}
		m_prep_stmt->setInt(1, info->characterInfo.unItemID);
		m_db_res = m_prep_stmt->executeQuery();
		if(m_db_res != NULL)
		{
			if(m_db_res->next())
			{
				info->characterInfo.unLevel = m_db_res->getInt("level");
				info->characterInfo.unVipLevel = m_db_res->getUInt("vip_level");
				set_name(m_db_res->getString("name"), info->characterInfo.name, MAX_CHARACTER_LENGTH);

				flag = true;
			}
		}

		destroy_db_res();

		if(flag)
		{
			char tmp_sql[1024];

			ACE_OS::sprintf(tmp_sql, "select score,total,win from %s where character_id=? and season_id=?", GameUtils::get_pvp_season_tbl_name(m_pvpSeasonMgr.m_unCurrentSeasonID));

			m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
			if(m_prep_stmt == NULL)
			{
				return -1;
			}

			//m_prep_stmt->setString(1, GameUtils::get_pvp_season_tbl_name(m_pvpSeasonMgr.m_unCurrentSeasonID));
			m_prep_stmt->setInt(1, info->characterInfo.unItemID);
			m_prep_stmt->setInt(2, m_pvpSeasonMgr.m_unCurrentSeasonID);
			m_db_res = m_prep_stmt->executeQuery();
			if(m_db_res != NULL)
			{
				if(m_db_res->next())
				{
					info->pvpRankInfo.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
					info->pvpRankInfo.unScore = m_db_res->getUInt("score");
					info->pvpRankInfo.unAll = m_db_res->getUInt("total");
					info->pvpRankInfo.unWin = m_db_res->getUInt("win");
				}
			}

			info->pvpRankInfo.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;

			destroy_db_res();

			m_prep_stmt = m_dbConn->prepareStatement("select team_info,rank,pvp_season from character_tmp_tbl where character_id=?");
			if(m_prep_stmt == NULL)
			{
				return -1;
			}
			m_prep_stmt->setInt(1, info->characterInfo.unItemID);
			//m_prep_stmt->setInt(2, m_pvpSeasonMgr.m_unCurrentSeasonID);
			m_db_res = m_prep_stmt->executeQuery();
			std::istream *stream;
			if(m_db_res != NULL)
			{
				if(m_db_res->next())
				{
					stream = m_db_res->getBlob("team_info");
					stream->read((char *)&info->characterInfo.pveTeam, sizeof(PlayerTeamInfo));
					CheckSetupMax(info);

// 					stream = m_db_res->getBlob("pvp_team_info");
// 					stream->read((char *)&info->characterInfo.pvpTeam, sizeof(PlayerTeamInfo));

					info->pvpRankInfo.unRank = m_db_res->getUInt("rank");
					info->pvpRankInfo.unRewardSeasonID = m_db_res->getUInt("pvp_season");
				}
			}

			destroy_db_res();
			if (info->characterInfo.pveTeam.unCount == 0)
				return -2;

			m_prep_stmt = m_dbConn->prepareStatement("select team_info from team_rank_tbl where character_id=?");
			if(m_prep_stmt == NULL)
			{
				return -1;
			}
			m_prep_stmt->setInt(1, info->characterInfo.unItemID);
			m_db_res = m_prep_stmt->executeQuery();
			if(m_db_res != NULL)
			{
				if(m_db_res->next())
				{
					stream = m_db_res->getBlob("team_info");
					stream->read((char *)&info->highestTeamInfo, sizeof(PlayerTeamInfo));

					//info->unTeamPoint = m_db_res->getUInt("point");
				}
			}

			destroy_db_res();

			ret = 0;
		}


		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("readFriendDetailFromDB exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

	return ret;
}

void UserInfoMgr::readAllFriendDetailFromDB()
{
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		int id_list[LOAD_ALL_COUNT_PER_QUERY];
		int id_count = 0;

		//ACE_UINT32 unCurrentID = 0;

		do
		{
			//m_prep_stmt = m_dbConn->prepareStatement("select character_id from character_tbl where character_id>? and level > 0 order by character_id limit ?");
			m_prep_stmt = m_dbConn->prepareStatement("select character_id from character_tbl where level > 0 order by RAND() limit ?");
			if(m_prep_stmt == NULL)
			{
				return;
			}

			//m_prep_stmt->setInt(1, unCurrentID);
			m_prep_stmt->setInt(1, LOAD_ALL_COUNT_PER_QUERY);

			m_db_res = m_prep_stmt->executeQuery();
			int c = 0;
			while(m_db_res->next())
			{
				id_list[c] = m_db_res->getUInt("character_id");
				//unCurrentID = id_list[c];

				c ++;
			}

			id_count = c;

			destroy_db_res();
			m_dbConn->commit();

			for(int i = 0;i < id_count;i ++)
			{
				PublicPlayerInfo *info = getFriendInfo(id_list[i]);
			}

			

			if(id_count < LOAD_ALL_COUNT_PER_QUERY)
			{
				break;
			}
		}while(false);
	}
	catch(SQLException &e)
	{
		printf("readAllFriendDetailFromDB exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::update_season()
{
	if(!m_pvpSeasonMgr.check_new_season(m_unCurrentTime))
	{
		return;
	}


	InfoDBUpdateConfigTable configCommand;
	configCommand.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
	configCommand.unRankUpdateFlag = m_pvpSeasonMgr.m_unRankUpdateFlag;
	INFO_DB_MGR_INSTANCE::instance()->add_command(&configCommand, sizeof(InfoDBUpdateConfigTable));

	InfoDBClearSeasonTable clearCommand;
	clearCommand.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
	INFO_DB_MGR_INSTANCE::instance()->add_command(&clearCommand, sizeof(InfoDBClearSeasonTable));

	//异步更新称号
	m_unCurrentRankUpdateID = 0;
	m_bRankUpdateDone = false;
	m_bProcessGetRank = false;

	m_pvpRankPool.reset();

	request_rank_from_db();
}

void UserInfoMgr::init_config()
{
	if(update_db_connection() == -1)
	{
		return;
	}

	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("select current_pvp_season,rank_update_flag from config_tbl");
		if(m_prep_stmt == NULL)
		{
			return;
		}

		m_db_res = m_prep_stmt->executeQuery();

		while(m_db_res->next())
		{
			m_pvpSeasonMgr.m_unCurrentSeasonID = m_db_res->getUInt("current_pvp_season");
			m_pvpSeasonMgr.m_unRankUpdateFlag = m_db_res->getUInt("rank_update_flag");
		}

		destroy_db_res();

		m_dbConn->commit();

		if(m_pvpSeasonMgr.m_unRankUpdateFlag == 0)
		{
			m_bProcessGetRank = false;
			m_bRankUpdateDone = false;
			m_unCurrentRankUpdateID = 0;
		}
		else
		{
			m_bRankUpdateDone = true;
		}

	}
	catch(SQLException &e)
	{
		printf("init team_rank exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}


}

void UserInfoMgr::init_team_rank()
{
	if(update_db_connection() == -1)
	{
		return;
	}

	m_teamRankMgr.reset();

	ACE_UINT32 unIDList[MAX_TEAM_RANK_COUNT];
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("select character_id from team_rank_tbl order by point desc,update_time limit ?");
		if(m_prep_stmt == NULL)					  
		{
			return;
		}
		m_prep_stmt->setInt(1, MAX_TEAM_RANK_COUNT);

		m_db_res = m_prep_stmt->executeQuery();
		int c = 0;
		while(m_db_res->next())
		{
			unIDList[c] = m_db_res->getUInt("character_id");
			c ++;
		}
		destroy_db_res();
		m_dbConn->commit();

		int i;
		PublicPlayerInfo *player;
		for(i = 0;i < c;i ++)
		{
			player = getFriendInfo(unIDList[i]);
			if(player == NULL)
			{
				continue;
			}

			m_teamRankMgr.add(player);
		}


		m_prep_stmt = m_dbConn->prepareStatement("select character_id from team_rank_tbl order by star_count desc,update_time limit ?");
		if(m_prep_stmt == NULL)
		{
			return;
		}
		m_prep_stmt->setInt(1, MAX_TEAM_RANK_COUNT);

		m_db_res = m_prep_stmt->executeQuery();
		c = 0;
		while(m_db_res->next())
		{
			unIDList[c] = m_db_res->getUInt("character_id");
			c ++;
		}

		destroy_db_res();
		m_dbConn->commit();

		for(i = 0;i < c;i ++)
		{
			player = getFriendInfo(unIDList[i]);
			if(player == NULL)
			{
				continue;
			}
			m_teamRankMgr.m_PlayerSortedByStar[player->highestTeamInfo.unStarCount].insert(unIDList[i]);
			m_teamRankMgr.m_PlayerID2StarCount[unIDList[i]] = player->highestTeamInfo.unStarCount;
		}


	}
	catch(SQLException &e)
	{
		printf("init team_rank exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}


void UserInfoMgr::init_team_rank_pvp100() //added by jinpan for pvp100
{
// 	if(update_db_connection() == -1)
// 	{
// 		return;
// 	}

	m_pvp100Cfg = GAME_CONFIG_INSTANCE::instance()->m_pvp100Cfg;

}

int UserInfoMgr::get_pvp100_rank(ACE_UINT32 point)
{
	int c;

	for(c = 0; c < m_pvp100Cfg.unCount; c++){
		if((point >= m_pvp100Cfg.pvp100Cfg[c].points.unStart) && (point <= m_pvp100Cfg.pvp100Cfg[c].points.unEnd)){
			return c;//返回排名
		}
	}
	return -1;  //没找到，配置有问题
}

void UserInfoMgr::init_pvp_season()
{
	if(update_db_connection() == -1)
	{
		return;
	}

	m_pvpSeasonMgr.reset();
	ACE_UINT32 unIDList[MAX_SEASON_RANK_COUNT];
	try
	{
		char tmp_sql[1024];
		ACE_OS::sprintf(tmp_sql, "select character_id from %s order by score desc,update_time limit ?", GameUtils::get_pvp_season_tbl_name(m_pvpSeasonMgr.m_unCurrentSeasonID));
		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
		if(m_prep_stmt == NULL)
		{
			return;
		}

		m_prep_stmt->setInt(1, MAX_SEASON_RANK_COUNT);

		m_db_res = m_prep_stmt->executeQuery();
		int c = 0;

		//ACE_UINT32 unChracterID;



		while(m_db_res->next())
		{
			//unChracterID = 0;

			unIDList[c] = m_db_res->getUInt("character_id");

			c ++;
			//player = getFriendInfo(unChracterID);

			//m_pvpSeasonMgr.add_player(player);
			//player->pvpRankInfo.nOrder = m_pvpSeasonMgr.m_unCount - 1;

		}

		destroy_db_res();

		m_dbConn->commit();

		int i;
		PublicPlayerInfo *player;
		for(i = 0;i < c;i ++)
		{
			player = getFriendInfo(unIDList[i]);
			if(player == NULL)
			{
				continue;
			}

			m_pvpSeasonMgr.add_player(player);
			player->pvpRankInfo.nOrder = i;
		}

	}
	catch(SQLException &e)
	{
		printf("init team_rank exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

int UserInfoMgr::set_name(SQLString str, char *dest, int len)
{
	const char *t = str.c_str();
	if(t == NULL)
	{
		dest[0] = '\0';
	}
	else
	{
		ACE_OS::strncpy(dest, t, len);
		dest[len] = '\0';
	}

	return 0;
}

PublicPlayerInfo *UserInfoMgr::alloc_character_detail()
{
	PublicPlayerInfo *info = new PublicPlayerInfo();

	if(info != NULL)
	{
		ACE_OS::memset(info, 0, sizeof(PublicPlayerInfo));

		int i;

		for(i = 0;i < PLAYER_POOL_TYPE_MAX;i ++)
		{
			info->poolPosition[i].nPoolID = -1;
		}

		info->pvpRankInfo.nOrder = -1;
	}

	return info;
}

ACE_UINT32 UserInfoMgr::get_character_id_list(ACE_UINT32 unCurrentID, ACE_UINT32 unMaxCount, ACE_UINT32 *dest)
{
	if(update_db_connection() == -1)
	{
		return 0;
	}
	int c = 0;
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("select character_id from character_tbl where character_id > ? and level > 0 order by character_id limit ?");
		if(m_prep_stmt == NULL)
		{
			return -1;
		}
		m_prep_stmt->setInt(1, unCurrentID);
		m_prep_stmt->setInt(2, unMaxCount);
		m_db_res = m_prep_stmt->executeQuery();

		while(m_db_res->next())
		{
			dest[c] = m_db_res->getUInt("character_id");
			c ++;
		}

		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("readFriendDetailFromDB exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

	return c;
}

int UserInfoMgr::get_pool_id(ACE_UINT32 unPoolType, PublicPlayerInfo *playerInfo)
{
	int nRet = -1;
	switch(unPoolType)
	{
	case PLAYER_POOL_TYPE_LEVEL:
		{
			nRet = (playerInfo->characterInfo.unLevel - 1) / 2;
		}
		break;
	case PLAYER_POOL_TYPE_TEAM_RANK:
		{
			nRet = 0;//(playerInfo->highestTeamInfo.unPoint - 1) / 2000;
		}
		break;
	case PLAYER_POOL_TYPE_PVP_RANK:
		{
			if(playerInfo->pvpRankInfo.unRank <= 0)
			{
				nRet = 0;
			}
			else
			{
				nRet = 0;//(playerInfo->pvpRankInfo.unRank & 0xFF)- 1;
			}
		}
		break;
	}

	return nRet;
}

/*
void UserInfoMgr::update_pvp_rank(PublicPlayerInfo *playerInfo)
{
//ACE_UINT32 unCurrentTime = GameUtils::get_utc();
ACE_UINT32 seasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;

if(seasonID != playerInfo->pvpRankInfo.unRewardSeasonID)
{
//update from db
}
else
{
m_pvpRankPool.move(get_pool_id(PLAYER_POOL_TYPE_PVP_RANK, playerInfo), playerInfo);
}

ACE_UINT32 t = m_unCurrentTime - playerInfo->unPVPOrderUpdateTime;

if(t > 0)
{
//update from db

}
}
*/

void UserInfoMgr::request_rank_from_db()
{
	if(m_bRankUpdateDone)
	{
		return;
	}
	if(m_bProcessGetRank)
	{
		return;
	}

	InfoDBGetRank command;
	command.unSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
	command.unCurrentCharacterID = m_unCurrentRankUpdateID;

	INFO_DB_MGR_INSTANCE::instance()->add_command(&command, sizeof(InfoDBGetRank));

	m_bProcessGetRank = true;
}

void UserInfoMgr::update_player_pvp_info(PublicPlayerInfo *player)
{
	if(player == NULL)
	{
		return;
	}

	if(player->pvpRankInfo.unRewardSeasonID != m_pvpSeasonMgr.m_unCurrentSeasonID)
	{
		player->pvpRankInfo.unRewardSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
		player->pvpRankInfo.unRewardID = 0;
		player->pvpRankInfo.unRank = 0;
	}

	if(player->pvpRankInfo.unSeasonID == m_pvpSeasonMgr.m_unCurrentSeasonID)
	{
		return;
	}

	player->pvpRankInfo.unSeasonID = player->pvpRankInfo.unRewardSeasonID = m_pvpSeasonMgr.m_unCurrentSeasonID;
	player->pvpRankInfo.unAll = 0;
	player->pvpRankInfo.unRank = 0;
	player->pvpRankInfo.unRewardID = 0;
	player->pvpRankInfo.unScore = 0;
	player->pvpRankInfo.unWin = 0;
	player->pvpRankInfo.nOrder = -1;

	update_pvp_pool(player);
}

int UserInfoMgr::fill_leaderboard_info(PVPTeamInfo *dest, PublicPlayerInfo *list[], ACE_UINT32 unCount, bool isPVPTeam,ACE_INT32 unPage)
{
	
	if(unPage <= 0)
		unPage = 1;

	unPage --;

	unCount = ((unPage + 1)* MAX_TEM_PAGE_COUNT)>unCount?unCount:((unPage + 1)* MAX_TEM_PAGE_COUNT);

	int n = 0;

	for(int i = (unPage * MAX_TEM_PAGE_COUNT);i < unCount;i ++)
	{
		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unItemID = list[i]->characterInfo.unItemID;
		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unLevel = list[i]->characterInfo.unLevel;
		ACE_OS::memcpy(dest[i-(unPage * MAX_TEM_PAGE_COUNT)].name, list[i]->characterInfo.name, MAX_CHARACTER_LENGTH + 1);

		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unScore = list[i]->pvpRankInfo.unScore;
		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unWin = list[i]->pvpRankInfo.unWin;
		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unAll = list[i]->pvpRankInfo.unAll;
		dest[i - (unPage * MAX_TEM_PAGE_COUNT)].unRankID = list[i]->pvpRankInfo.unRank;

		if(!isPVPTeam)
			dest[i-(unPage * MAX_TEM_PAGE_COUNT)].teamInfo = list[i]->highestTeamInfo;

		n++;
	}

	return n;
}

bool UserInfoMgr::is_pvp_team_valid(PublicPlayerInfo *info)
{
// 	if(info->characterInfo.pvpTeam.unCount < MAX_PLAYER_SELECTED_COUNT)
// 	{
// 		return false;
// 	}

	return true;
}

/*int UserInfoMgr::get_statistical_data(const ACE_UINT32 dwType)
{
int iData = -1;
if(update_db_connection() == -1)
{
printf("get_statistical_data[%d] failed1!\n",dwType);
return iData;
}
try
{
switch (dwType)
{
case E_Statistics_Character_Amount:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl ");
}break;
case E_Statistics_Daily_Online:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = CURRENT_DATE()");
}break;
case E_Statistics_Nextday_Remain:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 1 DAY)");
}break;
case E_Statistics_3days_Remain:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 3 DAY)");
}break;
case E_Statistics_7days_Remain:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 7 DAY)");
}break;
case E_Statistics_15days_Remain:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 15 DAY)");
}break;
case E_Statistics_30days_Remain:
{
m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 30 DAY)");
}break;
default:
{
return iData;
}//break;
}
if(m_prep_stmt == NULL)
{
printf("get_statistical_data [%d] failed2!\n", dwType);
return iData;
}
m_db_res = m_prep_stmt->executeQuery();

while(m_db_res->next())
{
//m_statisticsList[dwType] = m_db_res->getInt(0);
}
destroy_db_res();

m_dbConn->commit();
}
catch(SQLException &e)
{

}
return iData;
}*/

void UserInfoMgr::init_gift_bag_code()
{
	if(update_db_connection() == -1)
	{
		printf("get gift bag code failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("select gift_bag_code, gift_bag_type, code_type, used from gift_bag_code_tbl");
		if(m_prep_stmt == NULL)
		{
			printf("get gift bag code failed2!\n");
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		//m_unGlobleGiftBagCodeCount = 0;

		std::string strCode;
		while(m_db_res->next())
		{
			strCode.assign(m_db_res->getString("gift_bag_code").c_str());//, m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_strGiftBagCode, MAX_GIFT_BAG_CODE_LENGTH+1;
			std::transform(strCode.begin(),strCode.end(), strCode.begin(), tolower);
			GiftBagCodeInfo &stInfo = m_mapGiftBagCodeInfo[strCode];
			//m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_unExpiredTime = m_db_res->getUInt("UNIX_TIMESTAMP(expired_time)");
			stInfo.unGiftBagType = m_db_res->getUInt("gift_bag_type");
			stInfo.unCodeType = m_db_res->getUInt("code_type");
			stInfo.byUsed = m_db_res->getInt("used");
		}	


		destroy_db_res();

		m_dbConn->commit();
		/*printf("get gift bag code count: %d\n", m_mapGiftBagCodeInfo.size());*/
	}
	catch(SQLException &e)
	{
		printf("init_gift_bag_code exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::update_gift_bag_code(const char *strCode, const ACE_UINT32 dwUsed)
{
	std::map<std::string, GiftBagCodeInfo>::iterator it = m_mapGiftBagCodeInfo.find(strCode);
	if (it == m_mapGiftBagCodeInfo.end())
	{
		printf("No this gift bag code could be updated: code:%s, used:%d",strCode, dwUsed);
		return;
	}
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("update gift_bag_code_tbl set used=? where gift_bag_code=?");
		m_prep_stmt->setUInt(1, dwUsed);
		m_prep_stmt->setString(2, strCode);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();
		it->second.byUsed = dwUsed;
	}
	catch(SQLException &e)
	{
		printf("update_gift_bag_code exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

}

void UserInfoMgr::update_pvp_pool(PublicPlayerInfo *info)
{
	if(is_pvp_team_valid(info))
	{
		m_teamRankPool.move(get_pool_id(PLAYER_POOL_TYPE_TEAM_RANK, info), info);
		m_pvpRankPool.move(get_pool_id(PLAYER_POOL_TYPE_PVP_RANK, info), info);
	}
	else
	{
		m_teamRankPool.move(-1, info);
		m_pvpRankPool.move(-1, info);
	}
}

void UserInfoMgr::init_mail_list()
{
	m_dwMaxMailID = 0;
	if(update_db_connection() == -1)
	{
		printf("get mail list failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("select * from mail_tbl");
		if(m_prep_stmt == NULL)
		{
			printf("get mail list failed2!\n");
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		std::istream *stream = NULL;
		char *p = NULL;

		std::vector<std::pair<ACE_UINT32, ACE_UINT32> > vecDeleteMailID;
		while(m_db_res->next())
		{
			ACE_UINT32 dwCharacterID = m_db_res->getUInt("mail_owner_id");
			ACE_UINT32 dwMailID = m_db_res->getUInt("mail_id");
			ACE_UINT32 dwTimeoutDate = m_db_res->getUInt("mail_timeout");
			ACE_UINT32 dwReadDate = m_db_res->getUInt("mail_read_date");
			if((dwReadDate == 0 && dwTimeoutDate != 0 && dwTimeoutDate + MAIL_TIME_OUT <= GameUtils::get_utc()) ||
				(dwReadDate != 0 && dwReadDate + (24 * 3600) <= GameUtils::get_utc()))
			{
				vecDeleteMailID.push_back(std::make_pair(dwCharacterID, dwMailID));
			}
			else
			{
				std::map<ACE_UINT32, MailInfo> &rmapMailInfos = m_mapCharacter2Mail[dwCharacterID];
				MailInfo& roMailInfo = rmapMailInfos[dwMailID];
				roMailInfo.m_dwCharacterID = dwCharacterID;
				roMailInfo.m_dwID = dwMailID;
				roMailInfo.m_dwIDinTable = m_db_res->getUInt("mail_template_id");
				roMailInfo.m_dwFlag = m_db_res->getUInt("mail_flag");
				roMailInfo.m_dwTimeoutDate = dwTimeoutDate;
				roMailInfo.m_dwReadDate = dwReadDate;
				stream = m_db_res->getBlob("mail_attachment");
				p = (char *)roMailInfo.m_aMailAttachment;
				while(stream->read(p, sizeof(char)))
				{
					p ++;
				}
				set_name(m_db_res->getString("mail_title"), roMailInfo.m_strTitle, MAIL_TITLE_LEN);

				stream = m_db_res->getBlob("mail_body");
				p = (char *)roMailInfo.m_strBody;
				while(stream->read(p, sizeof(char)))
				{
					p ++;
				}
				//set_name(m_db_res->getString("mail_body"), roMailInfo.m_strBody, MAIL_BODY_LEN);

				set_name(m_db_res->getString("mail_sender"), roMailInfo.m_strSenderName, MAIL_SENDER_NAME_LEN);
				if(roMailInfo.m_dwID > m_dwMaxMailID)
					m_dwMaxMailID = roMailInfo.m_dwID;
			}
		}

		destroy_db_res();

		m_dbConn->commit();
		/*printf("get mail list cout: %d\n", m_mapCharacter2Mail.size());*/
		for(std::vector<std::pair<ACE_UINT32, ACE_UINT32> >::iterator it = vecDeleteMailID.begin();
			it != vecDeleteMailID.end(); it++)
		{
			delete_mail_info(it->first, it->second);
			m_mapCharacter2Mail[it->first].erase(it->second);
		}
	}
	catch(SQLException &e)
	{
		printf("init_mail_list exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::insert_mail_info( MailInfo& roMailInfo )
{
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		DBDataBuf data2((char *)&roMailInfo.m_aMailAttachment, sizeof(MailAttachment) * MAIL_ATTACHMENT_LEN);
		std::istream is2(&data2);
		DBDataBuf data3((char *)&roMailInfo.m_strBody, MAIL_BODY_LEN + 1);
		std::istream is3(&data3);
		m_prep_stmt = m_dbConn->prepareStatement("insert into mail_tbl(mail_id, mail_owner_id,mail_template_id,mail_timeout,mail_title,mail_body,mail_sender,mail_flag,mail_read_date,mail_attachment) values(?,?,?,?,?,?,?,?,?,?)");
		roMailInfo.m_dwID = ++m_dwMaxMailID;
		m_prep_stmt->setUInt(1, roMailInfo.m_dwID);
		m_prep_stmt->setUInt(2, roMailInfo.m_dwCharacterID);
		m_prep_stmt->setUInt(3, roMailInfo.m_dwIDinTable);
		m_prep_stmt->setInt(4, (int)roMailInfo.m_dwTimeoutDate);
		m_prep_stmt->setString(5, roMailInfo.m_strTitle);
		m_prep_stmt->setBlob(6, &is3);
		m_prep_stmt->setString(7, roMailInfo.m_strSenderName);
		m_prep_stmt->setUInt(8, roMailInfo.m_dwFlag);
		m_prep_stmt->setUInt(9, roMailInfo.m_dwReadDate);
		m_prep_stmt->setBlob(10, &is2);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();

		m_mapCharacter2Mail[roMailInfo.m_dwCharacterID][roMailInfo.m_dwID] = roMailInfo;
	}
	catch(SQLException &e)
	{
		printf("insert_mail_info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::delete_mail_info( ACE_UINT32 dwCharacterID, ACE_UINT32 dwMailID )
{
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("delete from mail_tbl where mail_id=?");
		m_prep_stmt->setUInt(1, dwMailID);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();
		//m_mapCharacter2Mail[dwCharacterID].erase(dwMailID);
	}
	catch(SQLException &e)
	{
		printf("init_mail_list exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::update_mail_info( MailInfo& roMailInfo )
{
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		//从数据库中得到邮件
		m_prep_stmt = m_dbConn->prepareStatement("update mail_tbl set mail_flag=?,mail_read_date=? where mail_id=?");
		m_prep_stmt->setUInt(1, roMailInfo.m_dwFlag);
		m_prep_stmt->setUInt(2, roMailInfo.m_dwReadDate);
		m_prep_stmt->setUInt(3, roMailInfo.m_dwID);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();
		m_mapCharacter2Mail[roMailInfo.m_dwCharacterID][roMailInfo.m_dwID] = roMailInfo;
	}
	catch(SQLException &e)
	{
		printf("update_mail_info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::deal_admin_op( MsgAdminOPRequest * request, ObjAdr& srcAdr )
{
	switch(request->unOpType)
	{
	case ADMIN_OP_TYPE_ADD_COIN://增加贝壳
		{
			MailInfo oMailInfo;
			oMailInfo.m_dwIDinTable = REWARD_MAIL_TEMPLATE_ID;
			oMailInfo.m_dwCharacterID = request->unCharacterID;
			oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;
			oMailInfo.m_aMailAttachment[0].m_dwItemID = RES_CURRENCY_COIN;
			oMailInfo.m_aMailAttachment[0].m_dwItemCount = request->paramList[0];
			oMailInfo.SetSenderName(_LOG_OP_WAY_SYSTEM);
			insert_mail_info(oMailInfo);
		}
		break;
	case ADMIN_OP_TYPE_ADD_MONEY://增加金币
		{
			MailInfo oMailInfo;
			oMailInfo.m_dwIDinTable = REWARD_MAIL_TEMPLATE_ID;
			oMailInfo.m_dwCharacterID = request->unCharacterID;
			oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;
			oMailInfo.m_aMailAttachment[0].m_dwItemID = RES_CURRENCY_MONEY;
			oMailInfo.m_aMailAttachment[0].m_dwItemCount = request->paramList[0];
			oMailInfo.SetSenderName(_LOG_OP_WAY_SYSTEM);
			insert_mail_info(oMailInfo);
		}
		break;
	case ADMIN_OP_TYPE_ADD_PLAYER://增加角色
		{
			MailInfo oMailInfo;
			oMailInfo.m_dwIDinTable = FRIENDSHIP_MAIL_PLAYER_ID;
			oMailInfo.m_dwCharacterID = request->unCharacterID;
			oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;
			oMailInfo.m_aMailAttachment[0].m_dwItemID = request->paramList[0];
			oMailInfo.m_aMailAttachment[0].m_dwItemCount = request->paramList[1];
			oMailInfo.SetSenderName(_LOG_OP_WAY_SYSTEM);
			insert_mail_info(oMailInfo);
		}
		break;
	case ADMIN_OP_TYPE_ADD_EQUIPMENT://增加装备
		{
			MailInfo oMailInfo;
			oMailInfo.m_dwIDinTable = FRIENDSHIP_MAIL_EQUIPMENT_ID;
			oMailInfo.m_dwCharacterID = request->unCharacterID;
			oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;
			oMailInfo.m_aMailAttachment[0].m_dwItemID = request->paramList[0];
			oMailInfo.m_aMailAttachment[0].m_dwItemCount = request->paramList[1];
			oMailInfo.SetSenderName(_LOG_OP_WAY_SYSTEM);
			insert_mail_info(oMailInfo);
		}
		break;
	case ADMIN_OP_TYPE_MAIL_POST://邮件公告
		{
			//xxj 2015/04/23  10:19:14 
			MailInfo oMailInfo;
			if (request->unCharacterID == 0)
				oMailInfo.m_dwFlag |= MAIL_FLAG_PUBLIC_MAIL;//公共邮件
			oMailInfo.m_dwTimeoutDate = GameUtils::get_utc();//发送时间
			oMailInfo.m_dwIDinTable = FRIENDSHIP_MAIL_POST_ID;//request->paramList[0];//第一个参数表示特定邮件种类标记
			oMailInfo.m_dwCharacterID = request->unCharacterID;//0表示广播
			memcpy(oMailInfo.m_strTitle,request->strTitle,std::strlen(request->strTitle));//标题
			memcpy(oMailInfo.m_strBody,request->strBuffer,request->unBufferLen);//内容
			oMailInfo.SetSenderName(_LOG_OP_WAY_SYSTEM);
			insert_mail_info(oMailInfo);
		}
		break;
	case ADMIN_OP_TYPE_GM_POST://GM推送公告
		{
			GMInfo info;
			ZeroVar(info);
			memcpy(info.strBuffer,request->strBuffer,MAIL_BODY_LEN);
			info.unGoodID = 0;//id
			info.unLevel = 0;//等级
			info.unFromID = 0;//系统消息
			info.unToID = request->unCharacterID;
			info.unType = request->paramList[0];
			ACE_UINT32 unDeleteID = request->paramList[1];
			if (unDeleteID > 0)
				Delete_GM_Info(unDeleteID);//删除此消息类型
			else
				Set_GM_info(&info);//插入此消息到数据库（运营消息）
		}
		break;
	}
}

void UserInfoMgr::deal_admin_buffer_op(MsgAdminOPBufferRequest *pRequest, ObjAdr &strAdr)
{
	switch(pRequest->unOpType)
	{
	case ADMIN_OP_TYPE_ADD_GIFT_BAG_CODE:
		{
			AdminGiftBagCode oCode;
			if (pRequest->unParamCount < 2)
			{
				printf("error occurs in ADMIN_OP_TYPE_ADD_GIFT_BAG_CODE");
				return;
			}
			oCode.unCodeType = pRequest->paramList[0];
			oCode.unGiftBagType = pRequest->paramList[1];

			memcpy(oCode.strCode, pRequest->strBuffer, pRequest->unBufferLen); //不会超长的
			for (int i=0;i<MAX_GIFT_BAG_CODE_LENGTH;i++)//大写转小写
			{
				if (oCode.strCode[i]>='A' && oCode.strCode[i] <= 'Z')
				{
					oCode.strCode[i] += 32;
				}
			}
			oCode.strCode[pRequest->unBufferLen] = '\0';
			insert_gift_bag_code(oCode);
		}break;
	case ADMIN_OP_TYPE_STATISTICS://统计
		{
			AdminStatistics oStatistics;
			if (pRequest->unParamCount < 1)
			{
				printf("error occurs in ADMIN_OP_TYPE_STATISTICS");
				return;
			}
			oStatistics.unStatisticsType = pRequest->paramList[0];
			ACE_OS::memcpy(oStatistics.strDate, pRequest->strBuffer, pRequest->unBufferLen); //不会超长的
			pRequest->strBuffer[pRequest->unBufferLen] = '\0';
			int iData = LoadStatistics(oStatistics.unStatisticsType, oStatistics.strDate,pRequest->paramList);

			tagMsgDBGetStatisticsResponse response;
			response.unData = iData;
			response.unType = oStatistics.unStatisticsType;
			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_GET_DATA_STATISTICS, (char *)&response, sizeof(MsgDBAdminStatisticsResponse), strAdr);
		}break;
	default:
		break;
	}
}

void UserInfoMgr::insert_gift_bag_code(AdminGiftBagCode &stCode)
{
	if(update_db_connection() == -1)
	{
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("insert into gift_bag_code_tbl(gift_bag_code, gift_bag_type, code_type) values(?,?,?)");
		m_prep_stmt->setString(1, stCode.strCode);
		m_prep_stmt->setUInt(2, stCode.unGiftBagType);
		m_prep_stmt->setUInt(3, stCode.unCodeType);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();
		GiftBagCodeInfo stInfo;
		stInfo.byUsed = 0;
		stInfo.unCodeType = stCode.unCodeType;
		stInfo.unGiftBagType = stCode.unGiftBagType;
		m_mapGiftBagCodeInfo.insert(std::make_pair(stCode.strCode, stInfo));
	}
	catch(SQLException &e)
	{
		printf("insert_gift_bag_code exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

int UserInfoMgr::get_reward_from_email( ACE_UINT32 dwCharacterID, MailInfo& roMailInfo, ACE_UINT32 dwReadMailRequestSN )
{
	MsgGetRewardFromMailRequest oRequest;
	oRequest.m_dwCharacterID = dwCharacterID;
	oRequest.m_dwMailID = roMailInfo.m_dwID;
	oRequest.m_dwReadMailRequestSN = dwReadMailRequestSN;
	memcpy(oRequest.m_strSenderName,roMailInfo.m_strSenderName,sizeof(char)*(MAIL_SENDER_NAME_LEN + 1));
	for(int i = 0; i != MAIL_ATTACHMENT_LEN; i++)
	{
		oRequest.m_aMailAttachment[i] = roMailInfo.m_aMailAttachment[i];
	}
	return this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_REWARD_FROM_MAIL_REQUEST, (char *)&oRequest, sizeof(MsgGetRewardFromMailRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, dwCharacterID);
}

int UserInfoMgr::get_all_reward_from_email( ACE_UINT32 dwCharacterID, ACE_UINT32 dwGetAllMailRewardRequestSN )
{
	MsgGetAllMailRewardToMapServerRequest *poRequest = (MsgGetAllMailRewardToMapServerRequest*)public_send_buff;
	poRequest->m_dwCount = 0;
	poRequest->m_dwCharacterID = dwCharacterID;
	poRequest->m_dwGetAllMailRewardRequestSN = dwGetAllMailRewardRequestSN;
	std::map<ACE_UINT32, MailInfo*> setPublicMails;
	std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(dwCharacterID);
	if(it != m_mapCharacter2Mail.end())
	{
		for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if((it1->second.m_dwFlag & MAIL_FLAG_PUBLIC_MAIL) != 0)
			{
				setPublicMails[it1->second.m_dwIDinTable] = &it1->second;
			}
			else
			{
				if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) == 0)
				{
					for (int i=0;i<MAIL_ATTACHMENT_LEN;++i)
					{
						if (it1->second.m_aMailAttachment[i].m_dwItemID == 0)
						{
							break;
						}
						poRequest->m_aMailAttachment[poRequest->m_dwCount++] = it1->second.m_aMailAttachment[i];
					}
				}
			}		
		}
	}
	it = m_mapCharacter2Mail.find(0);
	if(it != m_mapCharacter2Mail.end())
	{
		for(std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			std::map<ACE_UINT32, MailInfo*>::iterator it2 = setPublicMails.find(it1->first);
			if(it2 != setPublicMails.end())
			{
				if((it2->second->m_dwFlag & MAIL_FLAG_HAVE_READ) == 0)
				{
					for (int i=0;i<MAIL_ATTACHMENT_LEN;++i)
					{
						if (it2->second->m_aMailAttachment[i].m_dwItemID == 0)
						{
							break;
						}
						poRequest->m_aMailAttachment[poRequest->m_dwCount++] = it2->second->m_aMailAttachment[i];
					}
				}
			}
			else
			{
				if((it1->second.m_dwFlag & MAIL_FLAG_HAVE_READ) == 0)
				{
					for (int i=0;i<MAIL_ATTACHMENT_LEN;++i)
					{
						if (it1->second.m_aMailAttachment[i].m_dwItemID == 0)
						{
							break;
						}
						poRequest->m_aMailAttachment[poRequest->m_dwCount++] = it1->second.m_aMailAttachment[i];
					}
				}
			}
		}
	}
	int size = sizeof(MsgGetAllMailRewardToMapServerRequest) + poRequest->m_dwCount * sizeof(MailAttachment);
	return this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_ALL_MAIL_REWARD_TO_MAP_SERVER_REQUEST, (char *)poRequest, size, OBJ_ID_NONE, ADAPTER_MAP_MGR, dwCharacterID);
}

void UserInfoMgr::update_team_rank_info( ACE_UINT32 dwCharacterID, PlayerTeamInfo *info )
{
	if(update_db_connection() == -1)
	{
		return;
	}

	m_prep_stmt = m_dbConn->prepareStatement("replace into team_rank_tbl(point,team_info,update_time,star_count,character_id) values(?,?,?,?,?)");
	if(m_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info, sizeof(PlayerTeamInfo));
	std::istream is(&data);

	m_prep_stmt->setInt(1, info->unPoint);
	m_prep_stmt->setBlob(2, &is);
	m_prep_stmt->setInt(3, GameUtils::get_utc());
	m_prep_stmt->setInt(4, info->unStarCount);
	m_prep_stmt->setInt(5, dwCharacterID);
	m_db_res = m_prep_stmt->executeQuery();
	destroy_db_res();
	m_dbConn->commit();
}

bool UserInfoMgr::Get_mail_info( MailInfo& roMailInfo,ACE_UINT32 dwCharacterID, ACE_UINT32 dwMailID)
{
	std::map<ACE_UINT32, std::map<ACE_UINT32, MailInfo> >::iterator it = m_mapCharacter2Mail.find(dwCharacterID);
	if(it != m_mapCharacter2Mail.end())
	{
		std::map<ACE_UINT32, MailInfo>::iterator it1 = it->second.find(dwMailID);
		if(it1 != it->second.end())
		{
			roMailInfo = it1->second;
			return true;
		}
	}
	return false;
}

int UserInfoMgr::LoadStatistics( const ACE_UINT32 dwType, const char *strDate,ACE_UINT32 * paramList )
{
	int iData = 0;
	//ACE_UINT32 tCurrentTime = GameUtils::get_utc();
	//if (m_tLastReloadTime + Statistics_Reload_Interval < tCurrentTime)
	//{
	//m_tLastReloadTime = tCurrentTime;
	// 	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	// 	sql::ResultSet *db_res = NULL;
	// 	sql::PreparedStatement *prep_stmt = NULL;
	if(update_db_connection() == -1)
	{
		return -1;
	}
	if (dwType == E_Statistics_ACU)
	{
		ACE_UINT32 unCurrentTimes = 0;
		ACE_UINT32 ACUList[Statistics_ACU_Num];
		m_prep_stmt = m_dbConn->prepareStatement("select blob_data from statistics_info_tbl where record_time = CURRENT_DATE() AND statistics_type = 7");

		if (m_prep_stmt == NULL)
		{
			printf("get_statistical_data failed2!\n");
			return -1;
		}
		m_db_res = m_prep_stmt->executeQuery();

		while(m_db_res->next())
		{
			std::istream *stream = m_db_res->getBlob("blob_data");
			unCurrentTimes = 0;
			memset(ACUList, 0, Statistics_ACU_Num * sizeof(ACE_UINT32));
			while((unCurrentTimes < Statistics_ACU_Num) && stream->read((char *)&ACUList[unCurrentTimes], sizeof(ACE_UINT32)))
			{
				++unCurrentTimes;
			}
		}
		ACE_UINT32 unTotal = 0;
		for (ACE_UINT32 i=0;i<unCurrentTimes;++i)
		{
			unTotal += ACUList[i];
		}
		iData = unTotal / (unCurrentTimes+1);

		destroy_db_res();
		return iData;
	}
	// 	else if (dwType == E_Statistics_PCU)
	// 	{
	// 		return m_unPCU;
	// 	}
	try
	{
		switch (dwType)
		{
		case E_Statistics_Character_Amount:
			{
				m_prep_stmt = m_dbConn->prepareStatement("select count(1) from character_tbl ");
			}break;
		case E_Statistics_Daily_Online:
		case E_Statistics_Nextday_Remain:
		case E_Statistics_3days_Remain:
		case E_Statistics_7days_Remain:
		case E_Statistics_15days_Remain:
		case E_Statistics_30days_Remain:
		case E_Statistics_PCU:
			{
				m_prep_stmt = m_dbConn->prepareStatement("select digital_data from statistics_info_tbl where record_time = DATE(?) AND statistics_type = ?");
				m_prep_stmt->setDateTime(1, strDate);
				m_prep_stmt->setInt(2, dwType);
			}break;
		case E_Statistics_ACU:
			{

			}break;
		case  E_Statistics_Tutorial://新手引导
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				//ACE_UINT32 day = std::atoi(strDate);
				v *= paramList[1]; 
				m_prep_stmt = m_dbConn->prepareStatement("select count(user_id) from character_tbl WHERE tutorial_flag > 1024 AND last_login_time-create_time < ?");
				m_prep_stmt->setInt(1, v);
			}
			break;
		case E_Statistics_Effect_Character://指定时间段内达到某一等级的用户的数量
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				//ACE_UINT32 day = std::atoi(strDate);
				v *= paramList[1]; 
				m_prep_stmt = m_dbConn->prepareStatement("select count(user_id) from character_tbl WHERE level = ?  AND last_login_time-create_time < ?");
				m_prep_stmt->setInt(1, paramList[2]);//等级
				m_prep_stmt->setInt(2, v);//时间段
			}
			break;
		case E_Statistics_Effect_Register://时间区间查询目前累计注册账号
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				v *= paramList[1]; 
				ACE_INT32 day = GameUtils::Get_Day_from_str(strDate);//以当前时间为起点查询
				m_prep_stmt = m_dbConn->prepareStatement("select count(user_id) from character_tbl WHERE create_time > ? and create_time < ?");
				m_prep_stmt->setInt(1, day);//时间起点
				m_prep_stmt->setInt(2, day + v);//时间段
			}
			break;
		case E_Statistics_Effect_Login://可设定时间区间查询目前累计登陆账号，可查询时间区间内登陆变化曲线
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				v *= paramList[1]; 
				ACE_INT32 day = GameUtils::Get_Day_from_str(strDate);//以当前时间为起点查询
				m_prep_stmt = m_dbConn->prepareStatement("select count(user_id) from character_tbl WHERE last_login_time > ? and last_login_time < ?");
				m_prep_stmt->setInt(1, day);//时间起点
				m_prep_stmt->setInt(2, day + v);//时间段
			}
			break;
		case E_Statistics_lost_Login://指定时间点，玩家连续7/14/30未登陆游戏
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				v *= paramList[1]; 
				ACE_INT32 day = GameUtils::Get_Day_from_str(strDate);//以当前时间为起点查询
				m_prep_stmt = m_dbConn->prepareStatement("select count(user_id) from character_tbl WHERE last_login_time < ?");
				m_prep_stmt->setInt(1, day - v);//时间起点
			}
			break;
		default:
			{
				destroy_db_res();
				return iData;
			}//break;
		}
		if (m_prep_stmt == NULL)
		{
			printf("get_statistical_data [%d] failed2!\n", dwType);
			return iData;
		}
		m_db_res = m_prep_stmt->executeQuery();

		while(m_db_res->next())
		{
			iData = m_db_res->getInt(1);
		}
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadStatistics sql exception type[%u]",__FILE__, __LINE__, dwType);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadStatistics data handle exception type[%u]",__FILE__, __LINE__, dwType);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}

	destroy_db_res();
	return iData;
}

int UserInfoMgr::Set_GM_info(GMInfo *request )//添加公告
{
	int iReturn = -1;
	switch(request->unType)
	{
	case ADMIN_OP_GM_PUT:
		{
			if(update_db_connection() == -1)
			{
				return -1;
			}
			//m_prep_stmt = m_dbConn->prepareStatement("CALL do_gm_sys_insert(?,?,?,?,?);");
			m_prep_stmt = m_dbConn->prepareStatement("INSERT INTO gm_tbl(from_id,from_name,to_id,type,info) VALUES(?,?,?,?,?)");
			if(m_prep_stmt)
			{
				m_prep_stmt->setInt(1, request->unFromID);
				m_prep_stmt->setString(2,request->fromName);
				m_prep_stmt->setInt(3, request->unToID);
				m_prep_stmt->setInt(4, request->unType);
				m_prep_stmt->setString(5,request->strBuffer);

				m_prep_stmt->executeUpdate();
			}
			destroy_db_res();
			iReturn = 0;
		}
		break;
	case ADMIN_OP_GM_LUCK_EQUIPMENT://抽奖 获得3星或以上装备
	case ADMIN_OP_GM_LUCK_PLAYER://抽奖 获得角色
	case ADMIN_OP_GM_STEP_EQUIPMENT://进阶装备
	case ADMIN_OP_GM_STEP_PLAYER://进阶角色
	case ADMIN_OP_GM_COMPOSE://合成装备
		{
			m_queUserGMInfo.push(*request);
			while(m_queUserGMInfo.size()>MAX_GM_USER_COUNT)
				m_queUserGMInfo.pop();//删除一个元素
			//不更新到数据库
			iReturn = 0;
		}break;
	default:
		break;
	}

	return iReturn;
}

void UserInfoMgr::Init_GM_Info()
{
	if(update_db_connection() == -1)
	{
		printf("get gift bag code failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT from_id,from_name,to_id,type,info FROM gm_tbl");
		if(m_prep_stmt == NULL)
		{
			printf("get sys gm opst failed2!\n");
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		//m_unGlobleGiftBagCodeCount = 0;
		m_mapSysGMInfo.clear();
		while(!m_queUserGMInfo.empty()) 
			m_queUserGMInfo.pop();

		std::string strinfo;
		while(m_db_res->next())
		{
			GMInfo info;
			info.unType = m_db_res->getUInt("type");
			info.unFromID = m_db_res->getInt("from_id");
			info.unToID = m_db_res->getInt("to_id");
			const char *t = m_db_res->getString("info").c_str();
			if(t == NULL)
				info.strBuffer[0] = '\0';
			else
			{
				ACE_OS::strncpy(info.strBuffer, t, MAIL_BODY_LEN);
				info.strBuffer[MAIL_BODY_LEN] = '\0';
			}
			t = m_db_res->getString("from_name").c_str();

			if(t == NULL)
				info.fromName[0] = '\0';
			else
			{
				ACE_OS::strncpy(info.fromName, t, MAX_CHARACTER_LENGTH);
				info.fromName[MAX_CHARACTER_LENGTH] = '\0';
			}


			m_mapSysGMInfo[info.unToID].push_back(info);
		}	
		destroy_db_res();

		m_dbConn->commit();
		/*printf("get gm post count: %d\n", m_mapSysGMInfo.size());*/
	}
	catch(SQLException &e)
	{
		printf("Init_SYS_GM_Info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

int UserInfoMgr::Get_GM_info( MsgGMRequest * request,MsgGMRsponse & response )
{
	ZeroVar(response);
	response.nResult = -1;
	if (request->unTypeID < ADMIN_OP_GM_USER)//运营消息
	{
		response.unSN = request->unSN;
		std::map<ACE_UINT32, std::vector<GMInfo>>::const_iterator c_it = m_mapSysGMInfo.find(request->unTypeID);
		if(c_it != m_mapSysGMInfo.end())
		{
			std::vector<GMInfo>::const_iterator _it = c_it->second.begin();
			while(_it != c_it->second.end())
			{
				response.info[response.unCount] = *_it;
				// 				response.info[response.unCount].unType = _it->unType;
				// 				response.info[response.unCount].unFromID = _it->unFromID;
				// 				response.info[response.unCount].unToID = _it->unToID;
				// 				memcpy(response.info[response.unCount].strBuffer,_it->strBuffer,MAIL_BODY_LEN);
				response.unCount ++;
				if (response.unCount == MSG_GM_MAX_LEN)
					break;
				_it++;
			}
			response.nResult = 0;
		}
	}

	if(request->unTypeID >= ADMIN_OP_GM_USER ||  request->unTypeID == 0)//炫耀信息
	{
		std::queue<GMInfo> queUserGMInfo = m_queUserGMInfo;//炫耀信息，不需要存入数据库
		while(!queUserGMInfo.empty())
		{
			if (response.unCount == MSG_GM_MAX_LEN)
				break;
			response.info[response.unCount] = queUserGMInfo.front();
			// 			response.info[response.unCount].unFromID = info.unFromID;
			// 			response.info[response.unCount].unToID = info.unToID;
			// 			memcpy(response.info[response.unCount].strBuffer,info.strBuffer,MAIL_BODY_LEN);
			response.unCount ++;
			queUserGMInfo.pop();
		}
	}

	return 0;
}

int UserInfoMgr::Delete_GM_Info( ACE_UINT32 dwtype )
{
	if(update_db_connection() == -1)
	{
		return -1;
	}
	m_prep_stmt = m_dbConn->prepareStatement("DELETE FROM gm_tbl WHERE type = ?");
	if(m_prep_stmt)
	{
		m_prep_stmt->setInt(1, dwtype);
		m_prep_stmt->executeUpdate();
	}

	destroy_db_res();

	return 0;
}

void UserInfoMgr::Deal_recharge_vip_result( OrderInfo *request )
{
	ProductList list;
	GetProductList(request->unCharacterID,list);
	UpdateProductList(request->unCharacterID,request->unProductId,list);

	VipInfo vipInfo;
	if(GetVipInfo(request->unCharacterID,vipInfo))
	{
		UpdateVipInfo(request->unCharacterID,request->unRenminbi,vipInfo);//更新vip信息
	}
}

void UserInfoMgr::GetProductList( ACE_UINT32 unCharacterID,ProductList & list )
{
	if(update_db_connection() == -1)
	{
		return;
	}

	bool iReturn = true;
	m_prep_stmt = m_dbConn->prepareStatement("select product from product_tbl where character_id=?");
	if(m_prep_stmt != NULL)
	{
		m_prep_stmt->setInt(1, unCharacterID);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res != NULL && m_db_res->next())
		{
			std::istream *stream;
			stream = m_db_res->getBlob("product");
			stream->read((char *)&list, sizeof(ProductList));
		}
	}
	destroy_db_res();
	m_dbConn->commit();
}

void UserInfoMgr::UpdateProductList( ACE_UINT32 unCharacterID,ACE_UINT32 unProductID,ProductList & list )
{
	if(update_db_connection() == -1)
	{
		return;
	}

	if (list.unCount < RECHARGE_MAX_PRODUCT)
	{
		for (int i=0;i<list.unCount;i++)
		{
			if (list.list[i] == unProductID)
				return;//已经有了 不必更新
		}

		//没有这个商品id 加入
		list.list[list.unCount] = unProductID;
		list.unCount ++;

		m_prep_stmt = m_dbConn->prepareStatement("replace into product_tbl(character_id, product) values(?, ?)");
		if(m_prep_stmt != NULL)
		{
			m_prep_stmt->setInt(1, unCharacterID);

			DBDataBuf data((char *)&list, sizeof(ProductList));
			std::istream is(&data);
			m_prep_stmt->setBlob(2, &is);
			m_db_res = m_prep_stmt->executeQuery();

		}
	}

	destroy_db_res();
	m_dbConn->commit();

}

bool UserInfoMgr::GetVipInfo( ACE_UINT32 unCharacterID,VipInfo & vip )
{
	bool iResult = false;
	if(update_db_connection() == -1)
	{
		return false;
	}

	bool iReturn = true;
	m_prep_stmt = m_dbConn->prepareStatement("select vip_level,vip_amount from character_tbl where character_id=?");
	if(m_prep_stmt != NULL)
	{
		m_prep_stmt->setInt(1, unCharacterID);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res != NULL && m_db_res->next())
		{
			vip.vip_level = m_db_res->getInt("vip_level");
			vip.vip_amount = m_db_res->getInt("vip_amount");
			iResult = true;
		}
	}
	destroy_db_res();
	m_dbConn->commit();

	return iResult;
}

void UserInfoMgr::UpdateVipInfo( ACE_UINT32 unCharacterID,ACE_UINT32 unMoney,VipInfo & vip )
{
	if(update_db_connection() == -1)
	{
		return;
	}
	vip.vip_amount += unMoney;
	//此处计算vip
	UpdateVip(vip);

	m_prep_stmt = m_dbConn->prepareStatement("update character_tbl set vip_level=?,vip_amount = ? where character_id=?");
	if(m_prep_stmt != NULL)
	{
		m_prep_stmt->setInt(1, vip.vip_level);
		m_prep_stmt->setInt(2, vip.vip_amount);
		m_prep_stmt->setInt(3, unCharacterID);
		m_prep_stmt->executeUpdate();
	}

	destroy_db_res();
	m_dbConn->commit();

	this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DO_UPDATE_LIVEL_REQUEST, (char *)&vip, sizeof(VipInfo), OBJ_ID_NONE, ADAPTER_MAP_MGR, unCharacterID);
}

void UserInfoMgr::UpdateVip( VipInfo & vip )
{
	while(true)
	{
		std::map<ACE_UINT32, ACE_UINT32>  &_vipGiftList = GAME_CONFIG_INSTANCE::instance()->m_vipGiftList;//vip礼包列表
		std::map<ACE_UINT32, ACE_UINT32>::const_iterator c_it = _vipGiftList.find(vip.vip_level + 1);
		if (c_it != _vipGiftList.end())
		{
			VipRes * vipRes = (VipRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(c_it->second);//查询是否可以升级
			if(vipRes && (vipRes->m_unRechargeRequired <= vip.vip_amount))//找到了
			{
				vip.vip_level++;
				//vip.vip_amount -= vipRes->m_unRechargeRequired;
			}
			else
				break;
		}
		else
			break;
	}
}


void UserInfoMgr::SendMonthCard( MsgSendMonthCardRequest * request )
{
	MailInfo oMailInfo;
	oMailInfo.m_dwIDinTable = MONTH_CARD_MAIL_TEMPLATE_ID;
	oMailInfo.m_dwCharacterID = request->m_dwCharacterID;
	oMailInfo.m_dwTimeoutDate = request->m_unTime;/* + (7 * 24 * 3600)*/;
	oMailInfo.m_aMailAttachment[0].m_dwItemID = RES_CURRENCY_MONEY;
	oMailInfo.m_aMailAttachment[0].m_dwItemCount = 120;
	insert_mail_info(oMailInfo);
}

int UserInfoMgr::get_special_player( PublicPlayerInfo *list[],ACE_UINT32 unMapID )
{
	ACE_UINT32 cid = 0;
	switch(unMapID)
	{
	case 0x0F010101:
		cid = 99901;break;
	case 0x0F010201:
		cid = 99905;break;
	case 0x0F010301:
		cid = 99907;break;
	case 0x0F010401:
		cid = 99903;break;
	case 0x0F010501:
		cid = 99902;break;
	case 0x0F010601:
		cid = 99906;break;
	case 0x0F010701://进入
		cid = 99908;break;
	default:
		cid = 0;break;
	}

	if (cid > 0)
	{
		std::map<ACE_UINT32, PublicPlayerInfo *>::iterator itMap = GAME_CONFIG_INSTANCE::instance()->m_oRobotTeam.find(cid);
		if (itMap != GAME_CONFIG_INSTANCE::instance()->m_oRobotTeam.end())
		{
			list[0] = itMap->second;
			return 1;
		}
	}

	return 0;
}

void UserInfoMgr::Init_Honour_Level()
{
	if(update_db_connection() == -1)
	{
		printf("get Honour Level failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT character_id,honour FROM pvp_tbl WHERE honour >= 0");
		if(m_prep_stmt == NULL)
		{
			printf("get Honour Level failed2!\n");
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		//m_unGlobleGiftBagCodeCount = 0;
		HLInfo info;
		while(m_db_res->next())
		{
			info.m_characterID = m_db_res->getUInt("character_id");
			info.m_honour = m_db_res->getInt("honour");
			m_honorLevel.add(info);
		}

		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("Init_Honor_Level exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::DoLoadHL( std::vector<HLInfo> & ver )
{
	if(update_db_connection() == -1)
	{
		printf("get DoLoadHL failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT character_id,honour FROM pvp_tbl WHERE honour >= 0");
		if(m_prep_stmt == NULL)
		{
			printf("DoLoadHL failed2!\n");
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		ver.clear();
		HLInfo info;
		while(m_db_res->next())
		{
			info.m_characterID = m_db_res->getUInt("character_id");
			info.m_honour = m_db_res->getInt("honour");
			ver.push_back(info);
		}

		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("DoLoadHL exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::DoClearHL()
{
	m_nowHLinfoMap.clear();
	if(update_db_connection() == -1)
	{
		printf("get DoLoadHL failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("UPDATE pvp_tbl set honour = -1,win_lost = 0,user_list=NULL,fight_list=NULL");
		if(m_prep_stmt == NULL)
			return;

		m_prep_stmt->executeUpdate();

		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("DoLoadHL exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

HLInfo UserInfoMgr::GetNowHLinfo( ACE_UINT32 characterID )
{
	HLInfo info;
	std::map<ACE_UINT32,HLInfo>::const_iterator c_it = m_nowHLinfoMap.find(characterID);
	if (c_it != m_nowHLinfoMap.end())
	{
		info = c_it->second;
	}
	else//从数据库里面读取
	{
		if(update_db_connection() == -1)
		{
			printf("get DoLoadHL failed1!\n");
			return info;
		}
		try
		{
			m_prep_stmt = m_dbConn->prepareStatement("SELECT honour FROM pvp_tbl WHERE character_id = ?");
			if(m_prep_stmt == NULL)
			{
				printf("DoLoadHL failed2!\n");
				return info;
			}
			m_prep_stmt->setInt(1,characterID);
			m_db_res = m_prep_stmt->executeQuery();

			
			if(m_db_res->next())
			{
				info.m_characterID = characterID;
				info.m_honour = m_db_res->getInt("honour");
				info.isRobt = false;
			}

			destroy_db_res();

			m_dbConn->commit();
		}
		catch(SQLException &e)
		{
			printf("DoLoadHL exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
		}
	}

	return info;
}

void UserInfoMgr::UpdateHLinfo( HLInfo & info )
{
	m_nowHLinfoMap[info.m_characterID] = info;

	if(update_db_connection() == -1)
	{
		printf("get UpdateHLinfo failed1!\n");
		return;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("update pvp_tbl set honour=? where character_id=?");
		if(m_prep_stmt)
		{
			m_prep_stmt->setInt(1,info.m_honour);
			m_prep_stmt->setInt(2,info.m_characterID);
			m_prep_stmt->executeUpdate();

			destroy_db_res();
			m_dbConn->commit();
		}

	}
	catch(SQLException &e)
	{
		printf("DoLoadHL exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

bool UserInfoMgr::GetHLInfoArrayFromDB( HLInfoArray & _array,ACE_UINT32 characterID )
{
	bool isFind = false;
	if(update_db_connection() == -1)
	{
		printf("get GetHLInfoArrayFromDB failed1!\n");
		return false;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT user_list FROM pvp_tbl WHERE character_id = ?");
		if(m_prep_stmt == NULL)
		{
			printf("DoLoadHL failed2!\n");
			return false;
		}
		m_prep_stmt->setInt(1,characterID);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			isFind = true;
			std::istream *stream = m_db_res->getBlob("user_list");
			char *p = (char *)&_array;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}
		}

		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("GetHLInfoArrayFromDB exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

	return isFind;
}

bool UserInfoMgr::UpdateHLInfoArrayToDB( const HLInfoArray & _array,ACE_UINT32 characterID )
{
	if(update_db_connection() == -1)
	{
		return false;
	}
	try
	{
		DBDataBuf data((char *)&_array, sizeof(HLInfoArray));
		std::istream is(&data);

		m_prep_stmt = m_dbConn->prepareStatement("UPDATE pvp_tbl SET user_list = ? WHERE character_id = ?");
		m_prep_stmt->setBlob(1, &is);
		m_prep_stmt->setUInt(2, characterID);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("insert_mail_info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

}

void UserInfoMgr::UpdateFightRecordInfoToDB( FightRecordInfo & FRinfo,bool isRoobt )
{
	//更新挑战者
	{
		FightRecordInfoList info;
		ACE_UINT32 winLost = 0;
		if (GetFightRecordInfoList(info,winLost,FRinfo.from.m_characterID))
		{
			if (FRinfo.isWin)
			{
				ACE_UINT32 win = (winLost & 0x0FFFF) + 1; 
				ACE_UINT32 lost = ((winLost>>16)& 0x0FFFF);
				winLost = ((lost<<16) + win);
			}
			else
			{
				ACE_UINT32 win = (winLost & 0x0FFFF) ; 
				ACE_UINT32 lost = ((winLost>>16)& 0x0FFFF) + 1;
				winLost = ((lost<<16) + win);
			}

			if (info.unCount < MAX_FightRecordInfo_LEN)
			{
				info.info[info.unCount] = FRinfo;
				info.unCount++;
			}
			else
			{
				for (int i=1;i<MAX_FightRecordInfo_LEN;i++)
				{
					info.info[i-1] = info.info[i]; 
				}
				info.info[MAX_FightRecordInfo_LEN-1] = FRinfo;
				info.unCount = MAX_FightRecordInfo_LEN;
			}

			UpdateFightRecordInfoList(info,winLost,FRinfo.from.m_characterID);
		}
	}

	//更新防守者
	if (!isRoobt)
	{
		FightRecordInfoList info;
		ACE_UINT32 winLost = 0;
		if (GetFightRecordInfoList(info,winLost,FRinfo.to.m_characterID))
		{
			if (FRinfo.isWin)
			{
				ACE_UINT32 win = (winLost & 0x0FFFF); 
				ACE_UINT32 lost = ((winLost>>16)& 0x0FFFF) + 1;
				winLost = ((lost<<16) | win);
			}
			else//防守获胜
			{
				ACE_UINT32 win = (winLost & 0x0FFFF) + 1 ; 
				ACE_UINT32 lost = ((winLost>>16)& 0x0FFFF);
				winLost = ((lost<<16) | win);
			}

			if (info.unCount < MAX_FightRecordInfo_LEN)
			{
				info.info[info.unCount] = FRinfo;
				info.unCount++;
			}
			else
			{
				for (int i=1;i<MAX_FightRecordInfo_LEN;i++)
				{
					info.info[i-1] = info.info[i]; 
				}
				info.info[MAX_FightRecordInfo_LEN-1] = FRinfo;
				info.unCount = MAX_FightRecordInfo_LEN;
			}

			UpdateFightRecordInfoList(info,winLost,FRinfo.to.m_characterID);
		}
	}
}

bool UserInfoMgr::GetFightRecordInfoList( FightRecordInfoList & info,ACE_UINT32& winLost,ACE_UINT32 characterID )
{
	ZeroVar(info);
	bool isFind = false;
	winLost = 0;

	if(update_db_connection() == -1)
	{
		printf("get GetFightRecordInfoList failed1!\n");
		return false;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT win_lost,fight_list FROM pvp_tbl WHERE character_id = ?");
		if(m_prep_stmt == NULL)
		{
			printf("DoLoadHL failed2!\n");
			return false;
		}
		m_prep_stmt->setInt(1,characterID);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			winLost = m_db_res->getInt("win_lost");
			std::istream *stream = m_db_res->getBlob("fight_list");
			char *p = (char *)&info;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}
		}
		
		destroy_db_res();

		m_dbConn->commit();

		isFind = true;
	}
	catch(SQLException &e)
	{
		printf("GetFightRecordInfoList exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}

	return isFind;
}

bool UserInfoMgr::UpdateFightRecordInfoList( FightRecordInfoList & info,ACE_UINT32& winLost,ACE_UINT32 characterID )
{
	if(update_db_connection() == -1)
	{
		return false;
	}
	try
	{
		DBDataBuf data((char *)&info, sizeof(FightRecordInfoList));
		std::istream is(&data);

		m_prep_stmt = m_dbConn->prepareStatement("UPDATE pvp_tbl SET win_lost=?,fight_list=? WHERE character_id = ?");
		m_prep_stmt->setUInt(1, winLost);
		m_prep_stmt->setBlob(2, &is);
		m_prep_stmt->setUInt(3, characterID);
		m_prep_stmt->executeUpdate();
		destroy_db_res();

		m_dbConn->commit();

		return true;
	}
	catch(SQLException &e)
	{
		printf("UpdateFightRecordInfoList exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
	return false;
}

void UserInfoMgr::update_BS_info( BadgeShuxingS& infos,ACE_UINT32 unCharacterID )
{
	if(update_db_connection() == -1)
	{
		return ;
	}
	try
	{
		DBDataBuf data((char *)&infos, sizeof(BadgeShuxingS));
		std::istream is(&data);

		m_prep_stmt = m_dbConn->prepareStatement("REPLACE into badge_info_tbl(character_id ,info) values(?,?)");
		m_prep_stmt->setUInt(1, unCharacterID);
		m_prep_stmt->setBlob(2, &is);
		m_prep_stmt->executeUpdate();
		destroy_db_res();
		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("update_BS_info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::Get_BS_info( BadgeShuxingS& infos,ACE_UINT32 unCharacterID )
{
	if(update_db_connection() == -1)
	{
		return ;
	}
	try
	{
		m_prep_stmt = m_dbConn->prepareStatement("SELECT info FROM badge_info_tbl WHERE character_id = ?");
		if(m_prep_stmt == NULL)
		{
			printf("Get_BS_info failed2!\n");
			return ;
		}
		m_prep_stmt->setInt(1,unCharacterID);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			std::istream *stream = m_db_res->getBlob("info");
			char *p = (char *)&infos;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}
		}

		destroy_db_res();
		m_dbConn->commit();
	}
	catch(SQLException &e)
	{
		printf("Get_BS_info exception = %s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
}

void UserInfoMgr::CheckSetupMax( PublicPlayerInfo *info )
{
	if (info)
	{
		static int max = GAME_CONFIG_INSTANCE::instance()->g_maxSetup;
		for(int i=0;i<info->characterInfo.pveTeam.unCount && i<MAX_PLAYER_SELECTED_COUNT ;i++)
		{
			if (info->characterInfo.pveTeam.playerList[i].unStep > max)
			{
				info->characterInfo.pveTeam.playerList[i].unStep = max;
			}
		}
	}
}
