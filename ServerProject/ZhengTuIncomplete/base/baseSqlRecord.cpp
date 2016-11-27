#include "baseSqlRecord.h"

bool Record::put(const char *filedName)
{
	Filed *entry = new Filed();
	if(!entry)
	{
		return false;
	}
	strncpy(entry->name,filedName,strlen(filedName));
	if(addFiled(entry))
	{
		DELETE(entry);
		return false;
	}
	return true;
}
bool Record::putk(const char *filedName,DWORD key)
{
	Filed *entry = new Filed();
	if(!entry)
	{
		return false;
	}
	strncpy(entry->name,filedName,strlen(filedName));
	entry->id = key;
	if(!addFiled(entry))
	{
		DELETE(entry);
		return false;
	}
	return true;
}
bool Record::addNewFiled(const char *filedName,int filedType,DWORD mask)
{
	Filed *entry = new Filed();
	if(!entry)
	{
		return false;
	}
	strncpy(entry->name,filedName,strlen(filedName));
	entry->type = filedType;
	entry->mask = mask;
	if(!addFiled(entry))
	{
		DELETE(entry);
		return false;
	}
	return true;
}
bool Record::addFiled(Filed *entry)
{
	std::transform(entry->name,&entry->name[strlen(entry->name)],entry->name,Global::upper);
	bool bret = false;
	rwlock.wrlock();
	bret = addEntry(entry);
	rwlock.unlock();
	return bret;
}
void Record::removeFiled(Filed *entry)
{
	rwlock.wrlock();
	removeEntry(entry);
	rwlock.unlock();
}

