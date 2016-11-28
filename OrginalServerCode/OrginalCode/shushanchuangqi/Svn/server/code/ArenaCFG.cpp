// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SArenaCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ArenaCFG.h"
#include "tinyxml.h"

CArenaLoader::~CArenaLoader()
{
	ClearData();
}

void CArenaLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SArenaCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CArenaLoader::LoadData(const std::string& strPath)
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
		SArenaCFG* pData = new SArenaCFG;
		const char* pstr_id = pDataElem->Attribute("id");
		if(pstr_id != NULL)
			pData->_id = (UINT8)atoi(pstr_id);
		else
			pData->_id = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_byKeepLevelDays = pDataElem->Attribute("byKeepLevelDays");
		if(pstr_byKeepLevelDays != NULL)
			pData->_byKeepLevelDays = (UINT8)atoi(pstr_byKeepLevelDays);
		else
			pData->_byKeepLevelDays = 0;
		const char* pstr_dwKeepLevelLoot = pDataElem->Attribute("dwKeepLevelLoot");
		if(pstr_dwKeepLevelLoot != NULL)
			pData->_dwKeepLevelLoot = (UINT32)atoi(pstr_dwKeepLevelLoot);
		else
			pData->_dwKeepLevelLoot = 0;
		const char* pstr_dwLevelLoot = pDataElem->Attribute("dwLevelLoot");
		if(pstr_dwLevelLoot != NULL)
			pData->_dwLevelLoot = (UINT32)atoi(pstr_dwLevelLoot);
		else
			pData->_dwLevelLoot = 0;
		const char* pstr_byAwardNum = pDataElem->Attribute("byAwardNum");
		if(pstr_byAwardNum != NULL)
			pData->_byAwardNum = (UINT8)atoi(pstr_byAwardNum);
		else
			pData->_byAwardNum = 0;
		const char* pstr_strAwardLoot = pDataElem->Attribute("strAwardLoot");
		if(pstr_strAwardLoot != NULL)
			pData->_strAwardLoot = pstr_strAwardLoot;
		else
			pData->_strAwardLoot = "";
		const char* pstr_wVictorFame = pDataElem->Attribute("wVictorFame");
		if(pstr_wVictorFame != NULL)
			pData->_wVictorFame = (UINT16)atoi(pstr_wVictorFame);
		else
			pData->_wVictorFame = 0;
		const char* pstr_wFailFame = pDataElem->Attribute("wFailFame");
		if(pstr_wFailFame != NULL)
			pData->_wFailFame = (UINT16)atoi(pstr_wFailFame);
		else
			pData->_wFailFame = 0;
		const char* pstr_wVictorScore = pDataElem->Attribute("wVictorScore");
		if(pstr_wVictorScore != NULL)
			pData->_wVictorScore = (UINT16)atoi(pstr_wVictorScore);
		else
			pData->_wVictorScore = 0;
		const char* pstr_wFailScore = pDataElem->Attribute("wFailScore");
		if(pstr_wFailScore != NULL)
			pData->_wFailScore = (UINT16)atoi(pstr_wFailScore);
		else
			pData->_wFailScore = 0;
		const char* pstr_strExtraScore = pDataElem->Attribute("strExtraScore");
		if(pstr_strExtraScore != NULL)
			pData->_strExtraScore = pstr_strExtraScore;
		else
			pData->_strExtraScore = "";
		const char* pstr_byLevelUpRate = pDataElem->Attribute("byLevelUpRate");
		if(pstr_byLevelUpRate != NULL)
			pData->_byLevelUpRate = (UINT8)atoi(pstr_byLevelUpRate);
		else
			pData->_byLevelUpRate = 0;
		const char* pstr_byLevelDwonRate = pDataElem->Attribute("byLevelDwonRate");
		if(pstr_byLevelDwonRate != NULL)
			pData->_byLevelDwonRate = (UINT8)atoi(pstr_byLevelDwonRate);
		else
			pData->_byLevelDwonRate = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


