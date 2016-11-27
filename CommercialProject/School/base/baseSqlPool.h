#ifndef BASE_SQL_POOL_H
#define BASE_SQL_POOL_H
#include "baseEntry.h"
#include "baseSqlUrl.h"
#include "baseSqlHandle.h"
#include "baseSqlTable.h"
class MysqlPool : private Noncopyable
{
	public:
		MysqlPool(int max_hash = 1,int max_handle = 64);
		~MysqlPool();
		bool putUrl(unsigned int hashcode,const char *url);
		MysqlHandle* getHandle(DWORD hashcode = 0);
		void putHandle(MysqlHandle *handle);
	private:
		DWORD _max_handle;
		DWORD _max_hash;
	public:
		MysqlUrlManager mum;
		std::vector<TableManager*> tm;
		std::vector<MysqlHandleManager*> mhm;
};


#endif






			




