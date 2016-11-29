#include "stdafx.h" 
#include "RequestHandler.h"
#include "Script/GameScript.h"

int main(int argc, char* argv[])
{
	if(!Config.Init())
	{
		LOG_CRI << "CConfig::Init fails!";
		LOG_OBJ.Flush();
		return -1;
	}

	CRequestHandler::ProcessRequest(Config);
	Config.UnInit();
	return 0;
}
