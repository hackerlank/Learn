#ifndef BASE_PROPERTY_H
#define BASE_PROPERTY_H

#include <iostream>
#include <string>
#include <algorithm>
#include <ext/hash_map>

#include "baseSqlValType.h"
#include "global.h"
class Property
{
	public:
		const ValType &get( const std::string &key )
		{
			if( propertyMap.find( key ) == propertyMap.end() )
			{
				return Global::VAR_NULL;
			}
			return propertyMap[key];
		}
		void set( const std::string &key,const ValType &value )
		{
			propertyMap[key] = value;
		}
		bool find( const std::string &key )
		{
			return propertyMap.find( key ) == propertyMap.end();
		}

		ValType& operator[] ( const std::string &key )
		{
			return propertyMap[key];
		}
		void dump( std::ostream &out ) const
		{
			for( PropertyMap_ConstIter it = propertyMap.begin();it != propertyMap.end();++it )
			{
				out << it->first << " = " << ( const char * )it->second << std::endl;
			}
		}
		DWORD parseCmdLine( const std::string &cmdLine );
		DWORD parseCmdLine( const char *cmdLine );
	private:
		struct keyHash : public std::unary_function<const std::string,size_t>
		{
			size_t operator() ( const std::string &inst ) const
			{
				std::string temp = inst;
				__gnu_cxx::hash<const char*> hashInst;
				 transform( temp.begin(),temp.end(), temp.begin(),Global::lower );
				return hashInst( temp.c_str() );
			}
		};
		struct keyEqual : public std::binary_function<const std::string,const std::string,bool>
		{
			bool operator() ( const std::string &str1,const std::string &str2 ) const
			{
				return strcasecmp( str1.c_str(),str2.c_str() ) == 0;
			}
		};
		typedef __gnu_cxx::hash_map<std::string,ValType,keyHash,keyEqual> PropertyMap;
		typedef PropertyMap::iterator PropertyMap_Iter;
		typedef PropertyMap::const_iterator PropertyMap_ConstIter;
		PropertyMap propertyMap;
};

#endif

