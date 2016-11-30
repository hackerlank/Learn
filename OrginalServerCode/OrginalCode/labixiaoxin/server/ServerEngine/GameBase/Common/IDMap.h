#pragma once

#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, ACE_UINT32 *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> RES_ID_MAP;
typedef RES_ID_MAP::ITERATOR RES_ID_MAP_ITERATOR;

class IDMap
{
public:
	IDMap();
	~IDMap();

	void add(ACE_UINT32 unID);
	void remove(ACE_UINT32 unID);
	bool is_exist(ACE_UINT32 unID);

	RES_ID_MAP m_map;
};