// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCircleTaskNumCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CircleTaskNumCFG.h"
#include "tinyxml.h"

CCircleTaskNumLoader::~CCircleTaskNumLoader()
{
	ClearData();
}

void CCircleTaskNumLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCircleTaskNumCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCircleTaskNumLoader::LoadData(const std::string& strPath)
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
		SCircleTaskNumCFG* pData = new SCircleTaskNumCFG;
		const char* pstr_NumId = pDataElem->Attribute("NumId");
		if(pstr_NumId != NULL)
			pData->_NumId = (UINT16)atoi(pstr_NumId);
		else
			pData->_NumId = 0;
		const char* pstr_AdditionRate = pDataElem->Attribute("AdditionRate");
		if(pstr_AdditionRate != NULL)
			pData->_AdditionRate = (UINT16)atoi(pstr_AdditionRate);
		else
			pData->_AdditionRate = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


