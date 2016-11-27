#include "baseSocket.h"
#include "baseCmdBuffer.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/tcp.h>

DWORD Socket::s_compressSize = 0;

Socket::Socket(const SWORD sock,const struct sockaddr_in *addr,const bool compress)
{
	m_bitMask = 0;
	assert(sock != -1);
	this->m_sock = sock;
	m_sockChange = 0;
	m_kdpfd = 0;
	bzero(&this->m_addr,sizeof(struct sockaddr_in));
	if(!addr)
	{
		socklen_t len = sizeof(struct sockaddr);
		getpeername(this->m_sock,(struct sockaddr*)&this->m_addr,&len);
	}
	else
	{
		bcopy(addr,&this->m_addr,sizeof(struct sockaddr_in));
	}
	bzero(&m_localAddr,sizeof(struct sockaddr_in));
	socklen_t len = sizeof(struct sockaddr_in);
	getsockname(this->m_sock,(struct sockaddr *)&m_localAddr,&len);
	//设置当生成子进程时，子进程对应的套接口强制关闭
	fcntl(this->m_sock,F_SETFD,fcntl(this->m_sock,F_GETFD,0) | FD_CLOEXEC);
	setNonblock();
	m_rdMsec = s_rdMsec;
	m_wrMsec = s_wrMsec;
	m_recvRawSize = 0;
	m_currentCmd = 0;
	setFlag(s_incompleteRead | s_incompleteWrite);
#if 0
	if(compress)
	{
		m_bitMask |= s_packetZip;
	}
#endif
}

bool Socket::setChangeSocket(const SWORD socket)
{
	m_sockChange = socket;
	return true;
}

bool Socket::changeSocket(const SWORD socket)
{
	m_sock = m_sockChange;
	m_sockChange = 0;
	return true;
}

bool Socket::checkChangeSocket()
{
	return m_sockChange;
}

Socket::~Socket()
{
	Global::logger->debug("关闭套接口连接");
	shutdown(m_sock,SHUT_RDWR);
	TEMP_FAILURE_RETRY(close(m_sock));
	m_sock = -1;
}

DWORD Socket::successUnpack(void *cmd)
{
	DWORD retval = 0;
	//有消息还没有读出来
	CheckConditonReturn(m_recvRawSize >= packetMinSize(),0);
	//理论上消息的长度
	DWORD recordLen = packetSize(m_recvQueue.rdBuffer());
	if(m_recvRawSize >= recordLen)
	{
		retval = packetUnpack(m_recvQueue.rdBuffer(),recordLen,(BYTE*)cmd);
		m_recvQueue.rdFlip(recordLen);
		m_recvRawSize -= recordLen;
	}
	return retval;
}

SWORD Socket::recvToCmd(void *cmd,const bool wait)
{
	SWORD retval = successUnpack(cmd);
	CheckConditonReturn(!retval,retval);
	do
	{
		retval = recvToBuf();
		//套接字出错或者没有接收到数据且不等待
		if(retval == -1 || (!retval && !wait))
		{
			return retval;
		}
		retval = successUnpack(cmd);
		CheckConditonReturn(!retval,retval);	
	}while(true);
	return 0;
}

bool Socket::checkMaxSendSize(const DWORD size)
{
	LogErrorCheckCondition(size <= s_maxDataSize,false,"套接字发送失败数据过大");
	return true;
}

SWORD Socket::sendRawData(const void *pBuffer,const DWORD size)
{
	SWORD retcode = -1;
	if(isSetFlag(s_incompleteWrite))
	{
		clearFlag(s_incompleteWrite);
		goto do_select;
	}
	retcode = TEMP_FAILURE_RETRY(::send(m_sock,pBuffer,size,MSG_NOSIGNAL));
	//套接字出错且阻塞或者再试
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		do_select:
			retcode = waitForWrite();
			CheckConditonReturn(retcode==1,retcode);
			retcode = TEMP_FAILURE_RETRY(::send(m_sock,pBuffer,size,MSG_NOSIGNAL));
	}
	//没有发送完毕
	if(retcode > 0 && retcode < size)
	{
		setFlag(s_incompleteWrite);
	}
	return retcode;
}

bool Socket::sendRawDataIM(const void *pBuffer,const DWORD size)
{
	LogCheckCondition(pBuffer && size,false,"套接字发送消息失败消息非法");
	
	DWORD offset = 0;
	do
	{
		SWORD retcode = sendRawData(&((char*)pBuffer)[offset],size - offset);
		LogCheckCondition(retcode != -1,false,"套接字发送消息失败");
		offset += retcode;
	}while(offset < size);
	return offset == size;
}

