#include "GameUtils.h"

#include "ace\Date_Time.h"
#include "ace\Time_Value.h"
#include "ace\OS_NS_sys_time.h"
#include "ace\OS_NS_string.h"
#include "ace\OS_NS_stdlib.h"

#include "..\res\DropRes.h"

#include "..\res\ItemResMgr.h"
//#include "..\res\ArenaConfig.h"
#define SESSION_CHARACTER_TBL_LEN 62
static char *g_session_character_tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-=";

#define GMT_OFFSET (8 * 60 * 60)

#define WEEK_OFFSET 3 //星期4

ACE_UINT32 GameUtils::get_utc()//秒
{
	ACE_Time_Value v = ACE_OS::gettimeofday();

	ACE_UINT64 ret = 0;

	v.to_usec(ret);
	//microseconds
	return (ACE_UINT32)(ret / 1000000);
}

void GameUtils::get_current_time_str(char *str)
{
	//ACE_Time_Value v = ACE_OS::gettimeofday();

	ACE_Date_Time tvTime(ACE_OS::gettimeofday());

	ACE_OS::sprintf(str, "%02d-%02d-%02d %02d:%02d:%02d", tvTime.year(), tvTime.month(), tvTime.day(), tvTime.hour(), tvTime.minute(), tvTime.second());
}

void GameUtils::get_current_day_str(char *str)
{
	ACE_Date_Time tvTime(ACE_OS::gettimeofday());

	ACE_OS::sprintf(str, "%02d-%02d-%02d", tvTime.year(), tvTime.month(), tvTime.day());
}

int GameUtils::get_day_different(ACE_UINT32 t0, ACE_UINT32 t1)
{
	//ACE_UINT64 v = 1000000L;
	ACE_UINT32 v = 24L * 60L * 60L;

	t0 = (t0 + GMT_OFFSET) / v;
	t1 = (t1 + GMT_OFFSET) / v;

	int s = 0;

	if(t0 > t1)
	{
		s = (int)(t0 - t1);
	}
	else if(t0 < t1)
	{
		s = (int)(t1 - t0);
		s = -s;
	}

	return s;
}

int GameUtils::get_time_offset(ACE_UINT32 t0, ACE_UINT32 t1, ACE_UINT32 offset, ACE_UINT32 precision)
{
	t0 = (t0 + GMT_OFFSET - offset) / precision;
	t1 = (t1 + GMT_OFFSET - offset) / precision;

	int s = 0;

	if(t0 > t1)
	{
		s = (int)(t0 - t1);
	}
	else if(t0 < t1)
	{
		s = (int)(t1 - t0);
		s = -s;
	}

	return s;
}

int GameUtils::get_week_count(ACE_UINT32 unCurrentTime)
{
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) / v;

	t = t + WEEK_OFFSET;

	return (t / 7);
}

int GameUtils::get_day_time(ACE_UINT32 unCurrentTime)
{
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) % v;
	return t;
}

int GameUtils::get_week_time(ACE_UINT32 unCurrentTime)
{
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = unCurrentTime + GMT_OFFSET + WEEK_OFFSET * v;

	t = t % (7 * v);

	return t;
}

int GameUtils::get_week(ACE_UINT32 unCurrentTime)
{
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) / v;

	t = t + WEEK_OFFSET + 1;

	return (t % 7);
}

ACE_UINT32 GameUtils::get_pvp_season_id(ACE_UINT32 unCurrentTime)
{
	return get_week_count(unCurrentTime);

	/*ACE_UINT32 v = 5L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) / v;

	return t;*/
}

char *GameUtils::get_pvp_season_tbl_name(ACE_UINT32 unSeasonID)
{
	static char *season_tbl0 = "pvp_season_tbl0";
	static char *season_tbl1 = "pvp_season_tbl1";

	if(unSeasonID % 2 == 0)
	{
		return season_tbl0;
	}
	
	return season_tbl1;
}

bool GameUtils::can_commit_pvp_result(ACE_UINT32 unCurrentTime)
{
	
	int t = GameUtils::get_week_time(unCurrentTime);

	if(t < 9 * ( 60 * 60) || t > ((6 * 24 + 22) * 60 * 60))
	{
		return false;
	}
	/*
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) % v;

	if(t < 9 * 60 * 60 || t > (23 * 60 * 60 + 30 * 60))
	{
		return false;
	}
	*/

	return true;
}

