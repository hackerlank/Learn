
#ifndef REGULAR_H_
#define REGULAR_H_

#include <regex.h>
#include <string>
#include <vector>

class Regular
{
public:
    Regular(const char* pattern = NULL);
    ~Regular();

    bool reset(const char* pattern);
    bool matchFirst(const char* str);
    bool match(const char* str, int nmatch, std::vector<std::string>& ret);

private:
    bool _inited;
    regex_t _regex;
};

#endif

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

