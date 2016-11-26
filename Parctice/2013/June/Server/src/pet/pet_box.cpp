#include"pet_box.h"
extern map<string,Pet_Config*> id_to_pet;	
extern map<string,Pet*> id_to_activePet;
extern char g_out_buf[20480];

/**************************************
* Author:	Cookie
* Date	:	2012.9.12
* 传入参数 :HeroBasicData *obj，输出文件名：outfile
* Description：用于测试从game server中的Hero Basic Data数据是否正确
***************************************/
int Pet_Box::showPetData(Pet_BoxDataNew *obj, char *outfile)
{
 	// FILE *out;
	// if((out = fopen(outfile, "w+")) == NULL){
		// fprintf(stderr, "fopen file %s error!\n", outfile);
		// exit(EXIT_FAILURE);
	// }

	// for(int i=0;i!=obj->number;++i)
	// {
		// fprintf(out, "test PetData identity:%s\n", obj->petdata[i].identity);
		// fprintf(out, "test PetData id:%s\n", obj->petdata[i].id);
		// fprintf(out, "test PetData nickName:%s\n", obj->petdata[i].nickName);
		// fprintf(out, "test PetData photoId:%s\n", obj->petdata[i].photoId);
		// fprintf(out, "test PetData level:%d\n", obj->petdata[i].level);
		// fprintf(out, "test PetData outHarm:%d\n", obj->petdata[i].outHarm);
		// fprintf(out, "test PetData outHarmRate:%d\n", obj->petdata[i].outHarmRate);
		// fprintf(out, "test PetData inHarm:%d\n", obj->petdata[i].inHarm);
		// fprintf(out, "test PetData inHarmRate:%d\n", obj->petdata[i].inHarmRate);
		// fprintf(out, "test PetData outAttackVal:%d\n", obj->petdata[i].outAttackVal);
		// fprintf(out, "test PetData outAttackValRate:%d\n", obj->petdata[i].outAttackValRate);
		// fprintf(out, "test PetData inAttackVal:%d\n", obj->petdata[i].inAttackVal);
		// fprintf(out, "test PetData inAttackValRate:%d\n", obj->petdata[i].inAttackValRate);
		// fprintf(out, "test PetData hit:%d\n", obj->petdata[i].hit);
		// fprintf(out, "test PetData hitRate:%d\n", obj->petdata[i].hitRate);
		// fprintf(out, "test PetData crit:%d\n", obj->petdata[i].crit);
		// fprintf(out, "test PetData critRate:%d\n", obj->petdata[i].critRate);
		// fprintf(out, "test PetData hungryVal:%d\n", obj->petdata[i].hungryVal);
		// fprintf(out, "test PetData hungryValIncrease:%d\n", obj->petdata[i].hungryValIncrease);
		// fprintf(out, "test PetData hungryValDecrease:%d\n", obj->petdata[i].hungryValDecrease);
		// fprintf(out, "test PetData hungryValDecreaseRate:%d\n", obj->petdata[i].hungryValDecreaseRate);
		// fprintf(out, "test PetData happyVal:%d\n", obj->petdata[i].happyVal);
		// fprintf(out, "test PetData happyValIncrease:%d\n", obj->petdata[i].happyValIncrease);
		// fprintf(out, "test PetData happyValDecrease:%d\n", obj->petdata[i].happyValDecrease);
		// fprintf(out, "test PetData happyValDecreaseRate:%d\n", obj->petdata[i].happyValDecreaseRate);
		// fprintf(out, "test PetData type:%d\n", obj->petdata[i].type);
		// fprintf(out, "test PetData range:%d\n", obj->petdata[i].range);
		// fprintf(out, "test PetData generation:%d\n", obj->petdata[i].generation);
		// fprintf(out, "test PetData expNow:%d\n", obj->petdata[i].expNow);
		// fprintf(out, "test PetData expNeed:%d\n", obj->petdata[i].expNeed);
		// fprintf(out, "test PetData expAgo:%d\n", obj->petdata[i].expAgo);
		// fprintf(out, "test PetData active:%d\n", obj->petdata[i].active);
		// fprintf(out, "test PetData sex:%d\n", obj->petdata[i].sex);
		// fprintf(out, "test PetData quality:%d\n", obj->petdata[i].quality);
		// fprintf(out, "test PetData maxHappy:%d\n", obj->petdata[i].maxHappy);
		// fprintf(out, "test PetData maxHungry:%d\n", obj->petdata[i].maxHungry);
		// fprintf(out, "test PetData nowEvolution:%d\n", obj->petdata[i].nowEvolution);
		// fprintf(out, "test PetData maxEvolution:%d\n", obj->petdata[i].maxEvolution);
		// for(int succinctedi=0;succinctedi!=6;++succinctedi)
		// {
			// fprintf(out, "test PetData succincted:%d\n", obj->petdata[i].succincted[succinctedi]);
		// }
		// fprintf(out, "test fiveElement level:%d\n", obj->petdata[i].fiveElement.level);
		// fprintf(out, "test fiveElement element:%d\n", obj->petdata[i].fiveElement.element);
		// fprintf(out, "test fiveElement expNow:%d\n", obj->petdata[i].fiveElement.expNow);
		// fprintf(out, "test fiveElement expForNext:%d\n", obj->petdata[i].fiveElement.expForNext);
		// for(int petskilldatai=0;petskilldatai!=obj->petdata[i].skillNum;++petskilldatai)
		// {
			// fprintf(out, "test petskilldata identity:%s\n", obj->petdata[i].petskilldata[petskilldatai].identity);
			// fprintf(out, "test petskilldata id:%s\n", obj->petdata[i].petskilldata[petskilldatai].id);
			// fprintf(out, "test petskilldata flag:%d\n", obj->petdata[i].petskilldata[petskilldatai].flag);
			// fprintf(out, "test petskilldata effect:%d\n", obj->petdata[i].petskilldata[petskilldatai].effect);
			// fprintf(out, "test petskilldata increaseRatio:%d\n", obj->petdata[i].petskilldata[petskilldatai].increaseRatio);
			// fprintf(out, "test petskilldata limit:%d\n", obj->petdata[i].petskilldata[petskilldatai].limit);
			// fprintf(out, "test petskilldata needMoney:%d\n", obj->petdata[i].petskilldata[petskilldatai].needMoney);
			// fprintf(out, "test petskilldata needExp:%d\n", obj->petdata[i].petskilldata[petskilldatai].needExp);
			// fprintf(out, "test petskilldata level:%d\n", obj->petdata[i].petskilldata[petskilldatai].level);
		// }	
	// }
	
	// fprintf(out, "test Pet_BoxDataNew number:%d\n", obj->number);
	// fprintf(out, "test Pet_BoxDataNew maxNumber:%d\n", obj->maxNumber);
	// fprintf(out, "test Pet_BoxDataNew index:%d\n", obj->index);
	
	// if(fclose(out) != 0){
		// fprintf(stderr, "fclose file error!\n");
		// exit(EXIT_FAILURE);
	// } 	

	// return 0;
}

