#include "stdafx.h"
#include "Protocols.h"
#include "NPC.h"
#include "NPCMgr.h"

void CNpc::GetNpcAppear(SNpcAppear& rNpcAppear)
{
    rNpcAppear.wNpcID = GetNpcID();
    rNpcAppear.strName = GetNpcName();
}


SNpcPropCFG& CNpc::GetNpcConfig()
{
    if(_qwVersion != CNpcMgr::GetVersion())
        _pNpcPropCFG = CNpcMgr::GetNpcCFG(_pNpcPropCFG->_ID);
    return *_pNpcPropCFG; 
}

#if 0
CGameScriptPtr  CNpc::GetScript()
{
    if(_pScript == NULL)
        _pScript = CScriptMgr::GetScript(_rNpcPropCFG._Script, eScriptNpc);
    return _pScript;
}
#endif
