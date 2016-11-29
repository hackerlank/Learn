#pragma once

#include "ChatProt.h"

using namespace NGlobalChatProt;
using namespace NChatProt;

// forward declare
class CUser;

class CChat
{
public:
	// chat
	static void Chat(
		CUser& rUser, 
		EChannelType eChannelType,
		const std::string& strInfo,
        const TVecShowInfo& vecShowInfo //炫耀物品信息
		);

	static void SystemChat(
		UINT64 qwID,
		EChannelType eChannelType,
		const std::string& strInfo,
		EChannelSubType eSubType
		);
	static void DebugInfo(
		UINT64 qwID,
		const std::string& strInfo
		);
};
