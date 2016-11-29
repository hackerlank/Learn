#ifndef _SKILLATTR_H
#define _SKILLATTR_H
#include <map>
#include <memory>

#include "CommonDef.h"
struct SSkillAttr
{
    UINT32 _dwSkillAttrID;
    TVecFloat _vecAttr;
    const TVecFloat& GetVecAttr()
    {
        return _vecAttr;
    }
};

typedef std::shared_ptr<SSkillAttr> SSkillAttrPtr;
typedef std::map<UINT32,SSkillAttrPtr> TMapSkillAttrPtr;
class CSkillAttrMgr
{
 public:
     CSkillAttrMgr(){};
     ~CSkillAttrMgr(){};
     bool SkillAttrInit();
     SSkillAttrPtr GetSkillAttrByID(UINT32 dwSkillAttrID);
     static CSkillAttrMgr& Instance();
 private:
     TMapSkillAttrPtr _mapSkillAttr;

};

extern CSkillAttrMgr g_SkillAttrMgr;
#endif