bool GameUtils::can_match_pvp_opponent(ACE_UINT32 unCurrentTime)
{
	
	int t = GameUtils::get_week_time(unCurrentTime);

	if(t < 9 * ( 60 * 60) || t > ((6 * 24 + 20) * 60 * 60))
	{
		return false;
	}
	/*
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET) % v;

	if(t < 9 * 60 * 60 || t > 23 * 60 * 60)
	{
		return false;
	}
	*/

	return true;
}

ACE_UINT32 GameUtils::get_rank(ACE_UINT32 unOrder, ACE_UINT32 unCount)
{
	if(unCount <= 0)
	{
		return 0;
	}

	static ACE_UINT32 rank_id_list[] = {0x22000001, 0x22000002, 0x22000003, 0x22000004, 0x22000005, 0x22000006, 0x22000007, 0x22000008};
	
	int idx = 0;

	if(unOrder == 0)
	{
		idx = 0;
	}
	else if(unOrder == 1)
	{
		idx = 1;
	}
	else if(unOrder == 2)
	{
		idx = 2;
	}
	else if(unOrder < 10)
	{
		idx = 3;
	}
	else if(unOrder < 50)
	{
		idx = 4;
	}
	else if(unOrder < 100)
	{
		idx = 5;
	}
	else if(unOrder < 500)
	{
		idx = 6;
	}
	else
	{
		idx = 7;
	}

	/*
	else if(unOrder <= 3)
	{
		idx = 3;
	}
	else if(unOrder <= 10)
	{
		idx = 4;
	}
	else if(unOrder <= 50)
	{
		idx = 5;
	}
	else if(unOrder <= 100)
	{
		idx = 6;
	}
	else if(unOrder <= 500)
	{
		idx = 7;
	}
	else
	{
		idx = 8;
	}
	*/
/*	if(unOrder == 0)
	{
		idx = 0;
	}
	else if(unOrder < 10)
	{
		idx = 1;
	}
	else if(unOrder < 100)
	{
		idx = 2;
	}
	else
	{
		int t = unOrder * 100 / unCount;

		if(t < 2)
		{
			idx = 3;
		}
		else if(t < 20)
		{
			idx = 4;
		}
		else if(t < 50)
		{
			idx = 5;
		}
		else if(t < 80)
		{
			idx = 6;
		}
		else
		{
			idx = 7;
		}
	}
*/
	return rank_id_list[idx];
}

bool GameUtils::is_hit(float fRate)
{
	int m = (int)(fRate * 10000);
	int n = m % 100;
	m = m / 100;

	int t = ACE_OS::rand() % 100;

	if(t < m)
	{
		return true;
	}
	else if(t == m)
	{
		t = ACE_OS::rand() % 100;
		if(t < n)
		{
			return true;
		}
	}

	return false;
}


void GameUtils::reset_reward(RewardInfo &reward)
{
	ACE_OS::memset(&reward, 0, sizeof(RewardInfo));
}



int GameUtils::get_map_unlock_flag(ACE_UINT32 unFlag, int level)
{
	
	int t = (unFlag >> ((level - 1) / 2 * 4)) & 0x1;
	return t;
	/*
	int t = unFlag & 0x01;
	return t;
	*/
}

int GameUtils::set_map_unlock_flag(ACE_UINT32 unFlag, int new_flag, int level)
{
	int t = 0x01 << ((level - 1) / 2 * 4);
	t = ~t;
	unFlag = unFlag & t;
	
	t = new_flag << ((level - 1) / 2 * 4);
	t = unFlag | t;
	return t;
}

int GameUtils::get_map_star(ACE_UINT32 unFlag, int level)
{
	int t = (unFlag >> ((level - 1) / 2 * 4 + 1)) & 0x7;
	return t;
}

int GameUtils::set_map_star(ACE_UINT32 unFlag, int star, int level)
{
	int t = 0x07 << ((level - 1) / 2 * 4 + 1);
	t = ~t;
	unFlag = unFlag & t;

	t = star << ((level - 1) / 2 * 4 + 1);
	t = unFlag | t;
	return t;
}

