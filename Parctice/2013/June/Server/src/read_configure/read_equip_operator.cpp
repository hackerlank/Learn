#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<string.h>
#include<iostream>
#include<map>
using namespace std;
extern Equip_Operator equip_operator[51];
int read_files_equipOperator(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	int level=0;
	int rongLianPer=0;
	int rongLianAdd=0;
	int kaiRenAdd=0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"operator"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"level");
					level=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rongLianPer"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"rongLianPer");
					rongLianPer=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rongLianAdd"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"rongLianAdd");
					rongLianAdd=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"kaiRenAdd"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"kaiRenAdd");
					kaiRenAdd=atoi((char*)cTem);
					xmlFree(cTem);
				}
			}				
		}
		equip_operator[level].rongLianPer=rongLianPer;			
		equip_operator[level].rongLianAdd=rongLianAdd;			
		equip_operator[level].kaiRenAdd=kaiRenAdd;			
	}
	xmlFreeDoc(doc);
	return 0;
}
