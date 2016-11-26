/******************************************
	文件类型：头文件
	
	文件名称：command_return_define_data.h
	
	文件作用：其中包含一些返回的头命令的宏定义
*******************************************/
#ifndef COMMAND_RETURN_DEFINE_DATA_H
#define COMMAND_RETURN_DEFINE_DATA_H

#define SUCCESS 1                    	//成功标志
#define FAILED 0                     	//失败标志
#define NAME_SAME_FALLED 2				//同名失败
#define NAME_ILLEGAL_FAILED 3			//名字含有敏感字

//Tory Add	用户管理返回命令（cmdf = 0）
#define PWORD 2                   		//密码最小长度
#define REGISTER_RETURN 	0           //注册返回
#define LOGIN_RETURN_SELF 	1         	//登录返回自身
#define OTHER_EXIT			2			//其他用户退出

//Tory Add	角色管理返回命令（cmdf = 1）
#define CREATE_HERO_RETURN	0			//创建角色返回
#define ERASE_HERO_RETURN 	1			//删除角色返回
#define SELECT_HERO_RETURN	2			//进入场景
#define ADDEXPRETURN 3      			//英雄增加经验的命令返回 added by bison
#define INSTANCE_RECORD_RETURN 4		//英雄进出副本状态返回 added by tory

//Tory Add 游戏操作处理返回命令（cmdf = 2）
#define LOGIN_RETURN_OTHER 	0        	//其他玩家登录返回
#define MOVE_RETURN_OTHER 	1         	//其他角色移动返回
#define ATTACK_RETURN_SELF	2     	   	//攻击者自身返回
#define ATTACK_RETURN_HITED 3       	//被攻击者返回
#define ATTACK_RETURN_OTHER ATTACK_RETURN_SELF       	//战斗时，旁观者被动接收消息返回
#define DOWN_LINE 5		                //其他玩家下线返回
#define CHANGE_SCENE 6					//角色切换场景
#define MONSTER_DEAD_RETURN 7           //怪物死亡
#define SHOW_MONSTER 8					//显示怪物
#define ENTER_QUIT_FIGHT	10			//人物进入战斗,退出战斗
#define HERO_SKILL_EFFECT 13			//技能效果   evan add 2012.7.11
#define QUNGONG_SKILL_RETURN 14			//群攻消息回发  evan add 2012.7.13
//Tory Add 属性操作处理返回命令（cmdf = 3）
//Evan add 角色学习技能返回命令
#define LEARN_SKILL_RETURN 	0			//学习技能反馈
#define SIT_STATE 			1			//打坐状态
#define USER_ATTR_APPLY_RETURN 6		//人物属性请求返回	added by bison 7.24
#define USE_DRUG_RETURN		5			//使用血蓝药消息返回
#define SKILL_UPGRADE_RETURN 7			//玩家升级消息发送   evan add 2012.7.5
#define HERO_CHANGE_EQUIP	8			//玩家换装备的消息发送 evan add 2012.7.9
#define HERO_CHANGE_EQUIP_OTHERS 9	    //当前玩家换装备发送给周围玩家消息 evan add 2012.7.9
#define HERO_SUIT_NUMBER	10			//玩家身上组成套装的装备的数量发生改变后的消息反馈 evan add 2012.8.31
#define EQUIP_DURABILITY    11			//玩家身上装备的耐久度发生改变时的消息反馈		evan add 2012.8.31
#define HERO_SKILL_UPGRADE  12			//玩家所学技能升级的消息反馈			evan add 2012.9.17
#define BUFF_STATE_RETURN	15			//buff药使用成功返回；玩家上线时恢复buff药 Tory
#define BUFF_DELETE			16			//清除buff效果	Tory
#define HERO_FIGHT_STATUS 	18			//玩家PK模式改变是否成功  evan add 2012.9.23
#define USE_BUFF_RETURN		19			//使用buff药返回			Tory
#define BLOODINCREASE		23				//血包回血		jolly
#define MAGICINCREASE		24				//蓝包回血		jolly
#define AOTUINCREASE		25				//自动回血回蓝		jolly
#define CHANGE_NICKNAME		26
//Tory Add 玩家交互处理返回命令（cmdf = 4）
#define CHAT_MSG_SEND 0					//发送聊天信息
#define CREATE_TEAM_RETURN 1			//建队反馈
#define INVITE_JOIN_RETURN 2			//邀请某人入队得到的反馈
#define INVITE_JOIN 3					//邀请某人入队
#define IS_LEADER_ACCEPT 4				//队长是否同意某人的加入
#define JOIN_TEAM_RETURN 5				//加入队伍反馈
#define MEMBER_INCREASE_BDCAST 6		//队伍新增队友广播
#define MEMBER_DECREASE_BDCAST 7		//队友离开队伍广播	
	
