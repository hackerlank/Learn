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
#include <limits>

//include from STL
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

#ifdef _WIN32
#pragma warning(disable:4150)
#endif

#ifndef MYSQLPP_NO_DLL
#define MYSQLPP_NO_DLL
#endif
#ifndef MYSQLPP_EXPORT
#define MYSQLPP_EXPORT
#endif
//include from MySQL++
#include <mysql++.h>

//include from Network
#include "Interface.h"

//include from SvrLib
#include "ServerDefine.h"
#include "GateHandler.h"
#include "SvrHandler.h"
#include "SessionMgr.h"
#include "UsrSessMgr.h"
#include "ServerID.h"
#include "GUIDMgr.h"

//include from Utility
#include "ObjPool.h"
#include "Thread.h"
#include "Lock.h"
#include "Directory.h"
#include "UtilFunc.h"
#include "Encode.h"

//Basic include
#include "DBConfig.h"
#include "GlobalDefine.h"
#include "DBNetMgr.h"
#include "AllTimers.h"
#include "Protocols.h"

//DB logic include
#include "DBEvent.h"
#include "DBMgr.h"
