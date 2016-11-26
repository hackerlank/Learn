/*
		文件类型：头文件
		文件名称：chat.h
		文件作用：声明聊天函数动作；
*/

#ifndef _CHAT_
#define _CHAT_

#include"command_other_function_all_over.h"
#include"hero.h"
#include<map>
#include<vector>

class Hero;
class ChatGroup;
void advertise(char* buffer);

void whisper(char* buffer);

void handsel_flowers(char *buffers);

void find_hero_by_nickName(char *buffers);

void whisperAfter(char* buffer);

//退出群,不需要任何人同意
void outGroup(char *buffers);

//回应邀请进群
void responsePullPerson(char *buffers);

//邀请进群
void pullPerson(char *buffers);

//邀请进群
void pullPersonByNickName(char *buffers);

//邀请进群辅助函数
void asistPull(const Hero* inviter,const ChatGroup* chat,const int type,const vector<string> &pulledIdVec);

//客户端点击面板前的交互，为了设置面板的id
void offNewGroupId(char *buffers);

//获取基本数据
void gainMsgById(char *buff);

#endif
