#include "global.h"
#include "baseProperty.h"
#include "baseTime.h"

namespace Global
{
	volatile QWORD gameTime = 0;
	volatile WORD buildTime = 0;
	volatile WORD serverVersion = 0;

	Logger *logger = NULL;
	Property config;
	ValType VAR_NULL;
	
	static void initGlobal() __attribute__ ( ( constructor ) );
	void initGlobal()
	{
		config["threadPoolSize"] = "2048";
		config["maxClientSize"] = "50";
		config["serverIP"] = "127.0.0.1";
		config["port"] = "10000";
		config["ifname"] = "eth0";
		config["mysql"] = "mysql:://root:root@127.0.0.1:3306/school";
		config["LoggerLevel"] = "debug";
		Time::getLocalTZ();
	}

	static void finalGlobal() __attribute__ ( ( destructor ) );
	void finalGlobal()
	{
		DELETE( logger );
	}
	int getVerifyVersion()
	{
		if( ( DWORD )config["IgnoreVersion"] == 1 )
		{
			return 0;
		}
		return 1;
	//	return atoi( TITAN_VERSION );
	}
	bool isGM( const DWORD charID )
	{
		return charID <= 100;
	}
	int getGameTyper()
	{
		return 24;
	}

	int randBetween(int min,int max)
	{
		int grap = 0;
		if( min == max )
		{
			return min;
		}
		if( min > max )
		{
			grap = min - max;
			return max +  rand() % (grap + 1);
		}
		else
		{
			grap = max - min;
			return min + rand() % (grap + 1);
		}
	}

	char upper( char value )
	{
		if( value >= 'a' && value <= 'z' )
		{
			value -= ( 'a' - 'A' );
		}
		return value;
	}
	char lower( char value )
	{
		if( value >= 'A' && value <= 'Z' )
		{
			value +=  ( 'a' - 'A' );
		}
		return value;
	}

	void split( const std::string &str,std::vector<std::string> &strVec,const std::string splitStr )
	{
		std::string::size_type beginPos, findPos;
		beginPos = 0;
		findPos = str.find( splitStr,beginPos );
		while( findPos != string::npos )
		{
			std::string subStr = str.substr( beginPos,findPos - 1 );
			strVec.push_back( subStr );
			beginPos = findPos + splitStr.length();
			findPos = str.find( splitStr,beginPos );
		}
		return;
	}
			
}
