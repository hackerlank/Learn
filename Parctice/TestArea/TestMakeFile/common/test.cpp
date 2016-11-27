#include "test.h"
Test::Test(const int _key,const int _value):m_key(_key),m_value(_value)
{
}

void Test::print() const
{
	cout<<"key :"<<m_key<<" value:"<<m_value<<endl;
}

