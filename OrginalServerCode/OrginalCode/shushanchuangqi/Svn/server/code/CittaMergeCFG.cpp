// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaMergeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CittaMergeCFG.h"
#include "tinyxml.h"

CCittaMergeLoader::~CCittaMergeLoader()
{
	ClearData();
}

void CCittaMergeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCittaMergeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCittaMergeLoader::LoadData(const std::string& strPath)
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
		SCittaMergeCFG* pData = new SCittaMergeCFG;
		const char* pstr_FormulaID = pDataElem->Attribute("FormulaID");
		if(pstr_FormulaID != NULL)
			pData->_FormulaID = (UINT32)atoi(pstr_FormulaID);
		else
			pData->_FormulaID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_CittaID = pDataElem->Attribute("CittaID");
		if(pstr_CittaID != NULL)
			pData->_CittaID = pstr_CittaID;
		else
			pData->_CittaID = "";
		const char* pstr_SignetID = pDataElem->Attribute("SignetID");
		if(pstr_SignetID != NULL)
			pData->_SignetID = pstr_SignetID;
		else
			pData->_SignetID = "";
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_RoleLevel = pDataElem->Attribute("RoleLevel");
		if(pstr_RoleLevel != NULL)
			pData->_RoleLevel = (UINT16)atoi(pstr_RoleLevel);
		else
			pData->_RoleLevel = 0;
		const char* pstr_Material1ID = pDataElem->Attribute("Material1ID");
		if(pstr_Material1ID != NULL)
			pData->_Material1ID = (UINT32)atoi(pstr_Material1ID);
		else
			pData->_Material1ID = 0;
		const char* pstr_Material1Count = pDataElem->Attribute("Material1Count");
		if(pstr_Material1Count != NULL)
			pData->_Material1Count = (UINT32)atoi(pstr_Material1Count);
		else
			pData->_Material1Count = 0;
		const char* pstr_Material2ID = pDataElem->Attribute("Material2ID");
		if(pstr_Material2ID != NULL)
			pData->_Material2ID = (UINT32)atoi(pstr_Material2ID);
		else
			pData->_Material2ID = 0;
		const char* pstr_Material2Count = pDataElem->Attribute("Material2Count");
		if(pstr_Material2Count != NULL)
			pData->_Material2Count = (UINT32)atoi(pstr_Material2Count);
		else
			pData->_Material2Count = 0;
		const char* pstr_Material3ID = pDataElem->Attribute("Material3ID");
		if(pstr_Material3ID != NULL)
			pData->_Material3ID = (UINT32)atoi(pstr_Material3ID);
		else
			pData->_Material3ID = 0;
		const char* pstr_Material3Count = pDataElem->Attribute("Material3Count");
		if(pstr_Material3Count != NULL)
			pData->_Material3Count = (UINT32)atoi(pstr_Material3Count);
		else
			pData->_Material3Count = 0;
		const char* pstr_Material4ID = pDataElem->Attribute("Material4ID");
		if(pstr_Material4ID != NULL)
			pData->_Material4ID = (UINT32)atoi(pstr_Material4ID);
		else
			pData->_Material4ID = 0;
		const char* pstr_Material4Count = pDataElem->Attribute("Material4Count");
		if(pstr_Material4Count != NULL)
			pData->_Material4Count = (UINT32)atoi(pstr_Material4Count);
		else
			pData->_Material4Count = 0;
		const char* pstr_SilverCost = pDataElem->Attribute("SilverCost");
		if(pstr_SilverCost != NULL)
			pData->_SilverCost = (UINT32)atoi(pstr_SilverCost);
		else
			pData->_SilverCost = 0;
		const char* pstr_Tips = pDataElem->Attribute("Tips");
		if(pstr_Tips != NULL)
			pData->_Tips = pstr_Tips;
		else
			pData->_Tips = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


