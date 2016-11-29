
#ifndef ITEMTYPE_H_
#define ITEMTYPE_H_

#include "stdafx.h"
#include "ItemProt.h"

using namespace NItemProt;

#define ID_MIN(type) eItem##type##_min
#define ID_MAX(type) eItem##type##_max
#define ID_INTERVAL(type, min, max) ID_MIN(type) = min, ID_MAX(type) = max
#define ID_IFBETWEEN(id, type) if (((id) >= ID_MIN(type) && (id) <= ID_MAX(type))) return eItem##type

// XXX: 这个区间是一个闭包区间: [x,y] 包含x,y在内
enum EItemIDInterval
{
    eItemIDIntervalMin = 0,
    ID_INTERVAL(Normal,        100,     1999),
    ID_INTERVAL(ZodTrump,      4500,    4999),
    ID_INTERVAL(Trump,         5000,    6499),
    ID_INTERVAL(Fashion,       6500,    7999),
    ID_INTERVAL(Formation,     8000,    8199),
    ID_INTERVAL(Citta,         8200,    8499),
    ID_INTERVAL(Intensify,     8500,    8799),
    ID_INTERVAL(Stone,         8800,    8999),
    ID_INTERVAL(Task,          9000,    9499),
    ID_INTERVAL(Spirit,        9500,    9999),
    ID_INTERVAL(Soul,          10000,   10299),
    ID_INTERVAL(Neidan,        10300,   10499),
    ID_INTERVAL(Vigour,        10500,   10699),
    ID_INTERVAL(EquipTrump,    11000,   14999),
    eItemIDIntervalMax
};

#define IST(type, value) eItemSub##type = value

class CItemType
{
public:
	static EItemType GetItemType(UINT16 wItemID);
    static bool IsCitta(UINT16 wItemID);
    static bool IsTrump(UINT16 wItemID);
    static bool IsFashion(UINT16 wItemID);
    static bool IsEquipTrumpItem(UINT16 wItemID);
};

#endif // ITEMTYPE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

