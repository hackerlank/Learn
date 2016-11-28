// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaSignetSuitCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CittaSignetSuitCFG.h"
#include "tinyxml.h"

CCittaSignetSuitLoader::~CCittaSignetSuitLoader()
{
	ClearData();
}

void CCittaSignetSuitLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCittaSignetSuitCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCittaSignetSuitLoader::LoadData(const std::string& strPath)
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
		SCittaSignetSuitCFG* pData = new SCittaSignetSuitCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_SignetID = pDataElem->Attribute("SignetID");
		if(pstr_SignetID != NULL)
			pData->_SignetID = pstr_SignetID;
		else
			pData->_SignetID = "";
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Number1 = pDataElem->Attribute("Number1");
		if(pstr_Number1 != NULL)
			pData->_Number1 = (UINT8)atoi(pstr_Number1);
		else
			pData->_Number1 = 0;
		const char* pstr_AttrID1 = pDataElem->Attribute("AttrID1");
		if(pstr_AttrID1 != NULL)
			pData->_AttrID1 = (UINT32)atoi(pstr_AttrID1);
		else
			pData->_AttrID1 = 0;
		const char* pstr_Number2 = pDataElem->Attribute("Number2");
		if(pstr_Number2 != NULL)
			pData->_Number2 = (UINT8)atoi(pstr_Number2);
		else
			pData->_Number2 = 0;
		const char* pstr_AttrID2 = pDataElem->Attribute("AttrID2");
		if(pstr_AttrID2 != NULL)
			pData->_AttrID2 = (UINT32)atoi(pstr_AttrID2);
		else
			pData->_AttrID2 = 0;
		const char* pstr_Number3 = pDataElem->Attribute("Number3");
		if(pstr_Number3 != NULL)
			pData->_Number3 = (UINT8)atoi(pstr_Number3);
		else
			pData->_Number3 = 0;
		const char* pstr_AttrID3 = pDataElem->Attribute("AttrID3");
		if(pstr_AttrID3 != NULL)
			pData->_AttrID3 = (UINT32)atoi(pstr_AttrID3);
		else
			pData->_AttrID3 = 0;
		const char* pstr_Number4 = pDataElem->Attribute("Number4");
		if(pstr_Number4 != NULL)
			pData->_Number4 = (UINT8)atoi(pstr_Number4);
		else
			pData->_Number4 = 0;
		const char* pstr_AttrID4 = pDataElem->Attribute("AttrID4");
		if(pstr_AttrID4 != NULL)
			pData->_AttrID4 = (UINT32)atoi(pstr_AttrID4);
		else
			pData->_AttrID4 = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


