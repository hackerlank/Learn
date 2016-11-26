#include "my_memcached.h"
//全局函数头文件
#include "command_other_function_all_over.h"
//全局宏定义头文件
#include "wholeDefine.h"

//缓存服务器配置表
extern map<string, Mem_configure> mem_configure_table;

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;

extern MyMemcache* cdkeyMemcached;

bool initMyMemcached()
{
    map<string, Mem_configure>::iterator iter;
	iter = mem_configure_table.find("nickname_inspection_mem");
	if(iter != mem_configure_table.end())
    {
        mem_operate_nickname_inspection = new MyMemcache(iter->second.server_ip, iter->second.server_port);
    } else
    {
        cout<<"[XHM WARNING] new nickname_inspection_mem mem_operate_nickname_inspection ERROR(my_memcached.cpp)"<<endl;
        return false;
    }	
	

	if(test_memcached_server(mem_operate_nickname_inspection))
	{
		cout<<"[XHM MSG] mem_operate_nickname_inspection game memcached server is work!"<<endl;
	}else{
		cout<<"[XHM MSG] mem_operate_nickname_inspection game memcached server isn't work!"<<endl;
		return false;
	} 
	
	return true;
}

bool initCdKeyCached()
{
	map<string, Mem_configure>::iterator iter;
	iter = mem_configure_table.find("cdkey_server");
	if(iter != mem_configure_table.end())
    {
        cdkeyMemcached = new MyMemcache(iter->second.server_ip, iter->second.server_port);
    } else
    {
        cout<<"[XHM WARNING] new cdkeyMemcached mem_operate_nickname_inspection ERROR(my_memcached.cpp)"<<endl;
        return false;
    }	
	

	if(test_memcached_server(cdkeyMemcached))
	{
		cout<<"[XHM MSG] cdkeyMemcached game memcached server is work!"<<endl;
	}else{
		cout<<"[XHM MSG] cdkeyMemcached game memcached server isn't work!"<<endl;
		return false;
	} 
	
	return true;
}

MyMemcache::MyMemcache(char* server_ip, int server_port)
{
    memc_s = memcached_create(NULL);
    server_list = NULL;
    expiration = 0;
    flags = 0;
    //	ip和端口将通过Mem_configure提供
    //	first append server to memcached_server_list ,the first argument is  NULL
	server_list = memcached_server_list_append(server_list,server_ip,server_port,&rc);    
    if(rc == MEMCACHED_FAILURE)
    {
        cout<<"adds a server to the memcached_server_list failure"<<endl;
        exit(1);
    }

    //pushes an array of memcached_server_st into the memcached_st struct
    rc = memcached_server_push(memc_s, server_list);
	if(rc == MEMCACHED_FAILURE)
    {
        cout<<"memcached_server_push failure"<<endl;
        exit(1);
    }
//	MyMemcache::show_mem_server_infor();    
	memcached_server_list_free(server_list);

}

//测试缓存服务器是否正常工作
bool test_memcached_server(MyMemcache* my_mem)
{    
    string key = "memcached_test";
    char s[100] = {"----------memcached server is work-----------"};
    bool isSuccess = my_mem->set_mem_data(key, s, strlen(s));
    if(isSuccess != true)
    {
        return false;
    }

	
    int size = 0;
    char* result = my_mem->get_mem_data(key, &size);
    if(result == NULL)
    {
        return false;
    } 
	free(result);
	return true;
}

/*
* author:	Tory
* data	:	2012.9.23
* 传入参数：string类型键值key,用于存储数据data2set至memcached server中，数据大小size
* 返回值:	返回string类型ID，若ID不为空，表示数据存储成功，否则失败
* 注释掉cid()和#include "command_other_function_all_over.h"后测试已通过，Tory 2012.9.23
**/   
char* MyMemcache::add_mem_data(char* data2add, int size)
{
	return NULL; 	// this function no use any more 2012.11.30
}

