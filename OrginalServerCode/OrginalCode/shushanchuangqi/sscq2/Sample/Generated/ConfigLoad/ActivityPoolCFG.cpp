// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityPoolCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityPoolCFG.h"
#include "tinyxml.h"

CActivityPoolLoader::~CActivityPoolLoader()
{
	ClearData();
}

void CActivityPoolLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityPoolCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityPoolLoader::LoadData(const std::string& strPath)
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
		SActivityPoolCFG* pData = new SActivityPoolCFG;
		const char* pstr_VIPLevel = pDataElem->Attribute("VIPLevel");
		if(pstr_VIPLevel != NULL)
			pData->_VIPLevel = (UINT16)atoi(pstr_VIPLevel);
		else
			pData->_VIPLevel = 0;
		const char* pstr_LootID = pDataElem->Attribute("LootID");
		if(pstr_LootID != NULL)
			pData->_LootID = (UINT32)atoi(pstr_LootID);
		else
			pData->_LootID = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


