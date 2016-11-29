#ifndef TITLE_H__
#define TITLE_H__
#include "stdafx.h"
#include "RoleInfoDefine.h"
#include "TitleProt.h"
#include "Parameter.h"
class CPlayer;
using namespace NRoleInfoDefine;
using namespace NTitleProt;
using namespace NProtoCommon;
class CTitlePkg
{
    public:
        CTitlePkg(CPlayer& rPlayer);
        void Init(const TVecTitle &rvec);
        void Update2DB(const STitle& rInfo,EDataChange eUpdateType);
        void GetAllTitle(TVecTitle &rvec);
        ETitleResult EquipTitle(UINT16 wId,UINT8 byPos,UINT8& byCurPos);
        void AddTitle(UINT16 wId,UINT32 dwIntralTime = 0, bool bAdd = true);    //dwIntralTime为0表示永久时效
        void DelTitle(UINT16 wId,bool bNoticeFighter = true);
        void TimerCheck(UINT32 dwNow);
        void GetAllTitleAttr(TVecFloat &rVecAttr);  //获得所有属性
        STitle * GetTitle(UINT16 wId);
        bool CheckTypeWithPos(UINT8 byType,UINT8 byPos);
        void NoticeFighter();
        void GetTitleApear(map<UINT8,UINT16> &rmapAppear);
    private:
        map<UINT16,STitle> _mapAllTitle;
        CPlayer& _rPlayer;
        TVecUINT16 _equip;
};
#endif

