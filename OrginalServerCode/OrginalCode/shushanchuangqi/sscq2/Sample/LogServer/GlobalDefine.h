#pragma once

#define LOG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#ifdef _WIN32
#pragma warning(disable:4150)
#endif

#define DEF_SMART_POINTER(type, name) \
	type name; \
	typedef shared_ptr<name> name##Ptr; \
	typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(class, IDBEvt);
DEF_SMART_POINTER(class, CQueryDBEvt);
