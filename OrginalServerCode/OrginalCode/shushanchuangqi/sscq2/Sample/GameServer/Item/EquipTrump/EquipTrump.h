// =====================================================================================
//
//       Filename:  EquipTrump.h
//
//    Description:  装备用的法宝
//
//        Version:  1.0
//        Created:  05/14/2015 02:46:14 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================
#ifndef EQUIP_TRUMP_H
#define EQUIP_TRUMP_H

#include "Item.h"
#include "BattlePoint.h"

#include "EquipTrumpProtSvr.h"

using namespace NEquipTrumpProt;

// =====================================================================================
//        Class:  CEquipTrump
//  Description:  散仙装备的法宝
// =====================================================================================
class CEquipTrump : public CItem, public CBattlePointOwner
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CEquipTrump (UINT16 wItemID);                             // constructor //
        virtual ~CEquipTrump();

        void InitAttr();

        // ====================  ACCESSORS     ======================================= //
        UINT64 GetOwnerID() const;

        UINT8 GetIntensify() const;

        virtual UINT8 GetEquipTrumpLevel() const
        {
            return _byIntensifyLvl;
        };

        virtual SItemPtr ToProt() const;
        bool ToStream(SEquipTrump& rStream) const;

        bool IsDirty() const;

        EEquipTrumpSlotType GetSlotType() const;

        void GetAttr(TVecFloat& rvecAttr) const;

        UINT32 GetSkillID() const;

        virtual void GetAllSkillsID(TVecUINT32& vecSkillsID) const;
        virtual void AppendBPAttr(TVecFloat& rvecAttr) const;

        // ====================  MUTATORS      ======================================= //
        
        void SetOwnerID(UINT64 qwOwnerID);
        bool FromStream(const SEquipTrump& rStream);
        void SetDirty(bool bDirty, CPlayerPtr pPlayer);

        // ====================  OPERATORS     ======================================= //
        
        //强化一次
        EEquipTrumpIntensifyResult IntensifyOnce(CUser& rUser,ETIntensifyType eType,bool& bSucess);

        // 强化
        EEquipTrumpIntensifyResult OnIntensify(CUser& rUser,ETIntensifyType eType,
                shared_func<CEquipTrumpProtSvr::SIntensifyAck>& fnAck);

        // 一键强化
        EEquipTrumpIntensifyResult OnIntensifyOneKey(CUser& rUser,ETIntensifyType eType,
                shared_func<CEquipTrumpProtSvr::SIntensifyOneKeyAck>& fnAck);

        // 洗炼
        EEquipTrumpShuffleResult OnShuffleResult(CUser& rUser,UINT32 dwLock);


        //获取强化等级
        UINT8 GetIntensifyLevel();
        
        //获取关联物品属性id
        UINT32 GetItemAttrID();

    private:
        // ====================  METHODS       ======================================= //
        bool GetRandomVec(SShuffleInfo& rMaxShuffleInfo, TVecShuffleInfo& vecRandom);

        FLOAT GetRandomRate(TVecXiLianProb& vecXiLianProb,UINT32 dwBlessValue,UINT8& bySelect);

        // ====================  DATA MEMBERS  ======================================= //
        UINT64  _qwOwnerID; // 所属散仙ID

        bool _bDirty;

        UINT8 _byIntensifyLvl;          // 强化等级
        UINT8 _byIntensifyLvlMax;       // 最高强化等级
        UINT32 _dwBlessing;
        UINT32 _dwXiLianBlessing;

        TVecShuffleInfo _vecMaxShuffleInfo;


}; // -----  end of class CEquipTrump  ----- //

#endif // EQUIP_TRUMP_H

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

