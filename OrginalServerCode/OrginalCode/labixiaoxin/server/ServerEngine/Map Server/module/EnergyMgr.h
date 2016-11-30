#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

class EnergyMgr : public BaseModule, public EventListener
{
public:
	EnergyMgr();
	~EnergyMgr();

	void init(ACE_UINT32 unEnergy, ACE_UINT32 unRestoreTime);
	virtual void update(ACE_UINT32 unCurrentTime);

	int increase(int v);
	int decrease(int v);

	bool CanBuy();//是否能买体力

	int set_full();

	int need_value_2_full();

	bool is_enough(int v);

	virtual void handle_event(BaseEvent *e);

	ACE_UINT32 m_unEnergy;
	ACE_UINT32 m_unRestoreTime;
	//ACE_UINT32 m_unBuyTime;
	//ACE_UINT32 m_unBuyCount;

	ACE_UINT32 m_unExtraLimit;
	ACE_UINT32 m_unEnergyEx;

	ACE_UINT32 m_unMaxEnergy;
	ACE_UINT32 m_unRestoreInterval;
	ACE_UINT32 m_unRestoreEnergyGold;

	void update_EnergyMax(ACE_UINT32 energyMax,bool is);
private:
	void update_2_db();
};