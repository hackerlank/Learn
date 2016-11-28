// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBubbleCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BubbleCFG.h"
#include "tinyxml.h"

CBubbleLoader::~CBubbleLoader()
{
	ClearData();
}

void CBubbleLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBubbleCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBubbleLoader::LoadData(const std::string& strPath)
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
		SBubbleCFG* pData = new SBubbleCFG;
		const char* pstr_wID = pDataElem->Attribute("wID");
		if(pstr_wID != NULL)
			pData->_wID = (UINT16)atoi(pstr_wID);
		else
			pData->_wID = 0;
		const char* pstr_wMessageID = pDataElem->Attribute("wMessageID");
		if(pstr_wMessageID != NULL)
			pData->_wMessageID = (UINT16)atoi(pstr_wMessageID);
		else
			pData->_wMessageID = 0;
		const char* pstr_byPriority = pDataElem->Attribute("byPriority");
		if(pstr_byPriority != NULL)
			pData->_byPriority = (UINT8)atoi(pstr_byPriority);
		else
			pData->_byPriority = 0;
		const char* pstr_byResponeType = pDataElem->Attribute("byResponeType");
		if(pstr_byResponeType != NULL)
			pData->_byResponeType = (UINT8)atoi(pstr_byResponeType);
		else
			pData->_byResponeType = 0;
		const char* pstr_wGroupID = pDataElem->Attribute("wGroupID");
		if(pstr_wGroupID != NULL)
			pData->_wGroupID = (UINT16)atoi(pstr_wGroupID);
		else
			pData->_wGroupID = 0;
		const char* pstr_wGroupType = pDataElem->Attribute("wGroupType");
		if(pstr_wGroupType != NULL)
			pData->_wGroupType = (UINT16)atoi(pstr_wGroupType);
		else
			pData->_wGroupType = 0;
		const char* pstr_byOfflineEnable = pDataElem->Attribute("byOfflineEnable");
		if(pstr_byOfflineEnable != NULL)
			pData->_byOfflineEnable = (UINT8)atoi(pstr_byOfflineEnable);
		else
			pData->_byOfflineEnable = 0;
		const char* pstr_description = pDataElem->Attribute("description");
		if(pstr_description != NULL)
			pData->_description = pstr_description;
		else
			pData->_description = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


