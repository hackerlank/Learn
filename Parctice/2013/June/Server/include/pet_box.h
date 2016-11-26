#ifndef PET_BOX_H
#define PET_BOX_H
#include<iostream>
#include<string>
#include<map>
#include"pet.h"
using namespace std;

class Pet;
class Pet_Box
{
private:  		
	// int number;								//携带的宠物数量   用pet_boxdata.nuber代替
	// int maxNumber;							//可携带的宠物数量上限	 用pet_boxdata.maxNumber代替
	// int index;								//当前出战宠物的索引   用pet_boxdata.index代替
	Pet_BoxDataNew* pet_boxdata;
	Pet *pets[12];
	
public:
	Pet_Box();	
	Pet_Box(Pet_BoxDataNew *_pet_boxdata);
	~Pet_Box(void);
	Pet* getPet(int _index);							//取得排名第index位的宠物实例
	Pet* getActivePet(void);							//取得正在战斗的宠物实例
	int getNumber(void);								
	int getMaxNumber(void);
	void usePetAgg(Pet *_pet);							//使用宠物蛋
	void carryNum(int heroLevel);						//携带数量判定
	int getActivePetIndex(void);						//取得出战宠物的索引
	void setActivePetIndex(int _index);
	void send_msg_add(char* msg,Pet *pet,int len);
	void send_msg_list(char *msg,int len);
	bool verification(int _index,char* identity);		//验证宠物
	bool deletePet(int _index);
	// void saveInstruct(int _index);
	Pet_BoxDataNew getMemStruct(void);
	int getIndex(char* identity);						//根据宠物实例id 查找宠物索引
	void onlineSetActive(void);
	int showPetData(Pet_BoxDataNew *obj, char *outfile);	
	void msg_maxNumber(char *msg,int len);
};
#endif
