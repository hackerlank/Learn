#include "BuyEnergyCost.h"

BuyEnergyCostRes::BuyEnergyCostRes( )
{

}

BuyEnergyCostRes::~BuyEnergyCostRes()
{

}

void BuyEnergyCostRes::AddOne(const BuyEnergyCost & cost )
{
	if (cost.buy_count>m_maxBuy.buy_count )
	{
		m_maxBuy = cost;
	}

	m_mapBuyEnergyCost[cost.buy_count] = cost;
}

BuyEnergyCost BuyEnergyCostRes::GetOne( ACE_UINT32 unSetp )
{
	if (unSetp >= m_maxBuy.buy_count)
		return m_maxBuy;
	else
		return m_mapBuyEnergyCost[unSetp];
}
