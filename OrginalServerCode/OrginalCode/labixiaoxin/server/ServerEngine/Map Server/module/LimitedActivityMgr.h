#ifndef __LIMITEDACTIVITYMGR_H_
#define __LIMITEDACTIVITYMGR_H_

#include "ace/ace.h"
#include "BaseModule.h"
#include "../../GameBase/res/RechargeRes.h"

class LimitedActivityMgr : public BaseModule
{
public:
// 	
// 
// 	bool AddTask(ACE_UINT32 unNewTaskID);
// 	bool RefreshTask(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID);
// 	bool GetReward(ACE_UINT32 unTaskID, RewardInfo &oRewardInfo);
// 
// 	void BuildTaskListPkg(MsgTaskList &response);
public:
	void init(MsgDBLimitedActivityList * list);//初始化

	int GetReward(ACE_UINT32 unLAMissionID, RewardInfo &oRewardInfo);//获取奖励品
	LimitedActivityMissionConfig FindLAmissionItem(ACE_UINT32 unLAMissionID);//查找限时活动任务id
	LimitedActivityConfig FindLAItem(ACE_UINT32 unLAID);//查找限时活动任务id
	void Refresh();//更新
	void RefreshNew();//从配置文件中更新进度
	void RefreshOld();//删除老数据

	int GetLACurrentList(MsgGMLimitedActivityListResponse & response);//获取列表

	int ChickLARecharge(const RechargeRes * res);//检查限时活动是否在之内

	void Cost_basic_info(int nCoin, int nMoney, int nExp, int nPowerPoint, int nHonour, int nFriendship);//消费类 货币信息
	bool DoLATypeLinkcost(ACE_UINT32 unLAMissionType,CostInfoList & costList/*,int times*/);//关联类型,消费类任务，需要记录先决条件，达到之后由用户主动申请奖品
	bool DoLATypeLuck(ACE_UINT32 unLAMissionType,const CostInfoList & costList,ACE_UINT32 unMissionType = 1/*,int times*/);//关联类型,抽奖任务，需要记录先决条件，达到之后由用户主动申请奖品
	bool DoLATypeSecret(ACE_UINT32 unLAMissionType,CostInfoList & costList/*,int times*/);//关联类型,神秘商店打折，立刻折扣
	bool DoLATypeMapCount(ACE_UINT32 unMapID,ACE_UINT32 type,ACE_UINT32 & nMult);//关卡上限倍数
	bool DoLATypeLeveUP(ACE_UINT32 unLAtype,ACE_UINT32 & nMult);//强化折扣
	bool DoLATypeLinkRecharge(ACE_UINT32 unLAMissionType,ACE_UINT32 nGold/*,int times*/);//关联类型,充值类任务，需要记录先决条件，达到之后由用户主动申请奖品
	bool DoLATypeLinkRechargeGift(ACE_UINT32 unProductId);//限时礼包活动
	bool DoLATypeLogin();//连续登录
private:
	//通过类型查找并执行回调
	template<class T>
	bool DoActionFindByType(ACE_UINT32 unType,ACE_INT32 unLAType,T &t,/*int times,*/bool(LimitedActivityMgr::*CallFun)(ACE_INT32,LimitedActivityInfo &,T &/*,int*/));

	bool CallFun_Cost(ACE_INT32 unLAMissionType,LimitedActivityInfo & info,CostInfoList & costList/*,int times*/);
	bool CallFun_Luck(ACE_INT32 unLAMissionType,LimitedActivityInfo & info,ACE_UINT32 & unMissionType/*,int times*/);
	bool CallFun_Secret(ACE_INT32 unLAMissionType,LimitedActivityInfo & info,CostInfoList & costList/*,int times*/);
	bool CallFun_MapCount(ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nMult/*,int times*/);
	bool CallFun_LeveUp(ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nMult/*,int times*/);
	bool CallFun_Recharge(ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nGold/*,int times*/);
	bool callFun_RechargeGift(ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & unProductId);
	bool callFun_Login(ACE_INT32 unLAMissionType,LimitedActivityInfo & info,ACE_UINT32 & unTimes);

public://红点//
	bool m_isHaveNew;
	void isDown(ACE_UINT32 unLAMissionID);//是否已经做完了//
private:
	bool ChickCanGetReward(ACE_UINT32 unLAMissionID,ACE_INT32 & unProgress,LimitedActivityInfo *& pLa);
	bool ChickTimeIsInActivity(LimitedActivityConfig & laconfig );//判断当前时间是否在活动范围内
	void update_2_db();
	void update_2_db(const LimitedActivityInfo & laconfig);
	std::map<ACE_UINT32, LimitedActivityInfo> m_mapCurrentLA;//当前活动任务列表
};

template<class T>
bool LimitedActivityMgr::DoActionFindByType( ACE_UINT32 unType,ACE_INT32 unLAType,T & t/*,int times*/,bool(LimitedActivityMgr::*CallFun)(ACE_INT32,LimitedActivityInfo &,T &/*,int*/) )
{
	Refresh();//事件刷新
	std::map<ACE_UINT32, LimitedActivityInfo>::iterator it = m_mapCurrentLA.begin();//当前活动任务列表
	while(it != m_mapCurrentLA.end())
	{
		if (it->second.unLinkType == unType)
		{
			if ((this->*CallFun)(unLAType,it->second,t/*,times*/))
			{
				return true;
			}
		}
		it++;
	}
	return false;
}

#endif
