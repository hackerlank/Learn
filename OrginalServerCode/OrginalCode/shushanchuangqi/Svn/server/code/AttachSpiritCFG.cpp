// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttachSpiritCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AttachSpiritCFG.h"
#include "tinyxml.h"

CAttachSpiritLoader::~CAttachSpiritLoader()
{
	ClearData();
}

void CAttachSpiritLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAttachSpiritCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAttachSpiritLoader::LoadData(const std::string& strPath)
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
		SAttachSpiritCFG* pData = new SAttachSpiritCFG;
		const char* pstr_SoulLevel = pDataElem->Attribute("SoulLevel");
		if(pstr_SoulLevel != NULL)
			pData->_SoulLevel = (UINT8)atoi(pstr_SoulLevel);
		else
			pData->_SoulLevel = 0;
		const char* pstr_SoulCost = pDataElem->Attribute("SoulCost");
		if(pstr_SoulCost != NULL)
			pData->_SoulCost = (UINT32)atoi(pstr_SoulCost);
		else
			pData->_SoulCost = 0;
		const char* pstr_AttachMin = pDataElem->Attribute("AttachMin");
		if(pstr_AttachMin != NULL)
			pData->_AttachMin = (UINT32)atoi(pstr_AttachMin);
		else
			pData->_AttachMin = 0;
		const char* pstr_AttachMax = pDataElem->Attribute("AttachMax");
		if(pstr_AttachMax != NULL)
			pData->_AttachMax = (UINT32)atoi(pstr_AttachMax);
		else
			pData->_AttachMax = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


