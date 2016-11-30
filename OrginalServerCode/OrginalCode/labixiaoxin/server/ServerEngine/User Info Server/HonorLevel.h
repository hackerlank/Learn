
/********************************************************************
    创建时间：    2015/08/19  14:43:59 
    文件名：      HonorLevel.h
    作者：        xxj
    
    功能:		1.pvp 排行榜相关 竞技场
				2.
                
    说明:		1. 
                2. 
*********************************************************************/
#pragma once
#include "..\ace\Basic_Types.h"
#include "..\GameBase\Common\GameDefine.h"
#include <set>
#include <map>
#include <vector>

//flag 标记位
#define HL_Flag_Clear 0			//清除状态
#define HL_Flag_init 1			//初始化
#define HL_Flag_start 2			//进行中
#define HL_Flag_end 3			//完成 加载
#define HL_Flag_end_ex 4		//完成 发邮件
#define HL_Flag_get_reword 5	//已完成发奖


class UserInfoMgr;

class CHonorLevel
{
public:
	CHonorLevel();
	void SetSuper(UserInfoMgr * pSuper);
public:
	void add(HLInfo &info);
	void update(HLInfo & info,ACE_INT32 oldHonour);
	void Clear();
	void DoOnTimerOut();
	int  GetRanking(ACE_INT32 honour);//获取排名
	bool ChoiceFightRoole(const HLInfo & info,HLInfoArray & _array,HLInfo * quitList);//选择角色
	void ChoiceFightRooleEx(HLInfoArray & _array,ACE_UINT32 _characterID);//选择角色

	ACE_UINT32 m_unCount;
	HLInfo m_list[MAX_HONOUR_LEVEL_COUNT + 1];//多预留一个做缓存区//
	ACE_UINT32 GetSumNum();//获取多少人参加了这个赛季//
private:
	void InsertionSort(HLInfo & info);
	bool DoLoadHL();//发奖 加载数据
	bool DoSendWeakReword();//发奖
	void DoSendDayReword();//发送每日奖励
	void DoSendRankReword();//发送赛季奖励
	void UpdateLevelMap(const HLInfo & honour,bool isAdd);//更新荣誉排名
	void UpdateHonorLevelMap(const HLInfo & honour,bool isAdd);//更新荣誉排名
	ACE_INT32 GetHLevel(ACE_INT32 honour);//得到段位
	bool TryAdd(std::set<ACE_UINT32> & quitList,ACE_UINT32 id);//试着加入

	void OnSendMail(const HLInfo & info,ACE_INT32 behaviorID,ACE_UINT32 unMailId,ACE_UINT32 parm);//发邮件

	std::vector<HLInfo> m_verHLinfo;//缓存数据
	UserInfoMgr * m_pUserInfoCallback;//用于处理消息

	std::map<ACE_INT32,ACE_UINT32> m_levelMap;//每个荣誉值中用户个数 用于得到当前玩家排名
	std::map<ACE_INT32,std::vector<HLInfo> > m_honorlevelMap;//每个段位等级中的玩家排名
	std::set<ACE_UINT32> m_characterKey;//已参加的用户列表 用于区分是否已经参加
	ACE_INT32 m_flag;//标记位
	bool m_isRestart;//是否一个赛季结束
	ACE_INT32 m_max;
	ACE_INT32 m_min;
};