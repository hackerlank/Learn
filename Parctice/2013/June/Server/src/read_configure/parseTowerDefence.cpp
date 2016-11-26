/***********************************
    filename: parse_tower_defence_config.cpp 
    author:       Tory 
    depend:       libxml2.lib 
*************************************/
#include <libxml/parser.h>
#include <iostream>
#include <sstream>
#include "function_read_configuration_files.h"
// #include "TD_Instancing.h"
#include "instancing_manage.h"

//塔防配置信息
extern map<string, TD_Conf_T> id_2_tdConf;

using namespace std;

/*
 * str2int - string类型转成int类型
 * @str：要转换的string类型字符串
 * Return: 返回str对应的整数
 */
int str2int(string str)
{
    istringstream is(str);
    int n;
    is>>n;
    return n;

}
/*
 * str2pointSet - 字符串转换成二维坐标点集合 
 * @str: 所要转换的string类型字符串,str是一串的点坐标的字符串格式，
 * 		 点之间用分号隔开,点内x,y用逗号隔开
 * Return: 返回一个str对应的点集合
 */
vector<Point> str2pointSet(string str)
{
    vector<Point> pointSet;
    int pointX;
    int pointY;
    int pos = 0;

    while(!str.empty())
    {
        pos = str.find(',');
        pointX = str2int(str.substr(0, pos));
        str = str.substr(pos + 1);
        pos = str.find(';');
        pointY = str2int(str.substr(0,pos));
        str = str.substr(pos + 1);
        Point pt(pointX, pointY);
        pointSet.push_back(pt);
    }

    return pointSet;
}
       
vector<Point> str2pointSet1(string str)
{
    vector<Point> pointSet;
    int pointX;
    int pointY;
    int pos = 0;

    while(!str.empty())
    {
        pos = str.find(',');
        pointX = str2int(str.substr(0, pos));
        str = str.substr(pos + 1);
        pos = str.find(',');
        pointY = str2int(str.substr(0,pos));
        str = str.substr(pos + 1);
        Point pt(pointX, pointY);
        pointSet.push_back(pt);
    }

    return pointSet;


}

