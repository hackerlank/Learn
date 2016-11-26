#ifndef _MY_TIME_H_
#define _MY_TIME_H_

#include<sys/time.h>
#include"libev.h"
#include"time.h"

extern ev_timer *myTimer;
extern struct timeval myTime;
extern struct ev_loop *loops;
extern int mySecond;				//秒
extern int myMin;					//分
extern int myHour;					//时			
extern int myWeekDay;				//周几

#define MY_WEEK_DAY	myWeekDay
#define MY_HOUR		myHour
#define MY_MIN		myMin
#define MY_TIME		myTime
#define MY_TV_SEC	myTime.tv_sec
#define MY_TV_USEC	myTime.tv_usec

void initMyTimer(void);
void initMyTime(void);
timeval getMyTime(void);
int getMySecond(void);
bool isSameDayWithNow(int second);
bool isNextDayWithNow(int second);

//获取娱乐剩余时间
unsigned getHappyRemain();
extern bool isInHappyTime;							//是否在娱乐时间
extern bool isInFirstRoomHappyTime;					//是否在天下第一楼的娱乐时间
extern bool isInSecondRoomHappyTime;				//是否在天上人间的娱乐时间
#endif
