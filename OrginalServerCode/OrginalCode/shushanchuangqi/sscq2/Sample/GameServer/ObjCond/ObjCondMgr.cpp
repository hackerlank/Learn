#include "stdafx.h"
#include "ObjCondMgr.h"
#include "Point.h"

std::map<UINT16, SObjCondPtr> CObjCondMgr::_mapCondition;

bool CObjCondMgr::Init()
{
	CBarrierLoader oBarrierLoader;
	string strPath = Config._strConfigDir + "Conf/Table/Barrier.xml";
	if(!oBarrierLoader.LoadData(strPath))
		return false;
	for(size_t i = 0; i < oBarrierLoader._vecData.size(); ++i)
	{
		SObjCondPtr pCondition = NULL;
		SBarrierCFG& rCFG = *oBarrierLoader._vecData[i];
		if(rCFG._ConditionID > MAX_CUSTOM_COND_ID)
		{
			LOG_CRI << "Invalid ConditionID=" << rCFG._ConditionID;
			return false;
		}
		
		switch(rCFG._Type)
		{
		case eKillMonster:
			{
				SKillMonsterCondPtr pKillMonsterCond(new SKillMonsterCond);
				if(pKillMonsterCond == NULL)
					return false;
				if(!rCFG._Condition_1.empty())
					pKillMonsterCond->_vecMonsterID.push_back((UINT16)atoi(rCFG._Condition_1.c_str()));
				if(!rCFG._Condition_2.empty())
					pKillMonsterCond->_vecMonsterID.push_back((UINT16)atoi(rCFG._Condition_2.c_str()));
				if(!rCFG._Condition_3.empty())
					pKillMonsterCond->_vecMonsterID.push_back((UINT16)atoi(rCFG._Condition_3.c_str()));
				if(!rCFG._Condition_4.empty())
					pKillMonsterCond->_vecMonsterID.push_back((UINT16)atoi(rCFG._Condition_4.c_str()));
				if(!rCFG._Condition_5.empty())
					pKillMonsterCond->_vecMonsterID.push_back((UINT16)atoi(rCFG._Condition_5.c_str()));
				pCondition = pKillMonsterCond;
			}
			break;
#if 0
		case eOpenSwitcher:
			{
				SOpenSwitcherCondPtr pOpenSwitcherCond(new SOpenSwitcherCond);
				if(pOpenSwitcherCond == NULL)
					return false;
				if(!rCFG._Condition_1.empty())
					pOpenSwitcherCond->_vecSwitcherID.push_back((UINT16)atoi(rCFG._Condition_1.c_str()));
				if(!rCFG._Condition_2.empty())
					pOpenSwitcherCond->_vecSwitcherID.push_back((UINT16)atoi(rCFG._Condition_2.c_str()));
				if(!rCFG._Condition_3.empty())
					pOpenSwitcherCond->_vecSwitcherID.push_back((UINT16)atoi(rCFG._Condition_3.c_str()));
				if(!rCFG._Condition_4.empty())
					pOpenSwitcherCond->_vecSwitcherID.push_back((UINT16)atoi(rCFG._Condition_4.c_str()));
				if(!rCFG._Condition_5.empty())
					pOpenSwitcherCond->_vecSwitcherID.push_back((UINT16)atoi(rCFG._Condition_5.c_str()));
				pCondition = pOpenSwitcherCond;
			}
			break;
#endif
		case ePlayerPos:
			{
				SPlayerPosCondPtr pPlayerPosCond(new SPlayerPosCond);
				if(pPlayerPosCond == NULL)
					return false;
				TVecUINT8 vecUINT8;
#define POS_SWT_CFG(n) \
				if(!rCFG._Condition_##n.empty()) \
				{ \
					SplitToNumber(rCFG._Condition_##n, ",", vecUINT8); \
					if(vecUINT8.size() != 2) \
					{ \
						LOG_CRI << "config is error"; \
						return false; \
					} \
					pPlayerPosCond->_vecPoint.emplace_back(SPoint((float)vecUINT8[0], (float)vecUINT8[1])); \
					vecUINT8.clear(); \
				}

				POS_SWT_CFG(1);
				POS_SWT_CFG(2);
				POS_SWT_CFG(3);
				POS_SWT_CFG(4);
				POS_SWT_CFG(5);
#undef POS_SWT_CFG
				pCondition = pPlayerPosCond;
			}
			break;
        case eAllMonsterKilled:
            {
                SAllMonsterKilledPtr pSAllMonsterKilled(new SAllMonsterKilled);
                if(NULL == pSAllMonsterKilled)
                {
                    return false;
                }
                pCondition = pSAllMonsterKilled;
            }
            break;
		default:
			{
				assert(false);
				LOG_CRI << "Invalid Condition!";
			}
			break;
		}
		

		if(!_mapCondition.insert(std::make_pair(rCFG._ConditionID, pCondition)).second)
		{
			LOG_CRI << "duplicate key!";
			return false;
		}
	}
/*	
	// all monster killed
	SObjCondPtr pCondition(new SAllMonsterKilled);
	if(!pCondition)
		return false;

	if(!_mapCondition.insert(std::make_pair(COND_ID_ALL_MONSTER_KILLED, pCondition)).second)
	{
		LOG_CRI << "Duplicate!";
		return false;
	}
*/
	return true;
}

void CObjCondMgr::Destroy()
{
}

SObjCondPtr CObjCondMgr::GetCondition(UINT16 wCondID)
{
	auto it = _mapCondition.find(wCondID);
	if(it == _mapCondition.end())
		return NULL;
	return it->second;
}
