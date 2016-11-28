/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DBData.cpp
//  Purpose:      数据库序列化结构
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DBData.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDBData
{

SUserPropStream::SUserPropStream() : dwGoldCoin(0), dwHonour(0), byCamp(0), dwLastLeaveTime(0) { }

SUserPropStream::SUserPropStream(UINT32 dwGoldCoin_, UINT32 dwHonour_, UINT8 byCamp_, UINT32 dwLastLeaveTime_) : dwGoldCoin(dwGoldCoin_), dwHonour(dwHonour_), byCamp(byCamp_), dwLastLeaveTime(dwLastLeaveTime_) { }

CInArchive& operator>>(CInArchive& src, SUserPropStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwGoldCoin;
	src >> s.dwHonour;
	src >> s.byCamp;
	src >> s.dwLastLeaveTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserPropStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwGoldCoin;
	src << s.dwHonour;
	src << s.byCamp;
	src << s.dwLastLeaveTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUserPropStream& s)
{
	if(strcmp(rElement.Value(), "SUserPropStream") != 0)
	{
		LOG_CRI << "rElement is not SUserPropStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGoldCoin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGoldCoin") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGoldCoin!";
		return false;
	}
	const char* pszVal_dwGoldCoin = pElemChild->Attribute("value");
	if(pszVal_dwGoldCoin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGoldCoin, s.dwGoldCoin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHonour is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHonour") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHonour!";
		return false;
	}
	const char* pszVal_dwHonour = pElemChild->Attribute("value");
	if(pszVal_dwHonour == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHonour, s.dwHonour))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCamp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCamp") != 0)
	{
		LOG_CRI << "Attribute: name is not byCamp!";
		return false;
	}
	const char* pszVal_byCamp = pElemChild->Attribute("value");
	if(pszVal_byCamp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCamp, s.byCamp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastLeaveTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastLeaveTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastLeaveTime!";
		return false;
	}
	const char* pszVal_dwLastLeaveTime = pElemChild->Attribute("value");
	if(pszVal_dwLastLeaveTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastLeaveTime, s.dwLastLeaveTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SUserPropStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserPropStream");
	rElement.SetAttribute("type", ToUTF8Ptr("帐号基本数据"));
	unique_ptr<TiXmlElement> pElem_dwGoldCoin(new TiXmlElement("UINT32"));
	if(pElem_dwGoldCoin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGoldCoin->SetAttribute("name", "dwGoldCoin");
	pElem_dwGoldCoin->SetAttribute("value", NumberToString(s.dwGoldCoin).c_str());
	pElem_dwGoldCoin->SetAttribute("comment", ToUTF8Ptr("仙石"));
	if(rElement.LinkEndChild(pElem_dwGoldCoin.get()) != NULL)
		pElem_dwGoldCoin.release();
	unique_ptr<TiXmlElement> pElem_dwHonour(new TiXmlElement("UINT32"));
	if(pElem_dwHonour == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHonour->SetAttribute("name", "dwHonour");
	pElem_dwHonour->SetAttribute("value", NumberToString(s.dwHonour).c_str());
	pElem_dwHonour->SetAttribute("comment", ToUTF8Ptr("荣誉"));
	if(rElement.LinkEndChild(pElem_dwHonour.get()) != NULL)
		pElem_dwHonour.release();
	unique_ptr<TiXmlElement> pElem_byCamp(new TiXmlElement("UINT8"));
	if(pElem_byCamp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCamp->SetAttribute("name", "byCamp");
	pElem_byCamp->SetAttribute("value", NumberToString(s.byCamp).c_str());
	pElem_byCamp->SetAttribute("comment", ToUTF8Ptr("阵营"));
	if(rElement.LinkEndChild(pElem_byCamp.get()) != NULL)
		pElem_byCamp.release();
	unique_ptr<TiXmlElement> pElem_dwLastLeaveTime(new TiXmlElement("UINT32"));
	if(pElem_dwLastLeaveTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastLeaveTime->SetAttribute("name", "dwLastLeaveTime");
	pElem_dwLastLeaveTime->SetAttribute("value", NumberToString(s.dwLastLeaveTime).c_str());
	pElem_dwLastLeaveTime->SetAttribute("comment", ToUTF8Ptr("最后一次下线时间"));
	if(rElement.LinkEndChild(pElem_dwLastLeaveTime.get()) != NULL)
		pElem_dwLastLeaveTime.release();
	return true;
}

#endif

SBasePropStream::SBasePropStream() : dwCurHP(0), dwCurMP(0), byElement(0), wUseTitleID(0), wUseHorseID(0) { }

SBasePropStream::SBasePropStream(UINT32 dwCurHP_, UINT32 dwCurMP_, UINT8 byElement_, UINT16 wUseTitleID_, UINT16 wUseHorseID_)
			: dwCurHP(dwCurHP_), dwCurMP(dwCurMP_), byElement(byElement_), wUseTitleID(wUseTitleID_), wUseHorseID(wUseHorseID_) { }

CInArchive& operator>>(CInArchive& src, SBasePropStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwCurHP;
	src >> s.dwCurMP;
	src >> s.byElement;
	src >> s.wUseTitleID;
	src >> s.wUseHorseID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBasePropStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwCurHP;
	src << s.dwCurMP;
	src << s.byElement;
	src << s.wUseTitleID;
	src << s.wUseHorseID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBasePropStream& s)
{
	if(strcmp(rElement.Value(), "SBasePropStream") != 0)
	{
		LOG_CRI << "rElement is not SBasePropStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurHP!";
		return false;
	}
	const char* pszVal_dwCurHP = pElemChild->Attribute("value");
	if(pszVal_dwCurHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurHP, s.dwCurHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurMP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurMP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurMP!";
		return false;
	}
	const char* pszVal_dwCurMP = pElemChild->Attribute("value");
	if(pszVal_dwCurMP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurMP, s.dwCurMP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byElement is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byElement") != 0)
	{
		LOG_CRI << "Attribute: name is not byElement!";
		return false;
	}
	const char* pszVal_byElement = pElemChild->Attribute("value");
	if(pszVal_byElement == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byElement, s.byElement))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wUseTitleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wUseTitleID") != 0)
	{
		LOG_CRI << "Attribute: name is not wUseTitleID!";
		return false;
	}
	const char* pszVal_wUseTitleID = pElemChild->Attribute("value");
	if(pszVal_wUseTitleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wUseTitleID, s.wUseTitleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wUseHorseID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wUseHorseID") != 0)
	{
		LOG_CRI << "Attribute: name is not wUseHorseID!";
		return false;
	}
	const char* pszVal_wUseHorseID = pElemChild->Attribute("value");
	if(pszVal_wUseHorseID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wUseHorseID, s.wUseHorseID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBasePropStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBasePropStream");
	rElement.SetAttribute("type", ToUTF8Ptr("角色基本数据(战斗相关)"));
	unique_ptr<TiXmlElement> pElem_dwCurHP(new TiXmlElement("UINT32"));
	if(pElem_dwCurHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurHP->SetAttribute("name", "dwCurHP");
	pElem_dwCurHP->SetAttribute("value", NumberToString(s.dwCurHP).c_str());
	pElem_dwCurHP->SetAttribute("comment", ToUTF8Ptr("当前HP"));
	if(rElement.LinkEndChild(pElem_dwCurHP.get()) != NULL)
		pElem_dwCurHP.release();
	unique_ptr<TiXmlElement> pElem_dwCurMP(new TiXmlElement("UINT32"));
	if(pElem_dwCurMP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurMP->SetAttribute("name", "dwCurMP");
	pElem_dwCurMP->SetAttribute("value", NumberToString(s.dwCurMP).c_str());
	pElem_dwCurMP->SetAttribute("comment", ToUTF8Ptr("当前MP"));
	if(rElement.LinkEndChild(pElem_dwCurMP.get()) != NULL)
		pElem_dwCurMP.release();
	unique_ptr<TiXmlElement> pElem_byElement(new TiXmlElement("UINT8"));
	if(pElem_byElement == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byElement->SetAttribute("name", "byElement");
	pElem_byElement->SetAttribute("value", NumberToString(s.byElement).c_str());
	pElem_byElement->SetAttribute("comment", ToUTF8Ptr("元素属性"));
	if(rElement.LinkEndChild(pElem_byElement.get()) != NULL)
		pElem_byElement.release();
	unique_ptr<TiXmlElement> pElem_wUseTitleID(new TiXmlElement("UINT16"));
	if(pElem_wUseTitleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wUseTitleID->SetAttribute("name", "wUseTitleID");
	pElem_wUseTitleID->SetAttribute("value", NumberToString(s.wUseTitleID).c_str());
	pElem_wUseTitleID->SetAttribute("comment", ToUTF8Ptr("当前使用称号"));
	if(rElement.LinkEndChild(pElem_wUseTitleID.get()) != NULL)
		pElem_wUseTitleID.release();
	unique_ptr<TiXmlElement> pElem_wUseHorseID(new TiXmlElement("UINT16"));
	if(pElem_wUseHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wUseHorseID->SetAttribute("name", "wUseHorseID");
	pElem_wUseHorseID->SetAttribute("value", NumberToString(s.wUseHorseID).c_str());
	pElem_wUseHorseID->SetAttribute("comment", ToUTF8Ptr("当前骑乘坐骑"));
	if(rElement.LinkEndChild(pElem_wUseHorseID.get()) != NULL)
		pElem_wUseHorseID.release();
	return true;
}

#endif

SExtPropStream::SExtPropStream() : dwExp(0), dwDgnInstID(0), dwDgnCreateTime(0), wPreDgnMapID(0), fPreDgnX(0), 
			fPreDgnY(0) { }

SExtPropStream::SExtPropStream(UINT32 dwExp_, UINT32 dwDgnInstID_, UINT32 dwDgnCreateTime_, UINT16 wPreDgnMapID_, float fPreDgnX_, 
			float fPreDgnY_)
			: dwExp(dwExp_), dwDgnInstID(dwDgnInstID_), dwDgnCreateTime(dwDgnCreateTime_), wPreDgnMapID(wPreDgnMapID_), fPreDgnX(fPreDgnX_), 
			fPreDgnY(fPreDgnY_) { }

CInArchive& operator>>(CInArchive& src, SExtPropStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwExp;
	src >> s.dwDgnInstID;
	src >> s.dwDgnCreateTime;
	src >> s.wPreDgnMapID;
	src >> s.fPreDgnX;
	src >> s.fPreDgnY;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExtPropStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwExp;
	src << s.dwDgnInstID;
	src << s.dwDgnCreateTime;
	src << s.wPreDgnMapID;
	src << s.fPreDgnX;
	src << s.fPreDgnY;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExtPropStream& s)
{
	if(strcmp(rElement.Value(), "SExtPropStream") != 0)
	{
		LOG_CRI << "rElement is not SExtPropStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDgnInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDgnInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDgnInstID!";
		return false;
	}
	const char* pszVal_dwDgnInstID = pElemChild->Attribute("value");
	if(pszVal_dwDgnInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDgnInstID, s.dwDgnInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDgnCreateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDgnCreateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDgnCreateTime!";
		return false;
	}
	const char* pszVal_dwDgnCreateTime = pElemChild->Attribute("value");
	if(pszVal_dwDgnCreateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDgnCreateTime, s.dwDgnCreateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPreDgnMapID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPreDgnMapID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPreDgnMapID!";
		return false;
	}
	const char* pszVal_wPreDgnMapID = pElemChild->Attribute("value");
	if(pszVal_wPreDgnMapID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPreDgnMapID, s.wPreDgnMapID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fPreDgnX is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fPreDgnX") != 0)
	{
		LOG_CRI << "Attribute: name is not fPreDgnX!";
		return false;
	}
	const char* pszVal_fPreDgnX = pElemChild->Attribute("value");
	if(pszVal_fPreDgnX == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fPreDgnX, s.fPreDgnX))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fPreDgnY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fPreDgnY") != 0)
	{
		LOG_CRI << "Attribute: name is not fPreDgnY!";
		return false;
	}
	const char* pszVal_fPreDgnY = pElemChild->Attribute("value");
	if(pszVal_fPreDgnY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fPreDgnY, s.fPreDgnY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SExtPropStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExtPropStream");
	rElement.SetAttribute("type", ToUTF8Ptr("角色附加数据"));
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_dwDgnInstID(new TiXmlElement("UINT32"));
	if(pElem_dwDgnInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDgnInstID->SetAttribute("name", "dwDgnInstID");
	pElem_dwDgnInstID->SetAttribute("value", NumberToString(s.dwDgnInstID).c_str());
	pElem_dwDgnInstID->SetAttribute("comment", ToUTF8Ptr("副本实例ID"));
	if(rElement.LinkEndChild(pElem_dwDgnInstID.get()) != NULL)
		pElem_dwDgnInstID.release();
	unique_ptr<TiXmlElement> pElem_dwDgnCreateTime(new TiXmlElement("UINT32"));
	if(pElem_dwDgnCreateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDgnCreateTime->SetAttribute("name", "dwDgnCreateTime");
	pElem_dwDgnCreateTime->SetAttribute("value", NumberToString(s.dwDgnCreateTime).c_str());
	pElem_dwDgnCreateTime->SetAttribute("comment", ToUTF8Ptr("副本创建时间"));
	if(rElement.LinkEndChild(pElem_dwDgnCreateTime.get()) != NULL)
		pElem_dwDgnCreateTime.release();
	unique_ptr<TiXmlElement> pElem_wPreDgnMapID(new TiXmlElement("UINT16"));
	if(pElem_wPreDgnMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPreDgnMapID->SetAttribute("name", "wPreDgnMapID");
	pElem_wPreDgnMapID->SetAttribute("value", NumberToString(s.wPreDgnMapID).c_str());
	pElem_wPreDgnMapID->SetAttribute("comment", ToUTF8Ptr("进入副本之前的地图ID"));
	if(rElement.LinkEndChild(pElem_wPreDgnMapID.get()) != NULL)
		pElem_wPreDgnMapID.release();
	unique_ptr<TiXmlElement> pElem_fPreDgnX(new TiXmlElement("float"));
	if(pElem_fPreDgnX == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fPreDgnX->SetAttribute("name", "fPreDgnX");
	pElem_fPreDgnX->SetAttribute("value", NumberToString(s.fPreDgnX).c_str());
	pElem_fPreDgnX->SetAttribute("comment", ToUTF8Ptr("进入副本之前的X坐标"));
	if(rElement.LinkEndChild(pElem_fPreDgnX.get()) != NULL)
		pElem_fPreDgnX.release();
	unique_ptr<TiXmlElement> pElem_fPreDgnY(new TiXmlElement("float"));
	if(pElem_fPreDgnY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fPreDgnY->SetAttribute("name", "fPreDgnY");
	pElem_fPreDgnY->SetAttribute("value", NumberToString(s.fPreDgnY).c_str());
	pElem_fPreDgnY->SetAttribute("comment", ToUTF8Ptr("进入副本之前的Y坐标"));
	if(rElement.LinkEndChild(pElem_fPreDgnY.get()) != NULL)
		pElem_fPreDgnY.release();
	return true;
}

#endif

SSlotPropStream::SSlotPropStream() : dwRoleID(0), dwOwnerID(0), byStoreType(0), wSlotCount(0) { }

SSlotPropStream::SSlotPropStream(UINT64 dwRoleID_, UINT64 dwOwnerID_, UINT8 byStoreType_, UINT16 wSlotCount_) : dwRoleID(dwRoleID_), dwOwnerID(dwOwnerID_), byStoreType(byStoreType_), wSlotCount(wSlotCount_) { }

CInArchive& operator>>(CInArchive& src, SSlotPropStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRoleID;
	src >> s.dwOwnerID;
	src >> s.byStoreType;
	src >> s.wSlotCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSlotPropStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRoleID;
	src << s.dwOwnerID;
	src << s.byStoreType;
	src << s.wSlotCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSlotPropStream& s)
{
	if(strcmp(rElement.Value(), "SSlotPropStream") != 0)
	{
		LOG_CRI << "rElement is not SSlotPropStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRoleID!";
		return false;
	}
	const char* pszVal_dwRoleID = pElemChild->Attribute("value");
	if(pszVal_dwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRoleID, s.dwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOwnerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOwnerID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOwnerID!";
		return false;
	}
	const char* pszVal_dwOwnerID = pElemChild->Attribute("value");
	if(pszVal_dwOwnerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOwnerID, s.dwOwnerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStoreType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStoreType") != 0)
	{
		LOG_CRI << "Attribute: name is not byStoreType!";
		return false;
	}
	const char* pszVal_byStoreType = pElemChild->Attribute("value");
	if(pszVal_byStoreType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStoreType, s.byStoreType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSlotCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSlotCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wSlotCount!";
		return false;
	}
	const char* pszVal_wSlotCount = pElemChild->Attribute("value");
	if(pszVal_wSlotCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSlotCount, s.wSlotCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSlotPropStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSlotPropStream");
	rElement.SetAttribute("type", ToUTF8Ptr("各种槽（物品槽，心法槽）"));
	unique_ptr<TiXmlElement> pElem_dwRoleID(new TiXmlElement("UINT64"));
	if(pElem_dwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRoleID->SetAttribute("name", "dwRoleID");
	pElem_dwRoleID->SetAttribute("value", NumberToString(s.dwRoleID).c_str());
	pElem_dwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_dwRoleID.get()) != NULL)
		pElem_dwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_dwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOwnerID->SetAttribute("name", "dwOwnerID");
	pElem_dwOwnerID->SetAttribute("value", NumberToString(s.dwOwnerID).c_str());
	pElem_dwOwnerID->SetAttribute("comment", ToUTF8Ptr("拥有者实例ID"));
	if(rElement.LinkEndChild(pElem_dwOwnerID.get()) != NULL)
		pElem_dwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_byStoreType(new TiXmlElement("UINT8"));
	if(pElem_byStoreType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStoreType->SetAttribute("name", "byStoreType");
	pElem_byStoreType->SetAttribute("value", NumberToString(s.byStoreType).c_str());
	pElem_byStoreType->SetAttribute("comment", ToUTF8Ptr("槽类型"));
	if(rElement.LinkEndChild(pElem_byStoreType.get()) != NULL)
		pElem_byStoreType.release();
	unique_ptr<TiXmlElement> pElem_wSlotCount(new TiXmlElement("UINT16"));
	if(pElem_wSlotCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSlotCount->SetAttribute("name", "wSlotCount");
	pElem_wSlotCount->SetAttribute("value", NumberToString(s.wSlotCount).c_str());
	pElem_wSlotCount->SetAttribute("comment", ToUTF8Ptr("当前槽的数量"));
	if(rElement.LinkEndChild(pElem_wSlotCount.get()) != NULL)
		pElem_wSlotCount.release();
	return true;
}

#endif

} //namespace NDBData