Pet_Box::Pet_Box()
{
	
	// saveInstruct();
}

Pet_Box::Pet_Box(Pet_BoxDataNew *_pet_boxdata)
{	
	// showPetData(&_pet_boxdata,"pet_boxdata");
	pet_boxdata=_pet_boxdata;
	for(int i=0; i<12; i++) {
		pets[i] =0;
	}
	if (pet_boxdata->number > 12) {
		pet_boxdata->number = 12;
	}
	
	if (pet_boxdata->number <=0 ) {
                pet_boxdata->number = 0;
        }
	
	for(int i=0; i<pet_boxdata->number; i++){
		pets[i] = new Pet(pet_boxdata->petdata + i);
	}
}

Pet_Box::~Pet_Box(void)
{
	for(int i =0;  i < 12; i++){
		if(pets[i]) {
			delete pets[i];
			pets[i] = 0;
		}
	}
}
	
Pet* Pet_Box::getPet(int _index)							//取得排名第index位的宠物实例
{
	if((_index <0 ) || (_index >= 12)){
		return 0;
	}
	return pets[_index];
}

Pet* Pet_Box::getActivePet(void)							//取得正在战斗的宠物实例
{
	int _index = pet_boxdata->index;
	 if((_index <0 ) || (_index >= 12)){
                return 0;
        }

	return pets[_index];	
}

int Pet_Box::getNumber(void)		
{
	return pet_boxdata->number;
}						
int Pet_Box::getMaxNumber(void)
{
	return pet_boxdata->maxNumber;
}

void Pet_Box::usePetAgg(Pet *_pet)								//使用宠物蛋
{
	int _index = pet_boxdata->number;
	  if((_index <0 ) || (_index >= 12)){
                return ;
        }

	pets[_index] = _pet;  //外面不要再删除_pet了,谁删死全家超市.	
	_pet->setPet_boxIndex(pet_boxdata->number);
	pet_boxdata->number++;

	 if (pet_boxdata->number > 12) {
                pet_boxdata->number = 12;
        }

        if (pet_boxdata->number <=0 ) {
                pet_boxdata->number = 0;
        }

	cout<<"有没有到这 pet_boxdata->number:"<<pet_boxdata->number<<endl;
}

