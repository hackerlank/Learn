// =====================================================================================
//
//       Filename:  NewGuildBattleCaveCore.h
//
//    Description:  新帮派战洞府阵眼
//
//        Version:  1.0
//        Created:  03/20/2015 04:21:54 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_CAVE_CORE_H
#define NEW_GUILD_BATTLE_CAVE_CORE_H

#include "stdafx.h"

#include "NewGuildBattleProt.h"
#include "NewGuildBattleTypeDef.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{


// =====================================================================================
//        Class:  CCaveCore
//  Description:  新帮派战洞府阵眼
// =====================================================================================
class CCaveCore
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CCaveCore (ENGBCaveCore eType);                             // constructor //
        virtual ~CCaveCore();

        // ====================  ACCESSORS     ======================================= //
        ENGBCaveCore GetType() const;
        string  GetName() const;

        UINT8 GetResSpeed() const;

        CPlayerPtr GetOwner() const;

        bool GetAllInfo(SCaveCoreInfo& rInfo) const;

        // ====================  MUTATORS      ======================================= //
        void SetOwner(CPlayerPtr pOwner);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        const ENGBCaveCore  _eType;         // 阵眼类型

        UINT8               _byResSpeed;    // 资源增长速率

        CPlayerPtr          _pOwner;        // 占领者

}; // -----  end of class CCaveCore  ----- //

} // namespace NNewGuildBattle


#endif // #ifndef NEW_GUILD_BATTLE_CAVE_CORE_H

