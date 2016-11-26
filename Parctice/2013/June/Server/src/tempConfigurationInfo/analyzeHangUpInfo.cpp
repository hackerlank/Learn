#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
#include "wholeDefine.h"
extern Hero* pg_hero;
extern int g_msg_len;
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//设置角色对应挂机数据；
void setHangUpInfo(char* buffers)
{
	int flag;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(char* hero_id)
	MSG_INT(flag)
	MSG_CHAR_END(char* hangUpData)

	Hero *hero = pg_hero;

	if(!hero){
                return;
        }
	 if(!hero->memHero){
                return;
        }

	memset(hero->memHero->hangUpdata,'\0',sizeof(hero->memHero->hangUpdata));
	memcpy(hero->memHero->hangUpdata,hangUpData,sizeof(hero->memHero->hangUpdata)-1);
	
	sprintf(g_out_buf,"21,0,%d,%d,%s",0,flag,hangUpData);    
	send_msg(sock_fd,g_out_buf);    	
}


//获取角色对应挂机数据； updated by benliao
void getHangUpInfo(char* buffers)
{
	Hero* hero=pg_hero;
	if(!hero){
		return;
	}
	if(!hero->getMoney()){
		return;
	}

	if(!hero->memHero){
		return;
	}
	
	snprintf(g_out_buf,sizeof(g_out_buf),"21,1,0,0,%s",hero->memHero->hangUpdata);  	
	send_msg(sock_fd,g_out_buf);
}

void getGoldInfo(char* buffers)
{
	Hero* hero=pg_hero;
	if(!hero){
                return;
        }
	if(!hero->memHero){
                return;
        }

	sprintf(g_out_buf,"21,9,%d",0,hero->getMoney()->money_getBoundGold(),hero->getMoney()->money_getGold());
	send_msg(hero->getFd(),g_out_buf);		
}
