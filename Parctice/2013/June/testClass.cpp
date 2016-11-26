#include<iostream>
using namespace std;

class A
{
public:
	virtual void af()
	{
		cout<<"A::f():"<<endl;
	}
	int valuea;
};
class D:virtual public A
{
	public:
	virtual void df()
	{
		cout<<"call df:"<<endl; 
	}
	int valued;
};

class E:virtual public A
{
	public:
	virtual void ef()
	{
		cout<<"call ef:"<<endl;
	}
	int valuee;
};

class F:public D,public E
{
	public:
	virtual void ff()
	{
		cout<<"call ff:"<<endl;
	}
	int valuef;
};

int main()
{

	F *ff = new F();
	
	D *d = ff;
	
	cout<<"&ff:"<<ff<<endl;
	cout<<"&d:"<<d<<endl;
	cout<<"&valued:"<<&(d->valued)<<endl;
	cout<<"&valuea:"<<&(d->valuea)<<endl;
	cout<<"next segement:"<<endl;	
	E *e = ff;
	cout<<"&ff:"<<ff<<endl;
	cout<<"&e:"<<e<<endl;
	cout<<"&valuee:"<<&(e->valuee)<<endl;
	cout<<"&valuea:"<<&(e->valuea)<<endl;
	cout<<"thrid segment:"<<endl;
	cout<<"&valuef:"<<&(ff->valuef)<<endl;
	
	cout<<"sizeof(f):"<<sizeof(F)<<endl;
	return 1;
}
