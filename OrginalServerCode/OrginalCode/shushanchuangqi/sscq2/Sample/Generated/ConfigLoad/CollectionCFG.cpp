// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCollectionCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CollectionCFG.h"
#include "tinyxml.h"

CCollectionLoader::~CCollectionLoader()
{
	ClearData();
}

void CCollectionLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCollectionCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCollectionLoader::LoadData(const std::string& strPath)
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
		SCollectionCFG* pData = new SCollectionCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Type1 = pDataElem->Attribute("Type1");
		if(pstr_Type1 != NULL)
			pData->_Type1 = (UINT16)atoi(pstr_Type1);
		else
			pData->_Type1 = 0;
		const char* pstr_Type2 = pDataElem->Attribute("Type2");
		if(pstr_Type2 != NULL)
			pData->_Type2 = (UINT16)atoi(pstr_Type2);
		else
			pData->_Type2 = 0;
		const char* pstr_Carreer = pDataElem->Attribute("Carreer");
		if(pstr_Carreer != NULL)
			pData->_Carreer = (UINT8)atoi(pstr_Carreer);
		else
			pData->_Carreer = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_EventID = pDataElem->Attribute("EventID");
		if(pstr_EventID != NULL)
			pData->_EventID = (UINT16)atoi(pstr_EventID);
		else
			pData->_EventID = 0;
		const char* pstr_CP = pDataElem->Attribute("CP");
		if(pstr_CP != NULL)
			pData->_CP = (UINT16)atoi(pstr_CP);
		else
			pData->_CP = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


