#include<iostream>
using namespace std;
class A
{
	public:
	int values;
	public:
	A():values(0)
	{
		cout<<"A()"<<endl;
	}
	A(int _values):values(_values)
	{
		cout<<"call A(int)"<<endl;
	}
	/*注意，这个必须是const，否则会有问题*/
	A(const A &a):values(-1)
	{
		cout<<"call A(A)"<<endl;
	}
	A& operator= (const A &a)
	{
		cout<<"call operator ="<<endl;
		return *this;
	}
};

A func(void)
{
	return A(3);
}

A operator+ (const A &a,const A &b)
{
	return A(3);
}

A doNoThing(A a)
{
	return a;
}


int main(void)
{
	func();
	
	A b,a(2),c(3),e;
	
	/*这个先调operator+，再凋一次有参数的构造函数，之后凋一次operator= */
	e = a + c;
	
	/*这个先调operator+，再凋一次有参数的构造函数,就没有了，很奇怪，跟上面对比看 */
	A d = a + c;
	
	
	/*这个参数先调一次拷贝构造函数作为参数,之后再凋一次好呗构造函数，作为返回值 */
	e = doNoThing(a);
	
	return 1;
}


