#include<iostream>
#include<string.h>
#include<ext/hash_map>

using namespace __gnu_cxx;
using namespace std;

typedef struct UseInfo
{
	char name[16];
	char id[17];
	int where;
	
	UseInfo(const char* _name,const char* _id,int _where)
	{
		memset(name,'\0',sizeof(name));
		memset(id,'\0',sizeof(id));
		
		strncpy(name,_name,strlen(_name));
		strncpy(id,_id,strlen(_id));
		where = _where;
	}
	
	UseInfo(const UseInfo& useInfo)
	{
		memset(name,'\0',sizeof(name));
		memset(id,'\0',sizeof(id));
		
		strncpy(name,useInfo.name,strlen(useInfo.name));
		strncpy(id,useInfo.id,strlen(useInfo.id));
		where = useInfo.where;
	}
	UseInfo()
	{
		memset(name,'\0',sizeof(name));
		memset(id,'\0',sizeof(id));
		where = -1;
	}
	
	UseInfo& operator= (const UseInfo& useInfo)
	{
		memset(name,'\0',sizeof(name));
		memset(id,'\0',sizeof(id));
		
		strncpy(name,useInfo.name,strlen(useInfo.name));
		strncpy(id,useInfo.id,strlen(useInfo.id));
		where = useInfo.where;
		
		return *this;
	}
	
	bool operator< (const UseInfo& useInfo)
	{
		int flgName = strcmp(name,useInfo.name);
		if(flgName < 0)
		{
			return true;
		}
		if(flgName > 0)
		{
			return false;
		}
		
		int flgId = strcmp(id,useInfo.id);
		
		if(flgId < 0)
		{
			return true;
		}
		if(flgId > 0)
		{
			return false;
		}
		
		return where < useInfo.where;
	}
	
	bool operator== (const UseInfo& useInfo)
	{
		if(strcmp(name,useInfo.name) == 0 && where == useInfo.where)
		{
			return true;
		}
		return false;
	}
	
	
}UseInfor;


typedef struct UseFun
{
	inline bool operator() (const UseInfo& useInfo1,const UseInfo& useInfo2)
	{
		if(strcmp(useInfo1.name,useInfo2.name) == 0 && useInfo1.where == useInfo2.where)
		{
			return true;
		}
		return false;
	}
}UseFun;

int main()
{
	
//	hash_map<const char*,UseInfo,hash<const char*>,UseFun > hashMap;
	
	hash_map<const char*,UseInfo> hashMap;
	
	UseInfo a("123","456",1);
	
	hash_map<const char*,UseInfo>::const_iterator use_it = hashMap.find(a.name);
	
	if(use_it == hashMap.end())
	{
		hashMap[a.name] = a;
	}
	
	else
	{
		cout<<"use_it->first:"<<use_it->first<<endl;
	}
		
	UseInfo b("123","456",1);
	
	return 1;
}
	
	
