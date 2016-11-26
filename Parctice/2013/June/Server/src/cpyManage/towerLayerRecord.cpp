/************************************************************
	文件名：towerLayerRecord.cpp
	文件作用：实现类TowerLayerRecord类的方法
	作者：chenzhen
	创建日期：2013.04.08
************************************************************/

#include"command_other_function_all_over.h"
#include"towerLayerRecord.h"
#include"stdlib.h"
#include"hero.h"
#include<iostream>
#include"cpyLimit.h"

extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string,map<string,string> >towerMapConf;
using namespace std;

TowerLayerRecord::TowerLayerRecord(Hero *_owner)
{
	map<string,TowerRecordAsist>::iterator tower_it,layer_it,lay_it;	
	
	if(_owner == NULL)
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument _owner is NULL:"<<endl;
		return;
	}
	
	owner = _owner;
	
	/*初始化数据*/
	initTwoerMap();
	initLayerMap();
	
	tower_it = towerMap.find(_owner->memHero->nowTowerId);
	if(tower_it == towerMap.end())
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument towerId is error:"<<_owner->memHero->nowTowerId<<endl;
		return;
	}
	layer_it = layerMap.find(_owner->memHero->nowLayerId);
	if(layer_it == layerMap.end())
	{
		cout<<"HeroTowerRecord::HeroTowerRecord the argument layerId is error:"<<_owner->memHero->nowLayerId<<endl;
		return;
	}
	
	tower_it->second.flg = 1;	
	
	/*初始化每一次是否可以进入*/
	initLayerCanFlg();
	
#if 0
	for(lay_it = layerMap.begin();lay_it != layer_it;++lay_it)
	{
		lay_it->second.flg = 1;
	}
	layer_it->second.flg = 1;
#endif	
	
	memset(nowTowerId,'\0',sizeof(nowTowerId));
	
	memset(nowLayerId,'\0',sizeof(nowLayerId));
	
	strncpy(nowTowerId,_owner->memHero->nowTowerId,strlen(_owner->memHero->nowTowerId));
	
	strncpy(nowLayerId,_owner->memHero->nowLayerId,strlen(_owner->memHero->nowLayerId));	
	
	initTwoerMsg();
	
	if(isShouldBrushLayer())
	{		
		initLayerMsg(true);
	}
	else
	{
		initLayerMsg();
	}
	
	isSwap = false;
	
	cout<<"TowerLayerRecord::TowerLayerRecord test nowTowerId:"<<nowTowerId<<endl;
	cout<<"TowerLayerRecord::TowerLayerRecord test nowLayerId:"<<nowLayerId<<endl;
	
}

/*生成面板消息*/
void TowerLayerRecord::initMsg(void)
{
	initTwoerMsg();
	initLayerMsg();
}

/*生成塔面板消息*/
void TowerLayerRecord::initTwoerMsg(void)
{
	
	map<string,TowerRecordAsist>::iterator tower_it;
	
	memset(towerMsg,'\0',sizeof(towerMsg));
	
	sprintf(towerMsg,"%d,%d",TOWER_F,TOWER_S);
	
	for(tower_it = towerMap.begin();tower_it != towerMap.end();++tower_it)
	{
		sprintf(towerMsg + strlen(towerMsg),",%s,%d",tower_it->first.c_str(),tower_it->second.flg);
	}
}

/*生成层面板消息*/
void TowerLayerRecord::initLayerMsg(bool _isCanBuy)
{
	
	map<string,TowerRecordAsist>::iterator layer_it;
	
	memset(layerMsg,'\0',sizeof(layerMsg));
	
	sprintf(layerMsg,"%d,%d",LAYER_F,LAYER_S);
	
	for(layer_it = layerMap.begin();layer_it != layerMap.end();++layer_it)
	{
		sprintf(layerMsg + strlen(layerMsg),",%s,%d",layer_it->first.c_str(),layer_it->second.flg);
	}
	
	//刷新按钮是否亮，1，为可以点点
	if(_isCanBuy)
	{
		sprintf(layerMsg + strlen(layerMsg),",%d",1);
	}
	else
	{
		sprintf(layerMsg + strlen(layerMsg),",%d",0);
	}
}

