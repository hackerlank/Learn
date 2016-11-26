#include<iostream>
#include<string.h>
#include<map>
#include<libxml/parser.h>

#include"vip.h"
#include"hero.h"
#include"function_read_configuration_files.h"

using namespace std;

extern map<string ,VipDataInitial> vipDataStore;

int read_vip(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	xmlChar *carrier;
	char szDocName[50]={0};
	
	strncpy(szDocName,fileName,strlen(fileName));
		
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -1;
	}
	
	//循环读取xml的子节点，并取出相对应的内容	
	for(curNode = curNode->xmlChildrenNode; curNode != NULL; curNode = curNode->next)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"vip"))
		{
			VipDataInitial vipDataInitial;
			xmlNodePtr propNodePtr_item = curNode;
			xmlAttrPtr attrPtr = propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*vip id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"id");
					// cout<<"get vip id = "<<carrier<<endl;
				//	id = const_cast<char *>(reinterpret_cast<const char *>(carrier));	
					memset(vipDataInitial.id, 0, 13);
					strncpy(vipDataInitial.id, reinterpret_cast<const char *>(carrier), 13);
					xmlFree(carrier);
				}
				/*vip卡持续时间*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lastTime"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"lastTime");
					// cout<<"get vip lastTime = "<<carrier<<endl;
					vipDataInitial.lastTime = atoi(reinterpret_cast<const char *>(carrier));
					// cout<<"get vip lastTime second:"<<vipDataInitial.lastTime<<endl;
					xmlFree(carrier);
				}
				
				/*vip 头衔*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"title"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"title");
					// cout<<"get vip title = "<<carrier<<endl;
				//	title = const_cast<char *>(reinterpret_cast<const char *>(carrier));				
					memset(vipDataInitial.title, 0, 13);
					strncpy(vipDataInitial.title, reinterpret_cast<const char *>(carrier), 13);
					xmlFree(carrier);
				}
				
				/*保留数据1*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"invalid1"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"invalid1");
					// cout<<"get vip invalid1 = "<<carrier<<endl;
					vipDataInitial.invalid1 = atoi(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				
				/*保留数据2*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"invalid2"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"invalid2");
					// cout<<"get vip invalid2 = "<<carrier<<endl;
					vipDataInitial.invalid2 = atoi(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				/*保留数据3*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"invalid3"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"invalid3");
					// cout<<"get vip invalid3 = "<<carrier<<endl;
					vipDataInitial.invalid3 = atoi(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				/*保留数据4*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"invalid4"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"invalid4");
					// cout<<"get vip invalid4 = "<<carrier<<endl;
					vipDataInitial.invalid4 = atoi(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				/* vip每日获得的物品类型ID */
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"giftBagId"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"giftBagId");
					// cout<<"get vip giftBagId = "<<carrier<<endl;
				//	giftBagId = const_cast<char *>(reinterpret_cast<const char *>(carrier));
					memset(vipDataInitial.giftBagId, 0, 13);
					strncpy(vipDataInitial.giftBagId, reinterpret_cast<const char *>(carrier), 13);
					xmlFree(carrier);		
				}
				//modified by bison move it out
				//vipDataStore.insert(pair<string ,VipDataInitial>(vipDataInitial.id, vipDataInitial));
				attrPtr = attrPtr->next;	
			}
			//modified by bison
			vipDataStore.insert(pair<string ,VipDataInitial>(vipDataInitial.id, vipDataInitial));
		}
	}

	// cout<<"@@Tory:after read vip_config,vipDataStore.size():"<<vipDataStore.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
















