#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#include "head.h"
#include <curl/curl.h>
#include "singleton.h"

enum HttpReqType
{
    HRT_Post = 1, //pst
    HRT_Get = 2, //get
};

class HttpReq
{
    public:
        unsigned long m_id;
        std::string m_url;
        std::string m_data;
        HttpReqType m_type;
        static unsigned long s_id;
    public:
        HttpReq(const std::string &url,const std::string &data) : m_id(++s_id),m_url(url),m_data(data),m_type(HRT_Get)
        {
        }
        void setType(const HttpReqType &type)
        {
            m_type = type;
        }
        HttpReqType getType() const
        {
            return m_type;
        }
};


class HttpClient : public DisCopy
{
    private:
        std::string m_url;
        CURL *m_curl;
    public:
        HttpClient(const std::string &url);
        HttpClient();
        ~HttpClient();
        bool initCurl();
        void initUrl(const std::string &url);
        bool post(std::string &ret, const std::string &data);
        bool get(std::string &ret, const std::string &data);
        static size_t writer(const char *data, size_t size, size_t mem, std::string *buffer);
        bool postNoReturn(std::string &ret, const std::string &data);
        bool getNoReturn(std::string &ret, const std::string &data);
    private:
        void reset();
};

#endif
