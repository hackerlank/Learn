#include "stdafx.h"
#include "InvalidUserMgr.h"
#include "tinyxml.h"

std::set<string> CInvalidUserMgr::_setInvalidName;

bool CInvalidUserMgr::Init()
{
	std::string strPath = Config._strConfigDir + "InvalidUser.xml";
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
	TiXmlElement* pDataElem = pElemRoot->FirstChildElement("InvalidUser");
	while(pDataElem != NULL)
	{
		const char* pstr_name = pDataElem->Attribute("name");
		if(pstr_name != NULL)
			_setInvalidName.insert(pstr_name);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}

bool CInvalidUserMgr::CheckUserName(const std::string& strName)
{
	return _setInvalidName.find(strName) == _setInvalidName.end();
}