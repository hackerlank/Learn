/*
		文件类型：头文件
		文件名称：other_define_data.h
		文件作用：其他常量的定义
*/

#ifndef OTHER_DEFINE_DATA_H
#define OTHER_DEFINE_DATA_H
#include<string>
#define MAXLEN 1023          	//最大缓存空间
#define PORT 8090          		//端口号
#define MAX_NAME_LEN 50       	//用户名的最大长度
#define MAX_WORD_LEN 50       	//密码的最大长度
#define HERO_ID_LEN 38			//角色ID长度
/* #define FLAGLEN		2			//用于存放 */

#define MAX_TYPE_COMMAND 100      	//最大命令类型数
#define MAX_EACH_TYPE_COMMAND 50   	// 每种类型的命令的最大数

#define EFFECT_COMMAND_RANGE MAX_EACH_TYPE_COMMAND*MAX_TYPE_COMMAND          //可容纳最大命令数目

#define DEAD 0                  //死亡状态
#define LIVE 1                  //存活状态

#define SKILL_COLL_DOWN_TIME  0.01         //技能冷却时间
#define SKILL_COOL 1           //技能冷却状态
#define SKILL_HOT 0            //技能热状态
#define MONSTER_THINK_TIME 0.5
#define MONSTER_EACH_WALK_STEP 3
#define HERO_TYPE "H"
#define MONSTER_TYPE "M"

#define MAP_THINK_TIME 1         //add by chenzhen 

#define ATTACK_TYPE "000"     

#define MON_ATT_TYPE "000"   //ADD by chnzhen 4.23

#define ATTACK_VOID_BASE_NUM 0.0001
#define VOID_BASE_NUM 500
#define VOID_BASE 0.5

#define HANG_UP_DATA_SIZE 200			//挂机数据最大长度；
#define PARTY_LEN	2					//门派最大值，门派本可以用一个字符可表示，但是hero下面用的是字符串，所以只能定义2个字符呢，有疑问RTX xhm;
#define MAX_FRIEND_COUNTS 200			//xhm 添加 最大好友数目；	有疑问RTX xhm
#define HERO_MAME_LEN 32				//游戏昵称最大长度； 		有疑问RTX xhm
#define SHORT_CUT_BAR_DATA_SIZE 500		//快捷栏数据组大长度；		有疑问RTX xhm
#define SYSTEM_SET_DATA_SIZE 200		//系统设置基本数据长度；	有疑问RTX xhm
#define OPERATION_SET_DATA_SIZE 300		//操作设置基本数据长度；	有疑问RTX xhm
#define MAX_MESSAGE_DATA_LEN 1000		//聊天消息最大长度；		有疑问RTX xhm

#define WAGON_WALK_TIME 1800            //马车过期时间

#define COPY_SUM_LEVEL   49             //副本总数<后面副本数增加，则也增加>

#define COPY_SUM_FLG   19             	//副本总数

#define FIGHT_FRIST_HEAD 26              //攻击第一个头命令
#define FIGHT_SECOND_HEAD 2              //攻击第二个头命令
#define FIGHT_SECOND_BUFF 3              //buff技能第二个头命令
#define OPEN_BUFF 0                      //buff技能开启
#define CLOSE_BUFF 1                      //buff技能关闭

#define MONSTER_TASK_LIVE_TIME 180         //任务怪存活时间
#endif
