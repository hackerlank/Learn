#ifndef FUNCTION_READ_CONFIGURATION_FILES_H
#define FUNCTION_READ_CONFIGURATION_FILES_H

#include<string.h>

int read_main_config(char *fileName);		//读取主配置文件，得到其他配置文件路径

int read_scene_config(char *fileName);		//读取场景配置文件，获得场景配置文件的路径

int read_files_map(char *fileName);

int read_files_monster(char *fileName);

//int read_files_skill(char *fileName);     //原来的技能读取配置文件弃用  evan add 2012.5.25

int read_files_five(char *fileName);

int read_files_hatValRue(char *fileName);

int read_files_equip(char *fileName);

int read_files_cpy(char *cpyName);

int read_files_task(char *fileName);   //读取任务的配置文件的方法

int read_files_npc(char *fileName);    //读取NPC的配置文件的方法

int read_files_droplist(char *fileName); //读取掉落列表配置文件的方法

int read_files_touch(char *fileName);  //读取触发任务条件文件的方法声明  evan add 2012.5.24

int read_files_zhudong(char * fileName); //主动攻击类型的技能基础数据的读取  evan add 2012.5.25

int read_files_yiliao(char * fileName); //医疗类型的技能基础数据的读取  evan add 2012.5.25

int read_files_buff(char * fileName); //buff类型的技能基础数据的读取  evan add 2012.5.25

int read_files_beidong(char * fileName); //被动类型的技能基础数据的读取  evan add 2012.5.25

int read_ectype_reward_goods(char *fileName); //副本奖励物品范围配置	added by bison 6.13

int read_ectype_reward_info(char *fileName);	//读取副本奖励配置信息	added by bison	6.13

int read_files_cpyLimit(char *fileName);   //读取副本限制类         chenzhen add 2012.06.11 

int parseTowerDefence(char *fileName);		//读取塔防副本配置文件 

int read_files_ointment(char *fileName); //读取药膏基础数据 cookie 2012.6.14

int read_files_groupBrush(char *fileName); //读取批次刷怪基础数据 cookie 2012.07.06

int read_task_goods_info(char *fileName);	//读取任务道具配置 added by bison 7.6

int read_monster_skill(char *fileName);	//读取Boss技能 added by 陈真 7.10

int read_files_pet(char *fileName);	//读取宠物信息 added by jolly 7.13

int read_files_jumpId(char *fileName);  //读取跳转点ID对应的信息；  added by xhm 2012.07.18

int read_files_petSkill(char *fileName);	//读取宠物技能信息  add by jolly 7.31

int read_files_goods(char *fileName);		//读取所有物品的信息 add by jolly 8.14

int read_files_suit(char *fileName);		//获取套装的信息 add by evan 2012.8.30

int read_take_goods(char *fileName);		//读取可摘取任务道具

int read_wagon(char *fileName);		//读取马车任务道具

int read_files_reward_level(char *fileName);			//读取等级奖励的信息 add by jolly 2012.9.10

int read_files_reward_recharge(char *fileName);			//读取充值奖励信息 add by jolly 2012,9.10

int read_files_reward_time(char *fileName);				//读取新手时间奖励信息 add by jolly 2012.9.10

int read_bottle(char *fileName);					//读取瓶罐道具

int read_trap(char *fileName);						//读取瓶罐道具

int read_npc(char *fileName);	  					//npc 配置  cookie

int read_guild_activity_info(char *fileName);		//读取帮派活动信息

int read_cycle_limit_info(char *fileName);			//读取循环项目

int read_vip(char *fileName);						//cookie读取vip

int read_files_update(char *fileName);

int read_copyCause(char *fileName);					//读取副本令

int read_pitchTerm(char *fileName);

int read_files_revival(char *fileName);				//读取复活点位置信息 jolly 9.25

int read_title(char *fileName);

int read_files_mysteriousBussiness(char *fileName);		//读取神秘商人配置文件

int read_dirty_words(char *fileName);					//读取脏词

