// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWorldBossPrizeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "WorldBossPrizeCFG.h"
#include "tinyxml.h"

CWorldBossPrizeLoader::~CWorldBossPrizeLoader()
{
	ClearData();
}

void CWorldBossPrizeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SWorldBossPrizeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CWorldBossPrizeLoader::LoadData(const std::string& strPath)
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
		SWorldBossPrizeCFG* pData = new SWorldBossPrizeCFG;
		const char* pstr_RankTop = pDataElem->Attribute("RankTop");
		if(pstr_RankTop != NULL)
			pData->_RankTop = (UINT16)atoi(pstr_RankTop);
		else
			pData->_RankTop = 0;
		const char* pstr_RankBottom = pDataElem->Attribute("RankBottom");
		if(pstr_RankBottom != NULL)
			pData->_RankBottom = (UINT16)atoi(pstr_RankBottom);
		else
			pData->_RankBottom = 0;
		const char* pstr_PrizeType = pDataElem->Attribute("PrizeType");
		if(pstr_PrizeType != NULL)
			pData->_PrizeType = (UINT16)atoi(pstr_PrizeType);
		else
			pData->_PrizeType = 0;
		const char* pstr_BossID = pDataElem->Attribute("BossID");
		if(pstr_BossID != NULL)
			pData->_BossID = (UINT16)atoi(pstr_BossID);
		else
			pData->_BossID = 0;
		const char* pstr_BossName = pDataElem->Attribute("BossName");
		if(pstr_BossName != NULL)
			pData->_BossName = pstr_BossName;
		else
			pData->_BossName = "";
		const char* pstr_Resource1Type = pDataElem->Attribute("Resource1Type");
		if(pstr_Resource1Type != NULL)
			pData->_Resource1Type = (UINT16)atoi(pstr_Resource1Type);
		else
			pData->_Resource1Type = 0;
		const char* pstr_ResourceValue1 = pDataElem->Attribute("ResourceValue1");
		if(pstr_ResourceValue1 != NULL)
			pData->_ResourceValue1 = (UINT32)atoi(pstr_ResourceValue1);
		else
			pData->_ResourceValue1 = 0;
		const char* pstr_Resource2Type = pDataElem->Attribute("Resource2Type");
		if(pstr_Resource2Type != NULL)
			pData->_Resource2Type = (UINT16)atoi(pstr_Resource2Type);
		else
			pData->_Resource2Type = 0;
		const char* pstr_ResourceValue2 = pDataElem->Attribute("ResourceValue2");
		if(pstr_ResourceValue2 != NULL)
			pData->_ResourceValue2 = (UINT16)atoi(pstr_ResourceValue2);
		else
			pData->_ResourceValue2 = 0;
		const char* pstr_GivenExp = pDataElem->Attribute("GivenExp");
		if(pstr_GivenExp != NULL)
			pData->_GivenExp = (UINT32)atoi(pstr_GivenExp);
		else
			pData->_GivenExp = 0;
		const char* pstr_GivenItem = pDataElem->Attribute("GivenItem");
		if(pstr_GivenItem != NULL)
			pData->_GivenItem = pstr_GivenItem;
		else
			pData->_GivenItem = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


