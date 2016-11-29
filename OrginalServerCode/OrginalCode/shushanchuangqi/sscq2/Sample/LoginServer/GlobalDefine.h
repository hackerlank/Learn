#pragma once

#define LOGIN_SERVER

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#define DEF_SMART_POINTER(type, name) \
	type name; \
	typedef shared_ptr<name> name##Ptr; \
	typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(class, CClientObj);