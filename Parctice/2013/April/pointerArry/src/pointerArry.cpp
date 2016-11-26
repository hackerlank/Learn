#include<iostream>
using namespace std;

const void printPtrArr(const char* const ptrArr[],size_t length)
{
	size_t index;
	for(index = 0;index < length;++index)
	{
		cout<<"the ptrArr[%d]:contant is :%s"<<index<<ptrArr[index]<<endl;
	}
}

void chgePtrArr(char* ptrArr[])
{
	char *p = ptrArr[3];
	cout<<"*p:"<<*p<<endl;
	++p;
	ptrArr[3] = p;
}

int main(void)
{
	char* ptrArr[5] = {"go","to","shang","hai","work"};
	
	printPtrArr(ptrArr,5);
	
	chgePtrArr(ptrArr);
	
	printPtrArr(ptrArr,5);
}



 
