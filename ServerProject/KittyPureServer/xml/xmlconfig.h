#ifndef __XML_CONFIG_H__
#define __XML_CONFIG_H__
#include <functional>
#include "info_collect_config.h"
#include "new_massive_config.h"
#include "new_user_init.h"
#include "redis_config.h"
#include "redis_config_local.h"
#include "test_config.h"
#include "xmltest.h"

namespace config
{
	typedef std::function<const Fir::XMLParser::Node *(Fir::XMLParser &, const char *)>	ReadXmlFunc;

	void init(const config::ReadXmlFunc &func);

	const info_collect_config_t &info_collect_config();
	const new_massive_config_t &new_massive_config();
	const new_user_init_t &new_user_init();
	const redis_config_t &redis_config();
	const redis_config_local_t &redis_config_local();
	const test_config_t &test_config();
	const xmltest_t &xmltest();
}

#endif

