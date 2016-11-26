#ifndef TEAM_OPERATOR_H
#define TEAM_OPERATOR_H


//请求自己是否已创建队伍
void acceptTeamState(char *buffer);

//请求别人是否已创建队伍
void acceptOtherHeroTeamState(char *buffer);

//邀请别人“组队”
void inviteHeroJoinTeam(char *buffer);

//请求"组队"回应
void responseInviteHeroJoinTeam(char *buffer);

//退出
void offTeam(char *buffer);

//解散
void disMissTeam(char *buffer);

//转让
void transferTeamLeader(char *buffer);

//转让回应
void transferTeamLeaderResponse(char *buffer);

//踢人
void kickOutTeam(char *buffer);

//申请入队
void applyForInTeam(char *buffer);

//同意申请入队
void agreeApplyForInTeam(char *buffer);

#endif