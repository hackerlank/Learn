// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterZuHeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterZuHeCFG.h"
#include "tinyxml.h"

CFighterZuHeLoader::~CFighterZuHeLoader()
{
	ClearData();
}

void CFighterZuHeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterZuHeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterZuHeLoader::LoadData(const std::string& strPath)
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
		SFighterZuHeCFG* pData = new SFighterZuHeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_BaseEffect = pDataElem->Attribute("BaseEffect");
		if(pstr_BaseEffect != NULL)
			pData->_BaseEffect = (UINT16)atoi(pstr_BaseEffect);
		else
			pData->_BaseEffect = 0;
		const char* pstr_FullEffect = pDataElem->Attribute("FullEffect");
		if(pstr_FullEffect != NULL)
			pData->_FullEffect = (UINT16)atoi(pstr_FullEffect);
		else
			pData->_FullEffect = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


