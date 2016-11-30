#include "MyAsioTools.h"

CMyAsioTools::CMyAsioTools()
{
	memset(_Data,0,2*MAX_RESERVE_SIZE);
	_len = 0;
}

std::string CMyAsioTools::Serializing(const std::string & str )
{
	char _str[MAX_HEAD_LEN +1];
	memset(_str,0,MAX_HEAD_LEN +1);
	sprintf_s(_str,"%05d",str.length());
	return std::string(_str) + str;
}

std::vector<std::string> CMyAsioTools::UnSerializing(const char * data, int size )
{
	std::vector<std::string> ver;
	if (!data)return ver;

	//assert(_len + size < 2*MAX_RESERVE_SIZE);
	memcpy(_Data + _len,data,size);
	_len += size;
	int f=0,temp =0;
	char _str[MAX_HEAD_LEN +1];

	while(true)//开始拆分查找
	{
		if (_len - f < MAX_HEAD_LEN)//不够长度了
		{
			memcpy(_Data,_Data+f,_len - f);
			memset(_Data+_len-f,0,2*MAX_RESERVE_SIZE-_len+f);
			_len = _len - f;
			break;
		}
		else
		{
			memset(_str,0,MAX_HEAD_LEN +1);
			memcpy(_str,_Data+f,MAX_HEAD_LEN);
			int len = atoi(_str);
			if(_len-(f+MAX_HEAD_LEN) < len)//不满足要求了
			{
				memcpy(_Data,_Data+f,_len - f);
				memset(_Data+_len-f,0,2*MAX_RESERVE_SIZE-_len+f);
				_len = _len - f;
				break;
			}
			else//可以找到一个
			{
				ver.push_back(std::string(_Data+f+MAX_HEAD_LEN,len));
				f += MAX_HEAD_LEN+ len;
			}
		}
	}

	return ver;


// 	char _str[MAX_HEAD_LEN +1];
// 	memset(_str,0,MAX_HEAD_LEN +1);
// 
// 	char *f = NULL,*e = NULL;
// 	int i=0;
// 	for (i=0;(i<_len)&&(i<MAX_HEAD_LEN);i++)
// 		_str[i] = _Data[i];
// 	for (int j=i;j<5;j++)
// 		_str[i+j] = data[i];
// 
// 	if (_len )
// 	{
// 	}
}

