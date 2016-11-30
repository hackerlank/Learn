#pragma once

#include "GameDefine.h"
#include "libxml\parser.h"

class GameUtils
{
public:
	static ACE_UINT32 get_utc();//秒
	static void get_current_time_str(char *str);
	static void get_current_day_str(char *str);
	static int get_day_different(ACE_UINT32 t0, ACE_UINT32 t1);
	static int get_time_offset(ACE_UINT32 t0, ACE_UINT32 t1, ACE_UINT32 offset, ACE_UINT32 precision);
	static int get_week_count(ACE_UINT32 unCurrentTime);
	static int get_week_time(ACE_UINT32 unCurrentTime);
	static int get_day_time(ACE_UINT32 unCurrentTime);
	static int get_week(ACE_UINT32 unCurrentTime);

	static ACE_UINT32 get_pvp_season_id(ACE_UINT32 unCurrentTime);
	static char *get_pvp_season_tbl_name(ACE_UINT32 unSeasonID);
	static bool can_commit_pvp_result(ACE_UINT32 unCurrentTime);
	static bool can_match_pvp_opponent(ACE_UINT32 unCurrentTime);
	static ACE_UINT32 get_rank(ACE_UINT32 unOrder, ACE_UINT32 unCount);

	static bool is_hit(float fRate);

	static ACE_UINT32 parse_res_id(char *strID);

	//static ACE_UINT32 get_drop(DropGroup &group);

	static void reset_reward(RewardInfo &reward);

	static int get_map_unlock_flag(ACE_UINT32 unFlag, int level);
	static int set_map_unlock_flag(ACE_UINT32 unFlag, int new_flag, int level);
	static int get_map_star(ACE_UINT32 unFlag, int level);
	static int set_map_star(ACE_UINT32 unFlag, int star, int level);
	static int get_map_star_count(ACE_UINT32 unFlag, int level);
	static int get_map_enter_count(ACE_UINT32 unFlag, int level);
	static int set_map_enter_count(ACE_UINT32 unFlag, int count, int level);
	static bool check_enter_map_count(ACE_UINT32 unFlag, int level, int untotalCount);
	static int get_map_reset_count(ACE_UINT32 unFlag, int level);
	static int set_map_reset_count(ACE_UINT32 unFlag, int count, int level);

	static void sort(ACE_UINT32 unCount, void *list, int elementSize);
	static int find_element(ACE_UINT32 unCount, void *list, int elementSize, ACE_UINT32 unItemID);
	static int add_element(ACE_UINT32 &unCount, void *list, ACE_UINT32 unMaxSize, int elementSize, ACE_UINT32 unItemID);
	static int delete_element(ACE_UINT32 &unCount, void *list, int elementSize, ACE_UINT32 unItemID);

	static void parse_drop_group(DropGroup &group, char *strList, bool hasGlobal);
	static int parse_drop_entity(DropEntityInfo *info, char *entityStr);
	static void parse_property_list(PropertyComponent *propertyList, char *strList);
	static void parse_benefit_list(BenefitList &benefitList, char *strList);
	static void parse_cooldown_info(CooldownInfo &info, char *str);
	static void parse_cost_list(CostInfoList &list, char *strList);
	static void parse_cost(CostInfo &info, char *str);
	static void parse_property_value_list(ACE_UINT32 *list, char *str);
	static int value_token(char *str, int offset, int len, char *des);
	static int value_token(char *str, int offset, int len, char *des, char pattern);
	static int parse_secret_item(SecretItem *info, char *entityStr);  //added by jinpan for secret
	static int parse_secret_list(ACE_UINT32 *list,char *str);
	static int parse_secret_item_list(SecretItem *info, char *entityStr);
	static int parse_pvp_item(Pvp100 *info, char *entityStr);
	static int parse_pvp_item_list(Pvp100 *info, char *entityStr);  //added by jinpan
	static int parse_double_drop(std::map<UINT32, ACE_Byte> &mapID, char *entityStr, const ACE_Byte byType);
	//static int property_map_2_id(ACE_UINT32 v);
	static float my_atof(char *str, int precison);
	static void generate_session_id(char *session);
	static ACE_UINT32 Get_Day_from_str(const char *str);//日期字符串转换成ACE_UINT32,格式：YYYY-MM-DD （2015-04-24）
	static ACE_UINT32 Get_Detail_from_str(const char * str);//时间转换成ACE_UINT32,格式：年-月-日[空格]时:分:秒(2015-04-21 12:00:00	
	static ACE_UINT32 Get_Time_from_str(const char * str);//时间点转换成ACE_UINT32,格式：时:分:秒(12:00:00）
	static ACE_UINT32 Get_current_day_0_0();//获取今天的0时0分0秒
	static ACE_UINT32 cut_current_day_0_0(ACE_UINT32 _time);//当前时间的0时0分0秒
	static int get_weekEx(ACE_UINT32 unCurrentTime);
};