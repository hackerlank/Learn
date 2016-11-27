#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
using namespace std;

#include "baseLog.h"
#include "common/baseDef.h"

class Property;
class ValType;

namespace Global
{
	extern volatile QWORD gameTime;
	extern volatile WORD buildTime;
	extern volatile WORD serverVersion;
	extern Logger *logger;
	extern Property config;
	extern ValType VAR_NULL;

	int getVerifyVersion();
	bool isGM( const DWORD charID );
	int getGameType();

	int randBetween( int min,int max );
	char upper( char value );
	char lower( char value );
	void split( const std::string &str,std::vector<std::string> &strVec,const std::string splitStr );
};

#endif
	
