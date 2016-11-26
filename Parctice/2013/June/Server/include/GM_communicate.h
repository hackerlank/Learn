#ifndef GM_COMMUNICATE_H
#define GM_COMMUNICATE_H
#include "hero.h"
#include "GM.h"
#include"cpyLimit.h"
#include "systemMessage.h"

void GM_goods(char *buffer);
void GM_pet_exp(char *buffer);
void GM_money(char *buffer);
void GM_hero_exp(char *buffer);
void GM_ban_speak(char *buffer);
void GM_deliver(char *buffer);
void GM_broadcast(char *buffer);
void GM_viewInform(char *buffer);
void GM_freezeMoney(char *buffer);
void GM_lockHero(char *buffer);
void GM_stealth(char *buffer);
void GM_invincible(char *buffer);
void GM_kick(char *buffer);
void GM_inform(char *buffer);
void GM_see_heroNum(char *buffer);
void returnGlobalSize(void);
void GM_whisper(char *buffer);
void GM_bugCommit(char *buffer);
void GM_advertise(char *buffer);

#endif