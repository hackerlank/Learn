#include <libmemcached/memcached.h>
#include <curl/curl.h>

bool bMemcinited = false;
memcached_st memc;
int memc_version = 0;
int g_platform_login_number[256] = {0};
CURL* curl = NULL;


