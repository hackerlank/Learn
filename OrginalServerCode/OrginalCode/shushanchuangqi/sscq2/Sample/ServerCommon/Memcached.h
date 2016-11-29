
#ifndef _WIN32

#include <vector>
#include <libmemcached/memcached.h>
#include <curl/curl.h>
#include "Tokenizer.h"
#include "Config.h"
#include "RTime.h"

extern bool bMemcinited;
extern memcached_st memc;
extern int memc_version;
extern int g_platform_login_number[256];
extern CURL* curl;

//static const char* MemcachedGet(const char* key, size_t key_size, char* value, size_t size);
//static bool MemcachedSet(const char* key, size_t key_size, const char* value, size_t size, int timeout = -1);
static bool initMemcache()
{
    if (!bMemcinited)
    {
        memcached_return rc;
        memcached_create(&memc);
        //memcached_behavior_set(&memc,MEMCACHED_BEHAVIOR_TCP_NODELAY,1);
        //memcached_behavior_set(&memc,MEMCACHED_BEHAVIOR_NOREPLY,1);
        size_t sz = Config._vecTokenServer.size();
        for (size_t i = 0; i < sz; ++i)
        {
            string strAddr = Config._vecTokenServer[i].strAddr;
            UINT16 wPort   = Config._vecTokenServer[i].wPort;
            LOG_WRN << "strAddr:" << strAddr << " wPort:" << wPort;
            memcached_server_list_st servers = memcached_server_list_append(NULL, strAddr.c_str(), wPort, &rc);
            if (rc == MEMCACHED_SUCCESS)
            {
                rc = memcached_server_push(&memc, servers);
                memcached_server_list_free(servers);
                bMemcinited = true;
            }
        }
    }
    if (!curl)
        curl = curl_easy_init();

    if (bMemcinited)
    {
        memc_version = (rand()*(rand()/132))%0x8FFFFFFF;
        LOG_CRI << "memc_version: " << memc_version;
    }
    return bMemcinited;
}

__attribute__((destructor)) static void uninitMemcache()
{
    if (bMemcinited)
    {
        bMemcinited = false;
        memcached_free(&memc);
        //memcached_servers_reset(&memc);
    }
    if (curl)
    {
        curl_easy_cleanup(curl);
        curl = NULL;
    }
}
# if 0
const char* MemcachedGet(const char* key, size_t key_size, char* value, size_t size)
{
    if (!bMemcinited || !key || !key_size || !value || !size)
        return 0;

    size_t tlen = 0;
    unsigned int flags = 0;

    int retry = 3;
    memcached_return rc;
    bool got = false;

    while (retry)
    {
        --retry;
        char* rval = memcached_get(&memc, key, key_size, &tlen, &flags, &rc);
        if (rc == MEMCACHED_SUCCESS && rval && tlen)
        {
            tlen = tlen > size ? tlen : size;
            memcpy(value, rval, tlen);
            free(rval);
            got = true;
            break;
        }
        else
        {
            usleep(500);
        }
    }
    LOG_CRI << "memc get key:" << key << " value:" << value;
    return got?value:NULL;
}

bool MemcachedSet(const char* key, size_t key_size, const char* value, size_t size, int timeout)
{
    if (!bMemcinited || !key || !key_size || !value || !size)
        return false;

    memcached_return_t rc = memcached_set(&memc, key, key_size, value, size, timeout, 0);

    int retry = 2;
    while (rc != MEMCACHED_SUCCESS && retry)
    {
        rc = memcached_set(&memc, key, key_size, value, size, timeout, 0);
        --retry;
    }

    LOG_CRI << "memc set key:" << key << " value:" << value << " memcached_return_t:" << rc;
    return rc == MEMCACHED_SUCCESS;
}

#ifdef CALL_OPEN_API
#define MAX_RET_LEN 1024
static int recvret(char* data, size_t size, size_t nmemb, char* buf)
{
    size_t nsize = size * nmemb;
    if (nsize > MAX_RET_LEN)
    {
        //bcopy(data, buf, MAX_RET_LEN);
        memcpy(buf, data, MAX_RET_LEN);
        return MAX_RET_LEN;
    }

    memcpy(buf, data, nsize);
    //bcopy(data, buf, nsize);
    return nsize;
}

