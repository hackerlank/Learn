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

*/

#pragma once

// used for text debugging
#include <iostream>
#include <stdio.h>
//#include <conio.h>
#include <assert.h>

// stl includes
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

// fast fixed size memory allocator, used for fast node memory management
#include "Allocator.h"

// Fixed size memory allocator can be disabled to compare performance
// Uses std new and delete instead if you turn it off
#define USE_FSA_MEMORY 1

// disable warning that debugging information has lines that are truncated
// occurs in stl headers

#ifdef _WIN32
#pragma warning(disable : 4786)
#endif

class CAStar;

// The AStar search class. TUserState is the users state space type
template<class TUserState>
class CAStarSearch
{
public: // data

	enum
	{
		SEARCH_STATE_NOT_INITIALISED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};

	// A node represents a possible state in the search
	// The user provided state type is included inside this type

public:

	class CNode
	{
	public:
		CNode* pParent; // used during the search to record the parent of successor nodes
		CNode* pChild; // used after the search for the application to view the search in reverse

		float g; // cost of this pNode + it's predecessors
		float h; // heuristic estimate of distance to goal
		float f; // sum of cumulative cost of predecessors and self and heuristic

		CNode() : pParent(0), pChild(0), g(0.0f),	h(0.0f), f(0.0f) { }
		TUserState _oUserState;
	};


	// For sorting the heap the STL needs compare function that lets us compare
	// the f value of two nodes

	class CHeapCompare 
	{
	public:
		bool operator()(const CNode *x, const CNode *y) const
		{
			return x->f > y->f;
		}
	};

public: // methods

	// constructor just initialises private data
	CAStarSearch(const CAStar& rAStar, int iMaxNode = 1000) :
		_rAStar(rAStar),
		_iAllocateNodeCount(0),
#if USE_FSA_MEMORY
		_oFixedSizeAllocator(iMaxNode),
#endif
		_dwState(SEARCH_STATE_NOT_INITIALISED),
		_pCurrentSolutionNode(NULL),
		_bCancelRequest(false)
	{
	}

	const CAStar& GetAStar() const { return _rAStar; }

	// call at any time to cancel the search and free up all the memory
	void CancelSearch()
	{
		_bCancelRequest = true;
	}

	// Set start and goal states
	void SetStartAndGoalStates(TUserState& rStart, TUserState& rGoal)
	{
		_bCancelRequest = false;

		_pStart = AllocateNode();
		_pGoal = AllocateNode();

		assert(_pStart != NULL && _pGoal != NULL);
		
		_pStart->_oUserState = rStart;
		_pGoal->_oUserState = rGoal;

		_dwState = SEARCH_STATE_SEARCHING;
		
		// Initialise the AStar specific parts of the start CNode
		// The user only needs fill out the state information

		_pStart->g = 0; 
		_pStart->h = _pStart->_oUserState.GoalDistanceEstimate(_pGoal->_oUserState);
		_pStart->f = _pStart->g + _pStart->h;
		_pStart->pParent = 0;

		// Push the start pNode on the Open list

		_vecOpenList.push_back(_pStart); // heap now unsorted

		// Sort back element into heap
		push_heap(_vecOpenList.begin(), _vecOpenList.end(), CHeapCompare());

		// Initialise counter for search steps
		_iSteps = 0;
	}

