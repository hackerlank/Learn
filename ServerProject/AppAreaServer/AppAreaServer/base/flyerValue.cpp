#include "flyerValue.h"
#include <string.h>

namespace Flyer
{
    FlyerValue::FlyerValue()
    {
        clear();
    }

    FlyerValue::FlyerValue(const FlyerValue &arg)
    {
        clear();
        *this = arg;
    }

    FlyerValue::FlyerValue(const char arg)
    {
        clear();
        m_dataType.m_char = arg;
        m_val = std::to_string((long long)arg);
    }

    FlyerValue::FlyerValue(const unsigned char uarg)
    {
        clear();
        m_dataType.m_char = uarg;
        m_val = std::to_string((unsigned long long)uarg);
    }
    
    FlyerValue::FlyerValue(const bool arg)
    {
        clear();
        m_dataType.m_bool = arg;
        m_val = arg ? "true" : "false";
    }

    FlyerValue::FlyerValue(const short arg)
    {
        clear();
        m_dataType.m_short = arg;
        m_val = std::to_string((long long)arg);
    }
    FlyerValue::FlyerValue(const unsigned short uarg)
    {
        clear();
        m_dataType.m_ushort = uarg;
        m_val = std::to_string((unsigned long long)uarg);
    }
    FlyerValue::FlyerValue(const int arg)
    {
        clear();
        m_dataType.m_int = arg;
        m_val = std::to_string((long long)arg);
    }

    FlyerValue::FlyerValue(const unsigned int uarg)
    {
        clear();
        m_dataType.m_uint = uarg;
        m_val = std::to_string((unsigned long long)uarg);
    }
    FlyerValue::FlyerValue(const long arg)
    {
        clear();
        m_dataType.m_long = arg;
        m_val = std::to_string((long long)arg);
    }

    FlyerValue::FlyerValue(unsigned long uarg)
    {
        clear();
        m_dataType.m_ulong = uarg;
        m_val = std::to_string((unsigned long long)uarg);
    }

    FlyerValue::FlyerValue(const float arg)
    {
        clear();
        m_dataType.m_float = arg;
        float val = arg;
        m_val = std::to_string((long double)val);
    }

    FlyerValue::FlyerValue(const char *arg)
    {
        clear();
        if(arg)
        {
            m_val = arg;
        }
    }

    FlyerValue::FlyerValue(const std::string &arg)
    {
        clear();
        m_val = arg;
    }

    void FlyerValue::clear()
    {
        bzero(&m_dataType,sizeof(m_dataType));
        m_val.clear();
    }

    FlyerValue::operator const char*() const
    {
        return m_val.c_str();
    }

    FlyerValue::operator const std::string() const
    {
        return m_val;
    }

    FlyerValue::operator const char()
    {
        return m_dataType.m_char ? m_dataType.m_char : m_dataType.m_char = (char)atoi(m_val.c_str());
    }

    FlyerValue::operator const unsigned char()
    {
        return m_dataType.m_uchar ? m_dataType.m_uchar : m_dataType.m_uchar = (unsigned char)atoi(m_val.c_str());
    }

    FlyerValue::operator const bool()
    {
        return m_dataType.m_bool ? m_dataType.m_bool : m_dataType.m_bool = (m_val == "true" ? true : false);
    }

    FlyerValue::operator const short()
    {
        return m_dataType.m_short ? m_dataType.m_short : m_dataType.m_short = (short)atoi(m_val.c_str());
    }

    FlyerValue::operator const unsigned short()
    {
        return m_dataType.m_ushort ? m_dataType.m_ushort : m_dataType.m_ushort = (unsigned short)atoi(m_val.c_str());
    }

    FlyerValue::operator const int()
    {
        return m_dataType.m_int ? m_dataType.m_int : m_dataType.m_int = (int)atoi(m_val.c_str());
    }

    FlyerValue::operator const unsigned int()
    {
        return m_dataType.m_uint ? m_dataType.m_uint : m_dataType.m_uint = (unsigned int)atoi(m_val.c_str());
    }

    FlyerValue::operator const long()
    {
        return m_dataType.m_long ? m_dataType.m_long : m_dataType.m_long = (long)atol(m_val.c_str());
    }

    FlyerValue::operator const unsigned long()
    {
        return m_dataType.m_ulong ? m_dataType.m_ulong : m_dataType.m_ulong = (unsigned long)atol(m_val.c_str());
    }

    FlyerValue::operator const float()
    {
        return m_dataType.m_float ? m_dataType.m_float : m_dataType.m_float = (float)atof(m_val.c_str());
    }

    Flyer::FlyerValue& FlyerValue::operator= (const char *arg)
    {
        clear();
        if(arg)
        {
            m_val = arg;
        }
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const std::string &arg)
    {
        clear();
        m_val = arg;
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const char arg)
    {
        clear();
        m_dataType.m_char = arg;
        m_val = std::to_string((long long)(arg));
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const unsigned char uarg)
    {
        clear();
        m_dataType.m_uchar = uarg;
        m_val = std::to_string((unsigned long long)(uarg));
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const short arg)
    {
        clear();
        m_dataType.m_short = arg;
        m_val = std::to_string((long long)arg);
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const unsigned short uarg)
    {
        clear();
        m_dataType.m_ushort = uarg;
        m_val = std::to_string((unsigned long long)(uarg));
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const int arg)
    {
        clear();
        m_dataType.m_int = arg;
        m_val = std::to_string((long long)arg);
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const unsigned int uarg)
    {
        clear();
        m_dataType.m_uint = uarg;
        m_val = std::to_string((unsigned long long)(uarg));
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const long arg)
    {
        clear();
        m_dataType.m_long = arg;
        m_val = std::to_string((long long)arg);
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const unsigned long uarg)
    {
        clear();
        m_dataType.m_ulong = uarg;
        m_val = std::to_string((unsigned long long)(uarg));
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const float arg)
    {
        clear();
        m_dataType.m_float = arg;
        m_val = std::to_string((long double)arg);
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const long long arg)
    {
        clear();
        m_dataType.m_llong = arg;
        m_val = std::to_string((long long)arg);
        return *this;
    }

    Flyer::FlyerValue& FlyerValue::operator= (const unsigned long long uarg)
    {
        clear();
        m_dataType.m_ullong = uarg;
        m_val = std::to_string((unsigned long long)(uarg));
        return *this;
    }
}
