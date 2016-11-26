#include"function_read_configuration_files.h"
#include"mysteriousBussiness_config.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,MysteriousBussiness_Config*> stage_to_mysteriousBussiness;
int read_files_mysteriousBussiness(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char stage[5]={'\0'};
	int number;
	string goodsid;
	string money;
	string percent;
	int wnumber;
	string wgoodsid;
	int wpercent;
	int bnumber;
	string bgoodsid;
	int bpercent;
	int pnumber;
	string pgoodsid;
	int ppercent;
	
	int i = 0;	

	map<int,string> drop_goods_id;
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"stage"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(stage,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(stage));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"number"))
				{
					cTem= xmlNodeGetContent(curNode);
					number=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsid"))
				{
					cTem= xmlNodeGetContent(curNode);
					goodsid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money"))
				{
					cTem= xmlNodeGetContent(curNode);
					money=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"percent"))
				{
					cTem= xmlNodeGetContent(curNode);
					percent=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);					
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wnumber"))
				{
					cTem= xmlNodeGetContent(curNode);
					wnumber=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgoodsid"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgoodsid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);	
				
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wpercent"))
				{
					cTem= xmlNodeGetContent(curNode);
					wpercent=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"bnumber"))
				{
					cTem= xmlNodeGetContent(curNode);
					bnumber=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"bgoodsid"))
				{
					cTem= xmlNodeGetContent(curNode);
					bgoodsid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"bpercent"))
				{
					cTem= xmlNodeGetContent(curNode);
					bpercent=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"pnumber"))
				{
					cTem= xmlNodeGetContent(curNode);
					pnumber=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"pgoodsid"))
				{
					cTem= xmlNodeGetContent(curNode);
					pgoodsid=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ppercent"))
				{
					cTem= xmlNodeGetContent(curNode);
					ppercent=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	

					MysteriousBussiness_Config *mysteriousBussiness_config; 
					vector<string> gen_goodsid;
					vector<int> gen_money;
					vector<int> gen_percent;
					vector<string> white_goodsid;
					vector<string> blue_goodsid;
					vector<string> purple_goodsid;
					
					string b=";";
					string d="";
					string str="";
					int i;
					for(i=0;i<goodsid.size();i++)
					{
						d.push_back(goodsid[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							gen_goodsid.push_back(str);
							str = "";
						}
						d="";
					}	
					for(i=0;i<money.size();i++)
					{
						d.push_back(money[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							gen_money.push_back(atoi(str.c_str()));
							str = "";
						}
						d="";
					}	
					for(i=0;i<percent.size();i++)
					{
						d.push_back(percent[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							gen_percent.push_back(atoi(str.c_str()));
							str = "";
						}
						d="";
					}		
					for(i=0;i<wgoodsid.size();i++)
					{
						d.push_back(wgoodsid[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							white_goodsid.push_back(str);
							str = "";
						}
						d="";
					}		
					for(i=0;i<bgoodsid.size();i++)
					{
						d.push_back(bgoodsid[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							blue_goodsid.push_back(str);
							str = "";
						}
						d="";
					}		
					for(i=0;i<pgoodsid.size();i++)
					{
						d.push_back(pgoodsid[i]);
						if(b != d)
						{
							str.append(d);
						}else{			
							purple_goodsid.push_back(str);
							str = "";
						}
						d="";
					}	
					mysteriousBussiness_config = new MysteriousBussiness_Config(stage,number,gen_goodsid,gen_money,gen_percent,wnumber,white_goodsid,wpercent,bnumber,blue_goodsid,bpercent,pnumber,purple_goodsid,ppercent);
					stage_to_mysteriousBussiness.insert(map<string,MysteriousBussiness_Config*>::value_type(stage,mysteriousBussiness_config));
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
