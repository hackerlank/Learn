
#ifndef DBBOSSMGR_H_
#define DBBOSSMGR_H_

#include "Singleton.h"
#include "BossProt.h"
#include "Game2DBCommS.h" // XXX: for SLoadWorldBossInfoAck

using namespace NBossProt;

class CDBBossMgr : public Singleton<CDBBossMgr>
{
public:
    CDBBossMgr() {}
    ~CDBBossMgr() {}

    void LoadWorldBoss(shared_func<CGame2DBCommSvr::SLoadWorldBossInfoAck>& fnAck);
    void SaveWorldBoss(const SWBossDBInfo& sBossInfo);
    void Init();
    void Insert(const SWBossDBInfo& sBossInfo);
private:
    NGame2DBComm::TVecWBossDBInfo _vecWorldBossInfo;

};

#endif // DBBOSSMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

