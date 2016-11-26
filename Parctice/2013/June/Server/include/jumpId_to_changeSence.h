/*
		file name£º jumpId_to_changeSence.cpp
		   author£º xhm
		  created:  2012.7.19
	    directions: Analyzing the information sended from the client,
					and achieve jumping to target map;
*/
#ifndef JUMPID_TO_CHANGESEHCE_H
#define JUMPID_TO_CHANGESEHCE_H

#include <map>
#include"data_structure_struct.h"

void jumpid_to_change_sence(char *buffer);
void gotoNPC(Point pt,Map_Inform* map_next);
void goByNPC(char *buffer);
void goActive(char *buffer);
#endif
