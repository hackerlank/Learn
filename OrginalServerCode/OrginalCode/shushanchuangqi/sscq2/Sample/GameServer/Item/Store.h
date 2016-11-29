#pragma once
#include "Item.h"
#include "RoleInfoDefine.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;

class CUser;
class CPlayer;
class CStackItem;
struct SCollectItem;
struct SIdxCount;
struct SStoreSlot
{
	CItemPtr pItem;
	INT16 wIndex;

	SStoreSlot() : pItem(NULL), wIndex(-1) { }
	SStoreSlot(CItemPtr pItem_, INT16 wIndex_) : pItem(pItem_), wIndex(wIndex_) { }
};
typedef std::vector<SStoreSlot> TVecSStoreSlot;

class CStore
{
    public:
        CStore(UINT16 wCapacity) : _wCapacity(wCapacity),_wUseItem(0) { }
        virtual ~CStore();

        virtual CUser& GetUser() const = 0;
        CUserPtr GetUserPtr() const;

        bool SendPkg(const string& strPkg);

        virtual EStoreType GetStoreType() const { return eStoreNone; }

        virtual UINT16 GetCapacity() const { return _wCapacity; }
        void SetCapacity(UINT16 wCapacity) { _wCapacity = wCapacity; }
        void AddCapacity(UINT16 wCapacity) { _wCapacity += wCapacity; }

        bool ItemAddNotify(CItem& rItem, bool bNew);
        bool ItemAddNotify(SStoreSlot& rStoreSlot, bool bNew);
        bool ItemDelNotify(CItem& rItem);
        bool StoreItemNotify();
        bool CittaAddNotify(const vector<CCittaPtr>& vecCittaPtr);

        //--qf-- add 2014/5/7
        //是否有足够的物品扣除
        bool CanSubItem(const TVecItemCount& vecItemCount,EBindUseType eBindUseType = eBindUseBindFirst);
        bool CanSubItemWithID(UINT16 wItemID,UINT32 dwCount,EBindUseType eBindUseType);

        //扣除物品
        void SubItem(const TVecItemCount& vecItemCount,UINT16 toWhere,EBindUseType eBindUseType = eBindUseBindFirst);
        void SubItemWithID(UINT16 wItemID,UINT32 dwCount,UINT32 dwLogType ,EBindUseType eBindUseType);

        UINT32 GetItemCount(UINT16 wItemID);
        UINT32 GetItemCount(UINT16 wItemID) const;
        UINT16 GetItemCount(UINT16 wItemID, EBindUseType eBindUseType) const;
        UINT16 GetItemCount() const { return (UINT16)_mapID2Slot.size(); }
        UINT16 GetEmptyCount() const;

