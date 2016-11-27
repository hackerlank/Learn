#ifndef FLYER_H
#define FLYER_H

#include "head.h"
#define Debug LOG4CXX_DEBUG
#define Info  LOG4CXX_INFO
#define Error LOG4CXX_ERROR 
namespace Flyer
{
    extern log4cxx::LoggerPtr logger;
    extern unsigned int seed; 
    //全局属性键值对
    extern std::map<std::string,std::string> globalConfMap;
    //初始化全局变量
    void init();
    //设置logger属性
    void setLogger(const std::string &fileName);
    //产生随机数
    int randBetween(int min,int max);
    //打印globalConfMap内容
    void logGlobalMap();
    //更改日志
    void changeLogger(const char *file,const unsigned long now);
};


#endif

