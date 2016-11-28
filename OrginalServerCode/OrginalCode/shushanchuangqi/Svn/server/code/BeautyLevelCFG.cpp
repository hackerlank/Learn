// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BeautyLevelCFG.h"
#include "tinyxml.h"

CBeautyLevelLoader::~CBeautyLevelLoader()
{
	ClearData();
}

void CBeautyLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBeautyLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBeautyLevelLoader::LoadData(const std::string& strPath)
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
		SBeautyLevelCFG* pData = new SBeautyLevelCFG;
		const char* pstr_LevelID = pDataElem->Attribute("LevelID");
		if(pstr_LevelID != NULL)
			pData->_LevelID = (UINT16)atoi(pstr_LevelID);
		else
			pData->_LevelID = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT32)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		const char* pstr_SkillAttrID = pDataElem->Attribute("SkillAttrID");
		if(pstr_SkillAttrID != NULL)
			pData->_SkillAttrID = (UINT32)atoi(pstr_SkillAttrID);
		else
			pData->_SkillAttrID = 0;
		const char* pstr_Extral = pDataElem->Attribute("Extral");
		if(pstr_Extral != NULL)
			pData->_Extral = pstr_Extral;
		else
			pData->_Extral = "";
		const char* pstr_ItemType = pDataElem->Attribute("ItemType");
		if(pstr_ItemType != NULL)
			pData->_ItemType = pstr_ItemType;
		else
			pData->_ItemType = "";
		const char* pstr_SkillID = pDataElem->Attribute("SkillID");
		if(pstr_SkillID != NULL)
			pData->_SkillID = (UINT32)atoi(pstr_SkillID);
		else
			pData->_SkillID = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


