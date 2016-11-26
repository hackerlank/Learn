/************************************************************
	文件名：read_monster_skill.cpp
	文件作用：读取副本所有限制的配置文件
	作者：chenzhen
	创建日期：2012.07.10
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"skillBase.h"
#include"recoverBlood.h"
#include"rigidity.h"
#include"unEnemy.h"
#include"monCallSkill.h"
extern map<string,SkillBase*> monster_skill_map;
int read_monster_skill(char *fileName)  
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;     //xml中间节点临时变量
	
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	
	if(NULL == doc)
	{
		return -1;
	}
	//得到xml文件的root
	curNode = xmlDocGetRootElement(doc);		
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_skill;
	string name;              //技能名称
	string id;                //技能id 
	int rank;                 //技能等级
	double relPer;        	 //释放频率
	double angVal;			 //触发技能怒气值
	double cdTime;           //cd时间	
	double trgPer;            //生命值触发条件
	int flgSkill;             //标志变量
	
	SkillBase *skill;         //技能实例指针
	double recoverLife;      //生命值恢复比例
	double lastTime;         //技能持续时间
	bool durance;           //是否为延时性技能
	double hrtRatio;        //技能伤害
	int during;
	double playCd;          //技能动画播放时间
	
	flgSkill = -1;
	
	/*默认为2秒*/
	playCd = 2;             
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"skill"))
		{
			propNodePtr_skill = curNode;
			xmlAttrPtr attrPtr = propNodePtr_skill->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取技能id属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
				{					
					xmlChar *_id = xmlGetProp(propNodePtr_skill,(const xmlChar*)"id");
					id = reinterpret_cast<const char *>(_id);
					xmlFree(_id);
				}
				
				/*读取技能名称属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{					
					xmlChar *_name = xmlGetProp(propNodePtr_skill,(const xmlChar*)"name");
					name = reinterpret_cast<const char *>(_name);
					xmlFree(_name);
				}
				
				/*读取技能等级限制属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank"))
				{					
					xmlChar *_rank = xmlGetProp(propNodePtr_skill,(const xmlChar*)"rank");
					rank = atoi(reinterpret_cast<const char *>(_rank));
					xmlFree(_rank);
				}
				
				/*读取技能触发频率属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"relPer"))
				{					
					xmlChar *_relPer = xmlGetProp(propNodePtr_skill,(const xmlChar*)"relPer");
					relPer = atof(reinterpret_cast<const char *>(_relPer));
					xmlFree(_relPer);
				}
				
				/*读取技能怒气值触发属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"angVal"))
				{					
					xmlChar *_angVal = xmlGetProp(propNodePtr_skill,(const xmlChar*)"angVal");
					angVal = atof(reinterpret_cast<const char *>(_angVal));
					xmlFree(_angVal);
				}
				/*读取技能cd时间*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cdTime"))
				{					
					xmlChar *_cdTime = xmlGetProp(propNodePtr_skill,(const xmlChar*)"cdTime");
					cdTime = atof(reinterpret_cast<const char *>(_cdTime));
					xmlFree(_cdTime);
				}
				/*读取技能播放时间*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"playCd"))
				{					
					xmlChar *_playCd = xmlGetProp(propNodePtr_skill,(const xmlChar*)"playCd");
					playCd = atof(reinterpret_cast<const char *>(_playCd));
					xmlFree(_playCd);
				}
				/*读取技能伤害系数*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hrtRatio"))
				{					
					xmlChar *_hrtRatio = xmlGetProp(propNodePtr_skill,(const xmlChar*)"hrtRatio");
					hrtRatio = atof(reinterpret_cast<const char *>(_hrtRatio));
					xmlFree(_hrtRatio);
				}
				/*读取技能是否为延时技能*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"during"))
				{					
					xmlChar *_during = xmlGetProp(propNodePtr_skill,(const xmlChar*)"during");
					during = atoi(reinterpret_cast<const char *>(_during));
					xmlFree(_during);
					durance = during ? true:false;
						
				}
				/*读取技能生命值比例触发属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"trgPer"))
				{					
					xmlChar *_trgPer = xmlGetProp(propNodePtr_skill,(const xmlChar*)"trgPer");
					trgPer = atof(reinterpret_cast<const char *>(_trgPer));
					xmlFree(_trgPer);
				}
				/*读取技能回复生命值比例属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"recoverLife"))
				{					
					xmlChar *_recoverLife = xmlGetProp(propNodePtr_skill,(const xmlChar*)"recoverLife");
					recoverLife = atof(reinterpret_cast<const char *>(_recoverLife));
					xmlFree(_recoverLife);
				}
				
				/*读取技能回复生命值比例属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lastTime"))
				{					
					xmlChar *_lastTime = xmlGetProp(propNodePtr_skill,(const xmlChar*)"lastTime");
					lastTime = atof(reinterpret_cast<const char *>(_lastTime));
					xmlFree(_lastTime);
					flgSkill = 1;
				}
			
				/*实例化Skill类*/
				if(flgSkill == 1)
				{
					flgSkill = 0;
					if(id.find("darkSukBld") != string::npos)
					{
						/*默认*/
						recoverLife = 0.1;
						skill = new RecoverBlood(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer,recoverLife);	
					}
					else if(id.find("proArms") != string::npos ||\
							id.find("delMethod") != string::npos ||\
							id.find("tightEncir") != string::npos)
					{
						skill = new Rigidity(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer,lastTime);
					}
					else if(id.find("dieHard") != string::npos)
					{
						skill = new UnEnemy(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,lastTime);
					}
					
					else if(id.find("callType") != string::npos)
					{
						skill = new MonCallSkill(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance,trgPer);
					}
					
					else
					{
						skill = new SkillBase(const_cast<char *>(name.c_str()),\
						const_cast<char *>(id.c_str()),rank,relPer,angVal,\
						cdTime,playCd,hrtRatio,durance);
						// cout<<"id:"<<id<<endl;
						// cout<<"relPer:"<<relPer<<endl;
					}
					
					monster_skill_map[id] = skill;
					
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
