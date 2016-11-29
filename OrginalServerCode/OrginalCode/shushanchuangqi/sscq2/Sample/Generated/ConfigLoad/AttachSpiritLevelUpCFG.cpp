// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttachSpiritLevelUpCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AttachSpiritLevelUpCFG.h"
#include "tinyxml.h"

CAttachSpiritLevelUpLoader::~CAttachSpiritLevelUpLoader()
{
	ClearData();
}

void CAttachSpiritLevelUpLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAttachSpiritLevelUpCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAttachSpiritLevelUpLoader::LoadData(const std::string& strPath)
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
		SAttachSpiritLevelUpCFG* pData = new SAttachSpiritLevelUpCFG;
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_ArmorType = pDataElem->Attribute("ArmorType");
		if(pstr_ArmorType != NULL)
			pData->_ArmorType = (UINT8)atoi(pstr_ArmorType);
		else
			pData->_ArmorType = 0;
		const char* pstr_SoulLevel = pDataElem->Attribute("SoulLevel");
		if(pstr_SoulLevel != NULL)
			pData->_SoulLevel = (UINT8)atoi(pstr_SoulLevel);
		else
			pData->_SoulLevel = 0;
		const char* pstr_Soul1 = pDataElem->Attribute("Soul1");
		if(pstr_Soul1 != NULL)
			pData->_Soul1 = (UINT8)atoi(pstr_Soul1);
		else
			pData->_Soul1 = 0;
		const char* pstr_Value1 = pDataElem->Attribute("Value1");
		if(pstr_Value1 != NULL)
			pData->_Value1 = (UINT32)atoi(pstr_Value1);
		else
			pData->_Value1 = 0;
		const char* pstr_Soul2 = pDataElem->Attribute("Soul2");
		if(pstr_Soul2 != NULL)
			pData->_Soul2 = (UINT8)atoi(pstr_Soul2);
		else
			pData->_Soul2 = 0;
		const char* pstr_Value2 = pDataElem->Attribute("Value2");
		if(pstr_Value2 != NULL)
			pData->_Value2 = (UINT32)atoi(pstr_Value2);
		else
			pData->_Value2 = 0;
		const char* pstr_Soul3 = pDataElem->Attribute("Soul3");
		if(pstr_Soul3 != NULL)
			pData->_Soul3 = (UINT8)atoi(pstr_Soul3);
		else
			pData->_Soul3 = 0;
		const char* pstr_Value3 = pDataElem->Attribute("Value3");
		if(pstr_Value3 != NULL)
			pData->_Value3 = (UINT32)atoi(pstr_Value3);
		else
			pData->_Value3 = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


