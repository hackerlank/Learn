#pragma once

#include "DBHandlerMgr.h"
#include "DBHomeHandler.h"

class DBHomeMgr : public DBHandlerMgr
{
public:
	DBHomeMgr(ACE_UINT32 unID);
	virtual ~DBHomeMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};

	bool init_timer();

	void uninit_timer();

	static void ACUtimerCallback(void *p, long lTimerID);
	void DoACUStatistics();

	int LoadStatistics(const ACE_UINT32 dwType, const char *strDate,ACE_UINT32 * paramList);

	void LoadACU();
	void LoadPCU();

	void SaveACU();
	void SavePCU();

	void destroy_db_res(sql::PreparedStatement *& prep_stmt, sql::ResultSet *& db_res);

	//long m_lTimerID;
	BaseTimerHandler *m_serviceACUTimerHandler;

	ACE_UINT32 m_unPCU;
	ACE_UINT32 m_unCurrentTimes;

	time_t m_tLastReloadTime;

	time_t m_tLastStatisticsTime;
	ACE_UINT32 m_ACUList[Statistics_ACU_Num];
	ACE_UINT32 m_ACU;
};

