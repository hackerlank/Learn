// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuideConfigCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuideConfigCFG.h"
#include "tinyxml.h"

CGuideConfigLoader::~CGuideConfigLoader()
{
	ClearData();
}

void CGuideConfigLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuideConfigCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuideConfigLoader::LoadData(const std::string& strPath)
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
		SGuideConfigCFG* pData = new SGuideConfigCFG;
		const char* pstr_id = pDataElem->Attribute("id");
		if(pstr_id != NULL)
			pData->_id = (UINT16)atoi(pstr_id);
		else
			pData->_id = 0;
		const char* pstr_content = pDataElem->Attribute("content");
		if(pstr_content != NULL)
			pData->_content = pstr_content;
		else
			pData->_content = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


