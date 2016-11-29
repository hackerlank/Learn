
#ifndef ANSWER_H_
#define ANSWER_H_

#include "Singleton.h"
#include "AnswerProt.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
using namespace NAnswerProt;
using namespace NVarDefine;

struct STopicRankKey
{
    UINT32 dwScore;
    UINT32 dwTime;
    UINT64 qwRoleID;
    STopicRankKey(UINT32 dwS,UINT32 dwT,UINT64 qwR) :
        dwScore(dwS),
        dwTime(dwT),
        qwRoleID(qwR)
    {}
    bool operator < (const STopicRankKey& sk) const
    {
        if(dwScore != sk.dwScore)
            return dwScore > sk.dwScore;
        else if(dwTime != sk.dwTime)
            return dwTime < sk.dwTime;
        return qwRoleID < sk.qwRoleID;
    }

};
struct SAnswerAward
{
    UINT16 wTop;
    UINT16 wBottom;
    TVecMailItemInfo vecItem; 
    SAnswerAward()
    {
        wTop = 0;
        wBottom = 0;
    }
};
typedef std::vector<SAnswerAward> TVecAnswerAward;

struct STopicInfo
{
    UINT8  byIndex;
    UINT32 dwTopicID;
    UINT8 byAnswerID;
    UINT8 byAnswer_1;
    UINT8 byAnswer_2;
    UINT8 byAnswer_3;
    UINT8 byAnswer_4;
    SAnswerTime sTimeInfo;
    STopicInfo()
    {
        byIndex = 0;
        dwTopicID = 0;
        byAnswerID = 0;
        byAnswer_1 = byAnswer_2 = byAnswer_3 = byAnswer_4 = 0;
        sTimeInfo.dwReadTime = sTimeInfo.dwAnswerTime = sTimeInfo.dwEndTime = sTimeInfo.dwResultTime = dwTopicID;
    }
};
typedef shared_ptr<STopicInfo> STopicInfoPtr;
typedef std::vector<STopicInfoPtr> TVecTopicInfoPtr;

struct SAnswerUser
{
    UINT64 qwRoleID;
    UINT32 dwRank;
    UINT32 dwTotalScore;
    UINT32 dwTotalTime;
    UINT32 dwUntilFail;
    UINT32 dwRight;
    UINT32 dwThisScore;
    bool   bRight; //玩家本次答题是否正却
    bool   bCalUntilFail; //记录本次是否累积连续答对数
    bool   bUseSkill;//记录玩家是否使用技能
    UINT8  bySkillType;//玩家使用技能类型
    bool   bAnswer; //玩家本轮是否答题

    SAnswerUser() : qwRoleID(0),dwRank(0),dwTotalScore(0),dwTotalTime(0),dwUntilFail(0),dwRight(0),dwThisScore(0),bRight(false),bCalUntilFail(false),bUseSkill(false),bySkillType(0),bAnswer(false)
    { }
    bool IsUseSkill() { return bUseSkill; }
    UINT8 GetSkillType() { return bySkillType; }
    void  AddScore(UINT8 byValue) { dwTotalScore += byValue; }
    void  AddTime(UINT32 dwTime) { dwTotalTime += dwTime; }
    void  AddRight() { dwRight += 1; }
    UINT32 GetUntilFail() { return dwUntilFail; }
    bool  ChangeUntilFail();
    void  SetCalUntilFail(bool b) { bCalUntilFail = b ; }
    bool  GetCalUntilFail() { return bCalUntilFail; }
    bool  GetRight() { return bRight; }
    bool  GetAnswer() {  return bAnswer; }
    void  SetThisScore(UINT32 dwTmp) { dwThisScore = dwTmp; }
    UINT32 GetThisScore() { return dwThisScore; }

};
typedef shared_ptr<SAnswerUser> SAnswerUserPtr;
typedef std::map<UINT64,SAnswerUserPtr> TMapID2UserInfoPtr;

class CAnswer : public Singleton<CAnswer>
{
public:
    enum EState
    {
        eNone,
        eAlarm,
        eCountDown,
        eBegin,
        eEnd
    };
    enum ETopicState
    {
        eTopicNone,
        eTopicRead,
        eTopicAnswer,
        eTopicResult,
        eTopicEnd
    };
public:
    CAnswer();
    virtual ~CAnswer() {}
    
