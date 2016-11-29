
#include "stdafx.h"
#include "ExpMgr.h"

UINT64 CExpMgr::_qwExps[];
UINT8 CExpMgr::_byLevelMax = LEVEL_MAX;
TVecExpCFGPtr CExpMgr::_vecExpCFGPtr;

CExpMgr::CExpMgr()
{
}

bool CExpMgr::Init()
{
    memset(_qwExps, 0x00, sizeof(_qwExps));
    _vecExpCFGPtr.resize(_byLevelMax+1,NULL);
    return LoadConfig();
}

bool CExpMgr::LoadConfig(bool bReload)
{
    string strPath = Config._strConfigDir + "Conf/Table/Exp.xml";
    CExpLoader oExpLoader;
    if(!oExpLoader.LoadData(strPath))
    {
        LOG_CRI << "oExpLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    UINT8 byLevelMax = 0;
    for(size_t i = 0; i < oExpLoader._vecData.size(); ++i)
    {
        SExpCFG* pExpCFG = oExpLoader._vecData[i];
        if(pExpCFG->_Level == 0)
            continue;
        byLevelMax = byLevelMax>pExpCFG->_Level?byLevelMax:pExpCFG->_Level;

        SetExp(pExpCFG->_Level, pExpCFG->_Exp);
        if(pExpCFG->_Level<_vecExpCFGPtr.size())
        {
            SExpCFGPtr pExpCFGPtr(new SExpCFG);
            *pExpCFGPtr=*pExpCFG;
            _vecExpCFGPtr[pExpCFG->_Level] = pExpCFGPtr;
        }
    }
    SetMaxLevel(byLevelMax);
    return true;
}

void CExpMgr::SetMaxLevel(UINT8 byLevel)
{
    if (byLevel > LEVEL_MAX)
        _byLevelMax = LEVEL_MAX;
    else
        _byLevelMax = byLevel;
}

bool CExpMgr::TestLevelUp(UINT8& byLevel, UINT64& qwExp)
{
	bool r = false;
	while(_qwExps[byLevel-1] > 0 && qwExp >= _qwExps[byLevel-1])
	{
		r = true;
		++byLevel;
	}
	if(byLevel >= GetLevelMax())
    {
        byLevel = GetLevelMax();
		qwExp = _qwExps[GetLevelMax() - 1];
    }
	return r;
}

bool CExpMgr::TestLevelDown(UINT8& byLevel, UINT64& qwExp)
{
	bool r = false;
	while(byLevel > 1 && _qwExps[byLevel-1] > 0 && qwExp < _qwExps[byLevel-1])
	{
		r = true;
		--byLevel;
	}
	return r;
}

void CExpMgr::SetExp(UINT8 byLevel, UINT64 qwExp)
{
    if (byLevel >= GetLevelMax())
        return;
	_qwExps[byLevel - 1] = qwExp;
}

UINT64 CExpMgr::GetLevelMin(UINT8 byLevel)
{
	if(byLevel < 1)
		return 0;
	if(byLevel >= GetLevelMax())
		return _qwExps[GetLevelMax() - 1];
	return _qwExps[byLevel - 1];
}

UINT8 CExpMgr::Exp2Level(UINT64 qwExp)
{
    if (qwExp >= _qwExps[GetLevelMax() - 1])
        return GetLevelMax();
    for (UINT8 l = 0; l < GetLevelMax(); ++l)
    {
        if (_qwExps[l] > qwExp)
            return l+1;
    }
    return 1;
}

float CExpMgr::GetWBossFightRate(UINT8 byLevel)
{
    if(byLevel < _vecExpCFGPtr.size())
    {
        SExpCFGPtr pCFG = _vecExpCFGPtr[byLevel];
        if(pCFG)
        {
            return pCFG->_WC1/100.0;
        }
    }
    return 1.0;
}


float CExpMgr::GetWBossPrizeRate(UINT8 byLevel)
{
     if(byLevel < _vecExpCFGPtr.size())
    {
        SExpCFGPtr pCFG = _vecExpCFGPtr[byLevel];
        if(pCFG)
        {
            return pCFG->_WC2/100.0;
        }
    }

    return 1.0;
}

SExpCFGPtr CExpMgr::GetExpCfg(UINT8 byLevel)
{
    if(byLevel >= _vecExpCFGPtr.size())
    {
        return NULL;
    }
    return _vecExpCFGPtr[byLevel];
}

//获取基础打坐经验
UINT64 CExpMgr::GetBaseSitExp(UINT8 byLevel)
{
    SExpCFGPtr pExpCFG =  GetExpCfg(byLevel);
    if(pExpCFG)
    {
        return pExpCFG->_SitBasicExp;
    }

    return 0;
}


