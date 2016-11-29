#include "stdafx.h"
#include "Protocols.h"
#include "Answer.h"
#include "Random.h"
#include "RTime.h"
#include "ExaminationAnswerCFG.h"
#include "ExaminationAwardCFG.h"
#include "User.h"
#include "UserMgr.h"
#include "AnswerProtS.h"
#include "SystemMail.h" 
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "Tokenizer.h"

///////////////////////////////////
//前32 为表示积分，后32为表示答题时间
#define GETSCORE(qwValue) (qwValue & 0x00000000FFFFFFFF)
#define SETSCORE(var,score) var=(var|score)
#define GETTIME(qwValue) (qwValue>>32)
#define SETTIME(var,t) var=(var|(t << 32))
#define GET_ANS_BIT(value,index) (value&(1 << index));
#define SET_ANS_BIT(value,index) (value|(1 << index));
//////////////////////////////////////
const static UINT8 randAnswer[6][3] =
{
    {2,3,4},
    {2,4,3},
    {3,2,4},
    {3,4,2},
    {4,2,3},
    {4,3,2}
};
const static UINT32 dwMaxAnswerTopic = 30;
//const static UINT32 dwMaxTopic = 1000;
const static UINT32 BEGININTERVAL = 5 * 60;
const static UINT32 DAYSEC = 86400;
const static UINT32 COUNTDOWN = 30;
const static UINT16 wMailID = 520;
const static UINT16 wContentID = 521;

const static UINT32 DWMAXUNTILE = 10;
//////////////////////////////////
bool SAnswerUser::ChangeUntilFail()
{
    if(dwUntilFail != 0 || GetCalUntilFail())
    {
        dwUntilFail += 1;
        //LOG_INF <<"dwUntilFail=" <<dwUntilFail;
        return true;
    }
    //LOG_INF <<"dwUntilFail=" <<dwUntilFail;
    SetCalUntilFail(true);
    return true;
}
///////////////////////////////////////////
CAnswer::CAnswer() : 
    _dwTopicID(1),
    _bInit(false),
    _dwMaxTopicNum(0),
    _bRun(false),
    _eState(eNone),
    _bLoadVar(false),
    _eTopicState(eTopicNone),
    _bRead(false),
    _bAnswer(false),
    _bResult(false),
    _bCanUseSkill(true)
{ 
    dwAnswer_0 = 0;
    dwAnswer_2 = 3;
    dwAnswer_3 = 4;
    dwAnswer_5 = 7;
    dwAnswer_6 = 8;
    dwAnswer_10 = 12;
    READ = 8;
    ANSWER = 12;
    RESULT = 5;
    READINTERVAL = 1;
    RESULTINTERVAL = 2;
    BYFIRST = 20;
    BYSECOND = 16;
    BYTHIRD = 14;
    BEGINHOUR = 13;
    BEGINMIN = 30;
    ONETOPIC = READ + ANSWER + RESULT + READINTERVAL + RESULTINTERVAL;
    INTERVAL = ONETOPIC * dwMaxAnswerTopic;
}

bool CAnswer::Init()
{
    if(!LoadConfig())
    {
        LOG_INF <<"LoadConfig Err.";
        return false;
    }
    InitParam();
    _bInit = true;
    return true;
}

bool CAnswer::LoadConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/ExaminationAnswer.xml";
    CExaminationAnswerLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oExaminationAnswer LoadData fails! Path: " << strPath;
        return false;
    }
    _dwMaxTopicNum = oLoader._vecData.size();
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SExaminationAnswerCFG* pConfig = oLoader._vecData[i];
        if(pConfig)
        {
            UINT32 dwID = pConfig->_ID;
            UINT8  byPos = atoi(pConfig->_AnswerPosition.c_str());
            _mapTopic2Ans.insert(make_pair(dwID,byPos));
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/ExaminationAward.xml";
    CExaminationAwardLoader oAward;
    if(!oAward.LoadData(strPath))
    {
        LOG_CRI << "oAward LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oAward._vecData.size(); ++i)
    {
        SExaminationAwardCFG* pConfig = oAward._vecData[i];
        if(pConfig)
        {
            if(pConfig->_PrizeType == 1)
            {
                SAnswerAward oTmp;
                oTmp.wTop= pConfig->_RankTop;
                oTmp.wBottom = pConfig->_RankBottom;
                //LOG_CRI <<"====Begin====:Top=" << oTmp.wTop <<",Bottom="<<oTmp.wBottom;
                Tokenizer tk(pConfig->_GivenItem, "|"); // ID,Count| ID,Count
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    SMailItemInfo oMailItem;
                    Tokenizer yatk(tk[i], ",");
                    oMailItem.wItemID = atoi(yatk[0].c_str());
                    oMailItem.wCount = atoi(yatk[1].c_str());
                    //LOG_CRI <<"ItemID="<<oMailItem.wItemID <<",count="<<oMailItem.wCount;
                    oMailItem.eBindType = NItemProt::eBindGet;
                    oTmp.vecItem.push_back(oMailItem);
                }

                //LOG_CRI <<"====END====:Top=" << oTmp.wTop <<",Bottom="<<oTmp.wBottom;
                _vecAward.push_back(oTmp);
            }
            else if(pConfig->_PrizeType == 2)
            {
                Tokenizer tk(pConfig->_GivenItem, "|"); // ID,Count| ID,Count
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    SMailItemInfo oMailItem;
                    Tokenizer yatk(tk[i], ",");
                    oMailItem.wItemID = atoi(yatk[0].c_str());
                    oMailItem.wCount = atoi(yatk[1].c_str());
                    //LOG_CRI <<"ItemID="<<oMailItem.wItemID <<",count="<<oMailItem.wCount;
                    oMailItem.eBindType = NItemProt::eBindGet;
                    _vecLuckAward.push_back(oMailItem);
                }
            }
        }
    }
    return true;
}

