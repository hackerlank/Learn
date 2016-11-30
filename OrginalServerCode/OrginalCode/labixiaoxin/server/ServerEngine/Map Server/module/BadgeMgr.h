#ifndef __BADGE_MGR_H_
#define __BADGE_MGR_H_
#include "BaseModule.h"
#include <vector>

struct tagGaintFlag
{
	tagGaintFlag()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 flag[2];//1.固定值/2.百分比
};
struct ChargeBeginInfo
{
	ChargeBeginInfo()
	{
		ZeroVar(*this);
	}
	BadgeInfo m_old;
	BadgeInfo m_new;
};
class CBadgeMgr : public BaseModule
{
public:
	CBadgeMgr();
	~CBadgeMgr();
public:
	void init(MsgDBBadgeList * list);//初始化
	bool TryAddBadge(ACE_UINT32 equipmentID);//试着增加一个徽章
	
	void send_Gaint_info(ACE_UINT32 unSN);
	void DoCharge_Add_Begin();
	bool DoCharge_Add(const ItemInfo *itemInfo,ACE_UINT32 & powerPoint);//充能 装备
	bool DoCharge_Add(ACE_UINT32 tuzhiID,ACE_UINT32 & powerPoint);//充能 图纸
	void DoCharge_Add_After();//充能
	int GetGaintPage(MsgGETBadgeResponse & response,ACE_UINT32 unPage,bool isClear);
	double GetCoinGaint();
	double GetPowerPointGaint();
	bool isUnlock();//是否已经解锁
private:
	std::map<ACE_UINT32, BadgeInfo> m_mapBadge;//当前徽章列表
	//加成目标加成目标（16进制）1.全体2.队长characterID.指定角色（最多3人，逗号分割）
	//增益类型：加成类型(1.攻击加成/2.生命加成/3.暴击加成/4.韧性加成/5.贝壳收益/6.合金收益)，数值类型(1.固定值/2.百分比)
	std::map<ACE_UINT32,std::map<ACE_UINT32,tagGaintFlag> >m_mapGaint;//<加成目标<增益类型,百分比>>
	bool HaveBadgeByID(ACE_UINT32 badgeID);//判断是否已经有此徽章了
	BadgeInfo * GetBadgeByID(ACE_UINT32 badgeID);//获取此徽章
	void UpdateGaint();//更新加成目标，更新曾益
	//void UpdateGaint(const BadgeInfo & old,const BadgeInfo & _new);
	void update_2_db(ACE_UINT32 badgeID);
	void GetGaintInfo(std::vector<MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo> & ver);
	ACE_UINT32 GetLeve(ACE_UINT32 unID,ACE_UINT32 chargeNum);//得到等级
	std::map<ACE_UINT32,ChargeBeginInfo> m_chargeVer;

	ACE_UINT32 m_scheme_badge;//解锁等级

private:
	std::map<ACE_UINT32,int> m_playerListMap;
	void UpdatePlayerListMap();
	bool CanUse(ACE_UINT32 BadgeID);//是否能获取
};

#endif
