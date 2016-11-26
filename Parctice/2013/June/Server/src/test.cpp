/***************************************
*	文件类型：实现文件
*	文件名称：test.cpp
*	文件作用：测试文件
***************************************/
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
//全局函数头文件
#include"command_other_function_all_over.h"
//配置文件读取的头文件
#include"function_read_configuration_files.h"
//事件驱动头文件，IO
#include"libev.h"
//自定义数据类型头文件
#include"other_define_data.h"
//用到的标准头文件
#include<stdio.h>
#include "set_camp.h"
#include<vector>
#include<map>
#include<set>
#include <fcntl.h>
#include"map_inform.h"
#include"timerContainer.h"
// #include "campWarManagement.h"
#include"my_time.h"
#include"takeGoods.h"
#include"wagon.h"
#include"bottle.h"
#include"trap.h"
#include"guild_war_asist.h"
#include "my_memcached.h"
#include "rankInfoAsist.h"
#include "bootAssignment.h"
#include "campWarManagement.h"
#include "dictionary_asist.h"
#include "set_camp.h"
#include "command_user_role_manage.h"
#include "read_rsa_key.h"
#include "wholeDefine.h"
#include "instancing_manage.h"
#include"cpyManager.h"
#include "system_activity_reward_assist.h"
#include "activeAsist.h"
#include "mail_systerm_interface.h"
#include "my_mem_group.h"
#include"statuaryAsist.h"
#include "rob_flag_war_logic.h"
#include"chatGroupManager.h"
#include "camp_leader_and_chief.h"
#include"cpyAsist.h"

extern ChatGroupManager *chatManager;

extern struct event_base *loops;

extern map<string,string>mapId_connect_monsterId; 

extern char cross_domain_str[256];

extern GuildWarAsist *guildWarManage;           //帮派战管理
RobFlagWarLogic *robFlagWarManage;
extern int serverOpenTime;
//阵营战管理类；
extern campWarManagement campWarController; 

//空闲用户列表,初始化游戏数据(与副本数据的初始化类似)		
extern list<Role*> idle_role_list;

extern map<string, Hero*> heroId_to_pHero;

extern MapType_T mapTypeInfo;		//某些特殊地图的ID；

extern CpyManger *cpyManger;

int TakeGoods::count = 0;
// int Wagon::count = 0;  
int Bottle::count = 0;  
int Trap::count = 0;  
int Map_Inform::count = 0;  
extern DurCampTme durCampTime; 

//当前进程崩溃之前，存储数据函数
void dump(int);

