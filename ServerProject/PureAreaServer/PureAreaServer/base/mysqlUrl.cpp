#include "mysqlUrl.h"
#include "flyer.h"

UrlInfo::UrlInfo(const std::string &url) : m_host(),m_port(0),m_account(),m_passwd(),m_dbName(),m_code(0),m_valid(false)
{
    parseUrl(url);
}

bool UrlInfo::parseUrl(const std::string &url)
{
    bool ret = false;
    do
    {
        if(m_valid || url.empty())
        {
            break;
        }
        using namespace boost::algorithm;
        std::vector<std::string> splitVec;
        split(splitVec,url,is_any_of(":"),token_compress_on);
        if(splitVec.size() != 6)
        {
            break;
        }
        m_code = atol(splitVec[0].c_str());
        m_host = splitVec[1];
        m_port = atol(splitVec[2].c_str());
        m_account = splitVec[3];
        m_passwd = splitVec[4];
        m_dbName = splitVec[5];
        m_valid = true;
        ret = m_valid;
    }while(false);

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[数据库连接] 解析%s(%s,%s,%u,%s,%s,%s)",m_valid ? "成功" : "失败",url.c_str(),m_host.c_str(),m_port,m_account.c_str(),m_passwd.c_str(),m_dbName.c_str());
    Info(Flyer::logger,temp);
    return ret;
}
