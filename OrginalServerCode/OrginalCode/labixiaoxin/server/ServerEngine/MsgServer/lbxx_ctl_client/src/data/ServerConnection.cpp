#include "ServerConnection.h"

//DECLARE_SINGLETON_MEMBER(CServerConnectionData);

void CServerConnectionData::AddOneConnection( const Session_ptr & _ptr )
{
	//boost::mutex::scoped_lock writeLock(m_rw_mutex);//写锁 非递归锁(不可重入锁)
	boost::unique_lock<boost::shared_mutex> writeLock(m_rw_mutex);//写锁
	m_verConnection.push_back(_ptr);
	std::cout<<"connetc number:"<<m_verConnection.size()<<std::endl;
}

bool CServerConnectionData::DeleteOneConnection( Session_ptr & _ptr )
{
	boost::unique_lock<boost::shared_mutex> writeLock(m_rw_mutex);//写锁
	std::vector<Session_ptr>::iterator it = m_verConnection.begin();
	while(it != m_verConnection.end())
	{
		if (*it == _ptr)
		{
			it = m_verConnection.erase(it);
			return true ;
		}
		++it;
	}

	return false;
}

void CServerConnectionData::SendAllMessage( MsgInfo & info )
{
	CMyAsioTools tools;
	boost::scoped_array<char> _buffer;
	MY_UINT32 len = tools.Serializing(info,_buffer);

	boost::shared_lock<boost::shared_mutex> readLock(m_rw_mutex);
	std::vector<Session_ptr>::iterator it = m_verConnection.begin();
	while(it != m_verConnection.end())
	{
		(*it)->OnSend(_buffer,len);
		
		it++;
	}

	std::cout<<"send count:"<<m_verConnection.size()<<std::endl;
}