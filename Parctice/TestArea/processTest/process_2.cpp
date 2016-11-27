#include<iostream>
#include<unistd.h>
using namespace std;

int main(void)
{

	cout<<"process begin:"<<"pid:"<<getpid()<<"  ppid:"<<getppid()<<endl;

	pid_t child = fork();
	if(child == -1)
	{
		cout<<" error:"<<endl;
		exit(1);
	}
	else if(child == 0)
	{
		
		cout<<"process begin child :"<<"pid:"<<getpid()<<"  ppid:"<<getppid()<<"  child:"<<child<<endl;
	}
	else
	{
		
		cout<<"process begin child father :"<<"pid:"<<getpid()<<"  ppid:"<<getppid()<<"  child:"<<child<<endl;	  }

	
	cout<<"process end :"<<"pid:"<<getpid()<<"  ppid:"<<getppid()<<"  child:"<<child<<endl;
	return 1;
}
