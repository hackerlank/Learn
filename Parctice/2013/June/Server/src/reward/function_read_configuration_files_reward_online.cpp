#include"function_read_configuration_files.h"
#include"reward_online_config.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;
extern map<string,Reward_online_config*> id_to_reward_online;
int read_files_reward_online(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
		
	char stage[20]={'\0'};							//阶段
	int time;							//时间
	vector<int> moneyPercent;			//随即游戏币概率
	vector<int> moneyNum;				//随即游戏币数量

	vector<int> goldPercent;			//随即元宝概率
	vector<int> goldNum;				//随即元宝数量
	
	vector<int> goodsPercent;			//随即物品概率
	vector<string> goodsid;				//随即物品id

	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curnow=curnow->xmlChildrenNode;
	
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
		int num=0;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"stage"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(stage,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(stage));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time"))
				{
					cTem= xmlNodeGetContent(curNode);
					time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyPercent1"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money1"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyPercent2"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money2"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyPercent3"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money3"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyPercent4"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money4"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyPercent5"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money5"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}
				
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldPercent1"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold1"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldPercent2"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold2"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldPercent3"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold3"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldPercent4"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold4"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}			
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldPercent5"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold5"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldNum.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent1"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid1"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent2"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid2"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent3"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid3"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent4"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid4"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent5"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid5"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent6"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid6"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent7"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid7"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent8"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid8"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent9"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid9"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsPercent10"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsPercent.push_back(atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem))));			
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid10"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid.push_back(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				
					Reward_online_config *reward_online_config; 
					reward_online_config = new Reward_online_config(stage,time,moneyPercent,moneyNum,goldPercent,goldNum,goodsPercent,goodsid);
					id_to_reward_online.insert(map<string,Reward_online_config*>::value_type(stage,reward_online_config));
					moneyPercent.clear();			//随即游戏币概率
					moneyNum.clear();				//随即游戏币数量

					goldPercent.clear();			//随即元宝概率
					goldNum.clear();				//随即元宝数量
					
					goodsPercent.clear();			//随即物品概率
					goodsid.clear();				//随即物品id
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
