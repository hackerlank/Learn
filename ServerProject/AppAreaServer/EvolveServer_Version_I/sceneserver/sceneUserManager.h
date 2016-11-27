#ifndef SCENE_USER_MANAGER_H
#define SCENE_USER_MANAGER_H
#include "head.h"
#include "sceneUser.h"
#include "singleton.h"

class SceneUserManager : public Singleton<SceneUserManager>
{
    private:
        SceneUserManager();
        ~SceneUserManager(); 
        friend class Singleton<SceneUserManager>;
    public:
        bool add(boost::shared_ptr<SceneUser> user);
        void del(const unsigned long charID);
        void loop();
    private:
        std::map<unsigned long,boost::shared_ptr<SceneUser> > m_userMap;
};

#endif
