/****************************************************************
 * Filename: read_dirty_words.cpp
 * 
 * Description: 读取非法词汇
 *
 * Original Author : bison, 2012-10-11
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

extern set<string> dirtyWordsPack;					//脏词库
extern set<string> illegalCharPack;					//命名非法符号

int read_dirty_words(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	string dirty;						//脏词
	string illegal;						//非法字符

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
	
	illegalCharPack.clear();
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"illegality"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取脏词
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"illegalityChat"))
				{
					cTem = xmlNodeGetContent(thirdNode);
					dirty = const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				
				}
				//读取命名非法字符
				else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"illegalityName"))
				{
					cTem = xmlNodeGetContent(thirdNode);
					illegal = const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
					illegalCharPack.insert(illegal);
				}
			}
			
		}
	}
	
	dirtyWordsPack.clear();
	int pos = 0;
	string oneDirtyWords;
	while (!dirty.empty())
	{
		pos = dirty.find(',');
		if (pos == -1)
		{
			//防止最后一个没加逗号
			oneDirtyWords = dirty;
			dirty = "";
		} else {
			oneDirtyWords = dirty.substr(0, pos);
			dirty = dirty.substr(pos + 1);
		}
		dirtyWordsPack.insert(oneDirtyWords);
	}
	
	// cout<<"BisonTest: the dirty dictionary has "<<dirtyWordsPack.size()<<" dirty words"<<endl;
	// cout<<"BisonTest: @read_dirty_words.cpp: "<<"illegalChars size is "<<illegalCharPack.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}