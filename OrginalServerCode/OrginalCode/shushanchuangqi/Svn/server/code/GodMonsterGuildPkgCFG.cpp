// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGodMonsterGuildPkgCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GodMonsterGuildPkgCFG.h"
#include "tinyxml.h"

CGodMonsterGuildPkgLoader::~CGodMonsterGuildPkgLoader()
{
	ClearData();
}

void CGodMonsterGuildPkgLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGodMonsterGuildPkgCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGodMonsterGuildPkgLoader::LoadData(const std::string& strPath)
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
		SGodMonsterGuildPkgCFG* pData = new SGodMonsterGuildPkgCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_FieldDown = pDataElem->Attribute("FieldDown");
		if(pstr_FieldDown != NULL)
			pData->_FieldDown = (UINT16)atoi(pstr_FieldDown);
		else
			pData->_FieldDown = 0;
		const char* pstr_FieldUp = pDataElem->Attribute("FieldUp");
		if(pstr_FieldUp != NULL)
			pData->_FieldUp = (UINT16)atoi(pstr_FieldUp);
		else
			pData->_FieldUp = 0;
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_Content = pDataElem->Attribute("Content");
		if(pstr_Content != NULL)
			pData->_Content = pstr_Content;
		else
			pData->_Content = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


