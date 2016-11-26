#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"skill_configuration.h"
#include<string>
//add to test.
#include <iostream>
using namespace std;
extern map<string,Skill_Configuration*>id_to_skill;

int read_files_zhudong(char * fileName) //主动攻击类型的技能基础数据的读取  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//技能Id
	string name;         		//技能名称
	int   type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
	int   effect;              //技能附加效果
	int   con_time;            //效果持续时间
	int   cd_time;             //技能cd（冷却时间）
	int	  factor;              //技能系数基础值
	int   genuine;             //真气消耗
	int	  time_sec;            //技能动画播放时间（秒）
	int   time_usec;           //技能动画播放时间（微秒） 
	int  nggjjdz_debuff;	    //debuff降低内功攻击
	int  wggjjdz_debuff;		//debuff降低外功攻击		
	int  ngfyjdz_debuff;		//debuff降低内功防御		
	int  wgfyjdz_debuff;		//debuff降低外功防御
	int  mzjd_debuff;			//debuff降低命中
	int  jdrx_debuff;			//debuff降低韧性
	int	 jdsb_debuff;			//debuff降低闪避
	int  jdbj_debuff;			//debuff降低暴击
	int  cxdx_debuff;			//持续掉血值
	int  attack_type;			//攻击形式
	int  attack_range;			//攻击距离
	int  genuine_growup;		//技能消耗成长参数
	int	 effect_growup;			//附加效果成长参数
	int	 factor_growup;		//技能系数成长参数
	int    control_grade;		//等级限制
	int    value1;
	int    value2;
	int    value3;
	
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"con_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					con_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nggjjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					nggjjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wggjjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					wggjjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ngfyjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					ngfyjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgfyjdz_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgfyjdz_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"mzjd_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					mzjd_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdrx_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdrx_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdsb_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdsb_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"jdbj_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					jdbj_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxdx_debuff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxdx_debuff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_sec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_sec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_usec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_usec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"attack_type"))
				{
					cTem= xmlNodeGetContent(curNode);
					attack_type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"attack_range"))
				{
					cTem= xmlNodeGetContent(curNode);
					attack_range=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,con_time,cd_time,factor,
													genuine,time_sec,time_usec,nggjjdz_debuff,wggjjdz_debuff,
													ngfyjdz_debuff,wgfyjdz_debuff,mzjd_debuff,jdrx_debuff,jdsb_debuff,
													jdbj_debuff,cxdx_debuff,attack_type,attack_range,effect_growup,
													genuine_growup,factor_growup,control_grade,value1,value2,value3);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}
			
				
		curnow=curnow->next;
	}
	////cout<<"####################################################################"<<endl;
	////cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	////cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}

int read_files_yiliao(char * fileName) //医疗类型的技能基础数据的读取  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//技能Id
	string name;         		//技能名称
	int    type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
	int    effect;              //技能附加效果
	int    con_time;            //效果持续时间
	int    cd_time;             //技能cd（冷却时间）
	int	   factor;              //技能系数基础值
	int    genuine;             //真气消耗
	int	   time_sec;            //技能动画播放时间（秒）
	int    time_usec;           //技能动画播放时间（微秒）
	int    cure_type;           //医疗形式：1，单体医疗；2，群体医疗	
	int	   factor_growup;		//技能系数成长参数 
	int    control_grade;		//等级限制
	int    value1;
	int    value2;
	int    value3;
	//读取skill_yiliao配置文件
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"con_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					con_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_cd"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cure_type"))
				{
					cTem= xmlNodeGetContent(curNode);
					cure_type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_sec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_sec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"time_usec"))
				{
					cTem= xmlNodeGetContent(curNode);
					time_usec=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"factor_growup"))
				{
					cTem= xmlNodeGetContent(curNode);
					factor_growup=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,con_time,cd_time,factor,genuine,
							time_sec,time_usec,cure_type,factor_growup,control_grade,value1);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	////cout<<"####################################################################"<<endl;
	////cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	////cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}

