// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttrShowCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AttrShowCFG.h"
#include "tinyxml.h"

CAttrShowLoader::~CAttrShowLoader()
{
	ClearData();
}

void CAttrShowLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAttrShowCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAttrShowLoader::LoadData(const std::string& strPath)
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
		SAttrShowCFG* pData = new SAttrShowCFG;
		const char* pstr_List_ID = pDataElem->Attribute("List_ID");
		if(pstr_List_ID != NULL)
			pData->_List_ID = (UINT8)atoi(pstr_List_ID);
		else
			pData->_List_ID = 0;
		const char* pstr_Attr_ID = pDataElem->Attribute("Attr_ID");
		if(pstr_Attr_ID != NULL)
			pData->_Attr_ID = (UINT8)atoi(pstr_Attr_ID);
		else
			pData->_Attr_ID = 0;
		const char* pstr_Attr_Name = pDataElem->Attribute("Attr_Name");
		if(pstr_Attr_Name != NULL)
			pData->_Attr_Name = pstr_Attr_Name;
		else
			pData->_Attr_Name = "";
		const char* pstr_Attr_Name1 = pDataElem->Attribute("Attr_Name1");
		if(pstr_Attr_Name1 != NULL)
			pData->_Attr_Name1 = pstr_Attr_Name1;
		else
			pData->_Attr_Name1 = "";
		const char* pstr_Show_Mod = pDataElem->Attribute("Show_Mod");
		if(pstr_Show_Mod != NULL)
			pData->_Show_Mod = (UINT8)atoi(pstr_Show_Mod);
		else
			pData->_Show_Mod = 0;
		const char* pstr_Show_Page = pDataElem->Attribute("Show_Page");
		if(pstr_Show_Page != NULL)
			pData->_Show_Page = (UINT8)atoi(pstr_Show_Page);
		else
			pData->_Show_Page = 0;
		const char* pstr_Page_Part = pDataElem->Attribute("Page_Part");
		if(pstr_Page_Part != NULL)
			pData->_Page_Part = (UINT8)atoi(pstr_Page_Part);
		else
			pData->_Page_Part = 0;
		const char* pstr_Part_Num = pDataElem->Attribute("Part_Num");
		if(pstr_Part_Num != NULL)
			pData->_Part_Num = (UINT8)atoi(pstr_Part_Num);
		else
			pData->_Part_Num = 0;
		const char* pstr_Show_Form = pDataElem->Attribute("Show_Form");
		if(pstr_Show_Form != NULL)
			pData->_Show_Form = pstr_Show_Form;
		else
			pData->_Show_Form = "";
		const char* pstr_Show_Tip_1 = pDataElem->Attribute("Show_Tip_1");
		if(pstr_Show_Tip_1 != NULL)
			pData->_Show_Tip_1 = pstr_Show_Tip_1;
		else
			pData->_Show_Tip_1 = "";
		const char* pstr_Show_Tip_2 = pDataElem->Attribute("Show_Tip_2");
		if(pstr_Show_Tip_2 != NULL)
			pData->_Show_Tip_2 = pstr_Show_Tip_2;
		else
			pData->_Show_Tip_2 = "";
		const char* pstr_Tip_Need_Attr = pDataElem->Attribute("Tip_Need_Attr");
		if(pstr_Tip_Need_Attr != NULL)
			pData->_Tip_Need_Attr = pstr_Tip_Need_Attr;
		else
			pData->_Tip_Need_Attr = "";
		const char* pstr_Battle_Points = pDataElem->Attribute("Battle_Points");
		if(pstr_Battle_Points != NULL)
			pData->_Battle_Points = (UINT32)atoi(pstr_Battle_Points);
		else
			pData->_Battle_Points = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


