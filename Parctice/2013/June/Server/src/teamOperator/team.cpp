#include"team.h"
#include"command_other_function_all_over.h"
#include"teamAsist.h"
#include"teamOperator.h"
#include"cpyLimit.h"
#include "instancing_manage.h"
#include"instancing_communication.h"
#include"teamMem.h"
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern struct ev_loop *loops;
extern Instancing_manage *Inst_MNG; 

Team::Team(size_t _index):index(_index)
{
	memset(teamId,'\0',sizeof(teamId));
	
	init();
	
	createTeamId();
}

void Team::createTeamId()
{
	char * temp = cid();
	if(!temp)
	{
		cout<<"Team::createTeamId the temp is NULL error:"<<endl;		
		return;
	}
	strncpy(teamId,temp,strlen(temp));		
	free(temp);
}

void Team::init()
{
	initCaptureCopyId(true);
	memInvite = false;	
	memset(header,'\0',sizeof(header));	
	memset(teamMemMsg,'\0',sizeof(teamMemMsg));		
	memberIdSet.clear();
	agreeNum = 0;
}

Team::Team(const Team &team)
{
	
}

Team::~Team()
{
	init();
	memset(teamId,'\0',sizeof(teamId));
}

Team& Team::operator=(const Team &team)
{
	return *this;
}

const char* Team::captureTeam(const char* leaderId)
{
	
	if(!insertMemSet(leaderId))
	{
		return NULL;
	}
	
	strncpy(header,leaderId,strlen(leaderId));	
	
	return teamId;	
}

const char* Team::join(const char *teamMemId)
{
	if(!insertMemSet(teamMemId))
	{
		return NULL;
	}
	return teamId;	
}

bool Team::insertMemSet(const char *memId)
{
	if(!memId)
	{
		return false;
	}
	
	TeamMemInfo memInfo(memId);
	
	pair<set<TeamMemInfo>::iterator,bool> result_it = memberIdSet.insert(memInfo);
	
	if(result_it.second)
	{		
		return true;
	}
	
	return false;
}

bool Team::eraseMemSet(const char *memberId)
{
	if(!memberId)
	{
		return false;
	}
	
	TeamMemInfo memInfo(memberId);
	
	size_t result = memberIdSet.erase(memInfo);
	
	if(result == 1)
	{
		if(isHeader(memberId))
		{
			passHeader();
		}		
		return true;
	}	
	return false;
}

const char* Team::getTeamId() const
{
	return teamId;
}

const char* Team::getHeader() const
{
	return header;
}

size_t Team::size() const
{
	return memberIdSet.size();
}

bool Team::isInTeam(const char* memberId) const
{
	if(!memberId)
	{
		return false;
	}
	
	TeamMemInfo memInfo(memberId);
	
	set<TeamMemInfo>::const_iterator mem_it = memberIdSet.find(memInfo);
	
	if(mem_it == memberIdSet.end())
	{
		return false;
	}
	
	return true;
}

//是否是队长
bool Team::isHeader(const char* memberId) const
{
	if(!memberId || strlen(memberId) == 0)
	{
		return false;
	}
	if(strncmp(header,memberId,strlen(header)) == 0)
	{
		return true;
	}
	
	return false;
}

bool Team::getMemInvite(void) const
{
	return memInvite;
}

//只有队长才有权限设置成员是否有邀请别人进队的资格
void Team::setMemInvite(bool _memInvite)
{
	memInvite = _memInvite;
}

//发送队伍消息
void Team::sendMsg(const char* teamMsg) const
{
	if(memberIdSet.empty() || !teamMsg || strlen(teamMsg) == 0)
	{
		cout<<"Team::sendMsg the memberIdSet is empty or the  argument is error:"<<endl;
		return;
	}
	
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		if(!(*mem_it).onLine)
		{
			continue;
		}
		
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
			send_msg(memHero->getFd(),teamMsg);
		}
	}
}

void Team::formTeamMemMsg(void)
{
	memset(teamMemMsg,'\0',sizeof(teamMemMsg));
	
	if(strlen(header) == 0)
	{
		cout<<"Team::formTeamMemMsg the header is empty:"<<endl;
		return;
	}
	
	sprintf(teamMemMsg,"%d,%d,%d,%s,%d",BRAUSH_TEAM_HEAD_F,BRAUSH_TEAM_HEAD_S,1,header,(int)memberIdSet.size());
	
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
			(const_cast<TeamMemInfo *>(&(*mem_it)))->assignVal(memHero);			
		}
		else
		{
			(const_cast<TeamMemInfo *>(&(*mem_it)))->onLine = false;
		}
		
		sprintf(teamMemMsg + strlen(teamMemMsg),",%s,%s,%d,%s,%d,%d,%d,%d,%d",(*mem_it).memId,(*mem_it).nickName,\
		(int)(*mem_it).level,(*mem_it).party,(int)(*mem_it).lifeVal,(int)(*mem_it).lifeUpperVal,(int)(*mem_it).magic,\
		(int)(*mem_it).magicUpperVal,(*mem_it).onLine);
			
	}
}

