
#include"teamManager.h"
#include"team.h"
TeamManager* TeamManager::teamManager = NULL;
TeamManager::TeamManager(size_t teamNum)
{
	for(size_t index = 0;index < teamNum;++index)
	{
		try
		{
			Team *newTeam = new Team(index);
			teamVec.push_back(newTeam);
			usefulIndexlist.push_back(index);
		}
		catch(exception e)
		{
			throw e;
		}
	}
	
	totalSize = teamNum;
}

TeamManager::TeamManager(const TeamManager &teamManagers)
{

}


TeamManager& TeamManager::operator=(const TeamManager &teamManagers)
{
	return *this;
}

//创建单例
void TeamManager::createManagerInst(size_t teamNum)
{
	if(!teamManager)
	{
		try
		{
			teamManager = new TeamManager(teamNum);
		}
		catch(exception e)
		{
			throw e;
		}
	}
}

//返回一个单例实例指针
TeamManager* TeamManager::getManagerInst()
{	
	if(!teamManager)
	{
		createManagerInst(100);
	}
	return teamManager;
}

//占据一个群实例，返回实例id
const char* TeamManager::captureTeamHandle(const char *teamLeader)
{
	if(!teamLeader)
	{
		return NULL;
	}
	
	if(!usefulIndexlist.empty())
	{
		size_t index = usefulIndexlist.front();
		Team* team = teamVec[index];				
		pair<map<string,int>::iterator,bool> inset_it = usedTeamIdIndexMap.insert(pair<string,int>(team->getTeamId(),index));
		
		if(!inset_it.second)
		{
			cout<<"TeamManager::captureTeamHandle is camped or the index  before error:"<<index<<endl;
			return NULL;
		}
		usefulIndexlist.pop_front();
		
		return team->captureTeam(teamLeader);
	}
	else
	{
		size_t damamicIndex;
		Team *team = NULL;
		if(useAbledynamicIndex.empty())
		{
			damamicIndex = totalSize;
			++totalSize;
		}
		else
		{
			damamicIndex = useAbledynamicIndex.front();			
		}
				
		//正在使用的下标又多了一个
		pair<set<int>::iterator,bool> insert_it = usedDynamicIndex.insert(damamicIndex);
		
		//如果数据异常
		if(!insert_it.second)
		{
			cout<<"TeamManager::captureTeamHandle the dynamicIndex is camped or the index  before error:"<<damamicIndex<<endl;
			return NULL;
		}
		
		try
		{
			team = new Team(damamicIndex);				
		}
		catch(exception e)
		{
			throw e;
		}
		
		pair<map<string,int>::iterator,bool> inset_it = usedTeamIdIndexMap.insert(pair<string,int>(team->getTeamId(),damamicIndex));
		//数据异常
		if(!inset_it.second)
		{
			cout<<"TeamManager::captureTeamHandle the index is exist before :"<<damamicIndex<<endl;
			delete team;
			team = NULL;
			return NULL;
		}
		
		//补空孔
		if(damamicIndex - teamVec.size() < dynamicTeamVec.size())
		{
			dynamicTeamVec[damamicIndex] = team;
	
			//可以利用的空孔又少了一个呀
			useAbledynamicIndex.pop_front();
		}
		//往后追加
		else
		{
			dynamicTeamVec.push_back(team);
		}		
		
		return team->captureTeam(teamLeader);	
	}
}

//获得gruopId对应的群句柄
Team* TeamManager::getTeamHandle(const char* teamId)
{
	if(!teamId)
	{
		cout<<"TeamManager::getTeamHandle teamId is NULL:"<<endl;
		return NULL;
	}
	map<string,int>::iterator index_it;
	index_it = usedTeamIdIndexMap.find(teamId);
	if(index_it == usedTeamIdIndexMap.end())
	{
		cout<<"TeamManager::getTeamHandle teamId is not found:"<<teamId<<endl;
		return NULL;
	}
	if(index_it->second < teamVec.size())
	{
		return teamVec[index_it->second];
	}
	
	return dynamicTeamVec[index_it->second - teamVec.size()];
}

//回收一个群
void TeamManager::recoverTeamHandle(const char* teamId)
{
	cout<<"TeamManager::recoverTeamHandle begin the  team resoure teamId:"<<teamId<<endl;
	
	if(!teamId)
	{
		return;
	}
	
	map<string,int>::iterator index_it;
	index_it = usedTeamIdIndexMap.find(teamId);
	if(index_it == usedTeamIdIndexMap.end())
	{
		cout<<"TeamManager::recoverTeamHandle the teamId is error:"<<teamId<<endl;
		return;
	}
	
	if(index_it->second < teamVec.size())
	{
		teamVec[index_it->second]->init();
		usefulIndexlist.push_front(index_it->second);
	}
	else
	{		
		Team *danamicNewTeam = dynamicTeamVec[index_it->second - teamVec.size()] ;	
		delete danamicNewTeam;
		danamicNewTeam = NULL;
		dynamicTeamVec[index_it->second - teamVec.size()] = NULL;
		size_t flg = usedDynamicIndex.erase(index_it->second);		
		//如果数据异常，那就找原因吧
		if(flg == 0)
		{
			cout<<"TeamManager::recoverTeamHandle erase the index is error:"<<index_it->second<<endl;
		}		
		useAbledynamicIndex.push_front(index_it->second);
	}
	cout<<"TeamManager:: recoverTeamHandle success the  team resoure teamId:"<<teamId<<" index:"<<index_it->second<<endl;
	usedTeamIdIndexMap.erase(index_it);
}

//析构函数
TeamManager::~TeamManager()
{
	for(vector<Team*>::iterator team_it = teamVec.begin();team_it != teamVec.end();++team_it)
	{
		delete *team_it;
		*team_it = NULL;
	}
	
	for(vector<Team*>::iterator team_it = dynamicTeamVec.begin();team_it != dynamicTeamVec.end();++team_it)
	{
		delete *team_it;
		*team_it = NULL;
	}
	teamVec.clear();
	dynamicTeamVec.clear();
	usefulIndexlist.clear();
	usedDynamicIndex.clear();
	useAbledynamicIndex.clear();
	usedTeamIdIndexMap.clear();
	teamManager = NULL;	
}	

size_t TeamManager::size() const
{
	return totalSize;
}
