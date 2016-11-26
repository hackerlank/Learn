#include"function_read_configuration_files.h"
#include"droplist_configuration.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,DropList_Configuration*> id_to_dropgoods; 
int read_files_droplist(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char stage[20]={'\0'};
	int percent;
	int drugper;
	int drugnum;
	string drugid;
	int toolper;
	int toolnum;
	string toolid;
	int wequipper;
	int wequipnum;
	string wequipid;
	int bequipper;
	int bequipnum;
	string bequipid;
	int pequipper;
	int pequipnum;
	string pequipid;
	int pkequipper;
	int pkequipnum;
	string pkequipid;
	int oequipper;
	int oequipnum;
	string oequipid;

	
	int i = 0;
	string b = ";";
	string d;
	string str;


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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"Stage"))
				{
					int len;
					cTem= xmlNodeGetContent(curNode);
					// len=strlen(reinterpret_cast<const char *>(cTem));
					// stage=new char[len+1];
					strncpy(stage,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(stage));
					// stage[len]='\0';
					xmlFree(cTem);	
					// cout<<stage<<endl;
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"Percent"))
				{
					cTem= xmlNodeGetContent(curNode);
					percent=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"DrugPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					drugper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"DrugNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					drugnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"DrugId"))
				{
					cTem= xmlNodeGetContent(curNode);
					drugid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ToolPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					toolper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ToolNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					toolnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ToolId"))
				{
					cTem= xmlNodeGetContent(curNode);
					toolid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"WEquipPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					wequipper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"WEquipNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					wequipnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"WEquipId"))
				{
					cTem= xmlNodeGetContent(curNode);
					wequipid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"BEquipPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					bequipper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"BEquipNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					bequipnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"BEquipId"))
				{
					cTem= xmlNodeGetContent(curNode);
					bequipid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PEquipPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					pequipper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PEquipNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					pequipnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PEquipId"))
				{
					cTem= xmlNodeGetContent(curNode);
					pequipid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);			
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PkEquipPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					pkequipper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PkEquipNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					pkequipnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"PkEquipId"))
				{
					cTem= xmlNodeGetContent(curNode);
					pkequipid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"OEquipPer"))
				{
					cTem= xmlNodeGetContent(curNode);
					oequipper=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"OEquipNum"))
				{
					cTem= xmlNodeGetContent(curNode);
					oequipnum=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"OEquipId"))
				{
					cTem= xmlNodeGetContent(curNode);
					oequipid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
					
					map<int,string> drop_goods_id;
					drop_goods_id.clear();
					string test=drugid+toolid+wequipid+bequipid+pequipid+pkequipid+oequipid;
					int num=0;
					for(i=0;i<test.size();i++)
					{
						d.push_back(test[i]);
						if(b != d)
						{
							str.append(d);
						}else{		
							// cout<<str<<endl;
							drop_goods_id.insert(map<int,string>::value_type(num,str));
							str = "";
							num++;
						}
						d="";
					}	
					// cout<<drop_goods_id.size()<<endl;
					// map<int,string>::iterator id_it;
					// for (id_it=drop_goods_id.begin();id_it!=drop_goods_id.end();id_it++);
					// {
						// cout<<"goodsid:"<<id_it->second<<endl;
					// }
					DropList_Configuration *droplist; 
					droplist = new DropList_Configuration(stage,percent,drugper,drugnum,toolper,toolnum,
						wequipper,wequipnum,bequipper,bequipnum,pequipper,pequipnum,
						pkequipper,pkequipnum,oequipper,oequipnum,drop_goods_id);
					id_to_dropgoods.insert(map<string,DropList_Configuration*>::value_type(stage,droplist));
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
