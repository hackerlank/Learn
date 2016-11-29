// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterTalentCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterTalentCFG.h"
#include "tinyxml.h"

CFighterTalentLoader::~CFighterTalentLoader()
{
	ClearData();
}

void CFighterTalentLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterTalentCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterTalentLoader::LoadData(const std::string& strPath)
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
		SFighterTalentCFG* pData = new SFighterTalentCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TalentType = pDataElem->Attribute("TalentType");
		if(pstr_TalentType != NULL)
			pData->_TalentType = (UINT8)atoi(pstr_TalentType);
		else
			pData->_TalentType = 0;
		const char* pstr_GroupID = pDataElem->Attribute("GroupID");
		if(pstr_GroupID != NULL)
			pData->_GroupID = (UINT32)atoi(pstr_GroupID);
		else
			pData->_GroupID = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_CondID = pDataElem->Attribute("CondID");
		if(pstr_CondID != NULL)
			pData->_CondID = (UINT32)atoi(pstr_CondID);
		else
			pData->_CondID = 0;
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
		const char* pstr_Description = pDataElem->Attribute("Description");
		if(pstr_Description != NULL)
			pData->_Description = pstr_Description;
		else
			pData->_Description = "";
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = pstr_Icon;
		else
			pData->_Icon = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


