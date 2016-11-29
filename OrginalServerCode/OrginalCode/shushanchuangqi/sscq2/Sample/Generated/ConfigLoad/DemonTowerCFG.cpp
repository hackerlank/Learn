// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDemonTowerCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DemonTowerCFG.h"
#include "tinyxml.h"

CDemonTowerLoader::~CDemonTowerLoader()
{
	ClearData();
}

void CDemonTowerLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDemonTowerCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDemonTowerLoader::LoadData(const std::string& strPath)
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
		SDemonTowerCFG* pData = new SDemonTowerCFG;
		const char* pstr_FloorID = pDataElem->Attribute("FloorID");
		if(pstr_FloorID != NULL)
			pData->_FloorID = (UINT32)atoi(pstr_FloorID);
		else
			pData->_FloorID = 0;
		const char* pstr_MapID = pDataElem->Attribute("MapID");
		if(pstr_MapID != NULL)
			pData->_MapID = (UINT32)atoi(pstr_MapID);
		else
			pData->_MapID = 0;
		const char* pstr_DayPrizeType = pDataElem->Attribute("DayPrizeType");
		if(pstr_DayPrizeType != NULL)
			pData->_DayPrizeType = (UINT32)atoi(pstr_DayPrizeType);
		else
			pData->_DayPrizeType = 0;
		const char* pstr_DayPrize = pDataElem->Attribute("DayPrize");
		if(pstr_DayPrize != NULL)
			pData->_DayPrize = (UINT32)atoi(pstr_DayPrize);
		else
			pData->_DayPrize = 0;
		const char* pstr_PassPrizeType = pDataElem->Attribute("PassPrizeType");
		if(pstr_PassPrizeType != NULL)
			pData->_PassPrizeType = (UINT32)atoi(pstr_PassPrizeType);
		else
			pData->_PassPrizeType = 0;
		const char* pstr_PassPrize = pDataElem->Attribute("PassPrize");
		if(pstr_PassPrize != NULL)
			pData->_PassPrize = (UINT32)atoi(pstr_PassPrize);
		else
			pData->_PassPrize = 0;
		const char* pstr_PrizeBox = pDataElem->Attribute("PrizeBox");
		if(pstr_PrizeBox != NULL)
			pData->_PrizeBox = (UINT32)atoi(pstr_PrizeBox);
		else
			pData->_PrizeBox = 0;
		const char* pstr_ExtraPrize = pDataElem->Attribute("ExtraPrize");
		if(pstr_ExtraPrize != NULL)
			pData->_ExtraPrize = pstr_ExtraPrize;
		else
			pData->_ExtraPrize = "";
		const char* pstr_PositoinCount = pDataElem->Attribute("PositoinCount");
		if(pstr_PositoinCount != NULL)
			pData->_PositoinCount = (UINT32)atoi(pstr_PositoinCount);
		else
			pData->_PositoinCount = 0;
		const char* pstr_IsCanFighter = pDataElem->Attribute("IsCanFighter");
		if(pstr_IsCanFighter != NULL)
			pData->_IsCanFighter = (UINT8)atoi(pstr_IsCanFighter);
		else
			pData->_IsCanFighter = 0;
		const char* pstr_MonsterGroupID = pDataElem->Attribute("MonsterGroupID");
		if(pstr_MonsterGroupID != NULL)
			pData->_MonsterGroupID = (UINT32)atoi(pstr_MonsterGroupID);
		else
			pData->_MonsterGroupID = 0;
		const char* pstr_Hp = pDataElem->Attribute("Hp");
		if(pstr_Hp != NULL)
			pData->_Hp = (UINT32)atoi(pstr_Hp);
		else
			pData->_Hp = 0;
		const char* pstr_Atk = pDataElem->Attribute("Atk");
		if(pstr_Atk != NULL)
			pData->_Atk = (UINT32)atoi(pstr_Atk);
		else
			pData->_Atk = 0;
		const char* pstr_Craze = pDataElem->Attribute("Craze");
		if(pstr_Craze != NULL)
			pData->_Craze = (UINT32)atoi(pstr_Craze);
		else
			pData->_Craze = 0;
		const char* pstr_Pierce = pDataElem->Attribute("Pierce");
		if(pstr_Pierce != NULL)
			pData->_Pierce = (UINT32)atoi(pstr_Pierce);
		else
			pData->_Pierce = 0;
		const char* pstr_Agilty = pDataElem->Attribute("Agilty");
		if(pstr_Agilty != NULL)
			pData->_Agilty = (UINT32)atoi(pstr_Agilty);
		else
			pData->_Agilty = 0;
		const char* pstr_Def = pDataElem->Attribute("Def");
		if(pstr_Def != NULL)
			pData->_Def = (UINT32)atoi(pstr_Def);
		else
			pData->_Def = 0;
		const char* pstr_Destory = pDataElem->Attribute("Destory");
		if(pstr_Destory != NULL)
			pData->_Destory = (UINT32)atoi(pstr_Destory);
		else
			pData->_Destory = 0;
		const char* pstr_Tenacity = pDataElem->Attribute("Tenacity");
		if(pstr_Tenacity != NULL)
			pData->_Tenacity = (UINT32)atoi(pstr_Tenacity);
		else
			pData->_Tenacity = 0;
		const char* pstr_Guide = pDataElem->Attribute("Guide");
		if(pstr_Guide != NULL)
			pData->_Guide = (UINT16)atoi(pstr_Guide);
		else
			pData->_Guide = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


