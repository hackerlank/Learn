/****************************************************************
 * Filename: read_ectype_reward_goods.cpp
 * 
 * Description: 副本奖励的所有物品的配置读取方法
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//副本奖励物品的全局量
extern map<string, vector<string> > type_2_goodsList;

int read_ectype_reward_goods(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	char typeId[51];						//物品类型id

	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER); //解析文件
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Goods"))
		{
			xmlChar *_typeId = xmlGetProp(secondNode, (const xmlChar *)"typeId");
			strncpy(typeId, const_cast<char *>(reinterpret_cast<const char *>(_typeId)), 51);
			xmlFree(_typeId);
			
			//装备序列
			cTem = xmlNodeGetContent(secondNode);
			//物品id串
			string GoodsList = const_cast<char *>(reinterpret_cast<const char *>(cTem));
			xmlFree(cTem);
			string oneGoods;					//单个物品id
			int pos = 0;						//分隔号位置
			vector<string> temp;				//物品id列表
			//配置文件中是以分号隔开的物品id序列
			while (!GoodsList.empty())
			{
				pos = GoodsList.find(';');
				if (pos == -1)
				{
					//防止最后一个没加分号
					oneGoods = GoodsList;
					temp.push_back(oneGoods);
					break;
				}
				oneGoods = GoodsList.substr(0, pos);
				temp.push_back(oneGoods);
				GoodsList = GoodsList.substr(pos + 1);
			}
			type_2_goodsList.insert(pair<string,vector<string> >(typeId, temp));
		}
	}
	xmlFreeDoc(doc);
	/* 
	//测试副本物品奖励配置读取结果
	map<string,vector<string> >::iterator iter;
	//iter = type_2_goodsList.find("white020");
	for (iter = type_2_goodsList.begin(); iter != type_2_goodsList.end(); iter++)
	{
		cout<<iter->first<<endl;
		vector<string> goodsIdSet = iter->second;
		for (int i = 0; i < goodsIdSet.size(); i++)
			cout<<goodsIdSet[i]<<endl;
		cout<<endl;
	}
	*/
	
	return 0;
}