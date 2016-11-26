/*******************************************
* created	:	2012/2/28  9:24
* 鏂囦欢鍚?锿command_process_function_init.cpp
* purpose	:  娉ㄥ唽鎵€鏈夊懡浠ゅ鐞嗗嚱鏿
*********************************************************************/
#include<stdlib.h>

#include"data_structure_struct.h"

#include"library_head.h"

#include"command_other_function_all_over.h"

#include"command_user_role_manage.h"

#include"game_move.h"

#include"command_game_fight_manage.h"
#include"shengWang_bussiness.h"
#include"chat.h"
#include"user_role_manage_assist.h"

#include"entCpy.h"
#include "festivalActive.h"
#include"user_role_manage_task.h"

#include"user_role_accept_task.h"

#include"user_role_finish_task.h"

#include"user_role_buff.h"

#include"bag_operator.h"

#include"instancing_communication.h"

#include "dropgoods.h"

#include"cpy_series_command_function.h"

#include "instancing_communication.h"

#include"user_role_manage_equip.h"

#include"user_role_manage_skill.h"
#include "fingerGuessingGame_communicate.h"

#include "jumpId_to_changeSence.h"

#include "meridian_comm.h"

#include "five_elem_comm.h"

#include "user_attr_apply.h"

#include "pet_communicate.h"

#include "set_camp.h"

#include "analyzeCampWar.h"

#include "guild_comm.h"

#include "rob_flag_war_comm.h"

#include "friendAnalyze.h"

#include "attack_wagon.h"

#include "analyzeRankInfo.h"

#include "reward_communicate.h"
#include "guildBussiness.h"
#include "anyBusiness.h"

#include "warehouse_communicate.h"

#include "GM_communicate.h"

#include "guild_war_comm.h"
#include "sitControl.h"
#include "viewHangUpInfo.h"
#include "mail_systerm_communicate.h"
#include "user_role_manage_status.h"

#include "hero_title_use.h"
#include "mysteriousBussiness_communicate.h"

#include "hero_title_use.h"
#include "midasTouch_communicate.h"
#include"active_communicate.h"
#include "useGoods.h"
#include "configurationInfo.h"

#include "account_communication.h"
#include "wulinTarget.h"
#include"attackBottle.h"
#include "hero_skill_asist.h"
#include "hero_fight.h"
#include "wagon_comm.h"
#include "time_limit_events.h"
#include "ride_comm.h"
#include"statuaryCommunicate.h"
#include"cpyAsist.h"
#include "internal_forces_comm.h"
#include"teamOperator.h"
#include "camp_leader_and_chief.h"

extern vector<FUN>command_map;

using namespace std;

