/********************************************************************
//	TaskLoad Library Source File.
//	File name:	TaskConf.cpp
//	Created:	2011/09/12	15:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
*********************************************************************/

#include <fstream>
#include "tinyxml.h"
#include "TaskConf.h"
#include "TaskConfMgr.h"
#include "String2Value.h"

#ifdef _DEBUG
#include <iostream>
#define TRACE(msg) \
	do { std::cout << "[" << __FUNCTION__ << ":" << __LINE__ << "]<TaskID:" << wID << "> " << msg << std::endl; \
	CTaskConfMgr::Instance().GetLogStream() << "[" << __FUNCTION__ << ":" << __LINE__ << "]<TaskID:" << wID << "> " << msg << std::endl; } while(false)
#else
#define TRACE(msg)
#endif

using namespace std;

//一般奖励， 用于存放xml中的对应字段名
static const char* award_general_fields[] =
{	"gold", 
	"wood", 
	"iron", 
	"magic", 
	"diamond", 
	"ticket", 
	"playerExp", 
	"petExp", 
	"mercenaryExp" };

/*
std::wstring ToWString(UINT32 dwCodePage, const std::string& str)
{
	int iLen = MultiByteToWideChar(dwCodePage, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pText = new wchar_t[iLen];
	MultiByteToWideChar(dwCodePage, 0, str.c_str(), -1, pText, iLen);
	std::wstring wstr = pText;
	delete[] pText;
	return wstr;
}

std::string ToString(UINT32 dwCodePage, const std::wstring& wstr)
{
	int iLen = WideCharToMultiByte(dwCodePage, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	char* pText = new char[iLen];
	WideCharToMultiByte(dwCodePage, 0, wstr.c_str(), -1, pText, iLen, NULL, NULL);
	std::string str = pText;
	delete[] pText;
	return str;
}

string GetString(const char* pszValue, bool bUtf8Coding)
{
	if(bUtf8Coding)
	{
		wstring wstr = ToWString(CP_UTF8, pszValue);
		return ToString(CP_ACP, wstr);
	}
	return pszValue;
}
*/


template<typename T>
bool GetValueFromAttr(const TiXmlElement *elem, const char *name, T &value)
{
	assert(elem != NULL && name != NULL);
	const char *text = elem->Attribute(name);
	if(NULL == text)
		return false;

	return GetValueFromString(text, value);
}

/**
*	just to expose the interface StringEqual.
*/
class MyXMLDeclaration: public TiXmlDeclaration
{
public:
	static bool IsStringEqual(const char* p,
		const char* endTag,
		bool ignoreCase,
		TiXmlEncoding encoding)
	{
		return StringEqual(p, endTag, ignoreCase, encoding);
	}
};

/**
*	get the encoding of the xml.
*/
TiXmlEncoding GetXMLEncoding(const TiXmlDocument &doc)
{
	const TiXmlDeclaration *decl = doc.FirstChild()->ToDeclaration();
	if(decl != NULL)
	{
		const char* enc = decl->Encoding();
		assert( enc );

		if ( *enc == 0 ||  
			MyXMLDeclaration::IsStringEqual( enc, "UTF-8", true, TIXML_ENCODING_UNKNOWN ) || 
			MyXMLDeclaration::IsStringEqual( enc, "UTF8", true, TIXML_ENCODING_UNKNOWN ))
		{
			return TIXML_ENCODING_UTF8;
		}

	}

	return TIXML_ENCODING_UNKNOWN;
}

