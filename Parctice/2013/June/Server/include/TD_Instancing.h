#ifndef TD_INST_
#define TD_INST_

#include<string>
#include <vector>
#include <iostream>

#include "libev.h"
#include "map_cpy.h"
#include "ectype_reward_set.h"
#include "data_structure_struct.h"

class CpyLimit;
/**
*说明：以下宏定义为塔防副本记录表数据的索引标识，用于获取/修改塔防副本记录表的相应数值的传入参数
*常用函数：	int  getInstancingStatus(DATA_CHOICE_INT data_choice);
*			bool setInstancingStatus(DATA_CHOICE_INT data_choice);
*/
typedef int DATA_CHOICE_INT;

#define INST_STATUS_ISPOLL 				1
#define INST_STATUS_ISSYSATTACKOPEN 	2
#define INST_STATUS_POLL_COUNT 			3
#define INST_STATUS_LOSE_COUNT 			4
#define INST_STATUS_MONSTER_COUNT 		5
#define INST_STATUS_MONSTER_DISAPPEAR 	6
#define INST_STATUS_ROTATE_COUNT 		7
#define INST_STATUS_CUR_LIVE_COUNT 		8
#define INST_STATUS_HELP_VAL 			9

#define ALL_MAX_LOSE					5	//漏掉怪物的最大数目

/**副本进入的限制条件*/
typedef struct{
	int 	open_flag;				//开启条件，用于验证不同难度等级的副本的进入
	int 	level;					//等级要求
	int 	free_limit;				//每日进入次数
}Instancing_require;


/**塔防副本基本信息*/
typedef struct{
	string 	id;
	string 	name;
	int 	degree;					//当前副本的难度等级（0--->普通，1--->江湖，2--->英雄）
}Instancing_infor;


/**副本策略配置信息*/
typedef struct{	
	int		attractMonNum;			//可吸引怪物的数量
	int 	single_frequency;		//单个怪物刷出间隔
	int		unit_frequency;			//怪物批次刷出间隔
	vector<int>		time_gap;		//每批怪物的数量
 	vector<Point> 	route_left;		//怪物移动大致路径(左侧)
	vector<Point> 	route_right;	//怪物移动大致路径(右侧）
	vector<Point> 	stand_point;	//角色进入时的站立点 
}Instancing_strategy;


//副本状态记录表
typedef struct Instancing_record{
	bool	isPoll;					//是否已启动
	bool 	sysAttackOpen;			//系统攻击怪物功能是否已开启
	int		poll_count;				//轮询的次数
	int		lose_count;				//顺利跑到目标点的怪物
	int  	monster_count;			//已刷出的怪物个数
	int		monster_disappear;		//因为走到终点或被攻击而死亡的怪物数目，服务器将对该实例进行消失处理
	int		rotate_count;			//怪物批次
	int		cur_live_count;			//当前副本中存活怪物的数量
	int		help_val;				//斗气值
	
	int 	cur_max_monster_num;	//在当前批次下，所能刷出的最大怪物数目
	int		time_gap_sum;			//当前怪物批次下，间隔时间的总和，用于下一批次的怪物刷出需要隔多少时间
	
	Instancing_record(){
		data_reset();
	}
	
	void data_reset(){
		isPoll = false;
		sysAttackOpen = false;
		poll_count = 0;
		lose_count = 0;
		monster_count = 0;
		monster_disappear = 0;
		rotate_count = 0;
		cur_live_count = 0;		
		help_val = 0;
		
		cur_max_monster_num = 0;
		time_gap_sum = 0;
	}
}Instancing_record;


//塔防副本的配置信息
typedef struct TD_Conf_S {
	Instancing_infor		infor;				//副本基本配置信息
	Instancing_require		require;			//进入副本要求
	Instancing_strategy		strategy;			//副本玩法策略配置信息
	vector<string>			scenes_id_vec;		//副本中包含的场景ID集合
	
	TD_Conf_S(Instancing_infor _infor, Instancing_require _require,
		Instancing_strategy _strategy, vector<string> _scenes_id_vec)
	{
		infor = _infor; 
		require = _require;
		strategy = _strategy;
		scenes_id_vec = _scenes_id_vec;
	}
	
	TD_Conf_S(){};
	
} TD_Conf_T;

void show_TD_Conf_S(TD_Conf_T obj, char *outfile);

/*
 * int2str - 整型数转换成固定长度的字符串，位数不够的补零
 * author: bison
 * @val: 所要转换的整形数
 * @figure: 所要转换成的字符串位数
 * Return: 返回转换的字符串。如figure为4时,23则转成"0023"
 */
inline string int2str(int val, int figure)
{
	string str;
	while(figure--)
	{
		str.insert(str.begin(), (char)('0' + val % 10));
		val /= 10;
	}
	return str;
}


class TD_Instancing
{
	private:		
		/**实例化对象时需初始的数据*/
		Map_Cpy*	mapNow;
		vector<MonsterBase *>	monster_store;		//本副本包含的怪物数据,由地图实例管理
	
		Instancing_record		record;				//副本记录表
		EctypeRewardSet *		rewardSet;			//副本奖励集合
		
		list<MonsterBase *>     currMonster;		//当前副本的怪物集合
		vector< vector<string> > 	mon_vec;		//刷怪容器

	public:
		/**配置文件提供的信息*/
		Instancing_infor		infor;			//副本基本配置信息
		Instancing_require		require;		//进入副本要求
		Instancing_strategy		strategy;		//副本玩法策略配置信息
		
		string		td_inst_id;		//副本实例id
		int			roomNum;		
		vector<Hero*> heroPtr_vec;	//当前副本的玩家集合
		bool		isSingleChall;	//是否单人挑战模式
	public:
		TD_Instancing(int roomNum);	
		~TD_Instancing();
		bool reset(void);											//塔防副本实例重置接口；	
		bool loadNewInstance(const TD_Conf_T &tdConf, Map_Cpy* scene);
		int  response(void);	
		void stopMonThk();
		
		void setHeroLocation(Hero* heroWillEnt,int _index);			//设置角色在副本中的位置
		string get_instancing_id(void);								//得到副本实例的id编号
		string get_instancing_confId(void);							//得到副本类型id
		Instancing_strategy getInstancing_strategy(void);			//获得副本的策略信息
		Instancing_require	getInstancing_require(void);			//进入副本要求
				
		int  getInstancingStatus(DATA_CHOICE_INT data_choice);		
		bool AddSelfInstancingStatus(DATA_CHOICE_INT data_choice);
		void start_systerm_attack(vector<Hero *> team_unit);		//启动系统攻击怪物功能		
				
		ev_timer *timer;											//可以外部访问
		EctypeRewardSet* getRewardSet(void);						//得到副本奖励
							
		//describe: 向在塔防副本中的所有角色广播消息
		void sendMsgInTower(char *msg2Send);

};

//用于副本注册了poll函数后，通过事件回调，按先后顺序执行相应的副本response
void inst_poll_callback(struct ev_loop *loop,ev_timer *think,int revents);

CpyLimit* getLimitInst(const char* cpyType);
#endif