#include "stdafx.h"
#include "Parameter.h"
#include "ParameterCFG.h"

#define DEF_UINT32(name, id) UINT32 SParamConfig::dw##name = 0;
#define DEF_UINT16(name, id) UINT16 SParamConfig::w##name = 0;
#define DEF_UINT8(name, id) UINT8 SParamConfig::by##name = 0;
#define DEF_DOUBLE(name, id) double SParamConfig::f##name = 0.0f;
#define DEF_FLOAT(name, id) float SParamConfig::f##name = 0.0f;

#include "Parameter.inc"

#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT

map<EParamID, float> CParamMgr::_mapID2Value;
bool CParamMgr::Init()
{
	string strPath = Config._strConfigDir + "Conf/Table/Parameter.xml";
	CParameterLoader oParameterLoader;
	if(!oParameterLoader.LoadData(strPath))
	{
		LOG_CRI << "oParameterLoader.LoadData fails! Path: " << strPath;
		return false;
	}
	for(size_t i = 0; i < oParameterLoader._vecData.size(); ++i)
	{
#define DEF_UINT32(name, id) case id: SParamConfig::dw##name = (UINT32)pParameterCFG->_Fvalue;break;
#define DEF_UINT16(name, id) case id: SParamConfig::w##name = (UINT16)pParameterCFG->_Fvalue;break;
#define DEF_UINT8(name, id) case id: SParamConfig::by##name = (UINT8)pParameterCFG->_Fvalue;break;
#define DEF_DOUBLE(name, id) case id: SParamConfig::f##name = (double)pParameterCFG->_Fvalue;break;
#define DEF_FLOAT(name, id) case id: SParamConfig::f##name = (float)pParameterCFG->_Fvalue;break;
		SParameterCFG* pParameterCFG = oParameterLoader._vecData[i];
		switch(pParameterCFG->_ID)
		{
#include "Parameter.inc"
		}
#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT
	}

	return true;
}