int main(int argc ,char** argv)
{
    cout << "g_out_buf size:" << sizeof(g_out_buf) << endl;
    if(argc < 2)
    {
        perror("argument error\n");
        return(-1);
    }
	
#if 0
	//群聊目前不要
	ChatGroupManager::createManagerInst(1000);
	chatManager = ChatGroupManager::getManagerInst();
#endif
	
	cpyManger = new CpyManger(1000);
	cpyManger->print();
    loops = event_base_new();
	srand ( time(NULL) );
	
    //加载怪物技能限制配置文件add chenzhen 7.16
    string monSkill = "config/monSkill/monSkill.xml";
    read_monster_skill(const_cast<char *>(monSkill.c_str()));
	
	//加载game server配置文件
    char main_config_path[] = "config/main_config.xml";
    int rc = read_main_config(main_config_path); 
	if(rc < 0)
	{
		perror("read read_main_config.xml error");
        return -1;
	}

    //读取副本限制配置文件add chenzhen 6.13
    string cpyLimit = "config/cpyLimit.xml";
    read_files_cpyLimit(const_cast<char *>(cpyLimit.c_str()));
    vector<string> cpyFile;
    cpyFile.push_back("config/cpy.xml");
    int cpyFileLen = cpyFile.size();
    int i;
    for(i = 0; i < cpyFileLen; i++)
    {
        read_files_cpy(const_cast<char *>(cpyFile[i].c_str()));
    }   

    /** 加载安全策略文件 Tory **/
    int file_desc = open("config/crossdomain.xml", O_RDONLY, 0);
    memset(cross_domain_str, 0, 256);
    rc = read(file_desc, cross_domain_str, 256);
    if(rc < 0)
    {
        perror("read crossdomain.xml error");
        return -1;
    }
	close(file_desc);

	
    /** 初始化空闲玩家列表 list<Role*> idle_role_list **/
    i = 0;
    while(i < 2000)
    {
        Role* idle_role = new Role();
        idle_role_list.push_back(idle_role);
        i++;
    }

	if(initMyMemcached() == false)	//初始化连接缓存的操作类实例 Tory
	{
		cout<<"initMyMemcached failure"<<endl;
		return -1;
	}	
	
	if (initCdKeyCached()== false)
	{
		cout<<"initCdKeyCached failuer"<<endl;
		return -1;
	}

	if(initMyMemGroup() == false)	//初始化缓存服务器管理类实例 Tory
	{
		cout<<"initMyMemGroup failure"<<endl;
		return -1;
	}
	
	if(MailSystermInterface::createMailDir() < 0)		//检测邮件数据文件夹是否存在，不存在则创建 tory
	{
		cout<<"create createMailDir error"<<endl;
		return -1;
	}
	
	initCampeDurTme();
	//TODO 正式开服后，初始化用下面函数；
    campWarController.initCampWarInfo(durCampTime.camphappyFight,durCampTime.campcompeteFight,\
							durCampTime.takePartDurTme,durCampTime.kungFuMaster,durCampTime.campPeaceTme,durCampTime.kungPeaceTme);       //初始化阵营战战场（默认全部的开始持续时间是20分钟）； 	
	
	
    guildWarManage = new GuildWarAsist();
	robFlagWarManage = new RobFlagWarLogic();
    initAllExistGuild();                                //初始所有已存帮派
	init_command_map();                                 //初始化命令处理函数
    initMyTime();                                       //初始服务器内部维持的时间
    initMyTimer();                                      
    initDictionary();                                   //初始化字典
	initPlayerNumber();
	initInstManage();									//初始化塔防管理对象
    rankInfoBootInit();//触发排名信息更新；
    // nickNameCheckValueBootInit();//同名检查开始读取缓存；
	// initTowerDefRoom(500);//创建500个队伍房间；
	init_rechargeInfo_reward();//初始化充值奖励；
	init_consumeInfo_reward();//初始化消费奖励；	
	init_goods_opr_reward();//送花奖励初始化；
	initCampNumber();		//初始化阵营人数
	serverOpenTime=myTime.tv_sec;
	
	openServerStatuaryMsg();//初始化雕像
	
	init_leader_and_chief_from_mem();
	/*测试用*/
//	destroyAllStatuary();
	
   	//TODO 测试用，请不要删除。初始化阵营战战场（默认全部的开始持续时间是20分钟）；							
    // campWarController.initCampWarInfo(1*60+30,40*60,2*60-30,40*60,5*60,20); 

#if 1
	//TODO 正式开服后，初始化用下面函数；
    campWarController.initCampWarInfo(durCampTime.camphappyFight,durCampTime.campcompeteFight,\
							durCampTime.takePartDurTme,durCampTime.kungFuMaster,durCampTime.campPeaceTme,durCampTime.kungPeaceTme);       //初始化阵营战战场（默认全部的开始持续时间是20分钟）； 	
#endif	
	//test the special mapId，TODO 不要删除;
	cout<<"[XHM TEST]guid mapId:"<<mapTypeInfo.guidWarMapId<<endl;
	cout<<"[XHM TEST]campWar mapId:"<<mapTypeInfo.campWarMapId<<endl;
	cout<<"[XHM TEST]campSence mapId:"<<mapTypeInfo.campSenceMapId<<endl;
	cout<<"[XHM TEST]mainCity1 mapId:"<<mapTypeInfo.mainCityMapId<<endl;
	cout<<"[XHM TEST]mainCity2 mapId:"<<mapTypeInfo.mainCityMapId2<<endl;
	cout<<"[XHM TEST]towerDefMapId mapId:"<<mapTypeInfo.towerDefMapId<<endl;
	cout<<"[XHM TEST]campResWarMapId mapId:"<<mapTypeInfo.campResWarMapId<<endl;
	
	//获取webServer公钥
	get_pubilc_key();
	
    //signal(SIGSEGV, &dump);
    signal(SIGTERM, &dump); //kill 信号
	signal(SIGKILL, &dump);	//非友好kill发送
	signal(SIGINT, &dump);	//ctrl + c的处理
	signal(SIGPIPE, SIG_IGN);
	
	if (argc > 2 && (!strcmp(argv[2], "-d") || !strcmp(argv[2], "-D")))
	{
		cout<<"You have given the argv with -d "<<endl;
		daemon(1, 0);
    }
	
	int port;
    port = atoi(argv[1]);                //初始化套接字
	
    run_loop(port); 
	
	initCpyLimitMemRecord();
	
	cpyManger->print();
	
	
    return 0;
}

void dump(int signo)
{
    if(signo == SIGSEGV || signo == SIGKILL || signo == SIGTERM)
    {
        void *array[20];
        size_t size;
        char **strings;
        size_t i;

        size = backtrace(array, 20);
        strings = backtrace_symbols (array, size);

        printf ("Obtained %zd stack frames.\n", size);

        FILE *out;

		string out_file = "my_core.";
		char time_temp[20] = {0}; 
		int current_time = MY_TV_SEC;
		sprintf(time_temp, "%d",current_time);	
		out_file += time_temp;
		 
        if((out = fopen(out_file.c_str(), "w+")) == NULL)
        {
            fprintf(stderr, "fopen file error!\n");
            _exit(EXIT_FAILURE);
        }

		if(signo == SIGSEGV)	fprintf(out,"%s\n", "signo==SIGSEGV");
		if(signo == SIGKILL)	fprintf(out,"%s\n", "signo==SIGKILL");
		if(signo == SIGTERM)	fprintf(out,"%s\n", "signo==SIGTERM");
        for(i = 0; i < size; i++)
            fprintf(out, "%s\n", strings[i]);
        free (strings);
		if(fclose(out) != 0)
		{
			fprintf(stderr, "fclose file error!\n");
			_exit(EXIT_FAILURE);
		} 
    }
	
	//保存服务器所有帮派系统信息
	// saveGuildSystemToMemc();
    map<string, Hero*>::iterator iter =  heroId_to_pHero.begin();
    for(iter; iter != heroId_to_pHero.end(); iter++)
    {
        Hero* myHero = iter->second;
        cout<<"heroId:"<<iter->first<<endl;
        if(myHero != NULL)
        {
			closeServerDeal(myHero);
            //bool isSuccess = myHero->memSet();
        }
    }
	
	saveCampNumber();
	save_leader_and_chief_to_mem();
	
	/*关闭服务器时，往缓存里面存雕像信息*/
	closeServerStatuaryMsg();
	
	//存副本记录
	storeCpyLimitMemRecord();
	
	//event_base_free(loops);
    _exit(0);    
}
