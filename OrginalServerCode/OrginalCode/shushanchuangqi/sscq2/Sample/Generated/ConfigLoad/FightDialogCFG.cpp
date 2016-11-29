// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFightDialogCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FightDialogCFG.h"
#include "tinyxml.h"

CFightDialogLoader::~CFightDialogLoader()
{
	ClearData();
}

void CFightDialogLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFightDialogCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFightDialogLoader::LoadData(const std::string& strPath)
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
		SFightDialogCFG* pData = new SFightDialogCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Dialog = pDataElem->Attribute("Dialog");
		if(pstr_Dialog != NULL)
			pData->_Dialog = pstr_Dialog;
		else
			pData->_Dialog = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


