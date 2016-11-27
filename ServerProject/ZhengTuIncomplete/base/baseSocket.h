#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H
#include <sys/epoll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <errno.h>
#include "common/baseDef.h"
#include "baseClass.h"
#include "baseMsgContainer.h"
#include "global.h"

class Socket : private Noncopyable
{
	public:
		static const char* getIPByIfName(const char *ifName);
		bool checkChangeSocket();
		DWORD getMaxDataSize() const;
		bool setChangeSocket(const SWORD sock);
		bool changeSocket(const SWORD sock);
		bool checkMaxSendSize(const DWORD size);
		const SWORD getSocket()
		{
			return m_sock;
		}
		Socket(const SWORD sock,const struct sockaddr_in *addr = NULL,const bool compress = false);
		~Socket();
		inline const char* getIP() const
		{
			return inet_ntoa(m_addr.sin_addr);
		}
		inline const DWORD getAddr() const
		{
			return m_addr.sin_addr.s_addr;
		}
		inline const WORD getPort() const
		{
			return ntohs(m_addr.sin_port);
		}
		inline const char* getLocalIP() const
		{
			return inet_ntoa(m_localAddr.sin_addr);
		}
		inline const WORD getLocalPort() const
		{
			return ntohs(m_localAddr.sin_port);
		}
	public:
		inline void delEpoll(SWORD kdpfd,const DWORD events)
		{
			m_mutex.lock();
			m_ev.events = events;
			if(epoll_ctl(kdpfd,EPOLL_CTL_DEL,m_sock,&m_ev) == -1)
			{
				char buffer[100] = {0};
				strerror_r(errno,buffer,sizeof(buffer));
			}
			m_mutex.unlock();
		}

		inline void addEpoll(SWORD kdpfd,const DWORD events,void *ptr)
		{
			m_mutex.lock();
			m_kdpfd = kdpfd;
			m_ev.events = events;
			m_ev.data.ptr = ptr;
			if(epoll_ctl(kdpfd,EPOLL_CTL_ADD,m_sock,&m_ev) == -1)
			{
				char buffer[100] = {0};
				strerror_r(errno,buffer,sizeof(buffer));
			}
			m_mutex.unlock();
		}
	
		inline void fillPollFd(struct pollfd& pfd,const WORD events)
		{
			pfd.fd = m_sock;
			pfd.events = events;
			pfd.revents = 0;
		}
	
		/// @brief 强制同步数据发送出去
		void forceSync();
		/// @brief 同步一下缓存中的数据发送出去
		bool sync();
		/// @brief 发送数据（可以缓存或者及时发送)
		bool sendCmdNoPack(const void *cmd,const DWORD CmdLen,const bool bufer = false);

		/// @brief 发送数据（及时或者缓存)
		bool sendCmd(const void *pstrCmd,const DWORD nLen,const bool buffer = false);
		
		/// @brief 等待套接字是否可读
		//返回值 0:表示不可读 -1:表示套接字异常
		//其他:表示套接字可读
		inline SWORD waitForRead();
		/// @brief 立即接收消息且保存在消息队列中
		//返回值-1:表示套接字出错 0:表示没有接受到
		//消息,其他:表示接收到的长度
		SWORD recvToBufNoPoll();
		/// @brief 单纯的从消息队列中取出消息
		//返回值 表示取出的消息的长度
		DWORD recvToCmdNoPoll(void *cmd);
		/// @brief 接收消息到cmd中,参数wait表示等待
		//，直到有返回结果(-1:表示套接字异常，大于0
		//:表示接受的字符),如果不等待,那么可能返回0
		//表示没有接收到数据
		SWORD recvToCmd(void *cmd,const bool wait);
	private:
		bool setNonblock();
		inline DWORD packetSize(const BYTE *in) const
		{
			return s_packHeadLen + (*(DWORD*)in) & s_packetMask;
		}
		inline DWORD packetMinSize() const
		{
			return s_packHeadLen;
		}
		inline void clearFlag(const DWORD flag)
		{
			m_bitMask &= ~flag;
		}
		inline bool isSetFlag(const DWORD flag) const
		{
			return m_bitMask & flag;
		}	

		inline void setFlag(const DWORD flg)
		{
			m_bitMask |= flg;
		}

		/// @brief 把数据复制到cmdQueue且不压缩
		//返回值 复制数据的长度
		template<typename BufferType>
		DWORD packetPackNoZip(const void *pData,const DWORD len,BufferType &cmdQueue);
		
		/// @brief 把数据存储到cmdQueue中(可能压缩)
		//返回值 存储在cmdQueue的数据长度
		template<typename BufferType>
		DWORD packetAppend(const void *pData,const DWORD len,BufferType& cmdQueue);
		
		/// @brief 把数据存储到cmdQueue中(可能压缩）
		//返回值 存储在cmdQueue的数据长度
		template<typename BufferType>
		DWORD packetAppendNoEnc(const void *pData,const DWORD len,BufferType& cmdQueue);
		
