//读大厅服务器配置
#include"readConf.h"
#include"gameSer.h"
#include<libxml/parser.h>
GameSer* readGameSer(const char *fileName)
{
	xmlDocPtr doc = xmlReadFile(fileName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		exit(0);
	}
	//得到xml文件的root
	xmlNodePtr curNode = xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		exit(0);
	}
	char ip[IPADDR] = {'\0'};
    char name[SERNAME] = {'\0'};
    size_t port;
    size_t upperNum;
    bool flg = false;
    GameSer *gameSer = NULL;
	curNode = curNode->xmlChildrenNode;	
    xmlChar *val;
	while(curNode)
	{
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"gameSer"))
		{
			xmlAttrPtr attrPtr = curNode->properties;
			while(attrPtr)
			{	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"ip"))
				{
					val = xmlGetProp(curNode,(const xmlChar*)"ip");
                    strncpy(ip,reinterpret_cast<const char*>(val),sizeof(ip));	
                    xmlFree(val);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					val = xmlGetProp(curNode,(const xmlChar*)"name");
                    strncpy(name,reinterpret_cast<const char*>(val),sizeof(name));	
                    xmlFree(val);
				}
                else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"port"))
				{
					val = xmlGetProp(curNode,(const xmlChar*)"port");
                    int portFlg = atoi(reinterpret_cast<const char*>(val));
                    xmlFree(val);
                    if(portFlg <= 0)
                    {
                        perror("gameSer port error");
                        exit(0);
                    }
                    port = portFlg;				
				}
                else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"upperNum"))
				{
					val = xmlGetProp(curNode,(const xmlChar*)"upperNum");
                    int upperNumFlg = atoi(reinterpret_cast<const char*>(val));
                    xmlFree(val);
                    if(upperNumFlg <= 0)
                    {
                        perror("gameSer upperNumFlg error");
                        exit(0);
                    }
                    upperNum = upperNumFlg;
                    flg = true;
				}						
				if(flg)
				{
                    try
                    {
                        gameSer = new GameSer(ip,name,port,upperNum);
                    }
                    catch(...)
                    {
                        perror("readGameSer error gameSer NULL");
                        delete gameSer;
                        gameSer = NULL;
                    }
                    
					cout<<"ip:"<<ip <<"port:"<<port<<endl;
                    memset(ip,'\0',sizeof(ip));
                    memset(name,'\0',sizeof(name));
                    port = 0;
                    upperNum = 0;
                    break;
				}			
				attrPtr = attrPtr->next;				
			}	
		}
		curNode = curNode->next;
        if(flg)
        {
            break;
        }
	}
    xmlFreeDoc(doc);
    return gameSer;
}
