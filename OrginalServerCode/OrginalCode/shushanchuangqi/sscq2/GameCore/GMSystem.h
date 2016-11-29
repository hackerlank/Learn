
#ifndef GMSYSTEM_H_
#define GMSYSTEM_H_

#include "Platform.h"
#include "Tokenizer.h"

namespace buf
{
// XXX: It's just a template

#define GMT_PLAYER  0x01
#define GMT_NORMAL  0x02
#define GMT_DEBUG   0x04
#define GMT_ADMIN   0x08
#define GMT_SUPER   0x10
#define GMT_ALL     0x1F

struct GMHandler
{
    UINT8 mode;
    const char* name;
    void (*handler)(const char* cmd, const Tokenizer& params, void* p);
    const char* desc;
};

void GMParse(GMHandler handlers[], int nhandler, const char* cmd, int mode = GMT_ALL, void* p = NULL);

} // namespace buf

#endif // GMSYSTEM_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

