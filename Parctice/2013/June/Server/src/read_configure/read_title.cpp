#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"wholeDefine.h"
extern set<string>allTitle;
using namespace std;

int read_title(char *fileName)
{

	xmlDocPtr doc;              
	xmlNodePtr curNode;
	xmlChar *carrier;
	char szDocName[50]={0};
	
	char id[ALLTITLELEN];
	int number;
	int times;
	string mapId;
	
	
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
		return -3;
	}
	
	//xml的相关变量
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;

	
	//循环读取xml的子节点，并取出相对应的内容	

		if(!xmlStrcmp(curNode->name,(const xmlChar *)"title"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
		
			if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
			{
			
				carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"id");
				strcpy(id ,const_cast<char *>(reinterpret_cast<const char *>(carrier)));		
			
				char *pch = strtok (id,"|");
				char titleId[20] = {'\0'};
				while (pch != NULL)
				{					
					strncpy(titleId,pch,strlen(pch));
					allTitle.insert(titleId);
					pch = strtok (NULL, "|");	
				}

				xmlFree(carrier);
			}
			
		}

	// for(set<string>::iterator i=allTitle.begin();i!=allTitle.end();++i)
	// {
		
		// cout<<*i<<endl;
	// }  
	xmlFreeDoc(doc);
	return 0;
}