using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Text.RegularExpressions;
using System.Collections;
using System.Windows.Forms;
using System.Drawing;

namespace TaskEditor
{
    public enum ETaskType
    {
        eTaskNone = 0,
        eTaskMain,      //主线
        eTaskBranch,    //支线
        eTaskDay,       //日常
        eTaskVip,       //vip
        eTaskGuide      //新手引导
    };

    public enum EContentType
    {
        eContentNone = 0,
        eContentKill = 1,           //猎杀
        eContentGrow = 1 << 1,      //成长
        eContentCollect = 1 << 2,   //收集
        eContentGather = 1 << 3,    //采集
        eContentProbe = 1 << 4,     //探索
        eContentBehave = 1 << 5,    //行为
        eContentBuild = 1 << 6,     //建设
        eContentTalk = 1 << 7       //对话
    };

    //领取提交类型
    public enum ETargetType
    {
        eTargetNone,	//无
        eTargetNpc,		//NPC委托
        eTargetScene,	//系统给予
        eTargetItem,		//道具触发
    };

    //任务类型扩展标记
    public enum ETaskTypeExtent
    {
        eTaskTypeExtent_normal = 0,     //一般任务
        eTaskTypeExtent_reward = 1,     //悬赏任务
    };

    //性别限制
    public enum ELimitGender
    {
        eLimitGender_none = 0,
        eLimitGender_Male,
        eLimitGender_Female,
    };

    //阵营限制
    public enum ELimitCamp
    {
        eLimitCamp_none = 0,    // 无限制
        eLimitCamp_1,           // 峨眉
        eLimitCamp_2,           // 昆仑
        eLimitCamp_3,           // 中立
    };

    //家族公会限制
    public enum ELimitFamily
    {
        eLimitFamily_none = 0,
        eLimitFamily_family,
        eLimitFamily_faction,
    };

    //任务过程-成长-角色属性
    public enum EProcessRoleProperty
    {
        eProcessRoleProperty_none = 0,
        eProcessRoleProperty_level,     //等级
        eProcessRoleProperty_repute,    //声望
    };

    //任务过程-行为-功能
    public enum EProcessAction
    {
        eProcessAction_none = 0, 
        eProcessAction_sCopy,           //单人副本
        eProcessAction_mCopy,           //多人副本
        eProcessAction_StrEquip,        //强化装备次数
        eProcessAction_Upgrade,         //装备铸造
        eProcessAction_WorldBoss,       //世界boss伤害
        eProcessAction_JoinGuild,       //加入帮派
        eProcessAction_RecruitCortege,  //招募散仙
        eProcessAction_Chest,           //扫荡副本
        eProcessAction_RanCortege,      //培养散仙
        eProcessAction_GuildContrib,    //帮派贡献
        eProcessAction_GuildSkill,      //帮派技能
        eProcessAction_Skill,           //升级技能
        eProcessAction_CollectGame,     //收藏游戏
        eProcessAction_UnlockEquip,     //解封装备
        eProcessAction_LearnSkill,      //获得技能
        eProcessAction_GetTrump,        //获得法宝
        eProcessAction_Refer,           //推荐好友
        eProcessAction_ActFormation,    //激活阵型
        eProcessAction_ActMounts,       //激活坐骑
        eProcessAction_MountsUp,        //坐骑升级
        eProcessAction_ActPet,          //激活阵灵
        eProcessAction_PetUp,           //阵灵升级
        eProcessAction_FighterWork,     //散仙出战
        eProcessAction_FighterCT,       //散仙淬体
        eProcessAction_FighterTrump,    //散仙法宝
        eProcessAction_FighterSkill,    //散仙技能
        eProcessAction_UpdateTrump,     //法宝祭炼
        eProcessAction_TodayActivity,   //当日活跃度 
        eProcessAction_FinishGroupTask, //完成师门任务
        eProcessAction_FinishYaMenYask, //完成衙门任务
        eProcessAction_FighterDuJie,    //散仙渡劫到N
        eProcessAction_MakeFire,        //仙府祈火
        eProcessAction_BeastUpLevel,    //兽魂升级
        eProcessAction_FighterSkillUpLevel,//散仙技能升级 0
        eProcessAction_Max              //行为最大值
    };

    //一般奖励
   /* public enum EAwardGeneral
	{
        gold = 1, // 仙石
		coupon,	// 礼券
		silver, // 钱币
        soul, // 魂魄
        prestige, // 声望
        honor, // 荣誉
        pexp, // 修为
        sigil, // 符印
        centsy, // 仙元
        action, // 体力
        sop, // 阅历
        taoism, // 道术
        poten, // 潜能
        reiki, // 灵力
        hfp, // 寻仙积分
        exp, // 经验
		end,
	}*/

