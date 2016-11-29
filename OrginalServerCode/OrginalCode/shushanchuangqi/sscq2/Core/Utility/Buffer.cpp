
#include "Buffer.h"

namespace buf
{

#define OPERATOR_OUT(dst, src)                      \
do                                                  \
{                                                   \
    /* XXX: size UINT16 必须与operator<<保持一致*/   \
    UINT16 rsz = src.rsize();                        \
    if (!rsz || rsz < sizeof(UINT16))                \
        return src;                                 \
    UINT16 sz = 0;                                   \
    src >> sz;                                      \
    rsz -= sizeof(UINT16);                           \
    sz = rsz>=sz?sz:rsz;                            \
    if (sz)                                         \
    {                                               \
        dst.append(src.rbuf(), sz);                 \
        src.rflip_silence(sz);                      \
    }                                               \
    return src;                                     \
} while(0)

MemReader& operator>>(MemReader& mr, Buffer& buf)
{
    OPERATOR_OUT(buf, mr);
}

MemWriter& operator>>(MemWriter& mw, Buffer& buf)
{
    OPERATOR_OUT(buf, mw);
}

Buffer& operator>>(Buffer& sbuf, Buffer& buf)
{
    OPERATOR_OUT(buf, sbuf);
}

#define OPERATOR_IN(dst, src)               \
do                                          \
{                                           \
    UINT16 sz = src.rsize();                 \
    sz = sz>dst.wsize()?dst.wsize():sz;     \
    dst << sz;                              \
    if (sz)                                 \
        dst.append(src.rbuf(), sz);         \
    return dst;                             \
} while(0)

Buffer& operator<<(Buffer& sbuf, const MemReader& mr)
{
    OPERATOR_IN(sbuf, mr);
}

Buffer& operator<<(Buffer& sbuf, const Buffer& buf)
{
    OPERATOR_IN(sbuf, buf);
}

} // namespace buf

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

