/*
 * Filename: instancing_communication. 
 * Description: 副本模块与客户端的通信
 * Original Author : bison, 2012-6-18
 */
#include <arpa/inet.h>

#include <stdlib.h> 

#include "command_return_define_data.h"

#include "instancing_communication.h"
//塔防副本管理头文件
#include "instancing_manage.h"
//普通副本管理头文件
#include "cpyLimit.h"
//奖励
#include "ectype_reward_set.h"

#include"cpyLimit.h"

#include"cpyAsist.h"

#include"wholeDefine.h"

#include"cpyAsist.h"

#include"teamManager.h"

#include"team.h"

extern int g_msg_len;
extern Hero* pg_hero;
extern int sock_fd;

//角色容器
extern map<string, Hero*> heroId_to_pHero;
//塔防副本管理类
extern Instancing_manage *Inst_MNG;
//普通副本管理容器
extern map<string,CpyLimit*> cpyId_to_cpyLimit;

//奖励信息的全局变量
extern map<string, Ectype_Reward_Info*> idNum_2_rewardInfo;

extern map<string,CpyLimit*> cpyId_to_cpyLimit;

//发送副本奖励信息
void sendEctypeRewardMsg(char* ectypeId, Hero *hero, int flag)
{
    char msgReward[400];
    // string msgHead = "6";

    // msgReward = msgReward + msgHead;
    // msgReward += intTostring((flag == 0)?INST_REWARD_CONST_RETURN:INST_REWARD_GOODS_RETURN);

    TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(ectypeId);
    EctypeRewardSet *rewardSet = tdRoom->getRewardSet();
    if(rewardSet == NULL)
    {
        return;
    }
    if(flag == 0)
    {
        // msgReward += "," + ectypeId;                 //据说客户端较难获得副本ID，在这里发给客户端存着
        // msgReward += rewardSet->getConstRewardMsg(); //发送固定奖励信息
		sprintf(msgReward, "6,%d,%s", INST_REWARD_CONST_RETURN,
			ectypeId);
		rewardSet->getConstRewardMsg(msgReward + strlen(msgReward));
    } else
    {
        // msgReward += rewardSet->getGoodsRewardMsg(hero->getIdentity()); //发送物品奖励信息
		sprintf(msgReward, "6,%d,%s", INST_REWARD_GOODS_RETURN,
			ectypeId);
		rewardSet->getGoodsRewardMsg(hero->getIdentity(), msgReward + strlen(msgReward));
    }
    send_msg(hero->getFd(), msgReward);

}

