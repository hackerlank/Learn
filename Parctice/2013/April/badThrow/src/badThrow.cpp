
#if 0
	#include<new.h>	
	#define _THWOW_BAD_ALLOC thorw bad_alloc
#elif !defined(_THOWD_BAD_ALLOC)
	#include<iostream>
	#include<stdlib.h>
	#define _THROW_BAD_ALLOC cerr<<"out of memory"<<endl;exit(1)
#endif
	

using namespace std;

int main(void)
{
	int a = 0;
	
	if(a == 0)
	{
		_THROW_BAD_ALLOC;
	}
	
	return 1;
}

 
