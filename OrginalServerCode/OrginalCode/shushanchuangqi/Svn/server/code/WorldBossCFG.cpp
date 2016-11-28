// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWorldBossCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "WorldBossCFG.h"
#include "tinyxml.h"

CWorldBossLoader::~CWorldBossLoader()
{
	ClearData();
}

void CWorldBossLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SWorldBossCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CWorldBossLoader::LoadData(const std::string& strPath)
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
		SWorldBossCFG* pData = new SWorldBossCFG;
		const char* pstr_BossId = pDataElem->Attribute("BossId");
		if(pstr_BossId != NULL)
			pData->_BossId = (UINT16)atoi(pstr_BossId);
		else
			pData->_BossId = 0;
		const char* pstr_BossName = pDataElem->Attribute("BossName");
		if(pstr_BossName != NULL)
			pData->_BossName = pstr_BossName;
		else
			pData->_BossName = "";
		const char* pstr_MapId = pDataElem->Attribute("MapId");
		if(pstr_MapId != NULL)
			pData->_MapId = (UINT16)atoi(pstr_MapId);
		else
			pData->_MapId = 0;
		const char* pstr_MapName = pDataElem->Attribute("MapName");
		if(pstr_MapName != NULL)
			pData->_MapName = pstr_MapName;
		else
			pData->_MapName = "";
		const char* pstr_BossPosition = pDataElem->Attribute("BossPosition");
		if(pstr_BossPosition != NULL)
			pData->_BossPosition = pstr_BossPosition;
		else
			pData->_BossPosition = "";
		const char* pstr_BirthPlace = pDataElem->Attribute("BirthPlace");
		if(pstr_BirthPlace != NULL)
			pData->_BirthPlace = pstr_BirthPlace;
		else
			pData->_BirthPlace = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


