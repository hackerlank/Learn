
#include "Platform.h"
#include "RTime.h"
#include <stdio.h>

namespace buf
{

struct timezone RTime::_zone;
    
CONSTRUCTOR void TimeInit()
{
    tzset();
}

const char* Time::toString(void) const
{
    return yyyymmddhhmmss();
}

const char* Time::toNormal(void) const
{
    return toString();
}

const char* Time::yyyymmdd(char sep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%04d%c%02d%c%02d",
            year(), sep, month(), sep, day());
    return buf;
}

const char* Time::yyyymmddhhmm(char ysep, char hsep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%04d%c%02d%c%02d %02d%c%02d",
            year(), ysep, month(), ysep, day(), hour(), hsep, min());
    return buf;
}

const char* Time::yyyymmddhhmmss(char ysep, char hsep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%04d%c%02d%c%02d %02d%c%02d%c%02d",
            year(), ysep, month(), ysep, day(),
            hour(), hsep, min(), hsep, sec());
    return buf;
}

const char* Time::yymmdd(char sep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%02d%c%02d%c%02d",
            year()%TYEAR, sep, month(), sep, day());
    return buf;
}

const char* Time::yymmddhhmm(char ysep, char hsep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%02d%c%02d%c%02d %02d%c%02d",
            year()%TYEAR, ysep, month(), ysep, day(), hour(), hsep, min());
    return buf;
}

const char* Time::yymmddhhmmss(char ysep, char hsep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%02d%c%02d%c%02d %02d%c%02d%c%02d",
            year()%TYEAR, ysep, month(), ysep, day(),
            hour(), hsep, min(), hsep, sec());
    return buf;
}

const char* Time::hhmm(char sep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%02d%c%02d", hour(), sep, min());
    return buf;
}

const char* Time::hhmmss(char sep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf), "%02d%c%02d%c%02d", hour(), sep, min(), sep, sec());
    return buf;
}

const char* Time::hhmmssuu(char sep) const
{
    static char buf[32] = {0};
    SNPRINTF(buf, sizeof(buf)-1, "%02u%c%02u%c%02u.%03" I64_FMT "u", hour(), sep, min(), sep, sec(), RTime().usecs());
    return buf;
}

const char* TimeFilmOperatorDefault(const TimeFilm* tf, char* buf, size_t size)
{
    if (!tf)
        return 0;

    timediff_t diff = tf->end().msecs() - tf->begin().msecs();
    timediff_t udiff = tf->end().usecs() - tf->begin().usecs();
    SNPRINTF(buf, size-1, "(%" I64_FMT "u)%" I64_FMT "us.%" I64_FMT "ums(%" I64_FMT "uus)", diff, timediff_t(diff/1000), timediff_t(diff%1000), udiff);
    buf[size-1] = '\0';
    DEBUG_OUT("TIMEFILM: %s%s\n", tf->msg(), buf);
    return buf;
}

TimeFilm::~TimeFilm()
{
    _end.now();
    if (_op)
    {
        char buf[BUF_TFBUF_SIZE] = {0};
        _op(this, buf, sizeof(buf));
    }
}

} // namespace buf

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

