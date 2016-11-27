#include "baseProperty.h"
#include "global.h"

DWORD Property::parseCmdLine( const std::string &cmdLine )
{
	std::vector<std::string> cmdStrVec;
	Global::split( cmdLine,cmdStrVec," " );
	for( std::vector<std::string>::const_iterator iter = cmdStrVec.begin();iter != cmdStrVec.end();++iter )
	{
		std::vector<std::string> strVec;
		Global::split( *iter,strVec,"=" );
		if( strVec.size() == 2 )
		{
			propertyMap[strVec[0]] = strVec[1];
		}
	}
	return propertyMap.size();
}

DWORD Property::parseCmdLine( const char *cmdLine )
{
	std::vector<std::string> cmdStrVec;
	Global::split( cmdLine,cmdStrVec," " );
	for( std::vector<std::string>::const_iterator iter = cmdStrVec.begin();iter != cmdStrVec.end();++iter )
	{
		std::vector<std::string> strVec;
		Global::split( *iter,strVec,"=" );
		if( strVec.size() == 2 )
		{
			propertyMap[strVec[0]] = strVec[1];
		}
	}
	return propertyMap.size();
}

