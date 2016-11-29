// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillTipsCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SkillTipsCFG.h"
#include "tinyxml.h"

CSkillTipsLoader::~CSkillTipsLoader()
{
	ClearData();
}

void CSkillTipsLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSkillTipsCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSkillTipsLoader::LoadData(const std::string& strPath)
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
		SSkillTipsCFG* pData = new SSkillTipsCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


