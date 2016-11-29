#ifndef GAMESVERSYSMAIL_H__
#define GAMESVERSYSMAIL_H__
#include "Item.h"
#include "MailProt.h"
enum SysMailSource
{
    SEND_MONSTERDROP        = 3,    //怪物掉落
    TITLE_MONSTERDROP       = 4,    //怪物掉落标题
    BODY_MONSTERDROP        = 5,    //怪物掉落正文
    SEND_DGNPASS            = 6,    //副本通关邮件
    TITLE_DGNPASS           = 7,    //副本通关标题
    BODY_DGNPASS            = 8,    //副本通关正文
    SEND_GATHERDROP         = 9,    //采集邮件
    TITLE_GATHERDROP        = 10,   //采集标题
    BODY_GATHERDROP         = 11,   //采集正文
    SEND_ARENAAWARD         = 12,   //竞技场邮件
    TITLE_ARENAAWARD        = 13,   //竞技场标题
    BODY_ARENAAWARD         = 14,   //竞技场正文
    SEND_ARENAWIRSHIP       = 15,   //竞技场邮件
    TITLE_ARENAWIRSHIP      = 16,   //竞技场标题
    BODY_ARENAWIRSHIP       = 17,   //竞技场正文

    SEND_SHUSHANBATTLE      = 18,   //蜀山论剑奖励邮件
    TITLE_SHUSHANBATTLE     = 19,   //蜀山论剑奖励标题
    BODY_SHUSHANBATTLE      = 20,   //蜀山论剑奖励正文
    SEND_SSBTOPKILLER       = 21,   //连杀王奖励邮件(蜀山论剑)
    TITLE_SSBTOPKILLER      = 22,   //连杀王奖励标题(蜀山论剑)
    BODY_SSBTOPKILLER       = 23,   //连杀王奖励正文(蜀山论剑)
    SEND_SSBHONORKING       = 24,   //荣誉王奖励邮件(蜀山论剑)
    TITLE_SSBHONORKING      = 25,   //荣誉王奖励标题(蜀山论剑)
    BODY_SSBHONORKING       = 26,   //荣誉王奖励正文(蜀山论剑)
    SEND_YAMENHOLY          = 27,   //衙门任务,补偿圣义令
    TITLE_YAMENHOLY         = 28,   //衙门任务,补偿圣义令，标题
    BODY_YAMENHOLY          = 29,   //衙门任务,补偿圣义令，正文
    SEND_VIPFRIEND          = 30,   //给好友开启VIP特权邮件
    TITLE_VIPFRIEND         = 31,   //给好友开启VIP特权标题
    BODY_VIPFRIEND          = 32,   //给好友开启VIP特权正文
    BODY_PRESENTITEM        = 33,   //赠送物品

    SEND_WORLDBOSS_TOP      = 34,   //世界boss排行奖励邮件
    TITLE_WORLDBOSS_TOP     = 35,   //世界boss排行奖励标题
    BODY_WORLDBOSS_TOP      = 36,   //世界boss排行奖励正文

    SEND_WORLDBOSS_DMG      = 37,   //世界boss伤害奖励邮件
    TITLE_WORLDBOSS_DMG     = 38,   //世界boss伤害奖励标题
    BODY_WORLDBOSS_DMG      = 39,   //世界boss伤害奖励正文

    SEND_WORLDBOSS_LUCKY    = 40,   //世界boss幸运奖励邮件
    TITLE_WORLDBOSS_LUCKY   = 41,   //世界boss幸运奖励标题
    BODY_WORLDBOSS_LUCKY    = 42,   //世界boss幸运奖励正文
 
    SEND_WORLDBOSS_NPC      = 43,   //世界boss参与奖励邮件
    TITLE_WORLDBOSS_NPC     = 44,   //世界boss参与奖励标题
    BODY_WORLDBOSS_NPC      = 45,   //世界boss参与奖励正文
    
    SEND_WORLDBOSS_KILL     = 46,   //世界boss击杀奖励邮件
    TITLE_WORLDBOSS_KILL    = 47,   //世界boss击杀奖励标题
    BODY_WORLDBOSS_KILL     = 48,   //世界boss击杀奖励正文
	TITLE_STATUE_AWARD      = 49,   //帮派神像供奉奖励
	BODY_STSTUE_AWARD       = 50,   //你所在帮派昨天总共有($s)人供奉了神像，根据供奉的人数获得($s)银币和($s)帮贡的奖励

	TITLE_GUILDBATTLE_AWARD = 51,   //帮派战奖励
	BODY_GUILDBATTLE_AWARD  = 52,   //本轮帮派战结束，由于你在帮派战中的表现获得($s)帮派贡献的奖励！点击附件获取可获得奖励
	TITLE_BEASTSOUL_AWARD   = 53,   //篇章奖励
	BODY_BEASTSOUL_AWARD    = 54,   //点亮全部篇章奖励

    SEND_WACT_BATTLEPOINT   = 55,   //精彩活动战力排行奖励邮件
    TITLE_WACT_BATTLEPOINT  = 56,   //精彩活动战力排行奖励标题
    BODY_WACT_BATTLEPOINT   = 57,   //精彩活动战力排行奖励正文

    SNED_INVITE_SUC         = 60,   //好友邀请奖励
    TITLE_INVITE_SUC        = SNED_INVITE_SUC,//标题
    BODY_INVITE_SUC         = 61,   //正文
	TITLE_XINFA_AWARD       = 62,   //心法散功返回标题
	BODY_XINFA_AWARD        = 63,   //心法散功返回内容
    