const char* Team::getTeamMemMsg() const
{
	return teamMemMsg;
}

void Team::setCaptureCopy(const char* copyId)
{
	memset(captureCopyId,'\0',sizeof(captureCopyId));
	
	if(!copyId)
	{
		cout<<"Team::setCaptureCopy the copyId is NULL:"<<endl;
		return;
	}
	
	strncpy(captureCopyId,copyId,strlen(copyId));
}

const char* Team::getCaptureCopy(void) const
{
	return  captureCopyId;
}

//队友下线
bool Team::memOffLine(const Hero* memberHero) 
{
	if(!memberHero)
	{
		return false;
	}
	
	TeamMemInfo memInfo(memberHero->getIdentity());
	
	set<TeamMemInfo>::iterator mem_it = memberIdSet.find(memInfo);
	
	if(mem_it == memberIdSet.end())
	{
		return false;
	}
	
	(const_cast<TeamMemInfo *>(&(*mem_it)))->assignVal(memberHero);
	
	(const_cast<TeamMemInfo*>((&(*mem_it))))->onLine = false;
	
	//队长离线，则转让队长
	if(strncmp(header,memberHero->getIdentity(),strlen(header)) == 0)
	{
		passHeader();
	}
	
	return true;
}


//队伍在线人数
size_t Team::memOnLineSize() const
{
	size_t memOnLineCtn = 0;
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		if((*mem_it).onLine)
		{
			memOnLineCtn += 1;
		}
	}
	return memOnLineCtn;
}


void Team::initTimer(void)
{
	ev_timer_stop(loops,&bindCopyRoomTmer);	
	ext_ev_timer_init(&bindCopyRoomTmer,teamBindCal,TEAM_BIND_COPYROOM_TIME,0,this);
	ev_timer_start(loops,&bindCopyRoomTmer);
}


void Team::stopTimer(void)
{
	ev_timer_stop(loops,&bindCopyRoomTmer);	
}


void Team::passHeader()
{	
	
	if(memberIdSet.empty())
	{
		memset(header,'\0',sizeof(header));
		cout<<"Team::passHeader the memberIdSet is empty:"<<endl;		
		return;
	}
	
	for(set<TeamMemInfo>::const_iterator mem_it = memberIdSet.begin(); mem_it != memberIdSet.end();++mem_it)
	{
		if(strcmp(header,(*mem_it).memId) == 0)
		{
			continue;
		}
		
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
				
			strncpy(header,(*mem_it).memId,strlen((*mem_it).memId));
			return;
		}
	}
}
	

void Team::disMissTeam(const char* disMissMsg) const
{
	if(memberIdSet.empty() || !disMissMsg || strlen(disMissMsg) == 0)
	{
		cout<<"memberIdSet is empty or the disMissMsg is NULL:"<<endl;
		return;
	}
			
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
			send_msg(memHero->getFd(),disMissMsg);
			memHero->initTeamerId();
		}
	}
}

bool Team::passHeader(const char *newLeaderId)
{
	memset(header,'\0',sizeof(header));
	
	if(memberIdSet.empty() || !newLeaderId || strlen(newLeaderId) == 0)
	{
		cout<<"Team::passHeader the memberIdSet is empty or the argument is error:"<<endl;
		return false;
	}
	TeamMemInfo memInfo(newLeaderId);
	set<TeamMemInfo>::iterator mem_it = memberIdSet.find(memInfo);
	
	if(mem_it == memberIdSet.end())
	{
		cout<<"Team::passHeader the newLeaderId is not in team:"<<newLeaderId<<endl;
		return false;
	}
	
	if(!(*mem_it).onLine)
	{
		cout<<"Team::passHeader the newLeaderId is offLine:"<<newLeaderId<<endl;
		return false;
	}
	
	strncpy(header,newLeaderId,strlen(newLeaderId));	
	
	return true;
}


void Team::initCaptureCopyId(bool _isRecover)
{
	ev_timer_stop(loops,&bindCopyRoomTmer);	
	
	if(_isRecover)
	{
		recoverCpyRoom();	
		initAgreeNum();
	}	
	
	memset(captureCopyId,'\0',sizeof(captureCopyId));
}

const char* Team::getCaptureCopyId(void) const
{
	return captureCopyId;
}

void Team::holdCaptureCopyId(const char *_captureCopyId)
{
	if(!_captureCopyId || strlen(_captureCopyId) == 0)
	{
		cout<<"Team::holdCaptureCopyId the argument is error:"<<teamId<<endl;
		return;
	}
	memset(captureCopyId,'\0',sizeof(captureCopyId));
	strncpy(captureCopyId,_captureCopyId,strlen(_captureCopyId));
	initTimer();
}

const set<TeamMemInfo>& Team::getMemberInfo() const 
{
	return memberIdSet;
}

void Team::getTeamMemberId(vector<string>& teamMemberIdVec) 
{
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		teamMemberIdVec.push_back((*mem_it).memId);
	}
}

