/* 
		文件类型：头文件
		文件名称：npc.h
		文件作用：NPC实体类npc的属性以及方法的定义
		完成时间：2012.5.10
		  完成人：Evan
*/

#ifndef NPC_H
#define NPC_H
#include<string>
#include<set>
#include"data_structure_struct.h"
class Npc
{
private:  
	string npc_id;//npcid
	//string npc_name;  //npc名称
	char   *mapId;       				//地图id
	Point  standpoint;             			//npc所在地图的像素点/逻辑点

public:
	Npc(string _npc_id);
};
#endif

