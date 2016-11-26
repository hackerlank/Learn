#include"function_read_configuration_files.h"
#include"task_configuration.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string.h>
using namespace std;
extern map<string,Task_Configuration*> id_to_task;
map<int, TaskChaptReward_T> chapt_2_taskReward;
int read_files_task(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;
	xmlNodePtr typeNode;
	xmlNodePtr chaptNode;
	xmlNodePtr curNode;
	xmlNodePtr childNode;
	xmlAttrPtr attrPtr;    //节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char taskId[51];		//任务ID
	char taskName[51];   	//任务名称
	char recNpcId[51];      //接任务NPC id
	char finNpcId[51];      //交任务NPC id
	int taskType;      	//任务类型：主线、支线等
	int taskChapt;     	//任务章节：根据等级划分
	unsigned taskLevel;	//任务等级
	unsigned inFors;
	unsigned prestige;
	unsigned taskGold;  //任务奖励金钱
	unsigned taskExp;	//任务奖励经验
	int subType = 0;	//任务子类型
	int giveType;		//完成任务给奖励物品的方式：0：系统默认；1：玩家选择
	int freq;			//任务一天可接次数
	bool isLastOfThisChapt;
	char chaptReward[51] = {0};
	char chaptRewardNum = 0;
	
	/* 任务完成要求序列 */
	list<need_t*> taskNeed;
	/* 任务奖励序列 */
	set<give_t*> taskGive;
	/* 任务触发条件序列 */
	set<touch_t*> taskTouch;
	/* 任务接受时所给内容序列 */
	set<recv_t*> taskRecv;
	
//	xmlKeepBlanksDefault(0);
//	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER); //解析文件
	if (doc == NULL)
	{
		return -1;
	}
	
	//得到xml文件的root
	rootNode = xmlDocGetRootElement(doc);
	if (rootNode == NULL)
	{
		xmlFreeDoc(doc);
		return -1;
	}
	
	for (typeNode = rootNode->xmlChildrenNode; typeNode != NULL; typeNode = typeNode->next)
	{
		//读取任务类型
		taskType = 0;	//先初始为0，以后再定其缺省值
		if (!xmlStrcmp (typeNode->name, (const xmlChar*)"taskType"))
		{
			attrPtr = typeNode->properties;
			xmlChar *_taskType = xmlGetProp(typeNode, (const xmlChar *)"type");
			taskType = atoi(reinterpret_cast<const char *>(_taskType));
			xmlFree(_taskType);
			
			
		}
		
		//遍历每章节
		for (chaptNode = typeNode->xmlChildrenNode; chaptNode != NULL; chaptNode = chaptNode->next)
		{
			//读取任务章节
			taskChapt = 0;			//先初始为0，以后再定其缺省值
			if (!xmlStrcmp (chaptNode->name, (const xmlChar*)"Chapters"))
			{
				TaskChaptReward_T tempChaptReward;
				int cnt = 0;
				for (attrPtr = chaptNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
				{
					if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
					{
						xmlChar *_taskChapt = xmlGetProp(chaptNode, (const xmlChar *)"id");
						taskChapt = atoi((char*)_taskChapt);
						xmlFree(_taskChapt);
					} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardId"))
					{
						xmlChar *_item = xmlGetProp(chaptNode, (const xmlChar*)"rewardId");
						strncpy(tempChaptReward.rewardId, (char*)_item, sizeof tempChaptReward.rewardId);
						xmlFree(_item);
						cnt++;
					} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num"))
					{
						xmlChar *_item = xmlGetProp(chaptNode, (const xmlChar*) "num");
						tempChaptReward.rewardNum = atoi((char*)_item);
						xmlFree(_item);
						cnt++;
					}
				}
				
				if (cnt > 0)
				{			
					chapt_2_taskReward.insert(pair<int, TaskChaptReward_T>(taskChapt, tempChaptReward));
				}
		
			}
			
			//遍历各节点
			for (curNode = chaptNode->xmlChildrenNode; curNode != NULL; curNode = curNode->next)
			{
				if (!xmlStrcmp(curNode->name, (const xmlChar*)"task"))
				{	//读task节点的属性
					taskLevel = 0;         //配置文件现在不是每个任务都有level属性，给其默认值0
					for (attrPtr = curNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"subType")) {	
							/* 读任务的子类型 */
							xmlChar *_subType = xmlGetProp(curNode, (const xmlChar*)"subType");
							subType = atoi((char*)_subType);				
							//cout<<"in read_task_config::taskId: "<<taskId<<endl;
							xmlFree(_subType);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"isLastOfThisChapt"))
						{
							xmlChar *_item = xmlGetProp(curNode, (const xmlChar*)"isLastOfThisChapt");
							isLastOfThisChapt = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
							/* 读任务id属性 */
							xmlChar *_taskId = xmlGetProp(curNode, (const xmlChar*)"id");
							strncpy(taskId, const_cast<char *>(reinterpret_cast<const char *>(_taskId)), 51);				
							//cout<<"in read_task_config::taskId: "<<taskId<<endl;
							xmlFree(_taskId);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"name")) {	
							/* 读任务name属性 */
							xmlChar *_name = xmlGetProp(curNode, (const xmlChar*)"name");
							strncpy(taskName, const_cast<char *>(reinterpret_cast<const char *>(_name)), 51);			
							xmlFree(_name);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"receiveNPC")) {
							/* 读任务接受的NPC id属性 */
							xmlChar *_recNpcId = xmlGetProp(curNode, (const xmlChar*)"receiveNPC");
							strncpy(recNpcId, const_cast<char *>(reinterpret_cast<const char *>(_recNpcId)), 51);			
							xmlFree(_recNpcId);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardNPC")) {
							/* 读交任务的NPC id属性 */
							xmlChar *_finNpcId = xmlGetProp(curNode, (const xmlChar*)"rewardNPC");
							strncpy(finNpcId, const_cast<char *>(reinterpret_cast<const char *>(_finNpcId)), 51);			
							xmlFree(_finNpcId);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level")) {
							/* 读取任务等级属性 */
							xmlChar *_taskLevel = xmlGetProp(curNode, (const xmlChar*)"level");
							taskLevel = atoi(reinterpret_cast<const char*>(_taskLevel));
							xmlFree(_taskLevel);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"infors"))
						{
							xmlChar* _item = xmlGetProp(curNode, (const xmlChar*)"infors");
							inFors = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{
							xmlChar* _item = xmlGetProp(curNode, (const xmlChar*)"prestige");
							prestige = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money")) {
							/* 读取任务金钱奖励属性 */
							xmlChar *_taskGold = xmlGetProp(curNode, (const xmlChar*)"money");
							taskGold = atoi(reinterpret_cast<const char*>(_taskGold));
							xmlFree(_taskGold);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"experience")) {
							/* 读取任务经验奖励属性 */
							xmlChar *_taskExp= xmlGetProp(curNode, (const xmlChar*)"experience");
							taskExp = atoi(reinterpret_cast<const char*>(_taskExp));
							xmlFree(_taskExp);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"giveType")) {
							/* 读取任务奖励物品方式属性 */
							xmlChar *_giveType= xmlGetProp(curNode, (const xmlChar*)"giveType");
							giveType = atoi(reinterpret_cast<const char*>(_giveType));
							xmlFree(_giveType);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"frequency")) {
							if (taskType == 2) {
								/* 读取任务一天可接次数属性 */
								xmlChar *_freq= xmlGetProp(curNode, (const xmlChar*)"frequency");
								freq = atoi(reinterpret_cast<const char*>(_freq));
								xmlFree(_freq);
							}
						}
					}
					
					//读task的子节点need 和 give
					for (childNode = curNode->xmlChildrenNode; childNode != NULL; childNode = childNode->next)
					{
						if (!xmlStrcmp(childNode->name, (const xmlChar*)"need"))
						{	//读task的need子节点的属性
							int need_type;
							char need_id[51];
							int need_num;	
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* 读任务类型 */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									need_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* 读任务完成需要怪物或物品id */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(need_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* 完成任务需要数量 */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									need_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							need_t *need = new need_t(need_type, need_id, need_num); //实例need 结构
							taskNeed.push_back(need);
							
						}  else if (!xmlStrcmp(childNode->name, (const xmlChar*)"give")) {	
							//读task的give子节点的属性
							int give_type;
							char give_id[51];
							int give_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* 读任务奖励类型 */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									give_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* 读任务奖励物品id */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(give_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* 奖励数量 */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									give_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							give_t *give = new give_t(give_type, give_id, give_num); //实例give 结构
							taskGive.insert(give);
							
						} else if (!xmlStrcmp(childNode->name, (const xmlChar*)"touch")) {	
							//读task的touch子节点的属性
							int touch_type;
							char touch_id[51];
							int touch_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* 读任务触发类型 */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									touch_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* 读任务触发物品id */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(touch_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* 数量暂时未确定其功能 */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									touch_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							touch_t *touch = new touch_t(touch_type, touch_id, touch_num); //实例touch 结构
						
							taskTouch.insert(touch);
						}  else if (!xmlStrcmp(childNode->name, (const xmlChar*)"recv")) {	
							//读task的touch子节点的属性
							int recv_type;
							char recv_id[51];
							int recv_num;
							for (attrPtr = childNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type"))
								{	
									/* 读任务触发类型 */
									xmlChar *_type = xmlGetProp(childNode, (const xmlChar*)"type");
									recv_type = atoi(reinterpret_cast<const char *>(_type));
									xmlFree(_type);
							
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id")) {	
									/* 读任务触发物品id */
									xmlChar *_id = xmlGetProp(childNode, (const xmlChar*)"id");
									strncpy(recv_id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);	
									xmlFree(_id);
									
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"num")) {
									/* 数量暂时未确定其功能 */
									xmlChar *_num = xmlGetProp(childNode, (const xmlChar *)"num");
									recv_num = atoi(reinterpret_cast<const char *>(_num));
									xmlFree(_num);
								
								}
							}
							
							recv_t *recv = new recv_t(recv_type, recv_id, recv_num); //实例give 结构
							taskRecv.insert(recv);
						}
					} /* end of for 遍历task子节点 */
					
					/* 实例一个task_conf */
					Task_Configuration *task_conf = new Task_Configuration(taskId, taskName,
					recNpcId, finNpcId, freq, taskType, inFors, prestige, taskGold, taskExp, giveType, taskChapt, taskLevel,
					taskNeed, taskGive, taskTouch, taskRecv, subType, isLastOfThisChapt);
						
					id_to_task[taskId] = task_conf;
					taskNeed.clear();
					taskGive.clear();
					taskTouch.clear();
					taskRecv.clear();
					//cout<<"read taskId of "<<taskId<<endl;
					
				} /* end of if 节点为task */
				
			} /* end of for 节点遍历 */
		} /* end of for chapt */
	}	/*end of for type */
	//cout<<"&&&&&&&&&&&&&&&&&&&&&&::::"<<id_to_task.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}