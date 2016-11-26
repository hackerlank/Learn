/************************************************************
	文件名：numStr.cpp
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#include"numStr.h"
#include"asistFun.h"

/*--辅助函数*/
void NumStr::reduceOne(void)
{
	if(strData.empty())
	{
		cout<<"NumStr::reduceOne error the strData is empty"<<endl;
		dealErrorFun(ERROR_EMPTY);
	}
		
	if(strData[0] == '0')
	{
		cout<<"NumStr::reduceOne error the strData is zero"<<endl;
		dealErrorFun(ERROR_OTHRE);
	}
	
	int len = strData.size() - 1;
	
	while(len >= 0)
	{
		if(strData[len] > '0')
		{
			strData[len] -= 1;
			break;
		}		
		strData[len] += scale - 1;
		--len;
	}
	
	if(strData[0] == '0')
	{
		strData.erase(strData.begin());
	}
}

/*--重载函数*/
NumStr& NumStr::operator--(void)
{
	reduceOne();
	return *this;
}

/*测试打印函数*/			
void NumStr::printData(void)
{
	cout<<"the strData:"<<strData<<endl;
}

/*重载 += 函数*/
NumStr& NumStr::operator+= (const NumStr &numStrF)
{
	string result;
	if(numStrF.empty() || strData.empty())
	{
		cout<<"NumStr::operator+= the argument is error empty:"<<endl;
		dealErrorFun(ERROR_EMPTY);
	}
	
	int lenF,lenS;
	size_t lastNumSum;
	bool isEnterHead = false;
	
	lenF = numStrF.size() - 1;
	lenS = strData.size() - 1;	

	
	for(;lenF >= 0 && lenS >= 0; --lenF,--lenS)
	{
		lastNumSum = numStrF.strData[lenF] - '0' + strData[lenS] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenF >= 0; --lenF)
	{
		lastNumSum = numStrF.strData[lenF] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenS >= 0; --lenS)
	{
	
		lastNumSum = strData[lenS] - '0';
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	if(isEnterHead)
	{
		result.insert(result.begin(),'0' + 1);
	}
	
	fillNewData(result);
	
	return *this;
}






	
		
	


