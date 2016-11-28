// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMainIconCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "MainIconCFG.h"
#include "tinyxml.h"

CMainIconLoader::~CMainIconLoader()
{
	ClearData();
}

void CMainIconLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SMainIconCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CMainIconLoader::LoadData(const std::string& strPath)
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
		SMainIconCFG* pData = new SMainIconCFG;
		const char* pstr_id = pDataElem->Attribute("id");
		if(pstr_id != NULL)
			pData->_id = (UINT16)atoi(pstr_id);
		else
			pData->_id = 0;
		const char* pstr_data = pDataElem->Attribute("data");
		if(pstr_data != NULL)
			pData->_data = pstr_data;
		else
			pData->_data = "";
		const char* pstr_descript = pDataElem->Attribute("descript");
		if(pstr_descript != NULL)
			pData->_descript = pstr_descript;
		else
			pData->_descript = "";
		const char* pstr_type = pDataElem->Attribute("type");
		if(pstr_type != NULL)
			pData->_type = (UINT16)atoi(pstr_type);
		else
			pData->_type = 0;
		const char* pstr_index = pDataElem->Attribute("index");
		if(pstr_index != NULL)
			pData->_index = (UINT16)atoi(pstr_index);
		else
			pData->_index = 0;
		const char* pstr_display = pDataElem->Attribute("display");
		if(pstr_display != NULL)
			pData->_display = (UINT16)atoi(pstr_display);
		else
			pData->_display = 0;
		const char* pstr_iconid = pDataElem->Attribute("iconid");
		if(pstr_iconid != NULL)
			pData->_iconid = (UINT16)atoi(pstr_iconid);
		else
			pData->_iconid = 0;
		const char* pstr_layoutid = pDataElem->Attribute("layoutid");
		if(pstr_layoutid != NULL)
			pData->_layoutid = (UINT16)atoi(pstr_layoutid);
		else
			pData->_layoutid = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