bool CAnswer::SetActivityVar()
{
    time_t tNow = Time::Now();
    struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = BEGINHOUR;
	oTm.tm_min = BEGINMIN;
    oTm.tm_sec = 0;
    UINT32 dwBegin = mktime(&oTm);
    UINT32 dwAlarm =  dwBegin - BEGININTERVAL  ;
    UINT32 dwEnd = dwBegin + INTERVAL;//活动结束时间
    UINT32 dwNow = time(NULL);
    UINT32 dwTmp = 0;
    UINT8  byCnt = 0;
    if(dwAlarm > dwNow)
    {
        g_CenterGameVar.SetVar(eSystemVarAnswer,dwAlarm);
    }
    else if(dwNow > dwEnd)
    {
        dwTmp += dwAlarm + DAYSEC;
        g_CenterGameVar.SetVar(eSystemVarAnswer,dwTmp);
    }else
    { 
        if(dwNow >= dwAlarm && dwNow < (dwBegin - COUNTDOWN))
        {
            OnAlarm();

        }else if(dwNow >= (dwBegin - COUNTDOWN) && dwNow < dwBegin)
        {
            OnCountDown();

        }else if(dwNow >= dwBegin && dwNow < dwEnd)
        {
            OnBegin();
            UINT32 o = dwNow - dwBegin;
            byCnt += o / ONETOPIC;
            if(o % ONETOPIC != 0)
                byCnt += 1;
            _dwTopicID = byCnt; 
            LOG_INF <<"_dwTopicID="<<_dwTopicID<<" | byCnt = " <<byCnt;
        }
       _bRun = true;
    }
    LOG_INF <<"dwAlarm="<<dwAlarm<<"dwBegin=" << dwBegin<<"dwEnd="<<dwEnd;
    return true;
}

void CAnswer::InitParam()
{
    dwAnswer_0 = SParamConfig::wExaminationTime1Min;
    dwAnswer_2 = SParamConfig::wExaminationTime1Max;
    dwAnswer_3 = SParamConfig::wExaminationTime2Min;
    dwAnswer_5 = SParamConfig::wExaminationTime2Max;
    dwAnswer_6 = SParamConfig::wExaminationTime3Min;
    dwAnswer_10 = SParamConfig::wExaminationTime3Max;
    READ = SParamConfig::wExaminationTimeRead;
    ANSWER = SParamConfig::wExaminationTimeAnswer;
    RESULT = SParamConfig::wExaminationTimeWait;
    BYFIRST = SParamConfig::wExaminationPoint1;
    BYSECOND = SParamConfig::wExaminationPoint2;
    BYTHIRD = SParamConfig::wExaminationPoint3;
    BEGINHOUR = SParamConfig::wExaminationOpenTimeHour;
    BEGINMIN = SParamConfig::wExaminationOpenTimeMinute;
    ONETOPIC = READ + ANSWER + RESULT + READINTERVAL + RESULTINTERVAL;
    INTERVAL = ONETOPIC * dwMaxAnswerTopic;
}

bool CAnswer::RandTopic(std::vector<UINT32>& vecTopicID)
{
    bool bExsit;
    UINT32 dwIndex = 1;
    UINT32 dwCnt = 1;
    while(dwCnt <= dwMaxAnswerTopic)
    {
       bExsit = false;
       dwIndex = CRandom::RandInt(1,_dwMaxTopicNum);
       for(auto& it : vecTopicID)
       {
           if(it == dwIndex)
           {
               bExsit = true;
               break;
           }
       }
       if(!bExsit)
       {
           vecTopicID.push_back(dwIndex);
           dwCnt ++;
       }
    }
    return true;
}

bool CAnswer::OnJoin(CUser &rUser)
{
    if(!IsRunning())
    {
        LOG_INF <<"Answer not Open.";
        return false;
    }
    UINT64 qwRoleID = rUser.GetRoleID();
    if(!qwRoleID)
    {
        LOG_INF <<"qwRoleID 0.";
        return false;
    }
    SAnswerUserPtr pAnswerUser = GetUserPtr(qwRoleID);
    if(!pAnswerUser)
    {
        pAnswerUser = SAnswerUserPtr(new SAnswerUser());
        pAnswerUser->qwRoleID = qwRoleID;
        auto it = _mapID2UserInfoPtr.insert(make_pair(qwRoleID,pAnswerUser));
        if(!it.second)
        {
            LOG_INF << "qwRoleID(" << qwRoleID<<") join Err.";
            return false;
        }

        TVecINT32 vecParam;
        vecParam.push_back(1);
        rUser.OnEvent(eEventType_QuestionJoin,vecParam);
    }

    return true;
}

bool CAnswer::OnLeave(CUser &rUser)
{

    return true;
}

