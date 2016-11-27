#include "baseSqlPool.h"
#include "baseThread.h"

MysqlPool::MysqlPool(int max_hash,int max_handle)
{
	for(int i = 0;i < max_hash;++i)
	{
		mhm.push_back(new MysqlHandleManager());
		tm.push_back(new TableManager());
	}
	_max_hash = max_hash;
	_max_handle = max_handle;
	if(!mysql_thread_safe())
	{
		Global::logger->debug("the mysql libs is not thread safe ...");
	}
}

MysqlPool::~MysqlPool()
{
	for(int i = 0;i < (int)_max_hash;++i)
	{
		DELETE(mhm[i]);
		DELETE(tm[i]);
	}
	mhm.clear();
	tm.clear();
}
bool MysqlPool::putUrl(unsigned int hashcode,const char *url)
{
	MysqlUrl *mu = new MysqlUrl(hashcode,url);
	if(!mu)
	{
		return false;
	}
	if(!mum.addMysqlUrl(mu))
	{
		DELETE(mu);
		return false;
	}
	MysqlHandle *handle = new MysqlHandle(mu,this,hashcode%_max_hash);
	if(!handle)
	{
		return false;
	}
	if(!handle->initHandle())
	{
		DELETE(handle);
		return false;
	}
	if(!mhm[hashcode]->addMysqlHandle(handle))
	{
		handle->finalHandle();
		DELETE(handle);
		return false;
	}
	tm[hashcode]->reloadAllTables(handle->getMysql());
	return true;
}
MysqlHandle* MysqlPool::getHandle(DWORD hashcode)
{
	struct GetHandleExec : public EntryCallBack<MysqlHandle>
	{
		GetHandleExec():_handle(NULL)
		{
		}
		MysqlHandle *_handle;
		bool exec(MysqlHandle *entry)
		{
			switch(entry->m_state)
			{
				case HandleState_Valid:
				case HandleState_Invalid:
					{
						if(entry->setHandle())
						{
							_handle = entry;
							return false;
						}
					}
					break;
				case HandleState_Used:
					{
						entry->checkUseTime();
					}
					break;
				default:
					break;
			}
			return true;
		}
	};
	GetHandleExec exec;
	while(true)
	{
		mhm[hashcode%_max_hash]->execEveryMysqlHandle(exec);
		if(exec._handle)
		{
			return exec._handle;
		}
		if(mhm[hashcode%_max_hash]->getSize() < _max_handle)
		{
			MysqlUrl *mu = mum.getMysqlUrlByID(hashcode);
			if(mu)
			{
				MysqlHandle *handle = new MysqlHandle(mu,this,hashcode%_max_hash);
				if(!handle)
				{
					return NULL;
				}
				if(!handle->initHandle())
				{
					DELETE(handle);
					return NULL;
				}
				if(!mhm[hashcode]->addMysqlHandle(handle))
				{
					handle->finalHandle();
					DELETE(handle);
				}
				tm[hashcode]->reloadAllTables(handle->getMysql());
				return handle;
			}
		}
		Thread::msleep(50);
	}
}

void MysqlPool::putHandle(MysqlHandle *handle)
{
	if(handle)
	{
		handle->freeHandle();
	}
}

				

	





		
		
	
		
