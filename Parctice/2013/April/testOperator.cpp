
#include<iostream>
using namespace std;

class NumStr
{	
	public:
	string strData;
	
	size_t scale;
	
	public:
	
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
	
	
	inline void operator =(NumStr &_strData)
	{
		strData = _strData.strData;
		scale = _strData.scale;
	}
	
};



NumStr operator+(NumStr &numStrF,NumStr &numStrS)
{
	NumStr resultNum;
	
	string result;
	
	result +=  numStrF.strData;
	
	result +=  numStrS.strData;
	
	resultNum.fillNewData(result);
	
	return resultNum;
}

int main(void)
{
	string data("123");
	NumStr g1(data),g2(data),g3;
	
	g3 = g1 + g2;
	
	return g3;
}
