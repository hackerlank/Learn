#include "stdafx.h"
#include "SkillAttr.h"
#include "SkillAttrCFG.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;

CSkillAttrMgr g_SkillAttrMgr;

bool CSkillAttrMgr::SkillAttrInit()
{
    string strPath = Config._strConfigDir + "Conf/Table/SkillAttr.xml";
    CSkillAttrLoader oSkillAttrLoader;
    if(!oSkillAttrLoader.LoadData(strPath))
        return false;

    for(size_t i = 0; i < oSkillAttrLoader._vecData.size(); ++i)
    {
       SSkillAttrCFG* pCFG = oSkillAttrLoader._vecData[i];
       if(pCFG)
       {
            SSkillAttrPtr pSkillAttr(new SSkillAttr);
            pSkillAttr->_dwSkillAttrID = pCFG->_ID;
            VECATTR_RESET(pSkillAttr->_vecAttr);
            PHYATK_ADD(pSkillAttr->_vecAttr, pCFG);
            MGCATK_ADD(pSkillAttr->_vecAttr, pCFG);
            PHYDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            MGCDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            PHYRDC_ADD(pSkillAttr->_vecAttr, pCFG);
            MGCRDC_ADD(pSkillAttr->_vecAttr, pCFG);
            MAXHP_ADD(pSkillAttr->_vecAttr, pCFG);
            SPEED_ADD(pSkillAttr->_vecAttr, pCFG);
            HIT_ADD(pSkillAttr->_vecAttr, pCFG);
            HITRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            DODGE_ADD(pSkillAttr->_vecAttr, pCFG);
            DODGERATE_ADD(pSkillAttr->_vecAttr, pCFG);
            CRITICAL_ADD(pSkillAttr->_vecAttr, pCFG);
            CRTRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            ANTICRITCAL_ADD(pSkillAttr->_vecAttr, pCFG);
            ANTICRTRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            BLOCK_ADD(pSkillAttr->_vecAttr, pCFG);
            BLOCKRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            PIERCE_ADD(pSkillAttr->_vecAttr, pCFG);
            PIERCERATE_ADD(pSkillAttr->_vecAttr, pCFG);
            COUNTER_ADD(pSkillAttr->_vecAttr, pCFG);
            COUNTERRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            RESIST_ADD(pSkillAttr->_vecAttr, pCFG);
            RESISTRATE_ADD(pSkillAttr->_vecAttr, pCFG);
            INITAURA_ADD(pSkillAttr->_vecAttr, pCFG);
            MAXAURA_ADD(pSkillAttr->_vecAttr, pCFG);
            CRIEXTRAADD_ADD(pSkillAttr->_vecAttr, pCFG);
            CRIEXTRARDC_ADD(pSkillAttr->_vecAttr, pCFG);
            METALATK_ADD(pSkillAttr->_vecAttr, pCFG);
            WOODATK_ADD(pSkillAttr->_vecAttr, pCFG);
            WATERATK_ADD(pSkillAttr->_vecAttr, pCFG);
            FIREATK_ADD(pSkillAttr->_vecAttr, pCFG);
            EARTHATK_ADD(pSkillAttr->_vecAttr, pCFG);
            METALDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            WOODDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            WATERDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            FIREDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            EARTHDEF_ADD(pSkillAttr->_vecAttr, pCFG);
            PHYATK_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            MGCATK_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            PHYDEF_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            MGCDEF_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            MAXHP_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            SPEED_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            HIT_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            DODGE_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            CRITICAL_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            ANTICRITCAL_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            BLOCK_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            PIERCE_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            COUNTER_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            RESIST_PER_ADD(pSkillAttr->_vecAttr, pCFG);
            ANTIEFFECT_ADD(pSkillAttr->_vecAttr, pCFG);
            //COUTEREXTRAADD_ADD(pSkillAttr->_vecAttr, pCFG);
            //COUTEREXTRARDC_ADD(pSkillAttr->_vecAttr, pCFG);
            _mapSkillAttr.insert(make_pair(pSkillAttr->_dwSkillAttrID,pSkillAttr));
       }
    }
    return true;
}

SSkillAttrPtr CSkillAttrMgr::GetSkillAttrByID(UINT32 dwSkillAttrID)
{
    auto itr = _mapSkillAttr.find(dwSkillAttrID);
    if(itr != _mapSkillAttr.end())
    {
        return itr->second;
    }
    
    return NULL;
}
CSkillAttrMgr& CSkillAttrMgr::Instance()
{
    return g_SkillAttrMgr;
}
