////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include "AStar.h"

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

class CNullLog
{
public:
	template<typename T>
	CNullLog& operator<<(const T& rT)
	{
		return *this;
	}
};

static CNullLog g_oNullLog;

#ifdef OPEN_LOG
#define LOG_DBG cout
#define LOG_CRI cout
#else
#define LOG_DBG g_oNullLog
#define LOG_CRI cout
#endif

// Global data

// The world map

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

int map[ MAP_WIDTH * MAP_HEIGHT ] = 
{

	// 0001020304050607080910111213141516171819
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
	1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
	1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
	1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
	1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
	1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
	1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};

// map helper functions

bool SMapSearchNode::IsSameState(SMapSearchNode& rhs)
{
	// same state in a maze search is simply when (x,y) are the same
	if(x == rhs.x && y == rhs.y)
		return true;
	else
		return false;
}

void SMapSearchNode::PrintNodeInfo()
{
	LOG_DBG << "CNode position : (" << x << ", " << y << ")\n";
}

// Here's the heuristic function that estimates the distance from a CNode
// to the Goal. 

float SMapSearchNode::GoalDistanceEstimate(SMapSearchNode& rNodeGoal)
{
	float xd = fabs((float)x - (float)rNodeGoal.x);
	float yd = fabs((float)y - (float)rNodeGoal.y);
	return xd + yd;
}

bool SMapSearchNode::IsGoal(SMapSearchNode& rNodeGoal)
{
	if(x == rNodeGoal.x && y == rNodeGoal.y)
		return true;
	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool SMapSearchNode::GetSuccessors(CAStarSearch<SMapSearchNode>* pAStarSearch, SMapSearchNode* pParentNode)
{
	int parent_x = -1; 
	int parent_y = -1; 

	if(pParentNode != NULL)
	{
		parent_x = pParentNode->x;
		parent_y = pParentNode->y;
	}

	// push each possible move except allowing the search to go backwards

	const CAStar& rAStar = pAStarSearch->GetAStar();

	const int arDx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int arDy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	for(int i = 0; i < 8; ++i)
	{
		int px = x + arDx[i];
		int py = y + arDy[i];
		if(rAStar.GetMap(px, py) < GRID_BLOCK_NUMBER && !(parent_x == px && parent_y == py)) 
		{
			if(i % 2 != 0 && rAStar.GetMap(px, y) >= GRID_BLOCK_NUMBER && rAStar.GetMap(x, py) >= GRID_BLOCK_NUMBER)
			{
				// can't cross block corners
				continue;
			}
			SMapSearchNode oNewNode(px, py);
			pAStarSearch->AddSuccessor(oNewNode);
		}
	}

	return true;
}

// given this pNode, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this pNode since that is 
// conceptually where we're moving

float SMapSearchNode::GetCost(CAStarSearch<SMapSearchNode>* pAStarSearch, SMapSearchNode& rSucNode)
{
	const CAStar& rAStar = pAStarSearch->GetAStar();
	return (float)rAStar.GetMap(x, y);
}

// Main
bool CAStar::FindPath(SMapSearchNode& rStart, SMapSearchNode& rGoal, vector<SMapSearchNode>& vecResult) const
{
	LOG_DBG << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	CAStarSearch<SMapSearchNode> oAStarSearch(*this);

	// Set Start and goal states

	oAStarSearch.SetStartAndGoalStates(rStart, rGoal);

	unsigned int dwSearchState;
	unsigned int dwSearchSteps = 0;

	do
	{
		dwSearchState = oAStarSearch.SearchStep();
		dwSearchSteps++;

#if DEBUG_LISTS

		LOG_DBG << "Steps:" << dwSearchSteps << "\n";

		int len = 0;

		LOG_DBG << "Open:\n";
		SMapSearchNode* p = oAStarSearch.GetOpenListStart();
		while(p != NULL)
		{
			len++;
#if !DEBUG_LIST_LENGTHS_ONLY			
			p->PrintNodeInfo();
#endif
			p = oAStarSearch.GetOpenListNext();
		}

		LOG_DBG << "Open list has " << len << " nodes\n";

		len = 0;

		LOG_DBG << "Closed:\n";
		p = oAStarSearch.GetClosedListStart();
		while( p )
		{
			len++;
#if !DEBUG_LIST_LENGTHS_ONLY			
			p->PrintNodeInfo();
#endif			
			p = oAStarSearch.GetClosedListNext();
		}
		LOG_DBG << "Closed list has " << len << " nodes\n";
#endif
	}
	while(dwSearchState == CAStarSearch<SMapSearchNode>::SEARCH_STATE_SEARCHING);

	if(dwSearchState == CAStarSearch<SMapSearchNode>::SEARCH_STATE_SUCCEEDED)
	{
		LOG_DBG << "Search found goal state\n";

		SMapSearchNode* pNode = oAStarSearch.GetSolutionStart();
		if(pNode == NULL)
		{
			LOG_CRI << "Start pNode is NULL!";
			return false;
		}

#if DISPLAY_SOLUTION
		LOG_DBG << "Displaying solution\n";
#endif
		int steps = 0;

		pNode->PrintNodeInfo();
		vecResult.push_back(*pNode);
		while(true)
		{
			pNode = oAStarSearch.GetSolutionNext();
			if(pNode == NULL)
				break;

			pNode->PrintNodeInfo();
			vecResult.push_back(*pNode);
			steps++;
		};

		LOG_DBG << "Solution steps " << steps << "\n";

		// Once you're done with the solution you can free the nodes up
		oAStarSearch.FreeSolutionNodes();
	}
	else if(dwSearchState == CAStarSearch<SMapSearchNode>::SEARCH_STATE_FAILED) 
	{
		LOG_CRI << "Search terminated. Did not find goal state\n";
	}
	else
	{
		LOG_CRI << "Search failed with state: " << dwSearchState;
	}

	// Display the number of loops the search went through
	LOG_DBG << "dwSearchSteps : " << dwSearchSteps << "\n";
	oAStarSearch.EnsureMemoryFreed();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
