
#ifndef MAPSLOTS_H_
#define MAPSLOTS_H_

#include "Platform.h"
#include "Enumerator.h"

#include <map>

#ifndef INVALID_SLOT
#define INVALID_SLOT ((int)-1)
#endif

// XXX: S must be signed
template <typename S, typename T>
class CMapSlots
{
public:
    typedef std::pair<bool, T> V;
    typedef std::map<S, V> SlotsType;
    typedef typename SlotsType::iterator iterator;
    typedef typename SlotsType::const_iterator const_iterator;
    typedef typename SlotsType::value_type value_type;

public:
    CMapSlots(S sSlots) : _sSlots(sSlots), _bDirty(true)
    {}

    virtual ~CMapSlots()
    {
        _oSlots.clear();
    }

    S GetSlots() const { return _sSlots; }
    void SetSlots(S sSlots) { _sSlots = sSlots; }
    void Expand(S sSlots) { _sSlots += sSlots; }
    void Expand2(S sSlots)
    {
        if (sSlots < _sSlots)
            return;
        _sSlots = sSlots;
    }

    // XXX: Get的安全性由HasObj来保证
    const T& Get(S sSlot) const { return _oSlots[sSlot].second; }
    T& Get(S sSlot) { return _oSlots[sSlot].second; } 

    // XXX: 在Get之前一般使用HasObj来测试一下
    bool HasObj(S sSlot) const
    {
        if (sSlot >= _sSlots)
            return false;
        auto i = _oSlots.find(sSlot);
        if (i == _oSlots.end())
            return false;
        return _oSlots[sSlot].first;
    }

    bool HasObj(S sSlot)
    {
        if (sSlot >= _sSlots)
            return false;
        auto i = _oSlots.find(sSlot);
        if (i == _oSlots.end())
            return false;
        return _oSlots[sSlot].first;
    }

    bool IsObjIn(const T& v) const
    {
        for (size_t i = 0; i < _sSlots; ++i)
        {
            if (_oSlots[i] == v)
                return true;
            return false;
        }
    }

    bool Set(S sSlot, const T& obj)
    {
        if (sSlot >= _sSlots)
            return false;

        _oSlots[sSlot].first = true;
        _oSlots[sSlot].second = obj;
        return true;
    }

    bool Reset(S sSlot, const T& obj, T* pT = NULL)
    {
        if (sSlot >= _sSlots)
            return false;

        if (pT && &obj == pT)
            return false;

        V& v = _oSlots[sSlot];
        if (v.first)
        {
            if (pT)
                *pT = v.second;

            v.second = obj;
        }
        else
        {
            v.first = true;
            v.second = obj;
        }

        return true;
    }

    bool Move(S src, S dst)
    {
        if (src == dst)
            return false;
        if (src >= _sSlots || dst >= _sSlots)
            return false;
        V& v = _oSlots[src];
        if (!v.first)
            return false;

        V& yav = _oSlots[dst];
        if (yav.first)
            return Swap(src, dst);

        yav.first = true;
        yav.second = v.second;
        v.first = false;
    }

    bool Swap(S src, S dst)
    {
        if (src == dst)
            return false;
        if (src >= _sSlots || dst >= _sSlots)
            return false;

        V& v = _oSlots[src];
        V& yav = _oSlots[dst];

        if (v.first && yav.first)
        {
            T t = v.second;
            v.second = yav.second;
            yav.second = t;
            return true;
        }
        else if (v.first)
        {
            return Move(src, dst);
        }
        else if (yav.first)
        {
            return Move(dst, src);
        }

        return false;
    }

    S GetUsedCount()
    {
        S s = 0;
        for (iterator i = _oSlots.begin(); i != _oSlots.end(); ++i)
        {
            if (i->second.first)
                ++s;
        }
        return s;
    }

    S GetUsedCount() const
    {
        S s = 0;
        for (iterator i = _oSlots.begin(); i != _oSlots.end(); ++i)
        {
            if (i->second.first)
                ++s;
        }
        return s;
    }

    void enumerate(Enumerator<value_type>& enumerator)
    {
        for (iterator i = _oSlots.begin(); i != _oSlots.end(); ++i)
        {
            if (!enumerator(&*i))
                break;
        }
    }

    void enumerate(Enumerator<value_type>& enumerator) const
    {
        for (const_iterator i = _oSlots.begin(); i != _oSlots.end(); ++i)
        {
            if (!enumerator(&*i))
                break;
        }
    }

    bool IsDirty() const { return _bDirty; }
    void SetDirty(bool bDirty) const { _bDirty = bDirty; }

protected:
    S _sSlots;
    SlotsType _oSlots;
    mutable bool _bDirty;
};

template <typename I, typename S, typename T>
class SlotsEnumerateByInstID : public Enumerator<typename CMapSlots<S, T>::value_type>
{
public:
    typedef typename CMapSlots<S, T>::value_type value_type;

public:
    SlotsEnumerateByInstID(I iInstID) : _iInstID(iInstID), _sSlot(INVALID_SLOT) {}

    bool operator()(value_type* obj)
    {
        if (obj && obj->second.first && obj->second.second->GetInstID() == _iInstID)
        {
            _sSlot = obj->first;
            _pObj = obj->second.second;
            return false;
        }
        return true;
    }

public:
    I _iInstID;
    S _sSlot;
    T _pObj;
};

template <typename I, typename S, typename T>
class SlotsEnumerateByID : public Enumerator<typename CMapSlots<S, T>::value_type>
{
public:
    typedef typename CMapSlots<S, T>::value_type value_type;

public:
    SlotsEnumerateByID(I iID) : _iID(iID), _sSlot(INVALID_SLOT) {}

    bool operator()(value_type* obj)
    {
        if (obj && obj->second.first && obj->second.second->GetID() == _iID)
        {
            _sSlot = obj->first;
            _pObj = obj->second.second;
            return false;
        }
        return true;
    }

public:
    I _iID;
    S _sSlot;
    T _pObj;
};

#endif // MAPSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

