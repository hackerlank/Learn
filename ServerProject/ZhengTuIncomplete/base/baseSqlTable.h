#ifndef BASE_SQL_TABLE_H
#define BASE_SQL_TABLE_H

#include <ctype.h>
#include <mysql.h>
#include "baseEntry.h"
#include "baseSqlRecord.h"

struct Table : public Entry
{
	public:
		const char* getClassName() const
		{
			return "表";
		}
		Table()
		{
		}
		~Table()
		{
		}
	public:
		bool reloadAllFileds(MYSQL *mysql,const char *tableName);
		Record fs;
};

class TableManager : public EntryManager<EntryName,EntryNone<2>,EntryNone<3>,true>
{
	public:
		TableManager()
		{
		}
		~TableManager()
		{
		}

		bool addNewTable(MYSQL *mysql,const char *tableName);
		bool reloadAllTables(MYSQL *mysql);
		bool addTable(Table *entry)
		{
			std::transform(entry->name,&entry->name[strlen(entry->name)],entry->name,Global::upper);
			bool bret = false;
			rwlock.wrlock();
			bret = addEntry(entry);
			rwlock.unlock();
			return bret;
		}
		void removeTable(Table *entry)
		{
			rwlock.wrlock();
			removeEntry(entry);
			rwlock.unlock();
		}
		Table* getTableByName(const char *tableName)
		{
			Table *ret = NULL;
			rwlock.rdlock();
			ret = (Table*)getEntryByName(tableName);
			rwlock.unlock();
			return ret;
		}
		template <class YourEntry>
		bool execEveryTable(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
	private:
		RWLock rwlock;
};



#endif
