#ifndef MYSQL_URL_H
#define MYSQL_URL_H
#include "head.h"
class UrlInfo
{
    private:
        std::string m_host;
        unsigned short m_num;
        unsigned short m_port;
        std::string m_account;
        std::string m_passwd;
        std::string m_dbName;
        unsigned short m_code;
        bool m_valid;
    public:
        UrlInfo(const std::string &url);
    public:
        inline const char* getHost() const
        {
            return m_host.c_str();
        }
        inline const unsigned short getNum() const
        {
            return m_num;
        }
        inline const char* getAccount() const
        {
            return m_account.c_str();
        }
        inline const char* getPasswd() const
        {
            return m_passwd.c_str();
        }
        inline const char* getDBName() const
        {
            return m_dbName.c_str();
        }
        inline const bool getValid() const
        {
            return m_valid;
        }
        inline const unsigned short getPort() const
        {
            return m_port;
        }
        inline const unsigned short getCode() const
        {
            return m_code;
        }
    private:
        bool parseUrl(const std::string &url);
};

#endif
