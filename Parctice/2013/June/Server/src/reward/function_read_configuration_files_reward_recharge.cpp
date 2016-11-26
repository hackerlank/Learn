#include"function_read_configuration_files.h"
#include"reward_recharge_config.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<int,Reward_recharge_config*>id_to_reward_recharge;
map<string,Reward_recharge_config*> sid_to_reward_recharge;//added by benliao 2012.01.03
int read_files_reward_recharge(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
		
	string sid;
	int type;							//累计充值数量
	int flag;							//金币类型
	int money;							//奖励金钱数量
	int repeat;							//奖励送的物品占用的格子数量
	int num;							//goodsid的数目
	char goodsid[1024]={'\0'};							//包含goodsid和赠送的数量
	int loop=0;

	map<int,string> drop_goods_id;
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
                                {
                                        cTem= xmlNodeGetContent(curNode);
                                        sid = const_cast<char *>(reinterpret_cast<const char *>(cTem));
                                        xmlFree(cTem);
                                }

				if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"flag"))
				{
					cTem= xmlNodeGetContent(curNode);
					flag=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money"))
				{
					cTem= xmlNodeGetContent(curNode);
					money=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"repeat"))
				{
					cTem= xmlNodeGetContent(curNode);
					repeat=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"number"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(goodsid,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(goodsid));
					xmlFree(cTem);	
					Reward_recharge_config *reward_recharge_config; 
					reward_recharge_config = new Reward_recharge_config(type,flag,money,repeat,num,goodsid);
					id_to_reward_recharge.insert(map<int,Reward_recharge_config*>::value_type(loop,reward_recharge_config));
					loop++;
					sid_to_reward_recharge.insert(map<string,Reward_recharge_config*>::value_type(sid,reward_recharge_config));//added by benliao 2013.1.3
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
