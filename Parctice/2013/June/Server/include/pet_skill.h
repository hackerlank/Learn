// #ifndef PETSKILL_H
// #define PETSKILL_H
// #include<iostream>
// #include<string>
// #include<map>
// #include"pet.h"
// #include"petSkill_config.h"
// using namespace std;


// class Pet;
// class PetSkill_Config;
// class PetSkill
// {
// private:  
	// string identity;												//宠物技能实例id
	// string id;														//宠物技能id
	// int flag;														//宠物技能类型
	// int effect;														//宠物技能效果
	// int increaseRatio;												//宠物技能效果的增量
	// int limit;														//学习技能宠物需要的等级
	// int needMoney;													//宠物技能升级所需金币
	// int needExp;													//宠物技能升级所需经验
	// int level;														//宠物技能等级
	
	// Pet *pet;														//拥有此技能的宠物实例指针
	// PetSkillData petskilldata;

// public:
	// PetSkill(PetSkill_Config *_petSkill_config,Pet *_pet);
	// PetSkill(PetSkillData _petskilldata);
	// void initSkill(PetSkill_Config *petSkill_config,int _index);
	// bool skillLevelUpNeedExp(int _index);										//计算宠物技能升级所需经验
	// bool skillLevelUpNeedMoney(int _index);									//计算宠物技能升级所需金币
	// bool skillLevelUp(int _index);												//宠物技能升级
	// void triggerPassiveSkill(int _flag);									//触发被动技能
	// void removePassiveSkill(int _flag);									//去掉宠物技能的效果
	// void increaseEffect(int _index);										//技能属性增长
	// int getAttRatio(int _index);											//获得攻击比率
	// string getSkillId(int _index);												//获得技能id
	// string getSkillIdentity(int _index);
	// void saveInStruct(int _index);
	// PetSkillData getStruct(int _index);
	// int getSkillLevel(int _index);
	// int getSkillNeedMoney(int _index);
	// int getSkillNeedExp(int _index);
	// int getSkillLimit(int _index);
	// int getSkillFlag(int _index);
	// void setPet(Pet *_pet);	
// };
// #endif