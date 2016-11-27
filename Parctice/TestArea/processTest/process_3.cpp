#include<iostream>
#include<unistd.h>
using namespace std;

int gobal = 0;
int main(void)
{
	pid_t child;
	int heap = 1;
	int *mallInt = (int *)malloc(sizeof(int));
	*mallInt = 2;
	child = fork();
	if(child == -1)
	{
		cout<<"error:"<<endl;
		exit(1);
	}
	else if(child == 0)
	{
		++gobal;
		++heap;
		++*mallInt;
		cout<<"child process:"<<"gobal :"<<gobal<<" heap:"<<heap<<"mallInt:"<<*mallInt<<endl;
	}
	else
	{
		cout<<"father process:"<<"gobal :"<<gobal<<" heap:"<<heap<<" mallInt:"<<*mallInt<<endl;
	}

	return 1;
}