//玩家抽取副本的物品奖励
void ectypeRewardGoods(char *buffer)
{
    char *heroId;       //角色Id
    //char *instId;		//副本id
    int selectedTimes;  //抽奖次数
    int index;          //抽奖下标

	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(heroId);
	MSG_INT(selectedTimes);
	MSG_INT(index);
	Hero* hero = pg_hero;
    char msgReward[400];
    char* ectypeId = hero->getFbRom();
    //char idNum[10] = {0};
    //memcpy(idNum, ectypeId, 3);
    //int level = atoi(ectypeId.substr(4,1).c_str());
    EctypeRewardSet *rewardSet = NULL;
	cout<<"ectypeId is isi is sisis isis siisi s issi isi isis "<<ectypeId<<endl;
#if 0
    if(strncmp(ectypeId, "008",3) == 0)
    {
		if(strncmp(ectypeId, "008_1",4) == 0 || strncmp(ectypeId, "008_2",4) == 0)
		{
			/*通关副本记录*/
			hero->getCpyRecord()->inputPasCtn("008");
		}
		
			
        //45级为塔防副本
        TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(ectypeId);

        if(tdRoom == NULL)
        {
			sprintf(msgReward, "6,%d,0", INST_REWARD_GOODS_RETURN);
            // msgReward += intTostring(FAILED);
            send_msg(hero->getFd(), msgReward);
			cout<<"111111111111111111111111111111111111"<<endl;
            return;
        }

        rewardSet = tdRoom->getRewardSet();
    } 
#endif
//	else
    {
        //为普通副本
        // int found = ectypeId.find_last_of("_");
        // string fbId = ectypeId.substr(0,found);
        // int roomNum = atoi((ectypeId.substr(found + 1)).c_str());
#if 0		
		char roomNumStr[10], fbId[10];
		sub_str(fbId, ectypeId, 0, 5);
		sub_str(roomNumStr, ectypeId, 6, 0);
		int roomNum = atoi(roomNumStr);
        //查找普通副本
        map<string,CpyLimit*>::iterator cpyLimt_it;
        cpyLimt_it = cpyId_to_cpyLimit.find(fbId);
        if(cpyLimt_it == cpyId_to_cpyLimit.end())
        {
            // msgReward += intTostring(FAILED);
			sprintf(msgReward, "6,%d,0", INST_REWARD_GOODS_RETURN);
            send_msg(hero->getFd(), msgReward);
            return;
        }

        //在cpyLimit类中通过房间号找到副本实例
        Cpy *cpy = (cpyLimt_it->second)->getRoomCpy(roomNum);
        if(cpy == NULL)
        {
            // msgReward += intTostring(FAILED);
			sprintf(msgReward, "6,%d,0", INST_REWARD_GOODS_RETURN);
            send_msg(hero->getFd(), msgReward);
            return;
        }
        rewardSet = cpy->getRewardSet();
#endif	
		void *mapNow;
		Cpy *cpy;
		
		mapNow = (void*)hero->getMap();
		if(mapNow == NULL || !((Map_Inform*)mapNow)->getFlgCpy())
		{
			sprintf(msgReward, "6,%d,0", INST_REWARD_GOODS_RETURN);
            send_msg(hero->getFd(), msgReward);
			return;
		}
		
		cpy = ((Map_Cpy*)mapNow)->getCpy();		
		
		if(cpy == NULL)
		{
			sprintf(msgReward, "6,%d,0", INST_REWARD_GOODS_RETURN);
            send_msg(hero->getFd(), msgReward);
			return;
		}
		rewardSet = cpy->getRewardSet();
    }

	int ret = 1;
    if(rewardSet == NULL)
    {
        //副本中还未有对应奖励信息
        // msgReward += intTostring(FAILED);
		sprintf(msgReward, "6,%d,0,%d", INST_REWARD_GOODS_RETURN, ret);
        send_msg(hero->getFd(), msgReward);
		cout<<"55555555555555555555555555555555555555"<<endl;
        return;
    }

    //得到奖励物品的ID
    //string goodsId = rewardSet->getGoodsRewardMsg(hero->getIdentity(), index);
    char goodsId[100] = {0};
	ret = rewardSet->getGoodsRewardMsg(hero->getIdentity(), goodsId);
	// cout<<"##########################################################"<<endl;
	// cout<<"##########################################################"<<endl;
	// cout<<"##########################################################"<<endl;
	// cout<<"getGoodsRewardMsg return is "<<ret<<endl;
	// cout<<"getGoodsRewa return is "<<goodsId<<endl;
    if(strlen(goodsId) == 0)
    {
        //返回物品ID为空
        // msgReward += intTostring(FAILED);
		sprintf(msgReward, "6,%d,0,%d", INST_REWARD_GOODS_RETURN, ret);
        send_msg(hero->getFd(), msgReward);
        return;
    }
    // msgReward += intTostring(SUCCESS);
    // msgReward += goodsId;  //发送物品奖励信息
	sprintf(msgReward, "6,%d,1%s", INST_REWARD_GOODS_RETURN, goodsId);
    send_msg(hero->getFd(), msgReward);

}