void Team::addAgreeNum()
{
	++agreeNum;
}

size_t Team::getAgreeNum() const
{
	return agreeNum;
}

void Team::initAgreeNum()
{
	agreeNum = 0;
}


void Team::recoverCpyRoom()
{	
	if(strlen(captureCopyId) == 0)
	{
		return;
	}
#if 0		
	if(strncmp(captureCopyId,"008",3) == 0)	//塔防副本
	{
		TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(captureCopyId);
		if (NULL == tdRoom)	
		{
			return;
		}
		
		tdRoom->reset();        //reset塔防副本数据
		Inst_MNG->idleRooms.push_back(tdRoom);	
		
		return;
	}
#endif	
	CpyLimit *_cpyLimt;
	int roomNum;	
	
	/*回收队伍已经预定的房间号 add by chenzhen 201301291735*/
	if(dealTeamEntCpyAsist(captureCopyId,_cpyLimt,roomNum))
	{
		cout<<"go to deal the team captureCopyId begin:"<<captureCopyId<<endl;
			
		_cpyLimt = getCpylimit(captureCopyId);
	
				
		if(_cpyLimt != NULL)
		{		
			cout<<"go to recover  team roomNum begin:"<<roomNum<<endl;
			_cpyLimt->recoverRom(roomNum);
			cout<<"go to recover  team roomNum end:"<<roomNum<<endl;
		}
				
		cout<<"go to deal the team captureCopyId end:"<<captureCopyId<<endl;
	}
	
}

//发送队伍消息,屏蔽某个人
void Team::sendMsg(const char* teamMsg,const char* exceptMemId) const
{
	if(memberIdSet.empty() || !teamMsg || strlen(teamMsg) == 0 || !exceptMemId || strlen(exceptMemId) == 0)
	{
		cout<<"Team::sendMsg the memberIdSet is empty or the  argument is error:"<<endl;
		return;
	}
	
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		if(!(*mem_it).onLine || strcmp((*mem_it).memId,exceptMemId) == 0)
		{
			continue;
		}
		
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
			send_msg(memHero->getFd(),teamMsg);
		}
	}
}

//组队分配物品
bool Team::assignGoods(const char* goodsId,int num)
{
	size_t randIndx = 0,index = size();
	char goodsMsg[1000] = {'\0'};
	Hero *memHero=NULL;
	set<TeamMemInfo>::iterator mem_it;
	
	vector<TeamMemInfo> temp;
	temp.clear();
	
	for (mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{
		if ((*mem_it).onLine)
		{
			temp.push_back(*mem_it);
		}
	}
	
	int numberMax=temp.size();
	
	int randomNumber=random_number(0,numberMax-1);
	
	if (numberMax==0)
	{
		return false;
	}
	
	if (randomNumber<0||randomNumber>numberMax-1)
	{
		randomNumber=0;
	}
	
	memHero = heroid_to_hero(temp[randomNumber].memId);
	
	if (memHero!=NULL)
	{
		if(saveGoodsInBag(memHero,const_cast<char*>(goodsId),num))
		{
			sprintf(goodsMsg,"4,12,%s,%s,%s",memHero->getIdentity(),memHero->getNickName(),goodsId);
			sendMsg(goodsMsg);
			return true;
		}
	}	
	
	return false;
}

void Team::formTeamMemMsg(const char* expectMemHeroId)
{
	memset(teamMemMsg,'\0',sizeof(teamMemMsg));
	
	if(strlen(header) == 0 || !expectMemHeroId)
	{
		cout<<"Team::formTeamMemMsg the header is empty:"<<endl;
		return;
	}
	
	sprintf(teamMemMsg,"%d,%d,%d,%s,%d",BRAUSH_TEAM_HEAD_F,BRAUSH_TEAM_HEAD_S,1,header,(int)memberIdSet.size());
	
	for(set<TeamMemInfo>::iterator mem_it = memberIdSet.begin();mem_it != memberIdSet.end();++mem_it)
	{			
		Hero *memHero = heroid_to_hero((*mem_it).memId);
		if(memHero)
		{
			(const_cast<TeamMemInfo *>(&(*mem_it)))->assignVal(memHero);	
			if(strcmp((*mem_it).memId,expectMemHeroId) == 0)
			{
				(const_cast<TeamMemInfo *>(&(*mem_it)))->onLine = false;
			}
		}
		else
		{
			(const_cast<TeamMemInfo *>(&(*mem_it)))->onLine = false;
		}
		
		sprintf(teamMemMsg + strlen(teamMemMsg),",%s,%s,%d,%s,%d,%d,%d,%d,%d",(*mem_it).memId,(*mem_it).nickName,\
		(int)(*mem_it).level,(*mem_it).party,(int)(*mem_it).lifeVal,(int)(*mem_it).lifeUpperVal,(int)(*mem_it).magic,\
		(int)(*mem_it).magicUpperVal,(*mem_it).onLine);
			
	}
}


