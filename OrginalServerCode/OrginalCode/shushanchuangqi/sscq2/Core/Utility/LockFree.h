/********************************************************************
//	Server Utility Library Source File.
//	File name:	LockFree.h
//	Created:	2012/08/21	11:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#pragma once

#ifndef LOCK_FREE_H
#define LOCK_FREE_H

#include <deque>
#include "ObjPool.h"

using namespace std;

//无锁队列，使用原子操作实现
template<typename T>
class CLockFreeQueue
{
public:
	CLockFreeQueue() : _head(NULL) { }

	struct SNode : public CMTPoolObj<SNode>
	{
		template<typename U>
		SNode(U&& d) : data(forward<U>(d)), pNext(NULL) { }
		T data;
		SNode* pNext;

		int TailCount() const
		{
			int count = 0;
			SNode* pNode = this;
			while(pNode != NULL)
			{
				count++;
				pNode = pNode->pNext;
			}
			return count;
		}
	};

	bool Empty() const
	{
		return _head.load() == NULL;
	}

	template<typename U>
	bool Push(U&& rData)
	{
		SNode* pNode = new SNode(forward<U>(rData));
		if(pNode == NULL)
			return false;
		SNode* pHead = NULL;
		do
		{
			pHead = _head.load(memory_order_acquire);
			pNode->pNext = pHead;
		} while(!_head.compare_exchange_weak(pHead, pNode, memory_order_release, memory_order_acquire));
		return true;
	}

	SNode* PopAll()
	{
		SNode* pLast = PopAllReverse();
		SNode* pFirst = NULL;
		while(pLast != NULL)
		{
			SNode* pTemp = pLast;
			pLast = pLast->pNext;
			pTemp->pNext = pFirst;
			pFirst = pTemp;
		}
		return pFirst;
	}

	void PopAll(deque<T>& rDeque)
	{
		SNode* pLast = PopAllReverse();
		SNode* pNode = NULL;
		while(pLast != NULL)
		{
			pNode = pLast;
			pLast = pLast->pNext;
			rDeque.push_front(pNode->data);
			delete pNode;
		}
	}

	SNode* PopAllReverse()
	{
		return _head.exchange(NULL, memory_order_relaxed);
	}

private:
	atomic<SNode*> _head;
};

#endif // #ifndef LOCK_FREE_H