void ectypeRewardAll(char *buffer)
{
    char len_arg;       //参数长度
    char *heroId;       //角色Id
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
    char msgReward[400];
	
	Hero *hero = pg_hero;
	
    char* ectypeId = hero->getFbRom();
	char idNum[10];
	sub_str(idNum, ectypeId, 0, 3);
    //int level = atoi(ectypeId.substr(4,1).c_str());
    EctypeRewardSet *rewardSet = NULL;
	
#if 0
    if(!strcmp(idNum, "008"))
    {
        //为塔防副本
        TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(ectypeId);
        if(tdRoom == NULL)
        {
            // msgReward += intTostring(FAILED);
			sprintf(msgReward, "6,%d,0", INST_REWARD_ALL_RETURN);
            send_msg(hero->getFd(), msgReward);
			cout<<"ectypeRewardAll 11111111111111111111111111111111"<<endl;
            return;
        }
        rewardSet = tdRoom->getRewardSet();
    }
#endif
//	else
    {
        //为普通副本
		void *mapNow;
		Cpy *cpy;
		
		mapNow = (void*)hero->getMap();
		if(mapNow == NULL || !((Map_Inform*)mapNow)->getFlgCpy())
		{
			sprintf(msgReward, "6,%d,0", INST_REWARD_ALL_RETURN);
            send_msg(hero->getFd(), msgReward);
			cout<<"ectypeRewardAll 2222222222222222222222222222222222"<<endl;
			return;
		}
		
		cpy = ((Map_Cpy*)mapNow)->getCpy();		
		
		if(cpy == NULL)
		{
			sprintf(msgReward, "6,%d,0", INST_REWARD_ALL_RETURN);
            send_msg(hero->getFd(), msgReward);
			cout<<"ectypeRewardAll 33333333333333333333333333333333333333"<<endl;
			cout<<"ectypeId is "<<ectypeId<<endl;
			return;
		}
		rewardSet = cpy->getRewardSet();
    }

    if(rewardSet == NULL)
    {
        //此刻没有副本的奖励信息
        // msgReward = msgReward + intTostring(FAILED);
		sprintf(msgReward, "6,%d,0", INST_REWARD_ALL_RETURN);
		cout<<"ectypeRewardAll 444444444444444444444444444444444444444444444"<<endl;
    } else
    {
        int flag = rewardSet->setRewardToHero(hero->getIdentity());
        if(flag == 0)
        {
            //奖励成功
			sprintf(msgReward, "6,%d,1", INST_REWARD_ALL_RETURN);
            // msgReward = msgReward + intTostring(SUCCESS);
        } else
        {
            // msgReward = msgReward + intTostring(FAILED);
			sprintf(msgReward, "6,%d,0,%d", INST_REWARD_ALL_RETURN,flag);
        }
    }
    send_msg(hero->getFd(), msgReward);
}

/*
* author：	Tory
* date:		2012.9.27 
* Description：与客户端的交流函数，队长选择挑战副本时，服务器判断该队伍能否进入副本，
*				条件满足则向队员发送邀请，条件失败则回复给队长失败的原因
*/
void handleTeamLeaderOperate(char *buffer)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};    
    bool isParty = false;
    
	//解析角色ID
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(char* heroId);
    // cout<<"Tory: heroId :"<<heroId<<endl;

    //解析副本名字
	MSG_CHAR(char* inst_name);
    // cout<<"Tory:inst_name :"<<inst_name<<endl;

    //解析副本ID
	MSG_CHAR(char* inst_id);
    // cout<<"Tory:inst_id :"<<inst_id<<endl;

    //解析副本难度
	MSG_INT(int inst_level);
    cout<<"Tory:inst_level :"<<inst_level<<endl;	
    
	/*帮派副本*/
    if(inst_level == 3)
    {
        isParty = true;
    }
	
	// 生成副本类型ID（副本类型+副本难度 tory）
	char cpyId[50] = {0};
	strncpy(cpyId, inst_id, sizeof(cpyId));	
	strncat(cpyId,"_",strlen("_"));	
    appendNum(cpyId, inst_level, 1);
	
