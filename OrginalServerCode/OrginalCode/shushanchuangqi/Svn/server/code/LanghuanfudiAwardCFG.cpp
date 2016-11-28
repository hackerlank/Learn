// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLanghuanfudiAwardCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LanghuanfudiAwardCFG.h"
#include "tinyxml.h"

CLanghuanfudiAwardLoader::~CLanghuanfudiAwardLoader()
{
	ClearData();
}

void CLanghuanfudiAwardLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLanghuanfudiAwardCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLanghuanfudiAwardLoader::LoadData(const std::string& strPath)
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
		SLanghuanfudiAwardCFG* pData = new SLanghuanfudiAwardCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_SitBasicXiuwei = pDataElem->Attribute("SitBasicXiuwei");
		if(pstr_SitBasicXiuwei != NULL)
			pData->_SitBasicXiuwei = (UINT16)atoi(pstr_SitBasicXiuwei);
		else
			pData->_SitBasicXiuwei = 0;
		const char* pstr_SkillXiuwei = pDataElem->Attribute("SkillXiuwei");
		if(pstr_SkillXiuwei != NULL)
			pData->_SkillXiuwei = (UINT16)atoi(pstr_SkillXiuwei);
		else
			pData->_SkillXiuwei = 0;
		const char* pstr_SitBasicExp = pDataElem->Attribute("SitBasicExp");
		if(pstr_SitBasicExp != NULL)
			pData->_SitBasicExp = (UINT16)atoi(pstr_SitBasicExp);
		else
			pData->_SitBasicExp = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


