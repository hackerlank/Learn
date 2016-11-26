#include"function_read_configuration_files.h"
#include "data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern EveryDaySignRewardData signRewardData[30];
int read_files_everyDaySignReward(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

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
	
	int i=0;
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"reward"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"id");
					signRewardData[i].day=atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"day:"<<signRewardData[i].day<<endl;
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"number");
					signRewardData[i].number = atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"number:"<<signRewardData[i].number<<endl;
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid"))
				{	
					memset(signRewardData[i].goodsid,0,sizeof(signRewardData[i].goodsid));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"goodsid");
					strncpy(signRewardData[i].goodsid, (char*)cTem, sizeof (signRewardData[i].goodsid));
					xmlFree(cTem);
					// cout<<"goodsid:"<<signRewardData[i].goodsid<<endl;
				}	
			}
			i++;
		}
	}
		
	xmlFreeDoc(doc);
	return 0;
}
