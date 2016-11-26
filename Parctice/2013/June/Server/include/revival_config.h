#ifndef REVIVAL_CONFIG_H
#define REVIVAL_CONFIG_H
#include<string>
#include<vector>
using namespace std;


class Revival_Config
{
private:
		char mapId[50];
		char revivalMap[50];
		int ptx;
		int pty;
public:
		Revival_Config(char* _mapId,char* _revivalMap,int _ptx,int _pty);
		char* getMapId(void);
		char* getRevivalMap(void);
		int getPtx(void);
		int getPty(void);
};
#endif

