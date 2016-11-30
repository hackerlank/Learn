#include "IDMap.h"

IDMap::IDMap()
{

}

IDMap::~IDMap()
{
	m_map.unbind_all();
}

void IDMap::add(ACE_UINT32 unID)
{
	m_map.bind(unID, NULL);
}

void IDMap::remove(ACE_UINT32 unID)
{
	m_map.unbind(unID);
}

bool IDMap::is_exist(ACE_UINT32 unID)
{
	if(m_map.find(unID) == 0)
	{
		return true;
	}

	return false;
}