bool Socket::sendCmd(const void *cmd,const DWORD cmdLen,const bool buffer)
{
	LogCheckCondition(cmd && cmdLen,false,"套接字发送失败参数不合法");
	bool retval = true;
	StackCmdQueue rawQueue;
	if(buffer)
	{
		packetAppendNoEnc(cmd,cmdLen,rawQueue);
		m_mutex.lock();
		m_sendQueue.put(rawQueue.rdBuffer(),rawQueue.rdSize());
		m_currentCmd = rawQueue.rdSize();
		m_mutex.unlock();
	}
	else
	{
		packetAppend(cmd,cmdLen,rawQueue);
		m_mutex.lock();
		retval = sendRawDataIM(rawQueue.rdBuffer(),rawQueue.rdSize());
		m_currentCmd = rawQueue.rdSize();
		m_mutex.unlock();
	}
	return retval;
}

bool Socket::sendCmdNoPack(const void *cmd,const DWORD cmdLen,const bool buffer)
{
	LogCheckCondition(cmd && cmdLen,false,"套接字发送数据非法");
	bool retval = false;
	if(buffer)
	{
		m_mutex.lock();
		m_sendQueue.put((BYTE*)cmd,cmdLen);
		m_currentCmd = cmdLen;
		m_mutex.unlock();
	}
	else
	{
		m_mutex.lock();
		retval = sendRawDataIM(cmd,cmdLen);
		m_mutex.unlock();
	}
	return retval;
}

bool Socket::sync()
{
	CheckConditonReturn(m_sendQueue.rdReady(),true);
	m_mutex.lock();
	bool ret = sendRawDataIM(m_sendQueue.rdBuffer(),m_sendQueue.rdSize());
	m_currentCmd = m_sendQueue.rdSize();
	m_sendQueue.reset();
	m_mutex.unlock();
	return ret;

#if 0
	DWORD size = 0,offset = 0;
	m_mutex.lock();
	if(m_bufferQueue.rdReady())
	{
		BUFFER_CMD(Cmd::DataSendCmd,send,s_maxDataSize + 4);
		bcopy(m_bufferQueue.rdBuffer(),send->data,m_bufferQueue.rdSize());
		send->dwSize = m_bufferQueue.rdSize();
		m_bufferQueue.reset();
		StackCmdQueue rawQueue;
		m_mutex.unlock();
		if(*(DWORD*)send->data + sizeof(s_packHeadLen) < send->datasize())
		{
			packetAppendNoEnc(send,send->allsize(),rawQueue);
			m_mutex.lock();
			m_sendQueue.put(rawQueue.rdBuffer(),rawQueue.rdSize());
			m_currentCmd = rawQueue.rdSize();
		}
		else
		{
			m_mutex.lock();
			m_sendQueue.put((const BYTE*)send->data,send->datasize());
			m_currentCmd = send->datasize();
		}
		if(m_sendQueue.rdReady())
		{
			size = m_sendQueue.rdSize();
			m_currentCmd = size;
			offset = m_encQueue.rdSize();
			//暂时加密buffer还没用到
			m_encQueue.put(m_sendQueue.rdBuffer(),size);
			m_sendQueue.rdFlip(size);
			m_currentCmd = 0;
		}
	}
	m_mutex.unlock();
	if(m_encQueue.rdReady())
	{
		SWORD retcode = sendRawDataNoPoll(m_encQueue.rdBuffer(),m_encQueue.rdSize());
		if(retcode > 0)
		{
			m_encQueue.rdFlip(retcode);
		}
		else if(retcode == -1)
		{
			return false;
		}
	}
	return true;
#endif
}
void Socket::forceSync()
{
	CheckConditonVoid(m_sendQueue.rdReady());
	m_mutex.lock();
	sendRawDataIM(m_sendQueue.rdBuffer(),m_sendQueue.rdSize());
	m_currentCmd = m_sendQueue.rdSize();
	m_sendQueue.reset();
	m_mutex.unlock();
	return;

#if 0
	DWORD size = 0,offset = 0;
	m_mutex.lock();
	if(m_bufferQueue.rdReady())
	{
		BUFFER_CMD(Cmd::DataSendCmd,send,s_maxDataSize + 4);
		bcopy(m_bufferQueue.rdBuffer(),send->data,m_bufferQueue.rdSize());
		send->dwSize = m_bufferQueue.rdSize();
		m_bufferQueue.reset();
		m_mutex.unlock();
		StackCmdQueue rawQueue;
		if(*(DWORD*)send->data + sizeof(s_packHeadLen) < send->datasize())
		{
			packetAppendNoEnc(send,send->allsize(),rawQueue);
			m_mutex.lock();
			m_sendQueue.put(rawQueue.rdBuffer(),rawQueue.rdSize());
			m_currentCmd = rawQueue.rdSize();
		}
		else
		{
			m_mutex.lock();
			m_sendQueue.put((const BYTE*)send->data,send->datasize());
			m_currentCmd = send->datasize();
			offset = m_encQueue.rdSize();
			m_encQueue.put(m_sendQueue.rdBuffer(),size);
			m_sendQueue.rdFlip(size);
			m_currentCmd = 0;
		}
	}
	m_mutex.unlock();
	if(m_encQueue.rdReady())
	{
		sendRawDataIM(m_encQueue.rdBuffer(),m_encQueue.rdSize());
		m_encQueue.reset();
	}
#endif
}