void Pet_Box::carryNum(int heroLevel)
{
	if (heroLevel==10)
	{
		pet_boxdata->maxNumber=3;
	}
	else if (heroLevel==80)
	{
		pet_boxdata->maxNumber=12;
	}
	else if (heroLevel>10&&heroLevel%10==0)
	{
		pet_boxdata->maxNumber=2+heroLevel/10;
		if (pet_boxdata->maxNumber>12)
		{
			pet_boxdata->maxNumber=12;
		}
	}
}

int Pet_Box::getActivePetIndex(void)
{
	return pet_boxdata->index;
}

void Pet_Box::setActivePetIndex(int _index)
{
	pet_boxdata->index=_index;
	cout<<"active index is :"<<pet_boxdata->index<<endl;
}

void Pet_Box::send_msg_add(char *msg,Pet *pet,int len)
{
	if (msg==NULL)
	{
		return;
	}
	if (pet==NULL)
	{
		cout<<"pet is not exist pet_box 95"<<endl;
		snprintf(msg,len,"%d,%d,%d",10,PET_USE,0);
	}
	else
	{
		pet->send_pet_attr(msg,sizeof(msg));
	}
}

void Pet_Box::send_msg_list(char* msg,int len)
{
	Pet * _pet;
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%d,%d,%d",10,PET_LIST,12,pet_boxdata->maxNumber,pet_boxdata->number,pet_boxdata->index);
	for(int i=0; i < pet_boxdata->number; i++){
		_pet = pets[i];
		snprintf(msg+strlen(msg),len-strlen(msg),",%d,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d",i,_pet->getFlag(),_pet->getIdentity(),_pet->getId(),\
			_pet->getNickName(),_pet->getLevel(),_pet->getQuality(),_pet->getGeneration(),_pet->getType(),_pet->countPower(), (pet_boxdata->index==i) ? 1:0);
	}
}

bool Pet_Box::verification(int _index,char* identity)
{
	if(_index<0||_index>pet_boxdata->number-1)
	{
		return false;
	}

	return (strcmp((pets[_index])->getIdentity(),identity)==0);
}

bool Pet_Box::deletePet(int _index)
{
	if(_index<0||_index>pet_boxdata->number-1)
	{
		cout<<"delete Pet error "<<endl;
		return false;
	}
	
	pet_boxdata->number--;	
		
	if (_index<=pet_boxdata->index)
	{
		pet_boxdata->index--;
	}
	
	for(int i = _index; i < pet_boxdata->number; i++){		
		memcpy(pets[i]->petdata, pets[i+1]->petdata, sizeof(PetData)); //内存拷贝更安全。 benliao 2013.6.10
		pets[i]->setPet_boxIndex(i);


		map<string,Pet*>::iterator it;

        	it=id_to_activePet.find(pets[i]->petdata->identity);

       		if (it==id_to_activePet.end())
	        {	
                	cout<<"error-------------------------------------pet.cpp 771"<<endl;
        	}
        	else
        	{
                       id_to_activePet.erase(it);
		       id_to_activePet.insert(map<string,Pet*>::value_type(pets[i]->petdata->identity,pets[i]));
                }

		
		cout<<"pets["<<i<<"]->getNickName():"<<pets[i]->getNickName()<<endl;
		cout<<"pets["<<i<<"]->countPower():"<<pets[i]->countPower()<<endl;
	}
	
	if (pet_boxdata->number > 12) {
		pet_boxdata->number = 12;
	}

	if (pet_boxdata->number <=0 ) {
		pet_boxdata->number = 0;
	}	
	memset(pets[pet_boxdata->number]->petdata, 0, sizeof(PetData));
	delete pets[pet_boxdata->number];
	pets[pet_boxdata->number] = 0;	
}

Pet_BoxDataNew Pet_Box::getMemStruct(void)
{	
	return *pet_boxdata;
}

int Pet_Box::getIndex(char* identity)						//根据宠物实例id 查找宠物索引
{
	for(int i=0; i < pet_boxdata->number; i++ ){
		if (strcmp(identity, (pets[i] )->getIdentity()) == 0) return i;
	}
	return -1;
}

void Pet_Box::msg_maxNumber(char* msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d",10,PET_BOX_NUMBER,pet_boxdata->maxNumber);
}