static bool callOpenApi(const std::string& strParam)
{
    if (!Config._strRechargeUrl.length())
        return true;
    if (!curl)
        return false;
    char strUrl[4096] = {0};
    snprintf(strUrl, sizeof(strUrl), "%s?%s", Config._strRechargeUrl.c_str(), strParam.c_str());
    LOG_WRN << "CHARGE URL: " << strUrl;

    char buffer[MAX_RET_LEN] = {0};
    curl_easy_setopt(curl, CURLOPT_URL, strUrl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recvret);     //回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);         //存储指针
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    CURLcode res = curl_easy_perform(curl);
    if (CURLE_OK == res)
    {
        LOG_CRI << "callOpenApi [OK]:" << curl;
        const char* msg = strcasestr(buffer, "msg");
        if (!msg)
            return false;
        if (strcasestr(msg, "ok"))
            return true;
    }
    else
    {
        LOG_CRI << "callOpenApi [ERROR]:" << curl;
    }
    return false;
}
#endif
#endif
static void CheckRechargeToken(UINT64 qwUserID, const string& strToken, UINT16 wGoldID, const string& strParam, UINT8& byRet, string& strErr)
{
    (void)CheckRechargeToken;
    //initMemcache();
    if (!bMemcinited)
    {
        byRet = 6;
        strErr += "strToken server error.";
        return;
    }

    size_t len = 0;
    size_t tlen = 0;
    unsigned int flags = 0;
    char key[MEMCACHED_MAX_KEY] = {0};

    int retry = 3;
    memcached_return rc;
    len = snprintf(key, sizeof(key), "token_1103826576_%" I64_FMT "u_%s_%u", qwUserID, strToken.c_str(), wGoldID);
    while (retry)
    {
        --retry;
        char* rstrToken = memcached_get(&memc, key, len, &tlen, &flags, &rc);
        timediff_t tBegin = RTime().usecs();
        LOG_WRN << "memc get key:" << key << " value:" << rstrToken << ", time: " << tBegin << "rc: " << rc;
        if (rc == MEMCACHED_SUCCESS && rstrToken && tlen)
        {
            byRet = 0;
            if (strncmp(strToken.c_str(), rstrToken, strToken.length()) != 0)
                byRet = 2;
            free(rstrToken);

#ifdef CALL_OPEN_API
            if (byRet == 0 && !callOpenApi(strParam))
            {
                strErr = "confirm error.";
                byRet = 4;
            }
#endif
            break;
        }
        else
        {
            byRet = 3;
            usleep(500);
        }
    }

    if (byRet == 2)
        strErr += "strToken is not matched.";
    else if (byRet == 3)
        strErr += "fetch strToken value error.";

    if (rc == MEMCACHED_SUCCESS && !byRet)
    {
        rc = memcached_delete(&memc, key, len, (time_t)0);
        if (rc == MEMCACHED_SUCCESS)
            LOG_WRN << "delete memcached_key right";
        else
            LOG_WRN << "delete memcached_key error";
    }

    if (strErr.length() && byRet != 1)
    {   //重新初始化Memcache
        LOG_CRI << "key:" << key << ", strToken:" << strToken.c_str() << ", ret:" << byRet << ", rc:" << rc << ", strErr:" << strErr.c_str();
        uninitMemcache();
        initMemcache();
    }
}

#if 0
static void setCrackValue(const char* ip, int v, int serverNo)
{
    (void)setCrackValue;
    int timeout = 24*60*60;
    initMemcache();
    if (bMemcinited)
    {
        char value[64] = {0};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "%d_%s_%d", memc_version, ip, serverNo);
        size_t vlen = snprintf(value, sizeof(value), "%d", v);
        MemcachedSet(key, len, value, vlen, timeout);
    }
}

static void setForbidSaleValue(const UINT64 playerId, bool isForbid, UINT32 fTime = 9999999)
{
    (void)setForbidSaleValue;
    initMemcache();
    if(fTime > 99999999 ||fTime < 0)
        return ;
    if (bMemcinited)
    {
        char value[32] = {'0'};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "asss_globallock_%" I64_FMT "u", playerId);
        if (isForbid) value[0] = '1';
        UINT32 dwCurTime = time(NULL);
        sprintf(&value[1],"%d", dwCurTime);
        {
            if(fTime != 9999999)
                sprintf(&value[1],"%d_%d", dwCurTime, dwCurTime+fTime);
            else
                sprintf(&value[1],"%d", dwCurTime);
        }
        
        size_t vlen = strlen(value);

        MemcachedSet(key, len, value, vlen, 0);
    }
}

