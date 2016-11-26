#include<iostream>
using namespace std;
class A
{
	const int values;
	
public:
	A(int _values):values(_values)
	{
		cout<<"values:"<<values<<endl;
	}
	A(const A &_a):values(10)
	{
		cout<<"call A(const A &):"<<endl;
	}
};
A func(A &a)
{
	A b(a);
	return b;
//	return A(a);
}
int main(void)
{
	A a(10);
	A b = func(a);
	return 1;
}



