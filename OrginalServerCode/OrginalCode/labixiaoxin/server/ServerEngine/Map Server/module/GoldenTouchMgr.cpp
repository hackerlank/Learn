#include "GoldenTouchMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

GoldenTouchMgr::GoldenTouchMgr()
{
	m_unUsedTouchCount = 0;
	m_buy_gold_limit =0;
}

GoldenTouchMgr::~GoldenTouchMgr()
{

}

void GoldenTouchMgr::init(ACE_UINT32 unUsedTouchCount) 
{
	m_unUsedTouchCount = unUsedTouchCount;
}

void GoldenTouchMgr::update_2_db()
{
	MsgDBUpdateGoldenTouchRequest *db_request = (MsgDBUpdateGoldenTouchRequest *)public_send_buff;
	db_request->m_unUsedCount = m_unUsedTouchCount;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_GOLDEN_TOUCH_REQUEST, (char *)db_request, sizeof(MsgDBUpdateGoldenTouchRequest));
}

void GoldenTouchMgr::update_GoldMax( ACE_UINT32 nMax,bool is )
{
	m_buy_gold_limit = nMax;
}
