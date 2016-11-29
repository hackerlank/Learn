#include "LevelObject.h"
#include "ServerDefine.h"

CLevelObject::CLevelObject(): 
    _eLevelType(eLevelUpDefault), _wLevel(1), _dwExp(0), _dwUpdateTime(0)
{
}

CLevelObject::~CLevelObject()
{
}

void CLevelObject::InitFromDB(UINT32 dwExp, UINT16 wLevel, UINT32 dwUpdateTime)
{
    // 从数据库读取时更新建筑经验值
    _dwExp = dwExp;
    _wLevel = wLevel;
    _dwUpdateTime = dwUpdateTime;
    if (_eLevelType != eLevelUpByLevelResetExp)
    {
        if (_wLevel != GetTableLevel(_dwExp))
        {
            LOG_WRN << "CLevelObject dwExp error. wLevel = " << _wLevel << " , dwExp = " << _dwExp << ".";
            _wLevel = GetTableLevel(_dwExp);
        }
    }
}

ELevelObjectErr CLevelObject::TryLevelUp(UINT32& dwVal)
{
    // 升级
    ELevelObjectErr eResult = eErrUnknown;
    switch(_eLevelType)
    {
        case eLevelUpByLevel:
            eResult = LevelUpByLevel(dwVal);
            break;
        case eLevelUpByExp:
            eResult = LevelUpByExp(dwVal);
            break;
        case eLevelUpByLevelResetExp:
            eResult = LevelUpByLevelResetExp(dwVal);
            break;
        case eLevelUpDefault:
        default:
            eResult = LevelUpDefault(dwVal);
    }

    return eResult;
}

UINT16 CLevelObject::GetLevel() const
{
    return _wLevel;
}

UINT32 CLevelObject::GetExp() const
{
    return _dwExp;
}

UINT32 CLevelObject::GetUpdateTime() const
{
    return _dwUpdateTime;
}

void CLevelObject::SetExp(UINT32 dwExp)
{
    // 设定经验值
    _dwExp = dwExp;
    _wLevel = GetTableLevel(_dwExp);
    _dwUpdateTime = time(NULL);
}

void CLevelObject::SetLevel(UINT16 wLevel)
{
    // 设定等级
    if (wLevel > GetMaxLevel())
        wLevel = GetMaxLevel();
    _wLevel = wLevel;
    _dwExp = GetTableLevelExp(_wLevel);
    _dwUpdateTime = time(NULL);
}

UINT32 CLevelObject::GetShownExp() const
{
    // 返回客户端实际显示的dwExp
    return _dwExp - GetTableLevelExp(_wLevel);
}

UINT32 CLevelObject::GetShownNextExp() const
{
    // 返回客户端实际显示需要的下一级的dwExp
    return GetTableLevelExp(_wLevel + 1) - GetTableLevelExp(_wLevel);
}

ELevelObjectErr CLevelObject::LevelUpByLevel(UINT32& dwVal)
{
    // 只能根据等级一下子升级, 超过最大值不增加
    UINT32 dwMaxExp = GetTableLevelExp(GetMaxLevel());
    if (dwMaxExp <= _dwExp)
        return eErrMaxLevel;
    UINT32 dwNeedVal = GetTableLevelExp(_wLevel + 1) - GetTableLevelExp(_wLevel);
    if (!dwNeedVal) // 需要升级的经验值为0，应该是已经在最大等级，无法升级
        return eErrMaxLevel;
    if (dwNeedVal > dwVal)
        return eErrNoEnoughExp;
    _dwExp += dwNeedVal;
    dwVal -= dwNeedVal;
    ++_wLevel;
    _dwUpdateTime = time(NULL);
    return eErrSuccess;
}

ELevelObjectErr CLevelObject::LevelUpByExp(UINT32& dwVal)
{
    // 经验值离散增加，超过最大值不增加
    UINT32 dwMaxExp = GetTableLevelExp(GetMaxLevel());
    if (dwMaxExp <= _dwExp)
        return eErrMaxLevel;
    UINT32 dwNeedVal = GetTableLevelExp(_wLevel + 1) - GetTableLevelExp(_wLevel);
    if (!dwNeedVal) // 需要升级的经验值为1，应该是已经在最大等级，无法升级
        return eErrMaxLevel;
    UINT16 wOldLevel = _wLevel;
    _dwExp += dwVal;
    _wLevel = GetTableLevel(_dwExp);
    _dwUpdateTime = time(NULL);
    if (_wLevel == wOldLevel)
        return eErrSuccess;
    else
        return eErrSuccess;
}

ELevelObjectErr CLevelObject::LevelUpByLevelResetExp(UINT32& dwVal)
{
    // 只能根据等级一下子升级, 超过最大值不增加, 升级后经验值归零
    if (GetLevel() >= GetMaxLevel())
        return eErrMaxLevel;
    UINT32 dwNeedVal = GetTableLevelExp(_wLevel);
    if (!dwNeedVal) // 需要升级的经验值为0，应该是已经在最大等级，无法升级
        return eErrMaxLevel;
    if (dwNeedVal > dwVal)
        return eErrNoEnoughExp;
    dwVal -= dwNeedVal;
    ++_wLevel;
    _dwExp = 0;
    _dwUpdateTime = time(NULL);
    return eErrSuccess;
}

ELevelObjectErr CLevelObject::LevelUpDefault(UINT32& dwVal)
{
    // TODO: 默认升级方式
    return eErrUnknown;
}