	// Advances search one step 
	unsigned int SearchStep()
	{
		// Firstly break if the user has not initialised the search
		assert(_dwState > SEARCH_STATE_NOT_INITIALISED && _dwState < SEARCH_STATE_INVALID);

		// Next I want it to be safe to do a searchstep once the search has succeeded...
		if(_dwState == SEARCH_STATE_SUCCEEDED || _dwState == SEARCH_STATE_FAILED) 
			return _dwState;

		// Failure is defined as emptying the open list as there is nothing left to 
		// search...
		// New: Allow user abort
		if(_vecOpenList.empty() || _bCancelRequest)
		{
			FreeAllNodes();
			_dwState = SEARCH_STATE_FAILED;
			return _dwState;
		}
		
		// Incremement step count
		_iSteps++;

		// Pop the best node (the one with the lowest f) 
		CNode* pNode = _vecOpenList.front(); // get pointer to the pNode
		pop_heap(_vecOpenList.begin(), _vecOpenList.end(), CHeapCompare());
		_vecOpenList.pop_back();

		// Check for the goal, once we pop that we're done
		if(pNode->_oUserState.IsGoal(_pGoal->_oUserState))
		{
			// The user is going to use the Goal Node he passed in 
			// so copy the parent pointer of pNode 
			_pGoal->pParent = pNode->pParent;

			// A special case is that the goal was passed in as the start state
			// so handle that here
			if(false == pNode->_oUserState.IsSameState(_pStart->_oUserState))
			{
				FreeNode(pNode);

				// set the child pointers in each node (except Goal which has no child)
				CNode* pNodeChild = _pGoal;
				CNode* pNodeParent = _pGoal->pParent;

				do 
				{
					pNodeParent->pChild = pNodeChild;
					pNodeChild = pNodeParent;
					pNodeParent = pNodeParent->pParent;
				} 
				while(pNodeChild != _pStart); // start is always the first pNode by definition
			}

			// delete nodes that aren't needed for the solution
			FreeUnusedNodes();
			_dwState = SEARCH_STATE_SUCCEEDED;
			return _dwState;
		}
		else // not goal
		{
			// We now need to generate the successors of this node
			// The user helps us to do this, and we keep the new nodes in
			// _vecSuccessor ...

			_vecSuccessor.clear(); // empty vector of successor nodes to pNode

			// User provides this functions and uses AddSuccessor to add each successor of
			// node 'pNode' to _vecSuccessor
			bool ret = pNode->_oUserState.GetSuccessors(this, pNode->pParent ? &pNode->pParent->_oUserState : NULL);
			if(!ret)
			{
				// free the nodes that may previously have been added 
				for(auto it = _vecSuccessor.begin(); it != _vecSuccessor.end(); ++it)
					FreeNode(*it);

				_vecSuccessor.clear(); // empty vector of successor nodes to pNode

				// free up everything else we allocated
				FreeAllNodes();

				_dwState = SEARCH_STATE_OUT_OF_MEMORY;
				return _dwState;
			}
			
			// Now handle each successor to the current pNode ...
			for(auto it = _vecSuccessor.begin(); it != _vecSuccessor.end(); ++it)
			{
				CNode* pNodeSuc = *it;
				// 	The g value for this successor ...
				float newg = pNode->g + pNode->_oUserState.GetCost(this, pNodeSuc->_oUserState);

				// Now we need to find whether the pNode is on the open or closed lists
				// If it is but the node that is already on them is better (lower g)
				// then we can forget about this successor

				// First linear search of open list to find node
				auto itOpen = _vecOpenList.begin();
				for(; itOpen != _vecOpenList.end(); ++itOpen)
				{
					CNode* pNodeOpen = *itOpen;
					if(pNodeOpen->_oUserState.IsSameState(pNodeSuc->_oUserState))
						break;
				}

				if(itOpen != _vecOpenList.end())
				{
					// we found this state on open
					CNode* pNodeOpen = *itOpen;
					if(pNodeOpen->g <= newg)
					{
						FreeNode(pNodeSuc);
						// the one on Open is cheaper than this one
						continue;
					}
				}

				auto itClose = _vecClosedList.begin();
				for(; itClose != _vecClosedList.end(); ++itClose)
				{
					CNode* pNodeClose = *itClose;
					if(pNodeClose->_oUserState.IsSameState(pNodeSuc->_oUserState))
						break;
				}

				if(itClose != _vecClosedList.end())
				{
					// we found this state on closed
					CNode* pNodeClose = *itClose;
					if(pNodeClose->g <= newg)
					{
						// the one on Closed is cheaper than this one
						FreeNode(pNodeSuc);
						continue;
					}
				}

				// This node is the best node so far with this particular state
				// so lets keep it and set up its AStar specific data ...

				pNodeSuc->pParent = pNode;
				pNodeSuc->g = newg;
				pNodeSuc->h = pNodeSuc->_oUserState.GoalDistanceEstimate(_pGoal->_oUserState);
				pNodeSuc->f = pNodeSuc->g + pNodeSuc->h;

				// Remove successor from closed if it was on it
				if(itClose != _vecClosedList.end())
				{
					// remove it from Closed
					FreeNode(*itClose); 
					_vecClosedList.erase(itClose);

					// Fix thanks to ...
					// Greg Douglas <gregdouglasmail@gmail.com>
					// who noticed that this code path was incorrect
					// Here we have found a new state which is already CLOSED
					// anus
				}

				// Update old version of this pNode
				if(itOpen != _vecOpenList.end())
				{	   
					FreeNode(*itOpen); 
			   		_vecOpenList.erase(itOpen);

					// re-make the heap 
					// make_heap rather than sort_heap is an essential bug fix
					// thanks to Mike Ryynanen for pointing this out and then explaining
					// it in detail. sort_heap called on an invalid heap does not work
					make_heap(_vecOpenList.begin(), _vecOpenList.end(), CHeapCompare());
				}

				// heap now unsorted
				_vecOpenList.push_back(pNodeSuc);

				// sort back element into heap
				push_heap(_vecOpenList.begin(), _vecOpenList.end(), CHeapCompare());
			}

			// push n onto Closed, as we have expanded it now
			_vecClosedList.push_back( pNode );

		} // end else (not goal so expand)
 		return _dwState; // Succeeded bool is false at this point. 
	}

