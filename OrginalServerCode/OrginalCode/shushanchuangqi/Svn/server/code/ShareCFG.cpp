// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShareCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ShareCFG.h"
#include "tinyxml.h"

CShareLoader::~CShareLoader()
{
	ClearData();
}

void CShareLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SShareCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CShareLoader::LoadData(const std::string& strPath)
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
		SShareCFG* pData = new SShareCFG;
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
		const char* pstr_Msg = pDataElem->Attribute("Msg");
		if(pstr_Msg != NULL)
			pData->_Msg = pstr_Msg;
		else
			pData->_Msg = "";
		const char* pstr_Summary = pDataElem->Attribute("Summary");
		if(pstr_Summary != NULL)
			pData->_Summary = pstr_Summary;
		else
			pData->_Summary = "";
		const char* pstr_Button = pDataElem->Attribute("Button");
		if(pstr_Button != NULL)
			pData->_Button = (UINT8)atoi(pstr_Button);
		else
			pData->_Button = 0;
		const char* pstr_Pic = pDataElem->Attribute("Pic");
		if(pstr_Pic != NULL)
			pData->_Pic = (UINT16)atoi(pstr_Pic);
		else
			pData->_Pic = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


