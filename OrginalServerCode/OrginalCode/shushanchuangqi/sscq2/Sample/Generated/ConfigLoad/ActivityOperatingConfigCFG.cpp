// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityOperatingConfigCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityOperatingConfigCFG.h"
#include "tinyxml.h"

CActivityOperatingConfigLoader::~CActivityOperatingConfigLoader()
{
	ClearData();
}

void CActivityOperatingConfigLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityOperatingConfigCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityOperatingConfigLoader::LoadData(const std::string& strPath)
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
		SActivityOperatingConfigCFG* pData = new SActivityOperatingConfigCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TableID = pDataElem->Attribute("TableID");
		if(pstr_TableID != NULL)
			pData->_TableID = pstr_TableID;
		else
			pData->_TableID = "";
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_TypePara1 = pDataElem->Attribute("TypePara1");
		if(pstr_TypePara1 != NULL)
			pData->_TypePara1 = pstr_TypePara1;
		else
			pData->_TypePara1 = "";
		const char* pstr_TypePara2 = pDataElem->Attribute("TypePara2");
		if(pstr_TypePara2 != NULL)
			pData->_TypePara2 = pstr_TypePara2;
		else
			pData->_TypePara2 = "";
		const char* pstr_TypePara4 = pDataElem->Attribute("TypePara4");
		if(pstr_TypePara4 != NULL)
			pData->_TypePara4 = pstr_TypePara4;
		else
			pData->_TypePara4 = "";
		const char* pstr_TypePara5 = pDataElem->Attribute("TypePara5");
		if(pstr_TypePara5 != NULL)
			pData->_TypePara5 = pstr_TypePara5;
		else
			pData->_TypePara5 = "";
		const char* pstr_TypePara3 = pDataElem->Attribute("TypePara3");
		if(pstr_TypePara3 != NULL)
			pData->_TypePara3 = pstr_TypePara3;
		else
			pData->_TypePara3 = "";
		const char* pstr_MailTitle = pDataElem->Attribute("MailTitle");
		if(pstr_MailTitle != NULL)
			pData->_MailTitle = (UINT16)atoi(pstr_MailTitle);
		else
			pData->_MailTitle = 0;
		const char* pstr_MailContent = pDataElem->Attribute("MailContent");
		if(pstr_MailContent != NULL)
			pData->_MailContent = (UINT16)atoi(pstr_MailContent);
		else
			pData->_MailContent = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


