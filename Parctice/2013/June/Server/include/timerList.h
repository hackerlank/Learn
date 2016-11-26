/****************************************************************
 * Filename: timerList.h
 * 
 * Description: 定时器链表, 处理到期时间不同的定时器，
 *				按定时器剩余时间排序
 *
 * Original Author : bison, 2012-7-17
 *
 ****************************************************************/
 
#ifndef _TIMER_LIST_H_
#define _TIMER_LIST_H_

#include"libev.h"

//定时器节点
template<class T>
struct timerNode
{
	struct timerNode *next;	//前一节点
	struct timerNode *prev;	//后一节点
	double remaining;			//剩余时间
	ev_timer *timer;			//定时器
	T	obj;					//对象
	string id;					//对象id	停止正在进行的定时器时需要
	
};

template<class T>
class TimerList
{
	private:
	timerNode<T> *listHead;			//链表头
	
	public:
	TimerList();
	~TimerList();
	
	//查找是否有该对象id的节点
	bool find(string objId);
	//从前面查找插入位置并插入
	void push_front(ev_timer *timer, T obj, string objId);
	//弹出最早到期的定时器对应的对象
	T pop_front();
	//未到期的定时器停止时删除对应的对象
	T delInRun(string objId);
};

template<class T>
TimerList<T>::TimerList()
{
	listHead = new timerNode<T>;
	listHead->next = listHead;
	listHead->prev = listHead;
}

template<class T>
TimerList<T>::~TimerList()
{
	listHead->prev->next = NULL;
	
	timerNode<T> *temp;
	while(listHead->next != NULL)
	{
		temp = listHead->next;
		listHead->next = listHead->next->next;
		delete temp;
	}
	
	delete listHead;
}

template<class T>
void TimerList<T>::push_front(ev_timer *timer, T obj, string objId)
{
	if (find(objId) != false)
	{
		//对象重复
		return;
	}
	
	double remain =  ev_timer_remaining(loops, timer);
	timerNode<T> *searchPtr = listHead->next;
	
	//找插入位置前先更新第一个节点的定时器剩余时间
	if (searchPtr != listHead)
	{
		searchPtr->remaining = ev_timer_remaining(loops, searchPtr->timer);
	}
	
	bool done = true;
	//寻找该定时器应该插入的位置
	while( done && searchPtr != listHead)
	{
		if (searchPtr->remaining <= remain)
		{
			remain -= searchPtr->remaining;
			searchPtr = searchPtr->next;
		} else {
			searchPtr->remaining -= remain;
			done = false;
		}
	}
	
	timerNode<T> *listPtr = new timerNode<T>;
	listPtr->remaining = remain;
	listPtr->id = objId;
	listPtr->obj = obj;			//这个等号不知道有没有问题，如果是指针的话没有问题
	//插到searchPtr前
	listPtr->next = searchPtr;
	listPtr->prev = searchPtr->prev;
	searchPtr->prev->next = listPtr;
	searchPtr->prev = listPtr;
}

template<class T>
bool TimerList<T>::find(string objId)
{
	timerNode<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			return true;
		}
		
		searchPtr = searchPtr->next;
	}
	
	return false;
}

template<class T>
T TimerList<T>::pop_front()
{
	T obj;
	timerNode<T> *searchPtr = listHead->next;
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

template<class T>
T TimerList<T>::delInRun(string objId)
{
	timerNode<T>* searchPtr = listHead->next;
	while(searchPtr != listHead)
	{
		if (searchPtr->id == objId)
		{
			break;
		}
		
		searchPtr = searchPtr->next;
	}
	
	T obj;
	if (searchPtr != listHead)
	{
		obj = searchPtr->obj;
		
		//如果后面searchPtr后面还有节点，把剩余到期时间加到后面
		if (searchPtr->next != listHead)
		{
			searchPtr->next->remaining += searchPtr->remaining;
		}
		searchPtr->next->prev = searchPtr->prev;
		searchPtr->prev->next = searchPtr->next;
		searchPtr->next = searchPtr->prev = NULL;
		delete searchPtr;
		
		return obj; 
	}
	return NULL;
}

#endif