
#include "Utils.h"

namespace buf
{
    void trim(char* str, char ch)
    {
        if (!str)
            return;
        size_t len = ::strlen(str);
        if (!len)
            return;
        char* pstr = str;
        char* pend = str+len-1;
        if (pstr == pend && (isspace(*pstr) || *pstr == ch))
        {
            *pstr = '\0';
            return;
        }
        while (*pstr && (isspace(*pstr) || *pstr == ch)) ++pstr;
        while (*pend && (isspace(*pend) || *pstr == ch)) --pend;
        if (pstr >= pend)
        {
            *pstr = '\0';
            return;
        }
        size_t nlen = pend - pstr + 1;
        MEMCPY(str, pstr, nlen);
        str[nlen] = '\0';
        return;
    }

    void trim(std::string& str, char ch)
    {
        if (!str.length())
            return;
        std::string::size_type begin = 0;
        std::string::size_type end = str.length() - 1;
        while (begin != end && (isspace(str[begin]) || str[begin] == ch)) ++begin;
        while (begin != end && (isspace(str[end]) || str[end] == ch)) --end;
        if (begin == end)
        {
            str.clear();
            return ;
        }
        std::string tmp;
        tmp.insert(0, str, begin, end-begin+1);
        str.swap(tmp);
    }

    void upper(char* str)
    {
        if (!str)
            return;
        char* pstr = str;
        while (*pstr)
        {
            *pstr = toupper(*pstr);
            ++pstr;
        }
    }

    void upper(std::string& str)
    {
        size_t len = str.length();
        if (!len)
            return;
        for (size_t i = 0; i < len; ++i)
            str[i] = toupper(str[i]);
    }

    void lower(char* str)
    {
        if (!str)
            return;
        char* pstr = str;
        while (*pstr)
        {
            *pstr = tolower(*pstr);
            ++pstr;
        }
    }

    void lower(std::string& str)
    {
        size_t len = str.length();
        if (!len)
            return;
        for (size_t i = 0; i < len; ++i)
            str[i] = toupper(str[i]);
    }

    void cpystr(const char* src, char* dst, size_t dstlen, const char* DEFAULT)
    {
        if (!dst || !dstlen)
            return;

        if (!src && !DEFAULT)
            return;

        const char* p = src;
        if (!p)
            p = DEFAULT;
        if (!p)
            return;
        size_t size = strlen(p);
        size = size > dstlen - 1 ? dstlen - 1 : size;
        MEMCPY(dst, p, size);
        dst[size] = '\0';
    }

} // namespace buf

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

