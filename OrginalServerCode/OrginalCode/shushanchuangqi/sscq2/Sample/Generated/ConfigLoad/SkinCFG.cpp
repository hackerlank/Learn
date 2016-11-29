// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkinCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SkinCFG.h"
#include "tinyxml.h"

CSkinLoader::~CSkinLoader()
{
	ClearData();
}

void CSkinLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSkinCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSkinLoader::LoadData(const std::string& strPath)
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
		SSkinCFG* pData = new SSkinCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_Sex = pDataElem->Attribute("Sex");
		if(pstr_Sex != NULL)
			pData->_Sex = (UINT8)atoi(pstr_Sex);
		else
			pData->_Sex = 0;
		const char* pstr_SkinId = pDataElem->Attribute("SkinId");
		if(pstr_SkinId != NULL)
			pData->_SkinId = (UINT8)atoi(pstr_SkinId);
		else
			pData->_SkinId = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Appendix = pDataElem->Attribute("Appendix");
		if(pstr_Appendix != NULL)
			pData->_Appendix = (UINT16)atoi(pstr_Appendix);
		else
			pData->_Appendix = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