/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：char*类型键值key,用于存储/修改的数据data2set，数据大小size
* 返回值:	bool值，存储/修改成功，返回true,否则返回false
*/ 
bool MyMemcache::set_mem_data(char* key, char* data2set,int size)
{
    if(data2set == NULL || key == NULL)
    {
		cout<<"data or key is NULL,mem_set is failure"<<endl;
        return false;
    } else
    {
        rc=memcached_set(memc_s, key, strlen(key), data2set, (size_t)size, (time_t)0, (uint32_t)0);
        if(rc == MEMCACHED_FAILURE)
        {
            cout<<"set data to memcached server failure"<<endl;
            return false;
        }
        return true;
    }
} 

/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：string类型键值key,用于修改的数据data2set，数据大小size
* 返回值:	bool值，修改成功，返回true,否则返回false
*/ 
bool MyMemcache::set_mem_data(string key, char* data2set,int size)
{
    if(data2set == NULL || key.empty())
    {
		cout<<"data is NULL or key is empty"<<endl;
        return false;
    } else
    {
        rc=memcached_set(memc_s, key.c_str(), key.size(), data2set, (size_t)size, (time_t)0, (uint32_t)0);
        if(rc == MEMCACHED_FAILURE)
        {
            cout<<"set data to memcached server failure"<<endl;
            return false;
        }
        return true;
    }
}

/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：char*型键值key,用于获取数据大小的指针sz
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/ 
char* MyMemcache::get_mem_data(char* key, int* sz)
{
    if(key == NULL)
	{
		cout<<"get data to memcached server failure,key is empty"<<endl;
		return NULL;
	}
	char* data2get = memcached_get(memc_s, key, strlen(key), &value_length, &flags, &rc);
    if(rc == MEMCACHED_FAILURE || data2get == NULL)
    {
        cout<<"get data from memcached server is failure or data NULL,key:"<<key<<endl;
        return NULL;
    } else
    {
		// cout<<"get data from memcached server Success,key:"<<key<<endl;
        *sz = value_length;     //对传入的指针所指内容赋值
        return data2get;
    }
}

/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：键值key,用于获取得到的数据的字节大小
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/ 
char* MyMemcache::get_mem_data(string key, int* sz)
{
	if(key.empty())
	{
		cout<<"get data to memcached server failure,key is empty"<<endl;
		return NULL;
	}
	char* data2get = memcached_get(memc_s, key.c_str(), key.size(), &value_length, &flags, &rc);
    if(rc == MEMCACHED_FAILURE || data2get == NULL)
    {
        cout<<"get data from memcached server is failure or data NULL,key:"<<key<<endl;
        return NULL;
    } else
    {
		// cout<<"get data from memcached server Success,key:"<<key<<endl;
        *sz = value_length;     //对传入的指针所指内容赋值
        return data2get;
    }
}
/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：键值key,用于获取得到的数据的字节大小
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/
bool MyMemcache::delete_mem_data(string key)
{
	if(key.empty())
	{
		cout<<"delete data from memcached server failure,key is empty"<<endl;
		return false;
	}
    rc = memcached_delete(memc_s,key.c_str(),key_length,(time_t)0);
    if(rc == MEMCACHED_FAILURE)
    {
        cout<<"delete data from memcached server failure"<<endl;
        return false;
    } else
    {
        return true;
    }

}

/*
* author:	Tory
* data	:	2012.9.9
* 传入参数：键值key,用于获取得到的数据的字节大小
* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，同时为传入的int* sz赋上相应大小的值；否则返回NULL
*/
bool MyMemcache::delete_mem_data(char* key)
{
	if(key == NULL)
	{
		return false;
	}
    rc = memcached_delete(memc_s,key,strlen(key),(time_t)0);
    if(rc == MEMCACHED_FAILURE)
    {
        cout<<"delete data from memcached server failure"<<endl;
        return false;
    } 
    
	return true;
   
}