/*更改当前塔的id*/
bool TowerLayerRecord::changeTowerId(void)
{	
	map<string,TowerRecordAsist>::iterator tower_it,temp_it;
	
	tower_it = towerMap.find(nowTowerId);
	
	temp_it = tower_it;
	++temp_it;
	
	if(tower_it == towerMap.end())
	{
		cout<<"TowerLayerRecord::changeTowerId the nowTowerId is not exist or it up to top of the tower:"<<nowTowerId<<endl;
		return false;
	}
	
	if(temp_it == towerMap.end())
	{
		/*打完青衣楼，给头衔，勇往直前*/
		if(owner)
		{
			owner->addTitle("T053");
			
			owner->updataSingleTarget(7,7);
		}
		
		
		cout<<"TowerLayerRecord::changeTowerId get the top tower:"<<nowTowerId<<endl;
		return false;
	}
	
	/*上层塔置灰*/
	tower_it->second.flg = 0;
	
	++tower_it;
	
	/*下层塔置亮*/
	tower_it->second.flg = 1;
	
	/*更改当前塔id*/
	memset(nowTowerId,'\0',sizeof(nowTowerId));
	
	strncpy(nowTowerId,const_cast<char*>(tower_it->first.c_str()),tower_it->first.size());
	
	/*存memcached*/
	memset(owner->memHero->nowTowerId,'\0',sizeof(owner->memHero->nowTowerId));
	
	strncpy(owner->memHero->nowTowerId,nowTowerId,strlen(nowTowerId));
	
	return true;
}

/*打过层之后开通下一层函数*/
void TowerLayerRecord::changeLayerId(void)
{	
	char *choiceLayerId = owner->getChoiseLayerId();	
	
	if(strcmp(choiceLayerId,nowLayerId) != 0)
	{
		chgLayerFlg(choiceLayerId,0);
		
		/*生成层的消息*/
		initLayerMsg(true);
		
		send_msg(owner->getFd(), getLayerMsg());
		
		cout<<"TowerLayerRecord::changeLayerId enter the lowerLayer:"<<choiceLayerId<<endl;
		return;
	}
	
	if (owner != NULL)
	{
		char taskNeedCheck[20];
		sprintf(taskNeedCheck, "%s_%s", nowTowerId, nowLayerId);
		if(owner->updateHeroTaskStatus(PASS_TOWER_LAYER_TASK_NEED_TYPE, taskNeedCheck))
		{
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
			cout<<"Tower001 and layer001 task check ok ,you have finished it!!!!!!!!"<<endl;
		}
		owner->clrTskStSomeBit(TASK_NEED_PASS_TOWER_LAYER);
	}
	
	//最后一层，最后一个塔
	if(strncmp(nowTowerId,"tower_010",9) == 0 && strncmp(nowLayerId,"layer_005",9) == 0)
	{
		lastLayer();
		return;
	}
	
	
	map<string,TowerRecordAsist>::iterator layer_it,temp_it;
	
	layer_it = layerMap.find(nowLayerId);
	
	/*数据出错*/
	if(layer_it == layerMap.end() || owner == NULL)
	{
		cout<<"TowerLayerRecord::changeLayerId the nowLayerId is not exist or owner is NULL :"<<nowLayerId<<endl;
		return;
	}
	
	temp_it = layer_it;
	++temp_it;
	
	/*最后一层*/
	if(temp_it == layerMap.end())
	{
		/*跨一个塔层*/
		if(!changeTowerId())
		{
			return;		
		}
		
		/*重置层的数据*/
		initLayerFlg();
		
		/*生成塔，和层的消息*/
		initMsg();
		
		coverChgeLayerFlg();
		
		if(owner)
		{
			storeData();
			send_msg(owner->getFd(), getTowerMsg());
			send_msg(owner->getFd(), getLayerMsg());			
		}	
		return;
	}
	
	//当前层关闭，下一层开启你
	chgLayerFlg(nowLayerId,0);
	
	++layer_it;
	
	layer_it->second.flg = 1;

	memset(nowLayerId,'\0',sizeof(nowLayerId));
		
	strncpy(nowLayerId,const_cast<char*>(layer_it->first.c_str()),layer_it->first.size());
	
	chgLayerFlg(nowLayerId,1);
	
	/*生成层的消息*/
	initLayerMsg(true);
	
	storeData();
	
	send_msg(owner->getFd(), getLayerMsg());
	
	return ;	
}

