// stdafx.cpp : source file that includes just the standard includes
// Base.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
