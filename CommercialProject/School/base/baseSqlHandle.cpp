#include "baseSqlHandle.h"
#include "baseSqlPool.h"

MysqlHandle::MysqlHandle( const MysqlUrl *url,MysqlPool *pool,const DWORD hashcode ) : m_url(url),m_state(HandleState_Invalid),m_mysql(NULL),m_timeoutTime(1000L),m_pool(pool),m_hashCode(hashcode)
{
	static DWORD s_tempId = 0;
	s_tempId++;
	id = s_tempId;
}

MysqlHandle::~MysqlHandle()
{
	finalHandle();
}

bool MysqlHandle::initMysql()
{
	if(m_mysql)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
	
	m_mysql = mysql_init(NULL);
	LogCheckCondition( m_mysql,false,"初始化数据库句柄失败" );

	LogCheckCondition( mysql_real_connect(m_mysql,m_url->host,m_url->user,m_url->passwd,m_url->dbName,m_url->port,NULL,CLIENT_COMPRESS|CLIENT_INTERACTIVE),false,"连接数据库失败%s,%s,%s,%d",m_url->user,m_url->passwd,m_url->host,m_url->port );

	m_state = HandleState_Valid;
	m_lifeTime.now();
	m_count = 0;
	return true;
}

bool MysqlHandle::initHandle()
{
	finalHandle();
	if(!initMysql())
	{
		finalHandle();
		return false;
	}
	return true;
}

void MysqlHandle::finalHandle()
{
	if(m_mysql)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
	m_state = HandleState_Invalid;
	m_count = 0;
	m_lastsql = "";
}

bool MysqlHandle::setHandle()
{
	CheckConditonReturn( m_state != HandleState_Used,false );
	
	m_useTime.now();
	if(m_count > 10000 || mysql_ping(m_mysql))
	{
		CheckConditonReturn( initHandle(),false );
	}
	m_state = HandleState_Used;
	++m_count;
	return true;
}

void MysqlHandle::freeHandle()
{
	m_state = HandleState_Valid;
}

void MysqlHandle::checkUseTime()
{
	if(m_useTime.elapse(Time()) > m_timeoutTime)
	{
		m_timeoutTime += 10000L;
	}
}

SDWORD MysqlHandle::execSql(const char *sql,const DWORD sqllen,bool need_errlog)
{
	SDWORD ret = -1;
	LogCheckCondition( m_mysql && sql && sqllen,ret,"MysqlHandle::execSql 操作失败%s",sql );

	m_lastsql = sql;
	ret = mysql_real_query(m_mysql,sql,sqllen);
	LogCheckCondition( !(ret && need_errlog),ret,"数据库操作失败%s",mysql_error(m_mysql) );
	return ret;
}