int parseTowerDefence(char *fileName)
{
    xmlDocPtr doc;           //定义解析文档指针
    xmlNodePtr curNode;      //定义结点指针(你需要它为了在各个结点间移动) 
    xmlChar *szKey;          //临时字符串变量

    char *szDocName = (char*)malloc(strlen(fileName)+1);
    strcpy(szDocName, fileName);
    doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER); //解析文件    
    if(NULL == doc)
    {
        fprintf(stderr,"Document not parsed successfully.\n");     

        return -1; 
    }
    curNode = xmlDocGetRootElement(doc); //确定文档根元素
    /*检查确认当前文档中包含内容*/ 
    if(NULL == curNode)
    {
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return -1; 
    }
    for(curNode=curNode->xmlChildrenNode; curNode != NULL; curNode=curNode->next)
    {
        Instancing_infor instancing_config_infor;
        Instancing_require instancing_config_require;
        Instancing_strategy instancing_config_strategy;
        vector<string> scenes_id_vec;     
        instancing_config_strategy.stand_point; 
        
        if(xmlStrcmp(curNode->name, BAD_CAST "instancing"))
        {
            fprintf(stderr,"document of the wrong type, instancing node != instancing\n"); 
            xmlFreeDoc(doc); 
            return -1; 
        } else
        {
            xmlNodePtr sonNodePtr = curNode->xmlChildrenNode;
            while(sonNodePtr != NULL)
            {
                if(!xmlStrcmp(sonNodePtr->name, BAD_CAST "instancing_infor"))
                {
                    xmlNodePtr propNodePtr = sonNodePtr;
                    xmlAttrPtr attrPtr1 = sonNodePtr->properties;

                    while(attrPtr1 != NULL)
                    {
                        if(!xmlStrcmp(attrPtr1->name, BAD_CAST "id"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "id");
                        //    cout<<"get id = "<<szAttr<<endl;
                            instancing_config_infor.id = reinterpret_cast<const char *>(szAttr);
                            
                            xmlFree(szAttr);
                        }
                        if(!xmlStrcmp(attrPtr1->name, BAD_CAST "name"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "name");
                        //    cout<<"get name = "<<szAttr<<endl;
                            instancing_config_infor.name = reinterpret_cast<const char *>(szAttr);
                            xmlFree(szAttr);
                        }

                        if(!xmlStrcmp(attrPtr1->name, BAD_CAST "degree"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "degree");
                        //    cout<<"get degree = "<<szAttr<<endl;
                            instancing_config_infor.degree = atoi(reinterpret_cast<const char *>(szAttr));
                            xmlFree(szAttr);
                        }

                        attrPtr1 = attrPtr1->next;
                    }
                }
				
				if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"instancing_strategy"))
				{
					xmlNodePtr propNodePtr = sonNodePtr;
                    xmlAttrPtr attrPtr2 = sonNodePtr->properties;

                    while(attrPtr2 != NULL)
                    {
                        if(!xmlStrcmp(attrPtr2->name, BAD_CAST "sigle_frequency"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "sigle_frequency");
                        
                            instancing_config_strategy.single_frequency = atoi(reinterpret_cast<const char *>(szAttr));
						//	cout<<"get single_frequency = "<< instancing_config_strategy.single_frequency<<endl;
                            
                            xmlFree(szAttr);
                        }
                        if(!xmlStrcmp(attrPtr2->name, BAD_CAST "unit_frequency"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "unit_frequency");
                        
                            instancing_config_strategy.unit_frequency = atoi(reinterpret_cast<const char *>(szAttr));
						//	cout<<"get unit_frequency = "<< instancing_config_strategy.single_frequency<<endl;
                            
                            xmlFree(szAttr);
                        }
                        if(!xmlStrcmp(attrPtr2->name, BAD_CAST "attractMonNum"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "attractMonNum");
                        
                            instancing_config_strategy.attractMonNum = atoi(reinterpret_cast<const char *>(szAttr));
						//	cout<<"get attractMonNum = "<< instancing_config_strategy.single_frequency<<endl;
                            
                            xmlFree(szAttr);
                        }

                        attrPtr2 = attrPtr2->next;
                    }

				}
				
				if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"time_gap"))
                {
                    //读取每波刷怪数
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string _every = reinterpret_cast<const char *>(szKey);
                    vector<int> time_gap;
                    int temp_num;
                    int pos = 0;
                    while(!_every.empty())
                    {
                        pos = _every.find(',');
                        temp_num = str2int(_every.substr(0, pos));
                        time_gap.push_back(temp_num);
                        _every = _every.substr(pos + 1);
                    }
                    instancing_config_strategy.time_gap = time_gap;
                }
				
				if(!xmlStrcmp(sonNodePtr->name, BAD_CAST "instancing_require"))
                {
                    xmlNodePtr propNodePtr = sonNodePtr;
                    xmlAttrPtr attrPtr = propNodePtr->properties;
                    while(attrPtr != NULL)
                    {
                        if(!xmlStrcmp(attrPtr->name, BAD_CAST "open_flag"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "open_flag");
                            instancing_config_require.open_flag = atoi(reinterpret_cast<const char *>(szAttr));
                        //    cout<<"get open_flag = "<<instancing_config_require.open_flag<<endl;
							xmlFree(szAttr);
                        }

                        if(!xmlStrcmp(attrPtr->name, BAD_CAST "level"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "level");
                            instancing_config_require.level = atoi(reinterpret_cast<const char *>(szAttr));
						//    cout<<"get level = "<<instancing_config_require.level<<endl;
                            xmlFree(szAttr);
                        }

                        if(!xmlStrcmp(attrPtr->name, BAD_CAST "free_limit"))
                        {
                            xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "free_limit");
                            instancing_config_require.free_limit = atoi(reinterpret_cast<const char *>(szAttr));
                        //    cout<<"get free_limit = "<<instancing_config_require.free_limit<<endl;
							xmlFree(szAttr);
                        }
                        attrPtr = attrPtr->next;
                    }
                }                
 				if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"stand_point"))
                {
                    //读取角色站立点，存进站立点列表中
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string stand_point_str = reinterpret_cast<const char *>(szKey);
                    instancing_config_strategy.stand_point = str2pointSet(stand_point_str);
					/*                    	
					cout<<"read tower, stand_point: "<<instancing_config_strategy.stand_point[0]._x<<" "<<instancing_config_strategy.stand_point[0]._y<<endl;
					cout<<"read tower, stand_point: "<<instancing_config_strategy.stand_point[1]._x<<" "<<instancing_config_strategy.stand_point[1]._y<<endl;
					cout<<"read tower, stand_point: "<<instancing_config_strategy.stand_point[2]._x<<" "<<instancing_config_strategy.stand_point[2]._y<<endl;
					cout<<"read tower, stand_point: "<<instancing_config_strategy.stand_point[3]._x<<" "<<instancing_config_strategy.stand_point[3]._y<<endl; */
                    xmlFree(szKey);
                } 
                 if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"route_left"))
                {
                    //读取左路径
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string _route_left = reinterpret_cast<const char *>(szKey);
                    vector<Point> route_left = str2pointSet(_route_left);
                    instancing_config_strategy.route_left = route_left;
                    //	cout<<"read tower, route_left: "<<route_left[0]._x<<route_left[0]._y<<endl;
                    xmlFree(szKey);
                }

                if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"route_right"))
                {
                    //读取右路径
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string _route_right = reinterpret_cast<const char *>(szKey);
					vector<Point> route_right = str2pointSet(_route_right);
                    instancing_config_strategy.route_right = route_right;
                    //	cout<<"read tower, route_right.size(): "<<route_right.size()<<endl;
                    xmlFree(szKey);
                }				
 /*				if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"left_way"))
                {
                    //读取左边完整路径
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string _left_way = reinterpret_cast<const char *>(szKey);
					vector<Point> left_way = str2pointSet1(_left_way);
					instancing_config_strategy.left_way = left_way;
				//	cout<<"read tower,test:"<<instancing_config_strategy.left_way[left_way.size()-2]._x<<" "<<instancing_config_strategy.left_way[left_way.size()-2]._y<<endl;
                    xmlFree(szKey);
                } 				
				if(!xmlStrcmp(sonNodePtr->name, (const xmlChar*)"right_way"))
                {
                    //读取右边完整路径
                    szKey = xmlNodeGetContent(sonNodePtr);
                    string _right_way = reinterpret_cast<const char *>(szKey);
					vector<Point> right_way = str2pointSet1(_right_way);
                    instancing_config_strategy.right_way = right_way;
				//	cout<<"read tower,test:"<<instancing_config_strategy.right_way[right_way.size()-1]._x<<" "<<instancing_config_strategy.right_way[right_way.size()-1]._y<<endl;
                    xmlFree(szKey);
                } */
                if((!xmlStrcmp(sonNodePtr->name, (const xmlChar *)"instancing_scene")))
                {
					//读取孙子节点
                    xmlNodePtr grandsonNodePtr = sonNodePtr->xmlChildrenNode;            
                    while(grandsonNodePtr != NULL)
                    {
                        if((!xmlStrcmp(grandsonNodePtr->name, (const xmlChar *)"sceneId")))
                        {
                            szKey = xmlNodeGetContent(grandsonNodePtr);
						//	printf("sceneId: %s\n", szKey); 
                            string scene_id = reinterpret_cast<const char *>(szKey);
                            scenes_id_vec.push_back(scene_id);
                            xmlFree(szKey); 
                        }
                        grandsonNodePtr = grandsonNodePtr->next;
                    }
                }
                sonNodePtr = sonNodePtr->next;
            }
			TD_Conf_T tdConf(instancing_config_infor, instancing_config_require,instancing_config_strategy, scenes_id_vec);
			id_2_tdConf.insert(pair<string, TD_Conf_T>(instancing_config_infor.id,tdConf));  
        }
    }
    free(szDocName);
    xmlFreeDoc(doc);
    return 0;
}

