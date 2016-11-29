#include "stdafx.h"
#include <boost/progress.hpp>
#include "NPCMgr.h"
#include "GUIDMgr.h"
map<UINT64, CNpcPtr> CNpcMgr::_mapID2Npc;
map<UINT16, SNpcPropCFG> CNpcMgr::_mapID2NpcCfg;
UINT64 CNpcMgr::_qwVersion = VERSION_INIT;
bool CNpcMgr::Init()
{
	string strPath = Config._strConfigDir + "Conf/Table/NpcProp.xml";
	CNpcPropLoader oNpcPropLoader;
	if(!oNpcPropLoader.LoadData(strPath))
	{
		LOG_CRI << "oNpcPropLoader.LoadData fails! Path: " << strPath;
		return false;
	}
	if(LOG_OBJ.IsConsoleOpen())
		cout << "Loading NPC Scripts...";
	boost::progress_display show_progress((ULONG)oNpcPropLoader._vecData.size());
	for(size_t i = 0; i < oNpcPropLoader._vecData.size(); ++i)
	{
		SNpcPropCFG* pNpcPropCFG = oNpcPropLoader._vecData[i];
		if(pNpcPropCFG->_ID == 0)
			continue;
#if 0
        if(!LoadNpcScript(pNpcPropCFG->_Script))
		{
			LOG_CRI << "LoadNpcScript fails! Script: " << pNpcPropCFG->_Script;
#if STRICT_SCRIPT_CHECK
			return false;
#endif
		}
#endif        
		_mapID2NpcCfg[pNpcPropCFG->_ID] = *pNpcPropCFG;
		if(LOG_OBJ.IsConsoleOpen())
			++show_progress;
	}
	return true;
}

bool CNpcMgr::ReloadConfig(bool bReload /* = false */)
{
	string strPath = Config._strConfigDir + "Conf/Table/NpcProp.xml";
	CNpcPropLoader oNpcPropLoader;
	if(!oNpcPropLoader.LoadData(strPath))
	{
		LOG_CRI << "oNpcPropLoader.LoadData fails! Path: " << strPath;
		return false;
	}
	if(LOG_OBJ.IsConsoleOpen())
		cout << "Loading NPC Scripts...";
	boost::progress_display show_progress((ULONG)oNpcPropLoader._vecData.size());
	for(size_t i = 0; i < oNpcPropLoader._vecData.size(); ++i)
	{
		SNpcPropCFG* pNpcPropCFG = oNpcPropLoader._vecData[i];
		if(pNpcPropCFG->_ID == 0)
			continue;
#if 0
        if(!LoadNpcScript(pNpcPropCFG->_Script))
		{
			LOG_CRI << "LoadNpcScript fails! Script: " << pNpcPropCFG->_Script;
#if STRICT_SCRIPT_CHECK
			return false;
#endif
		}
#endif        
		_mapID2NpcCfg[pNpcPropCFG->_ID] = *pNpcPropCFG;
		if(LOG_OBJ.IsConsoleOpen())
			++show_progress;
	}

    if(bReload)
        ++ _qwVersion;
	return true;
}



void CNpcMgr::Destroy()
{
	_mapID2Npc.clear();
}
#if 0
bool CNpcMgr::LoadNpcScript(const string& strScript, bool bReload /*= false*/)
{
	if(strScript.empty())
	{
		//LOG_CRI << "strScript is empty!";
		return true;
	}
	string strScriptPath = Config._strConfigDir + "Conf/NPC/" + strScript;
	CGameScriptPtr pScript = CScriptMgr::GetScript(strScript, eScriptNpc);
	if(bReload)
	{
		if(pScript == NULL)
		{
			LOG_CRI << "Can't find script: " << strScript;
			return false;
		}
	}
	else
	{
		if(pScript != NULL)
			return true;
		pScript = CScriptMgr::AddScript(strScript, eScriptNpc);
		if(pScript == NULL)
		{
			LOG_CRI << "CScriptMgr::AddScript fails! dwScript: " << strScript;
			return false;
		}
		if(!pScript->Register())
		{
			LOG_CRI << "Register for " << strScriptPath << " fails!";
			return false;
		}

	}
	
	if(!pScript->LoadLuaFile(strScriptPath))
	{
		LOG_CRI << "LoadLuaFile " << strScriptPath << " fails!";
		return false;
	}
	return true;
}

void CNpcMgr::ReloadAllScript()
{
	for(auto& p : _mapID2NpcCfg)
	{
		const string& strScript = p.second._Script;
		if(!LoadNpcScript(strScript, true))
			LOG_CRI << "LoadNpcScript fails! Script: " << strScript;
	}
}
#endif
CNpcPtr CNpcMgr::CreateNpc(UINT16 wNpcID,UINT8 byIndex)
{
	auto it = _mapID2NpcCfg.find(wNpcID);
	if(it == _mapID2NpcCfg.end())
		return NULL;
	SNpcPropCFG& rNpcPropCFG = it->second;
	CNpcPtr pNpc(new CNpc(rNpcPropCFG,_qwVersion));
	if(pNpc == NULL)
		return NULL;
	pNpc->SetCreatureID(GET_GUID(GUID_NPC));
	pNpc->SetName(rNpcPropCFG._Name);
	if(!_mapID2Npc.insert(make_pair(pNpc->GetCreatureID(), pNpc)).second)
		LOG_DBG << "NPC already exist!";

	return pNpc;
}

void CNpcMgr::DestroyNpc(CNpc& rNpc)
{
	_mapID2Npc.erase(rNpc.GetCreatureID());
}


CNpcPtr CNpcMgr::GetNpc(UINT64 qwCreatureID)
{
	auto it = _mapID2Npc.find(qwCreatureID);
	if(it != _mapID2Npc.end())
		return it->second;
	return NULL;
}

SNpcPropCFG* CNpcMgr::GetNpcCFG(UINT16 wNpcID)
{
	auto it = _mapID2NpcCfg.find(wNpcID);
	if(it != _mapID2NpcCfg.end())
		return &it->second;
	return NULL;
}
