#include<string>
#include<hero.h>
using namespace std;

//开始经脉修炼
int startMeridStudy(Hero *hero, int index, char* result);
//使用道具加快修炼
int useMeridGoods(Hero *hero, char* goodsId, int index, int num, char* result);
//取消修炼
bool cancelMeridStudy(Hero *hero);
//经脉强化
int strenMerid(Hero *hero, char* result);
//从memcache上来数据后重启经脉
void restartMeridStudy(Hero *hero);
//玩家离线时停止经脉定时器
void stopMeridianTimer(char* heroId);

//获取八个经脉的总等级，该死的向慧明要的这个接口
int getTotalLevel(Hero *hero);

//花元宝减少经脉修炼时间
int decMeridTimeWithGold(Hero *hero, int flag, char *result);
