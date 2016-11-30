// Cluster Manager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "src\ClusterMgrService.h"
#include "ace\OS_main.h"
#include "ace\ACE.h"


int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{
	ClusterMgrService ts;

	ts.Startup(CLUSTER_MANAGER_ID, SERVICE_MGR_LISTEN_PORT, 1);
	
	return 0;
}