#if 0
	//如果是塔防副本ID，则进入塔防副本的副本申请函数
	if(strncmp(cpyId,"008",3) == 0)
	{
		Inst_MNG->apply_td_inst(pg_hero, cpyId);
		return;
	}
#endif

    Hero *teamLeader = pg_hero;
    //获得角色下的队伍Id 
	if(strlen(teamLeader->getTeamerId()) == 0)
        return ;
	
    TeamManager* teamManger = TeamManager::getManagerInst();
	
	Team *team = teamManger->getTeamHandle(teamLeader->getTeamerId());
		
	if(!team)
	{
		cout<<"handleTeamLeaderOperate team is NULL:"<<endl;
		return ;		
	}
	
	
	//不是队长，没有权限
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"handleTeamLeaderOperate you are not header :"<<pg_hero->getIdentity()<<endl;
		char failMsgTeam[200] = {'\0'};
		sprintf(failMsgTeam,"6,7,%d",ERROR_IN_TEAM,pg_hero->getNickName());
		send_msg(pg_hero->getFd(),failMsgTeam);	
		return;
	}

    //获得队伍中的在线成员的指针实例
    vector<Hero *> team_unit;
	vector<string> heroId_unit;
	team->getTeamMemberId(heroId_unit);
	
	for (vector<string>::iterator memIter = heroId_unit.begin(); memIter != heroId_unit.end(); ++memIter)
	{
            map<string, Hero *>::iterator iterHero = heroId_to_pHero.find(*memIter);
            if (iterHero == heroId_to_pHero.end()) continue;
            Hero *myHero = iterHero->second;
            if (myHero != NULL) 
			{
				team_unit.push_back(myHero);
			}

	}
	
	/*add chenzhen 20130128 重置队伍预定房间*/
	string cpyRoomStrOld;
	cpyRoomStrOld = team->getCaptureCopy();
	CpyLimit *_cpyLimt;
	int roomNum;
	cout<<"cpyRoomStrOld:"<<cpyRoomStrOld<<endl;
	if(!cpyRoomStrOld.empty())
	{
		/*回收队伍已经预定的房间号 add by chenzhen 201301241423*/
		if(dealTeamEntCpyAsist(cpyRoomStrOld,_cpyLimt,roomNum))
		{
			cout<<"go deal team fail:"<<endl;
			
			_cpyLimt = getCpylimit(cpyRoomStrOld);	
			
			if(_cpyLimt != NULL)
			{				
				cout<<"cancel the deal roomnum before:"<<roomNum<<endl;
				_cpyLimt->recoverRom(roomNum);
			}
			cout<<"cancel the deal roomnum end:"<<roomNum<<endl;
		}
		cpyRoomStrOld.clear();
	}
	team->initCaptureCopyId();

   

    string cpyParty;
    if(isParty)
    {
        /*队长请求加入帮派副本*/
        if(!judgeSameParty(heroId_unit))
        {
            cpyParty = "6";
            cpyParty += ",9,0";
            /*失败消息广播*/
            int personMem ;         
            for(personMem = 0;personMem < team_unit.size();personMem++)
            {
                send_msg(team_unit[personMem]->getFd(), const_cast<char*>(cpyParty.c_str()));
            }
            send_msg(teamLeader->getFd(), const_cast<char*>(cpyParty.c_str())); 
            return;
        }
    }
	
    map<string,CpyLimit*>::iterator cpyLimt_it = cpyId_to_cpyLimit.find(cpyId);
    if(cpyLimt_it != cpyId_to_cpyLimit.end())
    {
        string fbRoom;
        Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason)); 
        failure_reason->size = 0;           //初始化用于获取进入副本失败原因的结构体
		
		if(!initFailReson(failure_reason))
		{
			cout<<"failure_reason is NULL:"<<endl;	
			free(failure_reason);	//memory leak :tory_add 2013.1.26
			return;
		}

        //组队进普通副本资格审查
        CpyLimit* my_cpy_limit = cpyLimt_it->second;
		
		/*队伍里面就只有队长一人的情况*/
		if(heroId_unit.size() == 1)
		{
			/*资格审查*/
			if(!my_cpy_limit->qualifyExam(heroId_unit,failure_reason,false,isParty))
			{			
				dealFailRson(failure_reason,failMsg,sizeof(failMsg));
				sendFailMsg(heroId_unit,failMsg);			
				free(failure_reason);			
				return;
			}
	
			my_cpy_limit->assignRom(heroId_unit);
			free(failure_reason); 
			return;
		}
		
        fbRoom = my_cpy_limit->enable_enter_cpy(heroId_unit, failure_reason,isParty);

        if(fbRoom.size() != 0)      //副本分配成功
        {
            string msg_broadcast = "6";
            msg_broadcast += intTostring(TEAM_LEADER_OPERATE_RETURN);
            msg_broadcast += charTostring(inst_name);               //返回副本名字
            msg_broadcast += intTostring(inst_level);   

            //向队员发送邀请挑战副本的广播
            int i = 0;
            while(i < team_unit.size())
            {
                Hero* other_hero = team_unit[i];
               if(strcmp(other_hero->getIdentity(), heroId) != 0)
               {
                    send_msg(other_hero->getFd(), const_cast<char*>(msg_broadcast.c_str()));  
                    // i++;
               }
               i++;
            }           
	
			//锁定副本，并开启锁定计时器60s（原子操作） <tory>
			team->holdCaptureCopyId(fbRoom.c_str());			
			return;
        }
		else    //副本分配失败，读取failure_reason返回给队长
        {
            string msg_broadcast;
            msg_broadcast += intTostring(INST_COMMUNICATION);
            msg_broadcast += intTostring(TEAM_LEADER_OPERATE_RESULT);       

            //向队长返回挑战副本失败的原因
            int i = 0;
            while(i < failure_reason->size)
            {
                msg_broadcast += intTostring(failure_reason->member[i].failure_flag);
                msg_broadcast += charTostring(failure_reason->member[i].nickName);  
                i++;
            }
            msg_broadcast.erase(msg_broadcast.begin());
            cout<<"failure enter cpy::msg_broadcast:"<<msg_broadcast<<endl;
            //向队长返回挑战副本失败的消息

            /*失败消息广播*/
            int person ;            
            for(person = 0;person < team_unit.size();person++)
            {
                send_msg(team_unit[person]->getFd(), const_cast<char*>(msg_broadcast.c_str()));
            }

            // send_msg(teamLeader->getFd(), const_cast<char*>(msg_broadcast.c_str())); 

            free(failure_reason);           
        }
    } 
}

