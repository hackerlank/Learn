/**********************************************
* author:	Tory
* data	:	2012.9.9
* Description:用于创建与memcached server交互的memcached_st* memc；
* @@@@@@@@@@@ 并提供操作memcached server连接和memcached server的数据交互功能
************************************************/ 
#ifndef MYMEMCACHED_H_
#define MYMEMCACHED_H_

#include <iostream>
#include <string.h>
#include <libmemcached/memcached.h>

using namespace std;

//memcached server 配置数据
typedef struct mem_configure
{
	char server_ip[20]; 		//memcached server ip
	int  server_port;			//memcached server port
	mem_configure(char* ip, int port)
	{
		memset(server_ip, 0, 20);
		if(ip != NULL) 
		{
			strncpy(server_ip, ip, 20);
		}
		server_port = port;
	}
}Mem_configure;

bool initMyMemcached();

bool initCdKeyCached();

class MyMemcache
{
	public:
	//	MyMemcache(vector<Mem_configure> server_config_array)
		MyMemcache(char* server_ip, int server_port);
		
		void show_mem_server_infor()
		{
			cout<<"server_list_count:"<<(int)memcached_server_list_count(server_list)<<endl;
			cout<<"server_count:"<<(int)memcached_server_count(memc_s)<<endl;
		}
		/************************************************
		* 传入参数：用于存储数据data2set，数据大小size
		* 返回值:	返回string类型ID，若ID不为空，表示数据存储成功，否则失败
		************************************************/ 		
		char* add_mem_data(char* data2add, int size);
		
		/************************************************
		* 传入参数：键值key,用于修改的数据data2set，数据大小size
		* 返回值:	bool值，修改成功，返回true,否则返回false
		************************************************/ 
		bool set_mem_data(string key, char* data2set, int size);
		bool set_mem_data(char* key, char* data2set,int size);

		/************************************************
		* 传入参数：键值key,用于存储/修改的数据data2set，数据大小size
		* 返回值:	bool值，存储/修改成功，返回true,否则返回false
		************************************************/ 
		bool delete_mem_data(string key);
		bool delete_mem_data(char* key);
		/**********************************************
		* 传入参数：键值key,用于获取得到的数据的字节大小
		* 返回值:	若数据获取成功，根据键值获得的char*型数据指针，
		* @@@@@@@	同时为传入的int* sz赋上相应大小的值；否则返回NULL
		************************************************/
		char* get_mem_data(string key, int* sz);
		char* get_mem_data(char* key, int* sz);
	private:
		memcached_st* 				memc_s;		//be used by other libmemcached(3) functions to communicate with the server.用于其他memcached的C函数接口与memcached server交互
		memcached_server_list_st 	server_list;//memcached_server_st* was aliased to memcached_server_list_st.0.39版本后，memcached_server_list_st便是memcached_server_st的别名
		memcached_return_t 			rc;			//to hold any error
		
		size_t 		key_length;					//用于memcached_set时，作为键长值传入
		size_t 		value_length;				//用于memcached_get时，来标识获取到的值的大小
		time_t 		expiration;					//过期时间
		uint32_t 	flags;		
};
//测试缓存服务器是否正常工作
bool test_memcached_server(MyMemcache* my_mem);
#endif
