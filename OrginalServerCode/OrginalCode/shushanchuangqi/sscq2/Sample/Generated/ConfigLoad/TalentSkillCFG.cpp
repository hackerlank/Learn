// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STalentSkillCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TalentSkillCFG.h"
#include "tinyxml.h"

CTalentSkillLoader::~CTalentSkillLoader()
{
	ClearData();
}

void CTalentSkillLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STalentSkillCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTalentSkillLoader::LoadData(const std::string& strPath)
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
		STalentSkillCFG* pData = new STalentSkillCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_SkillID = pDataElem->Attribute("SkillID");
		if(pstr_SkillID != NULL)
			pData->_SkillID = (UINT32)atoi(pstr_SkillID);
		else
			pData->_SkillID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Quality = pDataElem->Attribute("Quality");
		if(pstr_Quality != NULL)
			pData->_Quality = (UINT8)atoi(pstr_Quality);
		else
			pData->_Quality = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_skillCostType = pDataElem->Attribute("skillCostType");
		if(pstr_skillCostType != NULL)
			pData->_skillCostType = (UINT16)atoi(pstr_skillCostType);
		else
			pData->_skillCostType = 0;
		const char* pstr_skillCost = pDataElem->Attribute("skillCost");
		if(pstr_skillCost != NULL)
			pData->_skillCost = (UINT32)atoi(pstr_skillCost);
		else
			pData->_skillCost = 0;
		const char* pstr_needLvl = pDataElem->Attribute("needLvl");
		if(pstr_needLvl != NULL)
			pData->_needLvl = (UINT8)atoi(pstr_needLvl);
		else
			pData->_needLvl = 0;
		const char* pstr_SkillAttr = pDataElem->Attribute("SkillAttr");
		if(pstr_SkillAttr != NULL)
			pData->_SkillAttr = (UINT32)atoi(pstr_SkillAttr);
		else
			pData->_SkillAttr = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