RecordSet* MysqlHandle::exeSelect(const char *sql,const DWORD sqllen)
{
	LogCheckCondition( m_mysql,NULL,"MysqlHandle::exeSelect 数据库连接为空" );
	m_selectTime.now();
	LogCheckCondition( !execSql(sql,sqllen),NULL,"MysqlHandle::exeSelect 数据库操作失败%s",mysql_error(m_mysql) );
	MYSQL_RES *result = NULL;
	result = mysql_store_result(m_mysql);
	CheckConditonReturn( result,NULL );
	DWORD retCount = mysql_num_rows(result);
	if(!retCount)
	{
		mysql_free_result(result);
		return NULL;
	}
	MYSQL_ROW row;
	DWORD num_filed = mysql_num_fields(result);
	MYSQL_FIELD *mysql_fileds = mysql_fetch_fields(result);
	RecordSet *ret_set = NULL;
	if(mysql_num_rows(result))
	{
		ret_set = new RecordSet(retCount);
		if(!ret_set)
		{
			mysql_free_result(result);
			return NULL;
		}
		DWORD index = 0;
		while(row = mysql_fetch_row(result))
		{
			QWORD *lengths = mysql_fetch_lengths(result);
			Record *rec = ret_set->get(index++);
			if(!rec)
			{
				mysql_free_result(result);
				return NULL;
			}
			for( size_t filedCnt = 0;filedCnt < num_filed;++filedCnt )
			{
				if(row[filedCnt])
				{
					rec->put(mysql_fileds[filedCnt].name,row[filedCnt],lengths[filedCnt]);
				}
			}
		}
	}
	mysql_free_result(result);
	if(ret_set && !ret_set->size())
	{
		DELETE(ret_set);
	}
	LogCheckConditionOnly( !(m_selectTime.elapse(Time()) >= 3*1000L),"MysqlHandle::exeSelectsql %s 超时%lu毫秒",sql,m_selectTime.elapse(Time()) );
	return ret_set;
}
DWORD MysqlHandle::exeInsert(const char *tableName,Record *data,bool need_log)
{
	DWORD ret = (DWORD)-1;
	Table *table = m_pool->tm[m_hashCode]->getTableByName(tableName);
	LogErrorCheckCondition( table && data && m_mysql,ret,"MysqlHandle::exeInsert 数据库插入错误%s",tableName );
	m_insertTime.now();
	std::ostringstream query_string;
	std::ostringstream value_string;
	query_string << "INSERT INTO ";
	query_string << table->name;
	query_string << " ( ";
	value_string << " VALUES( ";
	struct InsertExec : public EntryCallBack<Filed>
	{
		bool frist;
		Table *table;
		std::ostringstream &query_string;
		std::ostringstream &value_string;
		MysqlHandle *handle;
		InsertExec(Table *table,std::ostringstream &query_string,std::ostringstream &value_string):frist(true),table(table),query_string(query_string),value_string(value_string)
		{
		}
		bool exec(Filed *entry)
		{
			Filed *file = table->fs.get(entry->name);
			CheckConditonReturn( file,true );
			if(!frist)
			{
				frist = false;
			}
			else
			{
				query_string << " , ";
				value_string << " , ";
				query_string << "'" << entry->name << "'";
				handle->storeValue(table,value_string,file->type,entry->data);
				return true;
			}
		}
	}dcb(table,query_string,value_string);
	data->execEveryFiled(dcb);
	if(!execSql(query_string.str().c_str(),query_string.str().size(),need_log))
	{
		ret = (DWORD)mysql_insert_id(m_mysql);
	}
	LogCheckConditionOnly( !(m_insertTime.elapse(Time()) >= 3*1000L),"MysqlHandle::exeInsert 数据库插入超时 %s,%lu",query_string.str().c_str(),m_selectTime.elapse(Time()) );
	return ret;
}

