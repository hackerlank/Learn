// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_shimenCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "Daily_shimenCFG.h"
#include "tinyxml.h"

CDaily_shimenLoader::~CDaily_shimenLoader()
{
	ClearData();
}

void CDaily_shimenLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDaily_shimenCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDaily_shimenLoader::LoadData(const std::string& strPath)
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
		SDaily_shimenCFG* pData = new SDaily_shimenCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT16)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_Retrun = pDataElem->Attribute("Retrun");
		if(pstr_Retrun != NULL)
			pData->_Retrun = (UINT16)atoi(pstr_Retrun);
		else
			pData->_Retrun = 0;
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = (UINT8)atoi(pstr_Title);
		else
			pData->_Title = 0;
		const char* pstr_Task = pDataElem->Attribute("Task");
		if(pstr_Task != NULL)
			pData->_Task = (UINT16)atoi(pstr_Task);
		else
			pData->_Task = 0;
		const char* pstr_Descripition = pDataElem->Attribute("Descripition");
		if(pstr_Descripition != NULL)
			pData->_Descripition = pstr_Descripition;
		else
			pData->_Descripition = "";
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT16)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