bool STaskConfig::ParseXML(const string& strFilePath)
{
	if(strFilePath.empty())
	{
		TRACE("strFilePath is empty!");
		return false;
	}

	TiXmlDocument doc(strFilePath.c_str());
	if(!doc.LoadFile())
	{
		TRACE(strFilePath);
		return false;
	}

	//bool bUtf8Coding = (TIXML_ENCODING_UTF8 == GetXMLEncoding(doc)) ? true : false;

	TiXmlElement* pElemRoot = doc.RootElement();
	if(pElemRoot == NULL)
	{
		TRACE("pElemRoot is NULL!");
		return false;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//基本信息
	TiXmlElement* pElemProperty = pElemRoot->FirstChildElement("Property");
	if(pElemProperty == NULL)
	{
		TRACE("pElemProperty is NULL!");
		return false;
	}
	else
	{
		if(!GetValueFromAttr(pElemProperty, "type", (int &)eTaskType))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}

		if(!GetValueFromAttr(pElemProperty, "content", (int &)dwContentType))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}
	}

	TiXmlElement* pElemBasic = pElemProperty->FirstChildElement("Basic");
	if(pElemBasic == NULL)
	{
		return false;
	}
	else
	{
		if(!GetValueFromAttr(pElemBasic, "id", wID))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}

		if(!GetValueFromAttr(pElemBasic, "name", strName))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}

		if(!GetValueFromAttr(pElemBasic, "level", byLevel))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}
	}

	TiXmlElement* pElemMark = pElemProperty->FirstChildElement("Mark");
	if(pElemMark == NULL)
	{
		TRACE("pElemMark is NULL!");
		return false;
	}
	else
	{
		if(!GetValueFromAttr(pElemMark, "open", bOpen) ||
			!GetValueFromAttr(pElemMark, "share", bShare) ||
			!GetValueFromAttr(pElemMark, "repeat", dwRepeat) ||
			!GetValueFromAttr(pElemMark, "giveUp", bCanGiveUp) ||
			!GetValueFromAttr(pElemMark, "linklevel", bAwardLinkLevel) ||
			!GetValueFromAttr(pElemMark, "typeExtent", (int &)eTaskTypeExtent) ||
			!GetValueFromAttr(pElemMark, "Charge", dwCharge))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}
		GetValueFromAttr(pElemMark, "guidetype", dwGuideType);
	}

	TiXmlElement* pElemStar = pElemProperty->FirstChildElement("Star");
	if(pElemStar != NULL)
	{
		if(!GetValueFromAttr(pElemStar, "id", dwStarGroupID) ||
			!GetValueFromAttr(pElemStar, "level", (int &)eStarType))
		{
			TRACE("GetValueFromAttr fails!");
			return false;
		}
	}

	TiXmlElement* pElemTrigger = pElemProperty->FirstChildElement("Trigger");
	if(pElemTrigger == NULL)
	{
		TRACE("pElemTrigger is NULL!");
		return false;
	}
	else
	{
		TiXmlElement* pElemTarget = pElemTrigger->FirstChildElement("Target");
		if(pElemTarget != NULL)
		{
			//SIdxType oIdxType;

			if(!GetValueFromAttr(pElemTarget, "id", oTriggerTarget.dwIdx) ||
				!GetValueFromAttr(pElemTarget, "type", (int &)oTriggerTarget.eType))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}

			//vecTriggerTarget.push_back(oIdxType);
			//pElemTarget = pElemTarget->NextSiblingElement("Target");
		}
	}

