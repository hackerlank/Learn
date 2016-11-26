#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<iostream>
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern RankReward rankReward;
int read_files_rankReward(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"heroRank"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"reward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id1"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id1");
							strncpy(rankReward.heroRank[0],(char*)cTem,sizeof(rankReward.heroRank[0]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id2")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id2");
							strncpy(rankReward.heroRank[1],(char*)cTem,sizeof(rankReward.heroRank[1]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id3")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id3");
							strncpy(rankReward.heroRank[2],(char*)cTem,sizeof(rankReward.heroRank[2]));
							xmlFree(cTem);
						} 
					}
				}
			}							
		}
		else if (!xmlStrcmp(secondNode->name, (const xmlChar*)"petRank"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"reward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id1"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id1");
							strncpy(rankReward.petRank[0],(char*)cTem,sizeof(rankReward.petRank[2][0]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id2")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id2");
							strncpy(rankReward.petRank[1],(char*)cTem,sizeof(rankReward.petRank[2][1]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id3")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id3");
							strncpy(rankReward.petRank[2],(char*)cTem,sizeof(rankReward.petRank[2][2]));
							xmlFree(cTem);
						} 
					}
				}
			}	
		}
		else if (!xmlStrcmp(secondNode->name, (const xmlChar*)"rideRank"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"reward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id1"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id1");
							strncpy(rankReward.rideRank[0],(char*)cTem,sizeof(rankReward.rideRank[0]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id2")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id2");
							strncpy(rankReward.rideRank[1],(char*)cTem,sizeof(rankReward.rideRank[1]));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id3")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"id3");
							strncpy(rankReward.rideRank[2],(char*)cTem,sizeof(rankReward.rideRank[2]));
							xmlFree(cTem);
						} 
					}
				}
			}	
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
