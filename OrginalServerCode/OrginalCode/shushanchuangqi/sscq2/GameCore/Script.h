/********************************************************************
//	Game Server Source File.
//	File name:	Script.h
//	Created:	2012/08/30	10:00
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

#define BOOST_PP_ITERATION_FLAGS_0() 0

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <luabind/luabind.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/iterator_policy.hpp>
#include "Linux.h"
#include "ServerDefine.h"
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;
using namespace luabind;


#define DEF_SHAREDPTR(obj)          \
    class_<obj##Ptr>(#obj"Ptr")   \
        .def("get", &obj##Ptr::get)

#define DEF_WEAKPTR(obj)            \
    class_<obj##Wtr>(#obj"Wtr")   \
        .def("lock", &obj##Wtr::lock)

#define DEF_PTR(obj) DEF_SHAREDPTR(obj),DEF_WEAKPTR(obj)

enum ELuaError
{
    eLuaErrNone,
    eLuaErrCallNil,
    eLuaErrOther
};

#define LUA_BEGIN try {

#define LUA_END(script) \
	} \
	catch(exception& ex) \
	{ \
		LOG_CRI << (script).GetFilePath() << ": " << ex.what(); \
	} \
	catch(...) \
	{ \
		LOG_CRI << (script).GetFilePath() << ": Unknown Error!"; \
	}

ELuaError LuaError_CallBack(lua_State* pLuaState, bool bOpenLog = true);

class CScript : public enable_shared_from_this<CScript>
{
public:
    static bool IsDebug();
    static UINT32 GetVersion();

public:
	CScript();
	virtual ~CScript();
	DEF_NEW_DELETE(CScript);

	lua_State* GetState() const { return _pLuaState; }
	string& GetFilePath() { return _strFilePath; }
	ELuaError GetLuaError() const { return _eLuaError; }
    bool IsLoaded() const { return _bLoaded; }
	bool HasFunction(const string& strName);

	virtual bool Register();
    virtual void SetGlobals();
	bool LoadLuaFile(const string& strFile);
	bool LoadMainFile(const string& strFile, int server, int flag);
    bool Init(int server, int flag);
    bool Reload(int flag);

    template <typename T>
    void Set(const char* name, const T& value)
    {
        if (!name) return;
        luabind::globals(GetState())[name] = value;
    }

#define PRINT_EXECUTEFUNC_PARAM(z, n, unused) const P##n& rP##n

#define FUNCTION_BEGIN \
	if(!_bLoaded || strFuncName.empty()) \
		return false; \
	_eLuaError = eLuaErrNone; \
	try \
	{ \

#define FUNCTION_END \
		return true; \
	} \
	catch(luabind::error e) \
	{ \
		_eLuaError = LuaError_CallBack(_pLuaState, _bLogOpen); \
		if(_bLogOpen) \
			LOG_CRI << "[" << _strFilePath << ": " << strFuncName << "] " << e.what(); \
	} \
	catch(luabind::cast_failed e) \
	{ \
		_eLuaError = LuaError_CallBack(_pLuaState, _bLogOpen); \
		if(_bLogOpen) \
			LOG_CRI << "[" << _strFilePath << ": " << strFuncName << "] " << e.what(); \
	} \
	catch(...) \
	{ \
		_eLuaError = LuaError_CallBack(_pLuaState, _bLogOpen); \
		if(_bLogOpen) \
			LOG_CRI << "[" << _strFilePath << ": " << strFuncName << "]"; \
	} \
	return false;

#define DEF_FUNC_EXECUTEFUNC(z, n, unused) \
	template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename P)> \
	bool Call(const string& strFuncName, R& rRet BOOST_PP_ENUM_TRAILING(n, PRINT_EXECUTEFUNC_PARAM, none)) \
	{ \
		FUNCTION_BEGIN \
		rRet = call_function<R>(_pLuaState, strFuncName.c_str() BOOST_PP_ENUM_TRAILING_PARAMS(n, rP)); \
		FUNCTION_END \
	}

#define DEF_FUNC_EXECUTEVOIDFUNC_NO_PARAM \
	bool VCall(const string& strFuncName) \
	{ \
		FUNCTION_BEGIN \
		call_function<void>(_pLuaState, strFuncName.c_str()); \
		FUNCTION_END \
	}

#define DEF_FUNC_EXECUTEVOIDFUNC(z, n, unused) \
	template<BOOST_PP_ENUM_PARAMS(n, typename P)> \
	bool VCall(const string& strFuncName BOOST_PP_ENUM_TRAILING(n, PRINT_EXECUTEFUNC_PARAM, none)) \
	{ \
		FUNCTION_BEGIN \
		call_function<void>(_pLuaState, strFuncName.c_str() BOOST_PP_ENUM_TRAILING_PARAMS(n, rP)); \
		FUNCTION_END \
	}

#define MAX_PARAM_COUNT 15
	BOOST_PP_REPEAT(MAX_PARAM_COUNT, DEF_FUNC_EXECUTEFUNC, none);
	BOOST_PP_REPEAT_FROM_TO(1, MAX_PARAM_COUNT, DEF_FUNC_EXECUTEVOIDFUNC, none);
	DEF_FUNC_EXECUTEVOIDFUNC_NO_PARAM;

protected:
	lua_State* _pLuaState;
	string _strFilePath;
	bool _bLoaded;
	bool _bLogOpen;
    UINT8 _byServerType;
	ELuaError _eLuaError;
};

typedef shared_ptr<CScript> CScriptPtr;
typedef weak_ptr<CScript> CScriptWtr;

