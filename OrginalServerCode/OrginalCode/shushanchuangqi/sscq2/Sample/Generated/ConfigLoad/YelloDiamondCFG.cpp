// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SYelloDiamondCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "YelloDiamondCFG.h"
#include "tinyxml.h"

CYelloDiamondLoader::~CYelloDiamondLoader()
{
	ClearData();
}

void CYelloDiamondLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SYelloDiamondCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CYelloDiamondLoader::LoadData(const std::string& strPath)
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
		SYelloDiamondCFG* pData = new SYelloDiamondCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_BagType = pDataElem->Attribute("BagType");
		if(pstr_BagType != NULL)
			pData->_BagType = (UINT8)atoi(pstr_BagType);
		else
			pData->_BagType = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Pack = pDataElem->Attribute("Pack");
		if(pstr_Pack != NULL)
			pData->_Pack = pstr_Pack;
		else
			pData->_Pack = "";
		const char* pstr_PackEx = pDataElem->Attribute("PackEx");
		if(pstr_PackEx != NULL)
			pData->_PackEx = pstr_PackEx;
		else
			pData->_PackEx = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


