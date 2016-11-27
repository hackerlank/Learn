#include "flyer.h"

namespace Flyer
{
    log4cxx::LoggerPtr logger;
    unsigned int seed;
    std::map<std::string,std::string> globalConfMap;
    void init()
    {
        seed = 0;
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