int read_files_buff(char * fileName) //buff类型的技能基础数据的读取  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//技能Id
	string name;         		//技能名称
	int    type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
	int    effect;              //技能附加效果
	int    cd_time;             //技能cd（冷却时间）
	int    genuine;             //真气消耗
	int   zjngshbfb_buff;        //buff增加内功伤害
	int   zjwgshbfb_buff;        //buff增加外功伤害
	int   zjsmsx_buff;        	 //buff增加生命上限
	int   ftsh_buff;             //反弹伤害
	int   smxh_buff;       		 //生命消耗
	int   xxl_buff;              //吸血率
	int   cxsjcz_buff;           //持续时间初值
	int	  consumer_growth;		 //技能消耗成长参数
	int   cxsjcz_growup_buff;	 //技能持续时间成长参数
	int   cd_growup_buff;		 //技能CD成长参数      
	int   xg_growup_buff;		 //技能效果成长
	int    control_grade;		//等级限制
	int    value1;
	int    value2;
	int    value3;
	//读取skill_yiliao配置文件
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"genuine"))
				{
					cTem= xmlNodeGetContent(curNode);
					genuine=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_time"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_time=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjngshbfb_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjngshbfb_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjwgshbfb_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjwgshbfb_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"zjsmsx_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					zjsmsx_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ftsh_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					ftsh_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"smxh_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					smxh_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"xxl_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					xxl_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxsjcz_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxsjcz_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"consumer_growth"))
				{
					cTem= xmlNodeGetContent(curNode);
					consumer_growth=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cxsjcz_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cxsjcz_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"cd_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					cd_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"xg_growup_buff"))
				{
					cTem= xmlNodeGetContent(curNode);
					xg_growup_buff=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,cd_time,genuine,zjngshbfb_buff,
							zjwgshbfb_buff,zjsmsx_buff,ftsh_buff,smxh_buff,xxl_buff,cxsjcz_buff,
							consumer_growth,cxsjcz_growup_buff,cd_growup_buff,xg_growup_buff,control_grade);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	//cout<<"####################################################################"<<endl;
	//cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	//cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;
}

int read_files_beidong(char * fileName) //被动类型的技能基础数据的读取  evan add 2012.5.25
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);	
	string id;           		//技能Id
	string name;         		//技能名称
	int    type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
	int    effect;              //技能附加效果
	int    smsxjdz_bd;          //附加生命上限
	int    wgshbfb_bd;          //附加外功伤害
	int    wggjbfb_bd;          //附加外功攻击
	int    nggjbfb_bd;          //附加内功攻击
	int    wgfybfb_bd;          //附加外功防御
	int    ngfybfb_bd;          //附加内功防御
	int    mzjdz_bd;            //附加命中
	int    bjjdz_bd;            //附加暴击
	int    sbjdz_bd;            //附加闪避
	int    rxjdz_bd;            //附加韧性
	int    fjxgcs_growup_bd;	//附加效果绝对值成长参数
	int    control_grade;		//等级限制
	int    value1;
	int    value2;
	int    value3;
	//读取skill_yiliao配置文件
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					name=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					effect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"smsxjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					smsxjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgshbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgshbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wggjbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wggjbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"nggjbfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					nggjbfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"wgfybfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					wgfybfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ngfybfb_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					ngfybfb_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"mzjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					mzjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"bjjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					bjjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"sbjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					sbjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"rxjdz_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					rxjdz_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"fjxgcs_growup_bd"))
				{
					cTem= xmlNodeGetContent(curNode);
					fjxgcs_growup_bd=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"control_grade"))
				{
					cTem= xmlNodeGetContent(curNode);
					control_grade=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value1"))
				{
					cTem= xmlNodeGetContent(curNode);
					value1=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value2"))
				{
					cTem= xmlNodeGetContent(curNode);
					value2=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"value3"))
				{
					cTem= xmlNodeGetContent(curNode);
					value3=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Skill_Configuration *skill;
					skill = new Skill_Configuration(id,name,type,effect,smsxjdz_bd,wgshbfb_bd,wggjbfb_bd,
							nggjbfb_bd,wgfybfb_bd,ngfybfb_bd,mzjdz_bd,bjjdz_bd,sbjdz_bd,
							rxjdz_bd,fjxgcs_growup_bd,control_grade);
					id_to_skill[id] = skill;
				}
				curNode=curNode->next;	
			}		
		curnow=curnow->next;
	}
	//cout<<"####################################################################"<<endl;
	//cout<<"the size of lists is :"<<id_to_skill.size()<<endl;
	//cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}