const char* Socket::getIPByIfName(const char *ifName)
{
	static const char *none_ip = "127.0.0.1";
	return none_ip;

	LogErrorCheckCondition(ifName,none_ip,"获取本地ip地址失败参数为空");

	int ret = socket(AF_INET,SOCK_DGRAM,0);
	LogErrorCheckCondition(ret!=-1,none_ip,"获取本地ip地址失败%s",ifName);

	struct ifreq ifr;
	bzero(ifr.ifr_name,sizeof(ifr.ifr_name));
	strncpy(ifr.ifr_name,ifName,sizeof(ifr.ifr_name) - 1);
	if(ioctl( ret,SIOCGIFADDR,&ifr ) == -1)
	{
		TEMP_FAILURE_RETRY( ::close(ret) );
		return none_ip;
	}
	TEMP_FAILURE_RETRY( ::close(ret) );
	return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);
}

void Socket::successRecv(const DWORD retcode)
{
	/// 消息队列还有空
	if(retcode < m_recvQueue.wrSize())
	{
		setFlag(s_incompleteRead);
	}
	m_recvQueue.wrFlip(retcode);
	m_recvRawSize += retcode;
}

SWORD Socket::recvToBufNoPoll()
{
	m_recvQueue.wrReserve(s_maxDataBufferSize);
	SWORD retcode = TEMP_FAILURE_RETRY(::recv(m_sock,m_recvQueue.wrBuffer(),m_recvQueue.wrSize(),MSG_NOSIGNAL));
	//如果套接字出错，且阻塞或者尝试
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		return 0;
	}
	else if(retcode > 0)
	{
		successRecv(retcode);
	}
	return retcode;
}

DWORD Socket::recvToCmdNoPoll(void *cmd)
{
	return successUnpack(cmd);
}

SWORD Socket::sendRawDataNoPoll(const void *pBuffer,const DWORD size)
{
	SWORD retcode = TEMP_FAILURE_RETRY(::send(m_sock,pBuffer,size,MSG_NOSIGNAL));
	//如果套接字异常，且为阻塞或者再试
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		return 0;
	}
	//没有发送完毕
	else if(retcode > 0 && retcode < size)
	{
		setFlag(s_incompleteWrite);
	}
	return retcode;
}

bool Socket::setNonblock()
{
	SWORD fdFlags,nodelay = 1;
	//设置不延时发送
	if(setsockopt(m_sock,IPPROTO_TCP,TCP_NODELAY,(void*)&nodelay,sizeof(nodelay)))
	{
		return false;
	}
	//设置套接口为非阻塞
	fdFlags = fcntl(m_sock,F_GETFL,0);
	#if defined(O_NONBLOCK)
		fdFlags |= O_NONBLOCK;
	#elif defined(O_NDELAY)
		fdFlags |= O_NDELAY;
	#elif defined(FNDELAY)
		fdFlags |= O_FNDELAY;
	#else
		return false;
	#endif
	if(fcntl(m_sock,F_SETFL,fdFlags) == -1)
	{
		return false;
	}
	return true;
}

SWORD Socket::waitForRead()
{
	struct pollfd pfd;
	pfd.fd = m_sock;
	pfd.events = POLLIN | POLLERR | POLLPRI;
	pfd.revents = 0;

	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,m_rdMsec));
	//套接字异常
	if(retcode > 0 && !(pfd.revents & POLLIN))
	{
		retcode = -1;
	}
	return retcode;
}

SWORD Socket::waitForWrite()
{
	struct pollfd pfd;
	pfd.fd = m_sock;
	pfd.events = POLLOUT | POLLERR | POLLPRI;
	pfd.revents = 0;
	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,m_wrMsec));
	//套接字异常
	if(retcode > 0 && !(pfd.revents & POLLOUT))
	{
		retcode = -1;
	}
	return retcode;
}

SWORD Socket::recvToBuf()
{
	SWORD retcode = 0;
	if(isSetFlag(s_incompleteRead))
	{
		clearFlag(s_incompleteRead);
		goto do_select;
	}
	m_recvQueue.wrReserve(s_maxDataBufferSize);
	retcode = TEMP_FAILURE_RETRY(::recv(m_sock,m_recvQueue.wrBuffer(),m_recvQueue.wrSize(),MSG_NOSIGNAL));
	
	/// 如果出错，且阻塞或者再次尝试
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		do_select:
			retcode = waitForRead();
			CheckConditonReturn(retcode==1,retcode);
			retcode = TEMP_FAILURE_RETRY(::recv(m_sock,m_recvQueue.wrBuffer(),m_recvQueue.wrSize(),MSG_NOSIGNAL));
	}
	if(retcode > 0)
	{
		successRecv(retcode);
	}
	return retcode;
}

DWORD Socket::packetUnpack(BYTE *in,const DWORD packetLen,BYTE *out)
{
	///去掉4字节的消息头
	DWORD recvCmdLen = packetLen - s_packHeadLen;
	bcopy(&(in[s_packHeadLen]),out,recvCmdLen);
	return recvCmdLen;
}

DWORD Socket::getMaxDataSize() const
{
	return s_maxDataSize;
}
