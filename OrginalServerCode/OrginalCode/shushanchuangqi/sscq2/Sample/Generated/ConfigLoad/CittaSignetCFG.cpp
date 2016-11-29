// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaSignetCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CittaSignetCFG.h"
#include "tinyxml.h"

CCittaSignetLoader::~CCittaSignetLoader()
{
	ClearData();
}

void CCittaSignetLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCittaSignetCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCittaSignetLoader::LoadData(const std::string& strPath)
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
		SCittaSignetCFG* pData = new SCittaSignetCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TypeID = pDataElem->Attribute("TypeID");
		if(pstr_TypeID != NULL)
			pData->_TypeID = (UINT32)atoi(pstr_TypeID);
		else
			pData->_TypeID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_IdName = pDataElem->Attribute("IdName");
		if(pstr_IdName != NULL)
			pData->_IdName = pstr_IdName;
		else
			pData->_IdName = "";
		const char* pstr_Quality = pDataElem->Attribute("Quality");
		if(pstr_Quality != NULL)
			pData->_Quality = (UINT8)atoi(pstr_Quality);
		else
			pData->_Quality = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