int GameUtils::get_map_star_count(ACE_UINT32 unFlag, int level)
{
	int t = get_map_star(unFlag, level);

	int c = 0;
	int i;
	for(i = 0;i < 3;i ++)
	{
		if((t & 0x1) != 0)
		{
			c ++;
		}
		t = t >> 1;
	}

	return c;
}

ACE_UINT32 GameUtils::parse_res_id(char *strID)
{
	int len = ACE_OS::strlen(strID);
	bool flag = false;
	if(len > 8)
	{
		return 0;
	}
	
	char typeStr[3];
	char subStr[7];
	ACE_UINT32 ret = 0;
	if(len < 8)
	{
		ret = ACE_OS::strtol(strID, NULL, 16);
	}
	else
	{
		ACE_OS::strncpy(typeStr, &strID[0], 2);
		typeStr[2] = '\0';
		ACE_OS::strncpy(subStr, &strID[2], 6);
		subStr[6] = '\0';

		ACE_UINT32 unType = ACE_OS::strtol(typeStr, NULL, 16);
		ACE_UINT32 unSubID = ACE_OS::strtol(subStr, NULL, 16);

		ret = (unType << 24) + unSubID;
	}
	
	return ret;
}

void GameUtils::sort(ACE_UINT32 unCount, void *list, int elementSize)
{
	int i, j;
	ACE_UINT32 tmp_min;
	int idx;
	BaseItemInfo *t0, *t1;
	char *p0, *p1;
	char *base_p = (char *)list;
	char buff[128];
	for(i = 0;i < unCount;i ++)
	{
		idx = i;
		
		t0 = (BaseItemInfo *)(base_p + i * elementSize);

		tmp_min = t0->unItemID;
		for(j = i + 1;j < unCount;j ++)
		{
			t1 = (BaseItemInfo *)(base_p + j * elementSize);
			if(t1->unItemID < tmp_min)
			{
				tmp_min = t1->unItemID;
				idx = j;
			}
		}

		if(idx != i)
		{
			p0 = base_p + i * elementSize;
			p1 = base_p + idx * elementSize;

			ACE_OS::memcpy(buff, p0, elementSize);
			ACE_OS::memcpy(p0, p1, elementSize);
			ACE_OS::memcpy(p1, buff, elementSize);
		}
	}
}

int GameUtils::find_element(ACE_UINT32 unCount, void *list, int elementSize, ACE_UINT32 unItemID)
{
	int s = 0;
	int e = unCount - 1;

	int t;
	char *base_p = (char *)list;
	BaseItemInfo *element;
	do 
	{
		t = (s + e) / 2;

		element = (BaseItemInfo *)(base_p + t * elementSize);

		if(element->unItemID == unItemID)
		{
			return t;
		}
		else if(element->unItemID < unItemID)
		{
			s = t + 1;
		}
		else
		{
			e = t - 1;
		}
	} while (s <= e);

	return -1;
}

//增加并排序
int GameUtils::add_element(ACE_UINT32 &unCount, void *list, ACE_UINT32 unMaxSize, int elementSize, ACE_UINT32 unItemID)
{
	if(unCount >= unMaxSize)
	{
		return -1;
	}

	char *base_p = (char *)list;
	BaseItemInfo *element;
	int i;
	int j;

	for(i = 0;i < unCount;i ++)
	{
		element = (BaseItemInfo *)(base_p + i * elementSize);
		if(element->unItemID == unItemID)
		{
			return -1;
		}
		else if(element->unItemID > unItemID)
		{
			for(j = unCount - 1;j >= i;j --)
			{
				//m_inviteList[j + 1] = m_inviteList[j];
				ACE_OS::memcpy(base_p + (j + 1) * elementSize, base_p + j * elementSize, elementSize);
			}

			break;
		}
	}

	ACE_OS::memset(base_p + i * elementSize, 0, elementSize);
	element = (BaseItemInfo *)(base_p + i * elementSize);
	element->unItemID = unItemID;

	unCount ++;

	return i;
}

