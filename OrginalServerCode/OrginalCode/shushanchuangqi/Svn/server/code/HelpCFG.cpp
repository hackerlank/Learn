// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHelpCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "HelpCFG.h"
#include "tinyxml.h"

CHelpLoader::~CHelpLoader()
{
	ClearData();
}

void CHelpLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SHelpCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CHelpLoader::LoadData(const std::string& strPath)
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
		SHelpCFG* pData = new SHelpCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_NamePicId = pDataElem->Attribute("NamePicId");
		if(pstr_NamePicId != NULL)
			pData->_NamePicId = (UINT16)atoi(pstr_NamePicId);
		else
			pData->_NamePicId = 0;
		const char* pstr_FunctionName = pDataElem->Attribute("FunctionName");
		if(pstr_FunctionName != NULL)
			pData->_FunctionName = pstr_FunctionName;
		else
			pData->_FunctionName = "";
		const char* pstr_StoveExp = pDataElem->Attribute("StoveExp");
		if(pstr_StoveExp != NULL)
			pData->_StoveExp = pstr_StoveExp;
		else
			pData->_StoveExp = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


