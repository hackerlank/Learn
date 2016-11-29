
#ifndef EXPMGR_H_
#define EXPMGR_H_

#include "ExpCFG.h"

typedef shared_ptr<SExpCFG> SExpCFGPtr;
typedef std::vector<SExpCFGPtr> TVecExpCFGPtr;

class CExpMgr
{
public:
	CExpMgr();

    static bool Init();
    static bool LoadConfig(bool bReload = false);
    static bool ReLoadConfig(const string &);

    static SExpCFGPtr GetExpCfg(UINT8 byLevel);
    static float GetStoveAwardRate(UINT8 byLevel);
    static float GetStoveHelpRate(UINT8 byLevel);

private:
    static TVecExpCFGPtr _vecExpCFGPtr;
};

#endif // EXPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

