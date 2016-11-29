#include "stdafx.h"
#include "AIScript.h"
#include "Monster.h"

void CAIScript::Init()
{
	if(_rScript.HasFunction("OnLearnSkill"))
		_bHasOnLearnSkill = true;
	if(_rScript.HasFunction("OnSelectSkill"))
		_bHasOnSelectSkill = true;
	if(_rScript.HasFunction("OnHPLess"))
		_bHasOnHPLess = true;
	if(_rScript.HasFunction("OnAction"))
		_bHasOnAction = true;
}

void CAIScript::OnLearnSkill(CMonster& rMonster)
{
	if(!_bHasOnLearnSkill)
		return;
	//_rScript.VCall("OnLearnSkill", SLuaUInt64(rMonster.GetCreatureID()));
}

void CAIScript::OnSelectSkill(CMonster& rMonster)
{
	if(!_bHasOnSelectSkill)
		return;
	//_rScript.VCall("OnSelectSkill", SLuaUInt64(rMonster.GetCreatureID()));
}

void CAIScript::OnHPLess(CMonster& rMonster)
{
	if(!_bHasOnHPLess)
		return;
	//_rScript.VCall("OnHPLess", SLuaUInt64(rMonster.GetCreatureID()), (UINT32)rMonster.CurHP(), (UINT32)rMonster.MaxHP());
}

void CAIScript::OnAction(CMonster& rMonster, UINT32 dwActCount)
{
	if(!_bHasOnAction)
		return;
	//_rScript.VCall("OnAction", SLuaUInt64(rMonster.GetCreatureID()), dwActCount);
}

////////////////////////////////////////////////////////////////

map<string, CAIScriptPtr> CAIScriptMgr::_mapName2Script;

void CAIScriptMgr::Destroy()
{
	_mapName2Script.clear();
}

bool CAIScriptMgr::AddScript(const string& strName, const CAIScriptPtr& pAIScript)
{
	if(pAIScript == NULL)
		return false;
	auto pairRet = _mapName2Script.insert(make_pair(strName, pAIScript));
	if(!pairRet.second)
	{
		LOG_CRI << "Script already exists! Name: " << strName;
		return false;
	}
	return true;
}

CAIScriptPtr CAIScriptMgr::GetScript(const string& strName)
{
	auto it = _mapName2Script.find(strName);
	if(it != _mapName2Script.end())
		return it->second;
	return NULL;
}