/*
* author：	Tory
* date:		2012.9.27 
* Description：回复队长的副本邀请
 */
void accept_invite(char* buffer)
{
    //解析角色ID
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(char* heroId);
	cout<<"@@Tory: heroId:"<<heroId<<endl;
	
    //解析队员对队长邀请进入副本的回复
	MSG_INT(int isAgree);
	cout<<"@@Tory: isAgree:"<<isAgree<<endl;

    //获得角色下的队伍Id 
    const char* teamId = pg_hero->getTeamerId();
	
    if(strlen(teamId) == 0)
	{
        return ;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"accept_invite team is NULL:"<<endl;
		return;		
	}
    
	if(strlen(team->getCaptureCopy()) == 0)	//没有锁定的副本
	{
		return;
	}
	
	vector<string> heroId_unit;
	team->getTeamMemberId(heroId_unit);
	if(isAgree == 0)                //同意队长邀请进入副本
    {
       team->addAgreeNum();	//增加队伍中同意进入副本的计数器	
		
		CpyLimit *_cpyLimt = NULL;
		int roomNum = -1;
		if(team->getAgreeNum() == (team->size()-1) )	//全部同意进入普通副本,则对所有队员发送跳转消息
		{
            if(dealTeamEntCpyAsist(team->getCaptureCopyId(), _cpyLimt, roomNum))
            {				
                _cpyLimt = getCpylimit(team->getCaptureCopyId());				
				if(_cpyLimt != NULL)
				{
					_cpyLimt->assignRom(heroId_unit, roomNum);		
				}
            }
	#if 0		
			if(strncmp(team->getCaptureCopyId(),"008",3) == 0)	//全部同意进塔防副本
			{
				Inst_MNG->teamEnter(team);
			}
	#endif
			//停止队伍下的副本锁定计时器，并将锁定的副本房间ID清空
			team->initCaptureCopyId();
			team->initAgreeNum();
			return ;
		
		}

		
    } 
	else                           //有成员不同意队长的邀请，向其他成员广播此玩家的消息
    {
        string msg_broadcast = "6";
        msg_broadcast += intTostring(REJECT_ACCEPT);
        msg_broadcast += charTostring(pg_hero->getNickName());
        cout<<"rejectiong msg:"<<msg_broadcast<<endl;

        int i = 0;
        for(i ;i < heroId_unit.size(); i++)
        {
            map<string, Hero*>::iterator team_hero_it = heroId_to_pHero.find(heroId_unit[i]);
            if(team_hero_it == heroId_to_pHero.end())
            {
                continue;
            } else
            {
                Hero* other_hero = team_hero_it->second;
                if(strcmp(other_hero->getIdentity(), team->getHeader()) == 0)
                    send_msg(other_hero->getFd(), const_cast<char*>(msg_broadcast.c_str()));
            }
        }		
		/*add by chenzhen 201301291744*/
		team->initCaptureCopyId(true);
    }

}

