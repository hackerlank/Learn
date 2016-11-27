#ifndef TEST_AUTO_PTR_H
#define TEST_AUTO_PTR_H

#include "autoLifeHook.h"

class TestAutoPtr : public AutoLifeHook
{
	public:
		TestAutoPtr( const int a,const int b ) : m_a(a),m_b(b)
		{
		}
		int getA()
		{
			return m_a;
		}
		int getB()
		{
			return m_b;
		}
	private:
		int m_a;
		int m_b;
};

#endif
	