void init_command_map(void)					
{
	char cmdf,cmds;
	for(cmdf=0;cmdf<MAX_TYPE_COMMAND;cmdf++)
	{
		for(cmds=0;cmds<MAX_EACH_TYPE_COMMAND;cmds++)
		{
			int index=cmdf*MAX_EACH_TYPE_COMMAND+cmds;
/* 			if(index == 0*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &registerUser;
			} */
			if(index == 0*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &loginUser;
			}
			else if(index == 0*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index] = &exit_normal;
			}
			else if(index == 0*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &login_from_web;
			} else if (index == 0 * MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index] = &temp_guest_change_name;
			}
			else if(index==1*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &createHero;
			}
			else if(index == 1*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &deleteHero;
			}
			else if(index==1*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index]= &selectHero;
			}else if(index==1*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index]= &doneline_operate;
			}			
			else if(index==1*MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index]= &enterScenResponse;
			}					
			else if(index==2*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index]= &move_get_road;
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+1)
			{
				// command_map[index]= &flightAction;
			}						
			else if(index==2*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index]= &change_scene;
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &entCpy;					
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index] = &entCpyNextMap;					
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+5)
			{
				command_map[index] = &exitCpy;					
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+6)
			{
				// command_map[index] = &selectInstArea;					
			}		
			else if(index==2*MAX_EACH_TYPE_COMMAND+7)
			{
				command_map[index]= &heroResponse;
			}	
			else if(index==2*MAX_EACH_TYPE_COMMAND+9)				
			{
				// command_map[index] = &attackusebuff;				//buff鎶€鑳界殑浣跨敤		evan 2012.8.14
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+10)				
			{
				// command_map[index] = &qungongskill;					//缇ゆ敾鎶€鑳界殑浣跨敿evan 2012.7.13	
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+11)				
			{
				command_map[index] = &jumpid_to_change_sence;		 /*璺宠浆鐐硅繘鍏ョ壒瀹歮apID 鏈夌枒闂甊TX xhm;	 2012.7.13*/
			}
			else if(index==2*MAX_EACH_TYPE_COMMAND+13)				
			{
				command_map[index] = &ChangePKstatus;	 /*鐜╁鐨凱K妯″紡鏀瑰彉*/
			}			
			else if(index==2*MAX_EACH_TYPE_COMMAND+14)				
			{
				command_map[index] = &enterCpyByTool;	 /*鐢ㄩ亾鍏疯繘鍓湿*/
			}			
			else if(index==2*MAX_EACH_TYPE_COMMAND+16)				
			{
				command_map[index] = &panelResponse;	   /*娲诲姩鐘舵€?*/
			}			
			else if(index==2*MAX_EACH_TYPE_COMMAND+17)				
			{
				command_map[index] = &takePartActive;	   /*鍙傚姞娲诲姩*/
			}			
			else if(index==2*MAX_EACH_TYPE_COMMAND+18)				
			{
				command_map[index] = &attactBottleCom;	   /*鍙傚姞娲诲姩*/
			}			
			else if(index == 3*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &timePoll;					//绛夐棿闅旇疆璇㈠嚱鏁帮紝鐢ㄤ簬瀹炴椂鏇存柊鐜╁瑙掕壊鐨勫綋鍓嶇姸鎿
			}			
			else if(index == 3*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &sitControl;					//绛夐棿闅旇疆璇㈠嚱鏁帮紝鐢ㄤ簬瀹炴椂鏇存柊鐜╁瑙掕壊鐨勫綋鍓嶇姸鎿
			}
			else if(index == 3*MAX_EACH_TYPE_COMMAND+3)
			{
				// command_map[index] = &skillupgrade;				//鐜╁鎶€鑳藉崌绿evan add 2012.9.17
			}
			else if(index == 3*MAX_EACH_TYPE_COMMAND+11)
			{
				command_map[index] = &bloodAndMagicBagAgain;		//角色上线时，客户端请求血包蓝宝（双倍经验）的剩余数据
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+0)
			{
				// command_map[index] = &heroLearnSkill;			//
			}
 			else if(index == 4*MAX_EACH_TYPE_COMMAND+1)
			{
				
			} 
			else if(index == 4*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &getEquipInform;					//璇锋眰鍗曚欢瑁呭淇℃伅
			}/* 
		 	else if(index == 4*MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index] = &useGoods;					//浣跨敤鐗╁搧
			}  */
			else if(index == 4 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &userAttrApplyComm;		//请求人物基础属性数据
			}
		 	else if(index == 4*MAX_EACH_TYPE_COMMAND+6)
			{
				command_map[index] = &revival;					//浣跨敤鐗╁搧
			} 
			else if(index == 4*MAX_EACH_TYPE_COMMAND+7)
			{
				command_map[index] = &equipchange;					//浣跨敤瑁呭 evan add 2012.7.9
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+8)
			{
				// command_map[index] = &debuffstop;					//鍙栨秷鎶€鑳界壒鏿evan add 2012.7.10
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+9)
			{
				command_map[index] = &equiphelp_operate;			//锻造系统：对装备进行锻造 evan add 2012.8.22
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+10)
			{
				command_map[index] = &require_equip_operater;		//请求锻造消费和锻造预期结果 evan add 2012.8.30
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+11)
			{
				command_map[index] = &userExercise;					//浜虹墿璁粌璇锋眿
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+12)
			{
				command_map[index] = &userExerciseMoneySave;					//鍏嶈垂淇濆瓨璁粌缁撴灉 
			}
			else if(index == 4*MAX_EACH_TYPE_COMMAND+13)
			{
				command_map[index] = &userExerciseGoldSave;					//鍏冨疂淇濆瓨璁粌缁撴灉
			}	
			else if(index == 4*MAX_EACH_TYPE_COMMAND+14)
			{
				command_map[index] = &changeCamp;						//更改帮派
			}		
			else if(index == 4*MAX_EACH_TYPE_COMMAND+15)
			{
				command_map[index] = &changeNickName;						//改名
			}		
			else if(index==5*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &advertise;				//广播
			}
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 11)		
			{
				command_map[index] = &pickgoods;					//捡物品	
			}	
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 12)		
			{
				//已废弃 tory
			}	
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 13)		//绉佽亰锛?鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &whisper;						
			}		
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 14)		//韬笂瑁呭淇℃伅璇锋眰
			{
				command_map[index] = &heroWearEquip;						
			}		
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 15)		//韬笂瑁呭鎽ф瘉
			{
				command_map[index] = &heroWearEquipDestory;						
			}	
			
			else if(index == 5 * MAX_EACH_TYPE_COMMAND + 16)		//韬笂瑁呭鎽ф瘉
			{
				command_map[index] = &gainMsgById;						
			}			
			
			else if(index==6*MAX_EACH_TYPE_COMMAND+0)
			{
				//command_map[index] = &taskAction;               //瀹㈡埛绔彂閫佺粰鏈嶅姟鍣ㄧ帺瀹跺彲鎺ヤ换鍔″垪琿 evan add 2012.5.17
			}
			else if(index==6*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &taskAccept;               //瀹㈡埛绔彂閫佺粰鏈嶅姟鍣ㄧ帺瀹剁帺瀹舵槸鍚︽帴鍙椾换鍔′俊鎿 evan add 2012.5.18
			}
			else if(index==6*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index] = &taskFinish;               //瀹㈡埛绔彂閫佺粰鏈嶅姟鍣ㄧ帺瀹剁帺瀹跺畬鎴愪换鍔′俊鎿 evan add 2012.5.18
			}
			else if(index==6*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &taskAband;               //瀹㈡埛绔彂閫佺粰鏈嶅姟鍣ㄧ帺瀹剁帺瀹舵斁寮冧换鍿 added by bison
			}
			else if(index == 6 * MAX_EACH_TYPE_COMMAND + 4)
			{
				///command_map[index] = &taskUpdate;				//瀹㈡埛绔彂鏉ヤ换鍔＄姸鎬佹暟鎹洿鏂板懡浠?added by bison
			}
			else if(index == 6 * MAX_EACH_TYPE_COMMAND + 5)
			{
				// command_map[index] = &collectGoodsComm;				//閲囬泦浠诲姟閲囬泦鐨勭墿鍿added by bison
			}
			else if(index == 6 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &taskInfoComm;					//璇锋眰鐜╁浠诲姟淇℃伅	added by bison
			}
			else if(index == 6 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &attactWagonComm;					//鏀诲嚮椹溿added by bison
			} else if (index ==  6 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &getTaskChaptRewardComm;			//获取任务章节奖励
			}
			else if (index ==  6 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &viewHeroCycleTaskInfo;			//获取循环信息
			}
			
			else if (index == 6 * MAX_EACH_TYPE_COMMAND + 20)
			{
				command_map[index] = &viewWagonInfo;					//查看马车刷新面板
			}
			else if (index == 6 * MAX_EACH_TYPE_COMMAND + 21)
			{
				command_map[index] = &refreshWagonComm;					//花元宝刷新马车
			}
			else if (index == 6 * MAX_EACH_TYPE_COMMAND + 22)
			{
				command_map[index] = &getWagonComm;						//开始护送马车
			}
			else if (index == 6 * MAX_EACH_TYPE_COMMAND + 23)
			{
				command_map[index] = viewWagonRewardComm;				//查看马车对应的奖励
			}
			else if (index == 6 * MAX_EACH_TYPE_COMMAND + 24)
			{
				command_map[index] = wagonIncSpeedComm;				//马车加速
			}
			else if (index == 7 * MAX_EACH_TYPE_COMMAND + 0)
			{
				//已废弃 tory
			}
			else if (index == 7 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &ectypeRewardGoods;		//鐜╁鎶藉彇鍓湰鐗╁搧濂栧姿	added by bison 6.27
			}
			else if (index == 7 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &ectypeRewardAll;			//鐜╁棰嗗彇鎵€鏈夊壇鏈鍔?	added by bison 6.27
			}
			else if(index == 7 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &handleTeamLeaderOperate;	//队长选择挑战副本时，检测队伍的可进入状态和房间空闲状态，如果条件满足，则向队友广播挑战副本的消息 tory 2012.8.16
			}
			else if(index == 7 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &accept_invite;		//收到队长的副本挑战邀请时，队伍成员回复队长邀请	tory 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 10)
			{
				// command_map[index] = &HeroCreateTowerDefTeam;	//鍚戦槦鍛樺悓姝ラ槦闀挎墦寮€閫夋嫨濉旈槻鍓湰鐣岄潰	鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 11)
			{
				// command_map[index] = &TeamLeaderSetPosition;	//鍚戦槦鍛樺悓姝ラ槦闀跨偣閫夋嫨闃熷憳浣嶇疿		鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 12)
			{
				// command_map[index] = &aloneFight;									//鍗曠嫭杩庢晫			鏈夌枒闂甊TX xhm;	2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 13)
			{
				// command_map[index] = &clumpTeammate;								//鍙泦闃熷弸			鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 14)
			{
				// command_map[index] = &startTowerDefWar;								//寮€濮嬪闃叉父鎿	鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 15)	
			{
				// command_map[index] = &apply2TowerDefTeam;							//鐢宠鍔犲叆濉旈槻闃熶紞锿鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 16)
			{
				// command_map[index] = &exitTowerDefTeam;								//閫€鍑哄闃查槦浿	鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 17)
			{
				// command_map[index] = &disbandTowerDefTeam;							//瑙ｆ暎濉旈槻闃熶紿	鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 18)	
			{
				// command_map[index] = &Add2TowerDefTeam;								//娣诲姞濉旈槻闃熶紞浜哄憳(闃熼暱鎵嶆湁鏉冮檺鎿嶄綔)	鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 19)
			{
				// command_map[index] = &creatTowerDefTeam;							//鍒涘缓闃熶紞			鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 20)
			{
				// command_map[index] = &allTowerDefTeamInfo;							//鑾峰彇濉旈槻闃熶紞淇℃伅		鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 21)
			{
				// command_map[index] = &towerDefTeamMemInfo;							//鑾峰彇濉旈槻闃熷憳淇℃伅		鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 22)
			{
				// command_map[index] = &towerDefTeamAppMemInfo;						//鑾峰彇濉旈槻闃熷憳鐢宠鑰呬俊鎭?鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 23)
			{
				// command_map[index] = &TeamLeaderSetHardLevel;						//璁剧疆濉旈槻鍓湰闅惧害			鏈夌枒闂甊TX xhm;	 2012.8.16
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 24)
			{
				// command_map[index] = &ChangeTeamLeader;					
			}else if(index == 7 * MAX_EACH_TYPE_COMMAND + 25)
			{
				// command_map[index] = &ExcludingTeamMem;					
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &viewFiveElemComm;				//鏌ョ湅浜旇灞炴?
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &changFiveElemComm;			//鏇存敼浜旇灞炴?
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &applyMeridInfoComm;			//璇锋眰缁忚剦淇℃伿
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &startMeridComm;				//寮€濮嬬粡鑴変慨鐿
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &strenMeridComm;				//缁忚剦寮哄寲
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &openFiveElemComm;			//寮€鍚汉鐗╀簲琛岀郴缁?
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &useGoodsMeridComm;		//浣跨敤缁忚剦閬撳叿鍑忓皯淇偧鏃堕棿
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 10)
			{
				command_map[index] = &decMeridTimeComm;		//花元宝减少经脉修炼时间
			}
			else if (index == 8 * MAX_EACH_TYPE_COMMAND + 11)
			{
				command_map[index] = &showCampSelect;		//花元宝减少经脉修炼时间
			} else if (index == 8 * MAX_EACH_TYPE_COMMAND + 15)
			{
				command_map[index] = &viewInternalForcesComm;
			} else if (index == 8 * MAX_EACH_TYPE_COMMAND + 16)
			{
				command_map[index] = &openInternalForcesComm;
			} else if (index == 8 * MAX_EACH_TYPE_COMMAND + 17)
			{
				command_map[index] = &addInternalForcesExpComm;
			}
			 else if (index == 8 * MAX_EACH_TYPE_COMMAND + 18)
			{
				command_map[index] = &viewInternalForcesValueComm;
			}
			else if (index == 9 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &bag_operator;					//鑳屽寘鎿嶄綔
			}	
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 1)			//鎽ф瘉鐗╁搿
			{
				command_map[index] = &destoryGoods;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 2)			//鑳屽寘鏍囧織璁剧疿
			{
				command_map[index] = &bagFlagSet;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 3)			//鑳屽寘鏍囧織璁剧疿
			{
				command_map[index] = &bag_useAllGoods;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 4)			//棰嗗彇绂忓埄璁剧疿
			{
							
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 5)			//鐐瑰嚮鑳屽寘鎷撳睿璇锋眰鍏冨疂鏁伴噿
			{
				command_map[index] = &expandReturn;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 6)			//鐐瑰嚮濂栧姳闈㈡澘璇锋眰鏁版嵿
			{
				command_map[index] = &reward_return;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 7)			//批量使用
			{
				command_map[index] = &mulityUse;
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 8)			
			{

			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 9)			//璇锋眰绁炵鍟嗕汉璇︾粏淇℃伿
			{
				command_map[index] = &mysteriousBussiness_return;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 10)			//璇锋眰绁炵鍟嗕汉鍒锋柊
			{
				command_map[index] = &mysteriousBussiness_refresh;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 11)			//绁炵鍟嗕汉璐叿
			{
				command_map[index] = &mysteriousBussinessBuy;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 12)			//鑳屽寘鏁寸悊
			{
				command_map[index] = &bagArrang;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 13)			//帮派商人购入
			{
				command_map[index] = &buyGuildBussiness;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 14)			//帮派商人请求
			{
				command_map[index] = &GuildBussinessRequest;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 15)			//声望商人购入
			{
				command_map[index] = &buyShengWangGoods;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 16)			//声望请求
			{
				command_map[index] = &shengWangBussinessRequest;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 17)			//圣诞活动,领取奖励
			{
				command_map[index] = &XmasRewardResponse;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 18)			//圣诞活动领取奖励请求是否可领
			{
				command_map[index] = &XmasRewardReceive;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 19)			//圣诞活动领取奖励请求是否可领
			{
				command_map[index] = &XmasFasionReceive;				
			}		
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 21)			//玩家捡钱
			{
				command_map[index] = &pickMoney;				
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 22)			//使用高级多倍经验丹 返回
			{
				command_map[index] = &useExpTimesReturn;													
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 23)			//判断是否可以是用随身仓库和随身商店
			{
				command_map[index] = &judgeWarehouseAndShop;													
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 24)			//解绑
			{
				command_map[index] = &setGoodsUnBound;													
			}
			else if(index == 9 * MAX_EACH_TYPE_COMMAND + 25)			//vip
			{
				command_map[index] = &vipInformComm;													
			}			
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 0)			//
			{
				command_map[index] = &petStatus;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 3)			//瀹犵墿杩涘寲鍔熻兿
			{
				command_map[index] = &petEvolution;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 4)			//瀹犵墿娲楃粌鍔熻兿
			{
				command_map[index] = &petSuccinct;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 5)			//瀹犵墿淇℃伅璇锋眿
			{
				command_map[index] = &petRequst;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 6)			//瀹犵墿鏀瑰悕璇锋眿
			{
				command_map[index] = &petModifyName;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 8)			//瀹犵墿鎶€鑳?
			{
				command_map[index] = &petSkillHandle;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 9)			//瀹犵墿鎴樻枟
			{
				command_map[index] = &petFight;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 10)			//瀹犵墿鎶€鑳借繑鍿
			{
				command_map[index] = &petSkillReturn;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 11)			//瀹犵墿鏍忔牸瀛愭暟閲忚繑鍿
			{
				command_map[index] = &petBoxNum;				
			}
			else if(index == 10 * MAX_EACH_TYPE_COMMAND + 12)			//瀹犵墿鏍忔牸瀛愭暟閲忚繑鍿
			{
				command_map[index] = &petJingjie;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 0)			//鐢宠鍔犲叆闃佃惀鎿
			{
				command_map[index] = &enterCampWar;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 1)			//鐢宠閫€鍑洪樀钀ユ垬锛堟垬浜夊紑濮嬶級鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &exitCampWar;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 2)			//鑾峰彇闃佃惀鎴樻埧闂翠汉鏁版儏鍐碉紱鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &getCampWarCounts;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 3)			//鐢宠鎶ュ悕鍙傚姞缁熼鎴樻垨鑰呯洘涓绘垬锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &applyCampWar;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 4)			//鏌ョ湅濂栧姳锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &viewCampWarAwards;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 5)			//棰嗗彇濂栧姳锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &receiveWarAwards;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 6)			//閫夋嫨鏇存敼闃佃惀锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &setCamp;						
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 8)			//澶嶆椿锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &heroCampWarRevival;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 11)			//鏌ョ湅鎺掑悕淇℃伅锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &getRankInfo;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 14)			//鏌ョ湅闃佃惀甯富鍒楄〃淇℃伅锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &viewCampFactionInfo;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 15)			//杩涘叆闃佃惀杈瑰锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &applyCampSence;
			}			
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 16)			//閫€鍑洪樀钀ヨ竟澧冿紱鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &exitCampSence;
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 17)			//鏌ョ湅闃佃惀淇℃伅锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &viewCampInfo;						
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 18)			//璁剧疆骞挎挱锛涙湁鐤戦棶RTX xhm;	
			{
				command_map[index] = &setCampBroadcast;					
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 19)			//璁剧疆缁熼锿鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &setCampViceLeader;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 20)			//璁剧疆缁熼锿鏈夌枒闂甊TX xhm;	
			{
				command_map[index] = &heroCampWarLevalTime;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 27)			//统领战报名剩余时间 RTX xhm;	
			{
				command_map[index] = &getLeaderWarAppLastTime;				
			}
			else if(index == 11 * MAX_EACH_TYPE_COMMAND + 28)			//获取申请列表信息 RTX xhm;	
			{
				command_map[index] = &getLeaderCampWarAppInfo;				
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &createGuildComm;					//鍒涘缓甯淳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &viewGuildPageRankComm;			//鏌ョ湅甯淳鎺掕姒滅殑鏌愰〉淇℃伅 
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &searchOneGuildComm;				//鎼滅储鏌愪釜甯淿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &applyJoinGuildComm;				//鐢宠鍔犲叆甯淿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &viewOneGuildComm;					//鏌ョ湅鏌愪釜甯淳淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &viewMyGuildComm;					//鏌ョ湅鐜╁鎵€鍦ㄥ府娲剧殑甯淳淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &upgradeGuildComm;					//鍗囩骇甯淳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &getGuildRankRewardComm;			//棰嗗彇甯淳鎺掑悕濂栧姳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &changeGuildNoticesComm;			//鏇存敼鍏憿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &exitGuildComm;					//閫€鍑哄府娲?
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 10)
			{
				command_map[index] = &viewGuildMembsListComm;			//鏌ョ湅甯淳鎴愬憳淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 11)
			{
				command_map[index] = &viewGuildApplyListComm;			//鏌ョ湅甯淳鐢宠鍒楄〃淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 12)
			{
				command_map[index] = &removeFromGuildComm;				//鎶婃煇鐜╁绉婚櫎甯淳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 13)
			{
				command_map[index] = &agreeJoinGuildComm;				//鍚屾剰鏌愮帺瀹跺姞鍏ュ府娿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 14)
			{
				command_map[index] = &disagreeJoinGuildComm;			//鎷掔粷鏌愮帺瀹跺姞鍏ュ府娿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 15)
			{
				command_map[index] = &clrGuildApplyListComm;			//娓呴櫎甯淳鐢宠鍒楄?
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 15)
			{
				command_map[index] = &clrGuildApplyListComm;			//娓呴櫎甯淳鐢宠鍒楄?
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 16)
			{
				command_map[index] = &viewGuildSkillInfoComm;			//鏌ョ湅甯淳鎶€鑳戒俊鎭?
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 17)
			{
				command_map[index] = &openGuildSkillComm;				//婵€娲诲府娲炬妧鑿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 18)
			{
				command_map[index] = &upgradeGuildSkillComm;			//鍗囩骇甯淳鎶€鑿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 19)
			{
				command_map[index] = &viewGuildHistoryInfoComm;			//鏌ョ湅甯淳鍘嗗彶淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 20)
			{
				command_map[index] = &viewGuildActivityComm;			//鏌ョ湅甯淳娲诲姩淇℃伅
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 21)
			{
				command_map[index] = &getGuildSignRewardComm;			//棰嗗彇甯淳绛惧埌濂栧姳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 22)
			{
				command_map[index] = &guildDonateComm;					//鐜╁鍚戝府娲炬崘鐚?
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 23)
			{
				command_map[index] = &changeGuildTitleComm;				//璋冩暣甯淳鑱屽姿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 24)
			{
				command_map[index] = &disbandGuildComm;					//瑙ｆ暎甯淳
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 25)
			{ 
				command_map[index] = &agreeGuildAllApplyComm;			//鍚屾剰甯淳鎵€鏈夌敵璇疯€呭姞鍿
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 26)
			{
				command_map[index] = &guildGameComm;					//帮派游戏查看帮派列表
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 27)
			{
				command_map[index] = &refreshGuildTaskComm;
			}
			else if (index == 12 * MAX_EACH_TYPE_COMMAND + 28)
			{
				command_map[index] = &viewFreshGuildTaskInfoComm;
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &analyzeFriendApply;					//鐢宠濂藉弸 鏈夌枒闂甊TX xhm;	
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &analyzeResponseFriendApply;					//濂藉弸鐢宠鍙嶉淇℃伅 鏈夌枒闂甊TX xhm;	
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &FriendlistOperate;					//濂藉弸鍒楄〃鎿嶄綔 鏈夌枒闂甊TX xhm;	
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &BlacklistOperate;					//榛戝悕鍗曞垪琛ㄦ搷浣?鏈夌枒闂甊TX xhm;	
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &viewFriendInfo;					//鏌ョ湅鐜╁濂藉弸淇℃伅鍜岄粦鍚嶅崟淇℃伅锛涙湁鐤戦棶RTX xhm;	
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &handsel_flowers;						
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &find_hero_by_nickName;
			}

			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 7)           //查找好友
			{
				command_map[index] = &findFriendInfo;
			}
			else if (index == 13 * MAX_EACH_TYPE_COMMAND + 8)           //查找好友
			{
				command_map[index] = &findFriend;
			}
			
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &askForBusiness;					//浜ゆ槗璇锋眰
			}
			 else if (index == 14 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &feedbackForAsk;					//浜ゆ槗璇锋眰鍙嶉
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &addGoods;					//娣诲姞鐗╁搧
			}			
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &deleteGoods;					//鍒犻櫎鐗╁搧
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &businessLock;					//浜ゆ槗閿?
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &verifyThisBusiness;					//浜ゆ槗纭
			}
			 else if (index == 14 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &businessCancel;					//鍏抽棴浜ゆ槗
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &npcBusinessBuy;					//浜ゆ槗纭
			}
			 else if (index == 14 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &npcBusinessSell;					//鍏抽棴浜ゆ槗
			}
			 else if (index == 14 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &shopBusiness;					//商城购买物品
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 10)
			{
				command_map[index] = &repair;					//鍟嗗煄涔板崠
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 12)
			{
				command_map[index] = &top_up;					//提取元宝  测试用
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 13)
			{
				command_map[index] = &createStall;					//鍒涘缓鎽婁綅
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 14)
			{
				command_map[index] = &stallBusiness;					//他人买入
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 15)
			{
				command_map[index] = &changeStallCommodityPrice;					//鐗╁搧鏀逛环
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 16)
			{
				command_map[index] = &deleteStallCommodity;					//鐗╁搧涓嬫灦
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 17)
			{
				command_map[index] = &deleteStall;					//鏀舵憡
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 18)
			{
				command_map[index] = &checkStall;					//鏌ョ湅鎽婁綅
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 19)
			{
				command_map[index] = &addCommodity;					//娣诲姞鐗╁搧
			}
			else if (index == 14 * MAX_EACH_TYPE_COMMAND + 20)
			{
				command_map[index] = &changeName;					//鏀瑰悕
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &warehouse_destory;					//鎽ф瘉
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &warehouse_expand;					//浠撳簱鎷撳睍
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &warehouse_saveGoods;					//淇濆瓨鐗╁搧
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &warehouse_takeGoods;					//鍙栧嚭鐗╁搧
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &warehouse_drag;					//鎷栧姩鐗╁搧
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &warehouse_reduction;					//浠撳簱鏁版嵁杩樺帿
			}
			else if (index == 15 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &warehouseArrange;					//浠撳簱鏁版嵁杩樺帿
			}
			else if (index == 16 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &GM_goods;					//gm缁欎簣鐜╁閬撳叿
			}
			else if (index == 16 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &GM_whisper;					//gm缁欎簣鐜╁閬撳叿
			}
			else if (index == 16 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &GM_bugCommit;					//gm信息提交
			}
			else if (index == 17 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &goByNPC;					//鐤捐鐢查┈
			}
			else if (index == 17 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &goActive;					//鐤捐鐢查┈
			}
			else if(index == 18 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &MailSystermCommunicate::get_mail_content;		//获取邮件内容
			} 
			else if(index == 18 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &MailSystermCommunicate::get_mail_txt_list;	//客户端获取邮件列表数据
			} 
			else if(index == 18 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &MailSystermCommunicate::send_mail;			//发送邮件
			}
			else if(index == 18 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &MailSystermCommunicate::info_mail_all;		//请求当前玩家所有邮件的数量	evan add 2012.9.25
			}
			else if(index == 18 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &MailSystermCommunicate::mail_goods_receive;		//閭欢鍐呴檮浠剁墿鍝佺殑鎺ユ敿evan add 2012.9.28
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &viewGuildWarRoomInfoComm;			//鏌ョ湅甯淳鎴樻埧闂翠俊鎿
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &createGuildWarRoomComm;			//鍒涘缓甯淳鎴樻埧闂撮€氫俊
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &challengeGuildWarComm;			//甯垬鎸戞垬閫氫俿
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &callJoinGuildWarComm;				//鍙敜鍔犲叆甯淳鎴?
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &JoinGuildWarComm;					//甯紬鍔犲叆甯淳鎴?
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &prepareGuildWarComm;				//甯富鍑嗗甯淳鎴?
			}
			else if (index == 19 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &exitGuildWarComm;					//甯淳鎴橀€€鍿
			}else if (index == 19 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &revivalInGuildWar;					//甯淳鎴樺娿
			}
			else if(index == 20 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &chooseTitle;				//閫夋嫨澶磋锿
			} 			
			else if(index == 20 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &askTitle;				//璇锋眰鎵€鏈夋嫢鏈夌殑澶磋	
			}			
			else if(index == 20 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &updataCrime;				//鏇存柊缃伓鍊紇ip鏁版嵁璇锋眰	
			} 			
			else if(index == 20 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &cancelTitle;					//鍙栨秷澶磋	
			}  
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &setHangUpInfo;				//璁剧疆鎸傛満鏁版嵁锛涙湁鐤戦棶RTX xhm;	
			} 			
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &getHangUpInfo;				//鑾峰彇鎸傛満鏁版嵁锛涙湁鐤戦棶RTX xhm;		
			}			
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &setShortCutInfo;				//璁剧疆蹇嵎鏍忔暟鎹紱鏈夌枒闂甊TX xhm;		
			} 			
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &getShortCutInfo;				//鑾峰彇蹇嵎鏍忔暟鎹紱鏈夌枒闂甊TX xhm;		
			}  
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 4)
			{
				// command_map[index] = &acceptSkillMsg;				//鎶€鑳芥暟鎹紱
			}
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &setSystemDataInfo;				//璁剧疆绯荤粺璁剧疆鏁版嵁锛涙湁鐤戦棶RTX xhm;		
			}
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &getSystemDataInfo;				//鑾峰彇绯荤粺璁剧疆鏁版嵁锿鏈夌枒闂甊TX xhm;	
			}
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &setOperationDataInfo;				
			}
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &getOperationDataInfo;			
			}
			else if(index == 21 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &getGoldInfo;			
			}  			
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &midasTouchInform;				//点石成金点击请求	
			}    
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &midasTouchReceive;				//点石成金领取奖励	
			}     
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &midasTouchRefresh;				//普通刷新	
			}  
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &midasTouchModify;				//改运	
			} 
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &midasTouchResponse;				//点石成金响应	
			} 
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &wulinTargetReturn;				//请求武林目标数据	
			} 
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &wulinTargetReceive;				//请求武林目标数据	
			} 		
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 8)
			{
				command_map[index] = &onlineRewardRefresh;				//在线奖励普通刷新
			} 	
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 9)
			{
				command_map[index] = &onlineRewardReceive;				//在线奖励领取
			}  			
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 10)
			{
				command_map[index] = &onlineRewardGoldRefresh;				//在线奖励元宝刷新
			} 					
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 11)
			{
				
			} 						
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 12)
			{
				command_map[index] = &onlineRewardReturn;				//在线奖励返回
			} 						
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 13)
			{
				command_map[index] = &rechargeRewardReturn;				//充值奖励返回
			} 					
			else if(index == 22 * MAX_EACH_TYPE_COMMAND + 14)
			{
				command_map[index] = &receiveRechargeReward;				//领取充值奖励
			} 
			else if(index == 23 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &getHeroAttribute;				//请求指定角色属性数据
			} 	
			else if(index == 23 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &getHeroInfor;					//获取指定角色ID的资料
			} 
			else if(index == 23 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &saveHeroInfor;				//保存角色的个人资料
			}else if(index == 24 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &recharge_srv_msg;				//充值服务器消耗掉刀币处理。
			} 
			else if (index == 26 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &upgrade_hero_skill_comm;		//学习升级技能
			}
			else if (index == 26 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &view_hero_skills_comm;		//学习升级技能
			}
			else if (index == 26 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &use_skill_comm;			//使用技能返回
			}
			else if (index == 26 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &olderDish;			//点菜
			}
			else if (index == 27 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &fingerGuessGameAi;			//猜拳ai
			}
			else if (index == 27 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &enterFingerGuessGame;			//玩家加入游戏
			}
			else if (index == 27 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &exitFingerGuessGame;			//玩家退出游戏
			}
			else if (index == 27 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &FingerGuessGamePlayer;			//玩家猜拳游戏
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &collectGoodsComm;					//采集物通信
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &enterCampRom;		//进入自己帮派大本营
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &pickPetToBox;		//捉宠
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &acceptActiveCode;		//读取激活码领奖励
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &acceptCdkeySrv;		//读取激活码领奖励
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &acceptCdkeySrvSuccess;		//读取激活码领奖励
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 6)
			{
				command_map[index] = &testVip;					//体验vip
			}
			else if (index == 28 * MAX_EACH_TYPE_COMMAND + 7)
			{
				command_map[index] = &returnVipFreeNumber;					//体验vip
			}
			else if (index == 29 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &fire_shuai_pao_comm;			//摔炮
			}
			else if (index == 29 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &fire_yan_hua_comm;			//放烟花
			}
			else if (index == 30 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &rideDetailComm;			//坐骑详细信息
			}
			else if (index == 30 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &rideTakeOffEquip;			//坐骑脱装备
			}
			else if (index == 30 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &rideEvolutionComm;			//坐骑进阶
			}
			else if (index == 30 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &rideFinalSkillComm;			//坐骑最终技能相关
			}
			else if (index == 31 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &prepareRideComm;				//乘骑准备
			}
			else if (index == 31 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &startRideComm;				//开始乘骑(也是由客户端发起的动作)
			}
			else if (index == 31 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &stopRideComm;					//下马请求
			}
			else if (index == 32 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &viewCampResWarInforComm;
			}
			else if (index == 32 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &entCampResWarComm;
			}
			else if (index == 32 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &exitCampResWarComm;
			}
			else if (index == 32 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &campResWarViewHeroResNumComm;
			} 
			else if (index == 32 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &getCampResWarComm;
			} 
			else if (index == 33 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &purchaseFatigue;
			}
			else if (index == 34 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &viewRobFlagWarRoomInfoComm;
			}
			else if (index == 34 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &enterRobFlagWarRoomComm;
			}
			else if (index == 34 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &exitRobFlagWarRoomComm;
			}
			else if (index == 34 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &callJoinRobFlagWarRoomComm;
			}
			else if(index == 34 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &prepareRobFlagWarRoomComm;
			}
			else if (index == 33 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &enterTowerLayerCopy;
			} 
			else if (index == 33 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &swapTowerLayerCopy;
			} 
			else if (index == 33 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &brushTower;
			}			
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 0)
			{
				command_map[index] = &levelRewardReturn;
			}
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 1)
			{
				command_map[index] = &levelRewardReceive;
			}
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 2)
			{
				command_map[index] = &levelRewardExist;
			}
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 3)
			{
				command_map[index] = &reward_return;
			}
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 4)
			{
				command_map[index] = &receiveWelfare;
			}
			else if (index == 36 * MAX_EACH_TYPE_COMMAND + 5)
			{
				command_map[index] = &receiveSignReward;
			}

