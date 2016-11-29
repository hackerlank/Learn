// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayPriceCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BattleArrayPriceCFG.h"
#include "tinyxml.h"

CBattleArrayPriceLoader::~CBattleArrayPriceLoader()
{
	ClearData();
}

void CBattleArrayPriceLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBattleArrayPriceCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBattleArrayPriceLoader::LoadData(const std::string& strPath)
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
		SBattleArrayPriceCFG* pData = new SBattleArrayPriceCFG;
		const char* pstr_BoughtTimes = pDataElem->Attribute("BoughtTimes");
		if(pstr_BoughtTimes != NULL)
			pData->_BoughtTimes = (UINT16)atoi(pstr_BoughtTimes);
		else
			pData->_BoughtTimes = 0;
		const char* pstr_BattleArrayPrice = pDataElem->Attribute("BattleArrayPrice");
		if(pstr_BattleArrayPrice != NULL)
			pData->_BattleArrayPrice = (UINT32)atoi(pstr_BattleArrayPrice);
		else
			pData->_BattleArrayPrice = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


