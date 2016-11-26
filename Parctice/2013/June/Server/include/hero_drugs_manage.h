#ifndef _HERO_DRUGS_MANAGE_
#define _HERO_DRUGS_MANAGE_

#include "timerContainer.h"
#include "timerExpireList.h"
#include "hero.h"

bool drug_use_interface(Hero *hero,char* type_id,int index);	//药品开始使用
	
void continueUseBuffDrug(Hero* hero);			//上线恢复buff药的使用
	
int attribute_increase(Hero* hero,int effect_type);
		
int attribute_decrease(Hero* hero,int effect_type);

void initBuffDrugData(int index,Hero *hero);

#endif