/*组队副本辅助函数*/
bool dealTeamEntCpyAsist(string cpyRomStr,CpyLimit *_cpyLimt,int &roomNum)
{
    string cpyId,roomNumStr;
    int found;
	_cpyLimt = NULL;
    map<string,CpyLimit*>::iterator cpyLimt_it; 

    if(cpyRomStr.size() < 1)
    {
        return false;
    }

    found = cpyRomStr.find_last_of("_");
    if(found == string::npos)
    {
        return false;
    }

    cpyId = cpyRomStr.substr(0,found);

    cpyLimt_it = cpyId_to_cpyLimit.find(cpyId);

    if(cpyLimt_it == cpyId_to_cpyLimit.end())
    {
        return false;
    }

    _cpyLimt = cpyLimt_it->second;

    /*截取副本房间号id*/
    roomNumStr = cpyRomStr.substr(found + 1);
    roomNum = atoi(roomNumStr.c_str());

    if(roomNum < 0)
    {
        return false;
    }
    return true;
}


/*组队副本辅助函数*/
CpyLimit* getCpylimit(string cpyRomStr)
{
    string cpyId,roomNumStr;
    int found;

    map<string,CpyLimit*>::iterator cpyLimt_it; 

    if(cpyRomStr.size() < 1)
    {
        return NULL;
    }

    found = cpyRomStr.find_last_of("_");
    if(found == string::npos)
    {
        return NULL;
    }

    cpyId = cpyRomStr.substr(0,found);

    cpyLimt_it = cpyId_to_cpyLimit.find(cpyId);

    if(cpyLimt_it == cpyId_to_cpyLimit.end())
    {
        return NULL;
    }

    return cpyLimt_it->second;
}


/*
* author:xhm
* amend: tory
* 函数参数: inst_typeId,010_0,010_1,010_2 将要进入的塔防副本的类型ID
* 返回值：0,进入副本成功
*/
int enterTowerDefRoom(Hero *heroPtr, char *inst_typeId)
{

}

