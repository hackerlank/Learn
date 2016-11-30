/*
filename: debugnew.h

This code is based on code retrieved from a web site. The
author was not identified, so thanks go to anonymous.

This is used to substitute a version of the new operator that
can be used for debugging memory leaks. To use it:

- In any (all?) code files #include debugnew.h. Make sure all
system files (i.e. those in <>'s) are #included before
debugnew.h, and that any header files for your own code
are #included after debugnew.h. The reason is that some
system files refer to ::new, and this will not compile
if debugnew is in effect. You may still have problems
if any of your own code refers to ::new, or if any
of your own files #include system files that use ::new
and which have not already been #included before
debugnew.h.
- Add debugnew.cpp to the CodeWarrior project or compile
it into your Linux executable. If debugnew.cpp is in the
project, then debugnew.h must be #included in at least
one source file
*/

#ifndef __DEBUGNEW_1H__
#define __DEBUGNEW_1H__

//#define DEBUGNEW_CPP

#if _MEMORY_DEBUG
#include <map>

#define LOG_FILE

#if defined(LOG_FILE)
#define LOG_FILE_NAME "./GatWayDebugnew.log"
#endif

void* operator new (std::size_t size, const char* file, int line);
void operator delete (void* p, const char* name, int line);
void* operator new [] (std::size_t size, const char* file, int line);
void operator delete [] (void* p, const char* name, int line);

class DebugNewTracer  {
private:

	class Entry  {
	public:
		Entry (char const* file, int line) : _file (file), _line (line) {}
		Entry (char const* file, int line, int size) : _file (file), _line (line), _size (size) {}
		Entry () : _file (0), _line (0), _size (0) {}
		const char* File () const { return _file; }
		int Line () const { return _line; }
		size_t Size () const { return _size; }
	private:
		char const* _file;
		int _line;
		size_t _size;
	};

	class Lock {
	public:
		Lock (DebugNewTracer & DebugNewTracer) : _DebugNewTracer (DebugNewTracer) {
			_DebugNewTracer.lock ();
		}
		~Lock () {
			_DebugNewTracer.unlock ();
		}
	private:
		DebugNewTracer & _DebugNewTracer;
	};
	typedef std::map<void*, Entry>::iterator iterator;
	friend class Lock;
public:
	DebugNewTracer ();
	~DebugNewTracer ();
	void Add (void* p, const char* file, int line);
	void Add (void* p, const char* file, int line, size_t size);
	void Remove (void* p);
	void Dump ();

	static bool Ready;

private:
	void lock () { _lockCount++; }
	void unlock () { _lockCount--; }

private:

	std::map<void*, Entry> _map;
	int _lockCount;
	size_t _totalsize;
#if defined(LOG_FILE)
	FILE* _logfp;
#endif
};

// The file that implements class DebugNewTracer
// does NOT want the word "new" expanded.
// The object DebugNewTrace is defined in that
// implementation file but only declared in any other file.
//#ifdef DEBUGNEW_CPP
//DebugNewTracer DebugNewTrace;
//#else
//#define new new(__FILE__, __LINE__)
extern DebugNewTracer DebugNewTrace;
//#endif
#endif
#endif//#ifndef __DEBUGNEW_H__