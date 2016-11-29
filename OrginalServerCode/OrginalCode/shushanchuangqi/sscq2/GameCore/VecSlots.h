
#ifndef VECSLOTS_H_
#define VECSLOTS_H_

#include "Platform.h"
#include "Enumerator.h"

#include <tuple>
#include <vector>

#ifndef INVALID_SLOT
#define INVALID_SLOT ((int)-1)
#endif

// XXX: S must be signed
template <typename S, typename T>
class CVecSlots
{
public:
    typedef std::tuple<int/*slot*/, bool/*hasobj*/, T/*value*/> V;
    typedef std::vector<V> SlotsType;
    typedef typename SlotsType::iterator iterator;
    typedef typename SlotsType::const_iterator const_iterator;
    typedef typename SlotsType::value_type value_type;

public:
    CVecSlots(S sSlots) : _sSlots(sSlots), _sUsed(0), _bDirty(true)
    {
        _oSlots.resize(_sSlots);
    }

    virtual ~CVecSlots()
    {
        _sUsed = 0;
        _oSlots.clear();
    }

    S GetSlots() const { return _sSlots; }
    void SetSlots(S sSlots)
    {
        if (_sSlots != sSlots)
            _oSlots.resize(_sSlots);
        _sSlots = sSlots;
    }

    void Expand(S sSlots)
    {
        _sSlots += sSlots;
        if (sSlots)
            _oSlots.resize(_sSlots);
    }

    void Expand2(S sSlots)
    {
        if (sSlots < _sSlots)
            return;
        if (_sSlots != sSlots)
            _oSlots.resize(_sSlots);
        _sSlots = sSlots;
    }

    // XXX: Get的安全性由HasObj来保证
    const T& Get(S sSlot) const { return std::get<2>(_oSlots[sSlot]); }
    T& Get(S sSlot) { return std::get<2>(_oSlots[sSlot]); } 

    // XXX: 在Get之前一般使用HasObj来测试一下
    bool HasObj(S sSlot) const
    {
        if (sSlot >= _sSlots)
            return false;
        return std::get<1>(_oSlots[sSlot]);
    }

    bool HasObj(S sSlot)
    {
        if (sSlot >= _sSlots)
            return false;
        return std::get<1>(_oSlots[sSlot]);
    }

    bool IsObjIn(const T& v) const
    {
        for (size_t i = 0; i < _sSlots; ++i)
        {
            if (std::get<2>(_oSlots[i]) == v)
                return true;
            return false;
        }
    }
    
    bool SetHasObj(S sSlot, bool bHas = true)
    {
        if (sSlot >= _sSlots)
            return false;
        if (bHas && !std::get<1>(_oSlots[sSlot]))
            ++_sUsed;
        if (!bHas && std::get<1>(_oSlots[sSlot]) && _sUsed)
            --_sUsed;
        std::get<1>(_oSlots[sSlot]) = bHas;
        return true;
    }

    bool Set(S sSlot, const T& obj)
    {
        if (sSlot >= _sSlots)
            return false;

        std::get<0>(_oSlots[sSlot]) = sSlot;
        std::get<1>(_oSlots[sSlot]) = true;
        std::get<2>(_oSlots[sSlot]) = obj;
        ++_sUsed;
        return true;
    }

    bool Reset(S sSlot, const T& obj, T* pT = NULL)
    {
        if (sSlot >= _sSlots)
            return false;

        if (pT && &obj == pT)
            return false;

        V& v = _oSlots[sSlot];
        if (std::get<1>(v))
        {
            if (pT)
                *pT = std::get<2>(v);

            std::get<2>(v) = obj;
        }
        else
        {
            std::get<0>(v) = sSlot;
            std::get<1>(v) = true;
            std::get<2>(v) = obj;
        }

        return true;
    }

    bool Reset(S sSlot, T* pT = NULL)
    {
        if (sSlot >= _sSlots)
            return false;

        V& v = _oSlots[sSlot];
        if (std::get<1>(v))
        {
            if (pT)
                *pT = std::get<2>(v);

            std::get<1>(v) = false;
            if (_sUsed)
                --_sUsed;
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
        if (!std::get<1>(v))
            return false;

        V& yav = _oSlots[dst];
        if (std::get<1>(yav))
            return Swap(src, dst);

        std::get<0>(yav) = dst;
        std::get<1>(yav) = true;
        std::get<2>(yav) = std::get<2>(v);
        std::get<1>(v) = false;
    }

    bool Swap(S src, S dst)
    {
        if (src == dst)
            return false;
        if (src >= _sSlots || dst >= _sSlots)
            return false;

        V& v = _oSlots[src];
        V& yav = _oSlots[dst];

        if (std::get<1>(v) && std::get<1>(yav))
        {
            T t = std::get<2>(v);
            std::get<2>(v) = std::get<2>(yav);
            std::get<2>(yav) = t;
            return true;
        }
        else if (std::get<1>(v))
        {
            return Move(src, dst);
        }
        else if (std::get<1>(yav))
        {
            return Move(dst, src);
        }

        return false;
    }

    S GetUsedCount() { return _sUsed; }
    S GetUsedCount() const { return _sUsed; }

    S GetEmptySlot()
    {
        for (S i = 0; i < _sSlots; ++i)
        {
            if (!std::get<1>(_oSlots[i]))
                return i;
        }

        _oSlots.resize(_sSlots+1+10); // XXX:
        return _oSlots.size();
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
    S _sUsed;
    SlotsType _oSlots;
    mutable bool _bDirty;
};

template <typename I, typename S, typename T>
class VecSlotsEnumerateByInstID : public Enumerator<typename CVecSlots<S, T>::value_type>
{
public:
    typedef typename CVecSlots<S, T>::value_type value_type;

public:
    VecSlotsEnumerateByInstID(I iInstID) : _iInstID(iInstID), _sSlot(INVALID_SLOT) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj)->GetInstID() == _iInstID)
        {
            _sSlot = std::get<0>(*obj);
            _pObj = std::get<2>(*obj);
            return false;
        }
        return true;
    }

    bool operator()(value_type* obj) const
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj)->GetInstID() == _iInstID)
        {
            _sSlot = std::get<0>(*obj);
            _pObj = std::get<2>(*obj);
            return false;
        }
        return true;
    }

public:
    I _iInstID;
    mutable S _sSlot;
    mutable T _pObj;
};

template <typename I, typename S, typename T>
class VecSlotsEnumerateByID : public Enumerator<typename CVecSlots<S, T>::value_type>
{
public:
    typedef typename CVecSlots<S, T>::value_type value_type;

public:
    VecSlotsEnumerateByID(I iID) : _iID(iID), _sSlot(INVALID_SLOT) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj)->GetID() == _iID)
        {
            _sSlot = std::get<0>(*obj);
            _pObj = std::get<2>(*obj);
            return false;
        }
        return true;
    }

    bool operator()(const value_type* obj) const
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj)->GetID() == _iID)
        {
            _sSlot = std::get<0>(*obj);
            _pObj = std::get<2>(*obj);
            return false;
        }
        return true;
    }

public:
    I _iID;
    mutable S _sSlot;
    mutable T _pObj;
};

#endif // VECSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