/*
* author: tory
* date:2012.12.12
* describe:角色退出塔防副本
*/
void exitFromTowerDefence(Hero *hero)
{
    if (hero == NULL)	return;
    if (strncmp(hero->getFbRom(), "008", 3) != 0) return;   //不是在塔防副本中，禁止调用该方法

    TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(hero->getFbRom());
    if (NULL == tdRoom)	return;
                             
	//切换地图
    bool isSuccess = Inst_MNG->exit_inst_room(hero, tdRoom);  //将角色切到进副本前的地图中
    if (isSuccess == false)	return;
    hero->setFbRom("");     //将角色的副本ID置空

    //检测当前副本房间是否可以回收
    if (tdRoom->heroPtr_vec.size() == 0)
    {
        cout << "@@Tory 1000 will reset tower_defence_inst" << endl;
        Inst_MNG->stop_instancing(tdRoom);
        tdRoom->reset();        //reset塔防副本数据
        Inst_MNG->idleRooms.push_back(tdRoom);
    }
}

/*
函数参数；heroPtr：队长； team：队伍实例
  返回值：bool 
函数作用：检测队员是否在队长周围
*/
bool isAround(Hero *heroPtr, Team *team)
{

    vector<string> teamMember;             //获取所有队员ID；
	team->getTeamMemberId(teamMember);
    for (vector<string>::iterator memIter = teamMember.begin(); memIter != teamMember.end(); memIter++)
    {
        Hero *myHero = heroid_to_hero(*memIter);
        if (myHero == NULL) return false;
        int isNear = attackRangePoint(heroPtr->getLocation(), myHero->getLocation(), 300);  //需在300像素内,返回1；否则返回0
        if (isNear != 1)	return false;
    }

    return true;
}


void handleTeamLeaderOperateAsist(const char *heroId,const char *inst_id,int inst_level)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};    
    bool isParty = false;
    
	if(!heroId || !inst_id)
	{
		cout<<"handleTeamLeaderOperateAsist the argument is error:"<<endl;
		return;
	}
	
	/*帮派副本*/
    if(inst_level == 3)
    {
        isParty = true;
    }
	
	// 生成副本类型ID（副本类型+副本难度 tory）
	char cpyId[50] = {0};
	strncpy(cpyId, inst_id, sizeof(cpyId));	
	strncat(cpyId,"_",strlen("_"));	
    appendNum(cpyId, inst_level, 1);

#if 0
	//如果是塔防副本ID，则进入塔防副本的副本申请函数
	if(strncmp(cpyId,"008",3) == 0)
	{
		Inst_MNG->apply_td_inst(pg_hero, cpyId);
		return;
	}
