/* 

A* Algorithm Implementation using STL is
Copyright (C)2001-2005 Justin Heyes-Jones

Permission is given by the author to freely redistribute and 
include this code in any program as long as this credit is 
given where due.
 
  COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, 
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
  INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE COVERED CODE 
  IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
  OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND 
  PERFORMANCE OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED 
  CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL 
  DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY 
  NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
  WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE 
  OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
  THIS DISCLAIMER.
 
  Use at your own risk!



  CFixedSizeAllocator class
  Copyright 2001 Justin Heyes-Jones

  This class is a constant time O(1) memory manager for objects of 
  a specified type. The type is specified using a template class.

  Memory is allocated from a fixed size buffer which you can specify in the
  class constructor or use the default.

  Using GetFirst and GetNext it is possible to iterate through the elements
  one by one, and this would be the most common use for the class. 

  I would suggest using this class when you want O(1) add and delete
  and you don't do much searching, which would be O(n). Structures such as binary 
  trees can be used instead to get O(logn) access time.

*/

#pragma once

#include <string.h>
#include <stdio.h>

template<class USER_TYPE>
class CFixedSizeAllocator
{
public: 
	// Constants
	enum
	{
		FSA_DEFAULT_SIZE = 100
	};

	// This class enables us to transparently manage the extra data 
	// needed to enable the user class to form part of the double-linked
	// list class
	struct FSA_ELEMENT
	{
		USER_TYPE UserType;
		
		FSA_ELEMENT *pPrev;
		FSA_ELEMENT *pNext;
	};

public: // methods
	CFixedSizeAllocator(unsigned int dwMaxElements = FSA_DEFAULT_SIZE) :
		_dwMaxElements(dwMaxElements), _pFirstUsed(NULL)
	{
		// Allocate enough memory for the maximum number of elements
		_pMemory = (FSA_ELEMENT*)new char[_dwMaxElements * sizeof(FSA_ELEMENT)];

		// Set the free list first pointer
		_pFirstFree = _pMemory;

		// Clear the memory
		memset(_pMemory, 0, sizeof(FSA_ELEMENT) * _dwMaxElements);

		// Point at first element
		FSA_ELEMENT* pElement = _pFirstFree;

		// Set the double linked free list
		for(unsigned int i = 0; i < _dwMaxElements; i++)
		{
			pElement->pPrev = pElement - 1;
			pElement->pNext = pElement + 1;
			pElement++;
		}

		// first element should have a null prev
		_pFirstFree->pPrev = NULL;
		// last element should have a null next
		(pElement - 1)->pNext = NULL;
	}

	~CFixedSizeAllocator()
	{
		// Free up the memory
		delete[] (char*)_pMemory;
	}

	// Allocate a new USER_TYPE and return a pointer to it 
	USER_TYPE *alloc()
	{
		FSA_ELEMENT *pNewNode = NULL;

		if(_pFirstFree == NULL)
			return NULL;

		pNewNode = _pFirstFree;
		_pFirstFree = pNewNode->pNext;

		// if the new node points to another free node then
		// change that nodes prev free pointer...
		if(pNewNode->pNext != NULL)
			pNewNode->pNext->pPrev = NULL;

		// node is now on the used list

		pNewNode->pPrev = NULL; // the allocated node is always first in the list

		if(_pFirstUsed == NULL)
		{
			pNewNode->pNext = NULL; // no other nodes
		}
		else
		{
			_pFirstUsed->pPrev = pNewNode; // insert this at the head of the used list
			pNewNode->pNext = _pFirstUsed;
		}

		_pFirstUsed = pNewNode;
		return reinterpret_cast<USER_TYPE*>(pNewNode);
	}

	// Free the given user type
	// For efficiency I don't check whether the pUserData is a valid
	// pointer that was allocated. I may add some debug only checking
	// (To add the debug check you'd need to make sure the pointer is in 
	// the _pMemory area and is pointing at the start of a node)
	void free(USER_TYPE* pUserData)
	{
		FSA_ELEMENT* pNode = reinterpret_cast<FSA_ELEMENT*>(pUserData);

		// manage used list, remove this node from it
		if(pNode->pPrev != NULL)
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
		else
		{
			// this handles the case that we delete the first node in the used list
			_pFirstUsed = pNode->pNext;
		}

		if(pNode->pNext != NULL)
			pNode->pNext->pPrev = pNode->pPrev;

		// add to free list
		if(_pFirstFree == NULL) 
		{
			// free list was empty
			_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		}
		else
		{
			// Add this node at the start of the free list
			_pFirstFree->pPrev = pNode;
			pNode->pNext = _pFirstFree;
			_pFirstFree = pNode;
		}
	}

	// For debugging this displays both lists (using the prev/next list pointers)
	void Debug()
	{
		printf("free list ");

		FSA_ELEMENT* p = _pFirstFree;
		while(p != NULL)
		{
			printf("%x!%x ", p->pPrev, p->pNext);
			p = p->pNext;
		}
		printf("\n");
		printf("used list ");
		p = _pFirstUsed;
		while(p != NULL)
		{
			printf("%x!%x ", p->pPrev, p->pNext);
			p = p->pNext;
		}
		printf("\n");
	}

	// Iterators

	USER_TYPE* GetFirst()
	{
		return reinterpret_cast<USER_TYPE*>(_pFirstUsed);
	}

	USER_TYPE* GetNext(USER_TYPE* pUserData)
	{
		return reinterpret_cast<USER_TYPE*>((reinterpret_cast<FSA_ELEMENT*>(pUserData))->pNext);
	}

public: // data

private: // methods

private: // data

	FSA_ELEMENT* _pFirstFree;
	FSA_ELEMENT* _pFirstUsed;
	unsigned int _dwMaxElements;
	FSA_ELEMENT* _pMemory;

};
