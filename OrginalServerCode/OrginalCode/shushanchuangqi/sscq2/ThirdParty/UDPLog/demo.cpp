
#include "kingnet_analyzer.h"

int demo()
{
	_analyzer.Init();
	const char* uid  = "abc111";
	CUserLogger* logger = _analyzer.GetInstance(uid);
	logger->SetUserIP("192.168.9.2");
	logger->SetUserMsg("user|msg|is|here");
	logger->LogMsg("11","22","33","44","55","66","props",3);

	logger = _analyzer.GetInstance(uid);

	_analyzer.DestoryInstance(uid);

	return 0;
}
