// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SParameterCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ParameterCFG.h"
#include "tinyxml.h"

CParameterLoader::~CParameterLoader()
{
	ClearData();
}

void CParameterLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SParameterCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CParameterLoader::LoadData(const std::string& strPath)
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
		SParameterCFG* pData = new SParameterCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Fvalue = pDataElem->Attribute("Fvalue");
		if(pstr_Fvalue != NULL)
			pData->_Fvalue = (FLOAT)atof(pstr_Fvalue);
		else
			pData->_Fvalue = 0.0f;
		const char* pstr_Svalue = pDataElem->Attribute("Svalue");
		if(pstr_Svalue != NULL)
			pData->_Svalue = pstr_Svalue;
		else
			pData->_Svalue = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


