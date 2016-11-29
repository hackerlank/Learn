#pragma once
#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include "Platform.h"

using namespace std;

enum EGUIDType
{
	GUID_NONE       = 0,
	GUID_ROLE       = GUID_NONE,
    GUID_HERO       = 1, // 将
	GUID_ITEM       = 2, // 物品类
	GUID_EQUIP      = 3, // 装备类（包括宝石）

    GUID_MAIL       = 4,
	GUID_GUILD      = 5, // 帮派唯一ID

	GUID_NPC        = 6,
	GUID_MONSTER    = 7,
    GUID_DGN        = 8,
    GUID_SHIP       = 9,
    GUID_BATTLE     = 10,// 战报
    GUID_11         = 11, 
    GUID_12         = 12,
    GUID_13         = 13,
    GUID_14         = 14,
    GUID_15         = 15,

	GUID_MAX = 16
};

class CGUIDMgr
{
public:
	typedef void (*TFuncSaveGUID)(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter);
	typedef void (*TFuncOnLoaded)();

	struct SGUIDInfo
	{
		UINT64 qwCounter;
		UINT64 qwSavedCounter;
		TFuncSaveGUID fnSaveGUID;
		bool bSaveSucceed;

		SGUIDInfo() : qwCounter(0), qwSavedCounter(0), fnSaveGUID(nullptr), bSaveSucceed(true) { }
	};

	typedef shared_ptr<SGUIDInfo> SGUIDInfoPtr;

	static CGUIDMgr& Instance();
	CGUIDMgr() : _wGroup(0), _byIndex(0), _bLoaded(false), _fnOnLoaded(nullptr) { _pGUIDMgr = this; }
	bool IsLoaded() const { return _bLoaded; }
	void Init(UINT16 wGroup, UINT8 byIndex, TFuncOnLoaded fnOnLoaded = nullptr);
	bool InitType(const vector<EGUIDType>& vecType, bool bSave);
	void InitCounter(EGUIDType eType, UINT64 qwCounter);
	bool LoadGUID();
	UINT64 GenGUID(EGUIDType eType);
	void OnSaveFail(EGUIDType eType, UINT8 byRet);
	static UINT64 GetGUID(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter);
	static EGUIDType GetType(UINT64 qwGUID);
	static UINT8 GetIndex(UINT64 qwGUID);
	static UINT64 GetCounter(UINT64 qwGUID);
    static UINT16 GetGroupId(UINT64 qwGUID);
    
protected:
	UINT16 _wGroup;
	UINT8 _byIndex;
	SGUIDInfoPtr _arGUIDInfo[GUID_MAX];
	set<EGUIDType> _setSaveType;
	bool _bLoaded;
	TFuncOnLoaded _fnOnLoaded;
	static CGUIDMgr* _pGUIDMgr;
};

#define GET_GUID(type) CGUIDMgr::Instance().GenGUID(type)
