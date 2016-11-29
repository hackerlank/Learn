#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

#include "Config.h"

enum ELevelUpType
{
    eLevelUpDefault = 0,            // 默认升级方式，经验值离散增加，超过最大值不增加
    eLevelUpByLevel = 1,            // 只能根据等级一下子升级, 超过最大值不增加
    eLevelUpByExp = 2,              // 经验值离散增加，超过最大值不增加
    eLevelUpByLevelResetExp = 3,    // 只能根据等级一下子升级, 超过最大值不增加，升级后经验值归零
};

enum ELevelObjectErr
{
    eErrSuccess = 0,        // 成功，没有错误 
    eErrUnknown = 1,        // 未知错误 
    eErrNoEnoughExp = 2,    // 所需经验值不足
    eErrMaxLevel = 3,       // 已经是最高等级，无法升级
};

class CLevelObject
{
    public:
        CLevelObject();
        virtual ~CLevelObject();
    public:
        virtual void InitFromDB(UINT32 dwExp, UINT16 wLevel, UINT32 dwUpdateTime);

        UINT16 GetLevel()           const;
        UINT32 GetExp()             const;
        UINT32 GetShownExp()        const;
        UINT32 GetShownNextExp()    const;
        UINT32 GetUpdateTime()      const;

        virtual ELevelObjectErr TryLevelUp(UINT32& dwVal);

        virtual UINT32 GetTableLevelExp(UINT16 wLevel) const = 0;
        virtual UINT16 GetTableLevel(UINT32 dwExp) const = 0;
        virtual UINT16 GetMaxLevel() const = 0;

    public:
        void SetExp(UINT32 dwExp);
        void SetLevel(UINT16 wLevel);

    private:
        ELevelObjectErr LevelUpByLevel(UINT32& dwVal);
        ELevelObjectErr LevelUpByExp(UINT32& dwVal);
        ELevelObjectErr LevelUpDefault(UINT32& dwVal);
        ELevelObjectErr LevelUpByLevelResetExp(UINT32& dwVal);

    protected:
        ELevelUpType _eLevelType;

    private:
        UINT16 _wLevel;
        UINT32 _dwExp;
        UINT32 _dwUpdateTime;
};

#endif  //#ifndef LEVEL_OBJECT_H

