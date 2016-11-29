#pragma once

#define DEF_UINT32(name, id) e##name = id,
#define DEF_UINT16(name, id) e##name = id,
#define DEF_UINT8(name, id) e##name = id,
#define DEF_DOUBLE(name, id) e##name = id,
#define DEF_FLOAT(name, id) e##name = id,

enum EParamID
{
#include "Parameter.inc"
};

#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT

#define DEF_UINT32(name, id) static UINT32 dw##name;
#define DEF_UINT16(name, id) static UINT16 w##name;
#define DEF_UINT8(name, id) static UINT8 by##name;
#define DEF_DOUBLE(name, id) static double f##name;
#define DEF_FLOAT(name, id) static float f##name;

struct SParamConfig
{
	#include "Parameter.inc"
};

#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT


class CParamMgr
{
public:
	static bool Init();
private:
	static map<EParamID, float> _mapID2Value;
};
