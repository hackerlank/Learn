#include"function_read_configuration_files.h"
#include"suit.h"
#include<libxml/parser.h>
#include<string>
#include<iostream>
#include<map>
extern map<string,Suit*> suit_lists;
using namespace std;
int read_files_suit(char *fileName)
{
xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string suit_id;				//套装Id
	int	   type;				//套装类别
	string suit_name;			//套装名称
	int	   hp;					//套装提升生命值的数值
	int    mp;					//套装提升真气值的数值
	int    outHrt;				//套装提升外功伤害的数值
	int    inHrt;				//套装提升内功伤害的数值
	int    outAttVal;			//套装提升外功攻击的数值
	int    inAttVal;			//套装提升内功攻击的数值
	int    outDefVal;			//套装提升外功防御的数值
	int    inDefVal;			//套装提升内功防御的数值
	int    hit;					//套装提升的命中的数值
	int    crit;				//套装提升的暴击的数值
	int    dodge;				//套装提升的闪避的数值
	int    tenacity;			//套装提升的韧性的数值
	
	//读取skill_zhudong配置文件
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
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"suit_id"))
				{
					cTem= xmlNodeGetContent(curNode);
					suit_id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"suit_name"))
				{
					cTem= xmlNodeGetContent(curNode);
					suit_name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"hp"))
				{
					cTem= xmlNodeGetContent(curNode);
					hp=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"mp"))
				{
					cTem= xmlNodeGetContent(curNode);
					mp=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"outHrt"))
				{
					cTem= xmlNodeGetContent(curNode);
					outHrt=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"inHrt"))
				{
					cTem= xmlNodeGetContent(curNode);
					inHrt=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"outAttVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					outAttVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"inAttVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					inAttVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"outDefVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					outDefVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"inDefVal"))
				{
					cTem= xmlNodeGetContent(curNode);
					inDefVal=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"hit"))
				{
					cTem= xmlNodeGetContent(curNode);
					hit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"crit"))
				{
					cTem= xmlNodeGetContent(curNode);
					crit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"dodge"))
				{
					cTem= xmlNodeGetContent(curNode);
					dodge=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"tenacity"))
				{
					cTem= xmlNodeGetContent(curNode);
					tenacity=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Suit *suit = new Suit(suit_id,type,suit_name,hp,mp,outHrt,inHrt,outAttVal,inAttVal,outDefVal,inDefVal,hit,crit,dodge,tenacity);
					suit_lists[suit_id] = suit;
				}			
				curNode=curNode->next;	
			}
			
				
		curnow=curnow->next;
	}
	// cout<<"####################################################################"<<endl;
	// cout<<"the size of lists is :"<<suit_lists.size()<<endl;
	// cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
	
}