void CAnswer::GetCountdown(UINT64 qwRoleID,UINT32 &dwRet,SAnswerPlayer &rPlayerInfo,bool &bRet)
{
    UINT32 dwTime = Time::Now();
    UINT32 dwBegin = CalBeginTime();
    UINT32 dwEnd = dwBegin + INTERVAL;
    bRet = true; 
    dwRet = 0;
    if(dwTime < dwBegin && dwTime >= dwBegin - BEGININTERVAL)
    {
        dwRet = dwBegin - dwTime;
        bRet = true;
    }
    else if(dwTime < dwBegin - BEGININTERVAL)
    {
        dwRet = dwBegin - dwTime;
        bRet = false;
    }
    else if(dwTime > dwEnd)
    {
        dwRet = dwTime - dwBegin;
        bRet = false;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser)
        OnJoin(*pUser);
    else 
    {
        LOG_INF << "pUser null.";
        return;
    }
    SAnswerUserPtr pAnswerUser = GetUserPtr(qwRoleID);
    if(!InerSendInfo(pAnswerUser,rPlayerInfo)) //客户端需求，在打开面板的时候，主动发一次
    {
        LOG_INF <<"InerSendInfo Err.";
        return;
    }
}

//在答题之后使用技能2！ 策划新需求
void CAnswer::SkillEffect(SAnswerUserPtr &pAnswerUser)
{
    if(!pAnswerUser)
    {
        LOG_INF <<"pAnswerUser null.";
        return;
    }
    UINT8 byCurScore = pAnswerUser->GetThisScore(); 
    pAnswerUser->AddScore(byCurScore);
    pAnswerUser->SetThisScore(byCurScore * 2);
    
    OnRank(); //重新排名
    //LOG_INF <<"byCurScore = " << byCurScore <<" ,AfterAnswer useSkill2 Add Score=" <<byCurScore;
}

EAnswerResult CAnswer::UseSkill(CUser &rUser,UINT8 bySkillID)
{
    if(!IsRunning() || !_bCanUseSkill)
    {
        LOG_INF <<"Answer not Open.";
        return EAnswerResult_Err;
    }
    UINT64 qwRoleID = rUser.GetRoleID();
    SAnswerUserPtr pAnswerUser = GetUserPtr(qwRoleID);
    if(!pAnswerUser)
    {
        LOG_INF <<"pAnswerUser null.";
        return EAnswerResult_Err;
    }
    CCenterVar& rVar = rUser.GetCenterVar();
    UINT64 qwVar = rVar.GetVar(ePlayerAnswer);
    UINT8 byCnt = GetRemainSkillCount(qwRoleID,bySkillID);
    if(!byCnt)
    {
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgExaminationSkillEmpty);
        LOG_INF <<"qwRoleID=" <<qwRoleID<<",bySkillID=" <<bySkillID<<",byCnt="<<byCnt;
        return EAnswerResult_Lack;
    }
    UINT8 byBit = (bySkillID - 1) * 2;
    UINT8 byFlag = GET_ANS_BIT(qwVar,byBit);
    if(byFlag != 0) //第一位技能用过，第二位肯定没有用
    {
        byBit += 1;
    }
    qwVar = SET_ANS_BIT(qwVar, byBit);
    rVar.SetVar(ePlayerAnswer,qwVar);
    pAnswerUser->bUseSkill = true;
    pAnswerUser->bySkillType = bySkillID;
    if(bySkillID == EAnswerSkill_1)
    {
        UINT32 dwUntilFail = pAnswerUser->GetUntilFail();
        if(dwUntilFail >= DWMAXUNTILE)
            dwUntilFail = DWMAXUNTILE;
        AnswerRight(pAnswerUser,BYFIRST + dwUntilFail,0);    

    }else if(bySkillID == EAnswerSkill_2 && pAnswerUser->bAnswer)
    {
        SkillEffect(pAnswerUser);              
    }
    LOG_INF << "qwRoleID=" <<qwRoleID<<"Use Skill.SkillID=" <<bySkillID;

    TVecINT32 vecParam;
    vecParam.push_back(bySkillID);
    rUser.OnEvent(eEventType_QuestionUseSkill,vecParam);
    return EAnswerResult_Suc;
}


bool CAnswer::GetRankList(TVecAnswerRank& vecRank)
{
    if(_setRank.size() == 0)
    {
        //LOG_INF << " _setRank size 0.";
        return false;
    }
    UINT32 dwTmp = 1;
    for(auto & it : _setRank)
    {
        SAnswerRank tmpRank;
        tmpRank.dwRank = dwTmp ++; 
        GetUserName(it.qwRoleID,tmpRank.strName);
        tmpRank.dwScore = it.dwScore;
        vecRank.push_back(tmpRank);
    }
    return true;
}

void CAnswer::OnRank()
{
    if(_mapID2UserInfoPtr.size() == 0)
        return;
    _setRank.clear();
    std::set<STopicRankKey> setTmp;
    for(auto &it : _mapID2UserInfoPtr)
    {
        STopicRankKey oKey(it.second->dwTotalScore,it.second->dwTotalTime,it.second->qwRoleID);
        setTmp.insert(oKey);
    }
    //_setRank = std::move(setTmp);
    _setRank.insert(setTmp.begin(),setTmp.end());
}

