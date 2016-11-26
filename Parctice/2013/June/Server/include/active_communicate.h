/*
		文件类型：实现文件
		文件名称：active_communicate.h"
		文件作用：活动客户端和服务器交互处理函数；
		修改人：chenzhen
		修改时间：2012.10.24
*/
#ifndef ACTIVE_COMMIMUCATION_H
#define ACTIVE_COMMIMUCATION_H
void activeAccept(char *buffers);
void takePartActive(char *buffers);

/*激活码的交互*/
void acceptActiveCode(char *buffers);

//解析从cdkey Server返回的消息
void acceptCdkeySrvSuccess(char *buffer);

//解析从cdkey Server返回的消息
void acceptCdkeySrv(char *buffer);

#endif