    //一般奖励
     public enum EAwardGeneral
     {
         gold = 1,      // 仙石
         silver,        // 钱币
         coupon,	    // 礼券
         giftcoin,      // 金券
         exp,           // 经验
         prestige,      // 声望
         soul,          // 魂魄
         honor,         // 荣誉
         pexp,          // 修为
         sigil,         // 符印
         centsy,        // 仙元
         action,        // 体力
         sop,           // 阅历
         taoism,        // 道术
         poten,         // 渡劫点数
         peiki,         // 副本星级
         hfp,           // 寻仙积分
         demonsoul,     // 封印点
         soulattack,    // 攻击之魂
         soulhp,        // 生命之魂
         soulcritical,  // 暴击之魂
         soulcounter,   // 反击之魂
         soulspeed,     // 身法之魂
         souldefence,   // 防御之魂
         soulhit,       // 命中之魂
         souldodge,     // 闪避之魂
         achievementap, // 成就点
         collectap,     // 收藏点
         guildcontrib,  // 帮派贡献
         end,
     }

    //一般奖励
    class SAwardGeneral
    {
        public EAwardGeneral type;
        public uint value;
    };

    //属性奖励
    public enum EAwardProperty
    {
        repute = 0,    //声望
        familyContri,    //家族贡献
        factionContri,   //公会贡献
        end,
    };

    class CGatherIdxCount
    {
        public UInt32 dwIdx;
        public UInt16 wCount;
        public string strParam = "";
    }

    class CIdxNameType
    {
        public UInt32 dwIdx;
        public string strName = "";
        public Byte byType;
    }

    class CIdxNameCount
    {
        public UInt32 dwIdx;
        public string strName = "";
        public UInt16 wCount;
    }

    class CIdxNameCountEx
    {
        public UInt32 dwIdx;
        public string strName = "";
        public UInt16 wCount;
        public UInt32 dwFakeIdx;
        public string strParam = "";
    }

    class CIdxNameCountJob
    {
        public UInt32 dwIdx;
        public string strName = "";
        public UInt16 wCount;
        public string strJobName = "";
        public UInt16 wJob;
    }

    class CIdxKillItemCount
    {
        public UInt32 dwIdx1;
        public string strName1 = "";
        public UInt32 dwIdx2;
        public string strName2 = "";
        public UInt16 wCount;
        public string strParam = "";
    }

    class CIdxMercenPos
    {
        public UInt16 wIdx;
        public UInt16 wNameIDx;
        public UInt16 wPos;
    }

    public class CIdxName
    {
        public UInt32 id;
        public string name = "";
    }

    public class CEnumValue
    {
        public Byte type;
        public UInt32 value;
        public UInt32 param;
    }

    public class CEnumValueStr
    {
        public Byte type;
        public UInt32 value;
        public string param = "";
    }

    public class CEnumValueExt
    {
        public Byte type;
        public UInt32 value;
        public UInt32 dwIdx;
        public string name = "";
    }

    class CChat
    {
        public string strPC = "";
        public string strNPC = "";
    }

    class CNpcTalk
    {
        public string strName = "";

        private ArrayList arChat;
        public ArrayList ArChat
        {
            get
            {
                if (arChat == null)
                    arChat = new ArrayList();
                return arChat;
            }
            set { arChat = value; }
        }

        private ArrayList arReceiveItem;
        public ArrayList ArReceiveItem
        {
            get
            {
                if (arReceiveItem == null)
                    arReceiveItem = new ArrayList();
                return arReceiveItem;
            }
            set { arReceiveItem = value; }
        }
    }

    class CMapArea
    {
        public UInt32 dwMapID;
        public string strName = "";
        public int x;
        public int z;
        public int x2;
        public int z2;
        public string strParam = "";
    }

    class CUseItem
    {
        public UInt32 dwItemID;
        public string strName;
        public CMapArea mapArea;
    }

    class CUseSkill
    {
        public UInt32 dwSkillID;
        public string strName;
        public CMapArea mapArea;
    }

    class CSelection
    {
        public int argb;
        public int start;
        public int end;
    }

    class CTaskText
    {
        public string strText = "";
        public ArrayList arSelection = new ArrayList();

