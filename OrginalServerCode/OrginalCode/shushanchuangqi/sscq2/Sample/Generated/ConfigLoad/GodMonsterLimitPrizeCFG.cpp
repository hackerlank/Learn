// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGodMonsterLimitPrizeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GodMonsterLimitPrizeCFG.h"
#include "tinyxml.h"

CGodMonsterLimitPrizeLoader::~CGodMonsterLimitPrizeLoader()
{
	ClearData();
}

void CGodMonsterLimitPrizeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGodMonsterLimitPrizeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGodMonsterLimitPrizeLoader::LoadData(const std::string& strPath)
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
		SGodMonsterLimitPrizeCFG* pData = new SGodMonsterLimitPrizeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_CurPrice = pDataElem->Attribute("CurPrice");
		if(pstr_CurPrice != NULL)
			pData->_CurPrice = (UINT16)atoi(pstr_CurPrice);
		else
			pData->_CurPrice = 0;
		const char* pstr_Discount = pDataElem->Attribute("Discount");
		if(pstr_Discount != NULL)
			pData->_Discount = (FLOAT)atof(pstr_Discount);
		else
			pData->_Discount = 0.0f;
		const char* pstr_OrigPrice = pDataElem->Attribute("OrigPrice");
		if(pstr_OrigPrice != NULL)
			pData->_OrigPrice = (UINT16)atoi(pstr_OrigPrice);
		else
			pData->_OrigPrice = 0;
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_Cond = pDataElem->Attribute("Cond");
		if(pstr_Cond != NULL)
			pData->_Cond = (UINT8)atoi(pstr_Cond);
		else
			pData->_Cond = 0;
		const char* pstr_Num = pDataElem->Attribute("Num");
		if(pstr_Num != NULL)
			pData->_Num = (UINT8)atoi(pstr_Num);
		else
			pData->_Num = 0;
		const char* pstr_Devote = pDataElem->Attribute("Devote");
		if(pstr_Devote != NULL)
			pData->_Devote = (UINT32)atoi(pstr_Devote);
		else
			pData->_Devote = 0;
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