	// User calls this to add a successor to a list of successors
	// when expanding the search frontier
	bool AddSuccessor(TUserState &State)
	{
		CNode* pNode = AllocateNode();
		if(pNode != NULL)
		{
			pNode->_oUserState = State;
			_vecSuccessor.push_back(pNode);
			return true;
		}
		return false;
	}

	// Free the solution nodes
	// This is done to clean up all used Node memory when you are done with the
	// search
	void FreeSolutionNodes()
	{
		CNode* pNode = _pStart;
		if(_pStart->pChild != NULL)
		{
			do
			{
				CNode* pNodeDel = pNode;
				pNode = pNode->pChild;
				FreeNode(pNodeDel);
				pNodeDel = NULL;
			} while(pNode != _pGoal);
			FreeNode(pNode); // Delete the goal
		}
		else
		{
			// if the start node is the solution we need to just delete the start and goal
			// nodes
			FreeNode(_pStart);
			FreeNode(_pGoal);
		}
	}

	// Functions for traversing the solution

	// Get start node
	TUserState* GetSolutionStart()
	{
		_pCurrentSolutionNode = _pStart;
		if(_pStart != NULL)
			return &_pStart->_oUserState;
		else
			return NULL;
	}
	
	// Get next node
	TUserState* GetSolutionNext()
	{
		if(_pCurrentSolutionNode != NULL && _pCurrentSolutionNode->pChild != NULL)
		{
			CNode* pChild = _pCurrentSolutionNode->pChild;
			_pCurrentSolutionNode = _pCurrentSolutionNode->pChild;
			return &pChild->_oUserState;
		}
		return NULL;
	}
	
	// Get end node
	TUserState *GetSolutionEnd()
	{
		_pCurrentSolutionNode = _pGoal;
		if(_pGoal != NULL)
			return &_pGoal->_oUserState;
		else
			return NULL;
	}
	
	// Step solution iterator backwards
	TUserState* GetSolutionPrev()
	{
		if(_pCurrentSolutionNode != NULL && _pCurrentSolutionNode->pParent != NULL)
		{
			CNode* pParent = _pCurrentSolutionNode->pParent;
			_pCurrentSolutionNode = _pCurrentSolutionNode->pParent;
			return &pParent->_oUserState;
		}
		return NULL;
	}

	// For educational use and debugging it is useful to be able to view
	// the open and closed list at each step, here are two functions to allow that.

	TUserState* GetOpenListStart()
	{
		float f = 0.f, g = 0.f, h = 0.f;
		return GetOpenListStart(f, g, h);
	}

	TUserState* GetOpenListStart(float &f, float &g, float &h)
	{
		_itDbgOpen = _vecOpenList.begin();
		if(_itDbgOpen != _vecOpenList.end())
		{
			CNode* pNode = *_itDbgOpen;
			f = pNode->f;
			g = pNode->g;
			h = pNode->h;
			return &pNode->_oUserState;
		}
		return NULL;
	}

	TUserState* GetOpenListNext()
	{
		float f = 0.f, g = 0.f, h = 0.f;
		return GetOpenListNext(f, g, h);
	}

	TUserState* GetOpenListNext(float &f, float &g, float &h)
	{
		_itDbgOpen++;
		if(_itDbgOpen != _vecOpenList.end())
		{
			CNode* pNode = *_itDbgOpen;
			f = pNode->f;
			g = pNode->g;
			h = pNode->h;
			return &pNode->_oUserState;
		}
		return NULL;
	}

	TUserState* GetClosedListStart()
	{
		float f = 0.f, g = 0.f, h = 0.f;
		return GetClosedListStart(f, g, h);
	}

