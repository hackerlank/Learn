/********************************************************************
	创建时间：	2014/08/15  16:26:54 
	文件名：		MyQueue.h
	作者：		谢小军
	
	功能：		1. 线程安全队列
				2.
				
	说明：	    1. 多线程状态下的安全队列
				2. 
*********************************************************************/
#ifndef MYQUEUE_H_
#define MYQUEUE_H_
#include <queue>//std queue
#include <vector>
//#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

template<typename TYPE>
class CMyQueue
{
private:
	std::queue<TYPE> theQueue_;
	boost::mutex m_oMutex;
	boost::condition_variable_any m_cond;//条件变量
public:
	CMyQueue(){};
	~CMyQueue(){};
public:
	void Dequeue(std::vector<TYPE> & ver);
	TYPE Dequeue();//条件变量得到一个消息
	void Enqueue(const TYPE & e);//插入一个元素
protected:
// 	TYPE pop();//出一个队列
// 	void push( const TYPE &val );//压入一个队列
	size_t size();//队列长度
	bool empty();//判空
};


template<typename TYPE>
size_t CMyQueue<TYPE>::size()
{
	//boost::mutex::scoped_lock oLock(m_oMutex);//互斥锁
	//	size_t size=theQueue_.size();
	return theQueue_.size();
}

template<typename TYPE>
bool CMyQueue<TYPE>::empty()
{
	//boost::mutex::scoped_lock oLock(m_oMutex);//互斥锁
	return theQueue_.empty();
}

template<typename TYPE>
TYPE CMyQueue<TYPE>::Dequeue()
{
	boost::mutex::scoped_lock oLock(m_oMutex);//互斥锁
	while(theQueue_.empty())//必须循环，必须在判断之后再wait()
	{
		m_cond.wait(m_oMutex);//会原子性的unlock m_oMutex 并进入等待
		//wait执行完毕之后会自动重现加锁
	}

	assert(!theQueue_.empty());

	TYPE tmp = theQueue_.front();
	theQueue_.pop();
	return tmp;
}

template<typename TYPE>
void CMyQueue<TYPE>::Dequeue( std::vector<TYPE> & ver )
{
	boost::mutex::scoped_lock oLock(m_oMutex);//互斥锁
	while(theQueue_.empty())//必须循环，必须在判断之后再wait()
	{
		m_cond.wait(m_oMutex);//会原子性的unlock m_oMutex 并进入等待
		//wait执行完毕之后会自动重现加锁
	}

	assert(!theQueue_.empty());

	ver.clear();
	int n =0 ;
	while(!theQueue_.empty() && n < MAX_SEND_COUNT)
	{
		ver.push_back(theQueue_.front());
		theQueue_.pop();
		++n;
	}
}

template<typename TYPE>
void CMyQueue<TYPE>::Enqueue(const TYPE & e )
{
	{
		boost::mutex::scoped_lock oLock(m_oMutex);//互斥锁
		theQueue_.push(e);
	}

	m_cond.notify_one();//提示一个开启
}

#endif