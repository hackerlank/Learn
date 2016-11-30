#include "EnergyMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\Map.h"

EnergyMgr::EnergyMgr()
{
	m_unExtraLimit = 0;
	m_unEnergyEx = 0;

	m_unMaxEnergy = GAME_CONFIG_INSTANCE::instance()->m_unMaxEnergy;
	m_unRestoreInterval = GAME_CONFIG_INSTANCE::instance()->m_unEnergyRestoreInterval;
	m_unRestoreEnergyGold = GAME_CONFIG_INSTANCE::instance()->m_unRestoreEnergyGold;
}

EnergyMgr::~EnergyMgr()
{

}

void EnergyMgr::init(ACE_UINT32 unEnergy, ACE_UINT32 unRestoreTime)
{
	m_unMaxEnergy = GAME_CONFIG_INSTANCE::instance()->m_unMaxEnergy + m_map->m_unLevel / 2;
	m_unEnergy = unEnergy;
	m_unRestoreTime = unRestoreTime;
	//m_unBuyTime = unBuyTime;
	//m_unBuyCount = unBuyCount;
	update(GameUtils::get_utc());
}

void EnergyMgr::update(ACE_UINT32 unCurrentTime)
{
	int tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;
	if(m_unEnergy >= tmp_max)
	{
		//m_unEnergy = tmp_max;
		return;
	}

	int t = unCurrentTime - this->m_unRestoreTime;
	
	int c = (int)(t / m_unRestoreInterval);

	if (c>0)
	{
		int m = (int)(t % m_unRestoreInterval);

		m_unEnergy += c;

		if(m_unEnergy >= tmp_max)
		{
			m_unEnergy = tmp_max;
		}

		m_unRestoreTime = unCurrentTime - m;

		update_2_db();
	}
}

int EnergyMgr::increase(int v)
{
	if(v == 0)
	{
		return 0;
	}

// 	int tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;
// 
// 	if(v > tmp_max)
// 	{
// 		v = tmp_max;
// 	}

	m_unEnergy += v;
	
	/*
	if(m_unEnergy >= tmp_max)
	{
		m_unEnergy = tmp_max;
	}
	*/
	
	update_2_db();

	return 0;
}

int EnergyMgr::decrease(int v)
{
	int t = (int)m_unEnergy;
	bool flag = false;
	int tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;
	if(m_unEnergy >= tmp_max)
	{
		flag = true;
	}
	t = t - v;
	if(t < 0)
	{
		t = 0;
	}

	m_unEnergy = t;

	if(flag && m_unEnergy < tmp_max)
	{
		m_unRestoreTime = GameUtils::get_utc();
	}

	update_2_db();

	return 0;
}


int EnergyMgr::set_full()
{
	int tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;

	if(m_unEnergy >= tmp_max)
	{
		return -1;
	}

	m_unEnergy = tmp_max;

	update_2_db();

	return 0;
}

int EnergyMgr::need_value_2_full()
{
	int tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;

	if(m_unEnergy >= tmp_max)
	{
		return 0;
	}

	return (tmp_max - m_unEnergy);
}

void EnergyMgr::update_2_db()
{
	/*
	MsgDBUpdateEnergyRequest db_request;
	db_request.unEnergy = m_unEnergy;
	db_request.unRestoreTime = m_unRestoreTime;
	db_request.unEnergyBuyCount = m_unBuyCount;
	db_request.unEnergyBuyTime = m_unBuyTime;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_ENERGY, (char *)&db_request, sizeof(MsgDBUpdateEnergyRequest));
	*/
	m_map->update_energy_2_db();
}

void EnergyMgr::handle_event(BaseEvent *e)
{
	if(ACE_OS::strcmp(e->m_name, GAME_EVENT_LEVEL_UP) == 0)
	{
		m_unMaxEnergy = GAME_CONFIG_INSTANCE::instance()->m_unMaxEnergy + m_map->m_unLevel / 2;
	}
	else
	{
		m_unExtraLimit = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_ENERGY_LIMIT, 0);
		m_unRestoreInterval = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_ENERGY_RESTORE, (float)m_unRestoreInterval);
	}
}

bool EnergyMgr::is_enough(int v)
{
	int t = (int)m_unEnergy;
	if(t >= v)
	{
		return true;
	}

	return false;
}

void EnergyMgr::update_EnergyMax( ACE_UINT32 energyMax,bool is )
{
	m_unEnergyEx = energyMax;
}

bool EnergyMgr::CanBuy()
{
	ACE_UINT32 tmp_max = m_unMaxEnergy + m_unExtraLimit + m_unEnergyEx;

	return m_unEnergy < tmp_max;
}
