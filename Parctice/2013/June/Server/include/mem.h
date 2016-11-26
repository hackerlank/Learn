#ifndef _MEM_
#define _MEM_
#include <libmemcached/memcached.h>
#define mem_set(key,value)		do {memcached_set(memc, key, strlen(key), (char *)value, (size_t)sizeof(*value), (time_t)0, (uint32_t)0);} while (0)
#define mem_get(key,value_len)	do {memcached_get(memc, key, strlen(key), (char *)value, (size_t)sizeof(*value), (time_t)0, (uint32_t)0);} while (0)
#endif
