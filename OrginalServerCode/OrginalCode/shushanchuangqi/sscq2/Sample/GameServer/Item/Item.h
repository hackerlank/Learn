
#pragma once
#include "ItemCFG.h"
#include "ItemAttrCFG.h"
#include "ExpireItem.h"
#include "ItemProt.h"
#include "ItemType.h" // XXX: in ServerCommon
#include "Version.h"

using namespace NItemProt;
using namespace NProtoCommon;

namespace NGlobalChatProt { struct SShowInfo;}
struct SItemTimeInfo;
struct SItemInfo;

class CCreature;
class CPlayer;
class CStore;
class CCittaSlots;
class CGemstone;

class CItem : public CExpireItem, public CVersion, public enable_shared_from_this<CItem>, public CPoolObj<CItem>
{
	friend class CItemMgr;
    friend class CCittaSlots;
public:
	CItem(UINT16 wItemID);
	virtual ~CItem();
	DEF_NEW_DELETE(CItem);

	virtual UINT16 GetOptCount() const { return 1; }
	virtual UINT16 GetCount() const { return 1; }
	virtual UINT32 GetItemExp() const { return 0; }
    virtual UINT8  GetEquipTrumpLevel() const  { return 0; }
	virtual UINT32 GetSellPrice() { return GetItemConfig()._SellPrice; }
	virtual UINT32 GetTrumpExp() { return GetItemConfig()._TrumpExp; }
	virtual UINT32 GetEnergy() { return GetItemConfig()._Energy; }  //入鼎值
    float GetGoldPrice();

    bool IsCittaItem() const { return CItemType::GetItemType(GetItemConfig()._ID) == eItemCitta; }
    bool IsTrumpItem() const { return CItemType::GetItemType(GetItemConfig()._ID) == eItemTrump; }
    bool IsEquipTrumpItem() const { return CItemType::GetItemType(GetItemConfig()._ID) == eItemEquipTrump; }
    bool IsFashionItem() const { return CItemType::GetItemType(GetItemConfig()._ID) == eItemFashion; }
    bool IsGemstone() const { return CItemType::GetItemType(GetItemConfig()._ID) == eItemStone; }
    UINT8 GetItemCfgType() const { return GetItemConfig()._Type;}
    UINT8 GetType() const { return GetItemConfig()._Type;}

	UINT16 GetItemID() const { return _wItemID; }
	UINT16 GetID() const { return GetItemID(); }
    void SetItemID(UINT16 wItemID);
	UINT64 GetInstID() const { return _qwInstID; }
	UINT8 GetLevel() const { return GetItemConfig()._Level; }
	UINT8 GetShowLevel() const { return GetItemConfig()._LevelValue; }
    //宝石等级
    UINT8 GetStoneLevel() const { return GetItemConfig()._StoneLevel; }
	const string& GetItemName() const { return GetItemConfig()._Name; }
	UINT8 GetQuality() const { return GetItemConfig()._Quality; }
	UINT8 GetJob() const { return GetItemConfig()._Job; }
	const SItemCFG& GetItemCfg() const { return GetItemConfig(); }
	SItemInfo* GetItemInfo() { return _pItemInfo; }

	EItemType GetItemType() const;
    static EItemType GetItemType(UINT16 wItemID);
    static EItemType GetItemType(const SItemCFG& rItemCfg);
	EItemSubType GetItemSubType() const;
    static EItemSubType GetItemSubType(UINT16 wItemID);
    static EItemSubType GetItemSubType(const SItemCFG& rItemCfg);

	EBindType GetBindType() const { return _eBindType; }
	void SetBindType(EStoreType eStoreType, EBindType eBindType, const CUserPtr& pUser = NULL);
	bool IsBind() const { return _bBind; }
	void SetBind(bool bBind);

	bool IsStackItem() const { return IsStackItem(_wItemID); }
	UINT16 GetMaxNum() const { return GetMaxNum(GetItemConfig()); }
	static bool IsStackItem(const SItemCFG& rItemCfg) { return rItemCfg._Stack > 1; }
	static bool IsStackItem(UINT16 wItemID);
	static UINT16 GetMaxNum(const SItemCFG& rItemCfg) { return rItemCfg._Stack > 1 ? rItemCfg._Stack : 1; }

	//bDel是否直接删除
	virtual bool OnUse(CStore& rStore, UINT16 wCount, bool bDel, UINT16 toWhere);
    virtual bool CanUse(UINT16 wCount);
	void OnAddToStore(CStore& rStore, bool bNotify = true);

	static UINT16 GetTypeOrder(const SItemCFG& rItemCfg);

    INT16 GetIndex() const { return _wIndex; }
    void SetIndex(INT16 wIndex) { _wIndex = wIndex; }

    UINT8 GetStoreType() const { return _byStoreType; }
    void SetStoreType(UINT8 byStoreType) { _byStoreType = byStoreType; }

    virtual void InitItemAttr() {}
    virtual void RebuildAttr() {}
    virtual void AppendAttr(TVecFloat&/* vecAttr*/) {}

	virtual SItemPtr ToProt() const;
	void FromStream(const SItem& rStream);
	void ToStream(SItem& rStream) const;

    static void Update2DB(CItem& rItem, UINT64 qwUserID, UINT64 qwOwnerID, EStoreType eStoreType, UINT16 wIndex, EDataChange eDataChange = eOpUpdate);
    static void ItemChangeNotify(CUser& rUser, CItem& rItem, EStoreType eStoreType, UINT16 wIndex, UINT64 qwOwnerID = 0);

	void TimerCheck(time_t tNow, CStore& rStore);
    static void GetShowMsg(CItem& rItem,NGlobalChatProt::SShowInfo & stShow);

    UINT32 ToSize();

protected:
    const SItemCFG& GetItemConfig() const;

protected:
    mutable SItemInfo* _pItemInfo; // 为了优化每次都取配置里查询

protected:
    UINT16 _wItemID;
	UINT64 _qwInstID;
	EBindType _eBindType;
	bool _bBind;
    UINT8 _byStoreType;
    INT16 _wIndex;
};

bool operator<(CItem& left, CItem& right);

namespace std
{
	template<> struct less<CItemPtr>
	{
		bool operator()(CItemPtr left, CItemPtr right)
		{
			return *left < *right;
		}
	};
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

