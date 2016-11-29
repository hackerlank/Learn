#pragma once

#ifdef _WIN32
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#endif // _WIN32

//include from CRT
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

//include from STL
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>

using namespace std;
namespace std {	using namespace placeholders; }

#ifdef _WIN32
#pragma warning(disable:4150)
#endif

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4005)
#endif

//include from boost
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef _WIN32
#pragma warning(pop)
#endif

#ifndef MYSQLPP_NO_DLL
#define MYSQLPP_NO_DLL
#endif
#ifndef MYSQLPP_EXPORT
#define MYSQLPP_EXPORT
#endif
//include from MySQL++
#include <mysql++.h>

//include from Utility
#include "ObjPool.h"
#include "Archive.h"
#include "UtilFunc.h"

//Basic include

#ifndef GAME_CONFIG_H
#include "GameConfig.h"
#endif

#include "GlobalDefine.h"

