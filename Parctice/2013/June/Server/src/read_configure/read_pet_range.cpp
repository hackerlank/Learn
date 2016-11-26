#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<iostream>
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern Pet_ZhanLi pet_zhanli[10];
extern Pet_Xidian pet_xidian;
int read_files_petRange(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"partA"))
		{
			int i=0;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"range"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							pet_zhanli[i].max = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"number")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"number");
							pet_zhanli[i].number = atoi((char*)cTem);
							xmlFree(cTem);
						} 
					}
					i++;	
				}
			}							
		}
		else if (!xmlStrcmp(secondNode->name, (const xmlChar*)"partB"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"cost");
					pet_xidian.cost=atoi((char*)cTem);
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"charge"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"charge");
					pet_xidian.charge = atoi((char*)cTem);
					xmlFree(cTem);
				}	
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"outattackval"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"min"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"min");
							pet_xidian.outAttVal.min = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.outAttVal.min:"<<pet_xidian.outAttVal.min<<endl;
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							pet_xidian.outAttVal.max = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.outAttVal.max:"<<pet_xidian.outAttVal.max<<endl;
						} 
					}	
				}
				else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"inattackval"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"min"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"min");
							pet_xidian.inAttVal.min = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.inAttVal.min:"<<pet_xidian.inAttVal.min<<endl;
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							pet_xidian.inAttVal.max = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.inAttVal.max:"<<pet_xidian.inAttVal.max<<endl;
						} 
					}
				}
				else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"hit"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"min"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"min");
							pet_xidian.hit.min = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.hit.min:"<<pet_xidian.hit.min<<endl;
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							pet_xidian.hit.max = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.hit.max:"<<pet_xidian.hit.max<<endl;
						} 
					}
				}
				else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"crit"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"min"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"min");
							pet_xidian.crit.min = atoi((char*)cTem);
							xmlFree(cTem);
							// cout<<"pet_xidian.crit.min:"<<pet_xidian.crit.min<<endl;
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"max")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"max");
							pet_xidian.crit.max = atoi((char*)cTem);
							// cout<<"pet_xidian.crit.max:"<<pet_xidian.crit.max<<endl;
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
