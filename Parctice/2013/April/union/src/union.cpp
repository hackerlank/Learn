#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

union testObj
{
	testObj *next;	
	char data_client[1];	
//	char data_client[0];
};
int main(void)
{
	char *a = (char*)malloc(16);
	
	memset(a,'\0',16);
	
	cout<<"testObj size:"<<sizeof(testObj)<<endl;
	
	strncpy(a,"1,2,3,4,5,6,7,8",15);
	
	testObj *myObj1 = (testObj*)a;
	
//	cout<<"data_client:"<<myObj1->data_client<<endl;	
	
	/*此处就相当于把a全都给free掉聊*/
//	free(myObj1); 
	
//	cout<<"after free myObj1 a:"<<a<<endl;
	
	testObj *myObj2 = (testObj*)(a + 3);
	cout<<"data_client:"<<myObj2->data_client<<endl;
	
	free(myObj2); 
	myObj2 = NULL;	
	a[2] = '\0';
//	memset(a,'\0',3);
//	strncpy(a,"go",2);
	
	cout<<"after free myObj2 a:"<<a<<endl;
	
	return 1;
	 
}









 
