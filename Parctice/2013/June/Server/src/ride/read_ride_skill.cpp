#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern RideSkill_Config rideSkill_config[10];
int read_files_rideSkill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	char id[18]={0};
	int value;
	int flag;
	int grade;
	int fullGrade;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"skill"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					memset(id,0,sizeof(id));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(id, (char*)cTem, sizeof (id));
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"value");
					value = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"flag"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"flag");
					flag = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"grade"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"grade");
					grade = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fullGrade"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"fullGrade");
					fullGrade = atoi((char*)cTem);
					xmlFree(cTem);
				}				
			}	
			strncpy(rideSkill_config[flag].id,id,sizeof(rideSkill_config[flag].id));
			rideSkill_config[flag].value=value;		
			rideSkill_config[flag].level=grade;		
			rideSkill_config[flag].levelMax=fullGrade;				
		}		
	}
	xmlFreeDoc(doc);
	return 0;
}
