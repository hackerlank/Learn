#ifndef SIGNINMANAGER_H__
#define SIGNINMANAGER_H__
#include "stdafx.h"
#include "SignInCFG.h"
class CPlayer;
struct SSignInCFGEx :public SSignInCFG
{
    map<UINT16,UINT32> mapAward;
    SSignInCFGEx(const SSignInCFG&);
};
class CSignInManager
{
    public:
        bool Init();
        const SSignInCFGEx * GetCFGbyId(UINT16 wId);//获得签到奖励 
    private:
        map<UINT16,SSignInCFGEx> _mapCfg;//师门等级配置
};
extern CSignInManager g_CSignInManager;
#endif