int GameUtils::delete_element(ACE_UINT32 &unCount, void *list, int elementSize, ACE_UINT32 unItemID)
{
	int idx = GameUtils::find_element(unCount, list, elementSize, unItemID);

	if(idx == -1)
	{
		return -1;
	}

	int len = unCount - idx - 1;
	char *base_p = (char *)list;
	int i;
	for(i = idx;i < unCount - 1;i ++)
	{
		ACE_OS::memcpy(base_p + i * elementSize, base_p + (i + 1) * elementSize, elementSize);
	}

	ACE_OS::memset(base_p + (unCount - 1) * elementSize, 0, elementSize);

	unCount --;

	return 0;
}

void GameUtils::parse_drop_group(DropGroup &group, char *strList, bool hasGlobal)
{
	group.unCount = 0;

	char tmp_str[256];

	int len = ACE_OS::strlen(strList);
	int sub_len = 0;

	int offset = 0;

	int c = 0;
	int global_c = 0;

	char total_str[4096];

	ACE_OS::memcpy(total_str, strList, len);
	total_str[len] = '\0';
	if(total_str[len - 1] != ';')
	{
		total_str[len] = ';';
		total_str[len + 1] = '\0';
		len ++;
	}

	while(offset < len)
	{
		if(total_str[offset + sub_len] == ';')
		{
			ACE_OS::memcpy(tmp_str, &total_str[offset], sub_len * sizeof(char));
			tmp_str[sub_len] = '\0';

			if(parse_drop_entity(&group.list[c], tmp_str) == 0)
			{
				if(group.list[c].fRate < 0.0f)
				{
					group.list[c].fRate = -group.list[c].fRate;
					if(hasGlobal)
					{
						group.globalList[global_c] = group.list[c];

						global_c ++;
					}
					else
					{
						c ++;
					}
				}
				else
				{
					c ++;
				}
			}

			offset += (sub_len + 1);
			sub_len = 0;
		}
		else
		{
			sub_len ++;
		}
	}

	group.unGlobalCount = (ACE_UINT32)global_c;
	group.unCount = (ACE_UINT32)c;
}

int GameUtils::parse_drop_entity(DropEntityInfo *info, char *entityStr)
{
	int len = ACE_OS::strlen(entityStr);

	int i;
	int pos = -1;
	for(i = 0;i < len;i ++)
	{
		if(entityStr[i] == ',')
		{
			pos = i;
			break;
		}
	}

	if(pos == -1)
	{
		return -1;
	}

	entityStr[pos] = '\0';

	//info->unResID = ACE_OS::atoi(entityStr);
	//info->unResID = ACE_OS::strtol(entityStr, NULL, 16);
	info->unResID = GameUtils::parse_res_id(entityStr);
	//float tmp = (float)ACE_OS::atof(&entityStr[pos + 1]);
	float tmp = GameUtils::my_atof(&entityStr[pos + 1], 3);

	//info->unType = DROP_LOCAL_TYPE;

	/*
	if(tmp < 0.0)
	{
		tmp = -tmp;
		//info->unType = DROP_GLOBAL_TYPE;
	}
	*/

	info->fRate = tmp;

	return 0;
}