bool CAnswer::SendPlayerInfo()
{
    TVecAnswerRank vecRank;
    if(!GetRankList(vecRank))
    {
        //LOG_INF <<" GetRankList err.";
        //return false;
    }
    for(auto &it : _mapID2UserInfoPtr)
    {
       LOG_INF <<"qwRoleID=" <<it.first;
       SAnswerPlayer rPlayer;
       if(!InerSendInfo(it.second, rPlayer))
           continue;
       CUserPtr pUser = CUserMgr::GetUserByUserID(it.first);
       if(pUser)
       {
           std::string strPkg = g_AnswerProtS.BuildPkg_SendAnswerInfo(rPlayer,vecRank);
           pUser->SendPkg(strPkg);
       }
    }
    return true;
}

void CAnswer::AnswerError(SAnswerUserPtr pAnswerUser)
{
    if(!pAnswerUser)
    {
        LOG_INF <<"pAnswerUser null.";
        return;
    }
    //设置本题答题错误
    pAnswerUser->bRight = false;
    //本题不得分
    pAnswerUser->SetThisScore(0);
    //连续答对数重置
    pAnswerUser->dwUntilFail = 0;
    //连续答对数，从第二个答对开始
    pAnswerUser->SetCalUntilFail(false);
    //排名
    OnRank();
}

void CAnswer::AnswerRight(SAnswerUserPtr pAnswerUser,UINT8 byCalValue,UINT32 dwCalType)
{
    if(!pAnswerUser)
    {
        LOG_INF <<"pAnswerUser null.";
        return;
    }
    //设置玩家对本题做出了回答
    
    pAnswerUser->bAnswer = true;
    //设置本题答对
    pAnswerUser->bRight = true;
    //总分加上本题答对的分数
    pAnswerUser->AddScore(byCalValue);
    //答题时间加上本题答对的时间
    pAnswerUser->AddTime(dwCalType);
    //正确答对数增加
    pAnswerUser->AddRight();
    //设置本题得分
    pAnswerUser->SetThisScore(byCalValue);
    //修改连续答对数
    pAnswerUser->ChangeUntilFail();
    //排名
    OnRank();
}

void CAnswer::AnswerReset(SAnswerUserPtr pAnswerUser)
{
    if(!pAnswerUser)
    {
        LOG_INF <<"pAnswerUser null.";
        return;
    }
    //本题是否回答重置
    pAnswerUser->bAnswer = false;
    //本题是否答对重置
    pAnswerUser->bRight  = false;
    //本题是否使用技能重置
    pAnswerUser->bUseSkill = false;
    //本题得分重置
    pAnswerUser->SetThisScore(0);
}

bool CAnswer::SendTopicInfo()
{
    STopicInfoPtr p = GetTopicPtr(); 
    if(!p)
    {
        LOG_INF <<" pTopicInfo null.";
        return false;
    }

    SAnswerTopic sTopic;
    sTopic.byIndex = static_cast<UINT8>(_dwTopicID);
    sTopic.dwTopicID = p->dwTopicID;
    sTopic.sTimeInfo.dwReadTime = READ;
    sTopic.sTimeInfo.dwAnswerTime = ANSWER;
    sTopic.sTimeInfo.dwResultTime = RESULT;
    sTopic.sTimeInfo.dwEndTime = 0;
    sTopic.byAnswer1 = p->byAnswer_1;
    
    sTopic.byAnswer2 = p->byAnswer_2;
    sTopic.byAnswer3 = p->byAnswer_3;
    sTopic.byAnswer4 = p->byAnswer_4;
    sTopic.dwRemain = dwMaxAnswerTopic - _dwTopicID;
    g_AnswerProtS.SendClt_SendTopic(NULL,0,sTopic);
    return true;
}

UINT32 CAnswer::GetSelfRank(UINT64 qwRoleID)
{
    UINT32 dwRank = 1;
    if(qwRoleID == 0)
    {
        LOG_INF <<" qwRoleID 0";
        return dwRank - 1;
    }
    for(auto &it : _setRank)
    {
        if(it.qwRoleID == qwRoleID)
            break;
        else
            dwRank ++;

    }
    return dwRank;
}

bool CAnswer::InerSendInfo(SAnswerUserPtr pAnswerUser,SAnswerPlayer &rPlayer)
{
    if(!pAnswerUser)
        return false;
    UINT64 qwRoleID = pAnswerUser->qwRoleID;
    rPlayer.qwRoleID = qwRoleID;
    rPlayer.dwRank =  GetSelfRank(qwRoleID);
    rPlayer.bRight =  pAnswerUser->bRight;
    rPlayer.dwScore = pAnswerUser->dwTotalScore;
    rPlayer.dwRight = pAnswerUser->dwRight;
    rPlayer.dwThisScore = pAnswerUser->GetThisScore();
    if(!pAnswerUser->bAnswer || !pAnswerUser->bRight)
        rPlayer.dwUntilFail = pAnswerUser->dwUntilFail = 0;
    else 
        rPlayer.dwUntilFail = pAnswerUser->dwUntilFail;
    for(UINT8 byCnt=EAnswerSkill_1; byCnt<EAnswerSkill_END; ++byCnt)
    {
        SAnswerSkill oSkillInfo;
        oSkillInfo.eSkillType = static_cast<EAnswerSkill>(byCnt);
        oSkillInfo.byRemain = GetRemainSkillCount(qwRoleID,byCnt);
        rPlayer.vecSkillInfo.push_back(oSkillInfo);
    }
    //LOG_INF <<"rPlayer dwUntilFail = " << rPlayer.dwUntilFail << " dwTotalScore=" <<rPlayer.dwScore;
    return true;
}

