#include<iostream>
using namespace std;

class NEW
{	
	
	public:
	static void (*hander)(char *warningMsg);
	
	static void oom(char *warnMsg);
	
	static void chage(void (*_hander)(char *warningMsg));
};

void NEW::oom(char *warnMsg)
{
	cout<<"call the NEW::oom"<<endl;
	if(hander != 0)
	{
		(*hander)(warnMsg);
		
	}
}

//void(*fun)(char *warnMsg) NEW::hander = 0;
void(* NEW::hander)(char *warinMsg) = NULL;

void NEW::chage(void (*_hander)(char *warningMsg))
{
	if(_hander != 0)
	{
		hander = _hander;
	}
	
	cout<<"call the NEW::chage"<<endl;
}

void func(char *warningMsg)
{
	cout<<"warningMsg:"<<warningMsg<<endl;
}

int main(void)
{
	NEW::chage(&func);
	
	char * p = NULL;
	
	if(p == 0)
	{
		NEW::oom("p is NULL");
	}
	
	return 1;
}