void GameUtils::parse_property_list(PropertyComponent *propertyList, char *strList)
{
	ACE_OS::memset(propertyList, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

	int len = strlen(strList);

	char tmp[64];
	
	int offset = 0;

	int step = 0;
	int c = 0;
	int idx;
	int type = 0;
	//float value = 0;
	ACE_UINT32 unValue;

	while(offset != -1)
	{
		offset = value_token(strList, offset, len, tmp);

		if(step == 0)
		{
			//idx = property_map_2_id(ACE_OS::atoi(tmp));
			idx = ACE_OS::atoi(tmp) - 1;

			if(idx >= PLAYER_PROPERTY_MAX)
			{
				printf("fuck\n");
			}
			/*
			if(needRemap)
			{
				propertyList.list[c].unPropertyID = property_map_2_id(ACE_OS::atoi(tmp));
			}
			else
			{
				propertyList.list[c].unPropertyID = ACE_OS::atoi(tmp);
			}
			*/
		}
		else if(step == 1)
		{
			//propertyList.list[c].unType = ACE_OS::atoi(tmp);
			type = ACE_OS::atoi(tmp);
		}
		else if(step == 2)
		{
			//propertyList.list[c].fValue = (float)ACE_OS::atof(tmp);
			//propertyList.list[c].fValue = GameUtils::my_atof(tmp, 3);
			//unValue = GameUtils::my_atof(tmp, 3);
			unValue = ACE_OS::atoi(tmp);

			if(type == 1)
			{
				//propertyList[idx].fScale += value;
				propertyList[idx].unScale += unValue;
			}
			else if(type == 2)
			{
				//propertyList[idx].fValue += value;
				propertyList[idx].unValue += unValue;
			}
		}

		step = (step + 1) % 3;
	}
}

void GameUtils::parse_benefit_list(BenefitList &benefitList, char *strList)
{
	int len = strlen(strList);

	char tmp[64];
	
	int offset = 0;

	int step = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = value_token(strList, offset, len, tmp);

		if(step == 0)
		{
			benefitList.list[c].unBenefitID = ACE_OS::atoi(tmp);
		}
		else if(step == 1)
		{
			benefitList.list[c].unType = ACE_OS::atoi(tmp);
		}
		else if(step == 2)
		{
			//benefitList.list[c].fValue = GameUtils::my_atof(tmp, 3);
			benefitList.list[c].unValue = ACE_OS::atoi(tmp);

			c ++;
		}

		step = (step + 1) % 3;
	}

	benefitList.unCount = c;
}

void GameUtils::parse_cost_list(CostInfoList &list, char *strList)
{
	ACE_OS::memset(&list, 0, sizeof(CostInfoList));

	int len = strlen(strList);

	char tmp[64];
	
	int offset = 0;

	int step = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = value_token(strList, offset, len, tmp, ';');

		parse_cost(list.list[c], tmp);

		c ++;
	}

	list.unCount = c;
}

void GameUtils::parse_cost(CostInfo &info, char *str)
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	for(int i = 0;i < 2;i ++)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(i == 0)
		{
			//info.unID = ACE_OS::strtol(tmp, NULL, 16);
			info.unID = GameUtils::parse_res_id(tmp);
		}
		else
		{
			info.cost = ACE_OS::atoi(tmp);
		}
	}
}

void GameUtils::parse_property_value_list(ACE_UINT32 *list, char *str)
{
	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;

	int c = 0;

	while(offset != -1)
	{
		offset = value_token(str, offset, len, tmp, ',');

		list[c] = ACE_OS::atoi(tmp);

		c ++;
	}
}

void GameUtils::parse_cooldown_info(CooldownInfo &info, char *str)
{
	ACE_OS::memset(&info, 0, sizeof(CooldownInfo));

	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	for(int i = 0;i < 4;i ++)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(i == 0)
		{
			info.unCD = ACE_OS::atoi(tmp);
		}
		else if(i == 1)
		{
			info.unPrecision = ACE_OS::atoi(tmp);
		}
		else if(i == 2)
		{
			info.unCountLimit = ACE_OS::atoi(tmp);
		}
		else 
		{
			info.unOffset = ACE_OS::atoi(tmp);
			if(info.unPrecision == 0)
			{
				info.unOffset = 0;
			}
			else
			{
				info.unOffset = info.unOffset % info.unPrecision;
			}
		}
	}
}

int GameUtils::value_token(char *str, int offset, int len, char *des)
{
	return value_token(str, offset, len, des, ',');
}

int GameUtils::value_token(char *str, int offset, int len, char *des, char pattern)
{
	int i;
	int c = 0;
	int ret = -1;
	for(i = offset;i < len;i ++)
	{
		if(str[i] == pattern)
		{
			ret = i + 1;
			break;
		}
		des[c] = str[i];
		c ++;
	}

	des[c] = '\0';

	return ret;
}

/*
int GameUtils::property_map_2_id(ACE_UINT32 v)
{
	ACE_UINT32 ret = PROPERTY_ID_NONE;

	switch(v)
	{
	case 1:
		ret = PROPERTY_ID_DAMAGE;
		break;
	case 2:
		ret = PROPERTY_ID_HP;
		break;
	case 3:
		ret = PROPERTY_ID_ALL_DAMAGE;
		break;
	case 4:
		ret = PROPERTY_ID_ALL_HP;
		break;
	case 5:
		ret = PROPERTY_ID_INCREASE_COIN;
		break;
	case 6:
		ret = PROPERTY_ID_CRITICAL;
		break;
	case 7:
		ret = PROPERTY_ID_ARMOR;
		break;
	case 8:
		ret = PROPERTY_ID_ALL_CRITICAL;
		break;
	case 9:
		ret = PROPERTY_ID_ALL_ARMOR;
		break;
	default:
		break;
	}

	return ret;
}
*/