int read_server_config(char *fileName);				//读取连接缓存服务器的配置文件

int read_monsterActiveBoss(char *fileName);         //读取野外boss的配置文件

int read_dailyActive(char *fileName);               //读取活动配置文件

int read_cpyPassOlder(char *fileName);              //读取副本通关配置

int read_files_guildBussiness(char *fileName);              //读取帮派商店

int read_files_midasTouchReward(char *fileName);              //读取点石成金奖励

int read_guild_feast_info(char *fileName);					//读取帮派盛宴信息

int read_server_config(char *fileName);

int read_files_reward_online(char *fileName);				//读取在线奖励配置文件

int read_happy_map(char *fileName);							//读取娱乐地图配置

int read_guild_skill(char *fileName);						//读取帮派技能

int read_files_shengWangBussiness(char *fileName);						//读取声望商店

int read_files_reward_target(char *fileName);						//读取武林目标奖励

int read_buff_debuff(char *fileName);								//读取buff和debuff的配置

int read_tool_brush_monster(char *fileNme);                //读取道具刷怪文件

int read_campWar_reward_conf(char *fileNme);				//读取阵营战奖励配置文件；

int read_files_vipBaleRomLimit(char *fileName);           //读取VIP包厢限制类  

int read_files_partyRomLimit(char *fileName);             //读取帮派限制类  

int read_fight_const_value(char* fileName);					//读战斗公式常量

int read_hero_skill(char *fileName);						//读取人物技能配置

int read_hero_conf(char *fileName);						//读取人物门派属性数据

int read_recharge_reward_conf(char *fileName);			//读取充值奖励配置文件；

int read_guild_reward(char *fileName);					//读取帮派奖励

int read_Npc_cpy_pt(char *fileName);                    //读取副本npc坐标

int read_files_reward_useGold(char *fileName);           //读取副本npc坐标

int read_party_base_camp(char *fileName);                //读取帮派大本营

int read_consume_reward_conf(char *fileName);			//读取消费奖励配置文件 xhm added;

int read_heCheng_config(char *fileName);				//读取宝石合成所需的配置文件

int read_factor_reward(char *fileName);					//读取经验奖励配置文件

int read_outer_active_code(char *fileName);             //读取外部激活码配置文件

int read_inner_active_code(char *fileName);            	//读取内部激活码配置文件

int read_festivalGoods(char *fileName);               	//读取活动物品匹配配置文件

int read_five_elem_conf(char *fileName);				//读五行配置

int read_merid_conf(char *fileName);					//读经脉配置

int read_internal_forces(char *fileName);				//内力

int read_active_double(char *fileName);					//读各种双倍配置文件

int read_good_use_reward_conf(char *fileName);			//读取物品使用记录；

int read_files_ride(char *fileName);					//读取物品使用记录；

int read_statuaryBase(char *fileName);              //读取替身雕像配置文件

int read_mem_group_config(char* fileName);				//读取缓存服务器的配置列表

int read_files_vip(char* fileName);				//读取vip配置文件

int read_files_rideSkill(char* fileName);				//读取坐骑技能配置文件

int read_files_rideSpecialSkill(char* fileName);				//读取坐骑特殊技能配置文件

int read_camp_res_war_control(char *fileName);

int read_guild_war_control(char *fileName);

int read_rob_flag_war_control(char *fileName);

int read_files_petRange(char *fileName);				//读取宠物战力 已经刷新的配置文件

int read_black_margin(char *fileName);                 //读取黑木崖配置文件

int read_files_equipOperator(char *fileName);                 //读取装备操作配置文件

int read_global(char *fileName);

int read_files_rankReward(char *fileName);			//读取排名奖励

int read_files_words(char *fileName);			//读取服务器文字

int read_files_everyDaySignReward(char *fileName);			//读取每日签到奖励

int read_cycle_task_reward_info(char *fileName);			//每日无限循环任务奖励随循数增加减少

int read_files_cdkey(char *fileName);			//cdkey兑换奖励配置文件


#endif
