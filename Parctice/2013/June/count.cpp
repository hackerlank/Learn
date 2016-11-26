#include<iostream>
using namespace std;

size_t maxRowLen(const char *outPutChar,const char *inPutChar)
{
	if(!inPutChar)
	{
		outPutChar = NULL;
		return 0;
	}
	size_t resultLen ,len,lastSum;
	lastSum = resultLen = 0;
	len = 1;
	outPutChar = inPutChar;
	const char *beginPtr = inPutChar;
	const char *beforePtr = inPutChar;
	while(*++beginPtr != '\0')
	{
		++len;
		
		if(*beginPtr - *beforePtr != 1)
		{
			if(resultLen < len)
			{	
				resultLen = len;
				
				outPutChar = inPutChar + lastSum;
			}					
			
			lastSum += len;				
			
			beforePtr = beginPtr;
			
			len = 1;
		}
		
		beforePtr = beginPtr;
	}
	
	return resultLen;
}

int main()
{
	const char* inPutChar = "abcd123412345678abc";
	const char* outPutChar;
	
	size_t result = maxRowLen(outPutChar,inPutChar);
	
	cout<<"result:"<<result<<"  outPutChar:"<<outPutChar<<endl;
	
	return 1;
}
		