//Evan add 任务交互处理返回命令(cmdf = 5)
#define TASK_INFO_APPLY_RETURN 0 		//玩家任务信息请求的返回  
#define TASK_LOGIN_NOACCEPT_RETURN 1  	//发送未接任务列表（登陆游戏界面）evan add 2012.5.17
#define TASK_ACCEPT_RETURN 2 			//玩家是否可接任务
#define TASK_FINISH_RETURN 3 			//玩家是否完成任务

#define TASK_ABAND_RETURN 4				//放弃任务返回
#define TASK_UPDATE_RETURN 5			//任务状态更新           added by bison
#define TASK_FAILED_RETURN 6      		//任务失败返回
#define TASK_ACCEPT_MAP_RETURN 7		//可接位图返回
#define TASK_REFRESH_GUILD_TASK_RETURN 8 //刷新帮派任务返回
#define TASK_GET_CHAPT_REWARD	9		//获取任务章节奖励

//副本相关的通信处理返回（cmdf = 6)
#define INST_COMMUNICATION			6
#define INST_ENT_RETURN				0	//副本进入返回									added by bison
#define INST_REWARD_CONST_RETURN	1	//副本固定奖励信息（经验，金钱，银两）返回		added by bison
#define INST_REWARD_GOODS_RETURN	2	//副本奖励物品信息返回							added by bison
#define INST_REWARD_ALL_RETURN		3	//玩家领取副本奖励返回							added by bison
#define TD_REWARD_EVERY_WAVE_RETURN	4	//塔防副本每波怪刷完的奖励返回					added by bison
#define INST_AREA_SELCT_RETURN		5	//塔防副本区域设置完的返回						added by tory
#define TEAM_LEADER_OPERATE_RETURN	6	//向队员广播队长选择副本的信息返回				added by tory
#define TEAM_LEADER_OPERATE_RESULT	7	//向队长返回请求进入副本失败结果				added by tory
#define REJECT_ACCEPT				8	//有玩家拒绝进入副本的广播						added by tory
#define INST_GROUP_REWARD_GOODS		10	//队友副本奖励物品返回							added by bison


//人物相关操作通信处理返回（cmdf = 7)
#define HERO_REVIVAL				0
#define HERO_OFF_FIGHT				1
#define HERO_DEAD					2
#define SYSTEM_WARN					5

//#define MONSTER_RETURN_MOVE  MOVE_RETURN_OTHER            	//怪物移动//add by chenzhen 4.23
#define MONSTER_RETURN_MOVE  2          //怪物移动
#define ATTACK_HEAD 2       			//by chenzhen 4.23

//属性修炼处理 (cmdf = 8)
#define VIEW_FIVE_ELEM_INFO		0		//查看人物五行属性
#define CHANGE_FIVE_ELEM_RETURN	1		//更改五行属性返回
#define APPLY_MERID_INFO_RETURN	2		//玩家请求经脉信息返回
#define START_MERID_RETURN		3		//开启经脉返回
#define STREN_MERID_RETURN		4		//强化经脉返回
#define USER_EXERCISE			5		//人物锻炼属性返回
#define OPEN_FIVE_ELEM_RETURN	8		//开启五行属性返回
#define USE_FIVE_ELEM_RETURN	12		//使用五行丹返回
#define USE_MERID_RETURN		15		//使用经脉道具返回
#define EQUIP_OPERATE_REQUIRE	7		//装备改造要求 evan add 2012.8.30

