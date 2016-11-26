/************************************************************
	文件名：cpyManage.cpp
	文件作用：类CpyManger<副本动态管理类>的属性和方法的实现
	作者：chenzhen
	创建日期：2012.11.29
************************************************************/
#include"cpyManager.h"

/*构造函数*/
CpyManger::CpyManger(int num)
{
	int i;
	Cpy *newCpy;
	
	for(i = 0; i < num; i++)
	{
		try
		{
			newCpy = new Cpy();
			if(newCpy == NULL)
			{
				cout<<"it is NULL:"<<endl;
			}
		}
		catch(exception e)
		{
			throw e;
		}
		cpyVec.push_back(newCpy);
		ctnManager.insert(i);
	}
}

/*分配一个副本指针*/
int CpyManger::offerCpy(Cpy *offer)	
{
//	print();
	int index;
	offer = NULL;
	
	if(!judgeEmpty())
	{
		cout<<"the offer set is empty:"<<endl;
		return -1;		
	}
	index = *(ctnManager.begin());
	ctnManager.erase(ctnManager.begin());
	if(index < 0 || index >= cpyVec.size())
	{
		cout<<"the offer set index is error:"<<index<<endl;
		return -1;	
	}
	offer = cpyVec[index];	
	return index;
}


/*分配一个副本指针*/
Cpy* CpyManger::offerCpy(int &index)	
{
//	print();
	
	index = -1;	
	if(!judgeEmpty())
	{
		cout<<"the offer set is empty:"<<endl;
		
		return NULL;		
	}
	
	index = *(ctnManager.begin());
	
	cout<<"offer the index:"<<index<<endl;
	
	ctnManager.erase(ctnManager.begin());
	if(index < 0 || index >= cpyVec.size())
	{
		cout<<"the offer set index is error:"<<index<<endl;
		return NULL;	
	}
	return cpyVec[index];
}

/*回收副本指针*/
bool CpyManger::recover(Cpy* _cpy,int index)
{
	if(_cpy == NULL || index < 0 || index >= cpyVec.size())
	{
		cout<<"index is error or cpy is NULL:"<<index<<endl;
		return false;
	}
	if(!judRecovered(index))
	{
		return false;
	}
	ctnManager.insert(index);
	return true;
}
	

/*判断是否为空*/
bool CpyManger::judgeEmpty(void)
{
	if(ctnManager.empty())
	{
		return false;
	}
	return true;
}

/*判断已回收set里面是否有index*/
bool CpyManger::judRecovered(int index)
{
	set<int>::iterator index_it;
	
	if(index < 0 || index >= cpyVec.size())
	{
		cout<<"index is error:"<<index<<endl;
		return false;
	}
	
	index_it = ctnManager.find(index);
	if(index_it == ctnManager.end())
	{
		
		return true;
	}
	cout<<"index is recover again:"<<index<<endl;
	return false;
}

/*测试打印*/
void CpyManger::print(void)
{
	cout<<"the test of CpyManger begin:"<<endl;
	cout<<"size of ctnManager:"<<ctnManager.size()<<endl;
	cout<<"size of cpyVec:"<<cpyVec.size()<<endl;	
	cout<<"the test of CpyManger end:"<<endl;
}
	
	