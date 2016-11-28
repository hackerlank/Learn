// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBarrierCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BarrierCFG.h"
#include "tinyxml.h"

CBarrierLoader::~CBarrierLoader()
{
	ClearData();
}

void CBarrierLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBarrierCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBarrierLoader::LoadData(const std::string& strPath)
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
		SBarrierCFG* pData = new SBarrierCFG;
		const char* pstr_ConditionID = pDataElem->Attribute("ConditionID");
		if(pstr_ConditionID != NULL)
			pData->_ConditionID = (UINT16)atoi(pstr_ConditionID);
		else
			pData->_ConditionID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Condition_1 = pDataElem->Attribute("Condition_1");
		if(pstr_Condition_1 != NULL)
			pData->_Condition_1 = pstr_Condition_1;
		else
			pData->_Condition_1 = "";
		const char* pstr_Condition_2 = pDataElem->Attribute("Condition_2");
		if(pstr_Condition_2 != NULL)
			pData->_Condition_2 = pstr_Condition_2;
		else
			pData->_Condition_2 = "";
		const char* pstr_Condition_3 = pDataElem->Attribute("Condition_3");
		if(pstr_Condition_3 != NULL)
			pData->_Condition_3 = pstr_Condition_3;
		else
			pData->_Condition_3 = "";
		const char* pstr_Condition_4 = pDataElem->Attribute("Condition_4");
		if(pstr_Condition_4 != NULL)
			pData->_Condition_4 = pstr_Condition_4;
		else
			pData->_Condition_4 = "";
		const char* pstr_Condition_5 = pDataElem->Attribute("Condition_5");
		if(pstr_Condition_5 != NULL)
			pData->_Condition_5 = pstr_Condition_5;
		else
			pData->_Condition_5 = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