//物品相关的通信处理返回（cmdf = 9)
#define DROP_GOODS              0
#define PICK_RETURN				1	
#define SAVE_GOODS				2
#define GET_EXPERIENCE			3
#define ONLINE_BAG_RETURN		4
#define EQUIP_INFORM			5
#define MONEY					6
#define EXPAND_BAG				7
#define BAG_FULL				8
#define EQUIP_OPERATE			9		//装备辅助功能操作的回发命令 evan add 2012.8.22
#define GOODS_SPLIT				10
#define GOODS_USE_SUECCESS		11
#define EXPAND_RETURN 			12
#define MONEY_FLAG	 			13
#define REWARD_NEW				14
#define REWARD_RETURN 			15
#define REWARD_ONLINE			16
#define REWARD_EXP				17
#define BAG_DRAG				18
#define WEAR_EQUIP				19
#define WEAR_EQUIP_DESTORY		20
#define MYSTERIOUS_RETURN		21
#define MYSTERIOUS_REFRESH		22
#define MYSTERIOUS_BUY			23
#define GUILDGLORY				25
#define KILLMON_EARN_MONEY		26
#define SHENGWANG_RETURN		27	
#define MONEY_NOT_ENOUGH		28
#define DESTORY_GOODS			29
#define XMAS_REWARD				30
#define XMAS_FASION				31
#define EXP_TIMES_USE			32

//宠物相关的通信处理返回（cmdf = 10)
#define PET_EVOLUTION_MSG		0
#define PET_SUCCINCT			1
#define PET_SUCCINCT_SAVE		2
#define PET_EVOLUTION			3
#define PET_EVOLUTION_RETURN	4
#define PET_JINGJIE_NUM			5
#define PET_SKILL_LEARN			6
#define PET_USE					7
#define PET_ACTIVE				8
#define PET_LIST				9
#define PET_DOWNLINE			10
#define PET_SUCCINCT_GOLD		11
#define PET_LEVEL_UP			12
#define PET_JINGJIE				13
#define PET_NAME				14
#define PET_FEED_PET			15
#define PET_SKILL				16
#define PET_SUCCINCT_FIRST		17
#define PET_FUCHONG				18
#define PET_CHUZHAN				19	
#define ERROR					21
#define	PET_SKILL_INFORM		24
#define PET_SKILL_ADVANCE		25
#define PET_BOX_NUMBER			26	
#define PET_EXP					27
#define RIDE_FLAG				31

//物品相关的通信处理返回（cmdf = 12)
#define CREATE_GUILD_RETURN		0				//创建帮派返回
#define VIEW_GUILD_RANK_PAGE	1				//查看某页帮派排名信息返回
#define SEARCH_ONE_GUILD		2				//查找某个帮派
#define APPLY_JOIN_GUILD		3				//申请加入帮派返回
#define VIEW_ONE_GUILD_INFO		4				//查看某个帮派信息
#define VIEW_MY_GUILD_INFO		5				//查看本帮派信息
#define GUILD_UPGRADE_RETURN	6				//帮派升级返回
#define GET_GUILD_RANK_REWARD	7				//领取帮派福利返回
#define CHANGE_GUILD_NOTICE		8				//更改帮派公告
#define	EXIT_FROM_GUILD			9				//退出帮派
#define GUILD_MEMBS_LIST		10				//成员列表
#define GUILD_APPLY_LIST		11				//成员申请列表
#define	REMOVE_FROM_GUILD		12				//移除帮派
#define	AGREE_JOIN_GUILD		13				//同意加入帮派
#define	DISAGREE_JOIN_GUILD		14				//拒绝加入帮派
#define	CLEAR_APPLY_LIST		15				//清空申请列表
#define VIEW_GUILD_SKILL_INFO	16				//查看帮派技能
#define OPEN_GUILD_SKILL		17				//开启帮派技能
#define UPGRADE_GUILD_SKILL		18				//升级帮派技能
#define	VIEW_GUILD_HISTORY_INFO	19				//帮派历史
#define JOIN_GUILD_RETURN		20				//加入帮派返回
#define VIEW_GUILD_ACTIVITY		21				//查看帮派活动
#define GET_GUILD_SIGN_REWARD	22				//领取帮派签到奖励
#define GUILD_DONATE_RETURN		23				//帮派捐献返回
#define CHANGE_GUILD_TITLE		24				//调整帮派头衔
#define DISBAND_GUILD_RETURN	25				//解散帮派返回
#define AGREE_GUILD_ALL_APPLY	26				//同意所有申请者加入
#define INFORM_ONE_APPLY_GUILD	27				//通知帮主有人申请
#define INFORM_REMOVED_GUILD	28				//通知被移除了帮派

