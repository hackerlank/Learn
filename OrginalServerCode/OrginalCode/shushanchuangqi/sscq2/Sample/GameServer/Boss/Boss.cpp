
#include "Boss.h"

#define BOSS_MIN_HP 20000000
#define BOSS_MAX_HP 3500000000
#define BOSS_MIN_LVL 30

CBoss::CBoss()
    : _bDead(false), _dwHP(BOSS_MIN_HP), _dwMaxHP(BOSS_MIN_HP)
{
}

CBoss::~CBoss()
{
}

float CBoss::GetHPPercent() const
{
    if (!_dwHP)
        return 0.0f;
    if (!_dwMaxHP)
        return 0.0f;
    float p = (float)_dwHP/_dwMaxHP;
    if (p <= 0.001) // XXX: 精确到0.1%
        return 0.0f;
    return p;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

