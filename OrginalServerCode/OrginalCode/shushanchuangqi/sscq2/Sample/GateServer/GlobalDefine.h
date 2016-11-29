#pragma once

#define GATE_SERVER

#ifdef _DEBUG
#define KEEP_ALIVE_MAX_STALE_COUNT 100000
#else
#define KEEP_ALIVE_MAX_STALE_COUNT 10
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#define DEF_SMART_POINTER(type, name) \
	type name; \
	typedef shared_ptr<name> name##Ptr; \
	typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(class, CClientObj);
