
#include<iostream>
#include<stdio.h>
using namespace std;

class A
{	
	public:
		virtual void fun(int values = 1)
		{
			cout<<"call A:fun()"<<endl;
		}
	private :
		virtual void func(int values = 1)
		{
			cout<<"call A:func()"<<endl;
		}
	
};

class AA:public A
{
	private:
		virtual void fun(int values = 2)
		{
			cout<<"call AA:fun()"<<endl;
		}		
};	

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
	A *a = new AA;
	
	/*调用的是AA里面的,但是参数却是A的，虚函数的弊端*/
	a->fun();
	
	B *b = new BB;
	
	typedef void (*Fun)(void);

	
	Fun fptr = (Fun)*((int*)*(int*)(b) + 0);
	
//	printf("&(B::fun):0x%x",&(B::fun));
	printf("&fptr:0x%x\n",fptr);
	
	fptr();	
	
	
	return 1;	
}
