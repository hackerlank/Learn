#ifndef BASE_PTHREAD_H
#define BASE_PTHREAD_H
#include <signal.h>

/*
class ThreadGroup : private Noncopyable
{
	public:
		struct Callback
		{
			virtual void exec(Thread *e) = 0;
			virtual ~Callback() {};
		};

		typedef std::vector<Thread*> ThreadVec;
		typedef ThreadVec::size_type thread_t;
		typedef ThreadVec::iterator Vec_it;
		ThreadGroup();
		~ThreadGroup();

		void add(Thread *thread);
		Thread* getByIndex(const thread_t index);
		Thread* operator[](const thread_t index);
		void joinAll();
		void execAll(Callback &cb);
		const thread_t size()
		{
			RWLock_scope_rdlock scope_rdlock(rwlock);
			return threadVec.size();
		}

	private:
		ThreadVec threadVec;
		RWLock rwlock;
};
*/		
#endif
