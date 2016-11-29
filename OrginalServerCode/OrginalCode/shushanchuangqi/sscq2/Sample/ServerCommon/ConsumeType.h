#pragma once

#define DEF_UINT32(name, id) e##name = id,
#define DEF_UINT16(name, id) e##name = id,
#define DEF_UINT8(name, id) e##name = id,
#define DEF_DOUBLE(name, id) e##name = id,
#define DEF_FLOAT(name, id) e##name = id,

enum EConsumeType
{
#include "ConsumeType.inc"
};

#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT

