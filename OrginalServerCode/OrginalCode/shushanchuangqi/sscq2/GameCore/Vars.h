
#ifndef VARS_H_
#define VARS_H_

#include "Platform.h"
#include "Buffer.h"
#include "RTime.h"
#include <map>

typedef enum
{
    VARRECYCLE_NONE = -1,

    // Calendar
    VARRECYCLE_YEAR, // Calendar year
    VARRECYCLE_MONTH,
    VARRECYCLE_WEEK,
    VARRECYCLE_DAY,
    VARRECYCLE_HOUR,
    VARRECYCLE_MIN,

    // Absolute
    VARRECYCLE_YEAR_ABS,
    VARRECYCLE_MONTH_ABS,
    VARRECYCLE_WEEK_ABS,
    VARRECYCLE_DAY_ABS,
    VARRECYCLE_HOUR_ABS,
    VARRECYCLE_MIN_ABS,
    VARRECYCLE_ABS,

    VARRECYCLE_MAX
} VarRecycle_e;

extern std::map<UINT16, VarRecycle_e> _VarType;

// XXX: K and V must be in UINT8,UINT16,UINT32,UINT64

template <typename K = UINT16, typename V = UINT32>
class Vars
{
public:
    struct Var
    {
        V val;
        time_t end;

        Var(): val(0), end(0) {}
    };

    struct SerVar
    {
        K var;
        V val;
        time_t end;
    };

    typedef std::map<K, Var> container;
    typedef typename container::value_type value_type;
    typedef typename container::iterator iterator;
    typedef typename container::const_iterator const_iterator;

    Vars() {}
    ~Vars() { _vars.clear(); }

    static void DecVar(UINT16 wVar, VarRecycle_e recycle = VARRECYCLE_MAX)
    {
        if (recycle >= VARRECYCLE_MAX)
            recycle = VARRECYCLE_NONE;
        _VarType[wVar] = recycle;
    }

    V GetVar(K var, iterator& it, bool* bDel = NULL)
    {
        iterator i = _vars.find(var);
        it = i;
        if (i != _vars.end())
        {
            time_t now = Time::Now();
            if (i->second.end && now >= i->second.end)
            {
                i->second.val = 0;
                if (bDel)
                    *bDel = true;
                return 0;
            }
            return i->second.val;
        }
        return 0;
    }

protected:
    bool AddVar(K var, V val, time_t now, V Offset, iterator& it)
    {
        iterator i = _vars.find(var);
        it = i;
        if (i != _vars.end())
        {
            if (0 == now)
                now = Time::Now();
            if (i->second.end && now >= i->second.end)
            {
                i->second.val = 0;
                auto itr = _VarType.find(var);
                if (itr != _VarType.end())
                {
                    Var& v = i->second;
                    ResetTime(v, itr->second, now, Offset);
                }
            }

            i->second.val += val;
            return true;
        }

        SetVar(var, val, now, Offset, it);
        return false;
    }

    bool SetVar(K var, V val, time_t now, V Offset, iterator& it)
    {
        auto i = _VarType.find(var);
        if (i == _VarType.end())
            return false;
        bool bUpdate =false;
        VarRecycle_e recycle = i->second;
        if (recycle >= VARRECYCLE_MAX)
            recycle = VARRECYCLE_NONE;
        it = _vars.find(var);
        if(it != _vars.end())
        {
            bUpdate = true;
        }
        Var& v = _vars[var];
        v.val = val;
        it = _vars.find(var);
#if 0
        if (0 == now)
            now = Time::Now();
        now -= Offset;
        switch (recycle)
        {
            case VARRECYCLE_NONE:
                v.end = 0;
                break;
            case VARRECYCLE_YEAR:
                v.end = Time::TheYear(1,now) + Offset;
                break;
            case VARRECYCLE_MONTH:
                v.end = Time::TheMonth(1,now) + Offset;
                break;
            case VARRECYCLE_WEEK:
                v.end = Time::TheWeek(1,now) + Offset;
                break;
            case VARRECYCLE_DAY:
                v.end = Time::TheDay(1,now) + Offset;
                break;
            case VARRECYCLE_HOUR:
                v.end = Time::TheHour(1,now) + Offset;
                break;
            case VARRECYCLE_MIN:
                v.end = Time::TheMin(1,now) + Offset;
                break;

            case VARRECYCLE_YEAR_ABS:
                {
                    Time t(now);
                    v.end = Time::MkTime(t.year()+1, t.month(), t.day(), t.hour(), t.min(), t.sec()) + Offset;
                }
                break;
            case VARRECYCLE_MONTH_ABS:
                {
                    // XXX: t.day() >= now().day()
                    Time t(now);
                    if (t.month() + 1 >= 12)
                        v.end = Time::MkTime(t.year()+1, 0+1, t.day(), t.hour(), t.min(), t.sec()) + Offset;
                    else
                        v.end = Time::MkTime(t.year(), t.month()+1+1, t.day(), t.hour(), t.min(), t.sec())+ Offset;
                }
                break;
            case VARRECYCLE_WEEK_ABS:
                v.end = now + TIME_WEEK +Offset;
                break;
            case VARRECYCLE_DAY_ABS:
                v.end = now + TIME_DAY+Offset;
                break;
            case VARRECYCLE_HOUR_ABS:
                v.end = now + TIME_HOUR+Offset;
                break;
            case VARRECYCLE_MIN_ABS:
                v.end = now + TIME_MIN+Offset;
                break;
            case VARRECYCLE_ABS:
                v.end = now + Offset;
                break;

            default:
                v.end = 0;
                break;
        }
#endif
        ResetTime(v, recycle, now, Offset);
        return bUpdate;
    }

