#include<iostream>
#define BASE 8
using namespace std;

size_t roundUp(size_t bytes)
{
//	return (bytes + BASE - 1) & ~(BASE - 1);
	return (bytes + BASE - 1) & ~(BASE - 1);
}

int main(void)
{
	int a = -16;
	cout<<"size_t:"<<size_t(a)<<endl;	
	cout<<"result :"<<roundUp(a)<<endl;
	
	return 1;
}

 
