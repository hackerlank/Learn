/********************************************************************
//	Server Utility Library Source File.
//	File name:	ObjPool.h
//	Created:	2012/08/21	11:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
 *********************************************************************/
#ifndef OBJ_POOL_H
#define OBJ_POOL_H

#pragma once
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <atomic>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#ifdef _WIN32
#include <assert.h>
#define __PRETTY_FUNCTION__ __FUNCTION__
#else
#include <Linux.h>
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif
#include "Platform.h"
#include "Singleton.h"
#include <typeinfo>
#include "Linux.h"

class PoolRecord
{
    public:
        static  void DoNew(const std::string & strName)
        {
            _Count[strName]++;

        }
       static void DoDel(const std::string & strName)
        {
            _Count[strName]--;
        }
       static void  GetUseCount( std::map<std::string,UINT64> &Count)
        {
            Count = _Count;
        }
    private:
       static  std::map<std::string,UINT64> _Count;

};
namespace mpl = boost::mpl;

using std::atomic;
using std::memory_order_release;
using std::memory_order_acquire;
using std::memory_order_relaxed;

const UINT8 WRAP_MAKR = 0x12;
const UINT8 ALLOC_MARK = 0x34;

struct SSignSingleWord
{
    template<typename T>
        static UINT16 GetSign(T val)
        {
            return (UINT16)val;
        }
};

struct SSignDoubleWord
{
    template<typename T>
        static UINT16 GetSign(T val)
        {
            UINT32 dwValue = (UINT32)val;
            return UINT16(dwValue + *((UINT16*)&dwValue + 1));
        }
};

struct SSignQuadWord
{
    template<typename T>
        static UINT16 GetSign(T val)
        {
            UINT64 qwValue = (UINT64)val;
            return UINT16(qwValue + *((UINT16*)&qwValue + 1) + *((UINT16*)&qwValue + 2) + *((UINT16*)&qwValue + 3));
        }
};

typedef mpl::map<
mpl::pair<mpl::int_<1>, SSignSingleWord>,
    mpl::pair<mpl::int_<2>, SSignSingleWord>,
    mpl::pair<mpl::int_<4>, SSignDoubleWord>,
    mpl::pair<mpl::int_<8>, SSignQuadWord>
    > TMapSign;

    template<typename T>
UINT16 GetSign(T value)
{
    return mpl::at<TMapSign, mpl::int_<sizeof(T)> >::type::GetSign(value);
};

struct SFlag
{
    UINT8 byWrapper;
    UINT8 byAlloc;
    UINT16 wSign;

    SFlag() : byWrapper(0), byAlloc(0), wSign(0) { }
};

template<typename T>
struct SObjectWrapper
{
    SFlag flag;
    T object;