	TUserState* GetClosedListStart(float &f, float &g, float &h)
	{
		_itDbgClosed = _vecClosedList.begin();
		if(_itDbgClosed != _vecClosedList.end())
		{
			CNode* pNode = *_itDbgClosed;
			f = pNode->f;
			g = pNode->g;
			h = pNode->h;
			return &pNode->_oUserState;
		}
		return NULL;
	}

	TUserState* GetClosedListNext()
	{
		float f = 0.f, g = 0.f, h = 0.f;
		return GetClosedListNext(f, g, h);
	}

	TUserState* GetClosedListNext(float &f, float &g, float &h)
	{
		_itDbgClosed++;
		if(_itDbgClosed != _vecClosedList.end())
		{
			CNode* pNode = *_itDbgClosed;
			f = pNode->f;
			g = pNode->g;
			h = pNode->h;
			return &pNode->_oUserState;
		}
		return NULL;
	}

	// Get the number of steps

	int GetStepCount() { return _iSteps; }

	void EnsureMemoryFreed()
	{
#if USE_FSA_MEMORY
		assert(_iAllocateNodeCount == 0);
#endif
	}

private: // methods

	// This is called when a search fails or is cancelled to free all used
	// memory 
	void FreeAllNodes()
	{
		// iterate open list and delete all nodes
		for(auto it = _vecOpenList.begin(); it != _vecOpenList.end(); ++it)
		{
			CNode *pNode = *it;
			FreeNode(pNode);
		}

		_vecOpenList.clear();

		// iterate closed list and delete unused nodes
		for(auto it = _vecClosedList.begin(); it != _vecClosedList.end(); ++it)
		{
			CNode *pNode = *it;
			FreeNode(pNode);
		}

		_vecClosedList.clear();

		// delete the goal
		FreeNode(_pGoal);
	}


	// This call is made by the search class when the search ends. A lot of nodes may be
	// created that are still present when the search ends. They will be deleted by this 
	// routine once the search ends
	void FreeUnusedNodes()
	{
		// iterate open list and delete unused nodes
		for(auto it = _vecOpenList.begin(); it != _vecOpenList.end(); ++it)
		{
			CNode *pNode = *it;
			if(pNode->pChild == NULL)
			{
				FreeNode(pNode);
				pNode = NULL;
			}
		}
		_vecOpenList.clear();

		// iterate closed list and delete unused nodes
		for(auto it = _vecClosedList.begin(); it != _vecClosedList.end(); ++it)
		{
			CNode *pNode = *it;
			if(pNode->pChild == NULL)
			{
				FreeNode(pNode);
				pNode = NULL;
			}
		}
		_vecClosedList.clear();
	}

	// Node memory management
	CNode* AllocateNode()
	{

#if !USE_FSA_MEMORY
		CNode *p = new CNode;
		return p;
#else
		CNode* pAddress = _oFixedSizeAllocator.alloc();
		if(pAddress == NULL)
			return NULL;
		++_iAllocateNodeCount;
		CNode* p = new (pAddress) CNode;
		return p;
#endif
	}

	void FreeNode( CNode *pNode )
	{
		--_iAllocateNodeCount;

#if !USE_FSA_MEMORY
		delete pNode;
#else
		_oFixedSizeAllocator.free(pNode);
#endif
	}

private: // data

	const CAStar& _rAStar;

	// Heap (simple vector but used as a heap, cf. Steve Rabin's game gems article)
	vector<CNode*> _vecOpenList;

	// Closed list is a vector.
	vector<CNode*> _vecClosedList; 

	// Successors is a vector filled out by the user each type successors to a node
	// are generated
	vector<CNode*> _vecSuccessor;

	// State
	unsigned int _dwState;

	// Counts steps
	int _iSteps;

	// Start and goal state pointers
	CNode* _pStart;
	CNode* _pGoal;

	CNode* _pCurrentSolutionNode;

#if USE_FSA_MEMORY
	// Memory
 	CFixedSizeAllocator<CNode> _oFixedSizeAllocator;
#endif
	
	//Debug : need to keep these two iterators around
	// for the user Dbg functions
	typename vector<CNode*>::iterator _itDbgOpen;
	typename vector<CNode*>::iterator _itDbgClosed;

	// debugging : count memory allocation and free's
	int _iAllocateNodeCount;
	bool _bCancelRequest;
};
