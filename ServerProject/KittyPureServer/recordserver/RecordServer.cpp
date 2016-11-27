/**
 * \file
 * \version  $Id: RecordServer.cpp 65 2013-04-23 09:34:49Z  $
 * \author  ,okyhc@263.sina.com
 * \date 2004年12月10日 10时55分53秒 CST
 * \brief zebra项目档案服务器，用于创建、储存和读取档案
 *
 */

#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "RecordServer.h"
#include "RecordTask.h"
#include "zDBConnPool.h"
#include "zConfile.h"
#include "RecordUserManager.h"
#include "RecordUser.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "zProperties.h"
#include "xmlconfig.h"
#include "tbx.h"
#include "RecordTaskManager.h"
#include <google/protobuf/descriptor.h>

zDBConnPool *RecordService::dbConnPool = NULL;
MetaData* RecordService::metaData = NULL;

const Fir::XMLParser::Node *load_xmlconfig(Fir::XMLParser &xml, const char *filename)
{
    std::string path = Fir::global["configdir"];
    path += filename;
    xml.load_from_file(path.c_str());
    return xml.root();
}

void load_tbx_config(const std::string &filename, byte *&buf, int &size)
{
    std::string path("tbx/");
    path += filename;
    FILE *fp = fopen(path.c_str(), "rb+");
    if (fp) 
    {
        fseek(fp, SEEK_SET, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buf = new byte[size];   
        if(fread(buf, size, 1, fp));
        fclose(fp);
    }   
}

/**
 * \brief 初始化网络服务器程序
 *
 * 实现了虚函数<code>zService::init</code>
 *
 * \return 是否成功
 */
bool RecordService::init()
{
    //加载xml配置文件
    config::init(std::bind(&load_xmlconfig, std::placeholders::_1, std::placeholders::_2));

    verify_version = atoi(VERSION_STRING);
    Fir::logger->info("服务器版本号:%d",verify_version);
    strncpy(pstrIP, zSocket::getIPByIfName(Fir::global["ifname"].c_str()), MAX_IP_LENGTH - 1);
    if (!zSubNetService::init())
    {
        Fir::logger->debug("[DB服] 初始化网路服务器失败");
        return false;
    }

    //加载tbx配表
    if (!initConfig())
    {
        Fir::logger->debug("DB服] 加载excel配置失败");
        return false;
    }

    dbConnPool = zDBConnPool::newInstance(NULL);
    const char* pmysql = Fir::global["mysql"].c_str(); 
    metaData = MetaData::newInstance("");
    if (!dbConnPool || !dbConnPool->putURL(0, pmysql, false) || !metaData || !metaData->init(pmysql))
    {   
        Fir::logger->debug("[DB服] 连接数据库失败");
        return false;
    }

    if (!zMemDBPool::getMe().init() || (NULL == zMemDBPool::getMe().getMemDBHandle()))
    {
        Fir::logger->debug("[DB服] 连接内存数据库失败");
        return false;
    }

    //初始化连接线程池
    int state = state_none;
    Fir::to_lower(Fir::global["initThreadPoolState"]);
    if ("repair" == Fir::global["initThreadPoolState"] || "maintain" == Fir::global["initThreadPoolState"])
    {
        state = state_maintain;
    }

    taskPool = new zTCPTaskPool(atoi(Fir::global["threadPoolCapacity"].c_str()), state);
    if (NULL == taskPool || !taskPool->init())
    {
        Fir::logger->debug("[DB服] 初始化任务连接池失败");
        return false;
    }

    Fir::logger->removeLocalFileLog(Fir::global["logfilename"]);
    zConfile::CreateLog("recordserver","logfilename",atoi(Fir::global["logself"].c_str()) > 0,getServerID());
    Fir::logger->addLocalFileLog(Fir::global["logfilename"]);

    if (!RecordUserM::getMe().init())
    {
        Fir::logger->debug("[DB服] 加载角色数据失败");
        return false;
    }
    load();
    if(!RecordTimeTick::getMe().start())
    {
        Fir::logger->debug("[DB服] 时间线程启动失败");
        return false;
    }
    if(getMaxsqlLen() == 0)
    {
        Fir::logger->debug("[DB服] 无法获得SQL语句最大长度");
        return false;
    }
    return true;
}

DWORD RecordService::getMaxsqlLen()
{
    if(max_sqlLen != 0)
    {
        return max_sqlLen;
    }
    connHandleID handle = dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能获取数据库句柄");
        return 0;
    }

    const dbCol dbCol[] = 
    {
        {"Variable_name",   zDBConnPool::DB_STR,    50  },
        {"Value",      zDBConnPool::DB_DWORD,  sizeof(DWORD)},
        { NULL, 0, 0}
    };

    struct stReadData
    {   
        stReadData()
        {
            Value = 0;
            memset(Variable_name,0,sizeof(Variable_name));
        }   
        char  Variable_name[50];
        QWORD Value;
    }__attribute__ ((packed)) read_data;
    char buf[255];
    sprintf(buf,"SHOW VARIABLES LIKE 'max_allowed_packet';");
    std::string sql(buf); 
    unsigned int retcode = RecordService::dbConnPool->execSelectSql(handle, sql.c_str(), sql.length(), dbCol, 1, (BYTE *)(&read_data));
    dbConnPool->putHandle(handle);
    if (1 == retcode)
    {  
        max_sqlLen = read_data.Value;
        return max_sqlLen;
    }   
    Fir::logger->error("加载最大sql长度失败");
    return 0;
}

