#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<iostream>
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern WuLinTargetConfig wuLinTargetConfig[10];
int read_files_reward_target(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	int flag=0;
	char targetGoodsid[20]={0};
	int targetNumber=0;
	int id;
	char goodsid[20]={0};
	int number=0;
	int totalNumber=0;
	
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"targets"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"flag"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"flag");
					flag=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid"))
				{	
					memset(targetGoodsid,0,sizeof(targetGoodsid));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"goodsid");
					strncpy(targetGoodsid ,(char*)cTem,sizeof(targetGoodsid));
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"number");
					targetNumber = atoi((char*)cTem);
					xmlFree(cTem);
				}	
			}
			if (flag<0||flag>9)
			{
				cout<<"read_wulintarget error flag:"<<flag<<endl;
				break;
			}
			strncpy(wuLinTargetConfig[flag].goodsid,targetGoodsid,sizeof(wuLinTargetConfig[flag].goodsid));
			wuLinTargetConfig[flag].number=targetNumber;
			totalNumber=0;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				totalNumber++;
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id");
							id = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid")) 
						{
							memset(goodsid,0,sizeof(goodsid));					
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"goodsid");
							strncpy(goodsid, (char*)cTem, sizeof (goodsid));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"number");
							number = atoi((char*)cTem);
							xmlFree(cTem);
						}
					}			
					if (id<0||id>49)
					{	
						cout<<"read_wulintarget error id:"<<id<<endl;
						break;
					}
					strncpy(wuLinTargetConfig[flag].wuLinTargeItemtConfig[id].goodsid,goodsid,sizeof(wuLinTargetConfig[flag].wuLinTargeItemtConfig[id].goodsid));
					wuLinTargetConfig[flag].wuLinTargeItemtConfig[id].number=number;
				}
			}	
			wuLinTargetConfig[flag].totalNumber=totalNumber;
			
			// cout<<"flag:"<<flag<<endl;
			// cout<<"totalNumber:"<<totalNumber<<endl;
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
