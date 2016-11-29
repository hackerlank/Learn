// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SChatWithShifuCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ChatWithShifuCFG.h"
#include "tinyxml.h"

CChatWithShifuLoader::~CChatWithShifuLoader()
{
	ClearData();
}

void CChatWithShifuLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SChatWithShifuCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CChatWithShifuLoader::LoadData(const std::string& strPath)
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
		SChatWithShifuCFG* pData = new SChatWithShifuCFG;
		const char* pstr_Num = pDataElem->Attribute("Num");
		if(pstr_Num != NULL)
			pData->_Num = (UINT16)atoi(pstr_Num);
		else
			pData->_Num = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Tip = pDataElem->Attribute("Tip");
		if(pstr_Tip != NULL)
			pData->_Tip = pstr_Tip;
		else
			pData->_Tip = "";
		const char* pstr_Descripition = pDataElem->Attribute("Descripition");
		if(pstr_Descripition != NULL)
			pData->_Descripition = pstr_Descripition;
		else
			pData->_Descripition = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


