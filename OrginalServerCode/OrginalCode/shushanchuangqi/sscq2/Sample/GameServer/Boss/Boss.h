#ifndef BOSS_H_
#define BOSS_H_

#include "Monster.h"

class CBoss : public CMonster
{
public:
    CBoss();
    virtual ~CBoss(); 

    float GetHPPercent() const;
    virtual bool IsDead() const { return _bDead; }

    UINT32 GetHP() const { return _dwHP; }
    void SetHP(UINT32 dwHP) { _dwHP = dwHP; }
    UINT32 GetMaxHP() const { return _dwMaxHP; }
    void SetMaxHP(UINT32 dwMaxHP) { _dwMaxHP = dwMaxHP; }
    UINT32 GetExp() const { return _dwExp; }
    void SetExp(UINT32 dwExp) { _dwExp = dwExp; }
    UINT8 GetColor() const { return _byColor; }
    void SetColor(UINT8 byColor) { _byColor = byColor; }
    void SetName(const std::string& strName) { _strName = strName; }
    const std::string& GetName() const { return _strName; }
protected:
    bool _bDead;
    UINT32 _dwHP; // 当前血量
    UINT32 _dwMaxHP; // 当前最大血量
    UINT32 _dwExp; // 当前经验

    std::string _strName;
    UINT8 _byColor;
};

#endif // BOSS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

