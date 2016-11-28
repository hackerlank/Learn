// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SChongZhiCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ChongZhiCFG.h"
#include "tinyxml.h"

CChongZhiLoader::~CChongZhiLoader()
{
	ClearData();
}

void CChongZhiLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SChongZhiCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CChongZhiLoader::LoadData(const std::string& strPath)
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
		SChongZhiCFG* pData = new SChongZhiCFG;
		const char* pstr_Id = pDataElem->Attribute("Id");
		if(pstr_Id != NULL)
			pData->_Id = (UINT32)atoi(pstr_Id);
		else
			pData->_Id = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Amount = pDataElem->Attribute("Amount");
		if(pstr_Amount != NULL)
			pData->_Amount = (UINT32)atoi(pstr_Amount);
		else
			pData->_Amount = 0;
		const char* pstr_Icon1 = pDataElem->Attribute("Icon1");
		if(pstr_Icon1 != NULL)
			pData->_Icon1 = pstr_Icon1;
		else
			pData->_Icon1 = "";
		const char* pstr_Gift = pDataElem->Attribute("Gift");
		if(pstr_Gift != NULL)
			pData->_Gift = pstr_Gift;
		else
			pData->_Gift = "";
		const char* pstr_Icon2 = pDataElem->Attribute("Icon2");
		if(pstr_Icon2 != NULL)
			pData->_Icon2 = pstr_Icon2;
		else
			pData->_Icon2 = "";
		const char* pstr_Tips = pDataElem->Attribute("Tips");
		if(pstr_Tips != NULL)
			pData->_Tips = pstr_Tips;
		else
			pData->_Tips = "";
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = (UINT32)atoi(pstr_ItemID);
		else
			pData->_ItemID = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


