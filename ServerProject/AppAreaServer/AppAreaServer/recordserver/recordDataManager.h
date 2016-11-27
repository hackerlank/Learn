#ifndef RECORD_DATA_MANAGER_H
#define RECORD_DATA_MANAGER_H
#include "singleton.h"

class RecordDataManager : public Singleton<RecordDataManager>
{
    private:
        RecordDataManager();
        ~RecordDataManager();
        friend class Singleton<RecordDataManager>;
        bool loadUserData();
    public:
        bool init();
        bool createUser(const std::string &phone,unsigned long &charID);
        bool loop();
    private:
        static unsigned long s_charID;
};

#endif
