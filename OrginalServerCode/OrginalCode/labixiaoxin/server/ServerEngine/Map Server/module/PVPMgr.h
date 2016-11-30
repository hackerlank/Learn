#pragma once
/********************************************************************
    创建时间：    2015/08/18  15:20:51 
    文件名：      PVPMgr.h
    作者：        xxj
    
    功能:		1.pvp相关类
				2.
                
    说明:		1. honour = -1表示本赛季未参加
                2. 
*********************************************************************/

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

class PVPMgr:public BaseModule//, public EventListener
{
public:
	PVPMgr();
	void init(PVPInfo & info);
	void update();
	bool DoFreashen();//刷新
	void OnDo();
	virtual void update(ACE_UINT32 unCurrentTime);

	void update_pvp_Info(PVPInfoEx & info);
	void DoDayChange();
	void GetQuitList(HLInfo *list);
public:
	void EnterPVPFight(HLInfoArray & _array);//开始战斗
	void update_TimesMax(ACE_UINT32 nMax,bool is);
	int BuyTimes();//买次数
	int EnterMap();//进入地图
	int AccountsMap(FightRecordInfo & info,ACE_INT32 & score);//结算
	
	//更新基础信息
	void update_Info_2_db(bool isToUserServer);
	void update_honour(HLInfo & info);
public:
	PVPInfo m_pvpInfo;
	HLInfoArray m_array;
	ACE_UINT32 m_scheme_arena;//竞技场解锁等级

private:
	ACE_INT32 m_unRestoreInterval;
	ACE_UINT32 m_unRestoreAmount;
	ACE_INT32 m_oldHonour;
	ACE_UINT32 m_buy_pvp_limit;
	
	bool isEnter;
};