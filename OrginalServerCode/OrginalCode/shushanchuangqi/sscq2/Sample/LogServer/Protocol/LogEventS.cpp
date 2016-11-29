#include "stdafx.h"
#include "LogExt.h"

//½ÓÊÕ£ºÐÄÌø
void CLogEventS::OnRecv_KeepAlive(
        )
{
    UINT32 dwSvrID = GetCurSvrID();
    switch(GetPeerType())
    {
        case eHostCenter:
            NetMgr.GetSvrHandler(eHostCenter)->OnKeepAlive(dwSvrID);
            break;
        case eHostDB:
            NetMgr.GetSvrHandler(eHostDB)->OnKeepAlive(dwSvrID);
            break;
        case eHostGame:
            NetMgr.GetSvrHandler(eHostGame)->OnKeepAlive(dwSvrID);
            break;
        default: 
            break;
    }
}

//½ÓÊÕ£ºÐ´ÈÕÖ¾ÇëÇó
void CLogEventS::OnRecv_WriteLogReq(
        ELogType eLogType, //ÈÕÖ¾ÀàÐÍ
        const std::string& strLog //ÈÕÖ¾ÐÅÏ¢
        )
{
    CLogMgr::Instance().WriteLog(eLogType, strLog);
}

void CLogEventS::OnRecv_WriteLogToDB(
        const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
        )
{
    for(size_t i = 0 ;i < vecLog.size();i++)
    { 
        LogDataBase& sBase = const_cast<LogDataBase&>(*(vecLog[i]));
        switch (sBase.GetClassType())
        {
            case eType_SDgnLog:
                {
                    const SDgnLog &rDgn = dynamic_cast<SDgnLog &>(sBase);
                    CDBMgr::Instance().WriteDgnLogToDB(rDgn);
                }
                break;
            case eType_SRegisterLog:
                {
                    const SRegisterLog &rReg = dynamic_cast<SRegisterLog &>(sBase);
                    CDBMgr::Instance().WriteRegisterLogToDB(rReg);
                }
                break;
            case eType_SLoginLog:
                {
                    const SLoginLog &rLogin = dynamic_cast<SLoginLog &>(sBase);
                    CDBMgr::Instance().WriteLoginLogToDB(rLogin);
                }
                break;
            case eType_SItemCoursesLog:
                {
                    const SItemCoursesLog &rIC = dynamic_cast<SItemCoursesLog &>(sBase);
                    CDBMgr::Instance().WriteItemCoursesLogToDB(rIC);
                }
                break;
            case eType_SMoneyCoursesLog:
                {
                    const SMoneyCoursesLog &rMC = dynamic_cast<SMoneyCoursesLog &>(sBase);
                    CDBMgr::Instance().WriteMoneyCoursesLogToDB(rMC);
                }
                break;
            case eType_SDujieLog:
                {
                    const SDujieLog &rMC = dynamic_cast<SDujieLog &>(sBase);
                    CDBMgr::Instance().WriteDujieLogToDB(rMC);
                }
                break;
            case eType_SFashionLog:
                {
                    const SFashionLog &rMC = dynamic_cast<SFashionLog &>(sBase);
                    CDBMgr::Instance().WriteFashionLogToDB(rMC);
                }
                break;
            case eType_SFighterLog:
                {
                    const SFighterLog &rMC = dynamic_cast<SFighterLog &>(sBase);
                    CDBMgr::Instance().WriteFighterLogToDB(rMC);
                }
                break;
            case eType_SHorseLog:
                {
                    const SHorseLog &rMC = dynamic_cast<SHorseLog &>(sBase);
                    CDBMgr::Instance().WriteHorseLogToDB(rMC);
                }
                break;
            case eType_STrumpLog:
                {
                    const STrumpLog &rMC = dynamic_cast<STrumpLog &>(sBase);
                    CDBMgr::Instance().WriteTrumpLogToDB(rMC);
                }
                break;
            case eType_SEquipLog:
                {
                    const SEquipLog &rMC = dynamic_cast<SEquipLog &>(sBase);
                    CDBMgr::Instance().WriteEquipLogToDB(rMC);
                }
                break;
            case eType_SGuildLog:
                {
                    const SGuildLog &rMC = dynamic_cast<SGuildLog &>(sBase);
                    CDBMgr::Instance().WriteGuildLogToDB(rMC);
                }
                break;

            case eType_SMailLog:
                {
                    const SMailLog &rMail = dynamic_cast<SMailLog &>(sBase);
                    CDBMgr::Instance().WriteMailLogToDB(rMail);

                }
                break;
            case eType_SSendMoneyLog:
                {
                    const SSendMoneyLog &rLog = dynamic_cast<SSendMoneyLog &>(sBase);
                    CDBMgr::Instance().WriteSendMoneyLogToDB(rLog);

                }
                break;

            case eType_SSendItemLog:
                {
                    const SSendItemLog &rLog = dynamic_cast<SSendItemLog &>(sBase);
                    CDBMgr::Instance().writeSendItemLogToDB(rLog);

                }
                break;
            case eType_SMailOpLog:
                {
                    const SMailOpLog &rLog = dynamic_cast<SMailOpLog &>(sBase);
                    CDBMgr::Instance().WriteMailOpLogToDB(rLog);

                }
                break;

            case eType_SForbiddenLog:
                {
                    const SForbiddenLog &rLog = dynamic_cast<SForbiddenLog &>(sBase);
                    CDBMgr::Instance().WriteForbiddenLogToDB(rLog);

                }
                break;

            case eType_SForbiddenChatLog:
                {
                    const SForbiddenChatLog &rLog = dynamic_cast<SForbiddenChatLog &>(sBase);
                    CDBMgr::Instance().WriteForbiddenChatLogToDB(rLog);

                }
                break;

            case eType_SGlobalSendItemLog:
                {
                    const SGlobalSendItemLog &rLog = dynamic_cast<SGlobalSendItemLog &>(sBase);
                    CDBMgr::Instance().WriteGlobalSendItemLogToDB(rLog);

                }
                break;

            case eType_SQuesOptLog:
                {
                    const SQuesOptLog &rLog = dynamic_cast<SQuesOptLog &>(sBase);
                    CDBMgr::Instance().WriteQuesOptLogToDB(rLog);

                }
                break;
            case eType_SSendMailLog:
                {
                    const SSendMailLog &rLog = dynamic_cast<SSendMailLog &>(sBase);
                    CDBMgr::Instance().WriteSendMailLogToDB(rLog);

                }
                break;

            case eType_SVIPSendLog:
                {
                    const SVIPSendLog &rLog = dynamic_cast<SVIPSendLog &>(sBase);
                    CDBMgr::Instance().WriteVIPSendLogToDB(rLog);

                }
                break;

            case eType_SActivityOpenLog:
                {
                    const SActivityOpenLog &rLog = dynamic_cast<SActivityOpenLog &>(sBase);
                    CDBMgr::Instance().WriteActivityOpenLogToDB(rLog);
                }
                break;
            case eType_SDiscountItemLog:
                {
                    const SDiscountItemLog &rLog = dynamic_cast<SDiscountItemLog &>(sBase);
                    CDBMgr::Instance().WriteDiscountItemLogToDB(rLog);

                }
                break;

            case eType_SLevelChangeLog:
                {
                    const SLevelChangeLog &rLog = dynamic_cast<SLevelChangeLog &>(sBase);
                    CDBMgr::Instance().WriteLevelChangeLogToDB(rLog);

                }
                break;
            case eType_SPetLog:
                {
                    const SPetLog &rLog = dynamic_cast<SPetLog &>(sBase);
                    CDBMgr::Instance().WritePetLogToDB(rLog);
                }
                break;
            case eType_SBeautyLog:
                {
                    const SBeautyLog &rLog = dynamic_cast<SBeautyLog &>(sBase);
                    CDBMgr::Instance().WriteBeautyLogToDB(rLog);
                }
                break;
            default:
                break;
        }
    }
}
