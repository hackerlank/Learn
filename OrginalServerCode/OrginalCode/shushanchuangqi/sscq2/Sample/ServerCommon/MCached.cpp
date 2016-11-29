
#include "MCached.h"
#include "Tokenizer.h"

#ifndef _WIN32
MCached::MCached() : _inited(false)
{
}

MCached::~MCached()
{
    if (_inited)
        memcached_free(&_memsvr);
    _inited = false;
}

bool MCached::init(const char* hosts)
{
    if (_inited)
        return true;
    if (memcached_create(&_memsvr))
    {
        _inited = true;
        return pushHost(hosts);
    }
    return false;
}

bool MCached::init(const std::string& hosts)
{
    return init(hosts.c_str());
}

bool MCached::pushHost(const std::string& hosts)
{
    return pushHost(hosts.c_str());
}

bool MCached::pushHost(const char* hosts)
{
    if (!hosts || !strlen(hosts))
        return false;

    if (!_inited)
        return init(hosts);

    memcached_server_list_st servers = memcached_servers_parse(hosts);
    if (servers)
    {
        memcached_return rc = memcached_server_push(&_memsvr, servers);
        memcached_server_list_free(servers);
        if (rc == MEMCACHED_SUCCESS)
        {
            addHosts(hosts);
            return true;
        }
    }
    return false;
}

bool MCached::addHosts(const char* hosts)
{
    if (!hosts || !strlen(hosts))
        return false;
    Tokenizer tk(hosts, ",");
    if (!tk.size())
        return false;

    bool ret = false;
    size_t sz = tk.size();
    for (size_t i = 0; i < sz; ++i)
    {
        bool found = false;
        for (unsigned int n = 0; n < _hosts.size(); ++n)
        {
            if (!tk[i].empty())
                continue;
            if (tk[i] == _hosts[n])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            _hosts.push_back(tk[i]);
            ret = true;
        }
    }
    return ret;
}

const char* MCached::get(const char* key, char* value, size_t size)
{
    if (!key || !value || !size)
        return 0;
    return get(key, strlen(key), value, size);
}

const char* MCached::get(const char* key, size_t key_size, char* value, size_t size)
{
    if (!key || !key_size || !value || !size || !_hosts.size())
        return 0;

    size_t tlen = 0;
    unsigned int flags = 0;

    int retry = 3;
    memcached_return rc;

    while (retry)
    {
        --retry;
        char* rval = memcached_get(&_memsvr, key, key_size, &tlen, &flags, &rc);
        if (rc == MEMCACHED_SUCCESS && rval && tlen)
        {
            tlen = tlen > size ? size : tlen;
            memcpy(value, rval, tlen);
            free(rval);
            break;
        }
        else
        {
            //usleep(500);
        }
    }
    return value;
}

bool MCached::set(const char* key, const char* value, int timeout)
{
    if (!key || !value)
        return 0;
    return set(key, strlen(key), value, strlen(value), timeout);
}

bool MCached::set(const char* key, size_t key_size, const char* value, size_t size, int timeout)
{
    if (!key || !key_size || !value || !size || !_hosts.size())
        return false;

    memcached_return_t rc = memcached_set(&_memsvr, key, key_size, value, size, timeout, 0);

    int retry = 2;
    while (rc != MEMCACHED_SUCCESS && retry)
    {
        rc = memcached_set(&_memsvr, key, key_size, value, size, timeout, 0);
        --retry;
    }

    return rc == MEMCACHED_SUCCESS;
}

bool MCached::del(const char* key)
{
    if (!key || !strlen(key))
        return false;
    return del(key, strlen(key));
}

bool MCached::del(const char* key, size_t key_size)
{
    if (!key || !key_size)
        return false;
    return MEMCACHED_SUCCESS == memcached_delete(&_memsvr, key, key_size, 0);
}

#endif

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