/*
	TiXmlElement* pElemSubmit = pElemProperty->FirstChildElement("Submit");
	if(pElemSubmit == NULL)
	{
		return false;
	}
	else
	{
		TiXmlElement* pElemTarget = pElemSubmit->FirstChildElement("Target");
		while(pElemTarget != NULL)
		{
			SIdxType oIdxType;

			if(!GetValueFromAttr(pElemTarget, "id", oIdxType.dwIdx) ||
				!GetValueFromAttr(pElemTarget, "type", (int &)oIdxType.eType))
			{
				return false;
			}

			vecSubmitTarget.push_back(oIdxType);
			pElemTarget = pElemTarget->NextSiblingElement("Target");
		}
	}
*/

	//任务描述
	TiXmlElement* pElemDialog = pElemRoot->FirstChildElement("Dialog");
	if(pElemDialog == NULL)
	{
		TRACE("pElemDialog is NULL!");
		return false;
	}
	else
	{
		TiXmlElement* pElemDesc = pElemDialog->FirstChildElement("Desc");
		if(pElemDesc != NULL)
		{
			//strTaskDesc = GetString(pElemDesc->GetText(), bUtf8Coding);
			const char* pszText = pElemDesc->GetText();
			if(pszText != NULL)
				strTaskDesc = pszText;
		}

		TiXmlElement* pElemPurpose = pElemDialog->FirstChildElement("Purpose");
		if(pElemPurpose != NULL)
		{
			//strTaskPurpose = GetString(pElemPurpose->GetText(), bUtf8Coding);
			const char* pszText = pElemPurpose->GetText();
			if(pszText != NULL)
				strTaskPurpose = pszText;
		}

		TiXmlElement* pElemFail = pElemDialog->FirstChildElement("Fail");
		if(pElemFail != NULL)
		{
			//strTaskFail = GetString(pElemFail->GetText(), bUtf8Coding);
			const char* pszText = pElemFail->GetText();
			if(pszText != NULL)
				strTaskFail = pszText;
		}

		TiXmlElement* pElemFinish = pElemDialog->FirstChildElement("Finish");
		if(pElemFinish != NULL)
		{
			//strTaskFinish = GetString(pElemFinish->GetText(), bUtf8Coding);
			const char* pszText = pElemFinish->GetText();
			if(pszText != NULL)
				strTaskFinish = pszText;
		}
	}

	//任务限制
	TiXmlElement *pElementLimit = pElemRoot->FirstChildElement("Limit");
	if(NULL == pElementLimit)
	{
		TRACE("pElementLimit is NULL!");
		return false;
	}
	else
	{
		const TiXmlElement *elem = pElementLimit->FirstChildElement("Gender");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "value", (int &)eLimitGender))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}
		//区域触发器
		elem = pElementLimit->FirstChildElement("Area");
		if(elem != NULL)
		{
			const TiXmlElement* pElemMap = elem->FirstChildElement("Map");
			while(pElemMap != NULL)
			{
				SMapArea oMapArea;
				if(!GetValueFromAttr(pElemMap, "id", oMapArea.wMapID) ||
					!GetValueFromAttr(pElemMap, "x1", oMapArea.fX1) ||
					!GetValueFromAttr(pElemMap, "z1", oMapArea.fZ1) ||
					!GetValueFromAttr(pElemMap, "x2", oMapArea.fX2) ||
					!GetValueFromAttr(pElemMap, "z2", oMapArea.fZ2))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecTrigger.push_back(oMapArea);
				pElemMap = pElemMap->NextSiblingElement("Map");
			}
		}
		//属性限制
		elem = pElementLimit->FirstChildElement("Property");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Item");
			SLimitProp obj;
			while(child != NULL)
			{
				if(!GetValueFromAttr(child, "type", (int &)obj.eLimitType) ||
					!GetValueFromAttr(child, "value", obj.wValue))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				if(eLimtPropRepute == obj.eLimitType)
				{
					if(!GetValueFromAttr(child, "campID", wLimitCampID))
					{
						TRACE("GetValueFromAttr fails!");
						return false;
					}
				}

				vecLimitProp.push_back(obj);
				child = child->NextSiblingElement("Item");
			}
		}

		/*elem = pElementLimit->FirstChildElement("Repute");
		if(elem != NULL)
		{
		if(!GetValueFromAttr(elem, "Min", wLimitReputeMin) ||
		!GetValueFromAttr(elem, "Max", wLimitReputeMax))
		{
		return false;
		}
		}*/

		/*elem = pElementLimit->FirstChildElement("JingJie");
		if(elem != NULL)
		{
		if(!GetValueFromAttr(elem, "Min", wLimitJingJieMin) ||
		!GetValueFromAttr(elem, "Max", wLimitJingJieMax))
		{
		return false;
		}
		}*/

		elem = pElementLimit->FirstChildElement("Camp");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "value", (int &)eLimitCamp))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}

		elem = pElementLimit->FirstChildElement("Family");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "value", (int &)eLimitFamily))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}

		elem = pElementLimit->FirstChildElement("Race");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "value", byRace))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}

		elem = pElementLimit->FirstChildElement("Date");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "From", qwLimitDateFrom) ||
				!GetValueFromAttr(elem, "To", qwLimitDateTo))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}

		elem = pElementLimit->FirstChildElement("DayTime");
		if(elem != NULL)
		{
			if(!GetValueFromAttr(elem, "From", wLimitDayTimeFrom) ||
				!GetValueFromAttr(elem, "To", wLimitDayTimeTo))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
		}

		//前置任务
		elem = pElementLimit->FirstChildElement("PreTask");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Item");
			while(child != NULL)
			{
				UINT16 wTaskID;
				if(!GetValueFromAttr(child, "id", wTaskID))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecLimitPreTasks.push_back(wTaskID);
				child = child->NextSiblingElement("Item");
			}

			if(!vecLimitPreTasks.empty())
			{
				if(!GetValueFromAttr(elem, "flag", byLimitPreTaskFlag))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}
			}
		}

		//职业
		elem = pElementLimit->FirstChildElement("Career");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Item");
			while(child != NULL)
			{
				UINT32 id;
				if(!GetValueFromAttr(child, "id", id))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecLimitCareers.push_back(id);
				child = child->NextSiblingElement("Item");
			}
		}
	}

	//任务过程
	TiXmlElement* pElemProcess = pElemRoot->FirstChildElement("Process");
	if(pElemProcess == NULL)
	{
		TRACE("pElemProcess is NULL!");
		return false;
	}
	else
	{
		TiXmlElement* pElemGeneral = pElemProcess->FirstChildElement("General");
		if(pElemGeneral != NULL)
		{
			GetValueFromAttr(pElemGeneral, "time", dwLimitTime);

			TiXmlElement* pElemItem = pElemGeneral->FirstChildElement("Item");
			while(pElemItem != NULL)
			{
				SIdxCount oIdxCount;
				if(!GetValueFromAttr(pElemItem, "id", oIdxCount.dwIdx) ||
					!GetValueFromAttr(pElemItem, "count", oIdxCount.wCount))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}
				vecItemGive.push_back(oIdxCount);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}
		
		TiXmlElement* pElemKill = pElemProcess->FirstChildElement("Kill");
		if(pElemKill != NULL)
		{
			TiXmlElement* pElemMonster = pElemKill->FirstChildElement("Monster");
			while(pElemMonster != NULL)
			{
				const char* pID = pElemMonster->Attribute("id");
				if(pID == NULL)
				{
					TRACE("pID is NULL!");
					return false;
				}
				const char* pCount = pElemMonster->Attribute("count");
				if(pCount == NULL)
				{
					TRACE("pID is NULL!");
					return false;
				}
				const char* pFake = pElemMonster->Attribute("fake");
				SKillMonster oKillMonster;
				oKillMonster.wMonsterID = (UINT16)atoi(pID);
				oKillMonster.wCount = (UINT16)atoi(pCount);
				if(pFake != NULL && strlen(pFake) > 0)
					oKillMonster.bFake = true;
				vecMonsterKill.push_back(oKillMonster);
				pElemMonster = pElemMonster->NextSiblingElement("Monster");
			}
		}
			
		TiXmlElement* pElemCollect = pElemProcess->FirstChildElement("Collect");
		if(pElemCollect != NULL)
		{
			TiXmlElement* pElemItem = pElemCollect->FirstChildElement("Item");
			while(pElemItem != NULL)
			{
				const char* pID = pElemItem->Attribute("id");
				if(pID == NULL)
				{
					TRACE("pID is NULL!");
					return false;
				}
				const char* pCount = pElemItem->Attribute("count");
				SCollectItem oCollectItem;
				oCollectItem.wItemID = (UINT16)atoi(pID);
				oCollectItem.wCount = (UINT16)atoi(pCount);
				vecItemCollect.push_back(oCollectItem);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}

		TiXmlElement* pElemKillCollect = pElemProcess->FirstChildElement("KillCollect");
		if(pElemKillCollect != NULL)
		{
			TiXmlElement* pElemItem = pElemKillCollect->FirstChildElement("Item");
			while(pElemItem != NULL)
			{
				const char* pMonsterID = pElemItem->Attribute("monsterid");
				if(pMonsterID == NULL)
				{
					TRACE("pMonsterID is NULL!");
					return false;
				}
				const char* pItemID = pElemItem->Attribute("itemid");
				if(pItemID == NULL)
				{
					TRACE("pItemID is NULL!");
					return false;
				}
				const char* pCount = pElemItem->Attribute("count");
				SCollectItem oCollectItem;
				oCollectItem.wMonsterID = (UINT16)atoi(pMonsterID);
				oCollectItem.wItemID = (UINT16)atoi(pItemID);
				oCollectItem.wCount = (UINT16)atoi(pCount);
				vecItemCollect.push_back(oCollectItem);
				pElemItem = pElemItem->NextSiblingElement("KillItem");
			}
		}

		TiXmlElement* pElemProbe = pElemProcess->FirstChildElement("Probe");
		if(pElemProbe != NULL)
		{
			if (!GetValueFromAttr(pElemProbe, "flag", byProbeFlag))
			{
				TRACE("GetValueFromAttr fails!");
				return false;
			}
			TiXmlElement* pElemMap = pElemProbe->FirstChildElement("Map");
			while(pElemMap != NULL)
			{
				SMapArea oMapArea;
				if(!GetValueFromAttr(pElemMap, "id", oMapArea.wMapID) ||
					!GetValueFromAttr(pElemMap, "x1", oMapArea.fX1) ||
					!GetValueFromAttr(pElemMap, "z1", oMapArea.fZ1) ||
					!GetValueFromAttr(pElemMap, "x2", oMapArea.fX2) ||
					!GetValueFromAttr(pElemMap, "z2", oMapArea.fZ2))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecProbe.push_back(oMapArea);
				pElemMap = pElemMap->NextSiblingElement("Map");
			}
		}

		if(dwGuideType == 2 && vecProbe.empty())
		{
			TRACE("GuideType:2 has no probe!");
#ifdef _DEBUG
			return false;
#endif
		}

/*
		TiXmlElement* pElemUseItem = pElemProcess->FirstChildElement("UseItem");
		if(pElemUseItem != NULL)
		{
			TiXmlElement* pElemItem = pElemUseItem->FirstChildElement("Item");
			while(pElemItem != NULL)
			{
				const char* pID = pElemItem->Attribute("id");
				if(pID == NULL)
					return false;
				SUseItem oUseItem;
				oUseItem.wItemID = atoi(pID);
				const char* pMapID = pElemItem->Attribute("mapid");
				if(pMapID != NULL)
				{
					const char* pX1 = pElemItem->Attribute("x1");
					if(pX1 == NULL)
						return false;
					const char* pZ1 = pElemItem->Attribute("z1");
					if(pX1 == NULL)
						return false;
					const char* pX2 = pElemItem->Attribute("x2");
					if(pX1 == NULL)
						return false;
					const char* pZ2 = pElemItem->Attribute("z2");
					if(pX1 == NULL)
						return false;
					SMapArea* pMapArea = new SMapArea;
					if(pMapArea == NULL)
						return false;
					pMapArea->wMapID = atoi(pMapID);
					pMapArea->fX1 = (float)atoi(pX1);
					pMapArea->fZ1 = (float)atoi(pZ1);
					pMapArea->fX2 = (float)atoi(pX2);
					pMapArea->fZ2 = (float)atoi(pZ2);
					oUseItem.pMapArea = pMapArea;
				}
				
				vecUseItem.push_back(oUseItem);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}

		TiXmlElement* pElemUseSkill = pElemProcess->FirstChildElement("UseSkill");
		if(pElemUseSkill != NULL)
		{
			TiXmlElement* pElemSkill = pElemUseSkill->FirstChildElement("Skill");
			while(pElemSkill != NULL)
			{
				const char* pID = pElemSkill->Attribute("id");
				if(pID == NULL)
					return false;
				SUseSkill oUseSkill;
				oUseSkill.dwSkillID = atoi(pID);
				const char* pMapID = pElemSkill->Attribute("mapid");
				if(pMapID != NULL)
				{
					const char* pX1 = pElemSkill->Attribute("x1");
					if(pX1 == NULL)
						return false;
					const char* pZ1 = pElemSkill->Attribute("z1");
					if(pX1 == NULL)
						return false;
					const char* pX2 = pElemSkill->Attribute("x2");
					if(pX1 == NULL)
						return false;
					const char* pZ2 = pElemSkill->Attribute("z2");
					if(pX1 == NULL)
						return false;
					SMapArea* pMapArea = new SMapArea;
					if(pMapArea == NULL)
						return false;
					pMapArea->wMapID = atoi(pMapID);
					pMapArea->fX1 = (float)atoi(pX1);
					pMapArea->fZ1 = (float)atoi(pZ1);
					pMapArea->fX2 = (float)atoi(pX2);
					pMapArea->fZ2 = (float)atoi(pZ2);
					oUseSkill.pMapArea = pMapArea;
				}

				vecUseSkill.push_back(oUseSkill);
				pElemSkill = pElemSkill->NextSiblingElement("Skill");
			}
		}
*/
		
		TiXmlElement* pElemGatherList = pElemProcess->FirstChildElement("GatherList");
		if(pElemGatherList != NULL)
		{
			TiXmlElement* pElemGather = pElemGatherList->FirstChildElement("Gather");
			while(pElemGather != NULL)
			{
				const char* pID = pElemGather->Attribute("id");
				if(pID == NULL)
				{
					TRACE("pID is NULL!");
					return false;
				}
				const char* pCount = pElemGather->Attribute("count");
				if(pCount == NULL)
				{
					TRACE("pCount is NULL!");
					return false;
				}
				SIdxCount oIdxCount;
				oIdxCount.dwIdx = atoi(pID);
				oIdxCount.wCount = (UINT16)atoi(pCount);
				vecGather.push_back(oIdxCount);
				pElemGather = pElemGather->NextSiblingElement("Gather");
			}
		}


		TiXmlElement* pElemTalk = pElemProcess->FirstChildElement("Talk");
		if(pElemTalk != NULL)
		{
			TiXmlElement* pElemNPC = pElemTalk->FirstChildElement("NPC");
			while(pElemNPC != NULL)
			{
				UINT16 wNpcID;
				if(!GetValueFromAttr(pElemNPC, "id", wNpcID))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				SNpcTalk &rNpcTalk = mapNpc2Talk[wNpcID];
				
				TiXmlElement* pElemChat = pElemNPC->FirstChildElement("Chat");
				while(pElemChat != NULL)
				{
					SChat oChat;
					const char* pIndex = pElemChat->Attribute("index");
					if(pIndex == NULL)
					{
						TRACE("pIndex is NULL!");
						return false;
					}
					TiXmlElement* pElemPCSpeak = pElemChat->FirstChildElement("PCSpeak");
					if(pElemPCSpeak != NULL)
					{
						//oChat.strPC = GetString(pElemPCSpeak->GetText(), bUtf8Coding);
						const char* pszText = pElemPCSpeak->GetText();
						if(pszText != NULL)
							oChat.strPC = pszText;
					}
					TiXmlElement* pElemNPCSpeak = pElemChat->FirstChildElement("NPCSpeak");
					if(pElemNPCSpeak != NULL)
					{
						//oChat.strNPC = GetString(pElemNPCSpeak->GetText(), bUtf8Coding);
						const char* pszText = pElemNPCSpeak->GetText();
						if(pszText != NULL)
							oChat.strNPC = pszText;
					}
					rNpcTalk.vecChat.push_back(oChat);
					pElemChat = pElemChat->NextSiblingElement("Chat");
				}

				//道具
				const TiXmlElement *pElemItem = pElemNPC->FirstChildElement("Item");
				while(pElemItem != NULL)
				{
					UINT16 wItemId;
					UINT16 wCount;
					if(!GetValueFromAttr(pElemItem, "id", wItemId) ||
						!GetValueFromAttr(pElemItem, "value", wCount))
					{
						TRACE("GetValueFromAttr fails!");
						return false;
					}

					rNpcTalk.mapItem2Count.insert(std::make_pair(wItemId, wCount));
					pElemItem = pElemItem->NextSiblingElement("Item");
				}

				//mapNpc2Talk.insert(std::make_pair(wNpcID, npcTalk));
				pElemNPC = pElemNPC->NextSiblingElement("NPC");
			}
		}

		//成长
		const TiXmlElement *elem = pElemProcess->FirstChildElement("Grow");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Item");
			while(child != NULL)
			{
				SRoleProperty obj;
				if(!GetValueFromAttr(child, "type", (int &)obj.type) ||
					!GetValueFromAttr(child, "value", obj.value))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				if(eProcessRoleProperty_repute == obj.type)
				{
					if(!GetValueFromAttr(child, "extID", obj.dwExtID))
					{
						TRACE("GetValueFromAttr fails!");
						return false;
					}
				}

				vecRoleProps.push_back(obj);
				child = child->NextSiblingElement("Item");
			}
		}

		//行为
		elem = pElemProcess->FirstChildElement("Behave");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Item");
			while(child != NULL)
			{
				SProcessAction obj;
				if(!GetValueFromAttr(child, "type", (int &)obj.type) ||
					!GetValueFromAttr(child, "value", obj.value) ||
                  !GetValueFromAttr(child, "param", obj.param)  )
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecRoleActions.push_back(obj);
				child = child->NextSiblingElement("Item");
			}
		}

		//建设_建筑
		elem = pElemProcess->FirstChildElement("Build");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Building");
			while(child != NULL)
			{
				SIdxCount obj;
				if(!GetValueFromAttr(child, "id", obj.dwIdx) ||
					!GetValueFromAttr(child, "value", obj.wCount))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecBuildings.push_back(obj);
				child = child->NextSiblingElement("Building");
			}
		}

		//建设_科技
		elem = pElemProcess->FirstChildElement("Build");
		if(elem != NULL)
		{
			const TiXmlElement *child = elem->FirstChildElement("Technic");
			while(child != NULL)
			{
				SIdxCount obj;
				if(!GetValueFromAttr(child, "id", obj.dwIdx) ||
					!GetValueFromAttr(child, "value", obj.wCount))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecTechnics.push_back(obj);
				child = child->NextSiblingElement("Technic");
			}
		}

	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//任务奖励

	TiXmlElement* pElemAward = pElemRoot->FirstChildElement("Award");
	if(pElemAward != NULL)
	{
		TiXmlElement* pElemGeneral = pElemAward->FirstChildElement("General");
		if(pElemGeneral != NULL)
		{
			const TiXmlElement *child = pElemGeneral->FirstChildElement("Item");
			while(child != NULL)
			{
				SAwardGeneral obj;
				if(!GetValueFromAttr(child, "type", (UINT32 &)obj.type) ||
					!GetValueFromAttr(child, "value", obj.value))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecAwardGeneral.push_back(obj);
				child = child->NextSiblingElement("Item");
			}
		}

		TiXmlElement* pElemCoef = pElemAward->FirstChildElement("Coef");
		if(pElemCoef != NULL)
		{
			const char* pStar = pElemCoef->Attribute("star");
			if(pStar != NULL)
				fStarCoef = (float)atof(pStar);
			const char* pRing = pElemCoef->Attribute("ring");
			if(pRing != NULL)
				fRingCoef = (float)atof(pRing);
		}

		TiXmlElement* pElemMustItem = pElemAward->FirstChildElement("MustItem");
		if(pElemMustItem != NULL)
		{
			TiXmlElement* pElemItem = pElemMustItem->FirstChildElement("Item");
			while(pElemItem != NULL)
			{
				SIdxCountJob oIdxCount;
				const char* pID = pElemItem->Attribute("id");
				if(pID == NULL)
				{
					TRACE("pID is NULL!");
					return false;
				}
				oIdxCount.dwIdx = atoi(pID);

				const char* pCount = pElemItem->Attribute("count");
				if(pCount == NULL)
				{
					TRACE("pCount is NULL!");
					return false;
				}
				oIdxCount.wCount = (UINT16)atoi(pCount);
				const char* pJob = pElemItem->Attribute("job");
				if(pJob == NULL)
				{
					TRACE("pJob is NULL!");
					return false;
				}
				oIdxCount.byJob = (UINT8)atoi(pJob);
				vecMustAwardItem.push_back(oIdxCount);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}

		//称号奖励
		TiXmlElement* pElemTitle = pElemAward->FirstChildElement("Title");
		if(pElemTitle != NULL)
		{
			TiXmlElement* pElemItem = pElemTitle->FirstChildElement("Item");
			UINT32 dwID = 0;
			while(pElemItem != NULL)
			{
				if(!GetValueFromAttr(pElemItem, "id", dwID))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecAwardTitle.push_back(dwID);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}

		//属性奖励
		TiXmlElement* pElemProperty = pElemAward->FirstChildElement("Property");
		if(pElemProperty != NULL)
		{
			TiXmlElement* pElemItem = pElemProperty->FirstChildElement("Item");
			SAwardProperty oAwardProperty;
			while(pElemItem != NULL)
			{
				if(!GetValueFromAttr(pElemItem, "type", (int&)oAwardProperty.type) ||
					!GetValueFromAttr(pElemItem, "value", oAwardProperty.value))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				if(eAwardProperty_repute == oAwardProperty.type)
				{
					if(!GetValueFromAttr(pElemItem, "campID", wAwardPropCampID) ||
						!GetValueFromAttr(pElemItem, "campName", strAwardPropCampName))
					{
						TRACE("GetValueFromAttr fails!");
						return false;
					}
				}

				vecAwardProp.push_back(oAwardProperty);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}

		//佣兵奖励
		TiXmlElement* pElemMercen = pElemAward->FirstChildElement("Mercen");
		if(pElemMercen != NULL)
		{
			TiXmlElement* pElemItem = pElemMercen->FirstChildElement("Item");
			SAwardMercen oAwardMercen;
			while(pElemItem != NULL)
			{
				if(!GetValueFromAttr(pElemItem, "monster", oAwardMercen.wMonsterID) ||
					!GetValueFromAttr(pElemItem, "name", oAwardMercen.wNameID) ||
					!GetValueFromAttr(pElemItem, "pos", oAwardMercen.byPos))
				{
					TRACE("GetValueFromAttr fails!");
					return false;
				}

				vecAwardMercen.push_back(oAwardMercen);
				pElemItem = pElemItem->NextSiblingElement("Item");
			}
		}
	}
	return true;
}
