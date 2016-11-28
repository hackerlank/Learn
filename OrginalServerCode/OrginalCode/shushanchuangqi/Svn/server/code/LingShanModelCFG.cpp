// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanModelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LingShanModelCFG.h"
#include "tinyxml.h"

CLingShanModelLoader::~CLingShanModelLoader()
{
	ClearData();
}

void CLingShanModelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLingShanModelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLingShanModelLoader::LoadData(const std::string& strPath)
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
		SLingShanModelCFG* pData = new SLingShanModelCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_CondId = pDataElem->Attribute("CondId");
		if(pstr_CondId != NULL)
			pData->_CondId = (UINT16)atoi(pstr_CondId);
		else
			pData->_CondId = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


