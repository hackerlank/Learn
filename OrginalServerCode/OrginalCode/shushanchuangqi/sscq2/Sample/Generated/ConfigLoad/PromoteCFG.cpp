// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "PromoteCFG.h"
#include "tinyxml.h"

CPromoteLoader::~CPromoteLoader()
{
	ClearData();
}

void CPromoteLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SPromoteCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CPromoteLoader::LoadData(const std::string& strPath)
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
		SPromoteCFG* pData = new SPromoteCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Level1 = pDataElem->Attribute("Level1");
		if(pstr_Level1 != NULL)
			pData->_Level1 = (UINT32)atoi(pstr_Level1);
		else
			pData->_Level1 = 0;
		const char* pstr_Level2 = pDataElem->Attribute("Level2");
		if(pstr_Level2 != NULL)
			pData->_Level2 = (UINT32)atoi(pstr_Level2);
		else
			pData->_Level2 = 0;
		const char* pstr_Level3 = pDataElem->Attribute("Level3");
		if(pstr_Level3 != NULL)
			pData->_Level3 = (UINT32)atoi(pstr_Level3);
		else
			pData->_Level3 = 0;
		const char* pstr_Level4 = pDataElem->Attribute("Level4");
		if(pstr_Level4 != NULL)
			pData->_Level4 = (UINT32)atoi(pstr_Level4);
		else
			pData->_Level4 = 0;
		const char* pstr_Level5 = pDataElem->Attribute("Level5");
		if(pstr_Level5 != NULL)
			pData->_Level5 = (UINT32)atoi(pstr_Level5);
		else
			pData->_Level5 = 0;
		const char* pstr_Level6 = pDataElem->Attribute("Level6");
		if(pstr_Level6 != NULL)
			pData->_Level6 = (UINT32)atoi(pstr_Level6);
		else
			pData->_Level6 = 0;
		const char* pstr_Level7 = pDataElem->Attribute("Level7");
		if(pstr_Level7 != NULL)
			pData->_Level7 = (UINT32)atoi(pstr_Level7);
		else
			pData->_Level7 = 0;
		const char* pstr_Level8 = pDataElem->Attribute("Level8");
		if(pstr_Level8 != NULL)
			pData->_Level8 = (UINT32)atoi(pstr_Level8);
		else
			pData->_Level8 = 0;
		const char* pstr_Level9 = pDataElem->Attribute("Level9");
		if(pstr_Level9 != NULL)
			pData->_Level9 = (UINT32)atoi(pstr_Level9);
		else
			pData->_Level9 = 0;
		const char* pstr_Level10 = pDataElem->Attribute("Level10");
		if(pstr_Level10 != NULL)
			pData->_Level10 = (UINT32)atoi(pstr_Level10);
		else
			pData->_Level10 = 0;
		const char* pstr_Level11 = pDataElem->Attribute("Level11");
		if(pstr_Level11 != NULL)
			pData->_Level11 = (UINT32)atoi(pstr_Level11);
		else
			pData->_Level11 = 0;
		const char* pstr_Level12 = pDataElem->Attribute("Level12");
		if(pstr_Level12 != NULL)
			pData->_Level12 = (UINT32)atoi(pstr_Level12);
		else
			pData->_Level12 = 0;
		const char* pstr_Level13 = pDataElem->Attribute("Level13");
		if(pstr_Level13 != NULL)
			pData->_Level13 = (UINT32)atoi(pstr_Level13);
		else
			pData->_Level13 = 0;
		const char* pstr_Level14 = pDataElem->Attribute("Level14");
		if(pstr_Level14 != NULL)
			pData->_Level14 = (UINT32)atoi(pstr_Level14);
		else
			pData->_Level14 = 0;
		const char* pstr_Level15 = pDataElem->Attribute("Level15");
		if(pstr_Level15 != NULL)
			pData->_Level15 = (UINT32)atoi(pstr_Level15);
		else
			pData->_Level15 = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


