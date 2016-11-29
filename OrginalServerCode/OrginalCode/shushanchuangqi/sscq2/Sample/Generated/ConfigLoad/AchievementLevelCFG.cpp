// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAchievementLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AchievementLevelCFG.h"
#include "tinyxml.h"

CAchievementLevelLoader::~CAchievementLevelLoader()
{
	ClearData();
}

void CAchievementLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAchievementLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAchievementLevelLoader::LoadData(const std::string& strPath)
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
		SAchievementLevelCFG* pData = new SAchievementLevelCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Point = pDataElem->Attribute("Point");
		if(pstr_Point != NULL)
			pData->_Point = (UINT16)atoi(pstr_Point);
		else
			pData->_Point = 0;
		const char* pstr_AwardType = pDataElem->Attribute("AwardType");
		if(pstr_AwardType != NULL)
			pData->_AwardType = (UINT16)atoi(pstr_AwardType);
		else
			pData->_AwardType = 0;
		const char* pstr_AwardPara = pDataElem->Attribute("AwardPara");
		if(pstr_AwardPara != NULL)
			pData->_AwardPara = (UINT16)atoi(pstr_AwardPara);
		else
			pData->_AwardPara = 0;
		const char* pstr_PropAward = pDataElem->Attribute("PropAward");
		if(pstr_PropAward != NULL)
			pData->_PropAward = (UINT16)atoi(pstr_PropAward);
		else
			pData->_PropAward = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


