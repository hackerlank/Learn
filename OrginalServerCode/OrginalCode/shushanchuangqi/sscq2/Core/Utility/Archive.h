/********************************************************************
//	Server Utility Library Source File.
//	File name:	Archive.h
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

#pragma once
#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include <stack>
#include <typeinfo>
#include <type_traits>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include "CallStack.h"
#include "ServerDefine.h"

using namespace std;
namespace mpl = boost::mpl;

#define STRICT_DATA_CHECK 1

#define CONTAINER_MAX_SIZE 0x7FFF
#define STRING_MAX_SIZE 0x7FFFFFFF

#define ALIGNMENT_CHECK \
	struct _SAlignment { int x; }; \
	static_assert(TYPE_ALIGNMENT(_SAlignment) == 4, "Alignment not valid!")

#define SCALAR_TYPE_CHECK(T) \
	static_assert(mpl::and_<mpl::or_<is_scalar<T>, is_pod<T>>, mpl::not_<is_pointer<T>>>::value, "Only Scalar Type Allowed!")
#define ALLSIZE (1 << 10)
#define SINGLESIZE (0x100)
#define TEMPLATE_ARRAY_LENGTH_CHECK(T, SIZE) \
	static_assert(sizeof(T) * SIZE <= ALLSIZE  && SIZE < SINGLESIZE, "Array Length Too Large!")
#define TAKE_ARRAY_LENGTH(T) (ALLSIZE/(sizeof(T)) == 0 ? 1 :ALLSIZE/(sizeof(T)))
#define POINTER_TYPE_CHECK(T) \
	static_assert(mpl::not_<is_scalar<T>>::value, "Pointer Type Invalid!")

typedef vector<INT8> TVecINT8;
typedef vector<INT16> TVecINT16;
typedef vector<INT32> TVecINT32;
typedef vector<INT64> TVecINT64;
typedef vector<UINT8> TVecUINT8;
typedef vector<UINT16> TVecUINT16;
typedef vector<UINT32> TVecUINT32;
typedef vector<UINT64> TVecUINT64;
typedef vector<bool> TVecBool;
typedef vector<float> TVecFloat;
typedef vector<double> TVecDouble;
typedef vector<std::string> TVecString;

TVecFloat& operator+=(TVecFloat& vecAttr1, const TVecFloat& vecAttr2);
TVecFloat& operator-=(TVecFloat& vecAttr1, const TVecFloat& vecAttr2);

typedef set<UINT8>  TSetUINT8;
typedef set<UINT16> TSetUINT16;
typedef set<UINT32> TSetUINT32;
typedef set<UINT64> TSetUINT64;

class CInArchive
{
public:
	CInArchive(const char* pBuf = NULL, size_t stLen = 0) : _pBuf(pBuf), _pPos(pBuf), _dwLen((UINT32)stLen) { }
	CInArchive(const string& str) : _pBuf(str.c_str()), _pPos(str.c_str()), _dwLen((UINT32)str.size()) { }
	virtual ~CInArchive() { }
	virtual bool IsForDB() const { return false; }

	template<typename T>
	CInArchive& operator>>(T& val)
	{
		SCALAR_TYPE_CHECK(T);
		if(!CheckPos())
			return *this;
		if(_pPos + sizeof val > _pBuf + _dwLen)
		{
#ifdef _DEBUG
			if(IsForDB())
				DebugBreak();
			else
				throw "T Out of Border";
#elif STRICT_DATA_CHECK || !defined(LOG_CRI)
			throw "T Out of Border";
#else
			LOG_CRI << "T Out of Border";
			return *this;
#endif
		}
		memcpy(&val, _pPos, sizeof val);
		_pPos += sizeof val;
		return *this;
	}

	template<typename T, size_t SIZE>
	CInArchive& operator>>(T (&arr)[SIZE])
	{
		TEMPLATE_ARRAY_LENGTH_CHECK(T, SIZE);
		UINT16 wSize = ReadContainerSize();
		UINT16 i = 0;
		for(; i < wSize && i < SIZE; ++i)
			*this >> arr[i];
		if(wSize != SIZE)
		{
			LOG_WRN << "Array Size not equal! wSize: " << wSize << ", SIZE: " << SIZE;
			static T t;
			while(i < wSize)
				*this >> t;
		}
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(vector<T>& vec)
	{
		UINT16 wSize = ReadContainerSize();
		vec.resize(wSize);
		for(UINT16 i = 0; i < wSize; ++i)
			*this >> vec[i];
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(vector<T*>& vec)
	{
		POINTER_TYPE_CHECK(T);
		UINT16 wSize = ReadContainerSize();
		vec.resize(wSize);
		for(UINT16 i = 0; i < wSize; ++i)
		{
			T* pT = new T;
			if(pT == NULL)
				throw "pT is NULL";
			vec[i] = pT;
			*this >> *pT;
		}
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(list<T>& lst)
	{
		UINT16 wSize = ReadContainerSize();
		for(UINT16 i = 0; i < wSize; ++i)
		{
			lst.push_front(T());
			*this >> lst.front();
		}
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(list<T*>& lst)
	{
		POINTER_TYPE_CHECK(T);
		UINT16 wSize = ReadContainerSize();
		for(UINT16 i = 0; i < wSize; ++i)
		{
			T* pT = new T;
			if(pT == NULL)
				throw "pT is NULL";
			lst.push_front(pT);
			*this >> *pT;
		}
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(set<T>& st)
	{
		UINT16 wSize = ReadContainerSize();
		for(UINT16 i = 0; i < wSize; ++i)
		{
			T t;
			*this >> t;
			st.insert(t);
		}
		return *this;
	}

	template<typename T>
	CInArchive& operator>>(set<T*>& st)
	{
		POINTER_TYPE_CHECK(T);
		UINT16 wSize = ReadContainerSize();
		for(UINT16 i = 0; i < wSize; ++i)
		{
			T* pT = new T;
			if(pT == NULL)
				throw "pT is NULL";
			*this >> *pT;
			st.insert(pT);
		}
		return *this;
	}

	template<typename K, typename V>
	CInArchive& operator>>(map<K, V>& mapK2V)
	{
		UINT16 wSize = ReadContainerSize();
		for(UINT16 i = 0; i < wSize; ++i)
		{
			pair<K, V> pairKV;
			*this >> pairKV.first >> pairKV.second;
			mapK2V.insert(pairKV);
		}
		return *this;
	}

	CInArchive& operator>>(string& str)
	{
		if(!CheckPos())
			return *this;
		UINT32 dwLen = ReadStringLength();
		str.assign(_pPos, dwLen);
		_pPos += dwLen;
		return *this;
	}

	void ToBuf(char* pBuf, UINT32 dwLen)
	{
		if(_pPos + dwLen > _pBuf + _dwLen)
		{
#ifdef _DEBUG
			if(IsForDB())
				DebugBreak();
			else
				throw "T Out of Border";
#elif STRICT_DATA_CHECK || !defined(LOG_CRI)
			throw "T Out of Border";
#else
			LOG_CRI << "T Out of Border";
			return;
#endif
		}
		memcpy(pBuf, _pPos, dwLen);
		_pPos += dwLen;
	}

	void Seek(INT32 dwOffset)
	{
		_pPos += dwOffset;
	}

	template<typename T>
	void SeekThrough(T& size)
	{
		*this >> size;
		_pPos += size;
	}

	UINT16 ReadContainerSize()
	{
		UINT16 wSize = 0;
		*this >> (INT8&)wSize;
		if((INT8)wSize < 0)
		{
			wSize = (wSize & 0x7F) << 8;
			*this >> (UINT8&)wSize;
		}
		return wSize;
	}

	UINT32 ReadStringLength()
	{
		UINT32 dwSize = 0;
		*this >> (INT16&)dwSize;
		if((INT16)dwSize < 0)
		{
			dwSize = (dwSize & 0x7FFF) << 16;
			*this >> (UINT16&)dwSize;
		}
		if(dwSize > 0x100000)
		{
#ifdef _DEBUG
			if(IsForDB())
				DebugBreak();
			else
				throw "T Out of Border";
#elif STRICT_DATA_CHECK || !defined(LOG_CRI)
			throw "String Length Too Large!";
#else
			LOG_CRI << "String Length Too Large!";
			return;
#endif
		}
		return dwSize;
	}

protected:
	virtual bool CheckPos()
	{
		if(_pPos == _pBuf + _dwLen)
			return false;
		return true;
	}

	const char* _pBuf;
	const char* _pPos;
	UINT32 _dwLen;
};

class COutArchive
{
	friend class SFromScalar;
	friend class SFromClass;
public:
#define STRING_RESERVE_LENGTH 20
	COutArchive(string& strBuf = GetDefaultBuf(), UINT32 dwReserve = STRING_RESERVE_LENGTH) : _strBufRef(strBuf)
	{
		_strBufRef.clear();
		if(_strBufRef.capacity() < dwReserve)
			_strBufRef.reserve(dwReserve);
	}

	virtual ~COutArchive() { }
	virtual bool IsForDB() const { return false; }

	void Clear() { _strBufRef.clear(); }

	template<typename T>
	COutArchive& operator<<(const T& val)
	{
		SCALAR_TYPE_CHECK(T);
		_strBufRef.append((const char*)&val, sizeof val);
		return *this;
	}

	template<typename T, size_t SIZE>
	COutArchive& operator<<(T (&arr)[SIZE])
	{
		TEMPLATE_ARRAY_LENGTH_CHECK(T, SIZE);
		UINT16 wSize = (UINT16)SIZE;
		WriteContainerSize(wSize);
		for(UINT16 i = 0; i < wSize; ++i)
			*this << arr[i];
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const vector<T>& vec)
	{
		if(vec.size() > CONTAINER_MAX_SIZE)
			throw "Vector Size Too Large!";
		UINT16 wSize = (UINT16)vec.size();
		WriteContainerSize(wSize);
		for(UINT16 i = 0; i < wSize; ++i)
			*this << vec[i];
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const vector<T*>& vec)
	{
		POINTER_TYPE_CHECK(T);
		if(vec.size() > CONTAINER_MAX_SIZE)
			throw "Vector Size Too Large!";
		UINT16 wSize = (UINT16)vec.size();
		WriteContainerSize(wSize);
		for(UINT16 i = 0; i < wSize; ++i)
			*this << *vec[i];
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const list<T>& lst)
	{
		if(lst.size() > CONTAINER_MAX_SIZE)
			throw "List Size Too Large!";
		UINT16 wSize = (UINT16)lst.size();
		WriteContainerSize(wSize);
		for(typename list<T>::const_iterator cit = lst.begin(); cit != lst.end(); ++cit)
			*this << *cit;
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const list<T*>& lst)
	{
		POINTER_TYPE_CHECK(T);
		if(lst.size() > CONTAINER_MAX_SIZE)
			throw "List Size Too Large!";
		UINT16 wSize = (UINT16)lst.size();
		WriteContainerSize(wSize);
		for(typename list<T*>::const_iterator cit = lst.begin(); cit != lst.end(); ++cit)
			*this << **cit;
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const set<T>& st)
	{
		if(st.size() > CONTAINER_MAX_SIZE)
			throw "Set Size Too Large!";
		UINT16 wSize = (UINT16)st.size();
		WriteContainerSize(wSize);
		for(typename set<T>::const_iterator cit = st.begin(); cit != st.end(); ++cit)
			*this << *cit;
		return *this;
	}

	template<typename T>
	COutArchive& operator<<(const set<T*>& st)
	{
		POINTER_TYPE_CHECK(T);
		if(st.size() > CONTAINER_MAX_SIZE)
			throw "Set Size Too Large!";
		UINT16 wSize = (UINT16)st.size();
		WriteContainerSize(wSize);
		for(typename set<T*>::const_iterator cit = st.begin(); cit != st.end(); ++cit)
			*this << **cit;
		return *this;
	}

	template<typename K, typename V>
	COutArchive& operator<<(const map<K, V>& mapK2V)
	{
		if(mapK2V.size() > CONTAINER_MAX_SIZE)
			throw "Map Size Too Large!";
		UINT16 wSize = (UINT16)mapK2V.size();
		WriteContainerSize(wSize);
		for(typename map<K, V>::const_iterator cit = mapK2V.begin(); cit != mapK2V.end(); ++cit)
			*this << cit->first << cit->second;
		return *this;
	}

	COutArchive& operator<<(const string& str)
	{
		if(str.size() > STRING_MAX_SIZE)
			throw "String Length Too Large!";
		WriteStringLength((UINT32)str.size());
		_strBufRef.append(str.c_str(), str.size());
		return *this;
	}

	void FromBuf(const char* pBuf, UINT32 dwLen)
	{
		_strBufRef.append(pBuf, dwLen);
	}

	char* GetBuf(UINT32& dwLen)
	{
		dwLen = (UINT32)_strBufRef.size();
		return const_cast<char*>(_strBufRef.c_str());
	}

	void WriteContainerSize(UINT16 wSize)
	{
		if(wSize > 0x7F)
			*this << UINT16(wSize >> 8 | 0x80 | wSize << 8);
		else
			*this << (UINT8)wSize;
	}

	void WriteStringLength(UINT32 dwSize)
	{
		if(dwSize > 0x7FFF)
			*this << UINT32(dwSize >> 16 | 0x8000 | dwSize << 16);
		else
			*this << (UINT16)dwSize;
	}

	string& GetString() { return _strBufRef; }

protected:
	static string& GetDefaultBuf()
	{
		static string _strDefaultBuf;
		return _strDefaultBuf;
	}

	string& _strBufRef;
};

class CDBInArchive : public CInArchive
{
public:
	CDBInArchive(const char* pBuf = NULL, size_t stLen = 0) : CInArchive(pBuf, stLen) { }
	CDBInArchive(const string& str) : CInArchive(str) { }

	virtual ~CDBInArchive()
	{
		if(!_stkEndPos.empty())
		{
#ifdef _DEBUG
			DebugBreak();
#else
			throw "Stack of End Position is not empty!";
#endif
		}
	}

	virtual bool IsForDB() const { return true; }

	template<typename T>
	void PushEndPos(T& len)
	{
		(CInArchive&)*this >> len;
		const char* pEndPos = _pPos + len;
		_stkEndPos.push(pEndPos);
	}

	void PopEndPos()
	{
		const char* pEndPos = _stkEndPos.top();
		if(_pPos < pEndPos)
			_pPos = pEndPos;
		else if(_pPos > pEndPos)
			throw "End Position Corrupt!";
		_stkEndPos.pop();
	}

	virtual bool CheckPos()
	{
		if(!CInArchive::CheckPos())
			return false;
		if(!_stkEndPos.empty())
		{
			const char* pEndPos = _stkEndPos.top();
			if(_pPos >= pEndPos)
				return false;
		}
		return true;
	}

protected:
	stack<const char*> _stkEndPos;
};

class CDBOutArchive : public COutArchive
{
public:
	CDBOutArchive(string& strBuf, UINT32 dwReserve = STRING_RESERVE_LENGTH) : COutArchive(strBuf, dwReserve) { }
	virtual ~CDBOutArchive() { }
	virtual bool IsForDB() const { return true; }

	size_t GetLength() const { return _strBufRef.size(); }

	template<typename T>
	size_t PreWriteLength(T len)
	{
		size_t pos = _strBufRef.size();
		(COutArchive&)*this << len;
		return pos;
	}

	template<typename T>
	void WriteLength(size_t pos, T len)
	{
		if(len > STRING_MAX_SIZE)
			throw "Struct Length Too Large!";
		if(pos + sizeof(T) > _strBufRef.size())
			throw "Struct Member Error!";
		*(T*)&_strBufRef[pos] = len;
	}
};
