#include"function_read_configuration_files.h"
#include "data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern NewTimeData newTimeData;
int read_files_reward_time(char *fileName)
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
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"reward"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"time"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"time");
					newTimeData.time=atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"time:"<<newTimeData.time<<endl;
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"repeat"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"repeat");
					newTimeData.repeat = atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"repeat:"<<newTimeData.repeat<<endl;
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"number");
					newTimeData.number = atoi((char*)cTem);
					xmlFree(cTem);
					// cout<<"number:"<<newTimeData.number<<endl;
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid"))
				{	
					memset(newTimeData.goodsid,0,sizeof(newTimeData.goodsid));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"goodsid");
					strncpy(newTimeData.goodsid, (char*)cTem, sizeof (newTimeData.goodsid));
					xmlFree(cTem);
					// cout<<"goodsid:"<<newTimeData.goodsid<<endl;
				}	
			}
		}
	}
	
	// cout<<endl<<endl;
	// cout<<"newTimeData.time:"<<newTimeData.time<<endl;
	// cout<<"repeat:"<<newTimeData.repeat<<endl;
	// cout<<"number:"<<newTimeData.number<<endl;
	// cout<<"goodsid:"<<newTimeData.goodsid<<endl;
	
	xmlFreeDoc(doc);
	return 0;
}
