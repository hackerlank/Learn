#ifndef BASE_SQL_RECORD_H
#define BASE_SQL_RECORD_H
#include "baseEntry.h"
#include "baseSqlFiled.h"

class Record : public EntryManager<EntryName,EntryNone<2>,EntryNone<3>,true>
{
	public:
		Record()
		{
		}
		~Record()
		{
			deleteAll();
		}
		bool put(const char *filedName);
		bool putk(const char *fileName,DWORD key);
		template <typename T>
		void put_and_update(const char *fileName,T value)
		{
			Filed *entry = get(fileName);
			if(entry)
			{
				entry->data.put(value);
			}
			else
			{
				put(fileName,value);
			}
		}
		template <typename T>
		void put(const char *filedName,T value)
		{
			Filed *entry = new Filed();
			if(!entry)
			{
				Global::logger->debug("Record::put error the entry is NULL");
				return;
			}
			strncpy(entry->name,filedName,strlen(filedName));
			entry->data.put(value);
			if(!addFiled(entry))
			{
				DELETE(entry);
			}
		}
		void put(const char *filedName,const void *data,DWORD len)
		{
			Filed *entry = new Filed();
			if(!entry)
			{
				Global::logger->debug("Record::put void error the entry is NULL");
				return;
			}
			strncpy(entry->name,filedName,strlen(filedName));
			entry->data.put(data,len);
			if(!addFiled(entry))
			{
				Global::logger->debug("addFile error filedName:%s",entry->name);
				DELETE(entry);
			}
		}
		template <typename T>
		void putk(const char *filedName,T value,DWORD key)
		{
			Filed *entry = new Filed();
			if(!entry)
			{
				Global::logger->debug("Record::putk error entry is NULL");
				return;
			}
			strncpy(entry->name,filedName,strlen(filedName));
			entry->id = key;
			entry->data.put(value);
			if(!addFiled(entry))
			{
				DELETE(entry);
			}
		}
		void putk(const char *filedName,const void *data,DWORD len,DWORD key)
		{
			Filed *entry = new Filed();
			if(!entry)
			{
				Global::logger->debug("Record::putk void error entry is NULL");
				return;
			}
			strncpy(entry->name,filedName,strlen(filedName));
			entry->id = key;
			entry->data.put(data,len);
			if(!addFiled(entry))
			{
				DELETE(entry);
			}
		}
		bool addNewFiled(const char *filedName,int filedType,DWORD mask = 0);
		bool isEmpty()
		{
			return empty();
		}
		bool addFiled(Filed *entry);
		void removeFiled(Filed *entry);
		Filed* get(const char *filedName)
		{
			char temp[MAX_NAME_SIZE] = {'\0'};
			std::transform(filedName,&filedName[strlen(filedName)],temp,Global::upper);
			Filed *entry = NULL;
			rwlock.rdlock();
			entry = (Filed*)getEntryByName(temp);
			rwlock.unlock();
			return entry;
		}
		ValType getValue(const char *fileName)
		{
			Filed *entry = get(fileName);
			if(entry)
			{
				return entry->data;
			}
			ValType tempVal;
			return tempVal;
		}
		template <class YourEntry>
		bool execEveryFiled(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return true;
		}
	private:
		RWLock rwlock;
};

struct RecordSet
{
	public:
		RecordSet(int size):recordVec(size)
		{
			for(RecordVec_iter iter = recordVec.begin();iter != recordVec.end();++iter)
			{
				(*iter) = new Record;
			}
		}
		~RecordSet()
		{
			for(RecordVec_iter iter = recordVec.begin();iter != recordVec.end();++iter)
			{
				Record *record = (*iter);
				DELETE(record);
			}
		}
	public:
		inline unsigned int size() const
		{
			return recordVec.size();
		}
		inline bool empty() const
		{
			return recordVec.empty();
		}
		inline Record* get(unsigned int row) const
		{
			if(row < size())
			{
				return recordVec[row];
			}
			else
			{
				return NULL;
			}
		}
	private:
		typedef std::vector<Record*> RecordVec;
		typedef RecordVec::iterator RecordVec_iter;
		RecordVec recordVec;
};



#endif
