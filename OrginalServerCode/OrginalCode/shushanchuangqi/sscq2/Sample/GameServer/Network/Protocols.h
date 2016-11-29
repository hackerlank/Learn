#pragma once

#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include "Gate2GameCommS.h"
#include "Game2DBCommC.h"
#include "Game2CenterCommC.h"
#include "DBProtC.h"
#include "MapProtS.h"
#include "GameSvrBasicS.h"
#include "GameSvrCommC.h"
#include "GameSvrCommS.h"
#include "LogEventClt.h"
#include "ChatProtS.h"
#include "RoleEventS.h"
#include "NpcProtS.h"
#include "DungeonProtS.h"
#include "ItemProtS.h"
#include "PropInfoS.h"
#include "BattleGSS.h"
#include "TaskProtS.h"
#include "FighterProtS.h"
#include "GatherProtS.h"
#include "FormationProtS.h"
#include "ShushanBattleProtS.h"
#include "VIPProtS.h"
#include "MallProtS.h"
#include "GroupTaskProtS.h"
#include "YaMenTaskProtS.h"
#include "ActivityProtS.h"
#include "TitleProtS.h"
#include "GuildBattleProtS.h"
#include "CompareBattlePointS.h"
#include "Game2CenterGuildBattleC.h"
#include "SittingProtS.h"
#include "Game2CenterLogC.h"
#include "Game2CenterRankC.h"
#include "LevelPrizeSvrS.h"
#include "CoinProtS.h"
#include "SignProtS.h"


extern CRoleEventS g_RoleEventProtS;
extern CGate2GameCommS g_Gate2GameCommS;
extern CGame2DBCommC g_Game2DBCommC;
extern CGame2CenterCommC g_Game2CenterCommC;
extern CDBProtC g_DBProtC;
extern CDBProtC g_LogDBProtC;
extern CMapProtS g_MapProtS;
extern CGameSvrBasicS g_GameSvrBasicS;
extern CGatherProtS g_GatherProtS;
extern CGroupTaskProtS g_GroupTaskProtS;
extern CYaMenTaskProtS g_YaMenTaskProtS;

extern CGame2CenterLogC g_Game2CenterLog;
extern CGameSvrCommC g_GameSvrCommC;
extern CGameSvrCommS g_GameSvrCommS;
extern NLogEvent::CLogEventClt g_LogEvent;
extern CChatProtS g_ChatProtS;
extern CNpcProtS g_NpcProtS;
extern CDungeonProtS g_DungeonProtS;
extern CItemProtS g_ItemProtS;
extern CPropInfoS g_PropInfoS;
extern CBattleGSS g_BattleGSS;
extern CTaskProtS g_TaskProtS;
extern CFighterProtS g_FighterProtS;
extern CFormationProtS g_FormationProtS;
extern CShushanBattleProtS g_ShushanBattleProtS;
extern CVIPProtS g_VIPProtS;
extern CMallProtS g_MallProtS;
extern CActivityProtS g_ActivityProtS;
extern CTitleProtS g_TitleProtS;
extern CGuildBattleProtS g_GuildBattleProtS;
extern CGame2CenterGuildBattleC g_Game2CenterGuildBattleC;
extern CCompareBattlePointS g_CompareBattlePointS;
extern CSittingProtS g_SittingProtS;
extern CGame2CenterRankC g_Game2CenterRankC;
extern CCoinProtS g_CoinProtS;
extern CSignProtS g_SignProtS;

#endif // #ifndef PROTOCOLS_H
