// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SUpgradeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "UpgradeCFG.h"
#include "tinyxml.h"

CUpgradeLoader::~CUpgradeLoader()
{
	ClearData();
}

void CUpgradeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SUpgradeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CUpgradeLoader::LoadData(const std::string& strPath)
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
		SUpgradeCFG* pData = new SUpgradeCFG;
		const char* pstr_TargetItemId = pDataElem->Attribute("TargetItemId");
		if(pstr_TargetItemId != NULL)
			pData->_TargetItemId = (UINT16)atoi(pstr_TargetItemId);
		else
			pData->_TargetItemId = 0;
		const char* pstr_MaterialItemId = pDataElem->Attribute("MaterialItemId");
		if(pstr_MaterialItemId != NULL)
			pData->_MaterialItemId = pstr_MaterialItemId;
		else
			pData->_MaterialItemId = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


