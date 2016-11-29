// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEnergyPriceCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EnergyPriceCFG.h"
#include "tinyxml.h"

CEnergyPriceLoader::~CEnergyPriceLoader()
{
	ClearData();
}

void CEnergyPriceLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEnergyPriceCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEnergyPriceLoader::LoadData(const std::string& strPath)
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
		SEnergyPriceCFG* pData = new SEnergyPriceCFG;
		const char* pstr_BoughtTimes = pDataElem->Attribute("BoughtTimes");
		if(pstr_BoughtTimes != NULL)
			pData->_BoughtTimes = (UINT32)atoi(pstr_BoughtTimes);
		else
			pData->_BoughtTimes = 0;
		const char* pstr_Price = pDataElem->Attribute("Price");
		if(pstr_Price != NULL)
			pData->_Price = (UINT32)atoi(pstr_Price);
		else
			pData->_Price = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


