/********************************************************************

    created:   2012/5/10

    filename: read_scene_config.cpp 

    author:       Tory 

    depend:       libxml2.lib 

*********************************************************************/
#include <libxml/parser.h>

#include <iostream>

#include <string.h>

#include "function_read_configuration_files.h"

using namespace std;

int read_scene_config(char *fileName)
{

    xmlDocPtr doc;           //解析文档指针

    xmlNodePtr curNode;      //当前结点指针 

    xmlChar *szKey;          //临时字符串变量

    char *szDocName = (char*)malloc(strlen(fileName)+1);

    strcpy(szDocName, fileName);

    doc = xmlReadFile(szDocName,"GB2312",XML_PARSE_RECOVER); //解析文件

    if(NULL == doc)
    {

        fprintf(stderr,"Document not parsed successfully.\n");     

        return -1; 

    }

    curNode = xmlDocGetRootElement(doc); //确定文档根元素

    //检查确认当前文档中包含内容

    if(NULL == curNode)
    {

        fprintf(stderr,"empty document\n"); 

        xmlFreeDoc(doc); 

        return -1; 

    }

    if(xmlStrcmp(curNode->name, BAD_CAST "root"))
    {

        fprintf(stderr,"document of the wrong type, root node != root"); 

        xmlFreeDoc(doc); 

        return -1; 

    }

    curNode = curNode->xmlChildrenNode;

    while(curNode != NULL)
    {

        //读取Hero配置文件路径
        if((!xmlStrcmp(curNode->name, (const xmlChar *)"scene")))
        {

            szKey = xmlNodeGetContent(curNode);
		
			read_files_map((char*)szKey);
		
	   	//	printf("in read_scene_config szKey: %s\n", szKey); 
            
			xmlFree(szKey); 

        }

        curNode = curNode->next; 

    } 

    free(szDocName);

    xmlFreeDoc(doc);

    return 0;

}
