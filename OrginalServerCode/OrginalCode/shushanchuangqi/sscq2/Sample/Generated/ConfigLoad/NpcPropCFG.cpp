// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SNpcPropCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "NpcPropCFG.h"
#include "tinyxml.h"

CNpcPropLoader::~CNpcPropLoader()
{
	ClearData();
}

void CNpcPropLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SNpcPropCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CNpcPropLoader::LoadData(const std::string& strPath)
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
		SNpcPropCFG* pData = new SNpcPropCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_BarrierID = pDataElem->Attribute("BarrierID");
		if(pstr_BarrierID != NULL)
			pData->_BarrierID = (UINT8)atoi(pstr_BarrierID);
		else
			pData->_BarrierID = 0;
		const char* pstr_Script = pDataElem->Attribute("Script");
		if(pstr_Script != NULL)
			pData->_Script = pstr_Script;
		else
			pData->_Script = "";
		const char* pstr_FreePatrolDistance = pDataElem->Attribute("FreePatrolDistance");
		if(pstr_FreePatrolDistance != NULL)
			pData->_FreePatrolDistance = (UINT8)atoi(pstr_FreePatrolDistance);
		else
			pData->_FreePatrolDistance = 0;
		const char* pstr_Speed = pDataElem->Attribute("Speed");
		if(pstr_Speed != NULL)
			pData->_Speed = (UINT32)atoi(pstr_Speed);
		else
			pData->_Speed = 0;
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT32)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_ModelScale = pDataElem->Attribute("ModelScale");
		if(pstr_ModelScale != NULL)
			pData->_ModelScale = (FLOAT)atof(pstr_ModelScale);
		else
			pData->_ModelScale = 0.0f;
		const char* pstr_MapResID = pDataElem->Attribute("MapResID");
		if(pstr_MapResID != NULL)
			pData->_MapResID = pstr_MapResID;
		else
			pData->_MapResID = "";
		const char* pstr_AssetType = pDataElem->Attribute("AssetType");
		if(pstr_AssetType != NULL)
			pData->_AssetType = (UINT8)atoi(pstr_AssetType);
		else
			pData->_AssetType = 0;
		const char* pstr_AssetParam1 = pDataElem->Attribute("AssetParam1");
		if(pstr_AssetParam1 != NULL)
			pData->_AssetParam1 = (UINT16)atoi(pstr_AssetParam1);
		else
			pData->_AssetParam1 = 0;
		const char* pstr_AssetParam2 = pDataElem->Attribute("AssetParam2");
		if(pstr_AssetParam2 != NULL)
			pData->_AssetParam2 = (UINT8)atoi(pstr_AssetParam2);
		else
			pData->_AssetParam2 = 0;
		const char* pstr_AssetParam3 = pDataElem->Attribute("AssetParam3");
		if(pstr_AssetParam3 != NULL)
			pData->_AssetParam3 = pstr_AssetParam3;
		else
			pData->_AssetParam3 = "";
		const char* pstr_IfHide = pDataElem->Attribute("IfHide");
		if(pstr_IfHide != NULL)
			pData->_IfHide = (UINT8)atoi(pstr_IfHide);
		else
			pData->_IfHide = 0;
		const char* pstr_GuiDgn = pDataElem->Attribute("GuiDgn");
		if(pstr_GuiDgn != NULL)
			pData->_GuiDgn = (UINT16)atoi(pstr_GuiDgn);
		else
			pData->_GuiDgn = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


