/****************************************************************
 * Filename: dictionary.cpp
 * 
 * Description: ×Öµä
 *
 * Original Author : bison, 2012-10-16
 *
 ****************************************************************/

#include "dictionary.h"
 
Dictionary::Dictionary()
{
	indexTable.clear();
}

void Dictionary::addOneStr(AlpChar *p)
{
	map<AlpChar, mulTreNode_T*>::iterator it;
	it = indexTable.find(*p);
	mulTreNode_T *root;
	if (it == indexTable.end())
	{
		root = new mulTreNode_T(*p);
		indexTable.insert(pair<AlpChar, mulTreNode_T*>(*p, root));
		p++;
		while (*p)
		{
			mulTreNode_T *sonNode = new mulTreNode_T(*p);
			root->sonMap.insert(pair<AlpChar, mulTreNode_T*>(*p, sonNode));
			root->isEndFlag = false;
			root = sonNode;
			p++;
		}
	} else {
		root = it->second;
		mulTreNode_T *temp = root;
		p++;
		while(*p)
		{
			if (!temp->isEndFlag)
			{
				it = temp->sonMap.find(*p);
				if (it != temp->sonMap.end())
				{	
					p++;
					temp = it->second;
				} else {
					mulTreNode_T *nextSonNode = new mulTreNode_T(*p);
					temp->sonMap.insert(pair<AlpChar, mulTreNode_T*>(*p, nextSonNode));
					temp = nextSonNode;
					p++;
				}
			} else {
				mulTreNode_T *nextSon = new mulTreNode_T(*p);
				temp->sonMap.insert(pair<AlpChar, mulTreNode_T*>(*p, nextSon));
				temp->isEndFlag = false;
				temp = nextSon;
				p++;
			}
		}
		
	}
	
}

bool Dictionary::search(AlpChar *p)
{
	map<AlpChar, mulTreNode_T*>::iterator it;
	AlpChar *base = p;
	mulTreNode_T *root;
	while (*base)
	{
		
		AlpChar *temp = base;
		it = indexTable.find(*base);
		if (it == indexTable.end())
		{
			base++;
			continue;
		}
	
		root = it->second;
		temp++;
		if (root->isEndFlag)
		{
			return true;
		}
		while (!root->isEndFlag)
		{
			it = root->sonMap.find(*temp);
			if (it == root->sonMap.end())
			{
				break;
			} 
			root = it->second;
			if (root->isEndFlag)
			{
				return true;
			}
			
			temp++;
		}
		base++;
	}
	
	return false;
}
