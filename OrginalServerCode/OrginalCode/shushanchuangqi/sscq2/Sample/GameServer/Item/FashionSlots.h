
#ifndef FASHIONSLOTS_H_
#define FASHIONSLOTS_H_

#include "Fashion.h"
#include "VecSlots.h"
#include "ItemSlots.h"

#define FASHION_SIZE 10 // XXX: 初始时装个数

class CUser;

class CFashionSlots : public CItemSlots<FASHION_SIZE, CVecSlots<int, CItemPtr>>
{
public:
    typedef CItemSlots<FASHION_SIZE, CVecSlots<int, CItemPtr>> TYPE;
    typedef typename TYPE::value_type value_type;

public:
    CFashionSlots() {}
    virtual ~CFashionSlots();

    EStoreType GetStoreType() const { return eStoreFashion; }

    //激活时装
    bool AdoptFashion(UINT16 wItemID, bool bUpdate = true); 
    bool AdoptFashion(CItemPtr& pItem, bool bUpdate = true); 

    CFashionPtr GetCurrW() const { return _pCurrW; }
    CFashionPtr GetCurrD() const { return _pCurrD; }

    // 选择时装
    EFashionResult ActiveFashion(UINT64 qwInstID); 
    EFashionResult ActiveFashion(int iSlot, CItemPtr& pItem); 
    // 时装炼化
    EFashionResult FashionUpgrade(UINT64 qwInstID, bool bOneKey);

    bool GetAddAttr(TVecFloat& vecAddAttr) const;
    void ToProt(TVecItem& vecItem) const;
    void Update2DB(int iSlot, CItem& rItem, EDataChange eDataChange = eOpUpdate);
    void Update2DB(CItem& rItem);

    void WriteFashionLog(UINT16 wID, string rName,UINT32 dwLevel);

private:
    CFashionPtr _pCurrW; // 当前时装武器
    CFashionPtr _pCurrD; // 当前时装外套
    TVecFloat _vecAttr;
};

#endif // FASHIONSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

