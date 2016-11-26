#include<iostream>
using namespace std;
class Base
{
	int values;
	public:
	Base(void)
	{
	}
	void f(void)
	{
		cout<<"call Base:f:"<<endl;
	}
	void f(int)
	{
		cout<<"call Base:f(int):"<<endl;
	}
};

class Father:public Base
{
	public:
	Father(void):Base()
	{
	}
	using Base::f;
	void f(void)
	{
		cout<<"call Father:f(void):"<<endl;
	}
};

int main(void)
{
	Father father;
	father.f(6);
	father.Base::f();
	return 1;
}
