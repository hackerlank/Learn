#include "base/global.h"
#include "SuperServer.h"

void initGlobalVal()
{
	Global::config["mysql"] = "mysql://root:root@127.0.0.1:3306/flyer";
	Global::config["logfilename"] = "/home/flyer/flyer/SchoolProgress/trunk/School/log/superserver.log";
	Global::config["loginServerList"] = "loginServerList.xml";
	Global::config["threadPoolCapacity"] = 512;
	Global::config["ifname"] = "eth0";
	Global::config["daemon"] = "true";

	Global::config["plateip"] = "127.0.0.1";
	Global::config["plateport"] = "3000";
	Global::config["plateid"] = "3000";
}

int main()
{
	initGlobalVal();	
	Global::logger = new Logger("SU");
	Global::logger->setLevel((const char*)Global::config["LoggerLevel"]);
	if(strlen(Global::config["logfilename"]))
	{
		Global::logger->setFile((const char*)Global::config["logfilename"]);
	}
	if(strcmp("true",Global::config["daemon"]) == 0)
	{
		Global::logger->info("SuperServer will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1, 1);
	}
	SuperServer::newInstance<SuperServer>();
	SuperServer::getInstance().loop();
	return EXIT_SUCCESS;
}
