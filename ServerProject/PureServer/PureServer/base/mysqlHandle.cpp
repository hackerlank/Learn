#include "mysqlHandle.h"

unsigned int MysqlHandle::s_tempid = 0;

MysqlHandle::MysqlHandle(const UrlInfo &urlInfo) : m_urlInfo(urlInfo),m_id(++s_tempid),m_mysql(NULL),m_status(Handle_Invalid),m_usedCnt(0),m_lifeTime()
{
}

bool MysqlHandle::init()
{
    if(!initMysql())
    {
        closeHandle();
        return false;
    }
    return true;
}

bool MysqlHandle::initMysql()
{
    bool ret = false;
    do
    {
        if(m_mysql)
        {
            mysql_close(m_mysql);
            m_mysql = NULL;
        }
        m_mysql = mysql_init(NULL);
        if(!m_mysql || !m_urlInfo.getValid())
        {
            break;
        }
        if(!mysql_real_connect(m_mysql,m_urlInfo.getHost(),m_urlInfo.getAccount(),m_urlInfo.getPasswd(),m_urlInfo.getDBName(),m_urlInfo.getPort(),NULL,0))
        {
            break;
        }
        if(mysql_set_character_set(m_mysql,"utf8"))
        {
            break;
        }
        m_status = Handle_Valid;
        m_usedCnt = 0;
        ret = true;
    }while(false);
    
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[数据库连接] 连接%s(%s,%u,%s,%s,%s)",ret ? "成功" : "失败",m_urlInfo.getHost(),m_urlInfo.getPort(),m_urlInfo.getAccount(),m_urlInfo.getPasswd(),m_urlInfo.getDBName());
    Info(Flyer::logger,temp);
    return ret;
}

void MysqlHandle::closeHandle()
{
    if(m_mysql)
    {
        mysql_close(m_mysql);
        m_mysql = NULL;
    }
    m_status = Handle_Invalid;
}

unsigned int MysqlHandle::getID()
{
    return m_id;
}

HandleStatus MysqlHandle::getStatus()
{
    return m_status;
}

bool MysqlHandle::checkConnect()
{
    bool ret = false;
    do
    {
        if(mysql_ping(m_mysql))
        {
            break;
        }
        if(m_usedCnt >= atol(Flyer::globalConfMap["maxmysqlusecnt"].c_str()))
        {
            break;
        }
        if(m_lifeTime.elapse() >= (unsigned int)atol(Flyer::globalConfMap["maxmysqlusetime"].c_str()))
        {
            break;
        }
        ret = true;
    }while(false);

    if(!ret)
    {
        if(!initMysql())
        {
            closeHandle();
            return false;
        }
    }
    m_status = Handle_Used;
    ++m_usedCnt;
    m_lifeTime.now();
    return true;
}

bool MysqlHandle::execSql(const char *sql,const unsigned int sqlLen)
{
   bool ret = false;
   do
   {
       if(!sql || !sqlLen)
       {
           break;
       }
       if(mysql_real_query(m_mysql,sql,sqlLen))
       {
           Error(Flyer::logger,"[数据库连接] 执行失败(" << sql << "," << sqlLen << ")");
           break;
       }
       ret = true;
   }while(false);

   return ret;
}