        public string ColorText
        {
            get
            {
                string strColorText = strText;
                int delta = 0;
                foreach (Object obj in arSelection)
                {
                    CSelection sel = (CSelection)obj;
                    int start = sel.start + delta;
                    int end = sel.end + delta;
                    string strPrev = strColorText.Substring(0, start);
                    string strNext = strColorText.Substring(end + 1);
                    string strColor = strColorText.Substring(start, end - start + 1);
                    string strFormat = "<color value='#" + sel.argb.ToString("X8").Substring(2) + "'>" + strColor + "</color>";
                    strColorText = strPrev + strFormat + strNext;
                    delta += strFormat.Length - strColor.Length;
                }
                return strColorText;
            }
            set
            {
                arSelection.Clear();
                int len = @"<color value='#FFFFFF'></color>".Length;
                Regex rx = new Regex(@"<color value='#(?<1>[\d\w]*)'>(?<2>[^<>]*)</color>", RegexOptions.Compiled);
                MatchCollection matches = rx.Matches(value);
                int start = 0;
                ArrayList arPlainText = new ArrayList();
                ArrayList arColorText = new ArrayList();
                int delta = 0;
                foreach (Match match in matches)
                {
                    string strPrev = value.Substring(start, match.Index - start);
                    arPlainText.Add(strPrev);
                    start = match.Index + match.Length;
                    GroupCollection groups = match.Groups;
                    string strColor = match.Groups[1].Value;
                    string strInnerText = match.Groups[2].Value;
                    arColorText.Add(strInnerText);
                    CSelection sel = new CSelection();
                    sel.start = match.Index - delta;
                    delta += len;
                    sel.end = start - 1 - delta;
                    sel.argb = (int)(UInt32.Parse(strColor, NumberStyles.HexNumber) & 0xFFFFFFFF);
                    arSelection.Add(sel);
                }
                string strColorText = "";
                for (int i = 0; i < arPlainText.Count; ++i)
                {
                    string str1 = (string)arPlainText[i];
                    string str2 = (string)arColorText[i];
                    strColorText += str1 + str2;
                }
                strColorText += value.Substring(start);
                strText = strColorText;
            }
        }

        public void Resize(int end)
        {
            CSelection[] arSel = (CSelection[])arSelection.ToArray(typeof(CSelection));
            for (int i = 0; i < arSelection.Count; ++i)
            {
                CSelection sel = arSel[i];
                if (sel.start > end)
                    arSelection.Remove(sel);
                else if (sel.end > end)
                    sel.end = end;
            }
        }

        public void ShowColor(RichTextBox textBox)
        {
            foreach (Object obj in arSelection)
            {
                CSelection sel = (CSelection)obj;
                textBox.SelectionStart = sel.start;
                textBox.SelectionLength = sel.end - sel.start + 1;
                textBox.SelectionColor = Color.FromArgb(sel.argb);
            }
        }

        private class CLess : IComparer
        {
            int IComparer.Compare(Object x, Object y)
            {
                CSelection selX = (CSelection)x;
                CSelection selY = (CSelection)y;
                return selX.start - selY.start;
            }
        }

        public void AddSelection(int start, int end, int argb)
        {
            ArrayList arAdd = new ArrayList();
            ArrayList arDel = new ArrayList();
            foreach (Object obj in arSelection)
            {
                CSelection sel = (CSelection)obj;

                if (start <= sel.start && end > sel.start)
                {
                    if (end < sel.end)
                        sel.start = end + 1;
                    else
                        arDel.Add(sel);
                }
                else if (start >= sel.start && start < sel.end)
                {
                    if (end < sel.end)
                    {
                        CSelection newSel2 = new CSelection();
                        newSel2.start = end + 1;
                        newSel2.end = sel.end;
                        newSel2.argb = sel.argb;
                        arAdd.Add(newSel2);
                    }
                    sel.end = start - 1;
                }
            }

            arSelection.AddRange(arAdd);
            foreach (Object obj in arDel)
            {
                arSelection.Remove(obj);
            }

            if ((UInt32)argb != 0xFF000000)
            {
                CSelection newSel = new CSelection();
                newSel.start = start;
                newSel.end = end;
                newSel.argb = argb;
                arSelection.Add(newSel);
            }

            arSelection.Sort(new CLess());

            arDel.Clear();
            CSelection prev = null;
            foreach (Object obj in arSelection)
            {
                CSelection next = (CSelection)obj;
                if (prev != null)
                {
                    if (prev.argb == next.argb && prev.end + 1 >= next.start)
                    {
                        next.start = prev.start;
                        arDel.Add(prev);
                    }
                }
                prev = next;
            }
            foreach (Object obj in arDel)
            {
                arSelection.Remove(obj);
            }
        }
    }