		/// @brief 打包压缩数据（暂时先关闭压缩功能)
		// 返回值 压缩后的数据大小
		template<typename BufferType>
		DWORD packetPackZip(const void *pData,const DWORD len,BufferType& cmdQueue,const bool compress = false);

		/// @brief 判断是否发送完数据
		//返回值 真:数据完全发送完毕
		inline bool sendRawDataIM(const void *pBuffer,const DWORD size);
		/// @brief 等待发送数据
		//返回值 -1:套接字异常 0:发送阻塞 其他:发送
		//数据的长度
		inline SWORD sendRawData(const void *pBuffer,const DWORD size);
		/// @brief 立即发送数据
		//返回值 -1:套接字出错 0:发送阻塞 其他:发送
		//的字节数
		SWORD sendRawDataNoPoll(const void *pBuffer,const DWORD size);
		/// @brief 把in的消息中的消息长度拷贝到out中
		//返回值为拷贝的消息长度
		DWORD packetUnpack(BYTE *in,const DWORD packerLen,BYTE *out);
		
		/// @brief 等待套接字是否可写
		//返回值 0:表示不可读 -1:表示套接字异常
		//其他:表示套接字可写
		inline SWORD waitForWrite();

		/// @brief 等待且接收消息到消息队列中
		// 返回值 0:没有任何数据 -1:套接口出错 其他：
		// 接受到了数据
		inline SWORD recvToBuf();
	
		/// @成功接收消息后的一些处理
		void successRecv(const DWORD retcode);
		
		/// @brief 从解析好的消息队列中拷贝到参数中
		//返回值 0：表示没有消息 其他表示消息的长度
		DWORD successUnpack(void *cmd);
	private:
		
		//套接字读取数据时间
		static const DWORD s_rdMsec = 2100;
		//套接字写数据时间
		static const DWORD s_wrMsec = 5100;
		//数据头长度
		static const DWORD s_packHeadLen = sizeof(DWORD);
		//压缩标志
		static const DWORD s_packetZip = 0x40000000;
		//读取没彻底完成标志
		static const DWORD s_incompleteRead = 0X00000001;
		//写没彻底完成标志
		static const DWORD s_incompleteWrite = 0X00000002;
		static const DWORD s_packetMask = trunkSize - 1;
		static const DWORD s_maxDataBufferSize = s_packetMask;
		
		///套接口压缩的所有数据大小
		static DWORD s_compressSize;
		//套接字
		SWORD m_sock;
		SWORD m_sockChange;
		SWORD m_kdpfd;
		struct epoll_event m_ev;
		struct sockaddr_in m_addr;
		struct sockaddr_in m_localAddr;
		DWORD m_rdMsec;
		DWORD m_wrMsec;
		BufferCmdQueue m_recvQueue;
		DWORD m_recvRawSize;
		BufferCmdQueue m_bufferQueue;
		//发送消息的buffer
		BufferCmdQueue m_sendQueue;
		//加密消息的buffer
		BufferCmdQueue m_encQueue;
		//最后一次发送数据的长度
		DWORD m_currentCmd;
		Mutex m_mutex;
		DWORD m_bitMask;
	public:
		//发送数据最大长度
		 static const DWORD s_maxDataSize = s_maxDataBufferSize - s_packHeadLen;
		
};

template<typename BufferType>
DWORD Socket::packetAppendNoEnc(const void *pData,const DWORD len,BufferType& cmdQueue)
{
	return packetPackZip<BufferType>(pData,len,cmdQueue,s_packetZip == (m_bitMask & s_packetZip));
}
template<typename BufferType>
DWORD Socket::packetAppend(const void *pData,const DWORD len,BufferType& cmdQueue)
{
	DWORD size = packetPackZip(pData,len,cmdQueue,s_packetZip == (m_bitMask & s_packetZip));
	return size;
}

template<typename BufferType>
DWORD Socket::packetPackNoZip(const void *pData,const DWORD len,BufferType& cmdQueue)
{
	DWORD size = len > getMaxDataSize() ? getMaxDataSize() : len;
	cmdQueue.wrReserve(size + s_packHeadLen);
	bcopy(pData,&(cmdQueue.wrBuffer()[s_packHeadLen]),size);
	(*(DWORD*)cmdQueue.wrBuffer()) = size;
	cmdQueue.wrFlip(size + s_packHeadLen);
	return size + s_packHeadLen;
}
template<typename BufferType>
DWORD Socket::packetPackZip(const void *pData,const DWORD len,BufferType& cmdQueue,const bool compress)
{
	DWORD size = len > getMaxDataSize() ? getMaxDataSize() : len;
	s_compressSize += size;
	cmdQueue.wrReserve(size + s_packHeadLen);
	bcopy(pData,&(cmdQueue.wrBuffer()[s_packHeadLen]),size);
	(*(DWORD*)cmdQueue.wrBuffer()) = size;
	cmdQueue.wrFlip(size + s_packHeadLen);
	return size + s_packHeadLen;
}
#endif
