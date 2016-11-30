#include "HonorLevel.h"
#include "..\ace\os_include\os_assert.h"
#include "..\GameBase\Common\GameUtils.h"
#include "UserInfoMgr.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\GameBase\res\BehaviorRes.h"
#include "..\GameBase\res\ItemResMgr.h"

CHonorLevel::CHonorLevel()
{
	m_flag = HL_Flag_init;
	m_pUserInfoCallback = NULL;
	Clear();
	m_isRestart = true;
	m_max = GAME_CONFIG_INSTANCE::instance()->m_oHLmax;
	m_min = GAME_CONFIG_INSTANCE::instance()->m_oHLmin;
}

void CHonorLevel::add( HLInfo &info)
{
	assert(m_characterKey.find(info.m_characterID) == m_characterKey.end());
	if(info.m_honour >= 0)
	{
		m_characterKey.insert(info.m_characterID);//加入
		InsertionSort(info);
		UpdateLevelMap(info,true);
	}
	
}

void CHonorLevel::update(HLInfo & info,ACE_INT32 oldHonour)
{
	if (m_isRestart)
		return;
	
	if (m_characterKey.find(info.m_characterID) == m_characterKey.end())//加入新的
	{
		if(info.m_honour >= 0)
		{
			m_characterKey.insert(info.m_characterID);//加入
			InsertionSort(info);
			UpdateLevelMap(info,true);
		}
	}
	else
	{
		ACE_ASSERT(m_unCount <= MAX_HONOUR_LEVEL_COUNT);
		if (m_unCount == 0)
		{
			m_list[m_unCount] = info;
			m_unCount++;
			return;
		}

		if (m_unCount > MAX_HONOUR_LEVEL_COUNT)
			m_unCount = MAX_HONOUR_LEVEL_COUNT;

		if (m_list[m_unCount-1].m_honour <= oldHonour || m_list[m_unCount-1].m_honour <= info.m_honour)//有更新
		{
			InsertionSort(info);
		}
		else if (m_unCount < MAX_HONOUR_LEVEL_COUNT )
		{
			InsertionSort(info);
		}
		
		if (oldHonour>=0)
		{
			HLInfo _info;
			_info.m_characterID = info.m_characterID;
			_info.m_honour = oldHonour;
			UpdateLevelMap(_info,false);//减掉老的
		}

		UpdateLevelMap(info,true);//添加新的
	}

	//insert sort

}

void CHonorLevel::Clear()
{
	m_unCount = 0;
	m_levelMap.clear();
	m_characterKey.clear();
	m_verHLinfo.clear();
	m_honorlevelMap.clear();
	if (m_pUserInfoCallback)
		m_pUserInfoCallback->m_nowHLinfoMap.clear();
}

void CHonorLevel::InsertionSort( HLInfo & info)
{
	bool isAdd = true;
	for (int i=0;i<m_unCount;i++)
	{
		if (m_list[i].m_characterID == info.m_characterID)
		{
			m_list[i] = info;
			isAdd = false;
			break;
		}
	}

	int len = m_unCount;
	if (isAdd)
	{
		m_list[m_unCount] = info;
		if (m_unCount < MAX_HONOUR_LEVEL_COUNT)
			m_unCount ++;
		++len;
	}

	//插入排序
	for (int j=1; j<len; j++)  
	{  
		HLInfo key = m_list[j];  
		int i = j-1;  
		while (i>=0 && m_list[i].m_honour  <  key.m_honour)  
		{  
			m_list[i+1] = m_list[i];  
			i--;
		}  
		m_list[i+1] = key; 
	}
}

