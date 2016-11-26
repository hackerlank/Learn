
#include<iostream>
using namespace std;

class NumStr
{	
	public:
	string strData;
	
	size_t scale;
	
	public:
	
	NumStr():scale(10)
	{
		
	}
	
	NumStr(string &_strData,int _scale = 10):strData(_strData),scale(_scale)
	{
		
	}
	
	NumStr(NumStr &_strData):strData(_strData.strData),scale(_strData.scale)
	{
		
	}
	
	inline bool empty(void)
	{
		return strData.empty();
	}
	
	inline size_t size(void)
	{
		return strData.size();
	}
	
	inline void fillNewData(string& newData)
	{
		strData.clear();
		strData = newData;
	}
	
	
	inline NumStr& operator =(NumStr &_strData)
	{
		strData = _strData.strData;
		scale = _strData.scale;
		return *this;
	}
	
};



NumStr& operator+(NumStr &numStrF,NumStr &numStrS)
{	
	string result;
	
	result +=  numStrF.strData;
	
	result +=  numStrS.strData;
	
//	NumStr p(result);	
	return NumStr(result);
//	return p;
}

int main(void)
{
	string data("123");
	NumStr g1(data),g2(data),g3;
	
	//为什么不能赋值
//	NumStr g4 = (g1 + g2);
	
	return 1;
}
