#include "mysqlUrl.h"
#include "flyer.h"

UrlInfo::UrlInfo(const std::string &url) : m_host(),m_num(0),m_port(0),m_account(),m_passwd(),m_dbName(),m_code(0),m_valid(false)
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
        if(splitVec.size() != 7)
        {
            break;
        }
        m_code = atol(splitVec[0].c_str());
        m_num = atol(splitVec[1].c_str());
        m_host = splitVec[2];
        m_port = atol(splitVec[3].c_str());
        m_account = splitVec[4];
        m_passwd = splitVec[5];
        m_dbName = splitVec[6];
        m_valid = true;
        ret = m_valid;
    }while(false);

    std::ostringstream oss;
    oss << "[数据库连接] 解析" << (m_valid ? "成功" : "失败") << "(" << url << "," << m_host << "," << m_port << "," << m_account << "," << m_passwd << "," << m_dbName << ")";
    Info(Flyer::logger,oss.str().c_str());
    return ret;
}
