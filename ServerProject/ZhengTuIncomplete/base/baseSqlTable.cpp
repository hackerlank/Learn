#include "baseSqlTable.h"

bool Table::reloadAllFileds(MYSQL *mysql,const char     *tableName)
{
	MYSQL_RES *filed_res = mysql_list_fields(mysql,tableName,NULL);
	if(!filed_res)
	{
		return false;
	}
	WORD num_fileds = mysql_num_fields(filed_res);
	MYSQL_FIELD *mysql_fileds = mysql_fetch_fields(filed_res);
	for(size_t index = 0;index < num_fileds;++index)
	{
		if(!fs.addNewFiled(mysql_fileds[index].name,mysql_fileds[index].type))
		{
			mysql_free_result(filed_res);
			return false;
		}
	}
	mysql_free_result(filed_res);
	return true;
}

bool TableManager::reloadAllTables(MYSQL *mysql_conn)
{
	MYSQL_RES *table_res = mysql_list_tables( mysql_conn,NULL );
	if( !table_res )
	{
		Global::logger->debug( "mysql_list_table fail" );
		return false;
	}
	MYSQL_ROW row;
	deleteAll();
	while((row=mysql_fetch_row(table_res)))
	{
		addNewTable(mysql_conn,row[0]);
	}
	mysql_free_result(table_res);
	return true;
}

bool TableManager::addNewTable(MYSQL *mysql_conn,const char *tableName)
{
	Table *table = new Table();
	if(!table)
	{
		return false;
	}
	strncpy(table->name,tableName,sizeof(table->name));
	table->reloadAllFileds(mysql_conn,tableName);
	if(!addTable(table))
	{
		DELETE(table);
		return false;
	}
	return true;
}