/**
 * \brief 新建立一个连接任务
 *
 * 实现纯虚函数<code>zNetService::newTCPTask</code>
 *
 * \param sock TCP/IP连接
 * \param addr 地址
 */
void RecordService::newTCPTask(const int sock, const struct sockaddr_in *addr)
{
    RecordTask *tcpTask = new RecordTask(taskPool, sock, addr);
    if (NULL == tcpTask)
    {
        //内存不足，直接关闭连接
        TEMP_FAILURE_RETRY(::close(sock));
    }
    else if(!taskPool->addVerify(tcpTask))
    {
        //得到了一个正确连接，添加到验证队列中
        SAFE_DELETE(tcpTask);
    }
}

bool RecordService::msgParseSuperCmd(const CMD::SUPER::SuperServerNull *superNull,const DWORD nCmdLen)
{
    using namespace CMD::SUPER;
    switch(superNull->para)
    {
        case PARA_ZONE_ID:
            {
                t_ZoneID *rev = (t_ZoneID *)superNull;
                RecordService::getMe().zoneID = rev->zone;
                Fir::logger->debug("收到区编号 %u(%u, %u)", RecordService::getMe().zoneID.id, RecordService::getMe().zoneID.game, RecordService::getMe().zoneID.zone);
                return true;
            }
        case PARA_GAMETIME:
            {
                unsigned long long grap = Fir::qwGameTime - RecordTimeTick::currentTime.sec();
                RecordTimeTick::currentTime.setgrap(grap * 1000);
                RecordTimeTick::currentTime.now();
                Fir::logger->debug("[修改时间]:%s,%llu",RecordTimeTick::currentTime.toString().c_str(),grap);
                return true;
            }
            break;
        case PARA_RELOAD_CONFIG:
            {
                Fir::logger->debug("[重新加载配置]:%u",RecordService::getMe().getServerID());
                return true;
            }
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, superNull->cmd, superNull->para, nCmdLen);
    return false;
}




/**
 * \brief 解析来自服务器管理器的指令
 *
 * 这些指令是网关和服务器管理器交互的指令<br>
 * 实现了虚函数<code>zSubNetService::msgParse_SuperService</code>
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析是否成功
 */
bool RecordService::msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
    using namespace CMD::SUPER;
    switch (ptNullCmd->cmd)
    {
        case SUPERCMD:
            {
                return msgParseSuperCmd((SuperServerNull*)ptNullCmd,nCmdLen);
            }
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return false;
}

/**
 * \brief 结束网络服务器
 *
 * 实现了纯虚函数<code>zService::final</code>
 *
 */
void RecordService::final()
{
    //场景链接是否回收了
    while(!RecordTaskManager::getMe().sceneTaskEmpty())
    {
        zThread::msleep(100);
    }
    RecordUserM::getMe().saveplayer(true);
    if(taskPool)
    {
        taskPool->final();
        SAFE_DELETE(taskPool);
    }

    zSubNetService::final();

    zDBConnPool::delInstance(&dbConnPool);
    CHECK_LEAKS;
    Fir::logger->debug(__PRETTY_FUNCTION__);
}

/**
 * \brief 命令行参数
 *
 */
