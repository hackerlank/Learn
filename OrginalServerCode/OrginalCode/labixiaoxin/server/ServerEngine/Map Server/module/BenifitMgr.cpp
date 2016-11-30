#include "BenifitMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\VipRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "VipMgr.h"
#include "..\Map.h"
#include "ActivityMgr.h"

BenifitMgr::BenifitMgr()
{
	init_static_benefit();
}

BenifitMgr::~BenifitMgr()
{

}

void BenifitMgr::init()
{
}

void BenifitMgr::update(ACE_UINT32 unCurrentTime)
{
	
}


void BenifitMgr::update_2_db()
{
	
}

void BenifitMgr::handle_event(BaseEvent *e)
{
	VipRes *res = m_map->m_vipMgr.m_currentVipRes;

	int i;

	

	/*
	ACE_OS::memset(m_benefitList, 0, sizeof(BenefitValueInfo) * BENEFIT_TYPE_MAX);

	for(i = 0;i < GAME_CONFIG_INSTANCE::instance()->m_unInitBenefitCount;i ++)
	{
		benefitRes = (BenifitRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_InitBenefitList[i]);

		add_benefit(benefitRes);
	}
	*/
	init_static_benefit();

	BenifitRes *benefitRes;

	if(res != NULL)
	{
		for(i = 0;i < res->m_unBenefitCount;i ++)
		{
			benefitRes = (BenifitRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(res->m_benifitList[i]);

			add_benefit(benefitRes);
		}
	}

	m_map->dispatch_map_event(GAME_EVENT_MAX_LIMIT_CHANGE);
}

void BenifitMgr::add_benefit(BenifitRes *benefitRes)
{
	if(benefitRes == NULL)
	{
		return;
	}

	int i;

	for(i = 0;i < benefitRes->m_benefitList.unCount;i ++)
	{
		int idx = benefitRes->m_benefitList.list[i].unBenefitID;
		if(benefitRes->m_benefitList.list[i].unType == 1)
		{
			//m_benefitList[idx].fScale += benefitRes->m_benefitList.list[i].fValue;
			m_benefitList[idx].unScale += benefitRes->m_benefitList.list[i].unValue;
		}
		else if(benefitRes->m_benefitList.list[i].unType == 2)
		{
			//m_benefitList[idx].fValue += benefitRes->m_benefitList.list[i].fValue;
			m_benefitList[idx].unValue += benefitRes->m_benefitList.list[i].unValue;
		}
	}
}

int BenifitMgr::get_benefit(ACE_UINT32 unID, float base_value)
{
	int ret = 0;

	if(unID == BENEFIT_TYPE_ENERGY_RESTORE || unID == BENEFIT_TYPE_LUCK_COST)
	{
		ret = (int)((base_value - m_benefitList[unID].unValue) * (1000 - m_benefitList[unID].unScale) / 1000);
	}
	else
	{
		ret = (int)((m_benefitList[unID].unValue + base_value) * (1000 + m_benefitList[unID].unScale) / 1000);
	}

	if(ret < 0)
	{
		ret = 0;
	}

	return ret;
}

void BenifitMgr::init_static_benefit()
{
	BenifitRes *benefitRes;

	ACE_OS::memset(m_benefitList, 0, sizeof(BenefitValueInfo) * BENEFIT_TYPE_MAX);

	int i;

	for(i = 0;i < GAME_CONFIG_INSTANCE::instance()->m_unInitBenefitCount;i ++)
	{
		benefitRes = (BenifitRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_InitBenefitList[i]);

		add_benefit(benefitRes);
	}

	/*
	int count = 0;

	ACE_UINT32 *list = ACTIVITY_MGR_INSTANCE::instance()->get_related_list_by_type(ITEM_RES_TYPE_BENIFIT, count);

	for(i = 0;i < count;i ++)
	{
		benefitRes = (BenifitRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

		add_benefit(benefitRes);
	}
	*/
}