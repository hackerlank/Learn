#include "my_mem_group.h"
#include "my_memcached.h"

extern map<int, Mem_configure*> mem_group_table;
extern MyMemGroup* mem_group;
/* 
* author: tory
* date : 2013.3.13
* describe:服务器启动时，初始化缓存服务器列表管理类对象
*/
bool initMyMemGroup()	
{
	int size = mem_group_table.size();
	mem_group = new MyMemGroup();
	
	//检测缓存服务器管理类维护的可工作服务器数目和配置文件指定数目是否匹配
	if(size != mem_group->number)	
	{	
		return false;
	}else{
		return true;
	}	
}


/* 
* author: tory
* date : 2013.3.13
* describe: constructor
*/
MyMemGroup::MyMemGroup()
{
	map<int,Mem_configure*>::iterator iter = mem_group_table.begin();
	for(iter; iter != mem_group_table.end(); iter++)
	{
		MyMemcache *my_mem = NULL;
		my_mem = new MyMemcache(iter->second->server_ip, iter->second->server_port);
		
		//缓存服务器能正常工作，才能仿佛mem_server_map容器中，否则跳过
		if(test_memcached_server(my_mem) == true)	
		{
			MyMemGroup::mem_server_map[iter->first] = my_mem;
		}else{
			cout<<"new my_mem failue,ip:"<<iter->second->server_ip<<" port:"<<iter->second->server_port<<endl;
			continue;
		}		
	}
	
	MyMemGroup::number = MyMemGroup::mem_server_map.size();//缓存服务器管理类维护的缓存服务器数目
}

MyMemGroup::~MyMemGroup()
{

}

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：char*类型键值key,用于存储/修改的数据data2set，数据大小size,选择存储的区zone_index
* 返回值:	bool值，存储/修改成功，返回true,否则返回false
*/
bool MyMemGroup::set_data(char* key, char* data2set, int size, int zone_index)
{
	if(data2set == NULL || key == NULL )
    {
		// cout<<"data or key is NULL,otherwise zone_index illegality,set_data failure"<<endl;
        return false;
    } 
    
	map<int, MyMemcache*>::iterator iter = mem_server_map.find(zone_index);
	if(iter == mem_server_map.end())
	{
		return false;
	}	
	
	MyMemcache *my_mem = iter->second;
	if(my_mem == NULL)
	{
		return false;
	}
	
	return (my_mem->set_mem_data(key, data2set, size));	

}

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：string类型键值key,用于存储/修改的数据data2set，数据大小size,zone_index表示缓存服务器索引
* 返回值:	bool值，存储/修改成功，返回true,否则返回false
*/
bool MyMemGroup::set_data(string key, char* data2set, int size, int zone_index)
{
	if(data2set == NULL || key.empty())
    {
		// cout<<"data or key is empty,otherwise zone_index illegality,set_data failure"<<endl;
        return false;
    } 
    
	map<int, MyMemcache*>::iterator iter = mem_server_map.find(zone_index);
	if(iter == mem_server_map.end())
	{
		return false;
	}	
	
	MyMemcache *my_mem = iter->second;
	if(my_mem == NULL)
	{
		return false;
	}
	
	return (my_mem->set_mem_data(key, data2set, size));	
}

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：char*型键值key,int指针sz和where分别表示数据的大小和来源,zone_index为服务器区号，缺省默认为-1，表示从任意缓存服务器获取数据
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/
char* MyMemGroup::get_data(char* mem_key, int*sz, int*where, int zone_index)
{
	if(mem_key == NULL)
	{
		// cout<<"get data to memcached server failure,key is empty"<<endl;
		return NULL;
	}
	
	MyMemcache *my_mem = NULL;
	map<int, MyMemcache*>::iterator iter;
	if(zone_index == -1)
	{
		for(iter = mem_server_map.begin(); iter != mem_server_map.end(); iter++)
		{
			my_mem = iter->second;
			if(my_mem == NULL)
			{
				continue;
			}
			
			char* p_data = my_mem->get_mem_data(mem_key, sz);//拿到的缓存数据的地址
			if(p_data == NULL)
			{
				continue;
			}else{
				cout<<"get p_data from zone_index:"<<iter->first<<endl;
				*where = iter->first;
				return p_data;	//成功找到key对应的数据，函数返回
			}
		}	
		return NULL;
	}else{
		iter = mem_server_map.find(zone_index);
		if(iter == mem_server_map.end())
		{
			return NULL;
		}	
		my_mem = iter->second;
		if(my_mem == NULL)
		{
			return NULL;
		}
		*where = zone_index;	//也赋上值吧，以免somebody用
		return (my_mem->get_mem_data(mem_key, sz));
	}
}	

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：string型键值key,int指针sz和where分别表示数据的大小和来源,zone_index表示服务器索引，缺省默认为-1，表示从任意缓存服务器获取数据
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/
char* MyMemGroup::get_data(string mem_key, int*sz, int*where, int zone_index)
{
	if(mem_key.empty())
	{
		// cout<<"get data to memcached server failure,key is empty"<<endl;
		return NULL;
	}
	
	MyMemcache *my_mem = NULL;
	map<int, MyMemcache*>::iterator iter;
	if(zone_index == -1)
	{
		for(iter = mem_server_map.begin(); iter != mem_server_map.end(); iter++)
		{
			my_mem = iter->second;
			if(my_mem == NULL)
			{
				continue;
			}
			
			char* p_data = my_mem->get_mem_data(mem_key, sz);//拿到的缓存数据的地址
			if(p_data == NULL)
			{
				continue;
			}else{
				cout<<"get p_data from zone_index:"<<iter->first<<endl;
				*where = iter->first;
				return p_data;	//成功找到key对应的数据，函数返回
			}
		}	
		
		return NULL;
	}else{
		iter = mem_server_map.find(zone_index);
		if(iter == mem_server_map.end())
		{
			return NULL;
		}	
		my_mem = iter->second;
		if(my_mem == NULL)
		{
			return NULL;
		}
		
		*where = zone_index;	//也赋上值吧，以免somebody用
		return (my_mem->get_mem_data(mem_key, sz));
	}
}

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：string型键值key,zone_index表示服务器索引
* 返回值:	根据key值，从指定缓存服务器删除数据
*/	
bool MyMemGroup::delete_data(string key, int zone_index)
{
	if(key.empty())
	{
		return false;
	}
	
	map<int, MyMemcache*>::iterator iter = mem_server_map.find(zone_index);
	if(iter == mem_server_map.end())
	{
		return false;
	}	
	
	MyMemcache *my_mem = iter->second;
	if(my_mem == NULL)
	{
		return false;
	}
    
	return (my_mem->delete_mem_data(key));
}

/*
* author:	Tory
* data	:	2013.3.13
* 传入参数：char型键值key,zone_index表示服务器索引
* 返回值:	根据key值，从指定缓存服务器删除数据
*/	
bool MyMemGroup::delete_data(char* key, int zone_index)
{
	if(key == NULL)
	{
		return false;
	}
	
	map<int, MyMemcache*>::iterator iter = mem_server_map.find(zone_index);
	if(iter == mem_server_map.end())
	{
		return false;
	}	
	
	MyMemcache *my_mem = iter->second;
	if(my_mem == NULL)
	{
		return false;
	}
    
	return (my_mem->delete_mem_data(key));
}