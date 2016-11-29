// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSignInCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SignInCFG.h"
#include "tinyxml.h"

CSignInLoader::~CSignInLoader()
{
	ClearData();
}

void CSignInLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSignInCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSignInLoader::LoadData(const std::string& strPath)
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
		SSignInCFG* pData = new SSignInCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_SignIn = pDataElem->Attribute("SignIn");
		if(pstr_SignIn != NULL)
			pData->_SignIn = (UINT8)atoi(pstr_SignIn);
		else
			pData->_SignIn = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


