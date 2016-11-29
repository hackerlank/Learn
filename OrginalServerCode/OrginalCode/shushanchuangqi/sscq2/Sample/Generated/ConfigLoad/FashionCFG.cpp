// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFashionCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FashionCFG.h"
#include "tinyxml.h"

CFashionLoader::~CFashionLoader()
{
	ClearData();
}

void CFashionLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFashionCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFashionLoader::LoadData(const std::string& strPath)
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
		SFashionCFG* pData = new SFashionCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Material = pDataElem->Attribute("Material");
		if(pstr_Material != NULL)
			pData->_Material = (UINT16)atoi(pstr_Material);
		else
			pData->_Material = 0;
		const char* pstr_Number = pDataElem->Attribute("Number");
		if(pstr_Number != NULL)
			pData->_Number = (UINT16)atoi(pstr_Number);
		else
			pData->_Number = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT32)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		const char* pstr_Each_exp = pDataElem->Attribute("Each_exp");
		if(pstr_Each_exp != NULL)
			pData->_Each_exp = (UINT32)atoi(pstr_Each_exp);
		else
			pData->_Each_exp = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


