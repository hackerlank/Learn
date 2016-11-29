/********************************************************************
//	Game Server Source File.
//	File name:	Script.cpp
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

#include "Script.h"
#include "SvrLib/ServerDefine.h"

ELuaError LuaError_CallBack(lua_State* pLuaState, bool bOpenLog /*= true*/)
{
	ELuaError eLuaError = eLuaErrOther;
	lua_Debug d;
	memset(&d, 0, sizeof(lua_Debug));
	lua_getstack(pLuaState, 0, &d);
	lua_getinfo(pLuaState, "Sln", &d);
	const char* pszError = lua_tostring(pLuaState, -1);
	lua_pop(pLuaState, 1);
	std::string msg;
	msg = d.short_src;
	msg += ":";
	char szBuf[512];
	sprintf(szBuf, "%d", d.currentline);
	msg += szBuf;

	if(d.name != NULL && strlen(d.name) != 0)
	{
		msg += "(";
		msg += d.namewhat;
		msg += " ";
		msg += d.name;
		msg += ")";
	}

	msg += " ";
	if(pszError != NULL)
	{
		if(strcmp("attempt to call a nil value", pszError) == 0)
			eLuaError = eLuaErrCallNil;
		msg += pszError;
	}
	lua_pushstring(pLuaState, msg.c_str());
	if(bOpenLog)
		LOG_CRI << msg;

    fprintf(stderr, "%s\n", msg.c_str());
	return eLuaError;
}

CScript::CScript() : _bLoaded(false), _bLogOpen(true), _byServerType((UINT8)eHostNone), _eLuaError(eLuaErrNone)
{
	_pLuaState = lua_open();
	luaL_openlibs(_pLuaState);
	open(_pLuaState);
}

CScript::~CScript()
{
	lua_gc(_pLuaState, LUA_GCCOLLECT, 0);
	lua_close(_pLuaState);
}

bool CScript::HasFunction(const string& strName)
{
	luabind::object obj = luabind::globals(_pLuaState)[strName];
	if(luabind::type(obj) == LUA_TFUNCTION)
		return true;
	return false;
}

bool CScript::LoadLuaFile(const string& strFile)
{
	if(luaL_dofile(_pLuaState, strFile.c_str()))
	{
		LuaError_CallBack(_pLuaState);
		return false;
	}

	_strFilePath = strFile;
	_bLoaded = true;
	return _bLoaded;
}

bool CScript::LoadMainFile(const string& strFile, int server, int flag)
{
    if (IsLoaded())
        return false;
    Register();
    if (!LoadLuaFile(strFile))
        return false;
    _byServerType = server;
    return Init(server, flag);
}

bool CScript::Init(int server, int flag)
{
    bool ret = false;
    if (HasFunction("Init"))
    {
        if (!Call("Init", ret, server, flag))
            return false;
        if (!ret)
            return false;
        return true;
    }
    return false;
}

bool CScript::Reload(int flag)
{
    if (!IsLoaded())
        return false;
    if (!LoadLuaFile(_strFilePath))
        return false;
    return Init(_byServerType, flag);
}

bool CScript::IsDebug()
{
#ifdef _DEBUG
    return true;
#else
    return false;
#endif
}

UINT32 CScript::GetVersion()
{
#ifdef _VERSION
    return _VERSION;
#else
    return "201401010000";
#endif
}

static int tostring_s64(lua_State *L)
{
    char temp[64];
    sprintf(temp, "%"  I64_FMT  "d", *(INT64*)lua_topointer(L, 1));
    lua_pushstring(L, temp);
    return 1;
}

static int eq_s64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(long long)) == 0);
    return 1;
}

static int lt_s64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(long long)) < 0);
    return 1;
}

static int le_s64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(long long)) <= 0);
    return 1;
}

static void init_s64(lua_State *L)
{
    const char* name = "__s64";
    lua_pushstring(L, name);
    lua_newtable(L);

    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, -3);

    lua_pushstring(L, "__tostring");
    lua_pushcclosure(L, tostring_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__eq");
    lua_pushcclosure(L, eq_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__lt");
    lua_pushcclosure(L, lt_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__le");
    lua_pushcclosure(L, le_s64, 0);
    lua_rawset(L, -3);

    lua_settable(L, LUA_GLOBALSINDEX);
}

static int tostring_u64(lua_State *L)
{
    char temp[64];
    sprintf(temp, "%"  I64_FMT  "u", *(UINT64*)lua_topointer(L, 1));
    lua_pushstring(L, temp);
    return 1;
}

static int eq_u64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(unsigned long long)) == 0);
    return 1;
}

static int lt_u64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(unsigned long long)) < 0);
    return 1;
}

static int le_u64(lua_State *L)
{
    lua_pushboolean(L, memcmp(lua_topointer(L, 1), lua_topointer(L, 2), sizeof(unsigned long long)) <= 0);
    return 1;
}

static void init_u64(lua_State *L)
{
    const char* name = "__u64";
    lua_pushstring(L, name);
    lua_newtable(L);

    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, -3);

    lua_pushstring(L, "__tostring");
    lua_pushcclosure(L, tostring_u64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__eq");
    lua_pushcclosure(L, eq_u64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__lt");
    lua_pushcclosure(L, lt_u64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__le");
    lua_pushcclosure(L, le_u64, 0);
    lua_rawset(L, -3);

    lua_settable(L, LUA_GLOBALSINDEX);
}

void CScript::SetGlobals()
{
}

bool CScript::Register()
{
    init_s64(GetState());
    init_u64(GetState());
    SetGlobals();

	try
	{
		module(GetState())
        [
            class_<CScript>("Script") // XXX: 如果参数传递的时候或者在Lua里需要用到的类必须注册
                .def("IsDebug", &CScript::IsDebug)
                .def("GetVersion", &CScript::GetVersion)
                .def("Version", &CScript::GetVersion)
        ];
        Set("Script", boost::ref(*this)); // XXX: 对象传值必须使用boost::ref

        module(GetState())
        [
            class_<CLog>("Log")
                .enum_("ELogLevel")
                [
                    value("ELLCRI", eLogLevelCritical),
                    value("ELLWRN", eLogLevelWarning),
                    value("ELLINF", eLogLevelInfo),
                    value("ELLDBG", eLogLevelDebug),
                    value("ELLDMY", eLogLevelDummy),
                    value("ELLMAX", eLogLevelCount)
                ]
                .def("PushLogL", &CLog::PushLogL)
        ];
        Set("LOG_OBJ", boost::ref(LOG_OBJ));

		return true;
    }
	catch(...)
	{
		LuaError_CallBack(_pLuaState);
	}

    return false;
}