bool CAnswer::AnswerTopic(CUser& rUser,UINT8& byAnswerID)
{
    
    if(eTopicAnswer != _eTopicState)
    {
       // g_GlobalChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgExaminationCanNot);
        return false;
    }
    UINT64 qwRoleID = rUser.GetRoleID();
    SAnswerUserPtr pAnswerUser = GetUserPtr(qwRoleID);
    /*
    if(!pAnswerUser)
    {
        if(!OnJoin(rUser))
        {
            LOG_INF <<"OnJoin Err!";
            return false;
        }
    }
    */
    if(pAnswerUser->bAnswer)
    {
        LOG_INF <<"qwRoleID(" << qwRoleID <<") Answer twice!";
        rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgAnswerPicked));
        return false;
    }
    pAnswerUser->bAnswer = true;
    STopicInfoPtr pTopicInfo = GetTopicPtr();
    if(pTopicInfo)
    {
        if(pTopicInfo->byAnswerID != byAnswerID)
        {
            AnswerError(pAnswerUser); 
            return true;
        }
    }else 
    {
        LOG_INF <<" pTopicInfo null.";
        return false;
    }
    UINT32 dwNow = static_cast<UINT32>(time(NULL));
    UINT32 dwBeginTime = GetAnswerTime();
    if(!dwBeginTime)
    {
        LOG_INF << " dwAnswerTime is 0.";
        return false;
    }
    if(dwNow < dwBeginTime)
    {
        LOG_INF <<" dwNow < dwBeginTime";
        return false;
    }
    UINT32 dwCalType = dwNow - dwBeginTime;
    UINT8  byCalValue = 0;
    if(dwCalType >= dwAnswer_0  && dwCalType <= dwAnswer_2)
        byCalValue = BYFIRST;
    else if(dwCalType >= dwAnswer_3  && dwCalType <= dwAnswer_5)
        byCalValue = BYSECOND;
    else if(dwCalType >= dwAnswer_6  && dwCalType <= dwAnswer_10)
        byCalValue = BYTHIRD;
    else 
        byCalValue = 0;

    //在答题之前使用仅能2
    UINT8 bySkillType = 0;
    if(pAnswerUser->IsUseSkill())
        bySkillType = pAnswerUser->GetSkillType();
    UINT32 dwUntilFail = pAnswerUser->GetUntilFail();
    if(dwUntilFail >= DWMAXUNTILE)
        dwUntilFail = DWMAXUNTILE;
    if(byCalValue != 0)
        byCalValue += dwUntilFail * 1;
    if(bySkillType == EAnswerSkill_2)
    {
        byCalValue *= 2;
    }
    
    /*
    UINT32 dwUntilFail = pAnswerUser->GetUntilFail();
    if(dwUntilFail >= DWMAXUNTILE)
        dwUntilFail = DWMAXUNTILE;
    if(byCalValue != 0)
        byCalValue += dwUntilFail * 1;
    */ 
    AnswerRight(pAnswerUser,byCalValue,dwCalType); 
    
    LOG_INF << "qwRoleID=" <<qwRoleID << ", add Score(" <<byCalValue<<"),AnswerTime("<<dwCalType<<"),RightAnswer=" << _byRightAnswer <<"| UserAnswer=" << byAnswerID;
    return true;
}

void CAnswer::GetUserName(UINT64 qwRoleID,std::string& strName)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        LOG_INF << "pUser null.";
        return;
    }
    strName = pUser->GetUserName();
}

void CAnswer::ResetAllAnswer()
{
    for(auto &it : _mapID2UserInfoPtr)
    {
        AnswerReset(it.second);
    }
}

void CAnswer::CheckAnswer()
{
    for(auto &it : _mapID2UserInfoPtr)
    {
        if(it.second->bAnswer == false)
        {
            AnswerError(it.second);
        }
    }
}

SAnswerUserPtr CAnswer::GetUserPtr(UINT64 qwRoleID)
{
    auto it = _mapID2UserInfoPtr.find(qwRoleID);
    if(it == _mapID2UserInfoPtr.end())
        return NULL;
    return it->second;
}

UINT32 CAnswer::GetAnswerTime()
{
    STopicInfoPtr pTopic = GetTopicPtr(); 
    if(pTopic)
        return pTopic->sTimeInfo.dwAnswerTime;
    return 0;
}

STopicInfoPtr CAnswer::GetTopicPtr()
{
    if(_dwTopicID <= 0 || _dwTopicID > 30 || _dwTopicID > _vecTopicInfoPtr.size())
    {
        LOG_INF <<" _dwTopicID Err.";
        return NULL;
    }
    if(_vecTopicInfoPtr.size() == 0)
    {
        LOG_INF <<"_vecTopicInfoPtr size 0";
        return NULL;
    }
    
    STopicInfoPtr p = _vecTopicInfoPtr[_dwTopicID - 1];
    if(p)
        return p;
    return NULL;
}

