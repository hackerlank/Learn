#include "httpClient.h"
#include "flyer.h"

unsigned long HttpReq::s_id = 0;
HttpClient::HttpClient(const std::string &url) : m_url(url),m_curl(NULL) 
{
}

HttpClient::HttpClient() : m_url(),m_curl(NULL)
{
}

HttpClient::~HttpClient()
{
    curl_easy_cleanup(m_curl);
}

void HttpClient::reset()
{
    curl_easy_reset(m_curl);
}

bool HttpClient::initCurl()
{
    bool ret = false;
    do
    {
        m_curl = curl_easy_init();
        if(!m_curl)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

void HttpClient::initUrl(const std::string &url)
{
    m_url = url;
}

bool HttpClient::post(std::string &ret, const std::string &data)
{
    bool flag = false;
    do
    {
        if(!m_curl)
        {
            break;
        }
        reset();
        char error[CURL_ERROR_SIZE];
        bzero(error,sizeof(error));
        ret.clear();

        curl_easy_setopt(m_curl, CURLOPT_POST, 1);
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpClient::writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ret);
        if(data.length())
        {
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());
        }
        curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, atol(Flyer::globalConfMap["httptimeout"].c_str()));
        curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
        CURLcode res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
        {
            Error(Flyer::logger,"[post请求] 失败(" << m_url << "," << res << "," << error << ")"); 
            break;
        }
        flag = true;
    }while(false);
    return flag;
}

bool HttpClient::get(std::string &ret, const std::string &data)
{
    bool flag = false;
    do
    {
        if(!m_curl)
        {
            break;
        }
        reset();
        char error[CURL_ERROR_SIZE];
        bzero(error,sizeof(error));
        ret.clear();

        curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1);
        std::string url = m_url + "?";
        url += data;
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpClient::writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ret);
        curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, atol(Flyer::globalConfMap["httptimeout"].c_str()));
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
        CURLcode res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
        {
            Error(Flyer::logger,"[get请求] 失败(" << m_url << "," << res << "," << error << ")"); 
            break;
        }
        flag = true;
    }while(false);
    return flag;
}

size_t HttpClient::writer(const char *data, size_t size, size_t mem, std::string *buffer)
{
    size_t len = 0;
    do
    {
        if(!buffer)
        {
            break;
        }
        len = size * mem;
        buffer->append(data, len);
        Info(Flyer::logger,"[get返回](" << *buffer << ")");
    }while(false);
    return len;
}
        
bool HttpClient::postNoReturn(std::string &ret, const std::string &data)
{
    bool flag = false;
    do
    {
        if(!m_curl)
        {
            break;
        }
        reset();
        char error[CURL_ERROR_SIZE];
        bzero(error,sizeof(error));
        ret.clear();

        curl_easy_setopt(m_curl, CURLOPT_POST, 1);
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpClient::writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ret);
        if(data.length())
        {
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());
        }
        curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, atol(Flyer::globalConfMap["httptimeout"].c_str()));
        curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
        CURLcode res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
        {
            Error(Flyer::logger,"[post请求] 失败(" << m_url << "," << res << "," << error << ")"); 
            break;
        }
        flag = true;
    }while(false);
    return flag;
}

bool HttpClient::getNoReturn(std::string &ret, const std::string &data)
{
    bool flag = false;
    do
    {
        if(!m_curl)
        {
            break;
        }
        reset();
        char error[CURL_ERROR_SIZE];
        bzero(error,sizeof(error));
        ret.clear();

        curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1);
        std::string url = m_url + "?";
        url += data;
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpClient::writer);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ret);
        curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, atol(Flyer::globalConfMap["httptimeout"].c_str()));
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
        CURLcode res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
        {
            Error(Flyer::logger,"[get请求] 失败(" << m_url << "," << res << "," << error << ")"); 
            break;
        }
        flag = true;
    }while(false);
    return flag;
}


