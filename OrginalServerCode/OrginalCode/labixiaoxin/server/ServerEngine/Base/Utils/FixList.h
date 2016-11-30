#pragma once

#include "ace\ACE.h"

#define DEFAULT_FIX_LIST_SIZE 64

typedef struct tagFixListNode
{
	ACE_UINT32 val;
	struct tagFixListNode *prev;
	struct tagFixListNode *next;
	//int idx;
}FixListNode;

typedef struct tagFixListInfo
{
	struct tagFixListNode *head;
	struct tagFixListNode *tail;
}FixListInfo;

class FixList
{
public:
	FixList(ACE_UINT32 unSize = DEFAULT_FIX_LIST_SIZE);
	~FixList();

	int insert(ACE_UINT32 val);
	void remove(FixListNode *node);
	void reset();
	void startIter();
	void advance();
	FixListNode *currentNode();
	bool iterDone();
private:
	FixListNode *deleteNode(FixListInfo &info, FixListNode *node);
	void insertNode(FixListInfo &info, FixListNode *node);

	ACE_UINT32 m_unSize;

	FixListNode *m_iterCursor;
	FixListNode *m_nodeList;

	FixListInfo m_usedList;
	FixListInfo m_freeList;
};