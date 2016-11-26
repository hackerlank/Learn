#include"hero.h"
#include"hero_fight.h"
#include"time_limit_events.h"

void fire_shuai_pao_comm(char* buffer)
{
	char *targetHeroId;						//炮竹作用的玩家
	char *paozhuId;							//炮竹ID
	int index;								//炮竹在背包中的下标
	int ret = 0;
	char retMsg[4096] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(targetHeroId);
	MSG_CHAR(paozhuId);
	MSG_INT(index);
	
	Hero *targetHero = heroid_to_hero(targetHeroId);
	
	if (targetHero == NULL)
	{
		ret = 1;
	}
	
	if (strcmp(paozhuId, "f_cl_135_100") != 0 && strcmp(paozhuId, "b_cl_135_100") != 0)
	{
		ret = 2;
	}
	
	Point toPt = targetHero->getLocation();
	Point fromPt = pg_hero->getLocation();
	if (GET_DISTANCE(fromPt, toPt) > 250)
	{
		ret = 4;
	}
	
	if (useBagGoods(pg_hero, paozhuId, index, 1))
	{
		ret = 3;
	}
	
	if (ret != 0)
	{
		sprintf(retMsg, "29,0,%d", ret);
		send_msg(pg_hero->getFd(), retMsg);
	} else {
		
		pg_hero->addPrestigeValue(goodsReturnInt(paozhuId,1));//增加声望值；
		// pg_hero->addFriendLevel(1);//增加魅力值；//added xhm;
		
		// if(pg_hero->getFriendInfo())
			// (pg_hero->getFriendInfo())->addFriendDeg(targetHeroId,FLOWERS_ADD_FRIEND_DGR,1);	//亲密度
		
		sprintf(retMsg, "26,2,1,W001,1,%s,%d,%d,%d,%d,%d,%d,%d,1,%s,%d,%d,%d,%d,%d,%d",
		pg_hero->getIdentity(), pg_hero->getLifeVal(), pg_hero->getLifeUpperVal(),
		pg_hero->getMagicVal(), pg_hero->getMagicUpperVal(), 0, 0, 0, targetHeroId,
		(targetHero->getLifeVal() - 1), targetHero->getLifeUpperVal(), targetHero->getMagicVal(),
		targetHero->getMagicUpperVal(), 1, 0);
		//角色的血减少1
		proc_hero_lose_life(pg_hero, targetHero, 1);
		// targetHero->setLifeVal(targetHero->getLifeVal() - 1);
		send_nine_msg(pg_hero, retMsg);
	}
}

void fire_yan_hua_comm(char* buffer)
{
	char *yanhuaId;							//炮竹ID
	int index;								//炮竹在背包中的下标
	int ret = 0;
	char retMsg[4096] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(yanhuaId);
	MSG_INT(index);
	
	if (strcmp(yanhuaId, "f_cl_137_100") != 0 && strcmp(yanhuaId, "b_cl_137_100") != 0)
	{
		ret = 1;
	}
	
	if (useBagGoods(pg_hero, yanhuaId, index, 1))
	{
		ret = 2;
	}
	
	if (ret != 0)
	{
		sprintf(retMsg, "29,0,%d", ret);
		send_msg(pg_hero->getFd(), retMsg);
	} else {
		
		pg_hero->addPrestigeValue(goodsReturnInt(yanhuaId,1));//增加声望值；
		// pg_hero->addFriendLevel(1);//增加魅力值；//added xhm;
		
		// if(pg_hero->getFriendInfo())
			// (pg_hero->getFriendInfo())->addFriendDeg(targetHeroId,FLOWERS_ADD_FRIEND_DGR,1);	//亲密度
		char skillId[64] = "W00";
		sprintf(skillId + strlen(skillId), "%d", rand() % 3 + 2);
		sprintf(retMsg, "26,2,1,%s,1,%s,%d,%d,%d,%d,%d,%d,%d,0", skillId,
		pg_hero->getIdentity(), pg_hero->getLifeVal(), pg_hero->getLifeUpperVal(),
		pg_hero->getMagicVal(), pg_hero->getMagicUpperVal(), 0, 0, 0);
		
		send_nine_msg(pg_hero, retMsg);
	}
}
