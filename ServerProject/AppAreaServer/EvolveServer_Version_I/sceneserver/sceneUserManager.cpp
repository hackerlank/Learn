#include "sceneUserManager.h"
#include "serialize.pb.h"
#include "flyer.h"

SceneUserManager::SceneUserManager()
{
}

SceneUserManager::~SceneUserManager()
{
}

bool SceneUserManager::add(boost::shared_ptr<SceneUser> user)
{
    std::pair<std::map<unsigned long,boost::shared_ptr<SceneUser> >::iterator,bool> ret = m_userMap.insert(std::pair<unsigned long,boost::shared_ptr<SceneUser> >(user->getCharID(),user));
    return ret.second;
}

void SceneUserManager::del(const unsigned long charID)
{
    m_userMap.erase(charID);
}

void SceneUserManager::loop()
{
    for(auto iter = m_userMap.begin();iter != m_userMap.end();++iter)
    {
        bool ret = false;
        boost::shared_ptr<SceneUser> user = iter->second;
        if(user)
        {
            ret = user->saveData();
        }
        if(!ret)
        {
            Debug(Flyer::logger,"[角色存档] 出错(" << iter->first << ")");
        }

    }
}