        UINT32 GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel);

        UINT32 GetStoneCount(UINT8 byMinLevel);

        bool IsStoreFull() const { return (UINT16)_mapID2Slot.size() >= GetCapacity(); }

        SStoreSlot* GetSlot(UINT64 qwInstID);
        CItemPtr GetItem(UINT64 qwInstID, INT16* pIndex = NULL);
        CItemPtr GetItem(INT16 wIndex);
        CItemPtr GetItem(INT16 wIndex) const;
        UINT64 GetInstByIndex(INT16 wIndex);
        UINT64 GetInstByIndex(INT16 wIndex) const;
        INT16 GetIndexByInst(UINT64 qwInstID);

        bool HasItem(UINT64 qwInstID);
        bool HasItem(UINT16 wItemID);

        //判断容器是否满
        bool CanAddItem(const SItemGenInfo& rItemGenInfo);
        bool CanAddItem(const TVecItemGenInfo& rVecItemGenInfo, bool bNotify = false);
        bool CanAddItem(CItem& rItem, INT16 wIndex = -1);
        bool CanAddItem(const TVecSStoreSlot& vecStore);
        bool CanAddItem(vector<CItemPtr>& rVecCItem);
        bool CanAddItemWithID(UINT16 wItemID, UINT32 dwNum, EBindType eBindType, UINT8 byQuality);

        //容器添加道具

        virtual bool AddItemWithID(UINT16 wItemID, UINT32 dwNum, EBindType eBindType, UINT8 byQuality, UINT16 fromWhere);
        //wIndex为-1将判断堆叠和自动分配位置
        virtual bool AddItem(CItem& rItem, INT16 wIndex = -1, bool bNotify = true, bool bNew = false, bool bUpdate = true, UINT16 fromWhere = 0);
        bool  AddItemByLootID(UINT32 dwLootId,UINT16 fromWhere,bool bIsPend = false,TVecItemGenInfo* rVecItemGenInfo = NULL,TVecResource* vecRes = NULL);

        //XXX 增加道具使用这个接口！！AddItem(const TVecItemGenInfo& rVecItemGenInfo...
        virtual bool AddItem(const TVecItemGenInfo& rVecItemGenInfo, UINT16 fromWhere, bool bNotify = true, bool bNotifyMsg = true, bool bBuy = false);
        virtual bool AddItem(const SItemGenInfo& rItemGenInfo, UINT16 fromWhere, bool bNotify = true, bool bNotifyMsg = true, bool bBuy = false);

        static void MergeResource(TVecResource& vecRes); 
        static void AddResource(CUser& rUser, TVecResource& vecRes,UINT16 fromWhere, CPlayerPtr pPlayer = NULL,bool bNotify = true);

        static bool CanSubResource(CUser& rUser, TVecResource& vecRes, CPlayerPtr pPlayer = NULL);
        static bool SubResource(CUser& rUser, TVecResource& vecRes,UINT16 fromWhere, CPlayerPtr pPlayer = NULL,bool bNotify = true);

        bool DelItem(CItem& rItem, UINT16 wCount, bool bNotify = true, bool bUpdate = true, UINT16 toWhere = 0);
        bool DelItem(CItem& rItem, bool bNotify = true, bool bUpdate = true, UINT16 toWhere = 0);

        //XXX 删除道具使用以下三个接口DelItemByInstID DelItemByItemID
        bool DelItemByInstID(UINT64 qwInstID, UINT16 wCount, bool bNotify = true, bool bUpdate = true, UINT16 toWhere = 0);
        bool DelItemByInstID(UINT64 qwInstID, bool bNotify = true, bool bUpdate = true, UINT16 toWhere = 0);
        bool DelItemByItemID(UINT16 wItemID, UINT16 wCount = 1, bool bNotify = true, UINT16 toWhere = 0);

        bool DelItemType(UINT16 wItemID, UINT16 toWhere = 0);
        bool DelItemFromSlots(UINT16 wCount, TVecSStoreSlot& vecStore, UINT16 toWhere = 0);
        void DelItemFromList(const vector<SIdxCount>& rVecList, UINT16 toWhere = 0);
        void DelItemFromList(const vector<SCollectItem>& rVecList, UINT16 toWhere = 0);
        void DelGatherItemFromList(const vector<SIdxCount>& rVecList);
        bool DelItemWithBindType(UINT16 wItemID, UINT16 wCount, EBindUseType eBindUseType, UINT16& wBindCount, UINT16& wNoBindCount, bool bNotify = true, UINT16 toWhere = 0);

        //丢弃道具
        EItemResult DestroyItem(UINT64 qwInstID, UINT16 toWhere = 0);

        //脚本使用道具
        bool OnUseItem(CPlayer& rPlayer, CItem& rItem, UINT16 wCount);

        virtual EItemResult RelocateItem(UINT64 qwInstID, INT16 wNewIndex);
        bool Tidyup();

        EItemResult SplitStackItem(UINT64 qwInstID, UINT16 wStackCount, INT16 wIndex);
        bool MergeStackItem(CStackItem& rFromStackItem, CStackItem& rToStackItem, INT16* wFromIndex = NULL, INT16* wToIndex = NULL);
        EItemResult MergeStackItem(UINT64 qwFromInstID, UINT64 qwToInstID);

        void GetAllItemList(vector<CItemPtr>& rvecItem) const;
        void GetItemList(TVecItem& rVecStoreItem);
        void GetItemList(TVecItem& rVecStoreItem) const;
        void GetItemList(UINT16 wItemID, vector<CItemPtr>& rVecItem);
        // wCount: 0 不限定个数 否则达到个数后不遍历后面的物品
        UINT16 GetItemList(UINT16 wItemID, TVecSStoreSlot& rVecStoreSlot, UINT16 wCount = 0, EBindUseType eBind = eBindUseNone);

        EItemResult CanUseItem(CCreature& rCreature, CItem& rItem, UINT16 wCount);
        EItemResult CanUseItem(CCreature& rCreature, UINT16 wItemID, UINT16 wCount, EBindUseType eBind, TVecSStoreSlot& rVecStoreSlot);

        //直接购买扩充包裹或仓库的容量
        EItemResult Expand(UINT16 wCount);

        //包裹或仓库的容量变化同步
        bool CapacityNotify();

        // XXX: 背包数据属于玩家数据，在CPlayer::LoadFromDB里进行反持久化
        void Update2DB(UINT16 wIndex, CItem& rItem, EDataChange eDataChange = eOpUpdate, UINT16 fromWhere = 0);
        bool ToStream(SStoreStream& rStream) const;

        void TimerCheck(time_t tNow);
        static void PrintResInfo(const TVecResource& vecRes);
        void BeginUseItem(UINT16 wItemId);
        void EndUseItem(UINT32 dwNum);
        bool IsInUseItem();
        UINT16 GetEmptyIndex();

        virtual UINT32 ToSize();
    protected:
        bool InternalAddItem(const SItemGenInfo& rItemGenInfo, SAddItemMsg& rAddItemMsg, bool bNotify = true, UINT16 fromWhere = 0);
        UINT16 _wCapacity;
        map<UINT64, SStoreSlot> _mapID2Slot;	//物品存储
        map<INT16, UINT64> _mapIndex2Item;		//存储位，从0开始

    private:
        UINT16 _wUseItem;
        TVecResource _vecUseItemRes;
        TVecItemGenInfo _vecUseItemItems;
};
