#include "BattleArea.h"
#include "SkillAreaCFG.h"
#include "Tokenizer.h"
#include "BattleDebugger.h"

namespace NBattle
{
using namespace std;

CBattleArea::CBattleArea():
    _wID(0), 
    _eSide(eAreaSideBoth), _eSelectType(eAreaSelectDefault), _eRateType(eAreaRateDefault), _byMainTarget(0)
{
}

CBattleArea::~CBattleArea()
{
}

UINT16 CBattleArea::GetID() const
{ 
    return _wID; 
}
const string&   CBattleArea::GetName() const
{
    return _strName;
}

EAreaSide CBattleArea::GetSide() const
{ 
    return _eSide; 
}

EAreaSelectType CBattleArea::GetSelectType() const
{ 
    return _eSelectType; 
}

EAreaRateType CBattleArea::GetRateType() const
{ 
    return _eRateType; 
}

UINT8 CBattleArea::GetMainTargetType() const
{
    return _byMainTarget;
}
    
UINT8 CBattleArea::GetPosCount()  const
{ 
    return _vecPos.size(); 
}

FLOAT CBattleArea::GetPosFactor(UINT8 bySize, UINT8 byPosIndex) const
{
    auto it = _mapPosFactor.find(bySize);
    if (it == _mapPosFactor.end())
    {
        it = _mapPosFactor.begin();
        if(it == _mapPosFactor.end())
            LOG_CRI << "_mapPosFactor has no count " << static_cast<UINT32>(bySize) << ".";
    }
    if(byPosIndex >= static_cast<UINT8>((it->second).size()))
    {
        LOG_CRI << "_mapPosFactor has no PosIndex " << static_cast<UINT32>(bySize) << ", " << static_cast<UINT32>(byPosIndex) << ".";
        return 1.0f;
    }
    else
        return (it->second)[byPosIndex];
}

FLOAT CBattleArea::GetPosFactor(UINT8 byIndex) const
{
    auto it = _mapPosFactor.begin();
    if (it == _mapPosFactor.end())
    {
        LOG_CRI << "_mapPosFactor.empty().";
        return 1.0f;
    }
    if(byIndex >= static_cast<UINT8>((it->second).size()))
        return 1.0f;
    return (it->second)[byIndex];
}

UINT8 CBattleArea::GetPosFactorSize() const
{
    UINT8 byMaxSize = 0;
    for (auto it = _mapPosFactor.begin(); it != _mapPosFactor.end(); ++it)
    {
        UINT8 bySize = (it->second).size();
        byMaxSize = bySize > byMaxSize ? bySize:byMaxSize;
    }
    return byMaxSize;
}

FLOAT CBattleArea::GetRepeatFactor(UINT8 byIndex) const
{
    if(byIndex >= static_cast<UINT8>(_vecRepeatFactor.size()))
        return 1.0f;
    return _vecRepeatFactor[byIndex];
}

UINT8 CBattleArea::GetRepeatFactorSize() const
{
    return _vecRepeatFactor.size();
}

const TSetUINT16&  CBattleArea::GetFighterID() const
{
    return _setFighterID;
}

void CBattleArea::SetID(UINT16 wID) 
{ 
    _wID = wID; 
}

void CBattleArea::SetName(const string& strName) 
{ 
    _strName = strName; 
}

void CBattleArea::SetSide(UINT8 bySide) 
{ 
    _eSide = static_cast<EAreaSide>(bySide);
}

void CBattleArea::SetType(UINT8 byType) 
{ 
    _eSelectType = static_cast<EAreaSelectType>(byType);
}

void CBattleArea::SetRateType(UINT8 byType)
{
    _eRateType = static_cast<EAreaRateType>(byType);
}

void CBattleArea::SetMainTargetType(UINT8 byMainTarget)
{
    _byMainTarget = byMainTarget;
}

void CBattleArea::PushbackPos(const CBattleArea::SPos& rPos )
{   
    _vecPos.push_back(rPos);
}       

void CBattleArea::PushbackPosFactor(UINT8 bySize, const TVecFloat& vecFactor)
{
    if (_mapPosFactor.find(bySize) != _mapPosFactor.end())
        LOG_CRI << "bySize duplicate(" << static_cast<UINT32>(bySize) << ").";
    _mapPosFactor[bySize] = vecFactor;
}

void CBattleArea::PushbackRepeatFactor(FLOAT fRepeatFactor)
{
    _vecRepeatFactor.push_back(fRepeatFactor);
}
        
bool CBattleArea::PushbackFighterID(UINT16 wFighterID)
{
    if (_setFighterID.find(wFighterID) != _setFighterID.end())
        return false;
    _setFighterID.insert(wFighterID);
    return true;
}
        
const CBattleArea::SPos& CBattleArea::GetPos( UINT8 byIndex ) const
{   
    static SPos e;
    if(byIndex >= static_cast<UINT8>(_vecPos.size()))
        return e;
    return _vecPos[byIndex];
}

CBattleArea& CBattleArea::GetDefault()
{   
    static CBattleArea cArea;
    static bool inited = false;
    if(!inited)
    {
        inited = true;
        SPos sPos;
        cArea.PushbackPos(sPos);
    }
    return cArea;
}

CBattleAreaMgr::CBattleAreaMgr()
{
}

CBattleAreaMgr::~CBattleAreaMgr()
{
}

bool CBattleAreaMgr::Init(const string& strPath)
{
    return LoadCfg(strPath, "Conf/Table/SkillArea.xml");
}

bool CBattleAreaMgr::ReloadCfg(const string& strPath, const string& strName)
{
    _mapArea.clear();
    return LoadCfg(strPath, strName);
}

bool CBattleAreaMgr::LoadCfg(const string& strPath, const string& strName)
{
    CSkillAreaLoader cfg;
    string strFile = strPath + "Conf/Table/SkillArea.xml";

    if(!cfg.LoadData(strFile))
        return false;

    LOG_INF << "Loading " << strFile << " Config...";
    for (auto iter = cfg._vecData.begin(); iter != cfg._vecData.end(); iter++)
    {
        CBattleAreaPtr pArea(new CBattleArea);
        pArea->SetID((*iter)->_wID);
        pArea->SetName((*iter)->_strName);
        pArea->SetSide((*iter)->_bySide);
        pArea->SetType((*iter)->_bySelectType);
        pArea->SetRateType((*iter)->_byRateType);
        pArea->SetMainTargetType((*iter)->_byHasMainTarget);

        Tokenizer tkArea((*iter)->_strArea, ";");
        size_t count = tkArea.size();
        for (size_t i = 0; i < count; ++i)
        {               
            Tokenizer tkPos(tkArea[i], ",");
            CBattleArea::SPos cPos;
            if(tkPos.size() == 2)
            {
                cPos.byX = ::atoi(tkPos[0].c_str());
                cPos.byY = ::atoi(tkPos[1].c_str());
            }
            else
            {
                LOG_CRI << (*iter)->_wID << " Wrong Pos: " << tkArea[i] << ".";
                return false;
            }
            pArea->PushbackPos(cPos);
        } 

        Tokenizer tkFactor((*iter)->_strFactor, ";");
        count = tkFactor.size();
        for (size_t i = 0; i < count; ++i)
        {               
            Tokenizer tkFactor2(tkFactor[i], ",");
            TVecFloat vecFactor;
            for (size_t j = 0; j < tkFactor2.size(); ++j)
            {
                vecFactor.push_back(::atof(tkFactor2[j].c_str()));
            }
            pArea->PushbackPosFactor(tkFactor2.size(), vecFactor);
        } 

        Tokenizer tkRepeatFactor((*iter)->_strRepeatFactor, ",");
        count = tkRepeatFactor.size();
        for (size_t i = 0; i < count; ++i)
        {               
            pArea->PushbackRepeatFactor(::atof(tkRepeatFactor[i].c_str()));
        } 

        Tokenizer tkFighterID((*iter)->_strFighterID, ";");
        count = tkFighterID.size();
        for (size_t i = 0; i < count; ++i)
        {
            bool bRet = pArea->PushbackFighterID(static_cast<UINT16>(::atoi(tkFighterID[i].c_str())));
            if (!bRet)
            {
                LOG_CRI << "Wrong FighterID: " << tkFighterID[i] << ".";
                return bRet;
            }
        }

        if(!_mapArea.insert(make_pair(pArea->GetID(), pArea)).second)
        {
            LOG_CRI<<"Area ID duplicated in Area: "<< pArea->GetID();
            return false;
        }
    }
    return true;
}

CBattleAreaPtr CBattleAreaMgr::GetArea(UINT8 byType)
{
    auto it = _mapArea.find(byType);
    if(it == _mapArea.end())
        return NULL;
    return it->second;
}
} // namespace NBattle
