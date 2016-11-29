
#include "Regular.h"
#include "Platform.h"

Regular::Regular(const char* pattern) : _inited(false)
{
    if (pattern)
        reset(pattern);
}

Regular::~Regular()
{
    reset(NULL);
}

bool Regular::reset(const char* pattern)
{
    if (_inited)
    {
        regfree(&_regex);
        _inited = false;
    }

    if (!pattern)
        return true;

    if (regcomp(&_regex, pattern, REG_EXTENDED) == 0)
        _inited = true;

    return _inited;
}

bool Regular::matchFirst(const char* str)
{
    if (!str)
        return false;

    int err = regexec(&_regex, str, 0, NULL, 0);
    if (err == REG_NOMATCH)
        return false;

    return err == 0;
}

bool Regular::match(const char* str, int nmatch, std::vector<std::string>& ret)
{
    if (!str || !nmatch)
        return false;
    regmatch_t* pmatch = new regmatch_t[nmatch];
    if (!pmatch)
        return false;
    int err = regexec(&_regex, str, nmatch, pmatch, 0);
    if (err == REG_NOMATCH)
    {
        delete pmatch;
        return false;
    }

    for (UINT32 i = 0; i <= _regex.re_nsub; ++i)
    {
        size_t len = pmatch[i].rm_eo - pmatch[i].rm_so;
        ret.push_back(std::string(str+pmatch[i].rm_so, len));
    }

    delete pmatch;
    return true;
}

