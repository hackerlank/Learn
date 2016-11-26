#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"

//骑马准备
int Hero::prepareRide()
{
	//正在骑马状态
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		prepareRideSecond = 0;
		return 2;
	}
	
	if (ride == NULL)
	{
		//宠物栏错误
		return 3;
	}
	
	if (ride->ifFull()==false)
	{
		//没有出战骑宠
		return 4;	
	}
	
	if (heroState==5)
	{
		//摆摊中
		return 6;
	}
	
	//已经正在骑马状态
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		//已经准备过，重新准备一次
		prepareRideSecond = MY_TV_SEC;
		memHero->rideState = RIDE_STATE_PREPARE;
		return 1;
	}
	
	//未骑马状态
	if (memHero->rideState == RIDE_STATE_FREE)
	{	
		//准备骑乘成功
		prepareRideSecond = MY_TV_SEC;
		memHero->rideState = RIDE_STATE_PREPARE;
		return 0;
	}
	
	//先前的骑乘状态有误,进行纠正
	prepareRideSecond = MY_TV_SEC;
	memHero->rideState = RIDE_STATE_PREPARE;
	return 0;
}

//打断乘骑过程
int Hero::breakRide()
{
	if (memHero->rideState == RIDE_STATE_FREE)
	{
		prepareRideSecond = 0;
		return 0;
	}
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		prepareRideSecond = 0;
		memHero->rideState = RIDE_STATE_FREE;
		return 0;
	}
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		return 1;
	}
	return 2;
}

//开始骑乘
int Hero::startRide()
{
	if (memHero->rideState == RIDE_STATE_RIDING)
	{
		prepareRideSecond = 0;
		return 2;
	}
	
	if (ride == NULL)
	{
		//宠物栏错误
		return 3;
	}
	
	if (ride->ifFull() == false)
	{
		//没有出战骑宠
		return 4;	
	}
	
	if (memHero->rideState == RIDE_STATE_FREE)
	{
		//前面没有乘骑准备
		prepareRideSecond = 0;
		return 6;
	}
	
	if (memHero->rideState == RIDE_STATE_PREPARE)
	{
		//看骑乘准备时间是否足够
		if (MY_TV_SEC - prepareRideSecond >= RIDE_PREPARE_TIME)
		{
			prepareRideSecond = 0;
			memHero->rideState = RIDE_STATE_RIDING;
			// lastSpeed = speed;
			
			if (strlen(memHero->wagonId) != 0)
			{
				speed = NORMAL_WAGON_SPEED;
			} else {
				// speed = NORMAL_HERO_SPEED + ride->getActiveMove();
				speed = NORMAL_HERO_SPEED + ride->getMove();
			}
			hero_move_cb(loops, &moveTimer, 2);
			setLastSpeed(getSpeed());
			return 0;
		} else {
			//骑乘准备时间未到
			return 7;
		}
	}
	//骑乘状态有错
	memHero->rideState = RIDE_STATE_FREE;
	return 8;
}

//下马
int Hero::stopRide()
{
	if (memHero->rideState != RIDE_STATE_RIDING)
	{
		return 1;
	}
	else if (strlen(memHero->wagonId) != 0)
	{
		speed = NORMAL_WAGON_SPEED;
	} else {
		speed = NORMAL_HERO_SPEED;
	}
	memHero->rideState = RIDE_STATE_FREE;
	hero_move_cb(loops, &moveTimer, 2);
	setLastSpeed(getSpeed());
	return 0;
}

//获取骑乘状态
int Hero::getRideState()
{
	return memHero->rideState;
}
