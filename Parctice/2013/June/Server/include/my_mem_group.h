#ifndef MY_MEM_GROUP_
#define MY_MEM_GROUP_

#include <map>
#include <string>
using namespace std;

class MyMemcache;		//预先声明缓存操作类
bool initMyMemGroup();	//服务器启动时，用于初始化缓存服务器列表对象

/* 缓存服务器管理类 tory 2013.3.13 */
class MyMemGroup
{
	public:
		MyMemGroup();
		~MyMemGroup();

		//根据key值和zone_index,从指定缓存服务器获取数据,sz和where分别表示数据的大小和来源;若zone_index缺省则默认为-1，表示从任意一台缓存服务器获取数据
		char* get_data(string mem_key, int*sz, int*where, int zone_index=-1);
		char* get_data(char* mem_key, int*sz, int*where, int zone_index=-1);
		
		// 根据key值，将数据存储至指定缓存服务器
		bool set_data(string key, char* data2set, int size, int zone_index);
		bool set_data(char* key, char* data2set, int size, int zone_index);
		
		// 根据key值，从指定缓存服务器删除数据
		bool delete_data(string key, int zone_index);
		bool delete_data(char* key, int zone_index);

	public:
		int		number;							//连接的缓存服务器的数目

	private:
		map<int,MyMemcache*>	mem_server_map;	//缓存服务器操作对象容器，用于对不同区的DB数据进行访问和修改
};

#endif