#include <stdio.h>
#include <string>
#include <type_traits>

using namespace std;

#ifdef _WIN32
#define StrToINT64 _strtoi64
#define StrToUINT64 _strtoui64
#else
#define StrToINT64 strtoll
#define StrToUINT64 strtoull
#endif

template<typename T>
bool GetValueFromString(const char* pText, T& rVal)
{
	if(pText == NULL)
		return false;
	char* pEnd = NULL;
	if(is_floating_point<T>::value)
		rVal = (T)strtod(pText, &pEnd);
	else if(is_signed<T>::value)
		rVal = (T)StrToINT64(pText, &pEnd, 10);
	else
		rVal = (T)StrToUINT64(pText, &pEnd, 10);
	return pEnd > pText;
}

template<>
bool GetValueFromString<bool>(const char* pText, bool& bVal)
{
	if(pText == NULL)
		return false;
	bVal = atoi(pText) != 0;
	return true;
}

template<>
bool GetValueFromString<string>(const char* pText, string& strVal)
{
	if(pText == NULL)
		return false;
	strVal = pText;
	return true;
}
