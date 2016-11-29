// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanfangCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ComdldanfangCFG.h"
#include "tinyxml.h"

CComdldanfangLoader::~CComdldanfangLoader()
{
	ClearData();
}

void CComdldanfangLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SComdldanfangCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CComdldanfangLoader::LoadData(const std::string& strPath)
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
		SComdldanfangCFG* pData = new SComdldanfangCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Yuanqi = pDataElem->Attribute("Yuanqi");
		if(pstr_Yuanqi != NULL)
			pData->_Yuanqi = (UINT16)atoi(pstr_Yuanqi);
		else
			pData->_Yuanqi = 0;
		const char* pstr_Output = pDataElem->Attribute("Output");
		if(pstr_Output != NULL)
			pData->_Output = pstr_Output;
		else
			pData->_Output = "";
		const char* pstr_Ingredient = pDataElem->Attribute("Ingredient");
		if(pstr_Ingredient != NULL)
			pData->_Ingredient = pstr_Ingredient;
		else
			pData->_Ingredient = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


