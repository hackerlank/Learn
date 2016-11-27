#ifndef TEST_H
#define TEST_H									
#include <iostream>
using namespace std;
class Test
{
	public:
		Test(const int _key = 0,const int _value = 0);
		void print() const;
	private:
		int m_key;
		int m_value;
};

#endif

