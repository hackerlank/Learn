#include "base/global.h"
#include "PlateServer.h"

void initGlobalVal()
{
	Global::config["mysql"] = "mysql://root:root@127.0.0.1:3306/plate";
	Global::config["logfilename"] = "/home/flyer/flyer/SchoolProgress/trunk/School/log/plateserver.log";
	Global::config["threadPoolCapacity"] = 512;
	Global::config["ifname"] = "eth0";
	Global::config["daemon"] = "true";
}

int main()
{
	initGlobalVal();	
	Global::logger = new Logger("PL");
	Global::logger->setLevel((const char*)Global::config["LoggerLevel"]);
	if(strlen(Global::config["logfilename"]))
	{
		Global::logger->setFile((const char*)Global::config["logfilename"]);
	}
	if(strcmp("true",Global::config["daemon"]) == 0)
	{
		Global::logger->info("PlateServer will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1, 1);
	}

	PlateServer::newInstance<PlateServer>();
	PlateServer::getInstance().loop();
	return EXIT_SUCCESS;
}
