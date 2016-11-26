#ifndef A_H
#define A_H
#include<iostream>
using namespace std;

namespace CHEN
{
	void printA(int a)
	{
		cout<<"printA:"<<a<<endl;
	}
	
	void printAA(char *a);
	
	class A
	{
		int _a;
	};
}

#endif
