// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHorseUpgradeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "HorseUpgradeCFG.h"
#include "tinyxml.h"

CHorseUpgradeLoader::~CHorseUpgradeLoader()
{
	ClearData();
}

void CHorseUpgradeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SHorseUpgradeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CHorseUpgradeLoader::LoadData(const std::string& strPath)
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
		SHorseUpgradeCFG* pData = new SHorseUpgradeCFG;
		const char* pstr_HorseLevel = pDataElem->Attribute("HorseLevel");
		if(pstr_HorseLevel != NULL)
			pData->_HorseLevel = (UINT32)atoi(pstr_HorseLevel);
		else
			pData->_HorseLevel = 0;
		const char* pstr_SkillLevel = pDataElem->Attribute("SkillLevel");
		if(pstr_SkillLevel != NULL)
			pData->_SkillLevel = (UINT32)atoi(pstr_SkillLevel);
		else
			pData->_SkillLevel = 0;
		const char* pstr_Speed = pDataElem->Attribute("Speed");
		if(pstr_Speed != NULL)
			pData->_Speed = (UINT32)atoi(pstr_Speed);
		else
			pData->_Speed = 0;
		const char* pstr_NeedItemID = pDataElem->Attribute("NeedItemID");
		if(pstr_NeedItemID != NULL)
			pData->_NeedItemID = (UINT32)atoi(pstr_NeedItemID);
		else
			pData->_NeedItemID = 0;
		const char* pstr_NeedItemCnt = pDataElem->Attribute("NeedItemCnt");
		if(pstr_NeedItemCnt != NULL)
			pData->_NeedItemCnt = (UINT32)atoi(pstr_NeedItemCnt);
		else
			pData->_NeedItemCnt = 0;
		const char* pstr_ExpLow = pDataElem->Attribute("ExpLow");
		if(pstr_ExpLow != NULL)
			pData->_ExpLow = (UINT32)atoi(pstr_ExpLow);
		else
			pData->_ExpLow = 0;
		const char* pstr_ExpHigh = pDataElem->Attribute("ExpHigh");
		if(pstr_ExpHigh != NULL)
			pData->_ExpHigh = (UINT32)atoi(pstr_ExpHigh);
		else
			pData->_ExpHigh = 0;
		const char* pstr_NeedExp = pDataElem->Attribute("NeedExp");
		if(pstr_NeedExp != NULL)
			pData->_NeedExp = (UINT32)atoi(pstr_NeedExp);
		else
			pData->_NeedExp = 0;
		const char* pstr_SkillAttrID = pDataElem->Attribute("SkillAttrID");
		if(pstr_SkillAttrID != NULL)
			pData->_SkillAttrID = (UINT32)atoi(pstr_SkillAttrID);
		else
			pData->_SkillAttrID = 0;
		const char* pstr_ModelID = pDataElem->Attribute("ModelID");
		if(pstr_ModelID != NULL)
			pData->_ModelID = (UINT32)atoi(pstr_ModelID);
		else
			pData->_ModelID = 0;
		const char* pstr_ModelName = pDataElem->Attribute("ModelName");
		if(pstr_ModelName != NULL)
			pData->_ModelName = pstr_ModelName;
		else
			pData->_ModelName = "";
		const char* pstr_EffectName = pDataElem->Attribute("EffectName");
		if(pstr_EffectName != NULL)
			pData->_EffectName = pstr_EffectName;
		else
			pData->_EffectName = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