UINT8 CAnswer::GetRemainSkillCount(UINT64 qwRoleID,UINT8 bySkillType)
{
    UINT8 byCnt = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        LOG_INF <<"GetRemainSkillCount pUser null.";
        return byCnt;
    }
    CUser& rUser = *pUser;
    CCenterVar& rVar = rUser.GetCenterVar();
    UINT64 qwVar = rVar.GetVar(ePlayerAnswer);
    UINT8 byFlag = 0;
    switch(bySkillType)
    {
        
        case EAnswerSkill_1:
            {
                byFlag = GET_ANS_BIT(qwVar,0);
                byCnt = (byFlag ? 0 : 1); 
                byFlag = GET_ANS_BIT(qwVar,1);
                byCnt += (byFlag ? 0 : 1);
            }
            break;
        case EAnswerSkill_2:
            {
                byFlag = GET_ANS_BIT(qwVar,2);
                byCnt = (byFlag ? 0 : 1); 
                byFlag = GET_ANS_BIT(qwVar,3);
                byCnt += (byFlag ? 0 : 1);
            }
            break;
        case EAnswerSkill_3:
            {
                byFlag = GET_ANS_BIT(qwVar,4);
                byCnt = (byFlag ? 0 : 1); 
                byFlag = GET_ANS_BIT(qwVar,5);
                byCnt += (byFlag ? 0 : 1);
            }
            break;
        default:
            break; 
    }
    //LOG_INF <<"byCnt = "<<byCnt;
    return byCnt;
}

bool CAnswer::InitTopicInfo()
{
    std::vector<UINT32> vecTopicID;
    if(!RandTopic(vecTopicID) || vecTopicID.size() == 0)
    {
        LOG_INF <<" GetRandTopic Err.";
        return false;
    }
    INT32 byRandID = 0;
    UINT32 dwBegin = CalBeginTime();
    for(UINT8 i=1; i<=vecTopicID.size(); ++i)
    {
        STopicInfoPtr pTopic(new STopicInfo());
        pTopic->byIndex = i;
        pTopic->dwTopicID = vecTopicID[i-1];
        pTopic->byAnswerID = GetAnswer(vecTopicID[i-1]);
        if(pTopic->byAnswerID == 0 || pTopic->dwTopicID == 0)
        {
            LOG_INF << " GetAnswer(" <<i<<") Err.";
            return false;
        }
        byRandID = CRandom::RandInt(0,5); 
        switch(pTopic->byAnswerID)
        {
            case 1:
                {
                    pTopic->byAnswer_1 = 1;
                    pTopic->byAnswer_2 = randAnswer[byRandID][0];
                    pTopic->byAnswer_3 = randAnswer[byRandID][1];
                    pTopic->byAnswer_4 = randAnswer[byRandID][2];

                }
                break;
            case 2:
                {

                    pTopic->byAnswer_1 = randAnswer[byRandID][0];
                    pTopic->byAnswer_2 = 1;
                    pTopic->byAnswer_3 = randAnswer[byRandID][1];
                    pTopic->byAnswer_4 = randAnswer[byRandID][2];
                }
                break;
            case 3:
                {

                    pTopic->byAnswer_1 = randAnswer[byRandID][0];
                    pTopic->byAnswer_2 = randAnswer[byRandID][1];
                    pTopic->byAnswer_3 = 1;
                    pTopic->byAnswer_4 = randAnswer[byRandID][2];
                }
                break;
            case 4:
                {

                    pTopic->byAnswer_1 = randAnswer[byRandID][0];
                    pTopic->byAnswer_2 = randAnswer[byRandID][1];
                    pTopic->byAnswer_3 = randAnswer[byRandID][2];
                    pTopic->byAnswer_4 = 1;
                }
                break;
            default:
                break;
        }
        //pTopic->dwFinalTime = dwBegin;
        pTopic->sTimeInfo.dwReadTime  = dwBegin;
        pTopic->sTimeInfo.dwAnswerTime  = dwBegin + READ + READINTERVAL; //读题和答题之间延时 1s 策划需求
        pTopic->sTimeInfo.dwResultTime  = dwBegin + READ + ANSWER + READINTERVAL /*+ RESULTINTERVAL */; //答题和读题之间延时 2s 策划需求
        pTopic->sTimeInfo.dwEndTime  = dwBegin + READ + READINTERVAL + ANSWER + RESULTINTERVAL + RESULT;
        dwBegin += ONETOPIC;
        //dwBegin += 1;
        _vecTopicInfoPtr.push_back(pTopic);
        //LOG_INF <<"Index="<<i<<",TopicID="<<vecTopicID[i-1]<<",AnswerID="<<pTopic->byAnswerID
        //    <<",Read="<<pTopic->sTimeInfo.dwReadTime <<"Answer="<<pTopic->sTimeInfo.dwAnswerTime
        //    <<",Result="<<pTopic->sTimeInfo.dwResultTime <<"End="<<pTopic->sTimeInfo.dwEndTime;
    }
    return true;
}

UINT32 CAnswer::CalBeginTime()
{
    time_t tNow = Time::Now();
    struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = BEGINHOUR;
	oTm.tm_min = BEGINMIN;
    oTm.tm_sec = 0;
    return mktime(&oTm);
}

UINT8 CAnswer::GetAnswer(UINT32 dwTopicID)
{
    auto it = _mapTopic2Ans.find(dwTopicID);
    if(it ==  _mapTopic2Ans.end())
        return 0;
    return it->second;
}

