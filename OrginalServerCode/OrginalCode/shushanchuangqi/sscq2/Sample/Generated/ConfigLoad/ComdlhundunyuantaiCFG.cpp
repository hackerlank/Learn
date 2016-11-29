// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdlhundunyuantaiCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ComdlhundunyuantaiCFG.h"
#include "tinyxml.h"

CComdlhundunyuantaiLoader::~CComdlhundunyuantaiLoader()
{
	ClearData();
}

void CComdlhundunyuantaiLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SComdlhundunyuantaiCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CComdlhundunyuantaiLoader::LoadData(const std::string& strPath)
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
		SComdlhundunyuantaiCFG* pData = new SComdlhundunyuantaiCFG;
		const char* pstr_level = pDataElem->Attribute("level");
		if(pstr_level != NULL)
			pData->_level = (UINT8)atoi(pstr_level);
		else
			pData->_level = 0;
		const char* pstr_Yuanqi = pDataElem->Attribute("Yuanqi");
		if(pstr_Yuanqi != NULL)
			pData->_Yuanqi = (UINT16)atoi(pstr_Yuanqi);
		else
			pData->_Yuanqi = 0;
		const char* pstr_Greenloot = pDataElem->Attribute("Greenloot");
		if(pstr_Greenloot != NULL)
			pData->_Greenloot = pstr_Greenloot;
		else
			pData->_Greenloot = "";
		const char* pstr_Blueloot = pDataElem->Attribute("Blueloot");
		if(pstr_Blueloot != NULL)
			pData->_Blueloot = pstr_Blueloot;
		else
			pData->_Blueloot = "";
		const char* pstr_Purpleloot = pDataElem->Attribute("Purpleloot");
		if(pstr_Purpleloot != NULL)
			pData->_Purpleloot = pstr_Purpleloot;
		else
			pData->_Purpleloot = "";
		const char* pstr_Yellowloot = pDataElem->Attribute("Yellowloot");
		if(pstr_Yellowloot != NULL)
			pData->_Yellowloot = pstr_Yellowloot;
		else
			pData->_Yellowloot = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


