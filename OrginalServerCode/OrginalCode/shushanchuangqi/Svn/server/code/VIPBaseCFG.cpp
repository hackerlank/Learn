// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPBaseCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "VIPBaseCFG.h"
#include "tinyxml.h"

CVIPBaseLoader::~CVIPBaseLoader()
{
	ClearData();
}

void CVIPBaseLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SVIPBaseCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CVIPBaseLoader::LoadData(const std::string& strPath)
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
		SVIPBaseCFG* pData = new SVIPBaseCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Days = pDataElem->Attribute("Days");
		if(pstr_Days != NULL)
			pData->_Days = (UINT32)atoi(pstr_Days);
		else
			pData->_Days = 0;
		const char* pstr_NeedGold = pDataElem->Attribute("NeedGold");
		if(pstr_NeedGold != NULL)
			pData->_NeedGold = (UINT32)atoi(pstr_NeedGold);
		else
			pData->_NeedGold = 0;
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_Promotion = pDataElem->Attribute("Promotion");
		if(pstr_Promotion != NULL)
			pData->_Promotion = (UINT16)atoi(pstr_Promotion);
		else
			pData->_Promotion = 0;
		const char* pstr_Give = pDataElem->Attribute("Give");
		if(pstr_Give != NULL)
			pData->_Give = (UINT16)atoi(pstr_Give);
		else
			pData->_Give = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


