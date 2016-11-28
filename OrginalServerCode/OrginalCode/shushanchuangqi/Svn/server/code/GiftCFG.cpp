// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGiftCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GiftCFG.h"
#include "tinyxml.h"

CGiftLoader::~CGiftLoader()
{
	ClearData();
}

void CGiftLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGiftCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGiftLoader::LoadData(const std::string& strPath)
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
		SGiftCFG* pData = new SGiftCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Type2 = pDataElem->Attribute("Type2");
		if(pstr_Type2 != NULL)
			pData->_Type2 = (UINT8)atoi(pstr_Type2);
		else
			pData->_Type2 = 0;
		const char* pstr_Type3 = pDataElem->Attribute("Type3");
		if(pstr_Type3 != NULL)
			pData->_Type3 = pstr_Type3;
		else
			pData->_Type3 = "";
		const char* pstr_GiftItem = pDataElem->Attribute("GiftItem");
		if(pstr_GiftItem != NULL)
			pData->_GiftItem = pstr_GiftItem;
		else
			pData->_GiftItem = "";
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


