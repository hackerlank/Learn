#pragma once
#include "Creature.h"
#include "NpcPropCFG.h"
#include "GameScript.h"

class CNpc : public CCreature, public CPoolObj<CNpc>
{
	friend class CNpcMgr;
public:
	DEF_NEW_DELETE(CNpc);
	CNpc(SNpcPropCFG& rNpcPropCFG,UINT64 qwVersion) : _qwCreatureID(0), _pNpcPropCFG(&rNpcPropCFG),_qwVersion(qwVersion), _byIndex(0) { }
	virtual ~CNpc() { }
	virtual EObjType GetObjType() const { return eObjNpc; }
	UINT16 GetNpcID() { return GetNpcConfig()._ID; }
    string GetNpcName(){  _strName = GetNpcConfig()._Name; return _strName; }
	virtual UINT64 GetCreatureID() const { return _qwCreatureID; }
	void SetCreatureID(UINT64 qwCreatureID) { _qwCreatureID = qwCreatureID; }
	virtual bool IsDead() const { return false; }
	virtual bool IsAttackable() const { return false; }
	void GetNpcAppear(SNpcAppear& rNpcAppear);
    CGameScriptPtr GetScript();
    SNpcPropCFG& GetNpcConfig();

    //buffer相关
    virtual EBuffType GetBuffType() const { return eBTNPC; }
    virtual void UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange) {};
    virtual UINT64 GetRoleID() const { return 0; };
    virtual UINT64 GetOwnerID() const { return 0; };
    virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo){};
    UINT8 GetIndex() {return _byIndex;}

protected:
#if 0
    CGameScriptPtr _pScript;
#endif
	UINT64 _qwCreatureID;
	SNpcPropCFG *_pNpcPropCFG;
    UINT64 _qwVersion;
    UINT8 _byIndex;
};

inline CLogObj& operator<<(CLogObj& src, const CNpc& rNpc)
{
	src << " [" << rNpc.GetDescription() << "]";
	return src;
}
