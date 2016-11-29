#pragma once
#include "ServerCommon.h"

using namespace NServerCommon;

#include "DBProtS.h"
#include "Gate2DBCommS.h"
#include "Center2DBCommS.h"
#include "Game2DBCommS.h"
#include "LogEventClt.h"
#include "RoleEnterGameProtSvrS.h"
extern CDBProtS g_DBProtS4CT;
extern CDBProtS g_DBProtS4GS;
extern CGate2DBCommS g_Gate2DBCommS;
extern CCenter2DBCommS g_Center2DBCommS;
extern CGame2DBCommS g_Game2DBCommS;
extern NLogEvent::CLogEventClt g_LogEvent;
extern CRoleEnterGameProtSvrS g_RoleEnterGameProtSvrS;
