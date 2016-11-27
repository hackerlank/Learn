#include "flyer.h"

namespace Flyer
{
    log4cxx::LoggerPtr logger;
    unsigned int seed;
    unsigned long msglen;
    std::map<std::string,std::string> globalConfMap;
    void init()
    {
        msglen = 1024;
        seed = 0;
        globalConfMap.clear();
    }
    void destory()
    {
        log4cxx::Appender* appender = logger->getAppender("file");
        if(appender)
        {
            logger->removeAppender(appender);
            appender->close();
        }

#if 0
        delete logger;
#endif
        globalConfMap.clear();
    }
    void setLogger(const std::string &fileName)
    {
        //先删除
        log4cxx::Appender* oldAppender = logger->getAppender("file");
        if(oldAppender)
        {
            logger->removeAppender(oldAppender);
            //oldAppender->close();
        }
        log4cxx::PatternLayoutPtr layOut = new log4cxx::PatternLayout("%d{\%y\%m\%d-\%H:\%M:\%S }%c %5p:[%l] %m%n");
        log4cxx::FileAppender *appender = new log4cxx::FileAppender(layOut,fileName);
        appender->setName("file");
        appender->setEncoding("UTF-8");
        logger->addAppender(appender);

        if(!logger->getAppender("console"))
        {
            log4cxx::ConsoleAppenderPtr console = new log4cxx::ConsoleAppender(layOut);
            console->setName("console");
            logger->addAppender(console);
        }
    }
    void changeLogger(const char *file,const unsigned long now)
    {
        char fileName[100] = {0};
        if(now)
        {
            tm *localTime = localtime((time_t*)&now);
            snprintf(fileName,sizeof(fileName),"%s-%02d-%02d-%02d-%02d-%02d.log",file,localTime->tm_year + 1900,localTime->tm_mon + 1,localTime->tm_mday,localTime->tm_hour,localTime->tm_min);
        }
        else
        {
            snprintf(fileName,sizeof(fileName),"%s",file);
        }
        LOG4CXX_INFO(Flyer::logger,fileName);
        Flyer::setLogger(fileName);
    }

    int randBetween(int min,int max)
    {
        if(min == max)
        {
            return min;
        }
        if(min < max)
        {
            return min + int(((double)max - (double)min + 1.0) * rand_r(&seed) / (RAND_MAX+1.0));
        }
        return max + int(((double)min - (double)max + 1.0) * rand_r(&seed) / (RAND_MAX+1.0));
    }

    void logGlobalMap()
    {
        Debug(Flyer::logger,"测试全局配置开始(" << globalConfMap.size() << ")");
        for(auto iter = globalConfMap.begin();iter != globalConfMap.end();++iter)
        {
            Debug(Flyer::logger,"全局变量(" << iter->first << "," << iter->second << ")");
        }
        Debug(Flyer::logger,"测试全局配置结束(" << globalConfMap.size() << ")");
    }
};
