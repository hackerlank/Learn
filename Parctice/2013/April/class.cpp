#include<iostream>
using namespace std;
class A
{
};
class AA:public A
{
};

void func(const A& a)
{
	cout<<"go here:"<<endl;
}

int main(void)
{
	AA b;
	func(b);
	const int *p;
	int a = 3,d = 4;
	p = &a;
	p = &b;
	return 1;
}
