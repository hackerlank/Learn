#pragma once
#include "Search.h" // See header for copyright and usage information

#define GRID_BLOCK_NUMBER 9

// Definitions

struct SMapSearchNode
{
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;	

	SMapSearchNode() { x = y = 0; }
	SMapSearchNode(unsigned int px, unsigned int py) { x = px; y = py; }

	float GoalDistanceEstimate(SMapSearchNode& rNodeGoal);
	bool IsGoal(SMapSearchNode& rNodeGoal);
	bool GetSuccessors(CAStarSearch<SMapSearchNode>* pAStarSearch, SMapSearchNode* pParentNode);
	float GetCost(CAStarSearch<SMapSearchNode>* pAStarSearch, SMapSearchNode& rSucNode);
	bool IsSameState(SMapSearchNode& rhs);

	void PrintNodeInfo();
};

class CAStar
{
public:
	virtual int GetMap(int x, int y) const = 0;
	bool FindPath(SMapSearchNode& rStart, SMapSearchNode& rGoal, vector<SMapSearchNode>& vecResult) const;
};
