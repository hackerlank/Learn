#include<iostream>
#pragma pack (4)
using namespace std;

class A
{
public:
	A():valuea(-1)
	{
	}
	virtual void af()
	{
		cout<<"A::f():"<<endl;
	}
	int valuea;
};
class D:virtual public A
{
	public:
	D():valued(-2)
	{
	}
	virtual void df()
	{
		cout<<"call df:"<<endl; 
	}
	int valued;
};



int main()
{

	D *d = new D();
	A *a = d;
	cout<<"&d:"<<d<<endl;
	cout<<"&a:"<<a<<endl;
	cout<<"&valuea:"<<&(a->valuea)<<endl;
	cout<<"&valued:"<<&(d->valued)<<endl;	
	cout<<"next segment:"<<endl;
	cout<<"sizeof(A):"<<sizeof(A)<<endl;
	cout<<"sizeof(D):"<<sizeof(D)<<endl;

	return 1;
}
