#include<iostream>
#include<list>
using namespace std;
class A
{
public:
	A()
	{
		cout<<"call A::():"<<endl;
		return;
	}
	
	virtual void fo()
	{
		cout<<"call A::fo():"<<endl;
	}
	
	void go()
	{
		cout<<"call A::go():"<<endl;
	}
};

class AA:public A
{
public:
	AA()
	{
		cout<<"call AA::():"<<endl;
		fo();
		return;
	}
	
	virtual void fo()
	{
		cout<<"call AA::fo():"<<endl;
	}
	
	void go()
	{
		cout<<"call AA::go():"<<endl;
	}
};

class AAA:public AA
{
public:	
	virtual void fo()
	{
		cout<<"call AAA::fo():"<<endl;
	}
	
	void go()
	{
		cout<<"call AAA::go():"<<endl;
	}
};


	
int main(void)
{
	AAA aaa;
	A* p = &aaa;
	p->fo();
	p->go();
	
	
	/*注意，这里是强转，而非多态*/
	AA aa = (AA)aaa;
	
	aa.fo();
	aa.go(); //注意，这里是掉AA::go(),
	
	list<int> myList;
	for(int i = 0;i<10; ++i)
	{
		myList.push_back(i);
	}
	
	list<int>::iterator it;
	for(it = myList.begin();it != myList.end();)
	{
		if(*it == 3 || *it == 6)
		{
			it = myList.erase(it);
//			cout<<"*it:"<<*it<<endl;
		}
		else
		{
			cout<<"*it:"<<*it<<endl;
			++it;
		}
	}	

	cout<<"sizeof(unsigned int:)"<<sizeof(unsigned int)<<endl;	
	cout<<"sizeof(unsigned char:)"<<sizeof(unsigned char)<<endl;	
	cout<<"sizeof(double:)"<<sizeof(double)<<endl;	
	return 1;
}
