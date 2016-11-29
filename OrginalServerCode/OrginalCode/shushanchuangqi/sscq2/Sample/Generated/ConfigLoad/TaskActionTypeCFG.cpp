// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STaskActionTypeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TaskActionTypeCFG.h"
#include "tinyxml.h"

CTaskActionTypeLoader::~CTaskActionTypeLoader()
{
	ClearData();
}

void CTaskActionTypeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STaskActionTypeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTaskActionTypeLoader::LoadData(const std::string& strPath)
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
		STaskActionTypeCFG* pData = new STaskActionTypeCFG;
		const char* pstr_type = pDataElem->Attribute("type");
		if(pstr_type != NULL)
			pData->_type = (UINT16)atoi(pstr_type);
		else
			pData->_type = 0;
		const char* pstr_typepara = pDataElem->Attribute("typepara");
		if(pstr_typepara != NULL)
			pData->_typepara = (UINT16)atoi(pstr_typepara);
		else
			pData->_typepara = 0;
		const char* pstr_moduleName = pDataElem->Attribute("moduleName");
		if(pstr_moduleName != NULL)
			pData->_moduleName = pstr_moduleName;
		else
			pData->_moduleName = "";
		const char* pstr_format = pDataElem->Attribute("format");
		if(pstr_format != NULL)
			pData->_format = pstr_format;
		else
			pData->_format = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


