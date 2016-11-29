#pragma once
#include "Script.h"

class CMonster;

class CAIScript
{
public:
	DEF_NEW_DELETE(CAIScript);
	CAIScript(CScript& rScript) : _rScript(rScript), _bHasOnLearnSkill(false), _bHasOnSelectSkill(false),
		_bHasOnHPLess(false), _bHasOnAction(false) { }
	void Init();
	CScript& GetScript() { return _rScript; }
	void OnLearnSkill(CMonster& rMonster);
	void OnSelectSkill(CMonster& rMonster);
	void OnHPLess(CMonster& rMonster);
	void OnAction(CMonster& rMonster, UINT32 dwActCount);
protected:
	CScript& _rScript;
	bool _bHasOnLearnSkill;
	bool _bHasOnSelectSkill;
	bool _bHasOnHPLess;
	bool _bHasOnAction;
};

///////////////////////////////////////////////////////////////////////

class CAIScriptMgr
{
public:
	static void Destroy();
	static bool AddScript(const string& strName, const CAIScriptPtr& pAIScript);
	static CAIScriptPtr GetScript(const string& strName);
private:
	static map<string, CAIScriptPtr> _mapName2Script;
};