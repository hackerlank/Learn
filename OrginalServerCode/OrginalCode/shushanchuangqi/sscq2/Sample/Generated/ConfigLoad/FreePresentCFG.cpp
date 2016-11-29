// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFreePresentCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FreePresentCFG.h"
#include "tinyxml.h"

CFreePresentLoader::~CFreePresentLoader()
{
	ClearData();
}

void CFreePresentLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFreePresentCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFreePresentLoader::LoadData(const std::string& strPath)
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
		SFreePresentCFG* pData = new SFreePresentCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Content = pDataElem->Attribute("Content");
		if(pstr_Content != NULL)
			pData->_Content = pstr_Content;
		else
			pData->_Content = "";
		const char* pstr_Condition = pDataElem->Attribute("Condition");
		if(pstr_Condition != NULL)
			pData->_Condition = (UINT16)atoi(pstr_Condition);
		else
			pData->_Condition = 0;
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		const char* pstr_Msg = pDataElem->Attribute("Msg");
		if(pstr_Msg != NULL)
			pData->_Msg = pstr_Msg;
		else
			pData->_Msg = "";
		const char* pstr_img = pDataElem->Attribute("img");
		if(pstr_img != NULL)
			pData->_img = (UINT8)atoi(pstr_img);
		else
			pData->_img = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


