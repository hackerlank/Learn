// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDataUploadCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DataUploadCFG.h"
#include "tinyxml.h"

CDataUploadLoader::~CDataUploadLoader()
{
	ClearData();
}

void CDataUploadLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDataUploadCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDataUploadLoader::LoadData(const std::string& strPath)
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
		SDataUploadCFG* pData = new SDataUploadCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_EventID = pDataElem->Attribute("EventID");
		if(pstr_EventID != NULL)
			pData->_EventID = (UINT16)atoi(pstr_EventID);
		else
			pData->_EventID = 0;
		const char* pstr_category = pDataElem->Attribute("category");
		if(pstr_category != NULL)
			pData->_category = pstr_category;
		else
			pData->_category = "";
		const char* pstr_action = pDataElem->Attribute("action");
		if(pstr_action != NULL)
			pData->_action = pstr_action;
		else
			pData->_action = "";
		const char* pstr_Para = pDataElem->Attribute("Para");
		if(pstr_Para != NULL)
			pData->_Para = (UINT16)atoi(pstr_Para);
		else
			pData->_Para = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


