#include"function_read_configuration_files.h"
#include"pet_config.h"
#include<libxml/parser.h>
#include<string.h>
using namespace std;
extern map<string,Pet_Config*> id_to_pet; 
int read_files_pet(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char  id[20]={'\0'};
	char  nickName[50]={'\0'};
	char normal[20]={0};
	char nextid[50]={0};
	char nextGenid[50]={0};
	int flag;
	int level;
	int limit;
	int expTimes;
	int range;
	int outAttackVal;
	int outAttackValRate;
	int inAttackVal;
	int inAttackValRate;
	int hit;
	int hitRate;
	int crit;
	int critRate;
	int generation;
	int quality;
	int needNumber;
	int needCount;
	int type;
	char photoId[20];

	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curnow=curnow->xmlChildrenNode;
	
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
		int num=0;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}
			while(curNode != NULL)
			{			
				int len;
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"petid"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(id,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(id));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nickname"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(nickName,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(nickName));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nextid"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(nextid,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(nextid));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nextgenid"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(nextGenid,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(nextGenid));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"level"))
				{
					cTem= xmlNodeGetContent(curNode);
					level=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"limit"))
				{
					cTem= xmlNodeGetContent(curNode);
					limit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"exptimes"))
				{
					cTem= xmlNodeGetContent(curNode);
					expTimes=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"flag"))
				{
					cTem= xmlNodeGetContent(curNode);
					flag=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"outattackval"))
				{
					cTem= xmlNodeGetContent(curNode);
					outAttackVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"oavcrease"))
				{
					cTem= xmlNodeGetContent(curNode);
					outAttackValRate=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"inattackval"))
				{
					cTem= xmlNodeGetContent(curNode);
					inAttackVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"iavcrease"))
				{
					cTem= xmlNodeGetContent(curNode);
					inAttackValRate=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"hit"))
				{
					cTem= xmlNodeGetContent(curNode);
					hit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"hcrease"))
				{
					cTem= xmlNodeGetContent(curNode);
					hitRate=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"crit"))
				{
					cTem= xmlNodeGetContent(curNode);
					crit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ccrease"))
				{
					cTem= xmlNodeGetContent(curNode);
					critRate=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);			
				}			
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"generate"))
				{
					cTem= xmlNodeGetContent(curNode);
					generation=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				}			
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"quality"))
				{
					cTem= xmlNodeGetContent(curNode);
					quality=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				}		
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"range"))
				{
					cTem= xmlNodeGetContent(curNode);
					range=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"normal"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(normal,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(normal));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"needNumber"))
				{
					cTem= xmlNodeGetContent(curNode);
					needNumber=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);		
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"needCount"))
				{
					cTem= xmlNodeGetContent(curNode);
					needCount=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);		
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);		
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"photoId"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(photoId,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(photoId));
					xmlFree(cTem);						
					Pet_Config *pet; 
					pet = new Pet_Config(id,nickName,level,limit,outAttackVal,outAttackValRate,inAttackVal,inAttackValRate,hit,hitRate,crit,critRate,generation,quality,type,range,photoId,normal,flag,expTimes,needNumber,needCount,nextid,nextGenid);			
					id_to_pet.insert(map<string,Pet_Config*>::value_type(id,pet));
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