static bool checkForbidSale(const UINT64 playerId, std::string& fsale, std::string& over)
{
    (void)checkForbidSale;
    initMemcache();
    std::string t="0";
    char value[32] = {0};
    char key[MEMCACHED_MAX_KEY] = {0};
    UINT64 pid = playerId & 0xFFFFFFFFFF;
    size_t len = snprintf(key, sizeof(key), "asss_globallock_%" I64_FMT "u", pid);

    if (bMemcinited)
        MemcachedGet(key, len, value, sizeof(value));
    if (strlen(value) > 1)
        t = &(value[1]);
    
    
//    return value[0] == '1';
    
    
    if(value[0]=='0' || value[0] == 0 )
    {
        fsale = '0';
        over = "0";
        return false;
    }
    Tokenizer tk(t, "_");
    if(tk.size() < 2)
    {
        fsale=t;
        over = "1577808000";    //2020年1月1号
        return true;
    }
    fsale =tk[0];
    over = tk[1];
    if(time(NULL) > static_cast<UINT32>(atoi( over.c_str() ) ) )
    {
        fsale = '0';
        over = "0";
        setForbidSaleValue(playerId,false);
        return false;
    }
    return true;
}

static bool checkCrack(std::string& platform, std::string& ip, UINT64 id, int serverNo)
{
    (void)checkCrack;
    int pf = atoi(platform.c_str());
    if (!pf)
        return false;

    if (ip.empty())
        return false;

//    if (pf == 11 || pf == 17)
    if (pf >= 0 && pf < 255) 
    {
        initMemcache();
        if (bMemcinited)
        {
            size_t len = 0;
            char key[MEMCACHED_MAX_KEY] = {0};
            char value[32] = {0};

            len = snprintf(key, sizeof(key), "%d_%s_%d", memc_version, ip.c_str(), serverNo);
            int v = 0;
            if (MemcachedGet(key, len, value, sizeof(value)))
            {
                v = atoi(value);
                /*if (pf == 11 && v >= 3)
                {
                    LOG_CRI << "id:" << id << " from " << ip.c_str() << " of asss_" << serverNo << " is cracking...";
                    return true;
                }
                else if (pf == 17 && v >= 5)
                {
                    LOG_CRI << "id:" << id << " from " << ip.c_str() << " of asss_" << serverNo << " is cracking...";
                    return true;
                }*/
                if (g_platform_login_number[pf] > 0 && v >= g_platform_login_number[pf])
                {
                    LOG_CRI << "id:" << id << " from " << ip.c_str() << " of asss_" << serverNo << " is cracking...";
                    return true;
                }
            }
            v += 1;
            setCrackValue(ip.c_str(), v, serverNo);
        }
    }

    return false;
}
static void memLockUser(const UINT64 playerId, UINT32 expireTime)
{
    (void)memLockUser;
    initMemcache();
    if (bMemcinited)
    {
        char value[32] = {0};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "asss_locklogin_%" I64_FMT "u", playerId);
        size_t vlen = snprintf(value, sizeof(value), "%d", expireTime);

        MemcachedSet(key, len, value, vlen, 0);
    }
}
static void memUnLockUser(const UINT64 playerId)
{
    (void)memUnLockUser;
    initMemcache();
    if (bMemcinited)
    {
        char value[2] = {'0'};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "asss_locklogin_%" I64_FMT "u", playerId);

        MemcachedSet(key, len, value, 1, 0);
    }
}


static UINT32 getLockUserValue(const UINT64 playerId)
{
    (void)getLockUserValue;
    initMemcache();
    char value[32] = {0};
    char key[MEMCACHED_MAX_KEY] = {0};
    UINT64 pid = playerId & 0xFFFFFFFFFF;
    size_t len = snprintf(key, sizeof(key), "asss_locklogin_%" I64_FMT "u", pid);

    if (bMemcinited)
        MemcachedGet(key, len, value, sizeof(value));

    UINT32 v = 0;
    v = atoi(value);
    return v;
}

static void setPlatformLogin(UINT8 pf, int v)
{
    (void)setPlatformLogin;
    initMemcache();
    if (bMemcinited)
    {
        char value[32] = {0};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "asss_loginlimit_%u", pf);
        size_t vlen = snprintf(value, sizeof(value), "%d", v);

        MemcachedSet(key, len, value, vlen, 0);

        g_platform_login_number[pf] = v;
    }
}
static void initPlatformLogin()
{
    (void)initPlatformLogin;
    initMemcache();

    for (int i = 0; i < 256; ++i)
    {
        char value[32] = {0};
        char key[MEMCACHED_MAX_KEY] = {0};
        size_t len = snprintf(key, sizeof(key), "asss_loginlimit_%u", i);
        if (bMemcinited)
            MemcachedGet(key, len, value, sizeof(value));
        g_platform_login_number[i] = atoi(value);
    }
}
static bool isRPOpenid(const std::string openid)
{
    (void)isRPOpenid;
    initMemcache();
    char value[32] = {0};
    char key[64] = {0};
    size_t len = snprintf(key, sizeof(key), "asss_rp_%s", openid.c_str());;

    if (bMemcinited)
        MemcachedGet(openid.c_str(), len, value, sizeof(value));

    return value[0] == '1';
}
#endif

#endif // _WIN32

