// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarsCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StarsCFG.h"
#include "tinyxml.h"

CStarsLoader::~CStarsLoader()
{
	ClearData();
}

void CStarsLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStarsCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStarsLoader::LoadData(const std::string& strPath)
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
		SStarsCFG* pData = new SStarsCFG;
		const char* pstr_PrizeId = pDataElem->Attribute("PrizeId");
		if(pstr_PrizeId != NULL)
			pData->_PrizeId = (UINT16)atoi(pstr_PrizeId);
		else
			pData->_PrizeId = 0;
		const char* pstr_RequiredStars = pDataElem->Attribute("RequiredStars");
		if(pstr_RequiredStars != NULL)
			pData->_RequiredStars = (UINT32)atoi(pstr_RequiredStars);
		else
			pData->_RequiredStars = 0;
		const char* pstr_Awards = pDataElem->Attribute("Awards");
		if(pstr_Awards != NULL)
			pData->_Awards = pstr_Awards;
		else
			pData->_Awards = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


