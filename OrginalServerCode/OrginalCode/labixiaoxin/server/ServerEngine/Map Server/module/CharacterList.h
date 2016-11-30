#pragma once

#include "ace\ace.h"
#include "..\..\GameBase\Common\GameDefine.h"

class CharacterList
{
public:
	CharacterList();
	~CharacterList();

	virtual void init_size(int capcity);
	virtual void init(ACE_UINT32 unCount, void *list);

	ACE_UINT32 m_unCount;
	CharacterInfoExt *m_list;
protected:
	int m_capcity;
};