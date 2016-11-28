// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExclusionCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ExclusionCFG.h"
#include "tinyxml.h"

CExclusionLoader::~CExclusionLoader()
{
	ClearData();
}

void CExclusionLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SExclusionCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CExclusionLoader::LoadData(const std::string& strPath)
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
		SExclusionCFG* pData = new SExclusionCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_One = pDataElem->Attribute("One");
		if(pstr_One != NULL)
			pData->_One = (UINT8)atoi(pstr_One);
		else
			pData->_One = 0;
		const char* pstr_Two = pDataElem->Attribute("Two");
		if(pstr_Two != NULL)
			pData->_Two = (UINT8)atoi(pstr_Two);
		else
			pData->_Two = 0;
		const char* pstr_Three = pDataElem->Attribute("Three");
		if(pstr_Three != NULL)
			pData->_Three = (UINT8)atoi(pstr_Three);
		else
			pData->_Three = 0;
		const char* pstr_Four = pDataElem->Attribute("Four");
		if(pstr_Four != NULL)
			pData->_Four = (UINT8)atoi(pstr_Four);
		else
			pData->_Four = 0;
		const char* pstr_Five = pDataElem->Attribute("Five");
		if(pstr_Five != NULL)
			pData->_Five = (UINT8)atoi(pstr_Five);
		else
			pData->_Five = 0;
		const char* pstr_Six = pDataElem->Attribute("Six");
		if(pstr_Six != NULL)
			pData->_Six = (UINT8)atoi(pstr_Six);
		else
			pData->_Six = 0;
		const char* pstr_Seven = pDataElem->Attribute("Seven");
		if(pstr_Seven != NULL)
			pData->_Seven = (UINT8)atoi(pstr_Seven);
		else
			pData->_Seven = 0;
		const char* pstr_Eight = pDataElem->Attribute("Eight");
		if(pstr_Eight != NULL)
			pData->_Eight = (UINT8)atoi(pstr_Eight);
		else
			pData->_Eight = 0;
		const char* pstr_Nine = pDataElem->Attribute("Nine");
		if(pstr_Nine != NULL)
			pData->_Nine = (UINT8)atoi(pstr_Nine);
		else
			pData->_Nine = 0;
		const char* pstr_Ten = pDataElem->Attribute("Ten");
		if(pstr_Ten != NULL)
			pData->_Ten = (UINT8)atoi(pstr_Ten);
		else
			pData->_Ten = 0;
		const char* pstr_Eleven = pDataElem->Attribute("Eleven");
		if(pstr_Eleven != NULL)
			pData->_Eleven = (UINT8)atoi(pstr_Eleven);
		else
			pData->_Eleven = 0;
		const char* pstr_Twelve = pDataElem->Attribute("Twelve");
		if(pstr_Twelve != NULL)
			pData->_Twelve = (UINT8)atoi(pstr_Twelve);
		else
			pData->_Twelve = 0;
		const char* pstr_Thirteen = pDataElem->Attribute("Thirteen");
		if(pstr_Thirteen != NULL)
			pData->_Thirteen = (UINT8)atoi(pstr_Thirteen);
		else
			pData->_Thirteen = 0;
		const char* pstr_Forteen = pDataElem->Attribute("Forteen");
		if(pstr_Forteen != NULL)
			pData->_Forteen = (UINT8)atoi(pstr_Forteen);
		else
			pData->_Forteen = 0;
		const char* pstr_Fifteen = pDataElem->Attribute("Fifteen");
		if(pstr_Fifteen != NULL)
			pData->_Fifteen = (UINT8)atoi(pstr_Fifteen);
		else
			pData->_Fifteen = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


