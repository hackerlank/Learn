#include "FixList.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


FixList::FixList(ACE_UINT32 unSize)
{
	m_unSize = unSize;

	m_nodeList = new FixListNode[m_unSize];

	m_usedList.head = m_usedList.tail = NULL;
	m_freeList.head = m_freeList.tail = NULL;

	m_iterCursor = NULL;

	reset();
}

FixList::~FixList()
{
	if(m_nodeList != NULL)
	{
		delete m_nodeList;
	}
}

void FixList::reset()
{
	if(m_nodeList != NULL)
	{
		for(int i = 0;i < (int)m_unSize;i ++)
		{
			if(i == 0)
			{
				m_nodeList[i].prev = NULL;
			}
			else
			{
				m_nodeList[i].prev = &m_nodeList[i - 1];
			}
			
			if(i == (m_unSize - 1))
			{
				m_nodeList[i].next = NULL;
			}
			else
			{
				m_nodeList[i].next = &m_nodeList[i + 1];
			}
		}

		m_freeList.head = &m_nodeList[0];
		m_freeList.tail = &m_nodeList[m_unSize - 1];
	}
}

int FixList::insert(ACE_UINT32 val)
{
	FixListNode *pNode = deleteNode(m_freeList, NULL);

	if(pNode == NULL)
	{
		return -1;
	}

	pNode->val = val;

	insertNode(m_usedList, pNode);

	return 0;
}

void FixList::remove(FixListNode *node)
{
	deleteNode(m_usedList, node);

	insertNode(m_freeList, node);
}

void FixList::startIter()
{
	m_iterCursor = m_usedList.head;
}

void FixList::advance()
{
	if(m_iterCursor == NULL)
	{
		return;
	}

	m_iterCursor = m_iterCursor->next;
}

FixListNode *FixList::currentNode()
{
	return m_iterCursor;
}


bool FixList::iterDone()
{
	if(m_iterCursor == NULL)
	{
		return true;
	}

	return false;
}

FixListNode *FixList::deleteNode(FixListInfo &info, FixListNode *node)
{
	if(info.head == NULL || info.tail == NULL)
	{
		return NULL;
	}


	if(node == NULL)
	{
		node = info.head;
	}

	if(node->next != NULL)
	{
		node->next->prev = node->prev;
	}

	if(node->prev != NULL)
	{
		node->prev->next = node->next;
	}

	if(info.head == node)
	{
		info.head = node->next;
	}
	if(info.tail == node)
	{
		info.tail = node->prev;
	}

	node->next = node->prev = NULL;

	return node;
}

void FixList::insertNode(FixListInfo &info, FixListNode *node)
{
	if(info.head == NULL)
	{
		info.head = info.tail = node;
		node->prev = node->next = NULL;

		return;
	}

	info.tail->next = node;
	node->prev = info.tail;
	node->next = NULL;

	info.tail = node;
}