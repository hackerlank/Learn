
#include<iostream>
#include<stdio.h>
using namespace std;
class B
{	
	public:
		virtual void fun()
		{
			cout<<"call B:fun()"<<endl;
		}
	
};

class BB :public B
{	
};


int main(void)
{
	
	B *b = new BB;
	
	typedef void (*Fun)(void);	
	
	Fun fptr = (Fun)*((int*)*(int*)(b) + 0);	
	
	printf("&(B::fun):0x%x%\n",&(B::fun));
	
	printf("&fptr:0x%x\n",fptr);
	
	
	return 1;	
}