void CHonorLevel::DoOnTimerOut()
{
	int dayTime = GameUtils::get_day_time(GameUtils::get_utc());
	int weakDay = GameUtils::get_week(GameUtils::get_utc());

	//每日奖励
	if (dayTime > DAY_TIME_SETTLE_STARTEX && dayTime <= DAY_TIME_SETTLE_ENDEX)//21点 ~ 21：15点为结算时间
	{
		switch(m_flag)
		{
			case HL_Flag_Clear://清除状态
				 break;
			case HL_Flag_init ://初始化 只可能是服务器重启
				{
					m_flag = HL_Flag_start;//继续 开始
				}break;
			case HL_Flag_start ://进行中
				{
					m_isRestart = false;
					m_flag = HL_Flag_end;
				}break;
			case HL_Flag_end://完成中 等待发奖 1阶段
				{
					DoLoadHL();
					m_flag = HL_Flag_end_ex;
				}break;
			case HL_Flag_end_ex://完成中 等待发奖 2阶段
				{
					DoSendDayReword();//发送每日奖励
					m_flag = HL_Flag_get_reword;
				}break;
			case HL_Flag_get_reword://已完成发奖
				{
					m_flag = HL_Flag_Clear;//等待开始
				}break;
		}
	}
	else if((weakDay == 0) && dayTime > DAY_TIME_SETTLE_START && dayTime <= (DAY_TIME_SETTLE_END - 60))//23点30分 ~ 0点为结算时间 赛季奖励
	{
		switch(m_flag)
		{
		case HL_Flag_Clear://清除状态
			break;
		case HL_Flag_init ://初始化 只可能是服务器重启
			{
				m_flag = HL_Flag_start;//继续 开始
			}break;
		case HL_Flag_start ://进行中
			{
				m_isRestart = true;
				m_flag = HL_Flag_end;
			}break;
		case HL_Flag_end://完成中 等待发奖 1阶段
			{
				DoLoadHL();
				m_flag = HL_Flag_end_ex;
			}break;
		case HL_Flag_end_ex://完成中 等待发奖 2阶段
			{
				DoSendWeakReword();//发送赛季奖励
				m_flag = HL_Flag_get_reword;
			}break;
		case HL_Flag_get_reword://已完成发奖
			{
				m_flag = HL_Flag_Clear;//等待开始
			}break;
		}

	}
	else
	{
		switch(m_flag)
		{
		case HL_Flag_start ://进行中
			 break;
		case HL_Flag_init ://等待开始只可能是服务器重启
			{
				m_isRestart = false;
				m_flag = HL_Flag_start;//继续 开始
			}break;
		case HL_Flag_Clear ://已完成发奖
			{
				if (m_isRestart)//一个赛季结束了
				{
					Clear();
					if (m_pUserInfoCallback)
						m_pUserInfoCallback->DoClearHL();
				}
				m_isRestart = false;
				m_flag = HL_Flag_start;//继续 开始
			}break;
		case HL_Flag_end://完成中
			{
				assert(false);
				m_flag = HL_Flag_start;//继续 开始
			}break;
		case HL_Flag_end_ex://完成中 等待发奖
			{
				assert(false);
				m_flag = HL_Flag_start;//继续 开始
			}break;
		case HL_Flag_get_reword://已完成发奖
			{
				assert(false);
				m_flag = HL_Flag_start;//继续 开始
			}break;
		}
	}
}

bool CHonorLevel::DoSendWeakReword()
{
	int weakDay = GameUtils::get_week(GameUtils::get_utc());
	if (weakDay == 0)//赛季奖励
	{
		DoSendRankReword();//发送赛季奖励
		m_isRestart = true;
		return true;
	}
	else
	{
		m_isRestart = false;
		return false;
	}
	
	return false;
}

bool CHonorLevel::DoLoadHL()
{
	m_verHLinfo.clear();
	if (m_pUserInfoCallback)
	{
		m_pUserInfoCallback->DoLoadHL(m_verHLinfo);
		std::sort(m_verHLinfo.begin(),m_verHLinfo.end(),std::greater<HLInfo>());//大到小排序
	}
	return true;
}

void CHonorLevel::DoSendDayReword()
{
	const std::map<ACE_UINT32,HonorLevel> & oHonorLevel = GAME_CONFIG_INSTANCE::instance()->m_oHonorLevel;
	std::map<ACE_UINT32,HonorLevel>::const_iterator _it = oHonorLevel.begin();
	std::vector<HLInfo>::const_iterator c_it = m_verHLinfo.begin();

	while(_it != oHonorLevel.end() && c_it!= m_verHLinfo.end())
	{
		while(_it != oHonorLevel.end() && c_it->m_honour < _it->second.unlevelupHonor)//找到下一个满足要求的点
			_it++;

		if(_it != oHonorLevel.end())
		{
			assert(c_it->m_honour >= _it->second.unlevelupHonor);
			OnSendMail(*c_it,_it->second.undayReward,FRIENDSHIP_MAIL_PVP_DAY,c_it->m_honour);
			c_it++;
		}
	}

}

void CHonorLevel::DoSendRankReword()
{
	const std::map<ACE_UINT32,HonorRank> & oHonorRank = GAME_CONFIG_INSTANCE::instance()->m_oHonorRank;
	std::map<ACE_UINT32,HonorRank>::const_iterator _it = oHonorRank.begin();
	std::vector<HLInfo>::const_iterator c_it = m_verHLinfo.begin();

	int n = 0;
	while(_it != oHonorRank.end() && c_it!= m_verHLinfo.end())
	{
		while(_it != oHonorRank.end() && n >= _it->second.unrank_limited)//找到下一个满足要求的点
			_it++;

		if(_it != oHonorRank.end())
		{
			assert(n < _it->second.unrank_limited);
			OnSendMail(*c_it,_it->second.season_reward,FRIENDSHIP_MAIL_PVP_RANK,n+1);
			c_it++;
			n++;
		}
		else
			break;
	}
}

