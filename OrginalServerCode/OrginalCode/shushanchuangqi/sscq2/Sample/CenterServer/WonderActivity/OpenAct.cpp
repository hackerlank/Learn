#include "OpenAct.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivityMgr.h"

void COpenAct::OnEnd()
{
    CWonderActivity::OnEnd();
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    
    //通知 Icon消失
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eOpenActActivity;
    oState.bOpen = false;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState,true);

}

void COpenAct::OnBegin()
{
    CWonderActivity::OnBegin();
    OpenIcon(true);
}

void COpenAct::OpenIcon(bool bNotify)
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
   
    //通知 Icon出现
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eOpenActActivity;
    oState.bOpen = true;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState,bNotify);
}