#if 0			
			else if(index == 35*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &pullPerson;					//刷新地图内的所有队伍信息	
			}				
			else if(index == 35*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &pullPersonByNickName;					//刷新地图内的所有队伍信息	
			}
			else if(index == 35*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index] = &responsePullPerson;					//刷新地图内的所有队伍信息	
			}	
			else if(index == 35*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &outGroup;					//刷新地图内的所有队伍信息	
			}				
			else if(index == 35*MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index] = &whisper;					//刷新地图内的所有队伍信息	
			}				
			else if(index == 35*MAX_EACH_TYPE_COMMAND+5)
			{
				command_map[index] = &offNewGroupId;					//刷新地图内的所有队伍信息	
			}	
#endif			

			else if(index == 37*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &acceptTeamState;					
			}	
			
			else if(index == 37*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &acceptOtherHeroTeamState;						
			}	
			
			else if(index == 37*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index] = &inviteHeroJoinTeam;						
			}	
				
			else if(index == 37*MAX_EACH_TYPE_COMMAND+3)
			{
				command_map[index] = &applyForInTeam;						
			}	
			
			else if(index == 37*MAX_EACH_TYPE_COMMAND+4)
			{
				command_map[index] = &responseInviteHeroJoinTeam;						
			}
			
			else if(index == 37*MAX_EACH_TYPE_COMMAND+5)
			{
				command_map[index] = &agreeApplyForInTeam;						
			}	

			else if(index == 37*MAX_EACH_TYPE_COMMAND+6)
			{
				command_map[index] = &offTeam;						
			}	
			else if(index == 37*MAX_EACH_TYPE_COMMAND+7)
			{
				command_map[index] = &disMissTeam;						
			}	
			else if(index == 37*MAX_EACH_TYPE_COMMAND+8)
			{
				command_map[index] = &transferTeamLeader;						
			}	
			else if(index == 37*MAX_EACH_TYPE_COMMAND+9)
			{
				command_map[index] = &kickOutTeam;						
			}
			else if(index == 38*MAX_EACH_TYPE_COMMAND+0)
			{
				command_map[index] = &viewCampLeader;						
			}	
			else if(index == 38*MAX_EACH_TYPE_COMMAND+1)
			{
				command_map[index] = &changeCampNotice;						
			}	
			else if(index == 38*MAX_EACH_TYPE_COMMAND+2)
			{
				command_map[index] = &viewGuildScoreList;						
			}	
		}
	}
}








