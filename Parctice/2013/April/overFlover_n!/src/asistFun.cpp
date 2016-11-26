/************************************************************
	文件名：asistFun.cpp
	文件作用：辅助函数
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#include"asistFun.h"

/*重载乘号*/
const NumStr operator* (const NumStr &numStrF,const NumStr &numStrS)
{
	NumStr resultNumStr;
	string result;
	if(numStrF.empty() || numStrS.empty())
	{
		cout<<"operator* the argument is empty:"<<endl;
		errorDealFun(ERROR_EMPTY);
		return NumStr();
	}	

	int lenF,lenS;
	size_t lastNumF,lastNumS,lastNumSum;
	int  isEnterHead = 0;
	
	lenF = numStrF.size() - 1;
	lenS = numStrS.size() - 1;
	
	for(;lenF >= 0; --lenF)
	{
		size_t _lenS_ = lenF;

		while(_lenS_ < numStrF.size() - 1)
		{
			result.insert(result.begin(),'0');
			++_lenS_;
		}
			
		lastNumF = numStrF.strData[lenF] - '0';
		
		for(int _lenS = lenS;_lenS >= 0; --_lenS)
		{			
			lastNumS = numStrS.strData[_lenS] - '0';
			
			lastNumSum = lastNumF * lastNumS;
			
			
			lastNumSum += isEnterHead;
			isEnterHead = lastNumSum / 10;	

			result.insert(result.begin(),'0' + lastNumSum % 10);
		}
		
		if(isEnterHead != 0)
		{
			result.insert(result.begin(),'0' + isEnterHead);
			isEnterHead = 0;
		}
		resultNumStr += NumStr (result);
		
		result.clear();
	}

	if(resultNumStr.strData[0] == '0')
	{
		resultNumStr.strData.erase(resultNumStr.strData.begin());
	}

	return resultNumStr;
}

/*重载小于号*/
bool operator < (const NumStr &numStrL,const NumStr &numStrR)
{
	size_t lenR,lenL;
	
	if(numStrL.empty())
	{
		return numStrR.empty() ? false :true;
	}
	
	if(numStrR.empty())
	{
		return false;
	}	
	
	lenR = numStrR.size();
	lenL = numStrL.size();	
	
	if(lenL != lenR)
	{
		return lenL < lenR;
	}	
	
	for(int index = 0;index < lenR;++index)
	{
		if(numStrL.strData[index] != numStrR.strData[index])
		{
			return numStrL.strData[index] < numStrR.strData[index];
		}
		
	}	
	return false;
}

/*重载大于等于号*/
bool operator >= (const NumStr &numStrL,const NumStr &numStrR)
{
	return numStrR < numStrL;
}

/*计算阶层函数*/
void loopFor(NumStr& numStr)
{
	string data("1");
	NumStr lessNum(data);
	NumStr result = lessNum;
	while(numStr >= lessNum)
	{
		result = numStr * result;

		--numStr;
	}
	result.printData();
}

/*错误处理函数*/
void errorDealFun(int errorType)
{
	if(errorType == ERROR_EMPTY)
	{
		cerr<<"the contain is ERROR_EMPTY:"<<errorType<<endl;
	}
	if(errorType == ERROR_DIGST)
	{
		cerr<<"the contain is ERROR_DIGST:"<<errorType<<endl;
	}
	if(errorType == ERROR_OTHRE)
	{
		cerr<<"the contain is ERROR_OTHRE:"<<errorType<<endl;
	}
	exit(1);
}
	
		
	


