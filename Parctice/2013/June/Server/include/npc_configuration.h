#ifndef NPC_CONFIGURATION_H
#define NPC_CONFIGURATION_H
#include<iostream>
#include<string>
using namespace std;
class Npc_Configuration
{
private:  
	string npc_id;//npcid
	string npc_name;  //npcÃû³Æ
public:
	Npc_Configuration(string _npc_id,string _npc_name);
};
#endif