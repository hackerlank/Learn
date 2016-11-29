// =====================================================================================
//
//       Filename:  DrawMgr.h
//
//    Description:  求签总管理类
//
//        Version:  1.0
//        Created:  03/10/2015 05:39:33 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef DRAW_MGR_H
#define DRAW_MGR_H

#include "stdafx.h"

#include "Singleton.h"

#include "FighterProt.h"

using namespace NFighterProt;

typedef map<UINT16, CDrawDataPtr> MapDrawDataPtr;
typedef map<EDrawType, MapDrawDataPtr> MapTypeDrawDataPtr;

// =====================================================================================
//        Class:  CDrawMgr
//  Description:  求签总管理类
// =====================================================================================
class CDrawMgr : public Singleton<CDrawMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        virtual ~CDrawMgr();

        // ====================  ACCESSORS     ======================================= //
        CDrawDataPtr GetDrawData(EDrawType eType, UINT16 wLevel) const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        bool Init();

    private:
        // ====================  METHODS       ======================================= //
        bool LoadConfig(const string& strPath);

        // ====================  DATA MEMBERS  ======================================= //
        MapTypeDrawDataPtr _mapTypeDrawDataPtr;     // 求签配置数据

}; // -----  end of class CDrawMgr  ----- //

// =====================================================================================
//        Class:  CDrawData
//  Description:  求签配置数据
// =====================================================================================
class CDrawData
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CDrawData (UINT16 wLevel, EDrawType eType);                             // constructor //
        virtual ~CDrawData();

        // ====================  ACCESSORS     ======================================= //
        UINT16 GetLevel() const;
        EDrawType GetType() const;

        UINT32 GetSilver() const;
        UINT32 GetGold() const;

        UINT16 GetBaseProb() const;

        EDrawRewardType GetBaseRewardType() const;
        UINT16 GetBaseMinCount() const;
        UINT16 GetBaseMaxCount() const;

        EDrawRewardType GetUnexpectedRewardType() const;
        UINT16 GetUnexpectedMinCount() const;
        UINT16 GetUnexpectedMaxCount() const;

        // ====================  MUTATORS      ======================================= //
        bool SetBaseProb(UINT16 wBaseProb);
        bool InitBaseCount(EDrawRewardType eType, UINT16 wMinCount, UINT16 wMaxCount, UINT32 dwSilver);
        bool InitUnexpectedCount(EDrawRewardType eType, UINT16 wMinCount, UINT16 wMaxCount, UINT32 dwSilver, UINT32 dwGold);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        UINT16          _wLevel;    // 最低等级 
        EDrawType       _eType;     // 求签类型

        UINT16          _wBaseProb;   // 出现普通求签概率

        UINT32          _dwSilver;      //  求签消耗硬币数量
        UINT32          _dwGold;        //  求签消耗硬币数量

        EDrawRewardType _eBaseRewardType;   // 普通求签奖励类型
        UINT16          _wBaseMinCount;     // 普通求签奖励下限
        UINT16          _wBaseMaxCount;     // 普通求签奖励上限

        EDrawRewardType _eUnexpectedRewardType;   // 惊喜求签奖励类型
        UINT16          _wUnexpectedMinCount;     // 惊喜求签奖励下限
        UINT16          _wUnexpectedMaxCount;     // 惊喜求签奖励上限

}; // -----  end of class CDrawData  ----- //

#endif// #ifndef DRAW_MGR_H

