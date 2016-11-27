#include<iostream>
#include<unistd.h>
using namespace std;

int main(void)
{
	pid_t pid,ppid;
	pid = getpid();
	ppid = getppid();
	cout<<"pid:"<<pid<<"  ppid:"<<ppid<<endl;
	while(true)
	{
	}
	return 1;
}