    static SObjectWrapper* GetWrapper(const T* pObject)
    {
        static_assert(sizeof(SFlag) == sizeof(UINT32), "Wrap Head Size Invalid!");
        return CONTAINING_RECORD(pObject, SObjectWrapper, object);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//单线程对象池

template<typename T, bool WRAP = false>
class CObjectPool : public StaticSingleton<CObjectPool<T, WRAP>>
{
    public:
#ifdef _DEBUG
        CObjectPool() : _dwOutCount(0) { }
#endif

        ~CObjectPool()
        {
            for(size_t i = 0; i < _vecObj.size(); ++i)
            {
                T* p = _vecObj[i];
                if(WRAP)
                {
                    SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
                    if(pWrapper->flag.byWrapper != 0)
                        __builtin_trap();
                        // DebugBreak();
                    if(pWrapper->flag.byAlloc != 0)
                        __builtin_trap();
                        // DebugBreak();
                    free(pWrapper);
                }
                else
                {
                    free(p);
                }
            }
            _vecObj.clear();
        }

        T* Alloc()
        {
            T* p = Pop();
            if(p != NULL)
            {
#ifdef _DEBUG
                if(WRAP)
                {
                    SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
                    char* pBuf = (char*)pWrapper;
                    for(size_t i = 0; i < sizeof(SObjectWrapper<T>); ++i)
                        assert(pBuf[i] == (char)0xbb);
                }
                else
                {
                    char* pBuf = (char*)p;
                    for(size_t i = 0; i < sizeof(T); ++i)
                        assert(pBuf[i] == (char)0xbb);
                }
#endif
                if(WRAP)
                {
                    SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
                    pWrapper->flag.byWrapper = WRAP_MAKR;
                    pWrapper->flag.byAlloc = ALLOC_MARK;
                }
            }
            else if(WRAP)
            {
                SObjectWrapper<T>* pWrapper = (SObjectWrapper<T>*)malloc(sizeof(SObjectWrapper<T>));
                if(pWrapper == NULL)
                {
                    printf("malloc fails! [%s:%u]\n", __PRETTY_FUNCTION__, __LINE__);
                    return NULL;
                }
                pWrapper->flag.byWrapper = WRAP_MAKR;
                pWrapper->flag.byAlloc = ALLOC_MARK;
                p = &pWrapper->object;
            }
            else
            {
                p = (T*)malloc(sizeof(T));
                if(p == NULL)
                {
                    printf("malloc fails! [%s:%u]\n", __PRETTY_FUNCTION__, __LINE__);
                    return NULL;
                }
            }
#ifdef _DEBUG
            memset(p, 0xcd, sizeof(T));
            ++_dwOutCount;
#endif
            return p;
        }

        void Free(T* p)
        {
            if(p == NULL)
                return;
            if(WRAP)
            {
                SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
                if(pWrapper->flag.byWrapper != WRAP_MAKR)
                    __builtin_trap();
                    // DebugBreak();
                if(pWrapper->flag.byAlloc != ALLOC_MARK)
                    __builtin_trap();
                    // DebugBreak();
                pWrapper->flag.byWrapper = 0;
                pWrapper->flag.byAlloc = 0;
            }
#ifdef _DEBUG
            if(WRAP)
            {
                SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
                memset(pWrapper, 0xbb, sizeof(SObjectWrapper<T>));
            }
            else
            {
                memset(p, 0xbb, sizeof(T));
            }
            --_dwOutCount;
#endif
            _vecObj.push_back((T*)p);
        }

#ifdef _DEBUG
        UINT32 GetOutCount() const { return _dwOutCount; }
#endif

    private:
        T* Pop()
        {
            if(_vecObj.empty())
                return NULL;
            T* p = _vecObj.back();
            _vecObj.pop_back();
            return p;
        }

        std::vector<T*> _vecObj;
#ifdef _DEBUG
        UINT32 _dwOutCount;
#endif
};
template<typename T, bool WRAP = false>
class CPoolObj
{
    public:
        inline void* operator new(size_t size)
        {
            PoolRecord::DoNew(typeid(T).name());
            if(size != sizeof(T))
                return ::operator new(size);
            else
                return CObjectPool<T, WRAP>::Instance().Alloc();
        }
        inline void* operator new(size_t size,void *p)
        {
            return ::operator new(size,p);
        }
        inline void operator delete(void* p, size_t size)
        {
            PoolRecord::DoDel(typeid(T).name());
            if(size != sizeof(T))
                ::operator delete(p);
            else
                CObjectPool<T, WRAP>::Instance().Free((T*)p);
        }
};

//#define USE_MEM_POOL

#ifdef USE_MEM_POOL

#define DEF_NEW_DELETE(T) \
    friend struct SObjectWrapper<T>; \
inline void* operator new(size_t size) \
{ \
    if(size != sizeof(T)) \
    return ::operator new(size); \
    else \
    return CObjectPool<T>::Instance().Alloc(); \
} \
inline void* operator new(size_t size, void* ptr) \
{ \
    return ::operator new(size, ptr); \
} \
inline void operator delete(void* pMem, size_t size) \
{ \
    if(size != sizeof(T)) \
    ::operator delete(pMem); \
    else \
    CObjectPool<T>::Instance().Free((T*)pMem); \
} \
inline void operator delete(void* pMem, void* ptr) \
{ \
    ::operator delete(pMem, ptr); \
}

#define DEF_NEW_DELETE_WRAP(T) \
    friend struct SObjectWrapper<T>; \
bool IsValidObject() const { return SObjectWrapper<T>::GetWrapper(this)->flag.byAlloc == ALLOC_MARK; } \
template<typename U> \
void SetWrapSign(U val) { SObjectWrapper<T>::GetWrapper(this)->flag.wSign = GetSign(val); } \
template<typename U> \
bool IsValidObject(U val) const { return IsValidObject() && SObjectWrapper<T>::GetWrapper(this)->flag.wSign != 0 \
    && SObjectWrapper<T>::GetWrapper(this)->flag.wSign == GetSign(val); } \
inline void* operator new(size_t size) \
{ \
    if(size != sizeof(T)) \
    return (T*)::operator new(size); \
    else \
    return CObjectPool<T, true>::Instance().Alloc(); \
} \
inline void* operator new(size_t size, void* ptr) \
{ \
    return ::operator new(size, ptr); \
} \
inline void operator delete(void* pMem, size_t size) \
{ \
    if(size != sizeof(T)) \
    ::operator delete(pMem); \
    else \
    CObjectPool<T, true>::Instance().Free((T*)pMem); \
} \
inline void operator delete(void* pMem, void* ptr) \
{ \
    ::operator delete(pMem, ptr); \
}

#else

#define DEF_NEW_DELETE(T)
#define DEF_NEW_DELETE_WRAP(T)

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//多线程对象池

template<typename T, bool WRAP = false>
class CObjectPoolMT : public MultiThreadSingleton<CObjectPoolMT<T, WRAP>>
{
    struct SNode
    {
        SNode* next;
        char buf[sizeof(typename mpl::if_c<WRAP, SObjectWrapper<T>, T>::type)];
    };
    public:
    CObjectPoolMT() : _head(NULL) { }

    virtual ~CObjectPoolMT()
    {
        SNode* pNode;
        pNode = Pop();
        while(pNode)
        {
            free(pNode);
            pNode = Pop();
        }
    }

    T* Alloc()
    {
        SNode* pNode = Pop();
        if(pNode == NULL)
        {
            pNode = (SNode*)malloc(sizeof(SNode));
        }
#ifdef _DEBUG
        else
        {
            char* pBuf = (char*)pNode->buf;
            for(size_t i = 0; i < sizeof(pNode->buf); ++i)
                assert(pBuf[i] == (char)0xbb);
        }
#endif
        if(pNode == NULL)
        {
            printf("malloc fails! [%s:%d]\n", __PRETTY_FUNCTION__, __LINE__);
            return NULL;
        }
#ifdef _DEBUG
        memset(pNode, 0xcd, sizeof(SNode));
#endif
        T* p = NULL;
        if(WRAP)
        {
            SObjectWrapper<T>* pWrapper = (SObjectWrapper<T>*)pNode->buf;
            pWrapper->flag.byWrapper = WRAP_MAKR;
            pWrapper->flag.byAlloc = ALLOC_MARK;
            p = &pWrapper->object;
        }
        else
        {
            p = (T*)pNode->buf;
        }
        return p;
    }

    void Free(T* p)
    {
        if(p == NULL)
            return;
        SNode* pNode = NULL;
        if(WRAP)
        {
            SObjectWrapper<T>* pWrapper = SObjectWrapper<T>::GetWrapper(p);
            if(pWrapper->flag.byWrapper != WRAP_MAKR)
                __builtin_trap();
                // DebugBreak();
            if(pWrapper->flag.byAlloc != ALLOC_MARK)
                __builtin_trap();
                // DebugBreak();
            pWrapper->flag.byWrapper = 0;
            pWrapper->flag.byAlloc = 0;
            pNode = CONTAINING_RECORD(pWrapper, SNode, buf);
        }
        else
        {
            pNode = CONTAINING_RECORD(p, SNode, buf);
        }
#ifdef _DEBUG
        assert(pNode->next == (SNode*)0xcdcdcdcdcdcdcdcd);
        memset(pNode, 0xbb, sizeof(SNode));
#endif
        SNode* pHead = NULL;
        do {
            pHead = _head.load(memory_order_acquire);
            pNode->next = pHead;
        } while(!_head.compare_exchange_weak(pHead, pNode, memory_order_release, memory_order_acquire));
    }

    private:
    SNode* Pop()
    {
        SNode* pHead = NULL;
        SNode* pNode = NULL;
        do {
            pNode = _head.load(memory_order_acquire);
            if(pNode == NULL)
                break;
            pHead = pNode->next;
        } while(!_head.compare_exchange_weak(pNode, pHead, memory_order_release, memory_order_acquire));
        return pNode;
    }

    atomic<SNode*> _head;
};

template<typename T, bool WRAP = false>
class CMTPoolObj
{
    public:
        inline void* operator new(size_t size)
        {
            if(size != sizeof(T))
                return ::operator new(size);
            else
                return CObjectPoolMT<T, WRAP>::Instance().Alloc();
        }
        inline void operator delete(void* p, size_t size)
        {
            if(size != sizeof(T))
                ::operator delete(p);
            else
                CObjectPoolMT<T, WRAP>::Instance().Free((T*)p);
        }
};

#define USE_MT_MEM_POOL

#ifdef USE_MT_MEM_POOL

#define DEF_NEW_DELETE_MT(T) \
    friend struct SObjectWrapper<T>; \
inline void* operator new(size_t size) \
{ \
    if(size != sizeof(T)) \
    return (T*)::operator new(size); \
    else \
    return CObjectPoolMT<T>::Instance().Alloc(); \
} \
inline void operator delete(void *p, size_t size) \
{ \
    if(size != sizeof(T)) \
    ::operator delete(p); \
    else \
    CObjectPoolMT<T>::Instance().Free((T*)p); \
}

#define DEF_NEW_DELETE_MT_WRAP(T) \
    friend struct SObjectWrapper<T>; \
bool IsValidObject() const { return SObjectWrapper<T>::GetWrapper(this)->flag.byAlloc == ALLOC_MARK; } \
void SetWrapSign(UINT16 wSign) { SObjectWrapper<T>::GetWrapper(this)->flag.wSign = wSign; } \
bool IsValidObject(UINT16 wSign) const { return IsValidObject() && SObjectWrapper<T>::GetWrapper(this)->flag.wSign != 0 \
    && SObjectWrapper<T>::GetWrapper(this)->flag.wSign == wSign; } \
inline void* operator new(size_t size) \
{ \
    if(size != sizeof(T)) \
    return (T*)::operator new(size); \
    else \
    return CObjectPoolMT<T, true>::Instance().Alloc(); \
} \
inline void operator delete(void *p, size_t size) \
{ \
    if(size != sizeof(T)) \
    ::operator delete(p); \
    else \
    CObjectPoolMT<T, true>::Instance().Free((T*)p); \
}

#else

#define DEF_NEW_DELETE_MT(T)
#define DEF_NEW_DELETE_MT_WRAP(T)

#endif // #ifdef USE_MT_MEM_POOL

#endif // #ifndef OBJ_POOL_H
