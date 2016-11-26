#include"redName.h"
//罪恶值增加条件判断
bool term(Hero *me,Hero *hit)
{
	return me->getCamp()==hit->getCamp()?(hit->getisRedName()?false:true):false;
}