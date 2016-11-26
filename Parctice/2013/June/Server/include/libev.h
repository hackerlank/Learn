/*
* 文件名称：libev.h
* 文件作用：网络IO驱动
*/
#ifndef LIBEV_H
#define LIBEV_H	
#include"my_timer.h"

using namespace std;

//给每个连接的消息缓存结构体，用于标识和装载不完整的消息
typedef struct _Message_Receive
{
	char	ip_str[16];					//fd对应的IP
	struct bufferevent*  io_watcher;	//io监听
	unsigned char 	t;					//XOR key

    _Message_Receive()
    {
		memset(ip_str, 0, 16);
		io_watcher = NULL;
    }
}Message_Receive;


void run_loop(int port);

void closeConnect(int fd);

void event_cb(struct bufferevent *bev, short what, void *arg);

bool write_log(char* buffer);

bool con_recharge_server();//链接充值服务器；

bool con_cdkey_server();		//初始化cdkey服务器函数
#endif
