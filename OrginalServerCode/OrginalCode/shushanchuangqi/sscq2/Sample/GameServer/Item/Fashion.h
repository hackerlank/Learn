
#ifndef FASHION_H_
#define FASHION_H_

#include "Item.h"

class CFashion : public CItem
{
public:
    CFashion(UINT16 wItemID);
    virtual ~CFashion();
    DEF_NEW_DELETE(CFashion);

    UINT8 GetLevel() const { return _byLevel; }
    void SetLevel(UINT8 byLevel) { _byLevel = byLevel; }

    UINT32 GetExp() const { return _dwExp; }
    void SetExp(UINT32 dwExp) { _dwExp = dwExp; }

    UINT8 GetSelected() const { return _bySelected; }
    void SetSelected(UINT8 bySelected) { _bySelected = bySelected; }

    UINT8 GetHide() const { return _byHide; }
    void SetHide(UINT8 byHide) { _byHide = byHide; }

    void InitItemAttr() override;
    void AppendAttr(TVecFloat& vecAttr) override;

	SItemPtr ToProt() const override;
    bool FromStream(const SFashion& rStream);
    bool ToStream(SFashion& rStream) const;

    bool IsDirty() const { return _bDirty; }
    void SetDirty(bool bDirty) { _bDirty = bDirty; }

private:
    void RebuildAttr() override;
    void InitFashionLvAttr();
private:
    UINT8 _byLevel;
    UINT32 _dwExp;
    UINT8 _bySelected;
    UINT8 _byHide;

    bool _bDirty;
    TVecFloat _vecItemAttr; // (基础+等级)属性属性加成
};

#endif // FASHION_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

