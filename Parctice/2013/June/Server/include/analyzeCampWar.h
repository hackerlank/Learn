#ifndef ANALYZE_CAMP_WAR_H
#define ANALYZE_CAMP_WAR_H

#include <string>

/*apply enter to the camp war*/
void applyCampWar(char* buffers);

/*enter the camp war*/
void enterCampWar(char* buffers);

/*exit the camp war*/
void exitCampWar(char* buffers); 

/*apply exit from the camp war*/
void delFromCampWar(char* buffers);

/*getCampWarCouts*/
void getCampWarCounts(char* buffers);

/*view camp war awards 11,4,HeroId*/
void viewCampWarAwards(char* buffers);

/*receive the awards,11,5,HeroId,Type*/
void receiveWarAwards(char* buffers);

/*receive the awards,11,6,HeroId,Type*/ //申请阵营战；

/* hero revival , 11,8 heroId,type*/
void heroCampWarRevival(char* buffers);

/*当前还有多少时间**/
void heroCampWarLevalTime(char* buffers);

//进入阵营边境地图；
void applyCampSence(char* buffers);

//退出阵营边境地图；
void exitCampSence(char* buffers);

//查看阵营对应帮派数据；
void viewCampFactionInfo(char* buffers);

//请求查看阵营数据；
void viewCampInfo(char* buffers);

//设置阵营公告；
void setCampBroadcast(char*buffers);

//任命副统领；
void setCampViceLeader(char*buffers);

//获取报名列表；
void getLeaderCampWarAppInfo(char*buffers);

//统领战报名剩余时间；
void getLeaderWarAppLastTime(char*buffers);

//查看阵营资源战房间信息
void viewCampResWarInforComm(char *buffer);

//进阵营战房间
void entCampResWarComm(char* buffer);

//退出阵营战房间
void exitCampResWarComm(char* buffer);

void campResWarViewHeroResNumComm(char* buffer);

void getCampResWarComm(char* buffer);

#endif