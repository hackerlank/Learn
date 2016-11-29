
#ifndef UTILS_H_
#define UTILS_H_

#include "Config.h"
#include "TypeTraits.h"
#include <stdlib.h> // for ::ato*, ::strto*
#include <string>

namespace buf
{
    // [[ utilies for string

    template <typename T>
    bool str2num(const char* value, T* buffer)
    {
        if (!value || !buffer)
            return false;
        if (is_number<T>::value)
        {
            if (is_integer<T>::value)
            {
                char* end = 0;
                *buffer = strtoll(value, &end, 0);
                return end != value;
            }
            else if (is_float<T>::value)
            {
                char* end = 0;
#if _XOPEN_SOURCE >= 600 || _ISOC99_SOURCE || __APPLE__ || __MACH__
                if (sizeof(T) <= sizeof(float))
                    *buffer = ::strtof(value, &end);
                else
                    *buffer = ::strtod(value, &end);
                return end != value;
#elif defined(__CYGWIN__)
                if (sizeof(T) <= sizeof(float))
                    *buffer = ::atoff(value);
                else
                    *buffer = ::atof(value);
#else
                *buffer = ::atof(value);
#endif
                return true;
            }
        }
        return false;
    }

    inline int num2str(const bool& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%d", value);
    }
    inline int num2str(const char& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%d", value);
    }
    inline int num2str(const short& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%d", value);
    }
    inline int num2str(const int& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%d", value);
    }
    inline int num2str(const long& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%ld", value);
    }
    inline int num2str(const long long& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%lld", value);
    }
    inline int num2str(const double& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%f", value);
    }
    inline int num2str(const unsigned char& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%u", value);
    }
    inline int num2str(const unsigned short& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%u", value);
    }
    inline int num2str(const unsigned int& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%u", value);
    }
    inline int num2str(const unsigned long& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%lu", value);
    }
    inline int num2str(const unsigned long long& value, char* buffer, size_t size)
    {
        return SNPRINTF(buffer, size, "%llu", value);
    }

    template <typename T>
    inline std::string num2string(const T& value)
    {
        char buf[32] = {0};
        num2str(value, buf, sizeof(buf));
        return buf;
    }

    void trim(char* str, char ch = ' ');
    void trim(std::string& str, char ch = ' ');

    void upper(char* str);
    void upper(std::string& str);
    void lower(char* str);
    void lower(std::string& str);

    void cpystr(const char* src, char* dst, size_t dstlen, const char* DEFAULT = NULL);

    // ]] utilies for string

} // namespace buf

#endif // UTILS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

