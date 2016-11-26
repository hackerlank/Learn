#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<string.h>
#include<iostream>
#include<map>
using namespace std;
extern VIPRewardData vipRewardData[20];
int read_files_vip(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	int stage=0;
	int recharge;
	int store;
	int warehouse;
	int flyTimes;
	int callTimes;
	int lixianTimes;
	char bagId[20]={0};
	int lianxuTimes;
	int monTimes;
	int dazuoTimes;
	int guildTimes;
	int muscleTimes;
	int buyTimes;
	int midasTimes;
	int remidasTimes;
	int fubenRate;
	int refreshTimes;
	int freshNumber;
	int zuoqiFresh;
	int zuoqiNumber;
	int zuoqiRate;
	int rongLianRate;
	
	//解析文件
	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER);
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
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"vip"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				// if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				// {	
					// cTem = xmlGetProp(secondNode, (const xmlChar*)"id");
					// stage=atoi((char*)cTem);
					// xmlFree(cTem);
					// cout<<"stage:"<<stage<<endl;
				// }
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"recharge"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"recharge");
					recharge=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"store"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"store");
					store=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"warehouseFlag"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"warehouseFlag");
					warehouse=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"flyTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"flyTimes");
					flyTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"callTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"callTimes");
					callTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lixianTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"lixianTimes");
					lixianTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"bagId"))
				{	
					memset(bagId,0,sizeof(bagId));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"bagId");
					strncpy(bagId,(char*)cTem,sizeof(bagId));
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lianxuTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"lianxuTimes");
					lianxuTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"monTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"monTimes");
					monTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"dazuoTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"dazuoTimes");
					dazuoTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"guildTimes");
					guildTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"muscleTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"muscleTimes");
					muscleTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"buyTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"buyTimes");
					buyTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"midasTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"midasTimes");
					midasTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"remidasTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"remidasTimes");
					remidasTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fubenRate"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"fubenRate");
					fubenRate=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"refreshTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"refreshTimes");
					refreshTimes=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"freshNumber"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"freshNumber");
					freshNumber=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"zuoqiFresh"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"zuoqiFresh");
					zuoqiFresh=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"zuoqiNumber"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"zuoqiNumber");
					zuoqiNumber=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"zuoqiRate"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"zuoqiRate");
					zuoqiRate=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"jinglianRate"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"jinglianRate");
					rongLianRate=atoi((char*)cTem);
					xmlFree(cTem);
				}
			}
			// cout<<"stage:"<<stage<<endl<<endl;
			vipRewardData[stage].recharge=recharge;			
			vipRewardData[stage].store=store;			
			vipRewardData[stage].warehouse=warehouse;			
			vipRewardData[stage].flyTimes=flyTimes;			
			vipRewardData[stage].callTimes=callTimes;			
			vipRewardData[stage].lixianTimes=lixianTimes;			
			strncpy(vipRewardData[stage].bagId,bagId,sizeof(vipRewardData[stage].bagId));			
			vipRewardData[stage].lianxuTimes=lianxuTimes;			
			vipRewardData[stage].monTimes=monTimes;			
			vipRewardData[stage].dazuoTimes=dazuoTimes;			
			vipRewardData[stage].guildTimes=guildTimes;			
			vipRewardData[stage].muscleTimes=muscleTimes;			
			vipRewardData[stage].buyTimes=buyTimes;			
			vipRewardData[stage].midasTimes=midasTimes;			
			vipRewardData[stage].remidasTimes=remidasTimes;			
			vipRewardData[stage].fubenRate=fubenRate;			
			vipRewardData[stage].refreshTimes=refreshTimes;			
			vipRewardData[stage].freshNumber=freshNumber;			
			vipRewardData[stage].zuoqiFresh=zuoqiFresh;			
			vipRewardData[stage].zuoqiNumber=zuoqiNumber;			
			vipRewardData[stage].zuoqiRate=zuoqiRate;			
			vipRewardData[stage].rongLianRate=rongLianRate;		
			stage++;				
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
