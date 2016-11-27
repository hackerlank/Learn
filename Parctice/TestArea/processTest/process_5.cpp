#include<iostream>
#include<unistd.h>
using namespace std;

int gobal = 0;
int main(void)
{
	int heap = 1;
	int *mall = (int *)malloc(sizeof(int));
	*mall = 2;
	pid_t child = vfork();
	if(child == -1)
	{
		cout<<"error:"<<endl;
		exit(1);
	}
	else if(child == 0)
	{
		++gobal;
		++heap;
		++*mall;
		cout<<"child process:"<< "gobal:"<<gobal<<" heap:"<<heap<<" mall:"<<*mall<<endl;
//		return 1;
	//	exit(0);
	}
//	cout<<"father process:"<< "gobal:"<<gobal<<" heap:"<<heap<<" mall:"<<*mall<<endl;
	exit(1);
	return 0;
}
