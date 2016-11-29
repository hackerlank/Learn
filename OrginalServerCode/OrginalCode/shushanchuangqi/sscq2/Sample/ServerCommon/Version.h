
#ifndef VERSION_H_
#define VERSION_H_

#define VERSION_INIT 0

#include "Linux.h"

class CVersion
{
public:
    CVersion() : _qwVersion(VERSION_INIT) {}
    CVersion(UINT64 qwVersion) : _qwVersion(qwVersion) {}

    void SetVersion(UINT64 qwVersion) { _qwVersion = qwVersion; }
    UINT64 GetVersion() const { return _qwVersion; }

private:
    UINT64 _qwVersion;
};

#endif // VERSION_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

