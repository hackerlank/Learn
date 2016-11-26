#include<iostream>
using namespace std;

template<typename T>
class A
{
	static size_t size;
	
	public:	
	inline static size_t getSize(void)
	{
		return size;
	}
	
	inline static void setSize(size_t newSize)
	{
		size = newSize;
	}
	
	inline static void printSize(void)
	{
		cout<<"size:"<<size<<endl;
	}
};

template<typename T> 
size_t A<T>::size = 2;

int main(void)
{
	A<int> a;
	a.setSize(4);
	a.printSize();
	
	A<char*> b;
	b.printSize();
	b.setSize(3);
	
	a.printSize();
	b.printSize();

	A<int> c;
	c.printSize();
	
	return 1;
}

 
