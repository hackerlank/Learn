/********************************************************************

    created:   2012/5/09

    filename: read_main_config.cpp 

    author:       Tory 

    depend:       libxml2.lib 

*********************************************************************/
#include "function_read_configuration_files.h"

#include <libxml/parser.h>

#include <iostream>

#include "data_structure_struct.h"
#include <string.h>

using namespace std;

int read_main_config(char *fileName)
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
		/*读取陷阱配置文件 chenzhen add 2012.9.06*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"trap"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_trap((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_trap error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}		
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"five_elem"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_five_elem_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_five_elem_conf error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"meridian"))) 
        {
			cout<<"[BisonShow] Have read wellion's meridian.xml"<<endl;
            szKey = xmlNodeGetContent(curNode);
			int rc = read_merid_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_merid_conf error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取瓶罐配置文件 chenzhen add 2012.9.06*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"bottle"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_bottle((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_bottle error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}		
		
		/*读取马车配置文件 chenzhen add 2012.9.06*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"wagon"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_wagon((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_wagon error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取可摘取配置文件 chenzhen add 2012.9.04*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"takeGoods"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_take_goods((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_take_goods error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取jumpId配置文件对应的信息*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"jumpId"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_jumpId((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_jumpId error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取充值奖励配置文件对应的信息*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"rechargeReward"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_recharge_reward_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_recharge_reward_conf error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	
		
		/*读取阵营奖励配置文件对应的信息*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"campWar_reward"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_campWar_reward_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_campWar_reward_conf error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}		
	
		//读取副本配置文件 Tory add 2012.6.5
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"instance")))
        {

            szKey = xmlNodeGetContent(curNode);
			
			int rc = parseTowerDefence((char*)szKey);
            if(rc != 0)
			{
				cout<<"read parseTowerDefence config error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }

		//读取monster配置文件路径
        if((!xmlStrcmp(curNode->name, (const xmlChar *)"monster")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_monster((char*)szKey);	
        
			if(rc != 0)
			{
				cout<<"read read_files_monster error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		//读取场景配置文件路径
        if((!xmlStrcmp(curNode->name, (const xmlChar *)"scene")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_scene_config((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_scene_config error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }		
		
		/*读取物品配置文件*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"goods"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_goods((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_goods error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}		
		
		//读取装备配置文件路径
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"equip")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_equip((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_equip error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
	
		//读取仇恨值生成规则配置文件路径
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"hatValRle")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_hatValRue((char*)szKey);
       
			if(rc != 0)
			{
				cout<<"read read_files_hatValRue error"<<endl;
				return -1;
			}

            xmlFree(szKey); 

        }

		//读取任务配置文件路径 evan add 2012.5.14
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"task")))
        {

            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_task((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_task error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"droplist")))
        {

            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_droplist((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_droplist error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		//主动攻击类型的技能
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"zhudong")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_zhudong((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_files_zhudong error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }
		
		//医疗类型的技能
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"yiliao")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_yiliao((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_yiliao error"<<endl;
				return -1;
			}
        //    printf("in read_main_config have read skill_config: %s\n", szKey); 

            xmlFree(szKey); 
        }
	
		//被动类型的技能
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"beidong")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_beidong((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_beidong error"<<endl;
				return -1;
			}
        //    printf("in read_main_config have read skill_config: %s\n", szKey); 

            xmlFree(szKey); 
        }
		
		//buff类型的技能
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"buff")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_buff((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_buff error"<<endl;
				return -1;
			}
        //    printf("in read_main_config have read skill_config: %s\n", szKey); 

            xmlFree(szKey); 
        }
		
		//读取触发任务条件配置文件路径 evan add 2012.5.24
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"touch")))
        {

            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_touch((char*)szKey);
            //printf("**********touch: %s\n", szKey); 
			if(rc != 0)
			{
				cout<<"read read_files_touch error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		//读取副本奖励物品配置文件 added by bison 2012.6.13
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ectype_reward_goods")))
        {
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_ectype_reward_goods((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_ectype_reward_goods error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		//读取副本奖励信息配置文件 added by bison 2012.6.13
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ectype_reward_info")))
        {
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_ectype_reward_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_ectype_reward_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ointment")))
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_ointment((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_ointment error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"task_goods")))
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_task_goods_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_task_goods_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"pet")))
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_pet((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_pet error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取宠物技能信息*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"petSkill"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_petSkill((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_petSkill error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取套装配置文件 evan add 2012.8.30*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"suit"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_suit((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_suit error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取等级奖励的信息 add by jolly 2012.9.10*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"reward_level"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_reward_level((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_reward_level error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取充值奖励信息 add by jolly 2012,9.10*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"reward_recharge"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_reward_recharge((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_reward_recharge error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
	
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"npc")))
        {

            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_npc((char*)szKey);
            //printf("**********npc : %s\n", szKey); 
			if(rc != 0)
			{
				cout<<"read read_files_npc error"<<endl;
				return -1;
			}
            xmlFree(szKey); 

        }
		
		//读取帮派活动信息
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guild_activity"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_guild_activity_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_guild_activity_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取vip配置文件 cookie add 2012.9.14*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"vip"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			//cout<<"can not do this in read main config"<<endl;
			int rc = read_files_vip((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_vip error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取玩家升级所需要经验值配置文件 evan add 2012.9.14*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"upgrade"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
		
			int rc = read_files_update((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_update error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取副本令.xml配置文件 cookie add 2012.9.14*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"copyCause"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			//cout<<"can not do this in read main config"<<endl;
			int rc = read_copyCause((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_copyCause error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取摆摊区域.xml配置文件 cookie add 2012.9.22*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"pitchTerm"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			//cout<<"can not do this in read main config"<<endl;
			int rc = read_pitchTerm((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_pitchTerm error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取头衔.xml配置文件 cookie add 2012.9.22*/
		 if((!xmlStrcmp(curNode->name, (const xmlChar *)"title"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
		//	cout<<"can not do this in read main config"<<endl;
			int rc = read_title((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_title error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		//读取循环项目信息
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"cycle_limit"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_cycle_limit_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_cycle_limit_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//每日无限循环任务奖励系数
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"cycle_task_reward"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_cycle_task_reward_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_cycle_task_reward_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取复活点配置文件 jolly add 2012.9.25*/
		 if((!xmlStrcmp(curNode->name, (const xmlChar *)"revival"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			// cout<<"can not do this in read main config"<<endl;
			int rc = read_files_revival((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_revival error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"dirty_words"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_dirty_words((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_dirty_words error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		/*读取神秘商人配置文件 jolly add 2012.10.11*/
		 if((!xmlStrcmp(curNode->name, (const xmlChar *)"mysteriousBussiness"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			// cout<<"can not do this in read main config"<<endl;
			int rc = read_files_mysteriousBussiness((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_mysteriousBussiness error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"monsterActiveBoss"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_monsterActiveBoss((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_monsterActiveBoss error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"dailyActive"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_dailyActive((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_dailyActive error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"cpyPassOlder"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_cpyPassOlder((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_cpyPassOlder error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guildBussiness"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_guildBussiness((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_guildBussiness error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		/*读取点石成金奖励 jolly add 2012.11.9*/
		 if((!xmlStrcmp(curNode->name, (const xmlChar *)"midasTouch"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			// cout<<"can not do this in read main config"<<endl;
			int rc = read_files_midasTouchReward((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_midasTouchReward error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		//读取服务器开启配置文件路径 Tory added
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"server_configure"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_server_config((char*)szKey);
			if(rc != 0)
			{
				cout<<"read server config error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//读取帮派盛宴信息
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guild_feast"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_guild_feast_info((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_guild_feast_info error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"happy_map"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_happy_map((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_happy_map error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guild_skill"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_guild_skill((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_guild_skill error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"onlineReward"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_reward_online((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_reward_online error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"target"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_reward_target((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_reward_target error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//武林目标信息
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"target"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_reward_target((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_reward_target error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"buff_debuff"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_buff_debuff((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_buff_debuff error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"vipRoomLimit"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_vipBaleRomLimit((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_vipBaleRomLimit error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"fight_const"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_fight_const_value((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_fight_const_value error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"hero_skill"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_hero_skill((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_hero_skill error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"hero_conf"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_hero_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_hero_conf error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"partyRom"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_partyRomLimit((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_partyRomLimit error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guild_reward"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_guild_reward((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_guild_reward error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"cpyNpcPt"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_Npc_cpy_pt((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_Npc_cpy_pt error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		/*读取声望商店 add by jolly 2012,12.3*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"shengWangBussiness"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_shengWangBussiness((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_shengWangBussiness error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"partyBaseCampLimit"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_party_base_camp((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_party_base_camp error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		//消费奖励  xhm
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"consume_reward"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_consume_reward_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read consume_reward config error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	
		
		//读取宝石合成配置文件路径 Tory added
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"heCheng_configure"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_heCheng_config((char*)szKey);
			if(rc != 0)
			{
				cout<<"read heCheng_config error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	

		/*读取经验奖励配置文件 jolly add 2013.1.18*/
		 if((!xmlStrcmp(curNode->name, (const xmlChar *)"factor_reward"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			// cout<<"can not do this in read main config"<<endl;
			int rc = read_factor_reward((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_factor_reward error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 		
		
		//读节日物品兑换
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"festival"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_festivalGoods((char*)szKey);
			if(rc != 0)
			{
				cout<<"read fesitval error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	
		
		//双倍奖励的配置文件信息保存
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"activeDouble")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_active_double((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_active_double error"<<endl;
				return -1;
			}
        //    printf("in read_main_config have read skill_config: %s\n", szKey); 

            xmlFree(szKey); 
        }
		
		//读取送花奖励配置文件
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"goods_use_reward"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_good_use_reward_conf((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_good_use_reward_conf error!"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ride"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_files_ride((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_ride error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		} 
		
		//读取替身雕像配置类文件
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"statuaryBase"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_statuaryBase((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_statuaryBase error!"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//读取缓存服务器的配置列表
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"mem_group_config"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_mem_group_config((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_mem_group_config error!"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取vip配置文件 cookie add 2012.9.14*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ride_skill"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			//cout<<"can not do this in read main config"<<endl;
			int rc = read_files_rideSkill((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_vip error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		/*读取vip配置文件 cookie add 2012.9.14*/
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"ride_specialskill"))) 
        {
			
            szKey = xmlNodeGetContent(curNode);
			//cout<<"can not do this in read main config"<<endl;
			int rc = read_files_rideSpecialSkill((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_vip error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"camp_res_war_control"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_camp_res_war_control((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_camp_res_war_control error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"guild_war_control"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_guild_war_control((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_guild_war_control error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"rob_flag_war_control"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_rob_flag_war_control((char*)szKey);
			if(rc != 0)
			{
				cout<<"read rob_flag_war_control error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//读取黑木崖的配置文件
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"blackMargin"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_black_margin((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_black_margin error!"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//读取装备操作配置文件
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"equip_operator")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_equipOperator((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_equipOperator error"<<endl;
				return -1;
			}
        //    printf("in read_main_config have read skill_config: %s\n", szKey); 

            xmlFree(szKey); 
        }
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"pet_range")))
        {
			
            szKey = xmlNodeGetContent(curNode);
			
			int rc = read_files_petRange((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_files_petRange error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}	
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"internal_forces"))) 
        {
			cout<<"[BisonShow] Have read wellion's internal_forces.xml"<<endl;
            szKey = xmlNodeGetContent(curNode);
			int rc = read_internal_forces((char*)szKey);
			if(rc != 0)
			{
				cout<<"read internal_forces error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"global"))) 
        {			
            szKey = xmlNodeGetContent(curNode);
			int rc = read_global((char*)szKey);
			if(rc != 0)
			{
				cout<<"read read_global error!"<<endl;
				return -1;
			}
            xmlFree(szKey); 
		}
		
		//读取排名奖励
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"rankReward")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_rankReward((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_files_rankReward error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }
		//读取服务器文字
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"words")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_words((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_files_words error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }
		
		//读取每日签到奖励
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"everyDaySignReward")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_everyDaySignReward((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_files_everyDaySignReward error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }
		//cdkey兑换奖励配置文件
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"cdkey")))
        {

            szKey = xmlNodeGetContent(curNode);

			int rc = read_files_cdkey((char*)szKey);
			
			if(rc != 0)
			{
				cout<<"read read_files_cdkey error"<<endl;
				return -1;
			}
            xmlFree(szKey); 
        }
		curNode = curNode->next; 
	}
    
    free(szDocName);

    xmlFreeDoc(doc);

    return 0;

}
