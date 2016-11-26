#include"function_read_configuration_files.h"
#include"ride_config.h"
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern map<string,Ride_Config*> id_to_ride;
int read_files_ride(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	char identity[20]={0};
	char nickName[50]={0};
	int quality;
	int level;
	int expMax;
	int lifeUpperVal;
	int magicUpperVal;
	int outAttack;
	int inAttack;
	int outDef;
	int inDef;
	int hited;
	int crit;
	int dodge;
	int tenacity;
	int move;
	int evolutionMax;
	int expTimes;
	int skill001;
	int skill002;
	int skill003;
	int skill004;
	int skill005;
	int skill006;
	int skill007;
	int skill008;
	int skill009;
	int skill010;
	char photoId[20]={0};
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"ride"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					memset(identity,0,sizeof(identity));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(identity, (char*)cTem, sizeof (identity));
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"quality"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"quality");
					quality = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_103"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_103");
					skill001 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_104"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_104");
					skill002 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_105"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_105");
					skill003 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_106"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_106");
					skill004 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_101"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_101");
					skill005 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_102"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_102");
					skill006 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_107"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_107");
					skill007 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_108"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_108");
					skill008 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_109"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_109");
					skill009 = atoi((char*)cTem);
					xmlFree(cTem);
				}		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"b_zq_124_110"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"b_zq_124_110");
					skill010 = atoi((char*)cTem);
					xmlFree(cTem);
				}	
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"photoId"))
				{	
					memset(photoId,0,sizeof(photoId));
					cTem = xmlGetProp(secondNode, (const xmlChar*)"photoId");
					strncpy(photoId, (char*)cTem, sizeof (photoId));
					xmlFree(cTem);
				}
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"attribute"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"level");
							level = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"name")) 
						{
							memset(nickName,0,sizeof(nickName));					
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"name");
							strncpy(nickName, (char*)cTem, sizeof (nickName));
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"expMax")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"expMax");
							expMax = atoi((char*)cTem);
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lifeUpperVal")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"lifeUpperVal");
							lifeUpperVal = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"magicUpperVal"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"magicUpperVal");
							magicUpperVal = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outAttack"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"outAttack");
							outAttack = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inAttack"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"inAttack");
							inAttack = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outDef"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"outDef");
							outDef = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inDef"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"inDef");
							inDef = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hited"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"hited");
							hited = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"crit")) 
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"crit");
							crit = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"dodge"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"dodge");
							dodge = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tenacity"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"tenacity");
							tenacity = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"move"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"move");
							move = atoi((char*)cTem);							
							xmlFree(cTem);
						} 
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"evolutionMax"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"evolutionMax");
							evolutionMax = atoi((char*)cTem);							
							xmlFree(cTem);
						}
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"expTimes"))
						{
							cTem = xmlGetProp(thirdNode, (const xmlChar*)"expTimes");
							expTimes = atoi((char*)cTem);							
							xmlFree(cTem);
							
						}
					}
					char rideIdentity[30]={0};
					snprintf(rideIdentity,sizeof(rideIdentity),"%s%d%d",identity,quality,level);
					Ride_Config *ride=new Ride_Config(quality,expMax,lifeUpperVal,magicUpperVal,outAttack,inAttack,outDef,inDef,hited,crit,dodge,tenacity,move,evolutionMax,expTimes,skill001,skill002,skill003,skill004,skill005,skill006,skill007,skill008,skill009,skill010,photoId,nickName);
					id_to_ride.insert(map<string,Ride_Config*>::value_type(rideIdentity,ride));		
				}
			}							
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