/*跨塔时初始化层的数据*/
void TowerLayerRecord::initLayerFlg(void)
{
	
	map<string,TowerRecordAsist>::iterator layer_it;	
	
	for(layer_it = layerMap.begin();layer_it != layerMap.end();++layer_it)
	{
		layer_it->second.flg = 0;
	}
	
	layer_it = layerMap.begin();
	
	layer_it->second.flg = 1;
	
	memset(nowLayerId,'\0',sizeof(nowLayerId));
	
	strncpy(nowLayerId,const_cast<char*>(layer_it->first.c_str()),layer_it->first.size());
	
	/*存memcached*/
	memset(owner->memHero->nowLayerId,'\0',sizeof(owner->memHero->nowLayerId));
	
	strncpy(owner->memHero->nowLayerId,nowLayerId,strlen(nowLayerId));
}	

/*判断是否为当前塔*/
bool TowerLayerRecord::isRightTower(char *towerId)
{
	if(towerId == NULL)
	{
		cout<<"TowerLayerRecord::isRightTower the argument is NULL:"<<endl;
		return false;
	}
	
	if(strncmp(nowTowerId,towerId,strlen(nowTowerId)) == 0)
	{
		return true;
	}
	
	return false;
}

/*判断层是否开启*/
bool TowerLayerRecord::isRightLayer(char *layerId)
{
	map<string,TowerRecordAsist>::iterator layer_it;	
	
	if(layerId == NULL)
	{
		cout<<"TowerLayerRecord::isRightLayer the argument is NULL:"<<endl;
		return false;
	}
		
	layer_it = layerMap.find(layerId);
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::isRightLayer the layerId is not found:"<<layerId<<endl;
		return false;
	}
	
	if(layer_it->second.flg == 1)
	{
		return true;
	}
	
	return false;
}

/*析构函数*/
TowerLayerRecord::~TowerLayerRecord(void)
{
	owner = NULL;
}

/*初始化黑木崖塔的数据*/
void TowerLayerRecord::initTwoerMap(void)
{
	map<string,map<string,string> >::iterator towerConf_it;
	if(towerMapConf.empty())
	{
		cout<<"TowerLayerRecord::initTwoerMap the towerMapConf is empty ,it to say the towerMargin.xml is error,please stop the progress to check the towerMargin.xml now:"<<endl;
		exit(1);
		return;
	}
	for(towerConf_it = towerMapConf.begin();towerConf_it != towerMapConf.end();++towerConf_it)
	{
		TowerRecordAsist temp(const_cast<char*>(towerConf_it->first.c_str()));
		towerMap[towerConf_it->first] = temp;
	}
}

/*初始化黑木崖层的数据*/
void TowerLayerRecord::initLayerMap(void)
{
	map<string,map<string,string> >::iterator towerConf_it;
	map<string,string>::iterator layer_conf;
	towerConf_it = towerMapConf.begin();
	
	if(towerConf_it->second.empty())
	{
		cout<<"TowerLayerRecord::initLayerMap the towerConf_it->second is empty ,it to say the towerMargin.xml is error,please stop the progress to check the towerMargin.xml now:"<<endl;
		exit(1);
		return;
	}
	
	for(layer_conf = towerConf_it->second.begin();layer_conf != towerConf_it->second.end();++layer_conf)
	{
		TowerRecordAsist temp(const_cast<char*>(layer_conf->first.c_str()));
		layerMap[layer_conf->first] = temp;
	}
}

/*获得塔的开启消息*/
char* TowerLayerRecord::getTowerMsg(void)
{
	return towerMsg;
}

