/************************************************************
	文件名：cpyManage.h
	文件作用：类CpyManger<副本动态管理类>的属性和方法的实现
	作者：chenzhen
	创建日期：2012.11.29
************************************************************/
#ifndef CPY_MANAGER
#define CPY_MANAGER
#include"cpy.h"
#include<vector>
class CpyManger
{
	vector<Cpy*> cpyVec;
	
	set<int> ctnManager;
	
	/*判断是否为空*/
	bool judgeEmpty(void);
	
	/*判断已回收set里面是否有index*/
	bool judRecovered(int index);
	
	public:
	
	/*构造函数*/
	CpyManger(int _num);
	
	/*分配一个副本指针*/
	int offerCpy(Cpy *offer);	
	
	/*回收副本指针*/
	bool recover(Cpy* _cpy,int index);
	
	/*分配一个副本指针*/
	Cpy* offerCpy(int &index);
	
	/*测试打印*/
	void print(void);

};
#endif

	
	
	