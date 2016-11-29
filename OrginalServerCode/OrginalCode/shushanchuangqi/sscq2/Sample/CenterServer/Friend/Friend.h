
#ifndef FRIEND_H_
#define FRIEND_H_

#include "FriendProt.h"

using namespace NProtoCommon;
using namespace NFriendProt;

// forward declare
class CUser;

typedef std::map<UINT64, SFriendEntryPtr> TMapFriendEntry;

class CFriend
{
public:
	CFriend(CUser& rUser);

	// initialize
	void Init(const TVecFriendDBInfo& rVecTable);
	bool IsInitialized() const { return _bInitialized; }

	// user event
	static void OnUserLogout(CUser& rUser);
	static void OnUserLogin(CUser& rUser);

    // 
    void ChangeSign(const std::string& strSign);
    void ChangeMood(UINT16 wMood);
    void ChangeVIPLevel(UINT64 qwRoleID, UINT8 byVIPLevel);
    void ChangeVIPLevel(UINT8 byVIPLevel);

    void ChangeColor(UINT64 qwRoleID, UINT8 byColor);
    void ChangeColor(UINT8 byColor);

    void SyncLatestVIPLevel(UINT64 qwRoleID, SFriendEntryPtr pFriendEntry);

	// add
	void AddFriend(UINT64 qwID, UINT8 byNeedRet = 1);
	void AddFriend(const std::string& strName, UINT8 byNeedRet = 1);

	void AnswerAddFriend(bool bAgree, UINT64 qwUserID);
	// 添加黑名单
	void AddBlackList(UINT64 qwID);
	void AddBlackList(const std::string& strName);
	// remove
	void RemoveFriend(UINT64 qwUserID, bool bAddBlackList = false);
	// move
	EFriendResult MoveFriend(UINT64 qwUserID, EFriendGroupType eGroupType);
	// broadcast online status
	void BroadcastOnlineStatus(bool bOnlineStatus);
	// get map
	TMapFriendEntry& GetFriendEntryMap() { return _mapUserID2FriendEntry; }
	
	// get friend entry
	SFriendEntryPtr GetFriendEntry(UINT64 qwUserID) const;
	bool IsFriendEntry(UINT64 qwUserID) const;
	bool IsFriend(UINT64 qwUserID) const;
    bool IsBlackFriend(UINT64 qwUserID) const;

	bool FriendInfoNotify();
	void UserChangeNotify(const string& strMsg);
	//获得好友数量(非黑名单)
	UINT16 GetFriendNum();
    //VIP特权
    bool CheckAddFriendNum();

    void SyncUserVIPLevel(UINT8 byVIPLevel);
    void Update2DB(UINT64 qwUserID, SFriendEntry& rFriendEntry, EDataChange eDataChange);

private:
    void AddFriend(CUserPtr pUser, UINT8 byNeedRet = 1);

	enum
	{
		DEFAULT_GROUP_ID = 1,
		MAX_GROUP_ID = 6,
		MAX_FRIEND_NUM = 256,
	};

	CUser& _rUser;
	bool _bInitialized;
	TMapFriendEntry _mapUserID2FriendEntry;
};

#endif // FRIEND_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

