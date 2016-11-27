#ifndef BASE_SQL_VAL_TYPE_H
#define BASE_SQL_VAL_TYPE_H

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

#include "common/baseDef.h"
#include "baseClass.h"
#include "baseFunc.h"

class ValType
{
	private:
		std::vector<BYTE> _data;
	public:
		ValType():_data(1,'\0') {}
		ValType(const ValType & value)
		{
			_data = value._data;
		}
		template <typename T>
		explicit  ValType(const T& value)
		{
			put(value);
		}

		inline ValType& operator= (const ValType& value)
		{
			_data = value._data;
			return *this;
		}

		template <typename T>
		inline ValType& operator= (const T& value)
		{
			put(value);
			return *this;
		}
		inline void put(const void* data,const unsigned int len)
		{
			_data.resize(len+1);
			if(len)
			{
				bcopy(data,&_data[0],len);
			}
			_data[len] = '\0';
		}
		template <typename T>
		inline void put(const T& value)
		{
			std::ostringstream oss;
			oss << value;
			_data.resize(oss.str().length() + 1);
			strcpy((char*)&_data[0],oss.str().c_str());
		}
		void put(const BYTE& value)
		{
			put(static_cast<WORD>(value));
		}
		template <const void*>
		inline void put(const void* value);
		inline operator unsigned char() const
		{
			return atoi((const char*)(*this));
		}
		inline operator char() const
		{
			return atoi((const char*)(&_data[0]));
		}
		inline operator unsigned short() const
		{
			return atoi((const char*)(&_data[0]));
		}
		inline operator short() const
		{
			return atoi((const char*)(&_data[0]));
		}
		inline operator unsigned int() const
		{
			return atoi((const char*)(&_data[0]));
		}
		inline operator int() const
		{
			return atoi((const char*)(&_data[0]));
		}
		inline operator unsigned long() const
		{
			return strtoul((const char*)(&_data[0]),NULL,10);
		}
		inline operator long() const
		{
			return strtol((const char*)(&_data[0]),NULL,10);
		}
		inline operator unsigned long long()  const
		{
			return strtoul((const char*)(&_data[0]),NULL,10);
		}
		inline operator long long() const
		{
			return strtoll((const char*)(&_data[0]),NULL,10);
		}
		inline operator float() const
		{
			return atof((const char*)(&_data[0]));
		}
		inline operator double() const
		{
			return atof((const char*)(&_data[0]));
		}
		inline operator const char*() const
		{
			return (const char*)(&_data[0]);
		}
		inline operator const void*() const
		{
			return (const void*)(&_data[0]);
		}
		inline unsigned size() const
		{
			if(_data.empty())
				return 0;
			return _data.size() - 1;
		}
		inline bool empty() const
		{
			return _data.empty() || 1 == _data.size();
		}
		inline bool valid() const
		{
			return !empty();
		}
};

#endif
