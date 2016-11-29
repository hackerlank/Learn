
#ifndef ARRSLOTS_H_
#define ARRSLOTS_H_

#include "Platform.h"
#include "Enumerator.h"

#include <tuple>

#ifndef INVALID_SLOT
#define INVALID_SLOT ((int)-1)
#endif

#define DEFAULT_ARRSLOT_SIZE 3

// XXX: S must be signed
template <typename S, typename T, size_t SIZE = DEFAULT_ARRSLOT_SIZE>
class CArrSlots
{
public:
    typedef std::tuple<int/*slot*/, bool/*hasobj*/, T/*value*/> V;
    typedef V value_type;

public:
    CArrSlots(S size = SIZE) : _sSlots(size>static_cast<S>(SIZE)?SIZE:size), _sUsed(0), _bDirty(true)
    {
        for (S i = 0; i < _sSlots; ++i)
            std::get<1>(_oSlots[i]) = false;
    }

    virtual ~CArrSlots()
    {
        _sUsed = 0;
    }

    S GetSlots() const { return _sSlots; }

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

    bool Unset(S sSlot, T& obj)
    {
        if (sSlot >= _sSlots)
            return false;
        V& v = _oSlots[sSlot];
        if (std::get<1>(v))
        {
            std::get<1>(v) = false;
            obj = std::get<2>(v);
            if (_sUsed)
                --_sUsed;
            return true;
        }
        return false;
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
        return true;
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

    S GetEmptySlot() const
    {
        for (size_t i = 0; i < SIZE; ++i)
        {
            if (!std::get<1>(_oSlots[i]))
                return i;
        }
        return INVALID_SLOT;
    }

	bool Tidyup()
    {
        return true;
    }

    void enumerate(Enumerator<value_type>& enumerator)
    {
        for (S i = 0; i < _sSlots; ++i)
        {
            if (!enumerator(&_oSlots[i]))
                break;
        }
    }

    void enumerate(Enumerator<value_type>& enumerator) const
    {
        for (S i = 0; i < _sSlots; ++i)
        {
            if (!enumerator(&_oSlots[i]))
                break;
        }
    }

    bool IsDirty() const { return _bDirty; }
    virtual void SetDirty(bool bDirty) const { _bDirty = bDirty; }

protected:
    S _sSlots;
    S _sUsed;
    V _oSlots[SIZE];
    mutable bool _bDirty;
};

template <typename I, typename S, typename T, size_t SIZE = 3>
class ArrSlotsEnumerateByInstID : public Enumerator<typename CArrSlots<S, T, SIZE>::value_type>
{
public:
    typedef typename CArrSlots<S, T, SIZE>::value_type value_type;

public:
    ArrSlotsEnumerateByInstID(I iInstID) : _iInstID(iInstID), _sSlot(INVALID_SLOT) {}

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

public:
    I _iInstID;
    S _sSlot;
    T _pObj;
};

template <typename I, typename S, typename T, size_t SIZE = 3>
class ArrSlotsEnumerateByID : public Enumerator<typename CArrSlots<S, T, SIZE>::value_type>
{
public:
    typedef typename CArrSlots<S, T, SIZE>::value_type value_type;

public:
    ArrSlotsEnumerateByID(I iID) : _iID(iID), _sSlot(INVALID_SLOT) {}

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

public:
    I _iID;
    S _sSlot;
    T _pObj;
};

#endif // ARRSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