    void ResetTime(Var& v, VarRecycle_e recycle, time_t now, V Offset)
    {
        if (0 == now)
            now = Time::Now();
        now -= Offset;
        switch (recycle)
        {
            case VARRECYCLE_NONE:
                v.end = 0;
                break;
            case VARRECYCLE_YEAR:
                v.end = Time::TheYear(1,now) + Offset;
                break;
            case VARRECYCLE_MONTH:
                v.end = Time::TheMonth(1,now) + Offset;
                break;
            case VARRECYCLE_WEEK:
                v.end = Time::TheWeek(1,now) + Offset;
                break;
            case VARRECYCLE_DAY:
                v.end = Time::TheDay(1,now) + Offset;
                break;
            case VARRECYCLE_HOUR:
                v.end = Time::TheHour(1,now) + Offset;
                break;
            case VARRECYCLE_MIN:
                v.end = Time::TheMin(1,now) + Offset;
                break;

            case VARRECYCLE_YEAR_ABS:
                {
                    Time t(now);
                    v.end = Time::MkTime(t.year()+1, t.month(), t.day(), t.hour(), t.min(), t.sec()) + Offset;
                }
                break;
            case VARRECYCLE_MONTH_ABS:
                {
                    // XXX: t.day() >= now().day()
                    Time t(now);
                    if (t.month() + 1 >= 12)
                        v.end = Time::MkTime(t.year()+1, 0+1, t.day(), t.hour(), t.min(), t.sec()) + Offset;
                    else
                        v.end = Time::MkTime(t.year(), t.month()+1+1, t.day(), t.hour(), t.min(), t.sec())+ Offset;
                }
                break;
            case VARRECYCLE_WEEK_ABS:
                v.end = now + TIME_WEEK +Offset;
                break;
            case VARRECYCLE_DAY_ABS:
                v.end = now + TIME_DAY+Offset;
                break;
            case VARRECYCLE_HOUR_ABS:
                v.end = now + TIME_HOUR+Offset;
                break;
            case VARRECYCLE_MIN_ABS:
                v.end = now + TIME_MIN+Offset;
                break;
            case VARRECYCLE_ABS:
                v.end = now + Offset;
                break;

            default:
                v.end = 0;
                break;
        }
    }

    void SetVar(K var, V val, time_t end)
    {
        Var& v = _vars[var];
        v.val = val;
        v.end = end;
    }

    bool DelVar(K var)
    {
        iterator i = _vars.find(var);
        if (i != _vars.end())
        {
            _vars.erase(var);
            return true;
        }
        return false;
    }

    void clear()
    {
        _vars.clear();
    }

    V GetExpiredTime(K var)
    {
        iterator i = _vars.find(var);
        if (i != _vars.end())
            return i->second.end;
        return 0;
    }

    bool SetExpiredTime(K var, V dwExpired, iterator& it)
    {
        it = _vars.find(var);
        if(it == _vars.end())
            return false;
        Var& v = _vars[var];
        v.end = dwExpired;
        it = _vars.find(var);
        return true;
    }
protected:
    container _vars;
};

#endif // VARS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

