#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string.h>
#include"towerLayerRecord.h"

using namespace std;

extern map<string,map<string,string> >towerMapConf;

int read_black_margin(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;
	xmlNodePtr towerNode;
	xmlNodePtr layerNode;
	xmlAttrPtr attrPtr;    //节点属性值
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER); //解析文件
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
	
	for (towerNode = rootNode->xmlChildrenNode; towerNode != NULL; towerNode = towerNode->next)
	{
		string towerId;
		
		map<string,string>layerMap;
		
		if (!xmlStrcmp (towerNode->name, (const xmlChar*)"tower"))
		{
			xmlChar *_towerId = xmlGetProp(towerNode, (const xmlChar *)"towerId");
			towerId = reinterpret_cast<const char *>(_towerId);
			xmlFree(_towerId);
		}
		
		//遍历子节点
		for (layerNode = towerNode->xmlChildrenNode; layerNode != NULL; layerNode = layerNode->next)
		{			
			if (!xmlStrcmp (layerNode->name, (const xmlChar*)"layer"))
			{
				string layerId,cpyId;
				bool layerFlg = false;
				
				for (attrPtr = layerNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
				{
					if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"layerId"))
					{	
						xmlChar *_layerId = xmlGetProp(layerNode, (const xmlChar *)"layerId");
						layerId = reinterpret_cast<const char *>(_layerId);
						// cout<<"layerId:"<<layerId<<endl;
						xmlFree(_layerId);							
						
					} 
					
					else if (!xmlStrcmp (attrPtr->name, (const xmlChar*)"cpyId"))
					{
						xmlChar *_cpyId = xmlGetProp(layerNode, (const xmlChar *)"cpyId");
						cpyId = reinterpret_cast<const char *>(_cpyId);
						xmlFree(_cpyId);	
						// cout<<"cpyId:"<<cpyId<<endl;						
						layerFlg = true;
					}
					
					if(layerFlg)
					{
						layerFlg = false;
						layerMap[layerId] = cpyId;				
						// cout<<"layerId:"<<layerId<<" cpyId:"<<cpyId<<endl;
						layerId.clear();
						cpyId.clear();
					}
				}			
						
				
			}
		}
		
		towerMapConf[towerId] = layerMap;
		
		towerId.clear();
		
		layerMap.clear();
	}	
	xmlFreeDoc(doc);
	
	/*测试黑木崖配置读取是否成功*/
	testTowerLayerConf();
	
	return 0;
}