    TITLE_WORLDBOSS_DMGRATE = 71,   //世界Boss伤害奖励
    BODY_WORLDBOSS_DMGRATE  = 72,   //您在本次世界Boss活动中亲手将Boss血量降低至$s%以下，获得伤害奖励，请在附件中查收
    
    SEND_DRAGONBALL_ACT     = 73,   //七龙珠奖励邮件
    TITLE_DRAGONBALL_ACT    = 74,   //七星龙珠奖励标题
    BODY_DRAGONBALL_ACT     = 75,   //七星龙珠奖励正文
    TITLE_DRAGONBALL_ENDACT = 76,   //七星连珠奖励标题
    BODY_DRAGONBALL_ENDACT  = 77,   //七星连珠奖励正文
    
    SEND_TASKMARKET_ACT     = 78,   //任务集市奖励邮件
    TITLE_TASKMARKET_ACT    = SEND_TASKMARKET_ACT,   //任务集市奖励标题
    BODY_TASKMARKET_ACT     = 79,   //任务集市奖励正文

    SEND_FIGHTERDISMISS     = 84,   //散功返还
    TITLE_FIGHTERDISMISS    = 85,   //散功返还
    BODY_FIGHTERDISMISS     = 86,   //散功返还奖励正文
    
    SEND_RECHARGE_MAIL     = 88,   //充值仙石邮件
    TITLE_RECHARGE_MAIL    = SEND_RECHARGE_MAIL,   //充值仙石标题
    BODY_RECHARGE_MAIL     = 89,   //充值仙石正文

    SEND_MONTHCARD         = 92,   //月卡奖励邮件
    TITLE_MONTHCARD        = SEND_MONTHCARD,   //月卡奖励标题
    BODY_MONTHCARD         = 93,   //月卡奖励正文
    SEND_MONTHCARD_OVERDUE  = 94,   //月卡过期邮件
    TITLE_MONTHCARD_OVERDUE = SEND_MONTHCARD_OVERDUE,   //月卡过期标题
    BODY_MONTHCARD_OVERDUE  = 95,   //月卡过期正文

    SEND_NEW_GUILD_BATTLE_SELF_MAIL     = 543,   //新帮派战邮件(个人)
    TITLE_NEW_GUILD_BATTLE_SELF_MAIL    = SEND_NEW_GUILD_BATTLE_SELF_MAIL,   //新帮派战标题(个人)
    BODY_NEW_GUILD_BATTLE_SELF_MAIL     = 544,   //新帮派战正文(个人)

    SEND_NEW_GUILD_BATTLE_CAPTURE_MAIL     = 545,   //新帮派战邮件(占领)
    TITLE_NEW_GUILD_BATTLE_CAPTURE_MAIL    = SEND_NEW_GUILD_BATTLE_CAPTURE_MAIL,   //新帮派战标题(占领)
    BODY_NEW_GUILD_BATTLE_CAPTURE_MAIL     = 546,   //新帮派战正文(占领)

    SEND_NEW_GUILD_BATTLE_LOST_MAIL     = 547,   //新帮派战邮件(失败)
    TITLE_NEW_GUILD_BATTLE_LOST_MAIL    = SEND_NEW_GUILD_BATTLE_LOST_MAIL,   //新帮派战标题(失败)
    BODY_NEW_GUILD_BATTLE_LOST_MAIL     = 548,   //新帮派战正文(失败)

    SEND_FIRST_GOLD_LOTTERY     = 524,   //游历奖励
    TITLE_FIRST_GOLD_LOTTERY    = 525,   //游历奖励
    BODY_FIRST_GOLD_LOTTERY     = 526,   //\x20\x20\x20\x20行千里路，得万贯财，你在游历中获得了散仙谢琳的认可！点击附件领取奖励！

    SEND_LINGSHAN           = 541,   //秘境夺宝奖励
    TITLE_LINGSHAN          = 541,   //秘境夺宝奖励
    BODY_LINGSHAN           = 542,   //\x20\x20\x20\x20您在秘境夺宝中夺得了惊天机缘。点击附件领取奖励

    SEND_RECHARGEAWARD           = 551,   //冲值大回馈奖励
    TITLE_RECHARGEAWARD         = 551,   //冲值大回馈奖励
    BODY_RECHARGEAWARD           = 552,   //您在冲值大回馈中夺得了惊天机缘。点击附件领取奖励


};

class GameServerSysMail
{
    public:
        static bool Init();
        static bool GetMailMsgbyId(UINT32 dwMsgId,string& strMsg);

        static void SendSysMail(const string &strSender,const string& strTitle,const NMailProt::SysMailSendTxt& stBody, 
                const TVecUINT64 &vecTargets,std::vector<SItemGenInfo> * pvecGen = NULL,std::vector<CItemPtr>* pInsTance = NULL );

        static void SendSysMail(UINT32 dwSendId,UINT32 dwTitleId,const NMailProt::SysMailSendTxt& stBody, 
                const TVecUINT64 &vecTargets,std::vector<SItemGenInfo> * pvecGen = NULL,std::vector<CItemPtr>* pInsTance = NULL );

    private:
       static map<UINT32,string> _mapMailMsg;

};















#endif //GAMESVERSYSMAIL_H__
