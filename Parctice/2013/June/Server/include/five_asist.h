#include"five_elements.h"
#include"hero.h"

//玩家开启五行
bool openFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index);
//更改五行属性
bool changeFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index, int order);
//更改五行属性
int changeFiveElemNew(Hero *hero, FIVE_ELEMENT_T elem, int index);
//使用五行道具
bool useFiveElemGoods(Hero *hero, char* goodsId, int order, int index);
//获取五行伤害
int getFiveElemHurt(FiveElem *fiveHit, FiveElem *fiveHited);
