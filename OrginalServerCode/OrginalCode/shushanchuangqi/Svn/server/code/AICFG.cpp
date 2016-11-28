// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAICFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AICFG.h"
#include "tinyxml.h"

CAILoader::~CAILoader()
{
	ClearData();
}

void CAILoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAICFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAILoader::LoadData(const std::string& strPath)
{
	ClearData();
	TiXmlDocument doc;
	if(!doc.LoadFile(strPath.c_str(), TIXML_ENCODING_UTF8))
	{
		doc.Clear();
		return false;
	}
	TiXmlElement* pElemRoot = doc.RootElement();
	if(pElemRoot == NULL)
	{
		doc.Clear();
		return false;
	}
	TiXmlElement* pDataElem = pElemRoot->FirstChildElement("Row");
	while(pDataElem != NULL)
	{
		SAICFG* pData = new SAICFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Move = pDataElem->Attribute("Move");
		if(pstr_Move != NULL)
			pData->_Move = (UINT8)atoi(pstr_Move);
		else
			pData->_Move = 0;
		const char* pstr_Attack = pDataElem->Attribute("Attack");
		if(pstr_Attack != NULL)
			pData->_Attack = (UINT8)atoi(pstr_Attack);
		else
			pData->_Attack = 0;
		const char* pstr_StandbySpeed = pDataElem->Attribute("StandbySpeed");
		if(pstr_StandbySpeed != NULL)
			pData->_StandbySpeed = (UINT32)atoi(pstr_StandbySpeed);
		else
			pData->_StandbySpeed = 0;
		const char* pstr_ChaseSpeed = pDataElem->Attribute("ChaseSpeed");
		if(pstr_ChaseSpeed != NULL)
			pData->_ChaseSpeed = (UINT32)atoi(pstr_ChaseSpeed);
		else
			pData->_ChaseSpeed = 0;
		const char* pstr_FightRadius = pDataElem->Attribute("FightRadius");
		if(pstr_FightRadius != NULL)
			pData->_FightRadius = (FLOAT)atof(pstr_FightRadius);
		else
			pData->_FightRadius = 0.0f;
		const char* pstr_AtkDistance = pDataElem->Attribute("AtkDistance");
		if(pstr_AtkDistance != NULL)
			pData->_AtkDistance = (FLOAT)atof(pstr_AtkDistance);
		else
			pData->_AtkDistance = 0.0f;
		const char* pstr_MoveRadius = pDataElem->Attribute("MoveRadius");
		if(pstr_MoveRadius != NULL)
			pData->_MoveRadius = (FLOAT)atof(pstr_MoveRadius);
		else
			pData->_MoveRadius = 0.0f;
		const char* pstr_SightRadius = pDataElem->Attribute("SightRadius");
		if(pstr_SightRadius != NULL)
			pData->_SightRadius = pstr_SightRadius;
		else
			pData->_SightRadius = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


