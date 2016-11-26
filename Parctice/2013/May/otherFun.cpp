#include<iostream>
using namespace std;

void reverseChar(char *first,char *last)
{
	while((first != last) && (first != --last))
	{
		char temp = *first;
		*first = *last;
		*last = temp;
		++first;
	}
}

char* iToA(char buffer[],int values)
{
	char *ptr = buffer;	
	char *rtr = ptr;
	int _values = values;
	while(_values)
	{
		*ptr = '0' + _values % 10;
		_values /= 10;
		++ptr;
	}
	if(values < 0)
	{
		*ptr = '-';
		++ptr;
	}
	*ptr = '\0';

//	std::reverse(buffer,ptr);

	reverseChar(buffer,ptr);
	
	return rtr;
}
class A
{
	protected:
	void print()
	{
		cout<<"call the protected A:"<<endl;
	}
};


int main()
{
	char buff[10];
	char *ptr = iToA(buff,-10);
	cout<<"ptr:"<<ptr<<endl;
	cout<<"last:"<<15%-10<<endl;
//	A a;
//	a.print();
	return 1;
}
