#pragma once
#ifdef _WIN32
#pragma warning(disable:4150)
#endif
#include <memory>
#include <type_traits>
#define BOOST_FUNCTION_MAX_ARGS 20
#include <boost/function.hpp>
#include "Platform.h"
#include "Encode.h"

using namespace std;

typedef shared_ptr<void> VoidPtr;

template<typename T, typename U>
shared_ptr<T> ToPtr(U& rU)
{
	if(is_base_of<T, U>::value)
		return static_pointer_cast<T>(rU.shared_from_this());
	return dynamic_pointer_cast<T>(rU.shared_from_this());
}

template<typename T, typename U>
shared_ptr<T> ToPtr(U* pU)
{
	if(pU == NULL)
		return NULL;
	return ToPtr<T>(*pU);
}

template<typename T>
shared_ptr<T> ToThisPtr(T& rT)
{
	return static_pointer_cast<T>(rT.shared_from_this());
}

template<typename T>
shared_ptr<T> ToThisPtr(T* pT)
{
	if(pT == NULL)
		return NULL;
	return ToThisPtr<T>(*pT);
}

template<typename T>
class shared_func : public shared_ptr<T>
{
public:
	template<class U>
	shared_func(U&& u) : shared_ptr<T>(std::forward<U>(u)) { }

	template<typename Arg>
	void operator()(Arg&& arg) const { (**this)(std::forward<Arg>(arg)); }
};

class IProtocol;

class CProtFuncAck
{
public:
	CProtFuncAck(IProtocol& rProtocol, UINT32 dwSessionID)
		: _rProtocol(rProtocol), _dwSessionID(dwSessionID), _bReturned(false) { }
	virtual ~CProtFuncAck() { }
	void operator()(bool bRet)
	{
		if(_bReturned)
			return;
		SendReturn(bRet);
		_bReturned = true;
	}
	bool HasReturned() const { return _bReturned; }
protected:
	virtual void SendReturn(bool bRet) = 0;
	IProtocol& _rProtocol;
	UINT32 _dwSessionID;
	bool _bReturned;
};

class CServerFuncAck : public CProtFuncAck
{
public:
	CServerFuncAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID)
		: CProtFuncAck(rProtocol, dwSessionID), _dwSvrID(dwSvrID) { }
protected:
	UINT32 _dwSvrID;
};

class CClientFuncAck : public CProtFuncAck
{
public:
	CClientFuncAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID)
		: CProtFuncAck(rProtocol, dwSessionID), _qwUsrID(qwUsrID) { }
protected:
	UINT64 _qwUsrID;
};

////////////////////////////////////////////////////////////////////////////////////////////
//Server Common Macro

#ifdef _DEBUG
#define FRAME_OVERTIME_LIMIT 100
#else
#define FRAME_OVERTIME_LIMIT 50
#endif

#define OPEN_CRI
#define OPEN_WRN
#define OPEN_INF
#if defined(_DEBUG)
#define OPEN_DBG
#define OPEN_TXT
#endif
#include "Log.h"
extern CLog g_oLog;
#define LOG_OBJ g_oLog
#include "LogDefine.h"

#define DELETE_MAP_VALUE(map) \
	for(auto it_ = map.begin(); it_ != map.end(); ++it_) \
		delete it_->second; \
	map.clear();

#define DELETE_VEC_VALUE(vec) \
	for(size_t i_ = 0; i_ < vec.size(); ++i_) \
		delete vec[i_]; \
	vec.clear();

#ifdef _WIN32
#define ToUTF8(text) GB2312ToUTF8(text)
#define ToUTF8Ptr(text) GB2312ToUTF8(text).c_str()
#define ToGB2312(text) UTF8ToGB2312(text)
#define ToGB2312Ptr(text) UTF8ToGB2312(text).c_str()
#else
#define ToUTF8(text) text
#define ToUTF8Ptr(text) text
#define ToGB2312(text) text
#define ToGB2312Ptr(text) text
#endif

#define IS_ADD_OVERFLOW(a, b) ((a) + (b) < (a) || (a) + (b) < (b))
#define IS_ADD_MAX_OVERFLOW(a, b, max) ((a) > (max) || (b) > (max) || (a) + (b) > (max) || (a) + (b) < (a) || (a) + (b) < (b))

#define IS_SUB_OVERFLOW(a, b) ((b) > (a))
#define IS_MULTIPLY_OVERFLOW(a, b) (((a) != 0 && (b) != 0) ? ((a) * (b) / (a) != (b)) : false)

#ifndef UNUSED
#define UNUSED(x) x
#endif
