/****************************************************************
 * Filename: dictionary.h
 * 
 * Description: ×Öµä
 *
 * Original Author : bison, 2012-10-16
 *
 ****************************************************************/

#include<map>
using namespace std;

#define INVALID_DATA 0x5E5E5E5E

typedef int	AlpChar;
typedef struct mulTreNode_S
{
	AlpChar data;
	map<AlpChar, mulTreNode_S*> sonMap;
	bool isEndFlag;
	mulTreNode_S(AlpChar &val)
	{
		data = val;
		sonMap.clear();
		isEndFlag = true;
	}
} mulTreNode_T;

class Dictionary
{
	private:
	map<AlpChar, mulTreNode_T*> indexTable;
	public:
	Dictionary();
	void addOneStr(AlpChar *p);
	bool search(AlpChar *p);
};
