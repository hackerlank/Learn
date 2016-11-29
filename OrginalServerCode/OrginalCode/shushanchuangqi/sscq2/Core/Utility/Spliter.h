
#ifndef SPLITER_H_
#define SPLITER_H_

#include <strings.h>
#include <string.h>
#include <string>

namespace buf
{

//#define USING_CSPLIT 1

template <typename C>
void split(C& ret, const std::string& src, const char sp)
{
    std::string::size_type len = src.length();
    if (!len)
        return;
#ifdef USING_CSPLIT
    split(ret, src.c_str(), sp);
#else

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    if (src.find(sp, start) == std::string::npos)
    {
        ret.push_back(src);
        return;
    }

    bool empty = false;
    while (end < len)
    {
        if ((end = src.find(sp, start)) != std::string::npos)
        {
            ret.push_back(src.substr(start, end-start));
            ++end;
            if (end >= len)
            {
                empty = true;
                break;
            }
        }
        else
        {
            ret.push_back(src.substr(start));
            return;
        }
        start = end;
    }

    if (empty)
        ret.push_back("");

#endif // USING_CSPLIT
    return;
}

template <typename C>
void split(C& ret, const char* src, const char sp)
{
    if (!src)
        return;
#ifdef USING_CSPLIT
    size_t len = ::strlen(src);
    if (!len)
        return;
    
    char* start = (char*)src;
    char* end = (char*)src;

    bool empty = false;
    std::string s;
    while (*end)
    {
        if (s.length())
            s.clear();
        while (*end && *end++ != sp && *end) {}
        if (*end || *(end-1) == sp)
        {
            s.append(start, end-start-1);
            if (*(end-1) == sp && !(*end))
                empty = true;
        }
        else 
        {
            s.append(start, end-start);
        }

        ret.push_back(s);
        start = end;
    }
    if (empty)
        ret.push_back("");
#else
    split(ret, std::string(src), sp);
#endif // USING_CSPLIT
    return;
}

template <typename C>
void split(C& ret, const std::string& src, const std::string& sp)
{
    std::string::size_type len = src.length();
    if (!len)
        return;
    std::string::size_type splen = sp.length();
    if (!splen)
        return;

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    if (src.find(sp, start) == std::string::npos)
    {
        ret.push_back(src);
        return;
    }

    bool empty = false;
    while (end < len)
    {
        if ((end = src.find(sp, start)) != std::string::npos)
        {
            ret.push_back(src.substr(start, end-start));
            end += splen;
            if (end >= len)
            {
                empty = true;
                break;
            }
        }
        else
        {
            ret.push_back(src.substr(start));
            return;
        }
        start = end;
    }

    if (empty)
        ret.push_back("");
}

} // namespace buf

#endif // SPLITER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

