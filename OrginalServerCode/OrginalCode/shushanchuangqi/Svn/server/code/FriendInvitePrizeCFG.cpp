// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFriendInvitePrizeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FriendInvitePrizeCFG.h"
#include "tinyxml.h"

CFriendInvitePrizeLoader::~CFriendInvitePrizeLoader()
{
	ClearData();
}

void CFriendInvitePrizeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFriendInvitePrizeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFriendInvitePrizeLoader::LoadData(const std::string& strPath)
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
		SFriendInvitePrizeCFG* pData = new SFriendInvitePrizeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_MainId = pDataElem->Attribute("MainId");
		if(pstr_MainId != NULL)
			pData->_MainId = (UINT8)atoi(pstr_MainId);
		else
			pData->_MainId = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_SendInviteCnt = pDataElem->Attribute("SendInviteCnt");
		if(pstr_SendInviteCnt != NULL)
			pData->_SendInviteCnt = (UINT32)atoi(pstr_SendInviteCnt);
		else
			pData->_SendInviteCnt = 0;
		const char* pstr_FriendLevel = pDataElem->Attribute("FriendLevel");
		if(pstr_FriendLevel != NULL)
			pData->_FriendLevel = (UINT8)atoi(pstr_FriendLevel);
		else
			pData->_FriendLevel = 0;
		const char* pstr_VipLevel = pDataElem->Attribute("VipLevel");
		if(pstr_VipLevel != NULL)
			pData->_VipLevel = (UINT8)atoi(pstr_VipLevel);
		else
			pData->_VipLevel = 0;
		const char* pstr_BuyGold = pDataElem->Attribute("BuyGold");
		if(pstr_BuyGold != NULL)
			pData->_BuyGold = (UINT32)atoi(pstr_BuyGold);
		else
			pData->_BuyGold = 0;
		const char* pstr_GoodFriendCnt = pDataElem->Attribute("GoodFriendCnt");
		if(pstr_GoodFriendCnt != NULL)
			pData->_GoodFriendCnt = (UINT32)atoi(pstr_GoodFriendCnt);
		else
			pData->_GoodFriendCnt = 0;
		const char* pstr_Prize = pDataElem->Attribute("Prize");
		if(pstr_Prize != NULL)
			pData->_Prize = pstr_Prize;
		else
			pData->_Prize = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


