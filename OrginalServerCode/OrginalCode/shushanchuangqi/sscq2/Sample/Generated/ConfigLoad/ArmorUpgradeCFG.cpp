// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SArmorUpgradeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ArmorUpgradeCFG.h"
#include "tinyxml.h"

CArmorUpgradeLoader::~CArmorUpgradeLoader()
{
	ClearData();
}

void CArmorUpgradeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SArmorUpgradeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CArmorUpgradeLoader::LoadData(const std::string& strPath)
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
		SArmorUpgradeCFG* pData = new SArmorUpgradeCFG;
		const char* pstr_Id1 = pDataElem->Attribute("Id1");
		if(pstr_Id1 != NULL)
			pData->_Id1 = (UINT16)atoi(pstr_Id1);
		else
			pData->_Id1 = 0;
		const char* pstr_Id2 = pDataElem->Attribute("Id2");
		if(pstr_Id2 != NULL)
			pData->_Id2 = (UINT16)atoi(pstr_Id2);
		else
			pData->_Id2 = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Material1 = pDataElem->Attribute("Material1");
		if(pstr_Material1 != NULL)
			pData->_Material1 = (UINT16)atoi(pstr_Material1);
		else
			pData->_Material1 = 0;
		const char* pstr_Number1 = pDataElem->Attribute("Number1");
		if(pstr_Number1 != NULL)
			pData->_Number1 = (UINT8)atoi(pstr_Number1);
		else
			pData->_Number1 = 0;
		const char* pstr_Material2 = pDataElem->Attribute("Material2");
		if(pstr_Material2 != NULL)
			pData->_Material2 = (UINT16)atoi(pstr_Material2);
		else
			pData->_Material2 = 0;
		const char* pstr_Number2 = pDataElem->Attribute("Number2");
		if(pstr_Number2 != NULL)
			pData->_Number2 = (UINT8)atoi(pstr_Number2);
		else
			pData->_Number2 = 0;
		const char* pstr_Material3 = pDataElem->Attribute("Material3");
		if(pstr_Material3 != NULL)
			pData->_Material3 = (UINT16)atoi(pstr_Material3);
		else
			pData->_Material3 = 0;
		const char* pstr_Number3 = pDataElem->Attribute("Number3");
		if(pstr_Number3 != NULL)
			pData->_Number3 = (UINT8)atoi(pstr_Number3);
		else
			pData->_Number3 = 0;
		const char* pstr_Material4 = pDataElem->Attribute("Material4");
		if(pstr_Material4 != NULL)
			pData->_Material4 = (UINT16)atoi(pstr_Material4);
		else
			pData->_Material4 = 0;
		const char* pstr_Number4 = pDataElem->Attribute("Number4");
		if(pstr_Number4 != NULL)
			pData->_Number4 = (UINT8)atoi(pstr_Number4);
		else
			pData->_Number4 = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT32)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


