#include "basePthread.h"
/*
ThreadGroup::ThreadGroup():threadVec(),rwlock()
{
}

ThreadGroup::~ThreadGroup()
{
	joinAll();
}

void ThreadGroup::add(Thread *thread)
{
	RWLock_scope_wrlock scope_wrlock(rwlock);
	Vec_it it = std::find(threadVec.begin(),threadVec.end(),thread);
	if(it == threadVec.end())
	{
		threadVec.push_back(thread);
	}
}

Thread* ThreadGroup::getByIndex(const thread_t index){
	RWLock_scope_wrlock scope_wrlock(rwlock);
	if(index >= threadVec.size()) return NULL;
	return threadVec[index];
}

Thread* ThreadGroup::operator[](const thread_t index)
{
	RWLock_scope_wrlock scope_wrlock(rwlock);
	if(index >= threadVec.size()) return NULL;
	return threadVec[index];
}

void ThreadGroup::joinAll()
{
	RWLock_scope_wrlock scope_wrlock(rwlock);
	while(!threadVec.empty())
	{
		Thread *thread = threadVec.back();
		threadVec.pop_back();
		if(thread)
		{
			thread->final();
			thread->join();
			DELETE(thread);
		}
	}
}

void ThreadGroup::execAll(Callback &cb)
{
	RWLock_scope_rdlock scope_rdlock(rwlock);
	for(Vec_it it = threadVec.begin();it != threadVec.end();++it)
	{
		cb.exec(*it);
	}
}

*/
