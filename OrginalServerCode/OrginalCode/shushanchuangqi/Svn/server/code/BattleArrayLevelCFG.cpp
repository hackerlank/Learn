// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BattleArrayLevelCFG.h"
#include "tinyxml.h"

CBattleArrayLevelLoader::~CBattleArrayLevelLoader()
{
	ClearData();
}

void CBattleArrayLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBattleArrayLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBattleArrayLevelLoader::LoadData(const std::string& strPath)
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
		SBattleArrayLevelCFG* pData = new SBattleArrayLevelCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_BattleId = pDataElem->Attribute("BattleId");
		if(pstr_BattleId != NULL)
			pData->_BattleId = (UINT16)atoi(pstr_BattleId);
		else
			pData->_BattleId = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_SpotType = pDataElem->Attribute("SpotType");
		if(pstr_SpotType != NULL)
			pData->_SpotType = (UINT8)atoi(pstr_SpotType);
		else
			pData->_SpotType = 0;
		const char* pstr_MonsterGroupID = pDataElem->Attribute("MonsterGroupID");
		if(pstr_MonsterGroupID != NULL)
			pData->_MonsterGroupID = (UINT16)atoi(pstr_MonsterGroupID);
		else
			pData->_MonsterGroupID = 0;
		const char* pstr_PassLootId = pDataElem->Attribute("PassLootId");
		if(pstr_PassLootId != NULL)
			pData->_PassLootId = (UINT16)atoi(pstr_PassLootId);
		else
			pData->_PassLootId = 0;
		const char* pstr_FirstPassLootId = pDataElem->Attribute("FirstPassLootId");
		if(pstr_FirstPassLootId != NULL)
			pData->_FirstPassLootId = (UINT16)atoi(pstr_FirstPassLootId);
		else
			pData->_FirstPassLootId = 0;
		const char* pstr_CostEnergy = pDataElem->Attribute("CostEnergy");
		if(pstr_CostEnergy != NULL)
			pData->_CostEnergy = (UINT8)atoi(pstr_CostEnergy);
		else
			pData->_CostEnergy = 0;
		const char* pstr_PassTag = pDataElem->Attribute("PassTag");
		if(pstr_PassTag != NULL)
			pData->_PassTag = (UINT8)atoi(pstr_PassTag);
		else
			pData->_PassTag = 0;
		const char* pstr_RequiredPackage = pDataElem->Attribute("RequiredPackage");
		if(pstr_RequiredPackage != NULL)
			pData->_RequiredPackage = (UINT8)atoi(pstr_RequiredPackage);
		else
			pData->_RequiredPackage = 0;
		const char* pstr_Access = pDataElem->Attribute("Access");
		if(pstr_Access != NULL)
			pData->_Access = pstr_Access;
		else
			pData->_Access = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


