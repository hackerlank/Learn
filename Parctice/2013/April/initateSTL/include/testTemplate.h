/************************************************************
	文件名：testTemplate.h
	文件作用：类Iterator类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/

#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H
using namespace std;

struct A
{
};
struct AA : public A
{
};
	
class Test
{
	typedef int INT;
};

template<typename T>
struct my_traits
{
	typedef typename T::INT INT;
}

template<typename T>
struct my_traits<T*>
{
	typedef int INT;
}

template<typename T>
struct my_traits<const T*>
{
	typedef int INT;
}


