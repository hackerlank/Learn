#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"data_structure_struct.h"
#include"monster_configuration.h"
#include<iostream>
#include<string.h>
#include<map>
using namespace std;
extern map<string,Monster_Inform*>monTypeId_connect_property;
int read_files_monster(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	doc = NULL;
	curNode = NULL;
	//读取怪物配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{				
		xmlFreeDoc(doc);
		return -3;
	}
	
	//循环读取xml的子节点，并取出相对应的内容
	string typeId ;
	string nickName;
	string photoId;	
	double lifeUpperVal;
	double lifeVal;
	
	int magicUpperVal = 100;
	int magicVal = 100;
	
	string kind;
	string type;
	double rank;
	
	int attRange;	//攻击范围		
	int moveRange;		//行走范围
	int hrtSud;      //秒伤
	double outHrt;     //外伤
	double inHrt;      //内伤
	double outAttVal;    //外功攻击值
	double inAttVal;    //内功攻击值
	double outDefVal;    //外功防御值
	double inDefVal;    //内功防御值
	int defSumVal;   //防御值总和
	double hit;        //命中
	double crit;       //暴击
	double voids;      //闪避
	double tenacity;       //韧性	
	int hatRange;      //仇恨范围
	int failGoodsLess;   //怪物掉落最大值
	int failGoodsMost;   //怪物掉落最大值
	int hatVal;      //仇恨值
	int gold;       //金币
	set<string> failList;  //掉落列表
	string goodId;
	string stage;
	int radius = 0;
	double cdTime = 0.0;	//cd时间
	int flgMonster = 0;             //标志变量
	int experience;
	int angVal;             //怒气值
	string skiId;           //技能id
	vector<string> skiIdSet; //技能id列表
	int speed;               //移动速度
	
	int fiveEleInt = 6;      //五行属性代表值
	int fiveEleRank = 0;     //五行等级值
	int fiveHurt = 0;        //五行伤害值
	int goFor;
	int expTme;          
	int monyTme;
	int ownerAttriType = 0;            //类型，帮派为1，阵营为2，其余的暂为0
	string ownerAttri = "-1";
	string genAttId = "0";   //默认值
	double attackRatio = 0.5;          //击杀红名怪按比例来算
	
	bool isInnerAttack = false;          //偏内功为真，偏外功为假
	
	xmlAttrPtr attrPtr;
	Monster_Inform *mon_type_properity;
	flgMonster = -1;
	monyTme = 1;
	for(curNode=curNode->xmlChildrenNode;curNode!=NULL;curNode=curNode->next)
	{
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"monster"))
		{			
			for(attrPtr=curNode->properties;attrPtr!=NULL;attrPtr=attrPtr->next)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{	
					int len;
					xmlChar *_typeId=xmlGetProp(curNode,(const xmlChar*)"typeId");
					typeId = "MP";
					typeId  += reinterpret_cast<const char *>(_typeId);
					xmlFree(_typeId);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"type"))
				{	
					int len;
					xmlChar *_type=xmlGetProp(curNode,(const xmlChar*)"type");
					type = reinterpret_cast<const char *>(_type);
					xmlFree(_type);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"kind"))
				{	
					int len;
					xmlChar *_kind=xmlGetProp(curNode,(const xmlChar*)"kind");
					kind = reinterpret_cast<const char *>(_kind);
					xmlFree(_kind);
				}				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank"))
				{
					xmlChar *_rank=xmlGetProp(curNode,(const xmlChar*)"rank");
					rank=atof(reinterpret_cast<const char *>(_rank));
					xmlFree(_rank);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"nickName"))
				{	
					int len;
					xmlChar *_nickName=xmlGetProp(curNode,(const xmlChar*)"nickName");
					nickName = reinterpret_cast<const char *>(_nickName);	
					xmlFree(_nickName);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeUpperVal"))
				{
					xmlChar *_lifeUpperVal=xmlGetProp(curNode,(const xmlChar*)"lifeUpperVal");
					lifeUpperVal=atof(reinterpret_cast<const char *>(_lifeUpperVal));
					xmlFree(_lifeUpperVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeVal"))
				{
					xmlChar *_lifeVal=xmlGetProp(curNode,(const xmlChar*)"lifeVal");
					lifeVal=atof(reinterpret_cast<const char *>(_lifeVal));
					xmlFree(_lifeVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"getHrtSud"))
				{
					xmlChar *_getHrtSud=xmlGetProp(curNode,(const xmlChar*)"getHrtSud");
					hrtSud=atoi(reinterpret_cast<const char *>(_getHrtSud));
					xmlFree(_getHrtSud);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"outHrt"))
				{
					xmlChar *_outHrt=xmlGetProp(curNode,(const xmlChar*)"outHrt");
					outHrt=atof(reinterpret_cast<const char *>(_outHrt));
					xmlFree(_outHrt);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"inHrt"))
				{
					xmlChar *_inHrt=xmlGetProp(curNode,(const xmlChar*)"inHrt");
					inHrt=atof(reinterpret_cast<const char *>(_inHrt));
					xmlFree(_inHrt);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"outAttVal"))
				{
					xmlChar *_outAttVal=xmlGetProp(curNode,(const xmlChar*)"outAttVal");
					outAttVal=atof(reinterpret_cast<const char *>(_outAttVal));
					xmlFree(_outAttVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"inAttVal"))
				{
					xmlChar *_inAttVal=xmlGetProp(curNode,(const xmlChar*)"inAttVal");
					inAttVal=atof(reinterpret_cast<const char *>(_inAttVal));
					xmlFree(_inAttVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"outDefVal"))
				{
					xmlChar *_outDefVal=xmlGetProp(curNode,(const xmlChar*)"outDefVal");
					outDefVal=atof(reinterpret_cast<const char *>(_outDefVal));
					xmlFree(_outDefVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"inDefVal"))
				{
					xmlChar *_inDefVal=xmlGetProp(curNode,(const xmlChar*)"inDefVal");
					inDefVal=atof(reinterpret_cast<const char *>(_inDefVal));
					xmlFree(_inDefVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"defSumVal"))
				{
					xmlChar *_defSumVal=xmlGetProp(curNode,(const xmlChar*)"defSumVal");
					defSumVal=atoi(reinterpret_cast<const char *>(_defSumVal));
					xmlFree(_defSumVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hit"))     //此处是否为int或者double，待定
				{
					xmlChar *_hit=xmlGetProp(curNode,(const xmlChar*)"hit");
					hit=atof(reinterpret_cast<const char *>(_hit));
					xmlFree(_hit);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"crit"))  
				{
					/*此处是否为int或者double，待定*/
					xmlChar *_crit=xmlGetProp(curNode,(const xmlChar*)"crit");
					crit=atof(reinterpret_cast<const char *>(_crit));
					xmlFree(_crit);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"void"))
				{
					xmlChar *_void=xmlGetProp(curNode,(const xmlChar*)"void");
					voids=atof(reinterpret_cast<const char *>(_void));
					xmlFree(_void);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"tenacity"))
				{
					xmlChar *_tenacity=xmlGetProp(curNode,(const xmlChar*)"tenacity");
					tenacity=atof(reinterpret_cast<const char *>(_tenacity));
					xmlFree(_tenacity);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"moveRange"))
				{
					xmlChar *_moveRange=xmlGetProp(curNode,(const xmlChar*)"moveRange");
					moveRange=atoi(reinterpret_cast<const char *>(_moveRange));
					xmlFree(_moveRange);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hatRange"))
				{
					xmlChar *_hatRange=xmlGetProp(curNode,(const xmlChar*)"hatRange");
					hatRange=atoi(reinterpret_cast<const char *>(_hatRange));
					xmlFree(_hatRange);
				}
			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"attRange"))
				{
					xmlChar *_attRange=xmlGetProp(curNode,(const xmlChar*)"attRange");
					attRange=atoi(reinterpret_cast<const char *>(_attRange));
					xmlFree(_attRange);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"failGoodsless"))
				{
					xmlChar *_failGoodsless=xmlGetProp(curNode,(const xmlChar*)"failGoodsless");
					failGoodsLess=atoi(reinterpret_cast<const char *>(_failGoodsless));
					xmlFree(_failGoodsless);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"failGoodsmost"))
				{
					xmlChar *_failGoodsmost=xmlGetProp(curNode,(const xmlChar*)"failGoodsmost");
					failGoodsMost=atoi(reinterpret_cast<const char *>(_failGoodsmost));
					xmlFree(_failGoodsmost);
				}
			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hatVal"))
				{
					xmlChar *_hatVal=xmlGetProp(curNode,(const xmlChar*)"hatVal");
					hatVal=atoi(reinterpret_cast<const char *>(_hatVal));
					xmlFree(_hatVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"angVal"))
				{
					xmlChar *_angVal=xmlGetProp(curNode,(const xmlChar*)"angVal");
					angVal=atoi(reinterpret_cast<const char *>(_angVal));
					xmlFree(_angVal);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId1"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId1");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId2"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId2");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId3"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId3");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId4"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId4");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"skillId5"))
				{
					xmlChar *_skiId=xmlGetProp(curNode,(const xmlChar*)"skillId5");
					skiId=reinterpret_cast<const char *>(_skiId);
					xmlFree(_skiId);
					if(skiId.length() > 1)
					{
						skiIdSet.push_back(skiId);
					}
						
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"genAttId"))
				{
					xmlChar *_genAttId=xmlGetProp(curNode,(const xmlChar*)"genAttId");
					genAttId=reinterpret_cast<const char *>(_genAttId);
					xmlFree(_genAttId);
						
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"gold"))
				{
					xmlChar *_gold=xmlGetProp(curNode,(const xmlChar*)"gold");
					gold=atoi(reinterpret_cast<const char *>(_gold));
					xmlFree(_gold);
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					int len;
					xmlChar *_photoId=xmlGetProp(curNode,(const xmlChar*)"photoId");
					photoId = reinterpret_cast<const char *>(_photoId);
					xmlFree(_photoId);
				
				}		
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"radius"))
				{
					xmlChar *_radius=xmlGetProp(curNode,(const xmlChar*)"radius");
					radius=atoi(reinterpret_cast<const char *>(_radius));
					xmlFree(_radius);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"experience"))
				{
					xmlChar *_experience=xmlGetProp(curNode,(const xmlChar*)"experience");
					experience=atof(reinterpret_cast<const char *>(_experience));
					xmlFree(_experience);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cdTime"))
				{
					xmlChar *_cdTime=xmlGetProp(curNode,(const xmlChar*)"cdTime");
					cdTime=atof(reinterpret_cast<const char *>(_cdTime));
					xmlFree(_cdTime);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"stage"))
				{				
					int len;
					xmlChar *_stage=xmlGetProp(curNode,(const xmlChar*)"stage");
					stage = reinterpret_cast<const char *>(_stage);
					xmlFree(_stage);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"fiveEleInt"))
				{
					xmlChar *_fiveEleInt=xmlGetProp(curNode,(const xmlChar*)"fiveEleInt");
					fiveEleInt=atoi(const_cast<char *>(reinterpret_cast<const char *>(_fiveEleInt)));
					xmlFree(_fiveEleInt);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"fiveHurt"))
				{
					xmlChar *_fiveHurt=xmlGetProp(curNode,(const xmlChar*)"fiveHurt");
					fiveHurt=atoi(const_cast<char *>(reinterpret_cast<const char *>(_fiveHurt)));
					xmlFree(_fiveHurt);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"fiveEleRank"))
				{
					xmlChar *_fiveEleRank=xmlGetProp(curNode,(const xmlChar*)"fiveEleRank");
					fiveEleRank=atoi(const_cast<char *>(reinterpret_cast<const char *>(_fiveEleRank)));
					xmlFree(_fiveEleRank);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goFor"))
				{
					xmlChar *_goFor=xmlGetProp(curNode,(const xmlChar*)"goFor");
					goFor=atoi(const_cast<char *>(reinterpret_cast<const char *>(_goFor)));
					xmlFree(_goFor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"expTme"))
				{
					xmlChar *_expTme=xmlGetProp(curNode,(const xmlChar*)"expTme");
					expTme=atoi(const_cast<char *>(reinterpret_cast<const char *>(_expTme)));
					xmlFree(_expTme);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"monTme"))
				{
					xmlChar *_monyTme=xmlGetProp(curNode,(const xmlChar*)"monTme");
					monyTme=atoi(const_cast<char *>(reinterpret_cast<const char *>(_monyTme)));
					xmlFree(_monyTme);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"ownerAttriType"))
				{
					xmlChar *_ownerType=xmlGetProp(curNode,(const xmlChar*)"ownerAttriType");
					ownerAttriType=atoi(const_cast<char *>(reinterpret_cast<const char *>(_ownerType)));
					xmlFree(_ownerType);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"ownerAttri"))
				{				
					xmlChar *_typeValue=xmlGetProp(curNode,(const xmlChar*)"ownerAttri");
					ownerAttri = const_cast<char *>(reinterpret_cast<const char *>(_typeValue));
					xmlFree(_typeValue);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isInnerAttack"))
				{				
					xmlChar *_isInnerAttack=xmlGetProp(curNode,(const xmlChar*)"isInnerAttack");
					int innerValues = atoi(const_cast<char *>(reinterpret_cast<const char *>(_isInnerAttack)));
					xmlFree(_isInnerAttack);
					if(innerValues == 1)
					{
						isInnerAttack = true;
					}
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"attackRatio"))
				{				
					xmlChar *_attackRatio=xmlGetProp(curNode,(const xmlChar*)"attackRatio");
					attackRatio=atof(const_cast<char *>(reinterpret_cast<const char *>(_attackRatio)));
					xmlFree(_attackRatio);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"speed"))
				{
					lifeVal = lifeUpperVal;
					xmlChar *_speed=xmlGetProp(curNode,(const xmlChar*)"speed");
					speed=atoi(const_cast<char *>(reinterpret_cast<const char *>(_speed)));
					xmlFree(_speed);
					flgMonster = 1;
				}
				
				if(flgMonster == 1)
				{
					//srand ( time(NULL) );
					goFor = rand()%10;
					mon_type_properity = new Monster_Inform(const_cast<char*>(typeId.c_str()), const_cast<char*>(type.c_str()),\
					const_cast<char*>(kind.c_str()),rank,const_cast<char*>(nickName.c_str()),lifeUpperVal,lifeVal,magicUpperVal,\
					magicVal,hrtSud,outHrt,inHrt,outAttVal,inAttVal,outDefVal,inDefVal, defSumVal,hit,crit,voids,tenacity,moveRange,\
					hatRange,attRange,failGoodsLess,failGoodsMost,hatVal,angVal,skiIdSet,const_cast<char*>(genAttId.c_str()),gold,\
					failList,const_cast<char*>(photoId.c_str()),const_cast<char*>(stage.c_str()),experience,cdTime,fiveEleInt,fiveHurt,\
					fiveEleRank,goFor,expTme,monyTme,speed,ownerAttriType,const_cast<char*>(ownerAttri.c_str()),attackRatio,isInnerAttack,radius);	
										
					monTypeId_connect_property[typeId]=mon_type_properity;			
					skiIdSet.clear();
					flgMonster = 0;
				}
			}
			
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
