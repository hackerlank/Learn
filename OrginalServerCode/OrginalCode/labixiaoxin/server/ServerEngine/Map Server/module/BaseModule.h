#pragma once

#include "ace\ace.h"
#include "ace\OS_NS_string.h"
#include "..\..\GameBase\Common\GameDefine.h"
#include "..\..\GameBase\Protocol\ControlProtocol.h"
#include "..\..\GameBase\Protocol\DBProtocol.h"

class Map;

class BaseModule
{
public:
	BaseModule();
	~BaseModule();

	void set_map(Map *map);

	virtual void update(ACE_UINT32 unCurrentTime){};
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN){};

protected:
	Map *m_map;
};