float GameUtils::my_atof(char *str, int precison)
{
	double t = ACE_OS::atof(str);

	int i;
	int c = 1;
	for(i = 0;i < precison;i ++)
	{
		c = c * 10;
	}


	int m = (int)(t * c * 10);

	if(m < 0)
	{
		m = m - 5;
	}
	else
	{
		m = m + 5;
	}

	m = m / 10;

	t = (double)m;
	t = t / c;
	
	return (float)t;
}

void GameUtils::generate_session_id(char *session)
{
	int t = 0;

	for(int i = 0;i < CLIENT_SESSION_LEN;i ++)
	{
		t = rand() % SESSION_CHARACTER_TBL_LEN;
		session[i] = g_session_character_tbl[t];
	}

	session[CLIENT_SESSION_LEN] = '\0';
}




int GameUtils::parse_secret_item(SecretItem *info, char *entityStr)
{
	
	int len = strlen(entityStr);

	char tmp[64];

	int offset = 0;

	int step = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = value_token(entityStr, offset, len, tmp, ';');

		parse_secret_item_list(&info[c], tmp);

		c ++;
	}

//	list.unCount = c;
	return c;
}


int GameUtils::parse_secret_item_list(SecretItem *info, char *entityStr)  //added by jinpan
{
	int len = ACE_OS::strlen(entityStr);

	int i;
	int pos = -1;
	for(i = 0;i < len;i ++)
	{
		if(entityStr[i] == ',')
		{
			pos = i;
			break;
		}
	}

	if(pos == -1)
	{
		return -1;
	}

	entityStr[pos] = '\0';

	
	info->unId = GameUtils::parse_res_id(entityStr);

	float tmp = GameUtils::my_atof(&entityStr[pos + 1], 3);



	info->unCount = tmp;

	return 0;
}

int GameUtils::parse_secret_list(ACE_UINT32 *list,char *str)  //added by jinpan for secret
{
	

	int len = strlen(str);

	char tmp[64];

	int offset = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		//m_relatedList[c] = ACE_OS::strtol(tmp, NULL, 16);
		list[c] = GameUtils::parse_res_id(tmp);

		c ++;
	}

	return c;
}




int GameUtils::parse_pvp_item(Pvp100 *info, char *entityStr)
{

	int len = strlen(entityStr);

	char tmp[64];

	int offset = 0;

	int step = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = value_token(entityStr, offset, len, tmp, ';');

		parse_pvp_item_list(&info[c], tmp);

		c ++;
	}

	//	list.unCount = c;
	return c;
}


int GameUtils::parse_pvp_item_list(Pvp100 *info, char *entityStr)  //added by jinpan
{
	int offset = 0;
	int len = ACE_OS::strlen(entityStr);
	char tmp[64];

	for(int i = 0;i < 2;i ++)
	{
		offset = GameUtils::value_token(entityStr, offset, len, tmp, ',');

		if(i == 0)
		{
			//info.unID = ACE_OS::strtol(tmp, NULL, 16);
	//		info.unID = ACE_OS::atoi(tmp);
			info->unStart = ACE_OS::atoi(tmp);
		}
		else
		{
			info->unEnd = ACE_OS::atoi(tmp);
		}
	}

	return 0;
}

int GameUtils::parse_double_drop(std::map<UINT32, ACE_Byte> &mapID, char *entityStr, const ACE_Byte byType)
{
	int offset = 0;
	int len = ACE_OS::strlen(entityStr);
	char tmp[64];

	while(offset != -1)
	{
		offset = value_token(entityStr, offset, len, tmp, ',');

		//m_mapList[c] = ACE_OS::strtol(tmp, NULL, 16);
		mapID.insert(std::make_pair(parse_res_id(tmp), byType));
	}
	return 0;
}

