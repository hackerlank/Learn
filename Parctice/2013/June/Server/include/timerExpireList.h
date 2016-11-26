/****************************************************************
 * Filename: timerExpireList.h
 * 
 * Description: 定时器链表, 另外一种排序方式，按到期时刻排序，
 *				处理到期时间不同的定时器,
 *
 * Original Author : bison, 2012-7-17
 *
 * modified 2012-10-17，根据目前情况把所有时间由double改成int,进而能不调用ev_now
 *
 ****************************************************************/
 
#ifndef _TIMER_EXPIRE_LIST_H_
#define _TIMER_EXPIRE_LIST_H_
#include <iostream>
#include"libev.h"
#include"my_time.h"
using namespace std;
extern struct ev_loop *loops;
//定时器节点
template<class T>
struct timerNode_S
{
	struct timerNode_S *next;	//前一节点
	struct timerNode_S *prev;	//后一节点
	int expire; 				//到期时刻
	T	obj;					//对象
	string id;					//对象id	停止正在进行的定时器时需要
	
};

 
template<class T>
class TimerExpireList
{
	private:
	timerNode_S<T> *listHead;			//链表头
	
	public:
	TimerExpireList();
	~TimerExpireList();
	//从前面查找插入位置并插入
	void push_front(int expires, T obj, string objId);
	//从后面查找插入位置并插入
	void push_back(int expires, T obj, string objId);
	//弹出最早到期的定时器对应的对象
	//查找是否有该对象id的节点
	T find(string objId);
	//获取定时器的剩余时间
	int getTimerRemain(string objId);
	T pop_front();
	//未到期的定时器停止时删除对应的对象
	T delInRun(string objId);
};

template<class T>
TimerExpireList<T>::TimerExpireList()
{
	listHead = new timerNode_S<T>;
	listHead->next = listHead;
	listHead->prev = listHead;
}

template<class T>
TimerExpireList<T>::~TimerExpireList()
{
	listHead->prev->next = NULL;
	
	timerNode_S<T> *temp;
	while(listHead->next != NULL)
	{
		temp = listHead->next;
		listHead->next = listHead->next->next;
		delete temp;
	}
	
	delete listHead;
}

template<class T>
void TimerExpireList<T>::push_front(int expires, T obj, string objId)
{
	if (find(objId) != NULL)
	{
		//对象重复
		return;
	}
	
	cout<<"expires "<<expires<<endl;
	//double expire = expires + ev_now(loops);		//计算出到期时刻
	int expire = expires + MY_TV_SEC;				//计算出到期时刻
	cout<<"expire "<<expire<<endl;
	timerNode_S<T> *searchPtr = listHead->next;
	
	//寻找该定时器应该插入的位置
	while(searchPtr != listHead)
	{
		if (searchPtr->expire <= expire)
		{
			searchPtr = searchPtr->next;
		}
		else 
		{
			break;
		}
	}
	
	timerNode_S<T> *listPtr = new timerNode_S<T>;
	listPtr->expire = expire;
	listPtr->id = objId;
	listPtr->obj = obj;			//这个等号不知道有没有问题，如果是指针的话没有问题
	//插到searchPtr前
	listPtr->next = searchPtr;
	listPtr->prev = searchPtr->prev;
	searchPtr->prev->next = listPtr;
	searchPtr->prev = listPtr;
}

template<class T>
void TimerExpireList<T>::push_back(int expires, T obj, string objId)
{
	if (find(objId) != NULL)
	{
		//对象重复
		return;
	}
	
	/**
	 * 用到期时刻的一个不好处，启机最多50天后，启机时间可能要清零，前后调用ev_now可能会出错
	 */
	//double expire = expires + ev_now(loops);		//计算出到期时刻
	int expire = expires + MY_TV_SEC;		//计算出到期时刻
	timerNode_S<T> *searchPtr = listHead->prev;
	
	//寻找该定时器应该插入的位置
	while(searchPtr != listHead)
	{
		if (searchPtr->expire > expire)
		{
			searchPtr = searchPtr->prev;
		}
		else {
			break;
		}
	}
	
	timerNode_S<T> *listPtr = new timerNode_S<T>;
	listPtr->expire = expire;
	listPtr->id = objId;
	listPtr->obj = obj;			//这个等号不知道有没有问题，如果是指针的话没有问题
	//插到searchPtr后
	listPtr->prev = searchPtr;
	listPtr->next = searchPtr->next;
	searchPtr->next->prev = listPtr;
	searchPtr->next = listPtr;
}

template<class T>
T TimerExpireList<T>::find(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			return searchPtr->obj;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return NULL;
}

template<class T>
int TimerExpireList<T>::getTimerRemain(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	int remain = 0;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			remain = searchPtr->expire - MY_TV_SEC;
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return remain;
}

template<class T>
T TimerExpireList<T>::pop_front()
{
	T obj;
	timerNode_S<T> *searchPtr = listHead->next;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		listHead->next = searchPtr->next;
		searchPtr->next->prev = listHead;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		
		return obj; 
	}
	
	return NULL;
}

//删除运行中的定时器
template<class T>
T TimerExpireList<T>::delInRun(string objId)
{
	timerNode_S<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			cout<<"BionTest : have find the run timer to be deleted!"<<endl;
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	T obj;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		searchPtr->next->prev = searchPtr->prev;
		searchPtr->prev->next = searchPtr->next;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		cout<<"BionTest : have find the timer obj to be deleted!"<<endl;
		return obj; 
	}
	cout<<"BisonTest: haven't find the timer obj to be deleted!"<<endl;
	return NULL;
}

#endif