    //任务触发类型
    public enum ETaskTriggerType
    {
        eMap = 0,   //区域触发
        eNpc = 1,   //npc触发
        eItem = 2,  //道具触发
        end = 3
    };

    //任务属性触发类型
    public enum ETaskLimitPropType
    {
        none = 0,
        eLevel = 1, //等级触发
        eRepute = 2,    //声望触发
        end = 3
    }

    class CTaskInfo
    {
        public UInt16 wID;
        public string strName;
        public Byte byLevel;
        public UInt32 dwTaskType;
        public Byte byOpen;
        public Byte byShare;
        public Byte byCanGiveUp;   //可否放弃
        public Byte byAwardLinkLevel;   //奖励是否等级相关
        public UInt32 dwRepeat;
        public Byte byTaskTypeExtent;   //任务类型扩展
        public UInt32 dwContentType;
        public Byte byGuideType;   //任务引导类型

        public UInt32 dwStarGroupID;
        public UInt32 dwTaskStar;

        private ArrayList arTriggerTarget;

        public ArrayList ArTriggerTarget
        {
            get
            {
                if (arTriggerTarget == null)
                    arTriggerTarget = new ArrayList();
                return arTriggerTarget;
            }
            set { arTriggerTarget = value; }
        }

        private ArrayList arSubmitTarget;

        public ArrayList ArSubmitTarget
        {
            get
            {
                if (arSubmitTarget == null)
                    arSubmitTarget = new ArrayList();
                return arSubmitTarget;
            }
            set { arSubmitTarget = value; }
        }

        //任务描述
        public CTaskText taskTextDesc = new CTaskText();
        public CTaskText taskTextPurpose = new CTaskText();
        public CTaskText taskTextFail = new CTaskText();
        public CTaskText taskTextFinish = new CTaskText();

        //任务限制
        public Byte limitGender;    //性别限制
        public UInt16 limitReputeMin;//声望限制
        public UInt16 limitReputeMax;
        public UInt16 limitJingJieMin;  //境界限制
        public UInt16 limitJingJieMax;

        public Byte limitCamp;      //阵营限制
        public Byte limitFamily;    //家族公会限制
        public Byte limitRace;      //种族限制

        public long limitDateFrom;  //日期限制
        public long limitDateTo;

        public UInt16 limitDayTimeFrom; //每日时间段限制，目前存储的为hour值
        public UInt16 limitDayTimeTo;

        public Byte limitPreTaskFlag;   //0, 全部完成；1，完成其一
        public ArrayList preTasks;  //前置任务列表
        public ArrayList PreTasks
        {
            get
            {
                if (null == preTasks)
                {
                    preTasks = new ArrayList();   
                }

                return preTasks;
            }

            set { preTasks = value; }
        }

        public ArrayList limitCareers;   //职业限制
        public ArrayList LimitCareers
        {
            get
            {
                if (null == limitCareers)
                {
                    limitCareers = new ArrayList();
                }

                return limitCareers;
            }

            set { limitCareers = value; }
        }

        //属性限制
        private ArrayList limitProps;  //奖励_角色属性
        public ArrayList LimitProps
        {
            get
            {
                if (limitProps == null)
                    limitProps = new ArrayList();
                return limitProps;
            }
            set { limitProps = value; }
        }
        public UInt32 limitProp_campID;   //奖励_声望属性对应的阵营ID
        //public string limitProp_campName;

        //区域限制
        public UInt32 limitMapID;
       
        //任务过程
        //综合设定
        public UInt32 dwLimitTime;
        private ArrayList arGiveItem;

        public ArrayList ArGiveItem
        {
            get
            {
                if (arGiveItem == null)
                    arGiveItem = new ArrayList();
                return arGiveItem;
            }
            set { arGiveItem = value; }
        }

        //猎杀
        private ArrayList arKillMonster;
        public ArrayList ArKillMonster
        {
            get
            {
                if (arKillMonster == null)
                    arKillMonster = new ArrayList();
                return arKillMonster;
            }
            set { arKillMonster = value; }
        }

        //成长
        private ArrayList roleProps;  //角色属性
        public ArrayList RoleProps
        {
            get
            {
                if (roleProps == null)
                    roleProps = new ArrayList();
                return roleProps;
            }
            set { roleProps = value; }
        }

        //收集
        private ArrayList arCollectItem;
        public ArrayList ArCollectItem
        {
            get
            {
                if (arCollectItem == null)
                    arCollectItem = new ArrayList();
                return arCollectItem;
            }
            set { arCollectItem = value; }
        }

