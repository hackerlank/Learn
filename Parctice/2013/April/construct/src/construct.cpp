#include<iostream>
#include"string.h"
#include<string>
#include"stdlib.h"
#include<vector>
#include<memory>
using namespace std;

struct AA
{
	int b;
	AA(int _value):b(_value)
	{
		cout<<"call the construct:"<<endl;
	}


	AA(AA &aa)
	{
		b = -1;
		cout<<"call AA& aa:"<<endl;
	}
	
	/*这里很重要，小心,自己不写，系统会给默认的，就像构造函数一样*/
	AA operator=(AA &aa)
	{
		b += aa.b;
		AA test(b);
		cout<<"call the =:"<<endl;
		return test;
	}
	AA operator+(AA& aa)
	{
		AA result(aa.b + b);
		return result;
	}
	~AA(void)
	{
		cout<<"call the ~AA:"<<endl;
	}
			
};

AA operator=(AA& a,AA& b)
{
	AA result(a.b + b.b);
	return result;
}

	
int main()
{
	AA a(10);
	AA b(-3);
	AA c = a + b;	
	return 1;
}
