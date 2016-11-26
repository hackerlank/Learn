#include<iostream>
using namespace std;

class A
{
};

class AA:public A
{
	int a;
};

class AAA
{
	A a;
	int b;
};
enum Tree_color{red = false,black = true};
int main()
{
	cout<<"A:"<<sizeof(A)<<" AA:"<<sizeof(AA)<<"AAA:"<<sizeof(AAA)<<endl;
	cout<<"Tree_color:"<<sizeof(Tree_color)<<endl;
	return 1;
}
