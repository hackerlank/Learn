#include<iostream>
#include<unistd.h>
using namespace std;

int main(void)
{
	while(true)
		fork();
	return 1;
}
