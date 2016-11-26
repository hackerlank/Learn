/************************************************************
	文件名：main.cpp
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#include"numStr.h"
#include"asistFun.h"
using namespace std;

FUN NumStr::dealErrorFun = &errorDealFun;

int main(void)
{	
	string data1("5"),data2("1");
	NumStr numStr1(data1),numStr2(data2),result;
	loopFor(numStr1);
	
	return 1;
}
	
	
	