DWORD MysqlHandle::exeUpdate(const char *tableName,Record *data,Record *where)
{
	DWORD ret = (DWORD)-1;
	Table *table = this->m_pool->tm[this->m_hashCode]->getTableByName(tableName);
	LogErrorCheckCondition( table && data && m_mysql,ret,"MysqlHandle::exeUpdate 数据库更新失败%s",tableName );
	m_updateTime.now();
	std::ostringstream query_string;
	query_string << "UPDATE ";
	query_string << table->name;
	query_string << " SET ";
	struct UpdateExec : public EntryCallBack<Filed>
	{
		bool frist;
		Table *table;
		std::ostringstream &query_string;
		MysqlHandle *handle;
		UpdateExec(Table *table,std::ostringstream &query_string,MysqlHandle *handle):frist(true),table(table),query_string(query_string),handle(handle)
		{
		}
		bool exec(Filed *entry)
		{
			Filed *file = table->fs.get(entry->name);
			CheckConditonReturn( file,true );
			if(frist)
			{
				frist = false;
			}
			else
			{
				query_string << ",";
			}
			query_string << "'" << entry->name << "'" << " = ";
			handle->storeValue(table,query_string,file->type,entry->data);
			return true;
		}
	}updcb(table,query_string,this);
	data->execEveryFiled(updcb);
	getWhere(table,query_string,where);
	if(!execSql(query_string.str().c_str(),query_string.str().size()))
	{
		ret = (DWORD)mysql_affected_rows(m_mysql);
	}
	if(m_updateTime.elapse(Time()) >= 3 * 1000L)
	{
		std::ostringstream where_string;
		getWhere(table,where_string,where);
	}
	return ret;
}
DWORD MysqlHandle::exeDelete(const char *tableName,Record *where)
{
	DWORD ret = (DWORD)-1;
	Table *table = m_pool->tm[m_hashCode]->getTableByName(tableName);
	LogErrorCheckCondition( m_mysql && table,ret,"MysqlHandle::exeDelete 数据库删除操作失败%s",tableName );
	m_deleteTime.now();
	std::ostringstream query_string;
	query_string << "DELETE FROM ";
	query_string << table->name;
	getWhere(table,query_string,where);
	if(!execSql(query_string.str().c_str(),query_string.str().size()))
	{
		ret = (DWORD)mysql_affected_rows(m_mysql);
	}
	return ret;
}
char* MysqlHandle::escapeString(const char *src,char *dest,DWORD size)
{
	LogCheckCondition( src && dest && m_mysql,NULL,"MysqlHandle::escapeString 参数错误 %s,%s",src,dest );
	char *end = dest;
	mysql_real_escape_string(m_mysql,end,src,size == 0 ? strlen(src) : size);
	return dest;
}
std::string& MysqlHandle::escapeString(const std::string &src,std::string &dest)
{
	LogErrorCheckCondition( m_mysql,dest,"MysqlHandle::escapeString 数据库连接为空" );
	char buff[2 * src.length() + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(m_mysql,buff,src.c_str(),src.length());
	dest = buff;
	return dest;
}
bool MysqlHandle::escapeString(const std::string &src)
{
	LogErrorCheckCondition( m_mysql,false,"MysqlHandle::escapeString 数据库连接为空" );
	char buff[2 * src.length() + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(m_mysql,buff,src.c_str(),src.length());
	return (strcmp(buff,src.c_str()) == 0);
}
bool MysqlHandle::escapeString(const char *src)
{
	LogErrorCheckCondition( m_mysql,false,"MysqlHandle::escapeString 数据库连接为空" );
	char buff[2 * strlen(src) + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(m_mysql,buff,src,strlen(src));
	return(strcmp(buff,src) == 0);
}
RecordSet* MysqlHandle::exeSelect(const char *tableName,Record *column,Record *where,Record *having,DWORD limit_offset,DWORD limit_rows,Record *groupby,Record *order)
{
	Table *table = m_pool->tm[m_hashCode]->getTableByName(tableName);
	LogErrorCheckCondition( table && m_mysql,NULL,"数据库查询操作失败%s",tableName );
	m_selectTime.now();
	std::ostringstream query_string;
	query_string << "SELECT ";
	if(column && !column->isEmpty())
	{
		struct SqlFiledExec : public EntryCallBack<Filed>
		{
			bool frist;
			Table *table;
			std::ostringstream &query_string;
			SqlFiledExec(Table *table,std::ostringstream& query_string):frist(true),table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(strncmp(entry->name,"*",strlen(entry->name)) == 0 || table->fs.get(entry->name))
				{
					if(frist)
					{
						frist = false;
					}
					else
					{
						query_string << " , ";
					}
					if(entry->data.empty())
					{
						query_string << entry->name ;
					}
					else
					{
						query_string << (const char *)entry->data;
					}
				}
				return true;
			}
		}sfe(table,query_string);
		column->execEveryFiled(sfe);
	}
	else
	{
		query_string << " * ";
	}
	query_string << " FROM " << table->name ;
	getWhere(table,query_string,where);
	getGroupBy(table,query_string,groupby);
	getHaving(table,query_string,having);
	getOrder(table,query_string,order);
	if(limit_offset > 0 || limit_rows > 0)
	{
		query_string << " LIMIT " << limit_offset <<  " , " << limit_rows;
	}
	LogCheckCondition( !execSql(query_string.str().c_str(),query_string.str().size()),NULL,"数据库查询失败%s",query_string.str().c_str() );
	MYSQL_RES *result = mysql_store_result(m_mysql);
	LogCheckCondition( result,NULL,"数据库查询结果为空" );
	DWORD retCount = mysql_num_rows(result);
	LogCheckCondition( retCount,NULL,"数据库查询结果列数为空" );
	MYSQL_ROW row;
	DWORD num_filed = mysql_num_fields(result);
	MYSQL_FIELD *mysql_fileds = mysql_fetch_fields(result);
	RecordSet *ret_set = new RecordSet(retCount);
	if(ret_set)
	{
		DWORD index = 0;
		while((row = mysql_fetch_row(result)))
		{
			QWORD *lengths = mysql_fetch_lengths(result);
			Record *rec = ret_set->get(index++);
			if(rec)
			{
				for(DWORD filedCnt = 0;filedCnt < num_filed;++filedCnt)
				{
					if(row[filedCnt])
					{
						rec->put(mysql_fileds[filedCnt].name,row[filedCnt],lengths[filedCnt]);
					}
				}
			}
		}
	}
	mysql_free_result(result);
	if(ret_set && ret_set->size() == 0)
	{
		DELETE(ret_set);
	}
	return ret_set;
}
struct WhereExec : public EntryCallBack<Filed>
{
	bool frist;
	Table *table;
	std::ostringstream &query_string;
	WhereExec(Table *table,std::ostringstream &query_string):frist(true),table(table),query_string(query_string)
	{
	}
	bool exec(Filed *entry)
	{
		if(table->fs.get(entry->name) && entry->data.valid())
		{
			if(frist)
			{
				frist = false;
				query_string << " WHERE ";
			}
			else
			{
				query_string << " AND ";
			}
			query_string << (const char *)entry->data;
		}
	}
};
std::ostringstream& MysqlHandle::getWhere(Table *table,std::ostringstream &query_string,Record *where)
{
	if(table && where && !where->isEmpty())
	{
		WhereExec wcb(table,query_string);
		where->execEveryFiled(wcb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getHaving(Table *table,std::ostringstream &query_string,Record *having)
{
	if(having && !having->isEmpty())
	{
		struct HavingExec : public EntryCallBack<Filed>
		{
			bool frist;
			Table *table;
			std::ostringstream &query_string;
			HavingExec(Table *table,std::ostringstream& query_string):frist(true),table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(table->fs.get(entry->name))
				{
					if(frist)
					{
						query_string << " HAVING ";		
						frist = false;
					}
					else
					{
						query_string << " AND ";
					}
					query_string << entry->name ;
				}
				return true;
			}
		}hcb(table,query_string);
		having->execEveryFiled(hcb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getGroupBy(Table *table,std::ostringstream &query_string,Record *groupby)
{
	if(groupby && !groupby->isEmpty())
	{
		struct GroupExec : public EntryCallBack<Filed>
		{
			bool frist;
			Table *table;
			std::ostringstream &query_string;
			GroupExec(Table *table,std::ostringstream& query_string):frist(true),table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(table->fs.get(entry->name))
				{
					if(frist)
					{
						query_string << " GROUP BY ";		
						frist = false;
					}
					else
					{
						query_string << ", ";
					}
					query_string << entry->name ;
				}
				return true;
			}
		}exec(table,query_string);
		groupby->execEveryFiled(exec);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getOrder(Table *table,std::ostringstream &query_string,Record *order)
{
	if(order && !order->isEmpty())
	{
		struct OrderExec : public EntryCallBack<Filed>
		{
			bool frist;
			Table *table;
			std::ostringstream &query_string;
			OrderExec(Table *table,std::ostringstream& query_string):frist(true),table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(table->fs.get(entry->name))
				{
					if(frist)
					{
						query_string << " ORDER BY ";		
						frist = false;
					}
					else
					{
						query_string << ", ";
					}
					const char *filedValue = entry->data;
					if(strlen(filedValue) == 0)
					{
						query_string << entry->name ;
					}
					else
					{
						query_string << " " << entry->name << " " << filedValue;
					}
				}
				return true;
			}
		}exec(table,query_string);
		order->execEveryFiled(exec);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::storeValue(Table *table,std::ostringstream &query_string,const SDWORD type, const ValType &value)
{
	switch(type)
	{
		case FIELD_TYPE_STRING:
		case FIELD_TYPE_VAR_STRING:
		case FIELD_TYPE_DATE:
		case FIELD_TYPE_TIME:
		case FIELD_TYPE_DATETIME:
		case FIELD_TYPE_YEAR:
			{
				const char *filedvalue = value;
				DWORD len = strlen(filedvalue);
				char strData[len*2+1];
				mysql_real_escape_string(m_mysql,strData,filedvalue,len);
				query_string << "\'" << strData << "\'";
			}
			break;
		case FIELD_TYPE_BLOB:
			{
				DWORD len = value.size();
				if(len)
				{
					char strData[len*2+1];
					mysql_real_escape_string(m_mysql,strData,(const char*)value,len);
					query_string << "\'" << strData << "\'";
				}
				else
				{
					query_string << "NULL";
				}
			}
			break;
		default:
			{
				query_string << (const char*)value;
			}
			break;
	}
	return query_string;
}
/*
AutoHandle::AutoHandle(MysqlPool *pool):_pool(pool)
{
	handle = _pool->getHandle();
}
AutoHandle::~AutoHandle()
{
	_pool->putHandle(handle);
}
*/

