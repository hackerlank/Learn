// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDepotCostCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DepotCostCFG.h"
#include "tinyxml.h"

CDepotCostLoader::~CDepotCostLoader()
{
	ClearData();
}

void CDepotCostLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDepotCostCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDepotCostLoader::LoadData(const std::string& strPath)
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
		SDepotCostCFG* pData = new SDepotCostCFG;
		const char* pstr_Idx = pDataElem->Attribute("Idx");
		if(pstr_Idx != NULL)
			pData->_Idx = (UINT8)atoi(pstr_Idx);
		else
			pData->_Idx = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT8)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


