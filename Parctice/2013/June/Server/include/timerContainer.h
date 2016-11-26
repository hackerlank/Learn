#ifndef TIMER_CONTAINER_H
#define TIMER_CONTAINER_H
#include<string>
#include<map>
#include<list>
#include<set>
#include<iostream>
#include<string.h>
using namespace std;
template<class T>
class TimerContainer
{
	list<string> idSet;
	map<string,T> objectMap;
	set<string> asistSet;
public:
	TimerContainer(void);
	void inPushObj(T _obj);
	void inPushObj(char *id);
	T outObj(void);
	void dropObj(char *id);
	bool empty(void);
	void print(void);
	
	list<string>& getIdSet(void);
	void dropId(char *id);
	bool checkRepeat(string &_id);
	bool delAsist(string &_id);
};

template<class T>
TimerContainer<T>::TimerContainer(void)
{
	idSet.clear();
	asistSet.clear();
	
}

/*插入一个对象指针*/
template<class T>
void TimerContainer<T>::inPushObj(T _obj)
{
	if(_obj == NULL)
	{
		return;
	}
	string id;
	id = _obj->getIdentity();
	if(id.size() == 0)//Tory modify 2012.11.12
		return ;
	 if(!checkRepeat(id))
	 {
		 dropId(const_cast<char *>(id.c_str()));		
	 }
	 else
	 {
		asistSet.insert(id);
	 }
	idSet.push_back(id);
	objectMap[id] = _obj;
}

/*插入一个对象指针*/
template<class T>
void TimerContainer<T>::inPushObj(char *id)
{
	if(id == NULL)
	{
		return;
	}
	string ids = id;
	if(!checkRepeat(ids))
	{
		dropId(id);	
	}
	else
	{
		asistSet.insert(id);
	}
	asistSet.insert(id);
	idSet.push_back(id);
	
}

/*获得即将思考的一个对象指针*/
template<class T>	
T TimerContainer<T>::outObj(void)
{
	if(empty())
	{
		return NULL;
	}
	string id;
	typename map<string,T>::iterator obj_it;	
	while((!idSet.empty()) && (!objectMap.empty()))
	{		
		
		//cout<<"timerContainer.h:94 id is"<<id<<endl;
		id = idSet.front();
		idSet.pop_front();		
		delAsist(id);
		obj_it = objectMap.find(id);
		if(obj_it != objectMap.end())
		{
			/*测试思考时间*/
		//	string tiems;
			// testThkTime(tiems);
		//	//cout<<"think times:"<<tiems<<endl;
			
			return obj_it->second;				
		}		
			
	}
	return NULL;
}

/*删除一个对象实例指针*/
template<class T>
void TimerContainer<T>::dropObj(char *id)
{
	typename map<string,T>::iterator obj_it;
	obj_it = objectMap.find(id);
	if(obj_it == objectMap.end())
	{
		return;
	}
	else
	{
		objectMap.erase(obj_it);
		// dropId(id);
	}
}

/*判断是否为空*/
template<class T> 
bool TimerContainer<T>::empty(void)
{
	if(objectMap.empty())
	{
		idSet.clear();
		return true;
	}
	if(idSet.empty())
	{
		return true;
	}
	if(asistSet.empty())
	{
		return true;
	}
	return false;
}

/*测试打印函数*/
template<class T> 
void TimerContainer<T>::print(void)
{
	cout<<"test Begin:"<<endl;
	if(idSet.empty())
	{
		cout<<"test empty:"<<endl;
	}
	list<string>::iterator id_it;
	for(id_it = idSet.begin();id_it != idSet.end();id_it++)
	{
		cout<<"containId:"<<*id_it<<endl;
	}
	cout<<"test end:"<<endl;
}

template<class T> 
list<string>& TimerContainer<T>::getIdSet(void)
{
	return idSet;
}

/*删除一个对象指针*/
template<class T> 
void TimerContainer<T>::dropId(char *id)
{
	if(id == NULL)
	{
		return;
	}
	string ids = id;
	delAsist(ids);
	list<string>::iterator id_it;
	for(id_it = idSet.begin();id_it != idSet.end();id_it++)
	{
		if(strcmp((*id_it).c_str(),id) == 0)
		{ 
			idSet.erase(id_it);
			break;
		}
	}
}
/*检查插入对象是否重复*/
template<class T> 
bool TimerContainer<T>::checkRepeat(string &_id)
{
	set<string>::iterator id_it;
	id_it = asistSet.find(_id);
	if(id_it == asistSet.end())
	{
		return true;
	}
	return false;
}

/*辅助删除id*/
template<class T> 
bool TimerContainer<T>::delAsist(string &_id)
{
	set<string>::iterator id_it;	
	id_it = asistSet.find(_id);
	if(id_it == asistSet.end())
	{
		return false;
	}
	
	asistSet.erase(id_it);
	return false;
}


#endif