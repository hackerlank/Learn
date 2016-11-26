#include<iostream>
using namespace std;
class A
{
	public:
	
	void Fun()
	{
		asist();
	}
	private:
	
	virtual void asist()
	{
		cout<<"call A asist:"<<endl;
	}
};

class B : public A
{
	virtual void asist()
	{
		cout<<"call B asist()"<<endl;
	}
};

using namespace std;
int main()
{
	B b;
	b.Fun();
	return 1;
}

