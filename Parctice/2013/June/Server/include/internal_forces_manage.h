#ifndef _INTERNAL_FORCES_MANAGE_H_
#define _INTERNAL_FORCES_MANAGE_H_

#include "internal_forces.h"
#include "command_other_function_all_over.h"
#include "hero.h"

int internalForcesLvlUp(Hero* hero, int newLevel);

void internalForcesAttrReCountByLevel(Hero* hero);

int internalForcesIncExp(Hero* hero, int mode);

int viewHeroInternalForces(Hero* hero, int incExp = 0);

bool isInForsCanLvlUp(Hero* hero);
#endif