    //初始化 
    bool Init();
    //读配置
    bool LoadConfig();
    //初始化题目
    bool InitTopicInfo();
    //产生随机题目
    bool RandTopic(std::vector<UINT32>& vecTopicID); 
    //玩家答题
    bool AnswerTopic(CUser& rUser,UINT8& byAnswerID);
    //时间检测
    void TimerCheck(time_t tNow);
    //获得玩家排名列表
    bool GetRankList(TVecAnswerRank& vecRank);
    //每答完一题，向客户端发显示玩家数据
    bool SendPlayerInfo();
    //向客户端推送题目信息
    bool SendTopicInfo();
    //玩家使用技能
    EAnswerResult UseSkill(CUser &rUser,UINT8 bySkillID);
    //活动结束 发邮件
    void SendMail();
    //玩家报名参加游戏
    bool OnJoin(CUser &rUser);
    bool OnLeave(CUser &rUser);
    void GetCountdown(UINT64 qwRoleID,UINT32 &dwTime,SAnswerPlayer& sPlayerInfo,bool& bRet);//获取倒计时，客户端需求
    void OnBegin();
    void OnAlarm();
    void OnEnd();
    //30s倒计时
    void OnCountDown(); 
   
    //TODO
    void GMOpen(UINT8 byPeroid = 10);  
private:
    void SetCurTopicID(UINT32 dwTopicID) { _dwTopicID = dwTopicID; }
    UINT32 GetCurTopicID() const { return _dwTopicID; }
    SAnswerUserPtr GetUserPtr(UINT64 qwRoleID);
    void GetUserName(UINT64 qwRoleID,std::string& strName);
    bool InerSendInfo(SAnswerUserPtr pAnswerUser,SAnswerPlayer &rPlayer);
    void OnRank();
    bool IsRunning() { return _bRun; }
    UINT32 GetAnswerTime();
    STopicInfoPtr GetTopicPtr();
    UINT8 GetRemainSkillCount(UINT64 qwRoleID,UINT8 bySkillType);
    bool SetActivityVar();
    UINT32 CalBeginTime();
    UINT8 GetAnswer(UINT32 dwTopicID);
    void  UpdateState(UINT32,UINT32);
    void  Process(UINT32 dwNow);
    UINT32 GetSelfRank(UINT64 qwRoleID);
    void ResetAllAnswer();
    void AnswerError(SAnswerUserPtr pAnswerUser);
    void AnswerRight(SAnswerUserPtr pAnswerUser,UINT8 byCalValue,UINT32 dwCalType);
    void AnswerReset(SAnswerUserPtr pUser);
    void SkillEffect(SAnswerUserPtr &pAnswerUser);
    void CheckAnswer();
    bool OnSendMail(SAnswerUserPtr pAnswerUser,UINT32 dwRank);
    void InitAwardItem(UINT32 dwRank,TVecMailItemInfo &vecItem);
    void CalExp();
    void InitParam();
private:
    UINT32 _dwTopicID; //当前题目ID
    std::map<UINT32,UINT8> _mapTopic2Ans;  //题目<-->答案
    bool   _bInit; //服务器是否在活动期间重启过
    TVecTopicInfoPtr _vecTopicInfoPtr; //本次活动提取的答题信息
    std::set<STopicRankKey> _setRank; //临时保存玩家排名信息
    TMapID2UserInfoPtr  _mapID2UserInfoPtr; //报名玩家
    UINT32 _dwMaxTopicNum;
    bool _bRun;
    EState _eState;
    UINT8 _byRightAnswer;
    bool  _bLoadVar;
    ETopicState  _eTopicState;
    bool  _bRead;
    bool  _bAnswer;
    bool  _bResult;
    bool  _bCanUseSkill;
    TVecAnswerAward _vecAward;    
    TVecMailItemInfo _vecLuckAward;

private:
    UINT32 dwAnswer_0;
    UINT32 dwAnswer_2;
    UINT32 dwAnswer_3;
    UINT32 dwAnswer_5;
    UINT32 dwAnswer_6;
    UINT32 dwAnswer_10;
    UINT32 READ;
    UINT32 ANSWER;
    UINT32 RESULT;
    UINT32 READINTERVAL;
    UINT32 RESULTINTERVAL;
    UINT8  BYFIRST;
    UINT8  BYSECOND;
    UINT8  BYTHIRD;
    UINT32 ONETOPIC; 
    UINT32 INTERVAL;
    UINT32 BEGINHOUR;
    UINT32 BEGINMIN;
};

#define AnswerMgr CAnswer::Instance()

#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

