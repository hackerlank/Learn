#include<iostream>
using namespace std;
class A
{
	A(void)
	{
		cout<<"call A():"<<endl;
	}

	public:
	static A& creatA(void)
	{
		static A a;
		return a;
	}
};

int main(void)
{
	A a = A::creatA();
	A b = A::creatA();
	return 1;
}
	

