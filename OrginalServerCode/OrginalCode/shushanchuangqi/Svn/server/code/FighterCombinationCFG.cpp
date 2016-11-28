// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterCombinationCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterCombinationCFG.h"
#include "tinyxml.h"

CFighterCombinationLoader::~CFighterCombinationLoader()
{
	ClearData();
}

void CFighterCombinationLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterCombinationCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterCombinationLoader::LoadData(const std::string& strPath)
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
		SFighterCombinationCFG* pData = new SFighterCombinationCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT8)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_Hero = pDataElem->Attribute("Hero");
		if(pstr_Hero != NULL)
			pData->_Hero = pstr_Hero;
		else
			pData->_Hero = "";
		const char* pstr_Effect = pDataElem->Attribute("Effect");
		if(pstr_Effect != NULL)
			pData->_Effect = (UINT8)atoi(pstr_Effect);
		else
			pData->_Effect = 0;
		const char* pstr_Skill = pDataElem->Attribute("Skill");
		if(pstr_Skill != NULL)
			pData->_Skill = (UINT32)atoi(pstr_Skill);
		else
			pData->_Skill = 0;
		const char* pstr_GetCond = pDataElem->Attribute("GetCond");
		if(pstr_GetCond != NULL)
			pData->_GetCond = (UINT16)atoi(pstr_GetCond);
		else
			pData->_GetCond = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Limit = pDataElem->Attribute("Limit");
		if(pstr_Limit != NULL)
			pData->_Limit = (UINT16)atoi(pstr_Limit);
		else
			pData->_Limit = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