/*获得层的开启消息*/
char* TowerLayerRecord::getLayerMsg(void)
{
	return layerMsg;
}

/*测试黑木崖读取配置是否正确*/
void testTowerLayerConf(void)
{
	map<string,map<string,string> >::iterator tower_conf;
	for(tower_conf = towerMapConf.begin();tower_conf != towerMapConf.end();++tower_conf)
	{
		// cout<<"test the towerId before:"<<tower_conf->first<<endl;
		testTowerLayerConfAsist(tower_conf->second);
		// cout<<"test the towerId end:"<<tower_conf->first<<endl;
	}
}	

/*测试辅助函数*/
void testTowerLayerConfAsist(map<string,string> &conf)
{
	map<string,string>::iterator tower_conf;
	for(tower_conf = conf.begin();tower_conf != conf.end();++tower_conf)
	{
		// cout<<"layerId :"<<tower_conf->first<<" cpyId :"<<tower_conf->second<<endl;
	}
}	


/*往memcached存东西*/
void TowerLayerRecord::storeData(void)
{
	memset(owner->memHero->nowTowerId,'\0',sizeof(owner->memHero->nowTowerId));
	memset(owner->memHero->nowLayerId,'\0',sizeof(owner->memHero->nowLayerId));
		
	strncpy(owner->memHero->nowTowerId,nowTowerId,strlen(nowTowerId));
	strncpy(owner->memHero->nowLayerId,nowLayerId,strlen(nowLayerId));
}

/*求获得的扫荡集合*/
void TowerLayerRecord::bornSwapOutRewardSet(void)
{
	map<string,TowerRecordAsist>::iterator layer_it,layer_its;
	
	swapLayerId.clear();
	
	layer_it = layerMap.find(nowLayerId);
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::bornSwapOutRewardSet not find the nowLayerId:"<<nowLayerId<<endl;
		return;
	}
	for(layer_its = layerMap.begin();layer_its != layer_it;++layer_its)
	{
		swapLayerId.insert(layer_its->first);
	}
}

/*弹出扫荡奖励面板*/
void TowerLayerRecord::beginSwapOutReward(void)
{
	if(isSwap)
	{
		cout<<"TowerLayerRecord::beginSwapOutReward you have swaped:"<<endl;
		return;
	}
	
	bornSwapOutRewardSet();
	
	if(swapLayerId.empty())
	{
		cout<<"TowerLayerRecord::beginSwapOutReward the swapLayerId is empty:"<<endl;
		return ;
	}	
	set<string>::iterator layer_it;
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	char *ownerId = owner->getIdentity();
	
	map<string,map<string,string> >::iterator tower_it;
	map<string,string>::iterator layerCpy_it;
	tower_it = towerMapConf.find(nowTowerId);
	if(tower_it == towerMapConf.end())
	{
		cout<<"TowerLayerRecord::beginSwapOutReward the nowTowerId is not exist:"<<nowTowerId<<endl;
		return;
	}
	
	for(layer_it = swapLayerId.begin();layer_it != swapLayerId.end();++layer_it)
	{
		layerCpy_it = tower_it->second.find(*layer_it);
		if(layerCpy_it == tower_it->second.end())
		{
			cout<<"TowerLayerRecord::beginSwapOutReward the layerCpy_it is error:"<<*layer_it<<endl;
			return;
		}
		
		cpyLimt_it = cpyId_to_cpyLimit.find(layerCpy_it->second);
		if(cpyLimt_it == cpyId_to_cpyLimit.end())
		{		
			cout<<"TowerLayerRecord::beginSwapOutReward the layer_it is error:"<<*layer_it<<endl;
			return;
		}
		cpyLimt_it->second->insertWipeOut(ownerId);
	}	
	
	isSwap = true;
}


