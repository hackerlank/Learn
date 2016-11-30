#include "MapMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#include "..\GameBase\res\GameConfig.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

MapMgr::MapMgr(ACE_UINT32 unID)
:SubAdapter(unID)
{
	m_unMaxChild = 8192;
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");

	m_doubleDropTimerHandler = NULL;
	init_timer();
}

MapMgr::~MapMgr()
{
	uninit_timer();
}

BaseObj *MapMgr::new_child_obj(ACE_UINT32 unID)
{
	return new Map(unID, this);
}

bool MapMgr::init_timer()
{
	if (m_doubleDropTimerHandler == NULL)
	{
		GameConfig *pConfig = GAME_CONFIG_INSTANCE::instance();
		if (pConfig == NULL)
		{
			return false;
		}
		int iWeekTime = GameUtils::get_week_time(GameUtils::get_utc());
		ACE_UINT32 unStartTime = iWeekTime % pConfig->m_unRefreshDoubleDropSecs;  //此时的配置已经读完了
		pConfig->m_unRefreshDoubleDropVersion = iWeekTime / pConfig->m_unRefreshDoubleDropSecs;
		if ((m_doubleDropTimerHandler = TIMER_MGR_INSTANCE::instance()->registerTimer(this, DoubleDropTimerCallback, NULL, ACE_Time_Value(unStartTime, 0), ACE_Time_Value(pConfig->m_unRefreshDoubleDropSecs, 0))) == NULL)
		{
			return false;
		}
	}
	return true;
}

void MapMgr::uninit_timer()
{
	if(m_doubleDropTimerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_doubleDropTimerHandler->m_lTimerID);
		delete m_doubleDropTimerHandler;
		m_doubleDropTimerHandler = NULL;
	}
}

void MapMgr::DoubleDropTimerCallback(void *p, long lTimerID)
{
	printf("-------------------DoubleDropTimerCallback\n");
	MapMgr *pMgr = static_cast<MapMgr *>(p);
	if (pMgr != NULL)
	{
		pMgr->DoDoubleDropTimer();
	}
}

void MapMgr::DoDoubleDropTimer()
{
	GameConfig *pConfig = GAME_CONFIG_INSTANCE::instance();
	if (pConfig == NULL)
	{
		return;
	}
	ACE_UINT32 unSeq = GameUtils::get_week_time(GameUtils::get_utc()) / pConfig->m_unRefreshDoubleDropSecs;
	if (unSeq < pConfig->m_vecDoubleDropMap.size())
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
		pConfig->m_unRefreshDoubleDropVersion = unSeq;

		/*MsgDoubleDropListResponse &response = pConfig->m_globalDoubleDropResponse;
		response.nResult = 0;
		int i=0;
		std::map<UINT32, ACE_Byte>::iterator itMap = pConfig->m_vecDoubleDropMap[unSeq].begin();
		for (;i<MAX_DOUBLE_DROP_COUNT && itMap!=pConfig->m_vecDoubleDropMap[unSeq].end();++itMap, ++i)
		{
			response.doubleDropList[i].unRawMapID = itMap->first;
			response.doubleDropList[i].byType = itMap->second;
		}
		response.iCount = i;*/
	}
}