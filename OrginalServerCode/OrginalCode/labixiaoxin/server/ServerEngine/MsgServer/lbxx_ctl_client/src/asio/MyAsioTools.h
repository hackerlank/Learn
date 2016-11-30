#ifndef __MYASIOTOOLS_H_
#define __MYASIOTOOLS_H_
#include <string>
#include <vector>
#include <boost\smart_ptr\scoped_array.hpp>
#include "..\data\GameDefine.h"

#define MAX_RESERVE_SIZE 1024*8  //最大接收尺寸
#define MAX_HEAD_LEN sizeof(MY_UINT32) 
class CMyAsioTools
{
public:
	CMyAsioTools();
public:
	MY_UINT32 Serializing(const MsgInfo & msg,boost::scoped_array<char> & _dir);//序列化
	std::vector<MsgInfo> UnSerializing(const char * data, int size);//反序列化
private:
	bool UnSerializingMsg(boost::scoped_array<char> & _src,int size,MsgInfo & info);
	char _Data[2*MAX_RESERVE_SIZE];
	int _len;
protected:
	void writeUInt(void * _dir ,MY_UINT32 v,MY_UINT32 & offset);
	void writeInt(void * _dir ,int v,MY_UINT32 & offset);
	void writeString(void * _dir,const void * _src,MY_UINT32 len,MY_UINT32 & offset);

	void ReadUInt(void * _dir ,const void * _src,MY_UINT32 & offset);
	void ReadString(void * _dir,const void * _src,MY_UINT32 len,MY_UINT32 & offset);
	void Rmemcpy(void * _Dst, const void * _Src, size_t _Size);
};
#endif