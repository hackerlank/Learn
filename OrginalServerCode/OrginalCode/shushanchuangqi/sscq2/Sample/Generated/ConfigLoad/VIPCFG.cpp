// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "VIPCFG.h"
#include "tinyxml.h"

CVIPLoader::~CVIPLoader()
{
	ClearData();
}

void CVIPLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SVIPCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CVIPLoader::LoadData(const std::string& strPath)
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
		SVIPCFG* pData = new SVIPCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Total = pDataElem->Attribute("Total");
		if(pstr_Total != NULL)
			pData->_Total = (UINT32)atoi(pstr_Total);
		else
			pData->_Total = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