int GameUtils::get_map_enter_count( ACE_UINT32 unFlag, int level )
{
	int t = (unFlag >> (12 + (level - 1) / 2 * 6)) & 0x3f;
	return t;
}

int GameUtils::set_map_enter_count( ACE_UINT32 unFlag, int count, int level )
{
	ACE_UINT32 t = 0x003f << (12 + (level - 1) / 2 * 6);
	unFlag &= ~t;
	unFlag |= (count << (12 + (level - 1) / 2 * 6));
	return unFlag;
}

bool GameUtils::check_enter_map_count( ACE_UINT32 unFlag, int level, int unTotalCount )
{
	if(unTotalCount <= 0)
		return true;
	int unCount = get_map_enter_count(unFlag, level);
	return unCount < unTotalCount;
}

int GameUtils::get_map_reset_count( ACE_UINT32 unFlag, int level )
{
	int t = (unFlag >> ((level - 1) / 2 * 4)) & 0x0f;
	return t;
}

int GameUtils::set_map_reset_count( ACE_UINT32 unFlag, int count, int level )
{
	ACE_UINT32 t = 0x0f << ((level - 1) / 2 * 4);
	unFlag &= ~t;
	unFlag |= count << ((level - 1) / 2 * 4);
	return unFlag;
}

ACE_UINT32 GameUtils::Get_Day_from_str( const char *str )
{
	time_t time1;
	try
	{
		struct tm tm1; 
		sscanf( str, "%4d-%2d-%2d",     
			&tm1.tm_year,   
			&tm1.tm_mon,   
			&tm1.tm_mday);

		tm1.tm_hour = 0,   
			tm1.tm_min = 0,  
			tm1.tm_sec = 0; 
		tm1.tm_year -= 1900;  
		tm1.tm_mon --;
		tm1.tm_isdst=-1; 
		time1 = mktime(&tm1);

		//time1 -= GMT_OFFSET;
	}
	catch(...)
	{
		printf("error Get_Day_from_str");
	}


	return time1;  
}

//年-月-日[空格]时:分:秒(2015-04-21 12:00:00
ACE_UINT32 GameUtils::Get_Detail_from_str( const char * str )
{
	time_t time1;
	try
	{
		struct tm tm1; 
		sscanf( str, "%4d-%2d-%2d %2d:%2d:%2d",     
			&tm1.tm_year,   
			&tm1.tm_mon,   
			&tm1.tm_mday,
			&tm1.tm_hour,
			&tm1.tm_min,
			&tm1.tm_sec
			);
 
		tm1.tm_year -= 1900;  
		tm1.tm_mon --;
		tm1.tm_isdst=-1; 
		time1 = mktime(&tm1);
	}
	catch(...)
	{
		printf("error Get_Time_from_str");
	}


	return time1;
}

ACE_UINT32 GameUtils::Get_Time_from_str( const char * str )
{
	ACE_UINT32 hour = 0,min=0,sec=0;
	sscanf( str, "%2d:%2d:%2d",     
		&hour,
		&min,
		&sec
		);

	return (hour*60*60 + min *60 + sec);
}

ACE_UINT32 GameUtils::Get_current_day_0_0()
{
	time_t t;
	time(&t);
	struct tm * target_time;
	target_time = localtime (&t); //获取当地时间
	target_time->tm_hour = 0;
	target_time->tm_min = 0;
	target_time->tm_sec = 0;
	target_time->tm_isdst=-1; 

	return (ACE_UINT32)mktime(target_time);
}

int GameUtils::get_weekEx( ACE_UINT32 unCurrentTime )
{
	ACE_UINT32 v = 24L * 60L * 60L;

	ACE_UINT32 t = (unCurrentTime + GMT_OFFSET + v - 1) / v;

	t = t + WEEK_OFFSET;

	return (t % 7);
}

ACE_UINT32 GameUtils::cut_current_day_0_0( ACE_UINT32 _time )
{
	time_t t = _time;
	struct tm * target_time;
	target_time = localtime (&t); //获取当地时间
	target_time->tm_hour = 0;
	target_time->tm_min = 0;
	target_time->tm_sec = 0;
	target_time->tm_isdst=-1; 

	return (ACE_UINT32)mktime(target_time);
}
