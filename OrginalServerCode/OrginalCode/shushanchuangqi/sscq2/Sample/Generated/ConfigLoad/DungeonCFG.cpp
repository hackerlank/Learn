// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDungeonCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DungeonCFG.h"
#include "tinyxml.h"

CDungeonLoader::~CDungeonLoader()
{
	ClearData();
}

void CDungeonLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDungeonCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDungeonLoader::LoadData(const std::string& strPath)
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
		SDungeonCFG* pData = new SDungeonCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_NAME = pDataElem->Attribute("NAME");
		if(pstr_NAME != NULL)
			pData->_NAME = pstr_NAME;
		else
			pData->_NAME = "";
		const char* pstr_Position = pDataElem->Attribute("Position");
		if(pstr_Position != NULL)
			pData->_Position = (UINT16)atoi(pstr_Position);
		else
			pData->_Position = 0;
		const char* pstr_TYPE = pDataElem->Attribute("TYPE");
		if(pstr_TYPE != NULL)
			pData->_TYPE = (UINT8)atoi(pstr_TYPE);
		else
			pData->_TYPE = 0;
		const char* pstr_TYPENAME = pDataElem->Attribute("TYPENAME");
		if(pstr_TYPENAME != NULL)
			pData->_TYPENAME = pstr_TYPENAME;
		else
			pData->_TYPENAME = "";
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_PreDgns = pDataElem->Attribute("PreDgns");
		if(pstr_PreDgns != NULL)
			pData->_PreDgns = pstr_PreDgns;
		else
			pData->_PreDgns = "";
		const char* pstr_SpendEnergy = pDataElem->Attribute("SpendEnergy");
		if(pstr_SpendEnergy != NULL)
			pData->_SpendEnergy = (UINT32)atoi(pstr_SpendEnergy);
		else
			pData->_SpendEnergy = 0;
		const char* pstr_PassRequire = pDataElem->Attribute("PassRequire");
		if(pstr_PassRequire != NULL)
			pData->_PassRequire = pstr_PassRequire;
		else
			pData->_PassRequire = "";
		const char* pstr_Maps = pDataElem->Attribute("Maps");
		if(pstr_Maps != NULL)
			pData->_Maps = pstr_Maps;
		else
			pData->_Maps = "";
		const char* pstr_Logic = pDataElem->Attribute("Logic");
		if(pstr_Logic != NULL)
			pData->_Logic = pstr_Logic;
		else
			pData->_Logic = "";
		const char* pstr_Evaluate = pDataElem->Attribute("Evaluate");
		if(pstr_Evaluate != NULL)
			pData->_Evaluate = pstr_Evaluate;
		else
			pData->_Evaluate = "";
		const char* pstr_OUTPoint = pDataElem->Attribute("OUTPoint");
		if(pstr_OUTPoint != NULL)
			pData->_OUTPoint = pstr_OUTPoint;
		else
			pData->_OUTPoint = "";
		const char* pstr_PackSize = pDataElem->Attribute("PackSize");
		if(pstr_PackSize != NULL)
			pData->_PackSize = (UINT8)atoi(pstr_PackSize);
		else
			pData->_PackSize = 0;
		const char* pstr_AwardLoots = pDataElem->Attribute("AwardLoots");
		if(pstr_AwardLoots != NULL)
			pData->_AwardLoots = pstr_AwardLoots;
		else
			pData->_AwardLoots = "";
		const char* pstr_dwExp = pDataElem->Attribute("dwExp");
		if(pstr_dwExp != NULL)
			pData->_dwExp = (UINT32)atoi(pstr_dwExp);
		else
			pData->_dwExp = 0;
		const char* pstr_dwPExp = pDataElem->Attribute("dwPExp");
		if(pstr_dwPExp != NULL)
			pData->_dwPExp = (UINT32)atoi(pstr_dwPExp);
		else
			pData->_dwPExp = 0;
		const char* pstr_dwLoots = pDataElem->Attribute("dwLoots");
		if(pstr_dwLoots != NULL)
			pData->_dwLoots = (UINT32)atoi(pstr_dwLoots);
		else
			pData->_dwLoots = 0;
		const char* pstr_dwLoots2 = pDataElem->Attribute("dwLoots2");
		if(pstr_dwLoots2 != NULL)
			pData->_dwLoots2 = (UINT32)atoi(pstr_dwLoots2);
		else
			pData->_dwLoots2 = 0;
		const char* pstr_dwLoots3 = pDataElem->Attribute("dwLoots3");
		if(pstr_dwLoots3 != NULL)
			pData->_dwLoots3 = (UINT32)atoi(pstr_dwLoots3);
		else
			pData->_dwLoots3 = 0;
		const char* pstr_dwSweepingCoin = pDataElem->Attribute("dwSweepingCoin");
		if(pstr_dwSweepingCoin != NULL)
			pData->_dwSweepingCoin = (UINT32)atoi(pstr_dwSweepingCoin);
		else
			pData->_dwSweepingCoin = 0;
		const char* pstr_dwSweepingTime = pDataElem->Attribute("dwSweepingTime");
		if(pstr_dwSweepingTime != NULL)
			pData->_dwSweepingTime = (UINT32)atoi(pstr_dwSweepingTime);
		else
			pData->_dwSweepingTime = 0;
		const char* pstr_ECTYPE_PAGE = pDataElem->Attribute("ECTYPE_PAGE");
		if(pstr_ECTYPE_PAGE != NULL)
			pData->_ECTYPE_PAGE = (UINT32)atoi(pstr_ECTYPE_PAGE);
		else
			pData->_ECTYPE_PAGE = 0;
		const char* pstr_PAGE_POS = pDataElem->Attribute("PAGE_POS");
		if(pstr_PAGE_POS != NULL)
			pData->_PAGE_POS = (UINT32)atoi(pstr_PAGE_POS);
		else
			pData->_PAGE_POS = 0;
		const char* pstr_ItemDrop = pDataElem->Attribute("ItemDrop");
		if(pstr_ItemDrop != NULL)
			pData->_ItemDrop = pstr_ItemDrop;
		else
			pData->_ItemDrop = "";
		const char* pstr_Min = pDataElem->Attribute("Min");
		if(pstr_Min != NULL)
			pData->_Min = (UINT32)atoi(pstr_Min);
		else
			pData->_Min = 0;
		const char* pstr_Max = pDataElem->Attribute("Max");
		if(pstr_Max != NULL)
			pData->_Max = (UINT32)atoi(pstr_Max);
		else
			pData->_Max = 0;
		const char* pstr_IsSweeping = pDataElem->Attribute("IsSweeping");
		if(pstr_IsSweeping != NULL)
			pData->_IsSweeping = (UINT8)atoi(pstr_IsSweeping);
		else
			pData->_IsSweeping = 0;
		const char* pstr_Hide = pDataElem->Attribute("Hide");
		if(pstr_Hide != NULL)
			pData->_Hide = (UINT8)atoi(pstr_Hide);
		else
			pData->_Hide = 0;
		const char* pstr_HideBtn = pDataElem->Attribute("HideBtn");
		if(pstr_HideBtn != NULL)
			pData->_HideBtn = (UINT8)atoi(pstr_HideBtn);
		else
			pData->_HideBtn = 0;
		const char* pstr_Type2 = pDataElem->Attribute("Type2");
		if(pstr_Type2 != NULL)
			pData->_Type2 = (UINT8)atoi(pstr_Type2);
		else
			pData->_Type2 = 0;
		const char* pstr_AppearCondId = pDataElem->Attribute("AppearCondId");
		if(pstr_AppearCondId != NULL)
			pData->_AppearCondId = (UINT32)atoi(pstr_AppearCondId);
		else
			pData->_AppearCondId = 0;
		const char* pstr_SpeiceAward = pDataElem->Attribute("SpeiceAward");
		if(pstr_SpeiceAward != NULL)
			pData->_SpeiceAward = (UINT32)atoi(pstr_SpeiceAward);
		else
			pData->_SpeiceAward = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