//仓库物品相关的通信处理返回（cmdf = 15)
#define WAREHOUSE_GOODS			0
#define WAREHOUSE_EXPAND_NEED	1
#define WAREHOUSE_EXPAND		2
#define ONLINE_WAREHOUSE_RETURN	3

//GM相关的通信处理返回（cmdf = 16)
#define GM_BROADCAST			0



//邮件系统交互处理返回（cmdf = 17）
#define MAIL_SYSTERM			17				//邮件系统cmdf标识
#define MAIL_GET_MAIL_LIST		0				//获取邮件列表
#define MAIL_GET_CONTENT		1				//按邮件索引获取邮件内容
#define MAIL_SEND_ISFAILED      3				//邮件发送是否成功
#define MAIL_LIST_NUM			4				//玩家当前的收件的数量，以及发件的数量
#define MAIL_NEW_RECEIVE        5				//玩家有新的邮件
#define MAIL_GOODS_RECEIVE	    6				//附件内物品接收
//帮派战通信（cmdf = 18）
#define VIEW_GUILD_WAR_ROOM		0				//查看帮派战房间状态
#define CREATE_GUILD_WAR_ROOM	1				//创建帮派战房间
#define CHALLENGE_GUILD_WAR		2				//帮派战挑战
#define GUILD_WAR_CALL_JOIN		3				//召唤加入帮派战
#define GUILD_WAR_START_TIMER	4				//已进入两个帮派，开启强开倒计时
#define GUILD_WAR_JOIN_ONE		5				//帮派战自己帮派新加入一个人
#define SELF_JOIN_GUILD_WAR		6				//自己进入帮派战房间收到的消息
#define INFORM_PREPARE_GUILD_WAR 7				//通知房主可以准备
#define WE_PREPARE_GUILD_WAR	8				//自己帮派房主点了开始
#define GUILD_WAR_READY			9				//帮派战开始5秒倒计时
#define GUILD_WAR_ONE_EXIT		10				//帮派战中退出了一个人
#define GUILD_WAR_ONE_SIDE_EXIT	11				//帮派一边的人全部退出
#define GUILD_WAR_START			12				//帮派战开始
#define GUILD_WAR_OVER			13				//帮战结束
#define GUILD_WAR_REWARD		14				//帮派战奖励
#define GUILD_WAR_CHANGE_LEADER	15				//帮派更换房主
#define GUILD_WAR_SELF_EXIT		16				//自己退出看到的命令
#define GUILD_WAR_KILL_ONE		17				//帮派战杀死一个人返回
#define GUILD_WAR_PICK_FLAG_ERR	18				//采旗失败返回
//宠物双人繁殖 (cmdf = 22)
#define MATING_INVITE			0				//邀请繁殖
#define MATING_AGREE_INVITE		1				//同意繁殖
#define MATING_PET_INFORM		2				//对方宠物信息
#define MATING_GOODS_INFORM		3				//对方物品信息
#define MATING_LOCK				4				//锁定
#define MATING_START			5				//繁殖
//点石成金(cmdf = 23)
#define MIDASTOUCH_RETURN		0				//点石成金数据返回
#define POPULARITY_RETURN 		1				//人物声望变动
#define ONLINE_REWARD_TIME		3				//在线奖励时间发送
#define ONLINE_REWARD_RETURN	4				//在线奖励返回
#define ONLINE_REWARD_RETURN2	5				//再次上线,之前已经刷新过的在线奖励返回
#define TARGET_RETURN			6				//武林目标请求返回
#define TARGET_RECEIVE			7				//武林目标领取
#define COMPLETE_TARGET			11				//完成武林目标

//娱乐图(cmdf = 24)
#define HAPPY_ADD_PER_TIME		0				//娱乐图中每20秒奖励
#define HAPPY_END_RETURN		1				//退出娱乐图通信

//小游戏(cmdf = 27)
#define FINGERGUESSINGAI_RETURN	0				//与电脑对战的结果返回
#define FINGERGUESSINGAI_ENTER	1				//玩家加入房间
#define FINGERGUESSING_EXIT		2				//退出猜拳游戏
#define FINGERGUESSING_WARN		3				//猜拳提示

#endif
