#ifndef FIVE_CONFIGURATION_H
#define FIVE_CONFIGURATION_H
#include<string>
#include<iostream>
using namespace std;
class Five_Configuration
{
private:
	string id;
	int gold;
	int wood;
	int water;
	int fire;
	int soil;
public:
	Five_Configuration(string _id,int _gold,int _wood,int _water,int _fire,int _soil);
	string getid(void);
	int getgold(void);
	int getwood(void);
	int getwater(void);
	int getfire(void);
	int getsoil(void);
};
#endif