void CAnswer::OnAlarm()
{
    LOG_INF <<" Alarm Begin!";
    g_AnswerProtS.SendClt_AnswerAlarm(NULL,0,BEGININTERVAL);
    _vecTopicInfoPtr.clear();
    _mapID2UserInfoPtr.clear();
    _setRank.clear();

    if(!InitTopicInfo())
    {
        LOG_INF <<" InitTopicInfo Err.";
        return;
    }
    UINT32 dwBegin = CalBeginTime();
    //设置30s倒计时时间
    g_CenterGameVar.SetVar(eSystemVarAnswer, dwBegin-COUNTDOWN);
    _dwTopicID = 1;
    _bRun = true;
    _eState = eAlarm;
    LOG_INF <<" Answer Alarm suc.";
    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgAnswerReady);
}

void CAnswer::OnCountDown()
{
    g_AnswerProtS.SendClt_AnswerCountdown(NULL,0,COUNTDOWN);
    UINT32 dwBegin = CalBeginTime();
    g_CenterGameVar.SetVar(eSystemVarAnswer, dwBegin);
    _eState = eCountDown;
    LOG_INF <<"Answer CountDown 30s Suc.";
    _bRun = true;
}

void CAnswer::OnBegin()
{
    g_AnswerProtS.SendClt_AnswerBegin(NULL,0,time(NULL));
    UINT32 dwBegin = CalBeginTime();
    g_CenterGameVar.SetVar(eSystemVarAnswer, dwBegin + INTERVAL);
    _eState = eBegin;
    _bRun = true;
    LOG_INF <<"Answer Begin Suc.";
    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgAnswerBegin);
}

void CAnswer::OnEnd()
{
    g_AnswerProtS.SendClt_AnswerEnd(NULL,0,time(NULL));
    UINT32 dwBegin = CalBeginTime();
    UINT32 dwTmp  = 0;
    dwTmp = dwBegin - BEGININTERVAL + DAYSEC;
    g_CenterGameVar.SetVar(eSystemVarAnswer, dwTmp);
    _eState = eEnd;
    _bRead = _bAnswer = _bResult = _bRun = false;;
    LOG_INF <<"Answer End Suc.";
    //玩家添加经验 ,策划需求发邮件
    //CalExp();
    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgAnswerEnd);
    //发送邮件奖励
    SendMail();
}
void CAnswer::UpdateState(UINT32 dwNow,UINT32 dwNext)
{
    switch(_eState)
    {
        case eNone:
             if(dwNow >= dwNext)
                 OnAlarm();
             break;
        case eAlarm:
              if(dwNow >= dwNext)
                 OnCountDown();
            break;
        case eCountDown:
             if(dwNow >= dwNext)
                OnBegin();
            break;
        case eBegin:
             if(dwNow >= dwNext)
                OnEnd();
            break;
        case eEnd:
            _eState = eNone;
            break;
        default:
            break;
    }
}

void CAnswer::TimerCheck(time_t tNow)
{
    if(_bInit)
    {
        _vecTopicInfoPtr.clear();
        InitTopicInfo();
        _bInit = false;
    }
    if(!_bLoadVar)
    {
        if(g_CenterGameVar.IsLoad())
        {
            if(!SetActivityVar())
            {
               LOG_INF << " SetActivityVar Err.";
               return;
             }
            _bLoadVar = true;
        }
        else 
            return;
    }
    UINT32 dwNext = g_CenterGameVar.GetVar(eSystemVarAnswer);
    UINT32 dwNow = static_cast<UINT32>(tNow);
    
    //LOG_INF <<"Now:" <<dwNow <<"|dwNext=" <<dwNext << "| eState=" << _eState;
    UpdateState(dwNow,dwNext);
    Process(dwNow);

}

void CAnswer::Process(UINT32 dwNow)
{
    if(_bRun && _eState == eBegin)
    {
        STopicInfoPtr pTopic = GetTopicPtr(); 
        if(!pTopic)
        {
            LOG_INF <<" Process Topic Err.";
            return;
        }
        _byRightAnswer = pTopic->byAnswerID; //本题正确答案
        if(!_bRead && dwNow >= pTopic->sTimeInfo.dwReadTime && dwNow < pTopic->sTimeInfo.dwAnswerTime)
        {
            //玩家读题
            _eTopicState = eTopicRead;
            _bCanUseSkill = true;
            SendTopicInfo();  
           // LOG_INF <<" Read Index="<<_dwTopicID<<"| eTopicState"<< _eTopicState;
            _bRead = true;
            _bAnswer = false;
            _bResult = false;
            

        }else if(!_bAnswer && dwNow >= pTopic->sTimeInfo.dwAnswerTime && dwNow < pTopic->sTimeInfo.dwResultTime)
        {
            //玩家做题
            _eTopicState = eTopicAnswer;
            _bCanUseSkill = true;
            //LOG_INF <<" Answer Index="<<_dwTopicID <<"| eTopicState"<< _eTopicState;
            _bRead = false;
            _bAnswer = true;
            _bResult = false;

        }else if(!_bResult && dwNow >= pTopic->sTimeInfo.dwResultTime && dwNow < pTopic->sTimeInfo.dwEndTime)
        {
            //结果显示
            _eTopicState = eTopicResult;
            _bCanUseSkill = false;
            _bRead = false;
            _bAnswer = false;
            _bResult = true;
            //LOG_INF <<" Result Index="<<_dwTopicID<<"| eTopicState"<< _eTopicState;
            CheckAnswer(); //检测玩家是否回答问题
            SendPlayerInfo();
            _dwTopicID ++;
            ResetAllAnswer();
        }

    }
}

