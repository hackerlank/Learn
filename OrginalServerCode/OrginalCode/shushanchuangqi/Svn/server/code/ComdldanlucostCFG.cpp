// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanlucostCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ComdldanlucostCFG.h"
#include "tinyxml.h"

CComdldanlucostLoader::~CComdldanlucostLoader()
{
	ClearData();
}

void CComdldanlucostLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SComdldanlucostCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CComdldanlucostLoader::LoadData(const std::string& strPath)
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
		SComdldanlucostCFG* pData = new SComdldanlucostCFG;
		const char* pstr_Sequence = pDataElem->Attribute("Sequence");
		if(pstr_Sequence != NULL)
			pData->_Sequence = (UINT8)atoi(pstr_Sequence);
		else
			pData->_Sequence = 0;
		const char* pstr_playerLevel = pDataElem->Attribute("playerLevel");
		if(pstr_playerLevel != NULL)
			pData->_playerLevel = (UINT8)atoi(pstr_playerLevel);
		else
			pData->_playerLevel = 0;
		const char* pstr_Vip = pDataElem->Attribute("Vip");
		if(pstr_Vip != NULL)
			pData->_Vip = (UINT8)atoi(pstr_Vip);
		else
			pData->_Vip = 0;
		const char* pstr_Jiuyidinglevel = pDataElem->Attribute("Jiuyidinglevel");
		if(pstr_Jiuyidinglevel != NULL)
			pData->_Jiuyidinglevel = (UINT8)atoi(pstr_Jiuyidinglevel);
		else
			pData->_Jiuyidinglevel = 0;
		const char* pstr_Silver = pDataElem->Attribute("Silver");
		if(pstr_Silver != NULL)
			pData->_Silver = (UINT32)atoi(pstr_Silver);
		else
			pData->_Silver = 0;
		const char* pstr_Coupon = pDataElem->Attribute("Coupon");
		if(pstr_Coupon != NULL)
			pData->_Coupon = (UINT16)atoi(pstr_Coupon);
		else
			pData->_Coupon = 0;
		const char* pstr_Gold = pDataElem->Attribute("Gold");
		if(pstr_Gold != NULL)
			pData->_Gold = (UINT16)atoi(pstr_Gold);
		else
			pData->_Gold = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


