#include <iostream>
#include <libxml/parser.h>
#include <string.h>
#include "function_read_configuration_files.h"
extern char sendName[30];
extern char sendTitle[30];
extern char sendFlower[1024];
extern char receiveFlower[1024];
extern char recharge[1024];
extern char consume[1024];
extern char heroRankContent[1024];
extern char petRankContent[1024];
extern char rideRankContent[1024];
extern char shutDownContent[1024];
using namespace std;
int read_files_words(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

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
	
	memset(sendName,0,sizeof(sendName));
	memset(sendTitle,0,sizeof(sendTitle));
	memset(sendFlower,0,sizeof(sendFlower));
	memset(receiveFlower,0,sizeof(receiveFlower));
	memset(recharge,0,sizeof(recharge));
	memset(consume,0,sizeof(consume));
	memset(heroRankContent,0,sizeof(heroRankContent));
	memset(petRankContent,0,sizeof(petRankContent));
	memset(rideRankContent,0,sizeof(rideRankContent));

    for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{		
		if(!xmlStrcmp(secondNode->name, (const xmlChar*)"sendName"))
        {
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*)"name"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*)"name");
				strncpy(sendName,(char*)cTem,sizeof(sendName));
				xmlFree(cTem);
			}					
        } 		
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "sendTitle"))
        {
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "title"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "title");
				strncpy(sendTitle,(char*)cTem,sizeof(sendTitle));
				xmlFree(cTem);
			}					
        }		
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "sendFlower"))
        {
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(sendFlower,(char*)cTem,sizeof(sendFlower));
				xmlFree(cTem);
			}						
        }		
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "receiveFlower"))
        {
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(receiveFlower,(char*)cTem,sizeof(receiveFlower));
				xmlFree(cTem);
			}						
        }				
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "recharge"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(recharge,(char*)cTem,sizeof(recharge));
				xmlFree(cTem);
			}				
		}		
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "consume"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(consume,(char*)cTem,sizeof(consume));
				xmlFree(cTem);
			}
		}	
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "heroRank"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(heroRankContent,(char*)cTem,sizeof(heroRankContent));
				xmlFree(cTem);
			}
		}	
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "petRank"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(petRankContent,(char*)cTem,sizeof(petRankContent));
				xmlFree(cTem);
			}
		}	
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "rideRank"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(rideRankContent,(char*)cTem,sizeof(rideRankContent));
				xmlFree(cTem);
			}
		}
		else if(!xmlStrcmp(secondNode->name, (const xmlChar*) "shutDown"))
		{
			if(!xmlStrcmp(secondNode->properties->name, (const xmlChar*) "content"))
			{
				cTem = xmlGetProp(secondNode,(const xmlChar*) "content");
				strncpy(shutDownContent,(char*)cTem,sizeof(shutDownContent));
				xmlFree(cTem);
			}
		}
    }   
	
	// cout<<"sendName:"<<sendName<<endl;
	// cout<<"sendTitle:"<<sendTitle<<endl;
	// cout<<"sendFlower:"<<sendFlower<<endl;
	// cout<<"receiveFlower:"<<receiveFlower<<endl;
	// cout<<"recharge:"<<recharge<<endl;
	// cout<<"consume:"<<consume<<endl;
	
    xmlFreeDoc(doc);
	return 0;
}

