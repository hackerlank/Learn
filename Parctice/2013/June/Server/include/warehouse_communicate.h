#ifndef WAREHOUSE_COMMUNICATE_H
#define WAREHOUSE_COMMUNICATE_H
#include<iostream>
#include<string>
#include<map>
#include"warehouse_operator.h"
#include"warehouse.h"

void warehouse_drag(char* buffer);
void warehouse_expand(char* buffer);
void warehouse_saveGoods(char* buffer);
void warehouse_takeGoods(char* buffer);
void warehouse_destory(char* buffer);
void warehouse_reduction(char* buffer);
void warehouseArrange(char* buffer);

#endif