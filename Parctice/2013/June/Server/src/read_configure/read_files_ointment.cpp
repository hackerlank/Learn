#include"function_read_configuration_files.h"
#include"ointment.h"
#include<libxml/parser.h>
#include<map>
#include<iostream>
using namespace::std;
extern map<string, Ointment *>id_to_ointment;
int read_files_ointment(char *fileName) { 
   xmlDocPtr doc;
   xmlNodePtr curnow;
   xmlNodePtr curNode;
   char szDocName[50] = { 0 };
   xmlChar *cTem;
   strcpy(szDocName, fileName);
   //读取equip配置文件
   xmlKeepBlanksDefault(0);
   doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER);
   if (NULL == doc) {
      return -1;
   }
   //得到xml文件的root
   curnow = xmlDocGetRootElement(doc);
   if (NULL == curnow) {
      xmlFreeDoc(doc);
      return -3;
   }
   //xml的相关变量
   curnow = curnow->xmlChildrenNode;
   string id;
   string name;
   int cd;
   int sellPriceBoundGold;       //npc处售出价格	绑定元宝
   int sellPriceNoBoundGold;    //npc处售出价格	非绑定元宝
   int sellPriceBoundMoney;    //npc处售出价格	绑定游戏币
   int sellPriceNoBoundMoney; //npc处售出价格	非绑定游戏币
   int levelLimits;   //等级限制
   int pileUp; //堆叠上限
   int type; //0 药瓶 ，1 药包，2 buff药
   int ointmentType;
   int value;
   int factor;
   int level;  //药品等级
   while (curnow != NULL) {
      curNode = curnow->xmlChildrenNode;
      if (NULL == curNode) {
         xmlFreeDoc(doc);
         return -3;
      }
      while (curNode != NULL) {
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"type")) {
            cTem = xmlNodeGetContent(curNode);

            type = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"ointmentType")) {
            cTem = xmlNodeGetContent(curNode);

            ointmentType = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"id")) {
            cTem = xmlNodeGetContent(curNode);
            id = (char *)cTem;
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"name")) {
            cTem = xmlNodeGetContent(curNode);
            name = (char *)cTem;
            xmlFree(cTem);
         }

         if (!xmlStrcmp(curNode->name, (const xmlChar *)"cd")) {
            cTem = xmlNodeGetContent(curNode);
            cd = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"value")) {
            cTem = xmlNodeGetContent(curNode);
            value = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"goldBound")) {
            cTem = xmlNodeGetContent(curNode);
            sellPriceBoundGold = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"gold")) {
            cTem = xmlNodeGetContent(curNode);
            sellPriceNoBoundGold = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"moneyBound")) {
            cTem = xmlNodeGetContent(curNode);
            sellPriceBoundMoney = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"money")) {
            cTem = xmlNodeGetContent(curNode);
            sellPriceNoBoundMoney = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"levelLimits")) {
            cTem = xmlNodeGetContent(curNode);
            levelLimits = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"level")) {
            cTem = xmlNodeGetContent(curNode);
            level = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"factor")) {
            cTem = xmlNodeGetContent(curNode);
            factor = atoi((char *)cTem);
            xmlFree(cTem);
         }
         if (!xmlStrcmp(curNode->name, (const xmlChar *)"pileUp")) {
            cTem = xmlNodeGetContent(curNode);
            pileUp = atoi((char *)cTem);
            Ointment *ointment = new Ointment(id, name, cd,
                                              sellPriceBoundGold, ointmentType, sellPriceNoBoundGold,
                                              sellPriceBoundMoney, sellPriceNoBoundMoney, levelLimits,
                                              pileUp, type, value,level,factor);
            id_to_ointment[id] = ointment;

            xmlFree(cTem);
         }
         curNode = curNode->next;
      }
      curnow = curnow->next;
   }
   //cout<<"id_to_ointment.size():"<<id_to_ointment.size()<<endl;
   xmlFreeDoc(doc);
   return 0;
}
