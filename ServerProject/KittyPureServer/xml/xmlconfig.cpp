#include "xmlconfig.h"

namespace config
{
	info_collect_config_t _info_collect_config;
	new_massive_config_t _new_massive_config;
	new_user_init_t _new_user_init;
	redis_config_t _redis_config;
	redis_config_local_t _redis_config_local;
	test_config_t _test_config;
	xmltest_t _xmltest;

	void init(const config::ReadXmlFunc &func)
	{
		Fir::XMLParser xml;
		_info_collect_config.load(xml, func(xml, "info_collect_config.xml"));
		_new_massive_config.load(xml, func(xml, "new_massive_config.xml"));
		_new_user_init.load(xml, func(xml, "new_user_init.xml"));
		_redis_config.load(xml, func(xml, "redis_config.xml"));
		_redis_config_local.load(xml, func(xml, "redis_config_local.xml"));
		_test_config.load(xml, func(xml, "test_config.xml"));
		_xmltest.load(xml, func(xml, "xmltest.xml"));
	}

	const info_collect_config_t &info_collect_config()
	{
		return _info_collect_config;
	}
	const new_massive_config_t &new_massive_config()
	{
		return _new_massive_config;
	}
	const new_user_init_t &new_user_init()
	{
		return _new_user_init;
	}
	const redis_config_t &redis_config()
	{
		return _redis_config;
	}
	const redis_config_local_t &redis_config_local()
	{
		return _redis_config_local;
	}
	const test_config_t &test_config()
	{
		return _test_config;
	}
	const xmltest_t &xmltest()
	{
		return _xmltest;
	}
}

