/************************************************************
	文件名：numStr.h
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#ifndef NUMSTR_H
#define NUMSTR_H
#include<iostream>
#include<stdlib.h>

typedef void (*FUN)(int errorType);

using namespace std;

class NumStr
{	
	string strData;
	
	size_t scale;
	
	static FUN dealErrorFun;
	
	/*--辅助函数*/
	void reduceOne(void);
	
	public:
	NumStr(const string &_strData,int _scale = 10):strData(_strData),scale(_scale)
	{
		strData = _strData;
	}
	
	NumStr(const NumStr &_strData):strData(_strData.strData),scale(_strData.scale)
	{
		
	}

	NumStr(void):scale(10)
	{

	}
	
	/*判断是否为空*/
	inline bool empty(void)
	{
		return strData.empty();
	}
	
	inline bool empty(void) const
	{
		return strData.empty();
	}
	
	/*求长度*/
	inline size_t size(void)
	{
		return strData.size();
	}
	
	inline size_t size(void) const
	{
		return strData.size();
	}
	
	inline void fillNewData(const string& newData)
	{
		strData.clear();
		strData = newData;
	}
	
	
	inline NumStr& operator =(const NumStr &_strData)
	{
		strData = _strData.strData;
		scale = _strData.scale;
	}	
	
	/*--重载函数*/
	NumStr& operator--(void);
	
	/*重载 += 函数*/
	NumStr& operator+= (const NumStr &numStrF);
	
	/*测试打印函数*/	
	void printData(void);	
	
	friend const NumStr operator* (const NumStr& numStrF,const NumStr& numStrS);
	
	friend bool operator < (const NumStr &numStrL,const NumStr &numStrR);
	
};

#endif
	
