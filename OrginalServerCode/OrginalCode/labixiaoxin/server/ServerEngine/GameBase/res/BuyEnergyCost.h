#ifndef __BUYENERGYCOST_H_
#define __BUYENERGYCOST_H_
#include "BaseRes.h"
typedef struct tagBuyEnergyCost
{
	tagBuyEnergyCost()
	{
		buy_count = 0;
		cost = 0;
		Energy_Recover = 0;
	}
	ACE_UINT32 buy_count;//使用次数
	ACE_UINT32 cost;//金卡消耗 超过填表次数，按最大次数添加"
	ACE_UINT32 Energy_Recover;//每次恢复体力的量
}BuyEnergyCost;

class BuyEnergyCostRes
{
public:
	BuyEnergyCostRes();
	virtual ~BuyEnergyCostRes();
	void AddOne(const BuyEnergyCost & cost);
	BuyEnergyCost GetOne(ACE_UINT32 unSetp);
private:
	std::map<ACE_UINT32 , BuyEnergyCost> m_mapBuyEnergyCost;
	BuyEnergyCost m_maxBuy;
};

#endif