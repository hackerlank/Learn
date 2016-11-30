// SecuritySerailGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"

#define MAX_SECURITY_KEY_COUNT 80000

#define SECURITY_KEY_LENGTH 8
//#if _MEMORY_DEBUG
//#include "../GameBase/Common/debugnew.h"
//#define new new(__FILE__, __LINE__)
//#endif


void generate_key(char *dest)
{
	int i;
	int ret = 0;
	int t = 0;
	char c;

	for(i = 0;i < SECURITY_KEY_LENGTH;i ++)
	{
		t = rand() % (10 + 26);

		if(t < 10)
		{
			c = '0' + t;
		}
		else
		{
			t = t - 10;
			c = 'A' + t;
		}
		dest[i] = c;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	time_t _time_t;			//there is a differ srand(time());jinpan  D:\work\lexiyou\ref\ServerEngine_back_20140714\ServerEngine
	srand(time(&_time_t)); //这行没有

	char *list = new char[MAX_SECURITY_KEY_COUNT * SECURITY_KEY_LENGTH];

	int i;
	for(i = 0;i < MAX_SECURITY_KEY_COUNT;i ++)
	{
		generate_key(&list[i * SECURITY_KEY_LENGTH]);
	}

	FILE *fp;

	fp = fopen("security_key_list.bin", "wb");

	//fwrite(fp, list, MAX_SECURITY_KEY_COUNT * SECURITY_KEY_LENGTH, 1);
	fwrite(  list, MAX_SECURITY_KEY_COUNT * SECURITY_KEY_LENGTH, 1, fp);  //原来用的上一行
	
	fclose(fp);

	delete list;

	return 0;
}

