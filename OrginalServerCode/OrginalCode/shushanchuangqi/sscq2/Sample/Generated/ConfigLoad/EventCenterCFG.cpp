// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEventCenterCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EventCenterCFG.h"
#include "tinyxml.h"

CEventCenterLoader::~CEventCenterLoader()
{
	ClearData();
}

void CEventCenterLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEventCenterCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEventCenterLoader::LoadData(const std::string& strPath)
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
		SEventCenterCFG* pData = new SEventCenterCFG;
		const char* pstr_EventInstID = pDataElem->Attribute("EventInstID");
		if(pstr_EventInstID != NULL)
			pData->_EventInstID = (UINT32)atoi(pstr_EventInstID);
		else
			pData->_EventInstID = 0;
		const char* pstr_EventType = pDataElem->Attribute("EventType");
		if(pstr_EventType != NULL)
			pData->_EventType = (UINT32)atoi(pstr_EventType);
		else
			pData->_EventType = 0;
		const char* pstr_GetCondType = pDataElem->Attribute("GetCondType");
		if(pstr_GetCondType != NULL)
			pData->_GetCondType = (UINT16)atoi(pstr_GetCondType);
		else
			pData->_GetCondType = 0;
		const char* pstr_OpType1 = pDataElem->Attribute("OpType1");
		if(pstr_OpType1 != NULL)
			pData->_OpType1 = (UINT16)atoi(pstr_OpType1);
		else
			pData->_OpType1 = 0;
		const char* pstr_OpType2 = pDataElem->Attribute("OpType2");
		if(pstr_OpType2 != NULL)
			pData->_OpType2 = (UINT16)atoi(pstr_OpType2);
		else
			pData->_OpType2 = 0;
		const char* pstr_OpVecType = pDataElem->Attribute("OpVecType");
		if(pstr_OpVecType != NULL)
			pData->_OpVecType = (UINT16)atoi(pstr_OpVecType);
		else
			pData->_OpVecType = 0;
		const char* pstr_ParamLimit1 = pDataElem->Attribute("ParamLimit1");
		if(pstr_ParamLimit1 != NULL)
			pData->_ParamLimit1 = (UINT32)atoi(pstr_ParamLimit1);
		else
			pData->_ParamLimit1 = 0;
		const char* pstr_ParamLimit2 = pDataElem->Attribute("ParamLimit2");
		if(pstr_ParamLimit2 != NULL)
			pData->_ParamLimit2 = (UINT32)atoi(pstr_ParamLimit2);
		else
			pData->_ParamLimit2 = 0;
		const char* pstr_VecParamLimit = pDataElem->Attribute("VecParamLimit");
		if(pstr_VecParamLimit != NULL)
			pData->_VecParamLimit = pstr_VecParamLimit;
		else
			pData->_VecParamLimit = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


