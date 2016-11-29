// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBagCostCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BagCostCFG.h"
#include "tinyxml.h"

CBagCostLoader::~CBagCostLoader()
{
	ClearData();
}

void CBagCostLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBagCostCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBagCostLoader::LoadData(const std::string& strPath)
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
		SBagCostCFG* pData = new SBagCostCFG;
		const char* pstr_Idx = pDataElem->Attribute("Idx");
		if(pstr_Idx != NULL)
			pData->_Idx = (UINT8)atoi(pstr_Idx);
		else
			pData->_Idx = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT8)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_Time = pDataElem->Attribute("Time");
		if(pstr_Time != NULL)
			pData->_Time = (UINT16)atoi(pstr_Time);
		else
			pData->_Time = 0;
		const char* pstr_BagAttr = pDataElem->Attribute("BagAttr");
		if(pstr_BagAttr != NULL)
			pData->_BagAttr = (UINT16)atoi(pstr_BagAttr);
		else
			pData->_BagAttr = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


