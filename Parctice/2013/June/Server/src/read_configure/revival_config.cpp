#include "revival_config.h"
#include <string.h>
using namespace std;

Revival_Config::Revival_Config(char* _mapId,char* _revivalMap,int _ptx,int _pty)
{
	
	// int len;
	// len = strlen(_mapId);
	// mapId = new char[len+1];
	strncpy(mapId,_mapId,sizeof(mapId));
	// mapId[len]='\0';
	
	// len = strlen(_revivalMap);
	// revivalMap = new char[len+1];
	strncpy(revivalMap,_revivalMap,sizeof(revivalMap));
	// revivalMap[len]='\0';
	
	ptx=_ptx;
	pty=_pty;
}

char* Revival_Config::getMapId(void)
{
	return mapId;
}

char* Revival_Config::getRevivalMap(void)
{
	return revivalMap;
}

int Revival_Config::getPtx(void)
{
	return ptx;
}

int Revival_Config::getPty(void)
{
	return pty;
}
