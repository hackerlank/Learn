#include<iostream>
using namespace std;
class AA
{
	public:
	int a;
	public:
	AA(int _a):a(_a)
	{
	}
};
class A
{
	AA a;
	public:
	A(int _a):a(_a)
	{
	}
	operator AA() const
	{
		cout<<"call operator():"<<endl;
		return a;
	}
};


int main(void)
{
	A a(10);
	AA b = a;
	cout<<"b:"<<b.a<<endl;
	return 1;
}
