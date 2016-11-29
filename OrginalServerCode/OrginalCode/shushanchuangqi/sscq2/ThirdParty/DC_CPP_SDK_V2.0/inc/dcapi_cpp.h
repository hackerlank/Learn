#ifndef _H_DCAPI_H_
#define _H_DCAPI_H_

#include <string>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/un.h>

using namespace std;

class Sampling;
namespace DataCollector
{
    class SocketClient;

    typedef char logtype ;
    const logtype LT_NORMAL   = 0;   // 经分数据上报
    const logtype LT_MOD      = 1;   // 模调数据上报
    const logtype LT_BASE	  = 2;	 // 基础数据
    const logtype LT_MONITOR  = 3;	 // 监控数据
    const logtype LT_SECDATA  = 4;   // 安全数据上报

    class CLogger
    {
        public:
            enum ProType
            {
                PRO_STRING = 0,
                PRO_BINARY = 1,
            };


            //==========================================
            // 名称：constructor
            // 参数：sockettype, 0: unix domain socket, other :tcp protocol
            // needrsp, 短链接建议填true，长链接建议填false
            // 返回：无
            // 说明：通常情况直接使用默认参数
            //============================================
            CLogger(char socketType = 0, bool needRsp = false);
            ~CLogger();



            //==========================================
            // 名称：init
            // 参数：logname  dc用来区分业务的标识
            // 业务数据必须去相关页面申请
            // isModule  是否为模调数据
            // 填false
            // 返回：0 成功 !0 失败
            // 说明：初始化业务数据上报，只能调用一次
            //============================================
            int init(string& logName, bool isModule = false);

            //==========================================
            // 名称：init
            // 参数：mid
            // 请填主调ID(235000036)
            // 返回：0 成功 !0 失败
            // 说明：初始化模调数据上报，只能调用一次
            //============================================
            int init(int mid);




            //==========================================
            // 名称：encode
            // 参数：src_data 原字符串 
            // dst_data 编码后字符串
            // 返回：0 成功 !=0 失败
            // 说明：简单的编码函数
            //============================================
            int encode(string& src_data, string& dst_data);


            //===========================================
            // 名称：write_baselog
            // 返回：0 成功 != 0 失败
            // 参数：logtype	数据上报的类型
            // data		编码后的数据，业务需要直接传递格式为 "k1=v1&k2=v2"的数据(v2已经做过编码)
            // len       数据的长度
            // proType   0:字符串
            //           1:二进制
            // timestamp   unix时间戳，默认值为系统当前时间
            // 说明：数据上报函数，一般用于非落地数据的上报，不需要调用commit，也不分配序列号
            //=============================================
            int write_baselog(const char* data, unsigned int len, char logType, char proType, unsigned int timestamp = time(NULL));

            //===========================================
            // 名称：write_baselog   兼容1.0
            // 返回：0 成功 != 0 失败
            // 参数：logtype	数据上报的类型
            // data		编码后的数据，业务需要直接传递格式为 "k1=v1&k2=v2"的数据(v2已经做过编码)
            // fallFlag    该参数已不能控制是否落地，由后端配置项决定
            // timestamp   unix时间戳，默认值为系统当前时间
            // 说明：数据上报函数，一般用于非落地数据的上报
            //=============================================
            int write_baselog(logtype type, string& data, bool fallFlag = true, unsigned int timestamp = time(NULL));

            //===========================================
            // 名称：write_modulelog
            // 返回：0 成功 != 0 失败
            // 参数：		  sid               被调ID
            // ifid              接口ID
            // mip		    主调IP
            // sip               被调IP
            // retval            返回值
            // result	    调用结果结果
            // reservedInt0      保留字段，整数
            // reservedInt1	    保留字段，整数
            // reservedStr0      保留字段，字符串
            // reservedStr1      保留字段，字符串
            // 说明：模调数据上报函数
            //=============================================
            int write_modulelog(int sid, int ifid, string& mip, string& sip, int retval, int result, int delay, int reservedInt0, int reservedInt1, string& reservedStr0, string& reservedStr1);

            //===========================================
            // 名称：get_errmsg
            // 返回：错误信息
            // 参数：空				  
            // 说明：返回调用失败时的错误信息
            //==============================================
            string get_errmsg(void);


        private:

            SocketClient *pSocketClient;
            Sampling *pSampling;

            pthread_rwlock_t  errMsgrwlock;

            string appname;	
            string errmsg;	//last errmsg
            int rspMsgLen;
            int reqMsgHdrLen;


            int addrLen;
            bool needRsp;
            int socketType;

            int m_iMid;

            bool isInit;

            unsigned short appnameLen;
            unsigned short appnamePartLen;

        private:

            void update_errmsg(const char* cErrmsg, ...);

            void write_bin_file(const char* data, unsigned int len, const char* fileName);


            int inner_encode(string& src_data, string& dst_data);

            int comm_write(const char* data, unsigned short len, char logType = -1, char proType = -1, unsigned int tm = time(NULL));

            void encode_str(char* &p, string& str);

            string&    replace_all(string&    str,const    string&    old_value,const    string&    new_value);
    };

};

#endif

