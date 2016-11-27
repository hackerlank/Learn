#ifndef BASE_SQL_UINT_H
#define BASE_SQL_UINT_H

#include "baseEntry.h"
#include "baseSqlValType.h"

struct Filed : public Entry
{
	public:
		const char* getClassName() const
		{
			return "字段";
		}
		Filed()
		{
			type = 0;
			mask = 0;
		}
		~Filed()
		{
		}
	public:
		//字段类型
		DWORD type;
		//字段标志位
		DWORD mask;
		//数据
		ValType data;
};

#endif
