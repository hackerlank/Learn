#ifndef FLYER_VALUE_H
#define FLYER_VALUE_H
#include <string>

namespace Flyer
{
    class FlyerValue
    {
        private:
            typedef union DataType
            {
                char m_char;
                unsigned char m_uchar;
                bool m_bool;
                short m_short;
                unsigned short m_ushort;
                int m_int;
                unsigned m_uint;
                long m_long;
                unsigned m_ulong;
                float m_float;
            }DataType;
            DataType m_dataType;
            std::string m_val;
        public:
            FlyerValue();
            FlyerValue(const FlyerValue &arg);
            FlyerValue(const char arg);
            FlyerValue(const unsigned char uarg);
            FlyerValue(const bool arg);
            FlyerValue(const short arg);
            FlyerValue(const unsigned short uarg);
            FlyerValue(const int arg);
            FlyerValue(const unsigned int uarg);
            FlyerValue(const long arg);
            FlyerValue(unsigned long uarg);
            FlyerValue(const float arg);
            FlyerValue(const std::string &arg);
            FlyerValue(const char *arg);

            operator const char* () const;
            operator const std::string () const;
            operator const char ();
            operator const unsigned char ();
            operator const bool ();
            operator const short ();
            operator const unsigned short();
            operator const int();
            operator const unsigned int();
            operator const long();
            operator const unsigned long();
            operator const float();

            Flyer::FlyerValue& operator= (const char *arg);
            Flyer::FlyerValue& operator= (const std::string &arg);
            Flyer::FlyerValue& operator= (const char arg);
            Flyer::FlyerValue& operator= (const unsigned char uarg);
            Flyer::FlyerValue& operator= (const bool arg);
            Flyer::FlyerValue& operator= (const short arg);
            Flyer::FlyerValue& operator= (const unsigned short uarg);
            Flyer::FlyerValue& operator= (const int arg);
            Flyer::FlyerValue& operator= (const unsigned int uarg);
            Flyer::FlyerValue& operator= (const long arg);
            Flyer::FlyerValue& operator= (const unsigned long uarg);
            Flyer::FlyerValue& operator= (const float arg);
        private:
            void clear();
    };
}

#endif
