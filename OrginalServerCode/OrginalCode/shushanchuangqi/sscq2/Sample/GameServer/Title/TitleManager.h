#ifndef TITLEMANAGER_H__
#define TITLEMANAGER_H__
#include "stdafx.h"
#include "TitleCFG.h"
enum  ETitleType
{
    ETitle_Common =1,
    ETitle_Rare,
    ETitle_Legend,
    Etitle_Max,
};
class CPlayer;
class CTitleManager
{
    public:
        bool Init();
        const STitleCFG * GetCFGbyId(UINT16 wId);//获得师门等级配 
        void FinishAchievement(CPlayer & rPlayer,UINT16 wId);
    private:
        map<UINT16,STitleCFG> _mapCfg;//师门等级配置
};
extern CTitleManager g_CTitleManager;
#endif
