// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevDiscountCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SevDiscountCFG.h"
#include "tinyxml.h"

CSevDiscountLoader::~CSevDiscountLoader()
{
	ClearData();
}

void CSevDiscountLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSevDiscountCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSevDiscountLoader::LoadData(const std::string& strPath)
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
		SSevDiscountCFG* pData = new SSevDiscountCFG;
		const char* pstr_Day = pDataElem->Attribute("Day");
		if(pstr_Day != NULL)
			pData->_Day = (UINT16)atoi(pstr_Day);
		else
			pData->_Day = 0;
		const char* pstr_Price = pDataElem->Attribute("Price");
		if(pstr_Price != NULL)
			pData->_Price = (UINT16)atoi(pstr_Price);
		else
			pData->_Price = 0;
		const char* pstr_Discount = pDataElem->Attribute("Discount");
		if(pstr_Discount != NULL)
			pData->_Discount = (UINT16)atoi(pstr_Discount);
		else
			pData->_Discount = 0;
		const char* pstr_Agio = pDataElem->Attribute("Agio");
		if(pstr_Agio != NULL)
			pData->_Agio = (UINT16)atoi(pstr_Agio);
		else
			pData->_Agio = 0;
		const char* pstr_Reward = pDataElem->Attribute("Reward");
		if(pstr_Reward != NULL)
			pData->_Reward = pstr_Reward;
		else
			pData->_Reward = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


