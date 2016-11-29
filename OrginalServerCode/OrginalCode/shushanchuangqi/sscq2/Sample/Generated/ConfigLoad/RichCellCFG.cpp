// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SRichCellCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "RichCellCFG.h"
#include "tinyxml.h"

CRichCellLoader::~CRichCellLoader()
{
	ClearData();
}

void CRichCellLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SRichCellCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CRichCellLoader::LoadData(const std::string& strPath)
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
		SRichCellCFG* pData = new SRichCellCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_EmptyCellWeight = pDataElem->Attribute("EmptyCellWeight");
		if(pstr_EmptyCellWeight != NULL)
			pData->_EmptyCellWeight = (UINT16)atoi(pstr_EmptyCellWeight);
		else
			pData->_EmptyCellWeight = 0;
		const char* pstr_SmallBoxWeight = pDataElem->Attribute("SmallBoxWeight");
		if(pstr_SmallBoxWeight != NULL)
			pData->_SmallBoxWeight = (UINT16)atoi(pstr_SmallBoxWeight);
		else
			pData->_SmallBoxWeight = 0;
		const char* pstr_BigBoxWeight = pDataElem->Attribute("BigBoxWeight");
		if(pstr_BigBoxWeight != NULL)
			pData->_BigBoxWeight = (UINT16)atoi(pstr_BigBoxWeight);
		else
			pData->_BigBoxWeight = 0;
		const char* pstr_SuperBoxWeight = pDataElem->Attribute("SuperBoxWeight");
		if(pstr_SuperBoxWeight != NULL)
			pData->_SuperBoxWeight = (UINT16)atoi(pstr_SuperBoxWeight);
		else
			pData->_SuperBoxWeight = 0;
		const char* pstr_NormalWeight = pDataElem->Attribute("NormalWeight");
		if(pstr_NormalWeight != NULL)
			pData->_NormalWeight = (UINT16)atoi(pstr_NormalWeight);
		else
			pData->_NormalWeight = 0;
		const char* pstr_EliteWeight = pDataElem->Attribute("EliteWeight");
		if(pstr_EliteWeight != NULL)
			pData->_EliteWeight = (UINT16)atoi(pstr_EliteWeight);
		else
			pData->_EliteWeight = 0;
		const char* pstr_BossWeight = pDataElem->Attribute("BossWeight");
		if(pstr_BossWeight != NULL)
			pData->_BossWeight = (UINT16)atoi(pstr_BossWeight);
		else
			pData->_BossWeight = 0;
		const char* pstr_ChrushWeight = pDataElem->Attribute("ChrushWeight");
		if(pstr_ChrushWeight != NULL)
			pData->_ChrushWeight = (UINT16)atoi(pstr_ChrushWeight);
		else
			pData->_ChrushWeight = 0;
		const char* pstr_PicWeight = pDataElem->Attribute("PicWeight");
		if(pstr_PicWeight != NULL)
			pData->_PicWeight = (UINT16)atoi(pstr_PicWeight);
		else
			pData->_PicWeight = 0;
		const char* pstr_DrawWeight = pDataElem->Attribute("DrawWeight");
		if(pstr_DrawWeight != NULL)
			pData->_DrawWeight = (UINT16)atoi(pstr_DrawWeight);
		else
			pData->_DrawWeight = 0;
		const char* pstr_RandomWeight = pDataElem->Attribute("RandomWeight");
		if(pstr_RandomWeight != NULL)
			pData->_RandomWeight = (UINT16)atoi(pstr_RandomWeight);
		else
			pData->_RandomWeight = 0;
		const char* pstr_Xposition = pDataElem->Attribute("Xposition");
		if(pstr_Xposition != NULL)
			pData->_Xposition = (UINT16)atoi(pstr_Xposition);
		else
			pData->_Xposition = 0;
		const char* pstr_Ypisition = pDataElem->Attribute("Ypisition");
		if(pstr_Ypisition != NULL)
			pData->_Ypisition = (UINT16)atoi(pstr_Ypisition);
		else
			pData->_Ypisition = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


