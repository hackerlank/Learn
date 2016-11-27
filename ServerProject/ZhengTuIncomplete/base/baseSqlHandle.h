#ifndef BASE_SQL_HANDLE_H
#define BASE_SQL_HANDLE_H
#include <mysql.h>

#include "baseEntry.h"
#include "baseSqlUrl.h"
#include "baseSqlRecord.h"
#include "baseSqlTable.h"
#include "baseLock.h"
#include "baseTime.h"

class MysqlPool;

enum HandleState
{
	HandleState_Invalid = 1,  //无效
	HandleState_Valid   = 2,  //有效
	HandleState_Used    = 3   //使用
};
class MysqlHandle : public Entry
{
	public:
		const char* getClassName() const
		{
			return "MysqlHandle";
		}
	private:
		DWORD m_hashCode;
		const MysqlUrl *m_url;
		DWORD m_count;
		Time m_lifeTime;
		MYSQL *m_mysql;
		Time m_useTime;
 		DWORD m_timeoutTime;
		Time m_updateTime;
		Time m_insertTime;
		Time m_deleteTime;
		Time m_selectTime;
		std::string m_lastsql;
		MysqlPool *m_pool;
	public:
		HandleState m_state;
	private:
		bool initMysql();
	public:
		MysqlHandle(const MysqlUrl *url,MysqlPool *pool,const DWORD hashcode);
		~MysqlHandle();
		MYSQL* getMysql() const
		{
			return m_mysql;
		}
		bool initHandle();
		void finalHandle();
		bool setHandle();
		void freeHandle();
		void checkUseTime();
		RecordSet* exeSelect(const char *tableName,Record *column,Record *where,Record *having = NULL,DWORD limit_offset = 0,DWORD limit_rows = 0,Record *groupby=NULL,Record *order= NULL);
		DWORD exeInsert(const char *tableName,Record *data,bool need_errlog = true);
		DWORD exeUpdate(const char *tableName,Record *data,Record *where);
		DWORD exeDelete(const char *tableName,Record *where);
		char* escapeString(const char *src,char *dest,DWORD size);
		std::string& escapeString(const std::string &src,std::string &dest);

	private:
		bool escapeString(const char *src);
		bool escapeString(const std::string &src);
		SDWORD execSql(const char *sql,DWORD sqllen,bool need_errlog = true);
		RecordSet* exeSelect(const char *sql,const DWORD sqllen);
		inline std::ostringstream& getWhere(Table *table,std::ostringstream &query_string,Record *where);
		inline std::ostringstream& getGroupBy(Table *table,std::ostringstream &query_string,Record *groupby);
		inline std::ostringstream& getHaving(Table *table,std::ostringstream &query_string,Record *having);
		inline std::ostringstream& getOrder(Table *table,std::ostringstream &query_string,Record *order);
		inline std::ostringstream& storeValue(Table *table,std::ostringstream &query_string,const SDWORD type,const ValType &value);
};

class MysqlHandleManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>/*,public Singletonbase<MysqlHandleManager>*/
{
	public:
		MysqlHandleManager()
		{
		}
		~MysqlHandleManager()
		{
			deleteAll();
		}
		bool addMysqlHandle(MysqlHandle *entry)
		{
			bool ret = false;
			m_rwlock.wrlock();
			ret = addEntry(entry);
			m_rwlock.unlock();
			return ret;
		}
		void removeMysqlHandle(MysqlHandle *entry)
		{
			m_rwlock.wrlock();
			removeEntry(entry);
			m_rwlock.unlock();
		}
		MysqlHandle* getMysqlHandleByID(const DWORD handleId)
		{
			MysqlHandle *ret = NULL;
			m_rwlock.rdlock();
			ret = (MysqlHandle*)getEntryByID(handleId);
			 m_rwlock.unlock();
			return ret;
		}
		size_t getSize()
		{
			return EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>::size();
		}
		template <class YourEntry>
		bool execEveryMysqlHandle(EntryCallBack<YourEntry> &exec)
		{
			m_rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			m_rwlock.unlock();
			return ret;
		}
	private:
		RWLock m_rwlock;
};

#endif