#endif
    Hero *teamLeader = pg_hero;
    //获得角色下的队伍Id 
	if(strlen(teamLeader->getTeamerId()) == 0)
        return ;
	
    TeamManager* teamManger = TeamManager::getManagerInst();
	
	Team *team = teamManger->getTeamHandle(teamLeader->getTeamerId());
		
	if(!team)
	{
		cout<<"handleTeamLeaderOperateAsist team is NULL:"<<endl;
		return ;		
	}
	
	//不是队长，没有权限
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"handleTeamLeaderOperateAsist you are not header :"<<pg_hero->getIdentity()<<endl;
		char failMsgTeam[200] = {'\0'};
		sprintf(failMsgTeam,"6,7,%d,%s",ERROR_IN_TEAM,pg_hero->getNickName());
		send_msg(pg_hero->getFd(),failMsgTeam);	
		return;
	}

    //获得队伍中的在线成员的指针实例
    vector<Hero *> team_unit;
	vector<string> heroId_unit;
	team->getTeamMemberId(heroId_unit);
	
	for (vector<string>::iterator memIter = heroId_unit.begin(); memIter != heroId_unit.end(); ++memIter)
	{
            map<string, Hero *>::iterator iterHero = heroId_to_pHero.find(*memIter);
            if (iterHero == heroId_to_pHero.end()) continue;
            Hero *myHero = iterHero->second;
            if (myHero != NULL) 
			{
				team_unit.push_back(myHero);
			}

	}

	
	/*add chenzhen 20130128 重置队伍预定房间*/
	if(strlen(team->getCaptureCopy()) != 0)
	{
		team->initCaptureCopyId(true);
	}   

    string cpyParty;
    if(isParty)
    {
        /*队长请求加入帮派副本*/
        if(!judgeSameParty(heroId_unit))
        {
            cpyParty = "6";
            cpyParty += ",9,0";
            /*失败消息广播*/
            int personMem ;         
            for(personMem = 0;personMem < team_unit.size();personMem++)
            {
                send_msg(team_unit[personMem]->getFd(), const_cast<char*>(cpyParty.c_str()));
            }
            send_msg(teamLeader->getFd(), const_cast<char*>(cpyParty.c_str())); 
            return;
        }
    }
	
    map<string,CpyLimit*>::iterator cpyLimt_it = cpyId_to_cpyLimit.find(cpyId);
    if(cpyLimt_it != cpyId_to_cpyLimit.end())
    {
        string fbRoom;
        Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason)); 
        failure_reason->size = 0;           //初始化用于获取进入副本失败原因的结构体
		
		if(!initFailReson(failure_reason))
		{
			cout<<"failure_reason is NULL:"<<endl;	
			free(failure_reason);	//memory leak :tory_add 2013.1.26
			return;
		}

        //组队进普通副本资格审查
        CpyLimit* my_cpy_limit = cpyLimt_it->second;
		
		/*队伍里面就只有队长一人的情况*/
		if(heroId_unit.size() == 1)
		{
			/*资格审查*/
			if(!my_cpy_limit->qualifyExam(heroId_unit,failure_reason,false,isParty))
			{			
				dealFailRson(failure_reason,failMsg,sizeof(failMsg));
				sendFailMsg(heroId_unit,failMsg);			
				free(failure_reason);			
				return;
			}
	
			my_cpy_limit->assignRom(heroId_unit);
			free(failure_reason); 
			return;
		}
		
		char inst_name[100] = {'\0'};
		
		strncpy(inst_name,my_cpy_limit->getName(),strlen(my_cpy_limit->getName()));
		
        fbRoom = my_cpy_limit->enable_enter_cpy(heroId_unit, failure_reason,isParty);

        if(fbRoom.size() != 0)      //副本分配成功
        {
            string msg_broadcast = "6";
            msg_broadcast += intTostring(TEAM_LEADER_OPERATE_RETURN);
            msg_broadcast += charTostring(inst_name);               //返回副本名字
            msg_broadcast += intTostring(inst_level);   

            //向队员发送邀请挑战副本的广播
            int i = 0;
            while(i < team_unit.size())
            {
                Hero* other_hero = team_unit[i];
               if(strcmp(other_hero->getIdentity(), heroId) != 0)
               {
                    send_msg(other_hero->getFd(), const_cast<char*>(msg_broadcast.c_str()));  
               }
               i++;
            }           
	
			//锁定副本，并开启锁定计时器60s（原子操作） <tory>
			team->holdCaptureCopyId(fbRoom.c_str());			
			return;
        }
		else    //副本分配失败，读取failure_reason返回给队长
        {
            string msg_broadcast;
            msg_broadcast += intTostring(INST_COMMUNICATION);
            msg_broadcast += intTostring(TEAM_LEADER_OPERATE_RESULT);       

            //向队长返回挑战副本失败的原因
            int i = 0;
            while(i < failure_reason->size)
            {
                msg_broadcast += intTostring(failure_reason->member[i].failure_flag);
                msg_broadcast += charTostring(failure_reason->member[i].nickName);  
                i++;
            }
            msg_broadcast.erase(msg_broadcast.begin());
            cout<<"failure enter cpy::msg_broadcast:"<<msg_broadcast<<endl;
            //向队长返回挑战副本失败的消息

            /*失败消息广播*/
            int person ;            
            for(person = 0;person < team_unit.size();person++)
            {
                send_msg(team_unit[person]->getFd(), const_cast<char*>(msg_broadcast.c_str()));
            }

            free(failure_reason);           
        }
    } 
}
