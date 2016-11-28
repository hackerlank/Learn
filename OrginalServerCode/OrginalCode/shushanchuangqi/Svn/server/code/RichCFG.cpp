// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SRichCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "RichCFG.h"
#include "tinyxml.h"

CRichLoader::~CRichLoader()
{
	ClearData();
}

void CRichLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SRichCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CRichLoader::LoadData(const std::string& strPath)
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
		SRichCFG* pData = new SRichCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_SmallBoxDropGroup = pDataElem->Attribute("SmallBoxDropGroup");
		if(pstr_SmallBoxDropGroup != NULL)
			pData->_SmallBoxDropGroup = (UINT16)atoi(pstr_SmallBoxDropGroup);
		else
			pData->_SmallBoxDropGroup = 0;
		const char* pstr_BigBoxDropGroup = pDataElem->Attribute("BigBoxDropGroup");
		if(pstr_BigBoxDropGroup != NULL)
			pData->_BigBoxDropGroup = (UINT16)atoi(pstr_BigBoxDropGroup);
		else
			pData->_BigBoxDropGroup = 0;
		const char* pstr_SuperBoxDropGroup = pDataElem->Attribute("SuperBoxDropGroup");
		if(pstr_SuperBoxDropGroup != NULL)
			pData->_SuperBoxDropGroup = (UINT16)atoi(pstr_SuperBoxDropGroup);
		else
			pData->_SuperBoxDropGroup = 0;
		const char* pstr_NormalDropGroup = pDataElem->Attribute("NormalDropGroup");
		if(pstr_NormalDropGroup != NULL)
			pData->_NormalDropGroup = pstr_NormalDropGroup;
		else
			pData->_NormalDropGroup = "";
		const char* pstr_EliteDropGroup = pDataElem->Attribute("EliteDropGroup");
		if(pstr_EliteDropGroup != NULL)
			pData->_EliteDropGroup = pstr_EliteDropGroup;
		else
			pData->_EliteDropGroup = "";
		const char* pstr_BossDropGroup = pDataElem->Attribute("BossDropGroup");
		if(pstr_BossDropGroup != NULL)
			pData->_BossDropGroup = pstr_BossDropGroup;
		else
			pData->_BossDropGroup = "";
		const char* pstr_ChrushDropGroup1 = pDataElem->Attribute("ChrushDropGroup1");
		if(pstr_ChrushDropGroup1 != NULL)
			pData->_ChrushDropGroup1 = pstr_ChrushDropGroup1;
		else
			pData->_ChrushDropGroup1 = "";
		const char* pstr_ChrushDropGroup2 = pDataElem->Attribute("ChrushDropGroup2");
		if(pstr_ChrushDropGroup2 != NULL)
			pData->_ChrushDropGroup2 = pstr_ChrushDropGroup2;
		else
			pData->_ChrushDropGroup2 = "";
		const char* pstr_ChrushDropGroup3 = pDataElem->Attribute("ChrushDropGroup3");
		if(pstr_ChrushDropGroup3 != NULL)
			pData->_ChrushDropGroup3 = pstr_ChrushDropGroup3;
		else
			pData->_ChrushDropGroup3 = "";
		const char* pstr_ChrushDropGroup4 = pDataElem->Attribute("ChrushDropGroup4");
		if(pstr_ChrushDropGroup4 != NULL)
			pData->_ChrushDropGroup4 = pstr_ChrushDropGroup4;
		else
			pData->_ChrushDropGroup4 = "";
		const char* pstr_PicDropGroup = pDataElem->Attribute("PicDropGroup");
		if(pstr_PicDropGroup != NULL)
			pData->_PicDropGroup = pstr_PicDropGroup;
		else
			pData->_PicDropGroup = "";
		const char* pstr_DrawDropGroup = pDataElem->Attribute("DrawDropGroup");
		if(pstr_DrawDropGroup != NULL)
			pData->_DrawDropGroup = pstr_DrawDropGroup;
		else
			pData->_DrawDropGroup = "";
		const char* pstr_SuperBoxPV = pDataElem->Attribute("SuperBoxPV");
		if(pstr_SuperBoxPV != NULL)
			pData->_SuperBoxPV = (UINT16)atoi(pstr_SuperBoxPV);
		else
			pData->_SuperBoxPV = 0;
		const char* pstr_WelcomeWord = pDataElem->Attribute("WelcomeWord");
		if(pstr_WelcomeWord != NULL)
			pData->_WelcomeWord = pstr_WelcomeWord;
		else
			pData->_WelcomeWord = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