static struct argp_option record_options[] =
{
    {"daemon",		'd',	0,			0,	"Run service as daemon",						0},
    {"log",			'l',	"level",	0,	"Log level",									0},
    {"logfilename",	'f',	"filename",	0,	"Log file name",								0},
    {"objlogfilename",	'o',	"objfilename",	0,	"object Log file name",								0},
    {"mysql",		'y',	"mysql",	0,	"MySQL[mysql://user:passwd@host:port/dbName]",	0},
    {"ifname",		'i',	"ifname",	0,	"Local network device",							0},
    {"server",		's',	"ip",		0,	"Super server ip address",						0},
    {"port",		'p',	"port",		0,	"Super server port number",						0},
    {0,				0,		0,			0,	0,												0}
};

/**
 * \brief 命令行参数解析器
 *
 * \param key 参数缩写
 * \param arg 参数值
 * \param state 参数状态
 * \return 返回错误代码
 */
static error_t record_parse_opt(int key, char *arg, struct argp_state *state)
{
    switch (key)
    {
        case 'd':
            {
                Fir::global["daemon"] = "true";
            }
            break;
        case 'p':
            {
                Fir::global["port"]=arg;
            }
            break;
        case 's':
            {
                Fir::global["server"]=arg;
            }
            break;
        case 'l':
            {
                Fir::global["log"]=arg;
            }
            break;
        case 'f':
            {
                Fir::global["logfilename"]=arg;
            }
            break;
        case 'o':
            {
                Fir::global["objlogfilename"]=arg;
            }
        case 'y':
            {
                Fir::global["mysql"]=arg;
            }
            break;
        case 'i':
            {
                Fir::global["ifname"]=arg;
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/**
 * \brief 简短描述信息
 *
 */
static char record_doc[] = "\nRecordServer\n" "\t档案服务器。";

/**
 * \brief 程序的版本信息
 *
 */
const char *argp_program_version = "Program version :\t" VERSION_STRING\
                                    "\nBuild version   :\t" _S(BUILD_STRING)\
                                    "\nBuild time      :\t" __DATE__ ", " __TIME__;

/**
 * \brief 读取配置文件
 *
 */
class RecordConfile:public zConfile
{
    bool parseYour(const xmlNodePtr node)
    {
        if (node)
        {
            xmlNodePtr child=parser.getChildNode(node,NULL);
            while(child)
            {
                parseNormal(child);
                child=parser.getNextNode(child,NULL);
            }
            return true;
        }
        else
            return false;
    }
};

bool RecordService::initConfig()
{
    Fir::XMLParser xml;
    std::string path("tbx/tbx.xml");
    xml.load_from_file(path.c_str());
    tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));
    return true;
}

/**
 * \brief 重新读取配置文件，为HUP信号的处理函数
 *
 */
void RecordService::reloadconfig()
{
    //初始化配置文件系统
    config::init(std::bind(&load_xmlconfig, std::placeholders::_1, std::placeholders::_2));
    Fir::XMLParser xml;
    std::string path("tbx/tbx.xml");
    xml.load_from_file(path.c_str());
    tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));

    if (!RecordUserM::getMe().init())
    {
        Fir::logger->error("重新加载配置 RecordUser管理器模块...失败");
        return;
    }
    Fir::logger->info("重新加载配置 RecordUser管理器模块...成功");
    Fir::logger->debug("重新加载配置");
}

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */
int main(int argc, char **argv)
{
    Fir::initGlobal();
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Fir::logger=new zLogger("RS"); 

    //设置缺省参数
    Fir::global["configdir"] = "gametools/parseXmlTool/xmldir/";
    Fir::global["t_recordbinary"] = "t_recordbinary";
    //解析配置文件参数
    RecordConfile rc;
    if (!rc.parse("recordserver"))
    {
        Fir::logger->debug("[DB服] 读取config文件失败");
        return EXIT_FAILURE;
    }

    zConfile::CreateLog("recordserver","logfilename",atoi(Fir::global["logself"].c_str()) > 0 );
    //解析命令行参数
    zArg::getArg()->add(record_options, record_parse_opt, 0, record_doc);
    zArg::getArg()->parse(argc, argv);

    //设置日志级别
    Fir::logger->setLevel(Fir::global["log"]);
    //设置写本地日志文件
    if ("" != Fir::global["logfilename"])
    {
        Fir::logger->addLocalFileLog(Fir::global["logfilename"]);
    }

    //是否以后台进程的方式运行
    if ("true" == Fir::global["daemon"])
    {
        Fir::logger->info("Program will be run as a daemon");
        Fir::logger->removeConsoleLog();
        if(daemon(1, 1));
    }

    RecordService::getMe().main();
    google::protobuf::ShutdownProtobufLibrary();
    Fir::finalGlobal();
    return EXIT_SUCCESS;
}

