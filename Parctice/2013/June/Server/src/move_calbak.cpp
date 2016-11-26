#include"move_asist.h"
#include"hero.h"
#include"wagon.h"
#include"pet.h"
#include"takeGoods.h"
#include<iostream>
using namespace std;

static Point getCurrPt(Point &startPt, Point &endPt, unsigned speed, double t, double& remain)
{
	// cout<<"speed is "<<speed<<endl;
	if (t <= 0. || t > 0.5)
	{
		cout<<"[getCurrPt] Give a big error time!!!!!"<<endl;
		remain = 0.;
		return endPt;
	}
	if (startPt == endPt)
	{
		remain = t;
		return endPt;
	}
	
	int deltX = endPt._x - startPt._x;
	int deltY = endPt._y - startPt._y;
	double distance  = sqrt(deltX * deltX + deltY * deltY);
	//distance不会为0
	if (speed == 0)
	{
		cout<<"[hero_move_cb warn] give a error speed !"<<endl;
		remain = t;
		return startPt;
	}
	double totalTime = distance / speed;
	// cout<<"the corn need time is "<<totalTime<<endl;
	if (totalTime < t)
	{
		remain = t - totalTime;
		// cout<<"bison show first move dist is "<<distance<<endl; 
		return endPt;
	} else {
		double moveX = (t * deltX) / totalTime;
		double moveY = (t * deltY) / totalTime;
		//只有这里有一次取舍
		Point curPt(int(startPt._x + moveX), int(startPt._y + moveY));
		double dist = sqrt(moveX * moveX + moveY * moveY);
		// cout<<"bisosn ggggg dist is "<<dist<<endl;
		remain = 0.0;
		return curPt;
	}
}

static int correctThePoint(Point &curPt, Map_Inform* mapNow)
{
	if (mapNow->judgePiex(curPt))
	{
		return 0;
	} else {
		Point temp1(curPt._x + 1, curPt._y), temp2(curPt._x, curPt._y - 1),
			temp3(curPt._x - 1, curPt._y), temp4(curPt._x, curPt._y + 1);
		if (mapNow->judgePiex(temp1))
		{
			curPt = temp1;
			return 0;
		} else {
			if (mapNow->judgePiex(temp2))
			{
				curPt = temp2;
				return 0;
			} else {
				if (mapNow->judgePiex(temp3))
				{
					curPt = temp3;
					return 0;
				} else {
					if (mapNow->judgePiex(temp4))
					{
						curPt = temp4;
						return 0;
					} else {
						return 1;
					}
				}
			}
		}
	}
}

