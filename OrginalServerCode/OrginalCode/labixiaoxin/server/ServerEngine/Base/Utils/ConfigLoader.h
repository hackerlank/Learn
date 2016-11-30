#pragma once

#include "libxml\parser.h"

class ConfigLoader
{
public:
	ConfigLoader();
	virtual ~ConfigLoader();

	int load_config(int config_id, char *path);

	virtual int deal_config(int config_id, xmlNodePtr rootNode) = 0;
};