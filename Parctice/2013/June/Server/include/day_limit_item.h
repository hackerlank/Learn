#ifndef _DAY_LIMIT_ITEM_H_
#define _DAY_LIMIT_ITEM_H_

#include<map>
#include<string>
using namespace std;
#define MAX_DAY_LMT_ITEM_SIZE 400

//每日都会更新但每日有次数限制的项目，如签到，日更新活动，日常任务，帮派任务等
typedef struct DayLimitItem_S
{
	char id[32];				//项目Id
	int limit;				//项目每天的限制次数, limit要求是大于0
	int value;				//当日项目已经做过的次数
	
	DayLimitItem_S(char* _id, int _limit)
	{
		//id = _id;
		memset(id, 0, sizeof(id));
		strncpy(id, _id, strlen(_id));
		limit = _limit;
		value = 0;
	}
	
	//空构造
	DayLimitItem_S(){};
	
	//等号操作
	void operator =(const DayLimitItem_S &data)
	{
		memset(id, 0, sizeof(id));
		strncpy(id, data.id, sizeof(data.id));
		limit = data.limit;
		value = data.value;
	}
	
	//是否达到了限制
	bool isFull()
	{
		cout<<"BisonShow id is "<<id<<endl;
		cout<<"limit is "<<limit<<" current value is "<<value<<endl;
		if (limit > value)
		{
			return false;
		}
		return true;
	}
	
	//更新已做的次数
	bool incVal()
	{
		if (value < limit)
		{
			value++;
			return true;
		}
		return false;
	}
	
	//每日第一次登陆的时候清除已经做次数，重置为0
	void clrVal()
	{
		value = 0;
	}
	
}DayLimitItem_T;

//日限制项目查找组
typedef struct DayLmtFindGroup_S
{
	map<string, int> findMap;								//这个可以是写死的
	DayLimitItem_T dayLmtItemArr[MAX_DAY_LMT_ITEM_SIZE];	//只增不减
	int lastUsedIndex;
	DayLmtFindGroup_S()
	{
		lastUsedIndex = 0;
	}
	void addOneItem(DayLimitItem_T item)
	{
		dayLmtItemArr[lastUsedIndex] = item;
		findMap.insert(pair<string, int>(item.id, lastUsedIndex));
		lastUsedIndex++;
	}
	
	//更新某项 返回更新项的下标，返回-1时表明更新失败
	int incOneItem(string id)
	{
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			return -1;
		}
		if (dayLmtItemArr[index].incVal())
		{
			return index;
		
		} else {
			return -1;
		}
	}
	
	//判断某项是否达到限制
	int isOneItemFull(string id)
	{
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			cout<<"BisonShow "<<id<<" is not day limit item!"<<endl;
			return -1;
		}
		return dayLmtItemArr[index].isFull();
	}
	
	int clrOneItemVal(string id)
	{
	
		map<string, int>::iterator it;
		it = findMap.find(id);
		int index = ((it == findMap.end()) ? -1 : it->second);
		if (index == -1)
		{
			cout<<"BisonShow "<<id<<" is not day limit item!"<<endl;
			return -1;
		}
		cout<<"BisonShow: the day limit item of "<<id<<" val now clear to 0"<<endl;
		dayLmtItemArr[index].clrVal();
		return index;
	}
	
	//每日第一次登陆清空所有的val值
	void clrAllItemVal()
	{
		for(int i = 0; i < lastUsedIndex; i++)
		{
			dayLmtItemArr[i].clrVal();
		}
	}
	
	void items2group(DayLimitItem_T arr[], int size)
	{
		if (size > MAX_DAY_LMT_ITEM_SIZE)
		{
			//这里需要提醒调大size
			return;
		}
		
		for(int i = 0; i < size; i++)
		{
			addOneItem(arr[i]);
		}
	}
	
	void group2item(DayLimitItem_T &item, int index)
	{
		item = dayLmtItemArr[index];
	}
	
	//等号操作
	void operator =(const DayLmtFindGroup_S &data)
	{
		findMap.clear();
		findMap = data.findMap;
		memcpy(dayLmtItemArr, data.dayLmtItemArr, sizeof(dayLmtItemArr));
		lastUsedIndex = data.lastUsedIndex;
	}
}DayLmtFindGroup_T;

#endif