//revents == 0移动同步回调；revents == 1:强制终止移动；revents == 2:减速消息
void hero_move_cb(struct event_base *loop, ev_timer* think, int revents)
{
	double moveTime = 0.5;
	if (revents != 0)
	{
		moveTime = 0.5 - ev_timer_remaining(loops, think);
		ev_timer_stop(loops, think); 	//因为有可能强制调用
	}
	
	Hero *hero = (Hero*)think->target;
	if (hero == NULL)
	{
		cout<<"hero move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	
	if (!hero->getWalkingFlg())
	{
		ev_timer_start(loops, think);
	}
	Map_Inform *mapNow = hero->getMap();
	if(mapNow == NULL)
	{
		cout<<"in heroMove current mapInfor is NULL"<<endl;
		// exit(0);	
	}
	double remainTime = 0;
	char moveMsg[5120] = {0};
	char temp[4000] = {0};
	int realPtNum = 0;
	// struct timeval nowTv;
	// gettimeofday(&nowTv, NULL);
	// cout<<"[heroMove]sec is "<<nowTv.tv_sec<<" and usec is "<<nowTv.tv_usec<<endl;
	if (hero->keyPath.size() == 0 && hero->endPt == hero->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else if (hero->getLifeStation() == DEAD)	//如果死亡前的调用，请先调用再设置死亡
	{
		hero->keyPath.clear();
		hero->endPt = hero->currPt;
	}
	else 
	{
		//获取实时速度
		int speed = hero->getSpeed();
		if (revents == 2)
		{
			//速度变化了的，使用变化前速度计算当前位置
			speed = hero->getLastSpeed();
		}
		hero->currPt = getCurrPt(hero->currPt, hero->endPt, speed, moveTime, remainTime);
		
		while (hero->currPt == hero->endPt && hero->keyPath.size() > 0)
		{
			hero->endPt = hero->keyPath.front();
			hero->keyPath.pop_front();
			//像素点是否合法
			if (!mapNow->judgePiex(hero->endPt))
			{
				hero->keyPath.clear();
				hero->endPt = hero->currPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					hero->currPt = getCurrPt(hero->currPt, hero->endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(hero->currPt == hero->endPt) && !mapNow->judgePiex(hero->currPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(hero->currPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				hero->currPt = hero->endPt;
				hero->keyPath.clear();
			}
		}
		
		if (revents == 1)
		{
			//停止移动事件，强制清点
			hero->endPt = hero->currPt;
			hero->keyPath.clear();
		}
		
		if (revents == 2)
		{
			//如果是变速事件，发给客户端新速度，
			speed = hero->getSpeed();
		}
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"hero move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", hero->getIdentity(), hero->currPt._x, hero->currPt._y);
		if (hero->currPt == hero->endPt)
		{
			sprintf(temp, "%d,%d", hero->currPt._x, hero->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", hero->currPt._x, hero->currPt._y, hero->endPt._x, hero->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (hero->keyPath.size() > 0)
		{
			for (it_pt = hero->keyPath.begin(); it_pt != hero->keyPath.end(); it_pt++)
			{
				snprintf(temp + strlen(temp), sizeof (temp) - strlen(temp), ",%d,%d",
					(*it_pt)._x, (*it_pt)._y);
				realPtNum++;
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", hero->getIdentity(), realPtNum, temp, speed);
		StyObj obj(hero->getIdentity(), HERO_STYLE_TYPE);	
		if(mapNow->updateID(obj,hero->currPt))
		{		
			hero->setLocation(hero->currPt, 1);
			bool isNewRod = false;
			if (revents != 0 && revents != 1)
			{
				isNewRod = true;
			}
			box->heroPollTme(hero, moveMsg, isNewRod);	
		}
	}
	
	
	ev_timer_start(loops, think);
	
	
	Pet_Box* petBox = hero->getPetBox();
	if (petBox == NULL)
	{
		return;
	}
	cout << petBox->getActivePetIndex();
	Pet *pet = petBox->getActivePet();
		
	if (pet == NULL)
	{
		// cout<<"pet move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	
		// printf("%s\n", pet->getIdentity());
	if (!hero->getWalkingFlg())
	{
		ev_timer_start(loops, think);
		return;
	}
	
	remainTime = 0;
	memset(moveMsg, 0, sizeof moveMsg);
	memset(temp, 0, sizeof temp);
	realPtNum = 0;
	if (pet->getRouteSize() == 0 && pet->endPt == pet->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else 
	{
		//获取实时速度
		int speed = hero->getSpeed();
		
		int ownerSpeed = hero->getSpeed();
		if (speed < ownerSpeed)
		{
			speed = ownerSpeed;
		}
		
		pet->currPt = getCurrPt(pet->currPt, pet->endPt, speed, moveTime, remainTime);
		
		int whileFlag=0;
		while (pet->currPt == pet->endPt && pet->getRouteSize() > 0)
		{
			whileFlag++;
			if (whileFlag>1000)
			{
				break;
			}
			if (!pet->popOneRoutePt(pet->endPt))
			{
				cout<<"pet->getRouteSize is "<<pet->getRouteSize()<<endl;
				break;
			}
			
			//像素点是否合法
			if (!mapNow->judgePiex(pet->endPt))
			{
				pet->routeClear();
				pet->endPt = pet->currPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					pet->currPt = getCurrPt(pet->currPt, pet->endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(pet->currPt == pet->endPt) && !mapNow->judgePiex(pet->currPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(pet->currPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				pet->currPt = pet->endPt;
				pet->routeClear();
			}
		}
		
		if (revents == 1)
		{
			//停止移动事件，强制清点
			pet->endPt = pet->currPt;
			pet->routeClear();
		}
		
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"pet move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", hero->getIdentity(), hero->currPt._x, hero->currPt._y);
		if (pet->currPt == pet->endPt)
		{
			sprintf(temp, "%d,%d", pet->currPt._x, pet->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", pet->currPt._x, pet->currPt._y, pet->endPt._x, pet->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (pet->getRouteSize() > 0)
		{
			realPtNum += pet->getRouteSize();
			pet->viewRouteMsg(temp);
		}
		printf("%s\n", pet->getIdentity());
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", pet->getIdentity(), realPtNum, temp, speed);
		StyObj obj(pet->getIdentity(), PET_STYLE_TYPE);	
		if(mapNow->updateID(obj, pet->currPt))
		{		
			pet->setNowPix(pet->currPt, 1);
			bool isNewRod = false;
			if (revents != 0)
			{
				isNewRod = true;
			}
			box->petMove(pet, moveMsg, isNewRod, NULL);	
		}
	}
	
}


//revents == 0.5移动同步回调；revents == 1:强制终止移动；
void wagon_move_cb(struct event_base *loop, ev_timer* think, int revents)
{
	double moveTime = 0.5;
	if (revents != 0)
	{
		moveTime = 0.5 - ev_timer_remaining(loops, think);
		ev_timer_stop(loops, think); 	//因为有可能强制调用
	}
	
	Wagon *wagon = (Wagon*)think->target;
	if (wagon == NULL)
	{
		cout<<"wagon move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	
	Hero *owner = wagon->getOwner();
	if (owner == NULL || !owner->getWalkingFlg())
	{
		ev_timer_start(loops, think);
		return;
	}
	
	Map_Inform *mapNow = wagon->getMap();
	double remainTime = 0;
	char moveMsg[4000] = {0};
	char temp[4000] = {0};
	int realPtNum = 0;
	if (wagon->getRouteSize() == 0 && wagon->endPt == wagon->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else 
	{
		//获取实时速度
		int speed = wagon->getSpeed();
		if (revents == 2)
		{
			speed = wagon->getLastSpeed();
		}
		wagon->currPt = getCurrPt(wagon->currPt, wagon->endPt, speed, moveTime, remainTime);
		
		while (wagon->currPt == wagon->endPt && wagon->getRouteSize() > 0)
		{
			wagon->popOneRoutePt(wagon->endPt);
			//像素点是否合法
			if (!mapNow->judgePiex(wagon->endPt))
			{
				wagon->routeClear();
				wagon->endPt = wagon->currPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					wagon->currPt = getCurrPt(wagon->currPt, wagon->endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(wagon->currPt == wagon->endPt) && !mapNow->judgePiex(wagon->currPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(wagon->currPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				wagon->currPt = wagon->endPt;
				wagon->routeClear();
			}
		}
		
		if (revents == 1)
		{
			//停止移动事件，强制清点
			wagon->endPt = wagon->currPt;
			wagon->routeClear();
		}
		
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"wagon move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", hero->getIdentity(), hero->currPt._x, hero->currPt._y);
		if (wagon->currPt == wagon->endPt)
		{
			sprintf(temp, "%d,%d", wagon->currPt._x, wagon->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", wagon->currPt._x, wagon->currPt._y, wagon->endPt._x, wagon->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (wagon->getRouteSize() > 0)
		{
			wagon->viewRouteMsg(temp + strlen(temp));
			realPtNum += wagon->getRouteSize();
		}
		
		if (revents == 2)
		{
			speed = wagon->getSpeed();
		}
		
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", wagon->getIdentity(), realPtNum, temp, speed);
		StyObj obj(wagon->getIdentity(), WAGON_STYLE_TYPE);	
		if(mapNow->updateID(obj, wagon->currPt))
		{		
			wagon->setLocation(wagon->currPt, 1);
			bool isNewRod = false;
			if (revents != 0)
			{
				isNewRod = true;
			}
			box->wagonMove(wagon, moveMsg, isNewRod, NULL);	
		}
	}
	ev_timer_start(loops, think);
	
}



//revents == 0.5移动同步回调；revents == 1:强制终止移动；
void pet_move_cb(struct event_base *loop, ev_timer* think, int revents)
{
	// ev_timer_stop(loop,think);
	double moveTime = 0.5;
	if (revents != 0)
	{
		moveTime = 0.5 - ev_timer_remaining(loops, think);
		ev_timer_stop(loops, think); 	//因为有可能强制调用
	}
	
	Pet *pet = (Pet*)think->target;
	if (pet == NULL)
	{
		cout<<"wagon move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	if (pet->getActive() != 1)
	{
		return;
	}
	char *ownerId = pet->getMasterId();
	if (strlen(ownerId) <= 30)
	{
		pet->petDownLine();
		return;
	}
	Hero *owner = heroid_to_hero(ownerId);
	if (owner == NULL)
	{
		pet->petDownLine();
		return;
	}
	if (!owner->getWalkingFlg())
	{
		ev_timer_start(loops, think);
		return;
	}
	Map_Inform *mapNow = owner->getMap();
	if (mapNow == NULL)
	{
		ev_timer_start(loops, think);
		return;
	}

	double remainTime = 0;
	char moveMsg[4000] = {0};
	char temp[4000] = {0};
	int realPtNum = 0;
	if (pet->getRouteSize() == 0 && pet->endPt == pet->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else 
	{
		//获取实时速度
		int speed = pet->speed;
		int ownerSpeed = owner->getSpeed();
		if (speed < ownerSpeed)
		{
			speed = ownerSpeed;
		}
		pet->currPt = getCurrPt(pet->currPt, pet->endPt, speed, moveTime, remainTime);
		
		while (pet->currPt == pet->endPt && pet->getRouteSize() > 0)
		{
			pet->popOneRoutePt(pet->endPt);
			
			//像素点是否合法
			if (!mapNow->judgePiex(pet->endPt))
			{
				pet->routeClear();
				pet->endPt = pet->currPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					pet->currPt = getCurrPt(pet->currPt, pet->endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(pet->currPt == pet->endPt) && !mapNow->judgePiex(pet->currPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(pet->currPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				pet->currPt = pet->endPt;
				pet->routeClear();
			}
		}
		
		if (revents == 1)
		{
			//停止移动事件，强制清点
			pet->endPt = pet->currPt;
			pet->routeClear();
		}
		
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"pet move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", hero->getIdentity(), hero->currPt._x, hero->currPt._y);
		if (pet->currPt == pet->endPt)
		{
			sprintf(temp, "%d,%d", pet->currPt._x, pet->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", pet->currPt._x, pet->currPt._y, pet->endPt._x, pet->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (pet->getRouteSize() > 0)
		{
			realPtNum += pet->getRouteSize();
			pet->viewRouteMsg(temp + strlen(temp));
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", pet->getIdentity(), realPtNum, temp, speed);
		StyObj obj(pet->getIdentity(), PET_STYLE_TYPE);	
		if(mapNow->updateID(obj, pet->currPt))
		{		
			pet->setNowPix(pet->currPt, 1);
			bool isNewRod = false;
			if (revents != 0)
			{
				isNewRod = true;
			}
			box->petMove(pet, moveMsg, isNewRod, NULL);	
		}
	}
	ev_timer_start(loops, think);
	
}

//revents == 0移动同步回调；revents == 1:强制终止移动；revents == 2:减速消息
void mon_move_cb(struct event_base *loop, ev_timer* think, int revents)
{
	double moveTime = 0.5;
	if (revents != 0)
	{
		double timer_remaining = ev_timer_remaining(loops, think);
		moveTime = 0.5 - timer_remaining;
		// cout<<"moveTime is "<<moveTime<<" when mon stop! and timer_remaing is "<<timer_remaining<<endl;
		ev_timer_stop(loops, think); 	//因为有可能强制调用
		// if (moveTime < 0.08)
		// {
			// ev_timer_start(loops, think);
			// return;
		// }
		if (moveTime < 0.0)
		{
			moveTime = 0.0;
		}
		
	}
	MonsterBase *mon = (MonsterBase*)think->target;
	if (mon == NULL)
	{
		cout<<"mon move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	struct timeval nowTv;
	gettimeofday(&nowTv, NULL);
	// cout<<"Mon think move and kePath.size is  "<<mon->keyPath.size()<<" curPt("<<mon->currPt._x<<","<<mon->currPt._y<<") and endPt("<<mon->endPt._x<<","<<mon->endPt._y<<")!"<<endl;
	// cout<<"nowLogicPt._x "<<mon->getLogicPt()._x<<" and nowLogicPt._y "<<mon->getLogicPt()._y<<endl;
	// cout<<"monster move keyPath size is "<<mon->keyPath.size()<<endl;
	Map_Inform *mapNow = mon->getMap();
	double remainTime = 0;
	char moveMsg[MONSTER_ROAD_LENGTH + 1] = {0};
	char temp[MONSTER_ROAD_LENGTH + 1] = {0};
	int realPtNum = 0;

	//获取实时速度
	int speed = mon->getSpeed();
	if (mon->keyPath.size() == 0 && mon->endPt == mon->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else if (!mon->getLifeStation())	//如果死亡前的调用，请先调用再设置死亡
	{
		mon->keyPath.clear();
		mon->endPt = mon->currPt;
	}
	else 
	{
		if (mon->keyPath.size() != 0 && mon->endPt == mon->currPt && revents == 3)
		{
			// cout<<"need stop move!!!!!!!!!!!!!!!!"<<endl;
			mon->endPt = mon->keyPath.front();
			mon->keyPath.pop_front();
		} else {
			if (revents == 2)
			{
				//速度变化了的，使用变化前速度计算当前位置
				speed = mon->getLastSpeed();
			}
			mon->currPt = getCurrPt(mon->currPt, mon->endPt, speed, moveTime, remainTime);
			
			while (mon->currPt == mon->endPt && mon->keyPath.size() > 0)
			{
				mon->endPt = mon->keyPath.front();
				mon->keyPath.pop_front();
				//像素点是否合法
				if (!mapNow->judgePiex(mon->endPt))
				{
					cout<<"mon move s end pt is not logic"<<endl;
					mon->keyPath.clear();
					mon->endPt = mon->currPt;
					remainTime = 0;
					break;
				}
				else {
					if (remainTime > 0.0 && remainTime <= 0.5)
					{
						mon->currPt = getCurrPt(mon->currPt, mon->endPt, speed, remainTime, remainTime);
					}
				}
				
			}
			
			if (!(mon->currPt == mon->endPt) && !mapNow->judgePiex(mon->currPt))
			{
				//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
				if (correctThePoint(mon->currPt, mapNow) != 0)
				{
					//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
					cout<<"correct point is still not ok!!!"<<endl;
					mon->currPt = mon->endPt;
					mon->keyPath.clear();
				}
			}
			
			if (revents == 1)
			{
				//停止移动事件，强制清点
				// cout<<"stop move's clear()"<<endl;
				mon->endPt = mon->currPt;
				mon->keyPath.clear();
			}
			
			if (revents == 2)
			{
				//如果是变速事件，发给客户端新速度，
				speed = mon->getSpeed();
			}
		}	
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"mon move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", mon->getIdentity(), mon->currPt._x, mon->currPt._y);
		if (mon->currPt == mon->endPt)
		{
			sprintf(temp, "%d,%d", mon->currPt._x, mon->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", mon->currPt._x, mon->currPt._y, mon->endPt._x, mon->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (mon->keyPath.size() > 0)
		{
			for (it_pt = mon->keyPath.begin(); it_pt != mon->keyPath.end(); it_pt++)
			{
				snprintf(temp + strlen(temp), sizeof (temp) - strlen(temp), ",%d,%d",
					(*it_pt)._x, (*it_pt)._y);
				realPtNum++;
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", mon->getIdentity(), realPtNum, temp, speed);
		StyObj obj(mon->getIdentity(), MONSTER_STYLE_TYPE);	
		if(mapNow->updateID(obj, mon->currPt))
		{		
			mon->setLocation(mon->currPt, 1);
			bool isNewRod = false;
			if (revents != 0)
			{
				isNewRod = true;
			} 
			box->monsterMove(mon,moveMsg, isNewRod);	
		}
	}
	// printf("MonMove: Point(%d,%d), endPt(%d,%d) keyPath size %d\n", mon->currPt._x, mon->currPt._y, mon->endPt._x, mon->endPt._y, mon->keyPath.size());
	// ext_ev_timer_init(think, mon_move_cb, 0.5, 0, mon);
	ev_timer_start(loops, think);
	
}




//revents == 0移动同步回调；revents == 1:强制终止移动；revents == 2:减速消息
void takeGoods_move_cb(struct event_base *loop, ev_timer* think, int revents)
{
	double moveTime = 0.5;
	if (revents != 0)
	{
		double timer_remaining = ev_timer_remaining(loops, think);
		moveTime = 0.5 - timer_remaining;
		// cout<<"moveTime is "<<moveTime<<" when mon stop! and timer_remaing is "<<timer_remaining<<endl;
		ev_timer_stop(loops, think); 	//因为有可能强制调用
		// if (moveTime < 0.08)
		// {
			// ev_timer_start(loops, think);
			// return;
		// }
		if (moveTime < 0.0)
		{
			moveTime = 0.0;
		}
		
	}
	
	TakeGoods *takeGoods = (TakeGoods*)think->target;
	if (takeGoods == NULL)
	{
		cout<<"takeGoods move timer is accident closed !!!!!!!!!!!!!"<<endl;
		// exit(0);
		return;
	}
	struct timeval nowTv;
	gettimeofday(&nowTv, NULL);

	Map_Inform *mapNow = takeGoods->getMap();
	double remainTime = 0;
	char moveMsg[4000] = {0};
	char temp[4000] = {0};
	int realPtNum = 0;

	//获取实时速度
	int speed = takeGoods->getSpeed();
	if (takeGoods->keyPath.size() == 0 && takeGoods->endPt == takeGoods->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else 
	{
		if (takeGoods->keyPath.size() != 0 && takeGoods->endPt ==\
		takeGoods->currPt && revents == 3)
		{
			// cout<<"need stop move!!!!!!!!!!!!!!!!"<<endl;
			takeGoods->endPt = takeGoods->keyPath.front();
			takeGoods->keyPath.pop_front();
		} 
		else
		{
			if (revents == 2)
			{
				//速度变化了的，使用变化前速度计算当前位置
				speed = takeGoods->getLastSpeed();
			}
			takeGoods->currPt = getCurrPt(takeGoods->currPt, takeGoods->endPt, speed, moveTime, remainTime);
			
			while (takeGoods->currPt == takeGoods->endPt && takeGoods->keyPath.size() > 0)
			{
				takeGoods->endPt = takeGoods->keyPath.front();
				takeGoods->keyPath.pop_front();
				//像素点是否合法
				if (!mapNow->judgePiex(takeGoods->endPt))
				{
					cout<<"takeGoods move s end pt is not logic"<<endl;
					takeGoods->keyPath.clear();
					takeGoods->endPt = takeGoods->currPt;
					remainTime = 0;
					break;
				}
				else {
					if (remainTime > 0.0 && remainTime <= 0.5)
					{
						takeGoods->currPt = getCurrPt(takeGoods->currPt, takeGoods->endPt, speed, remainTime, remainTime);
					}
				}
				
			}
			
			if (!(takeGoods->currPt == takeGoods->endPt) && !mapNow->judgePiex(takeGoods->currPt))
			{
				//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
				if (correctThePoint(takeGoods->currPt, mapNow) != 0)
				{
					//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
					cout<<"correct point is still not ok!!!"<<endl;
					takeGoods->currPt = takeGoods->endPt;
					takeGoods->keyPath.clear();
				}
			}
			
			if (revents == 1)
			{
				//停止移动事件，强制清点
				cout<<"stop takeGoods's clear()"<<endl;
				takeGoods->endPt = takeGoods->currPt;
				takeGoods->keyPath.clear();
			}
			
			if (revents == 2)
			{
				//如果是变速事件，发给客户端新速度，
				speed = takeGoods->getSpeed();
			}
		}	
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"takeGoods move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		// sprintf(moveMsg, "2,1,%s,%d,%d", mon->getIdentity(), mon->currPt._x, mon->currPt._y);
		if (takeGoods->currPt == takeGoods->endPt)
		{
			sprintf(temp, "%d,%d", takeGoods->currPt._x, takeGoods->currPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", takeGoods->currPt._x, takeGoods->currPt._y, takeGoods->endPt._x, takeGoods->endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (takeGoods->keyPath.size() > 0)
		{
			for (it_pt = takeGoods->keyPath.begin(); it_pt != takeGoods->keyPath.end(); it_pt++)
			{
				snprintf(temp + strlen(temp), sizeof (temp) - strlen(temp), ",%d,%d",
					(*it_pt)._x, (*it_pt)._y);
				realPtNum++;
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d",takeGoods->getId(),realPtNum,temp,speed);
		StyObj obj(takeGoods->getId(), TAKEGOODS_STYLE_TYPE);	
		if(mapNow->updateID(obj, takeGoods->currPt))
		{		
			takeGoods->setLocation(takeGoods->currPt, 1);
			bool isNewRod = false;
			if (revents != 0)
			{
				isNewRod = true;
			} 
			box->takeGoodsMove(takeGoods,moveMsg, isNewRod);	
		}
	}
	ev_timer_start(loops, think);	
}



//看到九宫格内他人移动
void view_other_hero_move(Hero* witness, Hero* moveHero)
{
	ev_timer *think = &moveHero->moveTimer;
	double moveTime = 0.5 - ev_timer_remaining(loops, think);
	
	if (!moveHero->getWalkingFlg())
	{
		return;
	}
	Map_Inform *mapNow = moveHero->getMap();
	if(mapNow == NULL)
	{
		cout<<"in heroMove current mapInfor is NULL"<<endl;
		return;
		// exit(0);	
	}
	
	Point curPt = moveHero->currPt, endPt = moveHero->endPt;
	list<Point> keyPath = moveHero->keyPath;
	
	double remainTime = 0;
	char moveMsg[4000] = {0};
	char temp[4000] = {0};
	int realPtNum = 0;
	// struct timeval nowTv;
	// gettimeofday(&nowTv, NULL);
	// cout<<"[heroMove]sec is "<<nowTv.tv_sec<<" and usec is "<<nowTv.tv_usec<<endl;
	if (keyPath.size() == 0 && endPt == curPt)
	{
		return;
	}
	else if (moveHero->getLifeStation() == DEAD)	//如果死亡前的调用，请先调用再设置死亡
	{
		keyPath.clear();
		endPt =curPt;
		return;
	}
	else 
	{
		//获取实时速度
		int speed = moveHero->getSpeed();
		
		curPt = getCurrPt(curPt, endPt, speed, moveTime, remainTime);
		
		while (curPt == endPt && keyPath.size() > 0)
		{
			endPt = keyPath.front();
			keyPath.pop_front();
			//像素点是否合法
			if (!mapNow->judgePiex(endPt))
			{
				keyPath.clear();
				endPt = curPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					curPt = getCurrPt(curPt, endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(curPt == endPt) && !mapNow->judgePiex(curPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(curPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				curPt = endPt;
				keyPath.clear();
			}
		}
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"hero move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		
		if (curPt == endPt)
		{
			sprintf(temp, "%d,%d", curPt._x, curPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", curPt._x, curPt._y, endPt._x, endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (keyPath.size() > 0)
		{
			for (it_pt = keyPath.begin(); it_pt != keyPath.end(); it_pt++)
			{
				snprintf(temp + strlen(temp), sizeof (temp) - strlen(temp), ",%d,%d",
					(*it_pt)._x, (*it_pt)._y);
				realPtNum++;
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", moveHero->getIdentity(), realPtNum, temp, speed);
		send_msg(witness->getFd(), moveMsg);
		// StyObj obj(moveHero->getIdentity(), HERO_STYLE_TYPE);	
		// if(mapNow->updateID(obj, moveHero->currPt))
		// {		
			// hero->setLocation(hero->currPt, 1);
			// bool isNewRod = false;
			// if (revents != 0 && revents != 1)
			// {
				// isNewRod = true;
			// }
			// box->heroPollTme(hero, moveMsg, isNewRod);	
		// }
	}
	// printf("HeroMove: time(%d,%d) Point(%d,%d)\n", nowTv.tv_sec, nowTv.tv_usec, hero->currPt._x, hero->currPt._y);
	// ev_timer_start(loops, think);
	
}


//revents == 0移动同步回调；revents == 1:强制终止移动；revents == 2:减速消息
void view_mon_move(Hero* witness, MonsterBase *mon)
{
	if (witness == NULL || mon == NULL)
	{
		return;
	}
	
	ev_timer *think = &mon->moveTimer;
	
	double  moveTime = 0.5 - ev_timer_remaining(loops, think);
	
	if (moveTime < 0.0)
	{
		moveTime = 0.0;
	}

	// struct timeval nowTv;
	// gettimeofday(&nowTv, NULL);
	// cout<<"Mon think move and kePath.size is  "<<mon->keyPath.size()<<" curPt("<<mon->currPt._x<<","<<mon->currPt._y<<") and endPt("<<mon->endPt._x<<","<<mon->endPt._y<<")!"<<endl;
	// cout<<"nowLogicPt._x "<<mon->getLogicPt()._x<<" and nowLogicPt._y "<<mon->getLogicPt()._y<<endl;
	// cout<<"monster move keyPath size is "<<mon->keyPath.size()<<endl;
	Map_Inform *mapNow = mon->getMap();
	double remainTime = 0;
	char moveMsg[MONSTER_ROAD_LENGTH + 1] = {0};
	char temp[MONSTER_ROAD_LENGTH + 1] = {0};
	int realPtNum = 0;
	Point curPt = mon->currPt, endPt = mon->endPt;
	list<Point> keyPath = mon->keyPath;
	
	//获取实时速度
	int speed = mon->getSpeed();
	if (mon->keyPath.size() == 0 && mon->endPt == mon->currPt)
	{
		// ev_timer_start(loops, &moveTimer);
	}
	else if (!mon->getLifeStation())	//如果死亡前的调用，请先调用再设置死亡
	{
		keyPath.clear();
		endPt = curPt;
	}
	else 
	{
		curPt = getCurrPt(curPt, endPt, speed, moveTime, remainTime);
		
		while (curPt == endPt && keyPath.size() > 0)
		{
			endPt = keyPath.front();
			keyPath.pop_front();
			//像素点是否合法
			if (!mapNow->judgePiex(endPt))
			{
				keyPath.clear();
				endPt = curPt;
				remainTime = 0;
				break;
			}
			else {
				if (remainTime > 0.0 && remainTime <= 0.5)
				{
					curPt = getCurrPt(curPt, endPt, speed, remainTime, remainTime);
				}
			}
			
		}
		
		if (!(curPt == endPt) && !mapNow->judgePiex(curPt))
		{
			//如果当前点非法，对当前点进行纠正，这种情况概率估计不足1/(64*32*speed*2*2)
			if (correctThePoint(curPt, mapNow) != 0)
			{
				//纠正都没纠正成功，那就切到当前段终点停下来，这种情况概率估计为0
				curPt = endPt;
				keyPath.clear();
			}
		}
		
		Nbox *box=mapNow->getBox();   
		if(box == NULL)
		{
			cout<<"hero move close exit for no map Box !!!!!!!!!!!!!!"<<endl;
			// exit(0);
			return;
		}
		
		if (curPt == endPt)
		{
			sprintf(temp, "%d,%d", curPt._x, curPt._y);
			realPtNum = 1;
		} else {
			sprintf(temp, "%d,%d,%d,%d", curPt._x, curPt._y, endPt._x, endPt._y);
			realPtNum = 2;
		}
		list<Point>::iterator it_pt;
		if (keyPath.size() > 0)
		{
			for (it_pt = keyPath.begin(); it_pt != keyPath.end(); it_pt++)
			{
				snprintf(temp + strlen(temp), sizeof (temp) - strlen(temp), ",%d,%d",
					(*it_pt)._x, (*it_pt)._y);
				realPtNum++;
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", mon->getIdentity(), realPtNum, temp, speed);
		send_msg(witness->getFd(), moveMsg);
	}
	
}

