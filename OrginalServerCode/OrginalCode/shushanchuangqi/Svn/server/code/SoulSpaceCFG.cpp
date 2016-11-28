// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSoulSpaceCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SoulSpaceCFG.h"
#include "tinyxml.h"

CSoulSpaceLoader::~CSoulSpaceLoader()
{
	ClearData();
}

void CSoulSpaceLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSoulSpaceCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSoulSpaceLoader::LoadData(const std::string& strPath)
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
		SSoulSpaceCFG* pData = new SSoulSpaceCFG;
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
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT32)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_NeedLevel = pDataElem->Attribute("NeedLevel");
		if(pstr_NeedLevel != NULL)
			pData->_NeedLevel = (UINT32)atoi(pstr_NeedLevel);
		else
			pData->_NeedLevel = 0;
		const char* pstr_NeedMoneyType = pDataElem->Attribute("NeedMoneyType");
		if(pstr_NeedMoneyType != NULL)
			pData->_NeedMoneyType = (UINT32)atoi(pstr_NeedMoneyType);
		else
			pData->_NeedMoneyType = 0;
		const char* pstr_NeedMoneyValue = pDataElem->Attribute("NeedMoneyValue");
		if(pstr_NeedMoneyValue != NULL)
			pData->_NeedMoneyValue = (UINT32)atoi(pstr_NeedMoneyValue);
		else
			pData->_NeedMoneyValue = 0;
		const char* pstr_Attrib = pDataElem->Attribute("Attrib");
		if(pstr_Attrib != NULL)
			pData->_Attrib = pstr_Attrib;
		else
			pData->_Attrib = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