/*领取扫荡奖励*/
void TowerLayerRecord::endSwapOutReward(void)
{
	if(!isSwap)
	{
		cout<<"TowerLayerRecord::endSwapOutReward have not born the beginSwapOutReward:"<<endl;
		return;
	}
	
	if(swapLayerId.empty())
	{
		cout<<"TowerLayerRecord::endSwapOutReward the swapLayerId is empty:"<<endl;
		return;
	}	
	set<string>::iterator layer_it;
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	char *ownerId = owner->getIdentity();
	
	for(layer_it = swapLayerId.begin();layer_it != swapLayerId.end();++layer_it)
	{
		cpyLimt_it = cpyId_to_cpyLimit.find(*layer_it);
		if(cpyLimt_it == cpyId_to_cpyLimit.end())
		{		
			cout<<"TowerLayerRecord::beginSwapOutReward the layer_it is error:"<<*layer_it<<endl;
			return;
		}
		cpyLimt_it->second->eraseWipeOut(ownerId);
	}
	
	isSwap = false;
	swapLayerId.clear();
}

/*初始化层是否可以进入*/
void TowerLayerRecord::initLayerCanFlg(void)
{
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	int len = sizeof(owner->memHero->layerFlg)/sizeof(owner->memHero->layerFlg[0]);	
	for(size_t length = 0; length < len && layer_it != layerMap.end();++length,++layer_it)
	{
		layer_it->second.flg = owner->memHero->layerFlg[length];
	}
}


/*更改每层标志缓存数据*/
void TowerLayerRecord::chgLayerFlg(char *layerId,int flag)
{
	if(layerId == NULL || strlen(layerId) == 0)
	{
		cout<<"chgLayerFlg the layerId is NULL:"<<endl;
		return;
	}
	
	/*从0层开始*/
	size_t index = *(layerId + strlen(layerId) - 1) - '0' - 1;
	
	owner->memHero->layerFlg[index % 5] = flag;
	
	map<string,TowerRecordAsist>::iterator layer_it; 
	
	layer_it = layerMap.find(layerId);
	
	if(layer_it == layerMap.end())
	{
		cout<<"TowerLayerRecord::chgLayerFlg the layerId is error:"<<endl;
		return;
	}
	
	layer_it->second.flg = flag;
	
}


/*跨塔时更改层标志的数据*/
void TowerLayerRecord::coverChgeLayerFlg(void)
{	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	int len = sizeof(owner->memHero->layerFlg)/sizeof(owner->memHero->layerFlg[0]);	
	for(size_t length = 0; length < len && layer_it != layerMap.end();++length,++layer_it)
	{
		owner->memHero->layerFlg[length] = layer_it->second.flg;
	}
}


/*刷新层标志的数据*/
void TowerLayerRecord::brushLayerFlg(void)
{	
	size_t index = *(nowLayerId + strlen(nowLayerId) - 1) - '0' - 1;	
	index %= 5;
	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	for(size_t length = 0; length <= index && layer_it != layerMap.end();++length,++layer_it)
	{
		owner->memHero->layerFlg[length] = 1;
		layer_it->second.flg = 1;
	}
	
	/*生成层的消息*/
	initLayerMsg();
		
	send_msg(owner->getFd(), getLayerMsg());
}

/*判断是否有必要刷新如果为真，表示可以刷新，否则，表示没必要刷新*/
bool TowerLayerRecord::isShouldBrushLayer(void)
{	
	size_t index = *(nowLayerId + strlen(nowLayerId) - 1) - '0' - 1;	
	index %= 5;
	
	map<string,TowerRecordAsist>::iterator layer_it = layerMap.begin();
	for(size_t length = 0; length <= index && layer_it != layerMap.end();++length,++layer_it)
	{		
		if(layer_it->second.flg == 0)
		{
			return true;
		}
		
	}
	return false;
}


/*打完最后一层，最后一个塔后，控制那个刷新按钮*/
void TowerLayerRecord::lastLayer(void)
{	
	if(owner)
	{
		if(isShouldBrushLayer())
		{
			initLayerMsg(true);
		}
		else
		{
			initLayerMsg(false);				
		}
			
		send_msg(owner->getFd(), getTowerMsg());
		send_msg(owner->getFd(), getLayerMsg());	
	}
}



	
	


