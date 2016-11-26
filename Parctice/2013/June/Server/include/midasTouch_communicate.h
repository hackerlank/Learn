#ifndef MIDASTOUCH_COMMUNICATE_H
#define MIDASTOUCH_COMMUNICATE_H
#include <iostream>
#include <string>
#include "command_other_function_all_over.h"
#include "hero.h"
#include "midasTouch.h"

void midasTouchRefresh(char *buffer);
void midasTouchInform(char *buffer);
void midasTouchReceive(char *buffer);
void midasTouchModify(char *buffer);
void midasTouchResponse(char *buffer);

#endif