        //击杀收集
        private ArrayList arKillCollectItem;
        public ArrayList ArKillCollectItem
        {
            get
            {
                if (arKillCollectItem == null)
                    arKillCollectItem = new ArrayList();
                return arKillCollectItem;
            }
            set { arKillCollectItem = value; }
        }

        //采集
        private ArrayList arGather;
        public ArrayList ArGather
        {
            get
            {
                if (arGather == null)
                    arGather = new ArrayList();
                return arGather;
            }
            set { arGather = value; }
        }

        //探索
        public Byte ProbeFlag;   //0, 探索全部；1，探索其一
        private ArrayList arProbe;
        public ArrayList ArProbe
        {
            get
            {
                if (arProbe == null)
                    arProbe = new ArrayList();
                return arProbe;
            }
            set { arProbe = value; }
        }

        //行为
        private ArrayList roleActions;
        public ArrayList RoleActions
        {
            get
            {
                if (roleActions == null)
                    roleActions = new ArrayList();
                return roleActions;
            }
            set { roleActions = value; }
        }

        //建设
        private ArrayList buildings;    //建筑
        public ArrayList Buildings
        {
            get
            {
                if (buildings == null)
                    buildings = new ArrayList();
                return buildings;
            }
            set { buildings = value; }
        }

        private ArrayList technics; //科技
        public ArrayList Technics
        {
            get
            {
                if (technics == null)
                    technics = new ArrayList();
                return technics;
            }
            set { technics = value; }
        }

        private ArrayList arUseItem;
        public ArrayList ArUseItem
        {
            get
            {
                if (arUseItem == null)
                    arUseItem = new ArrayList();
                return arUseItem;
            }
            set { arUseItem = value; }
        }

        private ArrayList arUseSkill;
        public ArrayList ArUseSkill
        {
            get
            {
                if (arUseSkill == null)
                    arUseSkill = new ArrayList();
                return arUseSkill;
            }
            set { arUseSkill = value; }
        }


        //对话
        /*
        private ArrayList arNpcTalk;
        public ArrayList ArNpcTalk
        {
            get
            {
                if (arNpcTalk == null)
                    arNpcTalk = new ArrayList();
                return arNpcTalk;
            }
            set { arNpcTalk = value; }
        }*/

        private Dictionary<UInt32, CNpcTalk> mapNpc2Talk;
        public Dictionary<UInt32, CNpcTalk> MapNpc2Talk
        {
            get
            {
                if (mapNpc2Talk == null)
                    mapNpc2Talk = new Dictionary<UInt32, CNpcTalk>();
                return mapNpc2Talk;
            }
            set { mapNpc2Talk = value; }
        }

        //任务奖励
        //一般奖励
        private ArrayList awardGeneral;
        public ArrayList AwardGeneral
        {
            get
            {
                if (awardGeneral == null)
                    awardGeneral = new ArrayList();
                return awardGeneral;
            }
            set { awardGeneral = value; }
        }

        public float fStarCoef;
        public float fRingCoef;

        private ArrayList arMustAwardItem;

        public ArrayList ArMustAwardItem
        {
            get
            {
                if (arMustAwardItem == null)
                    arMustAwardItem = new ArrayList();
                return arMustAwardItem;
            }
            set { arMustAwardItem = value; }
        }
        private ArrayList arOptAwardItem;

        public ArrayList ArOptAwardItem
        {
            get
            {
                if (arOptAwardItem == null)
                    arOptAwardItem = new ArrayList();
                return arOptAwardItem;
            }
            set { arOptAwardItem = value; }
        }

        //称号奖励
        private ArrayList awardTitles;
        public ArrayList AwardTitles
        {
            get
            {
                if (awardTitles == null)
                    awardTitles = new ArrayList();
                return awardTitles;
            }
            set { awardTitles = value; }
        }

        //属性奖励
        private ArrayList awardProps;  //奖励_角色属性
        public ArrayList AwardProps
        {
            get
            {
                if (awardProps == null)
                    awardProps = new ArrayList();
                return awardProps;
            }
            set { awardProps = value; }
        }

        public UInt32 awardProp_campID;   //奖励_声望属性对应的阵营ID
        public string awardProp_campName;

        //佣兵阵型奖励
        private ArrayList awardMercen;
        public ArrayList AwardMercen
        {
            get 
            {
                if (awardMercen == null)
                    awardMercen = new ArrayList();
                return awardMercen; 
            }
            set { awardMercen = value; }
        }
    }
}