//发送邮件
void CAnswer::SendMail()
{
    for(auto &it : _mapID2UserInfoPtr)
    {
        SAnswerUserPtr pAnswerUser = it.second;
        if(pAnswerUser)
        {
            UINT32 dwRank = GetSelfRank(pAnswerUser->qwRoleID);
            LOG_INF <<"dwRank=" <<dwRank;
            OnSendMail(pAnswerUser,dwRank);
        }

        TVecINT32 vecParam;
        vecParam.push_back(pAnswerUser->dwTotalScore);
        CUser::OnRoleEvent(pAnswerUser->qwRoleID,eEventType_QuestionScore,vecParam);
    }
    // Luck Award    
   if(_mapID2UserInfoPtr.size() == 0)
   {
       LOG_INF <<"_mapID2UserInfoPtr size 0";
       return;
   }

   UINT32 dwIndex = CRandom::RandInt(1,_mapID2UserInfoPtr.size());
   auto it = _mapID2UserInfoPtr.begin();
   
   advance(it,dwIndex - 1);
   SItemAttachmentPtr pItem(new SItemAttachment());
   if(!pItem)
   {
       LOG_INF <<"pItem null. OR it NUll.";
       return ;
   }
   pItem->vecItemInfo.insert(pItem->vecItemInfo.begin(),_vecLuckAward.begin(),_vecLuckAward.end());
   CSystemMail sysMail;
   sysMail.AddTarget(it->second->qwRoleID);
   sysMail.SetSender("系统");
   sysMail.SetBody(SysMailSendTxt(523,BuildStrVec("zzz")));
   string strTile;
   CSystemMail::GetSysMailBody(522,strTile);
   sysMail.SetSubject(strTile);
   sysMail.AddItemInfo(pItem->vecItemInfo);
   sysMail.Send();
}

bool CAnswer::OnSendMail(SAnswerUserPtr pAnswerUser,UINT32 dwRank)
{
    UINT32 dwScore = pAnswerUser->dwTotalScore;
    SItemAttachmentPtr pItem(new SItemAttachment());
    if(!pItem)
    {
        LOG_INF <<"pItem null.";
        return false;
    }
    InitAwardItem(dwRank,pItem->vecItemInfo);

    //算经验
    SMailItemInfo oMailItem;
    oMailItem.wItemID = EMONEY_EXP;
    oMailItem.wCount = dwScore * 600;
    //LOG_CRI <<"ItemID="<<oMailItem.wItemID <<",count="<<oMailItem.wCount;
    oMailItem.eBindType = NItemProt::eBindGet;
    pItem->vecItemInfo.push_back(oMailItem);

    CSystemMail sysMail;
    sysMail.AddTarget(pAnswerUser->qwRoleID);
    sysMail.SetSender("系统");
    sysMail.SetBody(SysMailSendTxt(wContentID, BuildStrVec(dwScore,dwRank)));
    string strTile;
    CSystemMail::GetSysMailBody(wMailID,strTile);
    sysMail.SetSubject(strTile);
    sysMail.AddItemInfo(pItem->vecItemInfo);
    sysMail.Send();
    return true;
}

void CAnswer::InitAwardItem(UINT32 dwRank,TVecMailItemInfo &vecItem)
{
    for(auto &it : _vecAward)
    {
        if(it.wTop < dwRank && dwRank <= it.wBottom)
        {
            vecItem.insert(vecItem.begin(),it.vecItem.begin(),it.vecItem.end());
            break;
        }
    }
}

//TODO
void CAnswer::GMOpen(UINT8 byPeroid /* = 10 */)
{
   if(IsRunning())
   {
       LOG_CRI<<" Answer is running.";
       return;
   }


}
/*
void CAnswer::CalExp()
{
    if(_mapID2UserInfoPtr.size() == 0)
    {
        LOG_INF <<" _mapID2UserInfoPtr size 0.";
        return;
    }
    for(auto &it : _mapID2UserInfoPtr)
    {
        if(it.second)
        {
            UINT64 qwRoleID = it.second->qwRoleID;
            UINT32 dwScore = it.second->dwTotalScore;
            LOG_INF <<"qwRoleID= " <<qwRoleID <<" Score=" <<dwScore;
            UINT32 dwExp = dwScore * 1000;
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            TVecUserItem vecUserItem;
            SUserItem oUserItem;
            oUserItem.dwTypeID = EMONEY_EXP;
            oUserItem.dwCount = dwExp;
            vecUserItem.push_back(oUserItem);
            if(pUser)
            {
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemFrom_Answer,vecUserItem,[qwRoleID,dwExp](UINT8 byRet_, UINT8 byError)
                                {
                                    if(byRet_ || byError)
                                    {
                                       LOG_INF << "BagFull";
                                       return;
                                    }
                                    LOG_INF <<"qwRoleID="<<qwRoleID << ",AddExp(" <<dwExp<<").";
                                });
 
            }
        }
    }
}
*/

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

