#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern Ride_Special_Skill_Config rideSpecialSkill_config[3];
int read_files_rideSpecialSkill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	int id;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"part"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"id");
					id=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"number");
					rideSpecialSkill_config[id].number = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost1"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost1");
					rideSpecialSkill_config[id].openCost[0] = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost2"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost2");
					rideSpecialSkill_config[id].openCost[1] = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost3"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost3");
					rideSpecialSkill_config[id].refreshCost[0] = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost4"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost4");
					rideSpecialSkill_config[id].refreshCost[1] = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost5"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost5");
					rideSpecialSkill_config[id].refreshCost[2] = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"freeTimes"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"freeTimes");
					rideSpecialSkill_config[id].freeNumber = atoi((char*)cTem);
					xmlFree(cTem);
				}	
			}
			int i=0;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"skill"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"flag"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"flag");
							rideSpecialSkill_config[id].skill[i].flag = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rate")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"rate");
							rideSpecialSkill_config[id].skill[i].rate = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"freeRate")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"freeRate");
							rideSpecialSkill_config[id].skill[i].freeRate = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"min")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"min");
							rideSpecialSkill_config[id].skill[i].min = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							rideSpecialSkill_config[id].skill[i].max = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"color"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"color");
							rideSpecialSkill_config[id].skill[i].color = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
					}
					i++;	
				}
			}							
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
