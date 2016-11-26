#include"function_read_configuration_files.h"
#include"ride_config.h"
#include<libxml/parser.h>
#include<string.h>
#include<map>
using namespace std;
extern map<string,string> cdkey_to_goodsid;
int read_files_cdkey(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	
	string key;
	string goodsid;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"item"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"key"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"key");
					key = (char*)cTem;
					xmlFree(cTem);
				}
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsid"))
				{	
					cTem = xmlGetProp(secondNode, (const xmlChar*)"goodsid");
					goodsid = (char*)cTem;
					xmlFree(cTem);
				}	
			}		
			cout<<"key:"<<key<<endl;
			cout<<"goodsid:"<<goodsid<<endl;
			cdkey_to_goodsid.insert(map<string,string>::value_type(key,goodsid));
		}
	}
	xmlFreeDoc(doc);
	return 0;
}
