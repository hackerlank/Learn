#ifndef BATTLE_AREA_H_
#define BATTLE_AREA_H_

#include "Singleton.h"
#include "BattleTypeDef.h"

namespace NBattle
{
class CBattleArea
{
    public:
        struct SPos
        {
            INT8 byX;
            INT8 byY;
            SPos():
                byX(0), byY(0)
            {}
        };
    public:
        CBattleArea();
        virtual ~CBattleArea();

        UINT16              GetID()                         const;
        const std::string&  GetName()                       const;
        EAreaSide           GetSide()                       const;
        EAreaSelectType     GetSelectType()                 const;
        EAreaRateType       GetRateType()                   const;
        UINT8               GetMainTargetType()             const;

        UINT8               GetPosCount()                   const;
        FLOAT               GetPosFactor(UINT8, UINT8)      const;
        FLOAT               GetPosFactor(UINT8)             const;
        UINT8               GetPosFactorSize()              const;
        FLOAT               GetRepeatFactor(UINT8 byIndex)  const;
        UINT8               GetRepeatFactorSize()           const;
        const TSetUINT16&   GetFighterID()                  const;

        void                SetID(UINT16 wID);
        void                SetName(const string& strName);
        void                SetSide(UINT8 bySide);
        void                SetType(UINT8 byType);
        void                SetRateType(UINT8 byType);
        void                SetMainTargetType(UINT8 byMainTarget);
        void                PushbackPos(const SPos&);
        void                PushbackPosFactor(UINT8 bySize, const TVecFloat& vecFactor);
        void                PushbackRepeatFactor(FLOAT);
        bool                PushbackFighterID(UINT16 wFighterID);
                            
        const SPos&         GetPos(UINT8) const;

        static CBattleArea& GetDefault();
    private:
        UINT16                 _wID;
                               
        EAreaSide              _eSide;
        EAreaSelectType        _eSelectType;
        EAreaRateType          _eRateType;
        UINT8                  _byMainTarget;
        std::string            _strName;
                               
        std::vector<SPos>      _vecPos;
        map<UINT8, TVecFloat>  _mapPosFactor;
        TVecFloat              _vecRepeatFactor;
        TSetUINT16             _setFighterID;
};

class CBattleAreaMgr : public Singleton<CBattleAreaMgr>
{
    public:
        CBattleAreaMgr();
        virtual ~CBattleAreaMgr();

        bool LoadCfg(const string& strPath, const string& strName);
        bool Init(const string& strPath);
        bool ReloadCfg(const string& strPath, const string& strName);

        CBattleAreaPtr GetArea(UINT8 byType);

    private:
        std::map<UINT8, CBattleAreaPtr> _mapArea;
};

} // namespace NBattle

#endif // BATTLE_AREA_H_