void CHonorLevel::OnSendMail(const HLInfo & info,ACE_INT32 behaviorID,ACE_UINT32 unMailId,ACE_UINT32 parm )
{
	BehaviorRes *res = (BehaviorRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(behaviorID);//获得奖励
	if (res && m_pUserInfoCallback)
	{
		MailInfo mail;
		ZeroVar(mail);
		if(TeamRankMgr::GetMailInfo(mail,res->m_reward,info.m_characterID,unMailId))
		{
			sprintf(mail.m_strBody, "%d",parm);
			m_pUserInfoCallback->insert_mail_info(mail);
		}
	}
}

void CHonorLevel::UpdateLevelMap(const HLInfo & honour,bool isAdd )
{
	if (honour.m_honour < 0)
		return;

	if (isAdd)
	{
		m_levelMap[honour.m_honour]++;
	}
	else
	{
		assert(m_levelMap[honour.m_honour] > 0);
		m_levelMap[honour.m_honour]--;
	}

	UpdateHonorLevelMap(honour,isAdd);
}

void CHonorLevel::UpdateHonorLevelMap(const HLInfo & honour,bool isAdd )
{
	if (honour.m_honour < 0)
		return;

	ACE_INT32 level = GetHLevel(honour.m_honour);
	if (level<0)
		return;

	if (isAdd)
	{
		m_honorlevelMap[level].push_back(honour);
	}
	else
	{
		std::vector<HLInfo> & ver = m_honorlevelMap[level];

		bool isFind = false;
		std::vector<HLInfo>::iterator it= ver.begin();
		while(it != ver.end())
		{
			if (it->m_characterID == honour.m_characterID)
			{
				isFind = true;
				ver.erase(it);
				break;
			}
			it++;
		}

		assert(isFind);
	}
}


int CHonorLevel::GetRanking( ACE_INT32 honour )
{
	int nranking = 1;
	if (honour < 0)
		return -1;
	else
	{
		std::map<ACE_INT32,ACE_UINT32 >::const_reverse_iterator c_it = m_levelMap.rbegin();
		while(c_it != m_levelMap.rend())
		{
			if (c_it->first > honour)
			{
				nranking += c_it->second;
			}
			else
				break;

			c_it++;
		}

		return nranking;
	}
}

ACE_INT32 CHonorLevel::GetHLevel( ACE_INT32 honour )
{
	if(honour < 0)
		return -1;

	const std::map<ACE_UINT32,HonorLevel> & oHonorLevel = GAME_CONFIG_INSTANCE::instance()->m_oHonorLevel;
	std::map<ACE_UINT32,HonorLevel>::const_iterator c_it = oHonorLevel.begin();

	while(c_it != oHonorLevel.end())
	{
		if (honour >= c_it->second.unlevelupHonor)
		{
			return c_it->second.unLevel;
		}
		
		c_it++;
	}

	return -1;
}

bool CHonorLevel::ChoiceFightRoole( const HLInfo & info,HLInfoArray & _array,HLInfo * quitList)
{
	std::set<ACE_UINT32> realQuitList;
	std::set<ACE_UINT32> roobtQuitList;

	realQuitList.insert(info.m_characterID);//加入自己
	for(int i=0;i<3;i++)
	{
		if (quitList[i].m_characterID > 0)
		{
			if (quitList[i].isRobt)//机器人
				roobtQuitList.insert(quitList[i].m_characterID);
			else
				realQuitList.insert(quitList[i].m_characterID);
		}
		else
			break;
	}

	_array.uncount = 0;
	assert(info.m_honour >= 0);
	
	ACE_INT32 level = GetHLevel(info.m_honour);
	if (level >= 0)
	{
		//找相等的和更大的
		{
			std::map<ACE_INT32,std::vector<HLInfo> >::const_iterator c_it = m_honorlevelMap.begin();
			while(c_it != m_honorlevelMap.end())
			{
				if ((c_it->first >= level) && c_it->second.size()>0)
				{
					_array.m_array[_array.uncount] = c_it->second.at(ACE_OS::rand() % c_it->second.size());
					//if (_array.m_array[_array.uncount].m_characterID != info.m_characterID)
					if(TryAdd(realQuitList,_array.m_array[_array.uncount].m_characterID))
					{
						if (m_pUserInfoCallback)
						{
							PublicPlayerInfo * p = m_pUserInfoCallback->getFriendInfo(_array.m_array[_array.uncount].m_characterID);
							if (p)
							{
								_array.playerinfo[_array.uncount] = p->characterInfo;
								_array.playerinfo[_array.uncount].pvpTeam.unPoint = _array.m_array[_array.uncount].m_honour; 
								_array.uncount++;
								if (_array.uncount == 2)
									break;
							}
						}

					}
				}

				c_it++;
			}
		}

		//找小的
		{
			std::map<ACE_INT32,std::vector<HLInfo> >::const_reverse_iterator c_it = m_honorlevelMap.rbegin();
			while(c_it != m_honorlevelMap.rend())
			{
				if ((c_it->first <= level-1) && c_it->second.size()>0)
				{
					_array.m_array[_array.uncount] = c_it->second.at(ACE_OS::rand() % c_it->second.size());
					//if (_array.m_array[_array.uncount].m_characterID != info.m_characterID)
					if(TryAdd(realQuitList,_array.m_array[_array.uncount].m_characterID))
					{
						if (m_pUserInfoCallback)
						{
							PublicPlayerInfo * p = m_pUserInfoCallback->getFriendInfo(_array.m_array[_array.uncount].m_characterID);
							if (p)
							{
								_array.playerinfo[_array.uncount] = p->characterInfo; 
								_array.playerinfo[_array.uncount].pvpTeam.unPoint = _array.m_array[_array.uncount].m_honour;
								_array.uncount++;
								if (_array.uncount == 3)
									break;
							}
						}
					}
				}

				c_it++;
			}
		}

// 		//最后更新
// 		if (_array.uncount < 3)
// 		{
// 			ChoiceFightRooleEx(_array,info.m_characterID);
// 		}

		//如果不够：找机器人
		if (_array.uncount < 3)
		{
			if (m_pUserInfoCallback)
			{
				PublicPlayerInfo * player = m_pUserInfoCallback->getFriendInfo(info.m_characterID);
				if (player)
				{
					std::map<ACE_UINT32, std::pair<std::vector<UINT32>, std::vector<PublicPlayerInfo *> > >::const_iterator itMap = GAME_CONFIG_INSTANCE::instance()->m_oLevelRobotTeam.find(player->characterInfo.unLevel);

					if (itMap != GAME_CONFIG_INSTANCE::instance()->m_oLevelRobotTeam.end())
					{
						std::vector<PublicPlayerInfo *>::const_iterator c_it = itMap->second.second.begin();
						int ranum = 0;
						if (itMap->second.second.size()>6)
						{
							ranum = (ACE_OS::rand() % (itMap->second.second.size()-6));
							c_it += ranum;
						}
						while(c_it != itMap->second.second.end() && _array.uncount < 3)
						{
							if (TryAdd(roobtQuitList,(*c_it)->characterInfo.unItemID))
							{
								HLInfo _info;
								_info.isRobt = true;
								_info.m_characterID = (*c_it)->characterInfo.unItemID;
								_info.m_honour = 1;
								_array.m_array[_array.uncount] = _info;
								_array.playerinfo[_array.uncount] = (*c_it)->characterInfo; 
								_array.playerinfo[_array.uncount].pvpTeam.unPoint = 1200;
								_array.uncount++;
							}
							c_it++;
						}
					}
				}
			}
		}

		return true;
	}
	
	return false;
}

void CHonorLevel::SetSuper( UserInfoMgr * pSuper )
{
	m_pUserInfoCallback = pSuper;
}

void CHonorLevel::ChoiceFightRooleEx( HLInfoArray & _array,ACE_UINT32 _characterID )
{
	if (_array.uncount == 3)
		return;

	std::map<ACE_INT32,std::vector<HLInfo> >::const_iterator c_it = m_honorlevelMap.begin();
	while(c_it != m_honorlevelMap.end())
	{
		if (c_it->second.size() > 0)
		{
			int n = ACE_OS::rand() % c_it->second.size();
			if (n>0)
				n--;

			for (int i=n;i<c_it->second.size();i++)
			{
				HLInfo info = c_it->second.at(i);
				bool isHave = false;
				for (int j=0;j<_array.uncount;j++)
				{
					if (_array.m_array[j].m_characterID == info.m_characterID || info.m_characterID == _characterID)
					{
						isHave = true;
						break;
					}
				}
				if (!isHave && info.m_characterID != _characterID)
				{
					_array.m_array[_array.uncount] = info;
					if (m_pUserInfoCallback)
					{
						PublicPlayerInfo * p = m_pUserInfoCallback->getFriendInfo(_array.m_array[_array.uncount].m_characterID);
						if (p)
						{
							_array.playerinfo[_array.uncount] = p->characterInfo; 
							_array.playerinfo[_array.uncount].pvpTeam.unPoint = _array.m_array[_array.uncount].m_honour;
							_array.uncount++;
							if (_array.uncount == 3)
								return;
						}
					}
				}
			}
		}
		c_it++;
	}
}

ACE_UINT32 CHonorLevel::GetSumNum()
{
	return m_characterKey.size();
}

bool CHonorLevel::TryAdd( std::set<ACE_UINT32> & quitList,ACE_UINT32 id )
{
	if (quitList.find(id) != quitList.end())//已经有此人了
	{
		return false;
	}
	else
	{
		quitList.insert(id);
		return true;
	}

}

