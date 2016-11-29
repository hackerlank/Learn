// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShuShanLunJianExpCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ShuShanLunJianExpCFG.h"
#include "tinyxml.h"

CShuShanLunJianExpLoader::~CShuShanLunJianExpLoader()
{
	ClearData();
}

void CShuShanLunJianExpLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SShuShanLunJianExpCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CShuShanLunJianExpLoader::LoadData(const std::string& strPath)
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
		SShuShanLunJianExpCFG* pData = new SShuShanLunJianExpCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_ExpAward = pDataElem->Attribute("ExpAward");
		if(pstr_ExpAward != NULL)
			pData->_ExpAward = (UINT32)atoi(pstr_ExpAward);
		else
			pData->_ExpAward = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


