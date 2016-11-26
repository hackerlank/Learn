/**
	好友信息解析函数，信息解析基本操作；
	如果有疑问，请RTX xhm;
*/

#ifndef _FRIEND_ANALYZE_H
#define _FRIEND_ANALYZE_H
class Hero;
/**
	函数作用 申请好友信息解析；
	消息类型 13,0,myHeroId,friendHeroId;
*/
void analyzeFriendApply(char *buffers);					


/**
	函数作用 响应好友申请信息解析；
	消息类型 13,1,myHeroId,applyFriendHeroId;
*/
void analyzeResponseFriendApply(char *buffers);		


/**
	函数作用 好友列表操作信息解析；
	消息类型 13,2，type(1,删除 2，拉入黑名单),myHeroId,friendHeroId；
*/
void FriendlistOperate(char *buffers);	


/**
	函数作用 黑名单列表操作信息解析；
	消息类型 13,3，type(1，删除，2，移出黑名单),myHeroId,friendHeroId；
*/
void BlacklistOperate(char *buffers);				


/**
	函数作用 黑名单列表操作信息解析；
	消息类型 13,4，type;(1，好友信息 2，黑名单信息),myHeroId,friendHeroId；
*/
void viewFriendInfo(char *buffers);			

void findFriendInfo(char *buffers);

void findFriend(char *buffers);

bool asistOneKeyAppFriend(Hero* ownerHero,const char *applyHeroId);

void analyzeResponseFriendApplyOneKey(char *buffers);

bool ResponseApplyOneKeyAsist(Hero *ownerHero,const char *responseHeroId,const char *agreeFlag);

//一键申请好友
void analyzeFriendApplyByOneKey(char *buffers);

#endif
