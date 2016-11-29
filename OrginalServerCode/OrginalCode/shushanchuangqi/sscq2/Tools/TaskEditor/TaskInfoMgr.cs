using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Windows.Forms;

namespace TaskEditor
{
    struct SNpcTask
    {
        public ArrayList arAcceptTask;
        public ArrayList arFinishTask;
        public Dictionary<UInt16, CNpcTalk> mapTask2Talk;
    }

    class CTaskInfoMgr
    {
        //public Dictionary<UInt16, CTaskInfo> _mapID2TaskInfo = new Dictionary<UInt16, CTaskInfo>();

        static public XmlElement GetDescendElement(XmlElement elem, string name)
        {
            XmlNodeList list = elem.GetElementsByTagName(name);
            if (list.Count == 0)
                return null;
            return (XmlElement)list[0];
        }

        static public IEnumerable<XmlElement> GetDescendElementList(XmlElement elem, string name)
        {
            XmlNodeList list = elem.GetElementsByTagName(name);
            IEnumerable<XmlElement> elemList = list.Cast<XmlElement>();
            return elemList;
        }

        static public XmlElement GetDescendElement(XmlDocument doc, string name)
        {
            XmlNodeList list = doc.GetElementsByTagName(name);
            if (list.Count == 0)
                return null;
            return (XmlElement)list[0];
        }

        public CTaskInfo LoadXMLFile(string file)
        {
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.ConformanceLevel = ConformanceLevel.Fragment;
            settings.IgnoreWhitespace = true;
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(file, settings);
            XmlDocument doc = new XmlDocument();
            doc.Load(reader);
            
            CTaskInfo taskInfo = new CTaskInfo();

            //基本属性
            XmlElement elemProperty = GetDescendElement(doc, "Property");
            string str = elemProperty.GetAttribute("type");
            taskInfo.dwTaskType = UInt32.Parse(str);
            str = elemProperty.GetAttribute("content");
            taskInfo.dwContentType = UInt32.Parse(str);

            XmlElement elemBasic = GetDescendElement(elemProperty, "Basic");
            str = elemBasic.GetAttribute("id");
            UInt16.TryParse(str, out taskInfo.wID);
            taskInfo.strName = elemBasic.GetAttribute("name");
            str = elemBasic.GetAttribute("level");
            Byte.TryParse(str, out taskInfo.byLevel);

            XmlElement elemMark = GetDescendElement(elemProperty, "Mark");
            str = elemMark.GetAttribute("open");
            Byte.TryParse(str, out taskInfo.byOpen);
            str = elemMark.GetAttribute("share");
            Byte.TryParse(str, out taskInfo.byShare);
            str = elemMark.GetAttribute("giveUp");
            Byte.TryParse(str, out taskInfo.byCanGiveUp);
            str = elemMark.GetAttribute("linklevel");
            Byte.TryParse(str, out taskInfo.byAwardLinkLevel);
            str = elemMark.GetAttribute("repeat");
            UInt32.TryParse(str, out taskInfo.dwRepeat);
            str = elemMark.GetAttribute("typeExtent");
            Byte.TryParse(str, out taskInfo.byTaskTypeExtent);
            str = elemMark.GetAttribute("guidetype");
            Byte.TryParse(str, out taskInfo.byGuideType);

            XmlElement elemStar = GetDescendElement(elemProperty, "Star");
            if (elemStar != null)
            {
                str = elemStar.GetAttribute("id");
                UInt32.TryParse(str, out taskInfo.dwStarGroupID);
                str = elemStar.GetAttribute("level");
                UInt32.TryParse(str, out taskInfo.dwTaskStar);
            }

            XmlElement elemTrigger = GetDescendElement(elemProperty, "Trigger");
            if (elemTrigger != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemTrigger, "Target");
                foreach (XmlElement elem in elemList)
                {
                    CIdxNameType idxNameType = new CIdxNameType();
                    str = elem.GetAttribute("id");
                    idxNameType.dwIdx = UInt32.Parse(str);
                    idxNameType.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("type");
                    idxNameType.byType = Byte.Parse(str);
                    taskInfo.ArTriggerTarget.Add(idxNameType);
                }
            }

            XmlElement elemSubmit = GetDescendElement(elemProperty, "Submit");
            if (elemSubmit != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemSubmit, "Target");
                foreach (XmlElement elem in elemList)
                {
                    CIdxNameType idxNameType = new CIdxNameType();
                    str = elem.GetAttribute("id");
                    idxNameType.dwIdx = UInt32.Parse(str);
                    idxNameType.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("type");
                    idxNameType.byType = Byte.Parse(str);
                    taskInfo.ArSubmitTarget.Add(idxNameType);
                }
            }

            //任务描述
            XmlElement elemDialog = GetDescendElement(doc, "Dialog");
            if (elemDialog != null)
            {
                XmlElement elemDesc = GetDescendElement(elemDialog, "Desc");
                if (elemDesc != null)
                    taskInfo.taskTextDesc.ColorText = elemDesc.InnerText;
                XmlElement elemPurpose = GetDescendElement(elemDialog, "Purpose");
                if (elemPurpose != null)
                    taskInfo.taskTextPurpose.ColorText = elemPurpose.InnerText;
                XmlElement elemFail = GetDescendElement(elemDialog, "Fail");
                if (elemFail != null)
                    taskInfo.taskTextFail.ColorText = elemFail.InnerText;
                XmlElement elemFinish = GetDescendElement(elemDialog, "Finish");
                if(elemFinish != null)
                    taskInfo.taskTextFinish.ColorText = elemFinish.InnerText;
            }

            //任务限制
            XmlElement elemLimit = GetDescendElement(doc, "Limit");
            if (elemLimit != null)
            {
                XmlElement elem = GetDescendElement(elemLimit, "Gender");
                if (elem != null)
                {
                    Byte.TryParse(elem.GetAttribute("value"), out taskInfo.limitGender);
                }

                //声望
                elem = GetDescendElement(elemLimit, "Repute");
                if(elem != null)
                {
                    string value = elem.GetAttribute("Min");
                    UInt16.TryParse(value, out taskInfo.limitReputeMin);
                    value = elem.GetAttribute("Max");
                    UInt16.TryParse(value, out taskInfo.limitReputeMax);
                }

                //境界
                elem = GetDescendElement(elemLimit, "JingJie");
                if (elem != null)
                {
                    string value = elem.GetAttribute("Min");
                    UInt16.TryParse(value, out taskInfo.limitJingJieMin);
                    value = elem.GetAttribute("Max");
                    UInt16.TryParse(value, out taskInfo.limitJingJieMax);
                }

                elem = GetDescendElement(elemLimit, "Camp");
                if (elem != null)
                {
                    Byte.TryParse(elem.GetAttribute("value"), out taskInfo.limitCamp);
                }

                elem = GetDescendElement(elemLimit, "Family");
                if (elem != null)
                {
                    Byte.TryParse(elem.GetAttribute("value"), out taskInfo.limitFamily);
                }

                elem = GetDescendElement(elemLimit, "Race");
                if (elem != null)
                {
                    Byte.TryParse(elem.GetAttribute("value"), out taskInfo.limitRace);
                }

                elem = GetDescendElement(elemLimit, "Date");
                if (elem != null)
                {
                    uint timeFrom;
                    uint timeTo;
                    string value = elem.GetAttribute("From");
                    UInt32.TryParse(value, out timeFrom);
                    value = elem.GetAttribute("To");
                    UInt32.TryParse(value, out timeTo);

                    //转换为64bit时间
                    DateTime offset = new DateTime(1970, 1, 1);
                    taskInfo.limitDateFrom = ((long)timeFrom) * 10000000 + offset.Ticks;
                    taskInfo.limitDateTo = ((long)timeTo * 10000000) + offset.Ticks;
                }

                elem = GetDescendElement(elemLimit, "DayTime");
                if(elem != null)
                {
                    string value = elem.GetAttribute("From");
                    UInt16.TryParse(value, out taskInfo.limitDayTimeFrom);
                    value = elem.GetAttribute("To");
                    UInt16.TryParse(value, out taskInfo.limitDayTimeTo);
                }

                elem = GetDescendElement(elemLimit, "PreTask");
                if (elem != null)
                {
                    IEnumerable<XmlElement> elemList = GetDescendElementList(elem, "Item");

                    String value;
                    foreach (XmlElement child in elemList)
                    {
                        CIdxName obj = new CIdxName();

                        value = child.GetAttribute("id");
                        obj.id = UInt32.Parse(value);
                        obj.name = child.GetAttribute("name");

                        taskInfo.PreTasks.Add(obj);
                    }

                    if (taskInfo.PreTasks.Count > 0)
                    {
                        value = elem.GetAttribute("flag");
                        Byte.TryParse(value, out taskInfo.limitPreTaskFlag);
                    }
                }

                elem = GetDescendElement(elemLimit, "Career");
                if (elem != null)
                {
                    IEnumerable<XmlElement> elemList = GetDescendElementList(elem, "Item");

                    String value;
                    foreach (XmlElement child in elemList)
                    {
                        CIdxName obj = new CIdxName();

                        value = child.GetAttribute("id");
                        obj.id = UInt32.Parse(value);
                        obj.name = child.GetAttribute("name");

                        taskInfo.LimitCareers.Add(obj);
                    }
                }

                //属性限制
                elem = GetDescendElement(elemLimit, "Property");
                if (elem != null)
                {
                    IEnumerable<XmlElement> children = GetDescendElementList(elem, "Item");
                    foreach (XmlElement child in children)
                    {
                        CEnumValue obj = new CEnumValue();
                        obj.type = Byte.Parse(child.GetAttribute("type"));
                        obj.value = UInt32.Parse(child.GetAttribute("value"));

                        if (obj.type > (Byte)ETaskLimitPropType.none && obj.type < (Byte)ETaskLimitPropType.end)
                        {
                            taskInfo.LimitProps.Add(obj);

                            if (obj.type == (Byte)ETaskLimitPropType.eRepute)
                            {
                                taskInfo.limitProp_campID = UInt32.Parse(child.GetAttribute("campID"));
                            }
                        }
                    }
                }
            }

            //任务过程
            XmlElement elemProcess = GetDescendElement(doc, "Process");
            XmlElement elemProcessGeneral = GetDescendElement(elemProcess, "General");
            if (elemProcessGeneral != null)
            {
                if (elemProcessGeneral.HasAttribute("time"))
                {
                    taskInfo.dwLimitTime = UInt32.Parse(elemProcessGeneral.GetAttribute("time"));
                }

                IEnumerable<XmlElement> elemList = GetDescendElementList(elemProcessGeneral, "Item");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CIdxNameCount idxNameCount = new CIdxNameCount();
                    idxNameCount.dwIdx = UInt32.Parse(str);
                    idxNameCount.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("count");
                    idxNameCount.wCount = UInt16.Parse(str);
                    taskInfo.ArGiveItem.Add(idxNameCount);
                }
            }

            XmlElement elemKill = GetDescendElement(elemProcess, "Kill");
            if (elemKill != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemKill, "Monster");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CIdxNameCountEx idxNameCount = new CIdxNameCountEx();
                    idxNameCount.dwIdx = UInt32.Parse(str);
                    idxNameCount.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("count");
                    idxNameCount.wCount = UInt16.Parse(str);
                    str = elem.GetAttribute("fake");
                    UInt32.TryParse(str, out idxNameCount.dwFakeIdx);
                    idxNameCount.strParam = elem.GetAttribute("strParam");
                    taskInfo.ArKillMonster.Add(idxNameCount);
                }
            }

            XmlElement elemCollect = GetDescendElement(elemProcess, "Collect");
            if (elemCollect != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemCollect, "Item");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CIdxNameCount idxNameCount = new CIdxNameCount();
                    idxNameCount.dwIdx = UInt32.Parse(str);
                    idxNameCount.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("count");
                    idxNameCount.wCount = UInt16.Parse(str);
                    taskInfo.ArCollectItem.Add(idxNameCount);
                }
            }

            XmlElement elemKillCollect = GetDescendElement(elemProcess, "KillCollect");
            if (elemKillCollect != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemKillCollect, "Item");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("monsterid");
                    CIdxKillItemCount idxKillCount = new CIdxKillItemCount();
                    idxKillCount.dwIdx1 = UInt32.Parse(str);
                    idxKillCount.dwIdx2 = UInt32.Parse(elem.GetAttribute("itemid"));
                    str = elem.GetAttribute("count");
                    idxKillCount.wCount = UInt16.Parse(str);
                    idxKillCount.strName1 = elem.GetAttribute("monstername");
                    idxKillCount.strName2 = elem.GetAttribute("itemname");
                    idxKillCount.strParam = elem.GetAttribute("strParam");
                    taskInfo.ArKillCollectItem.Add(idxKillCount);
                }
            }

            XmlElement elemProbe = GetDescendElement(elemProcess, "Probe");
            if (elemProbe != null)
            {
                str = elemProbe.GetAttribute("flag");
                Byte.TryParse(str, out taskInfo.ProbeFlag);
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemProbe, "Map");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CMapArea mapArea = new CMapArea();
                    mapArea.dwMapID = UInt32.Parse(str);
                    mapArea.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("x1");
                    mapArea.x = Int32.Parse(str);
                    str = elem.GetAttribute("z1");
                    mapArea.z = Int32.Parse(str);
                    str = elem.GetAttribute("x2");
                    mapArea.x2 = Int32.Parse(str);
                    str = elem.GetAttribute("z2");
                    mapArea.z2 = Int32.Parse(str);
                    mapArea.strParam = elem.GetAttribute("strParam");
                    taskInfo.ArProbe.Add(mapArea);
                }
            }

            XmlElement elemUseItem = GetDescendElement(elemProcess, "UseItem");
            if (elemUseItem != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemUseItem, "Item");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CUseItem useItem = new CUseItem();
                    useItem.dwItemID = UInt32.Parse(str);
                    useItem.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("mapid");
                    UInt32 dwMapID = 0;
                    if (UInt32.TryParse(str, out dwMapID) && dwMapID > 0)
                    {
                        CMapArea mapArea = new CMapArea();
                        mapArea.dwMapID = dwMapID;
                        mapArea.strName = elem.GetAttribute("mapname");
                        str = elem.GetAttribute("x1");
                        mapArea.x = Int32.Parse(str);
                        str = elem.GetAttribute("z1");
                        mapArea.z = Int32.Parse(str);
                        str = elem.GetAttribute("x2");
                        mapArea.x2 = Int32.Parse(str);
                        str = elem.GetAttribute("z2");
                        mapArea.z2 = Int32.Parse(str);
                        mapArea.strParam = elem.GetAttribute("strParam");
                        useItem.mapArea = mapArea;
                    }
                    taskInfo.ArUseItem.Add(useItem);
                }
            }

            XmlElement elemUseSkill = GetDescendElement(elemProcess, "UseSkill");
            if (elemUseSkill != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemUseSkill, "Skill");
                foreach (XmlElement elem in elemList)
                {
                    str = elem.GetAttribute("id");
                    CUseSkill useSkill = new CUseSkill();
                    useSkill.dwSkillID = UInt32.Parse(str);
                    useSkill.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("mapid");
                    UInt32 dwMapID = 0;
                    if (UInt32.TryParse(str, out dwMapID) && dwMapID > 0)
                    {
                        CMapArea mapArea = new CMapArea();
                        mapArea.dwMapID = dwMapID;
                        mapArea.strName = elem.GetAttribute("mapname");
                        str = elem.GetAttribute("x1");
                        mapArea.x = Int32.Parse(str);
                        str = elem.GetAttribute("z1");
                        mapArea.z = Int32.Parse(str);
                        str = elem.GetAttribute("x2");
                        mapArea.x2 = Int32.Parse(str);
                        str = elem.GetAttribute("z2");
                        mapArea.z2 = Int32.Parse(str);
                        mapArea.strParam = elem.GetAttribute("strParam");
                        useSkill.mapArea = mapArea;
                    }
                    taskInfo.ArUseSkill.Add(useSkill);
                }
            }

            XmlElement elemGather = GetDescendElement(elemProcess, "GatherList");
            if (elemGather != null)
            {
                IEnumerable<XmlElement> elemList = GetDescendElementList(elemGather, "Gather");
                foreach (XmlElement elem in elemList)
                {
                    CGatherIdxCount idxCount = new CGatherIdxCount();
                    str = elem.GetAttribute("id");
                    idxCount.dwIdx = UInt32.Parse(str);
                    str = elem.GetAttribute("count");
                    idxCount.wCount = UInt16.Parse(str);
                    idxCount.strParam = elem.GetAttribute("strParam");
                    taskInfo.ArGather.Add(idxCount);
                }
            }

            XmlElement elemTalk = GetDescendElement(elemProcess, "Talk");
            if (elemTalk != null)
            {
                IEnumerable<XmlElement> elemNpcList = GetDescendElementList(elemTalk, "NPC");
                foreach (XmlElement elemNpc in elemNpcList)
                {
                    str = elemNpc.GetAttribute("id");
                    UInt32 dwNpcIdx = UInt32.Parse(str);
                    CNpcTalk npcTalk = new CNpcTalk();
                    npcTalk.strName = elemNpc.GetAttribute("name");
                    IEnumerable<XmlElement> elemChatList = GetDescendElementList(elemNpc, "Chat");
                    foreach (XmlElement elemChat in elemChatList)
                    {
                        CChat chat = new CChat();
                        XmlElement elemPCSpeak = GetDescendElement(elemChat, "PCSpeak");
                        if (elemPCSpeak != null)
                            chat.strPC = elemPCSpeak.InnerText;
                        XmlElement elemNPCSpeak = GetDescendElement(elemChat, "NPCSpeak");
                        if (elemNPCSpeak != null)
                            chat.strNPC = elemNPCSpeak.InnerText;
                        npcTalk.ArChat.Add(chat);
                    }

                    IEnumerable<XmlElement> items = GetDescendElementList(elemNpc, "Item");
                    foreach(XmlElement child in items)
                    {
                        CIdxNameCount obj = new CIdxNameCount();
                        UInt32.TryParse(child.GetAttribute("id"), out obj.dwIdx);
                        obj.strName = child.GetAttribute("name");
                        UInt16.TryParse(child.GetAttribute("value"), out obj.wCount);

                        npcTalk.ArReceiveItem.Add(obj);
                    }
                    taskInfo.MapNpc2Talk.Add(dwNpcIdx, npcTalk);
                }
            }

            //成长
            XmlElement elemGrow = GetDescendElement(doc, "Grow");
            if (elemGrow != null)
            {
                IEnumerable<XmlElement> children = GetDescendElementList(elemGrow, "Item");
                foreach (XmlElement child in children)
                {
                    CEnumValueExt obj = new CEnumValueExt();
                    obj.type = Byte.Parse(child.GetAttribute("type"));
                    obj.value = UInt32.Parse(child.GetAttribute("value"));

                    if (obj.type > (Byte)EProcessRoleProperty.eProcessRoleProperty_none)
                    {
                        if (obj.type == (Byte)EProcessRoleProperty.eProcessRoleProperty_repute)
                        {
                            obj.dwIdx = UInt32.Parse(child.GetAttribute("extID"));
                            obj.name = child.GetAttribute("extName");
                        }
                        taskInfo.RoleProps.Add(obj);
                    }
                }
            }

            //行为
            XmlElement elemBehave = GetDescendElement(doc, "Behave");
            if (elemBehave != null)
            {
                IEnumerable<XmlElement> children = GetDescendElementList(elemBehave, "Item");
                foreach (XmlElement child in children)
                {
                    CEnumValueStr obj = new CEnumValueStr();
                    obj.type = Byte.Parse(child.GetAttribute("type"));
                    obj.value = UInt32.Parse(child.GetAttribute("value"));
                    obj.param = child.GetAttribute("param");

                    if (obj.type > (Byte)EProcessAction.eProcessAction_none)
                    {
                        taskInfo.RoleActions.Add(obj);
                    }
                }
            }

            XmlElement elemBuild = GetDescendElement(doc, "Build");
            if (elemBuild != null)
            {
                IEnumerable<XmlElement> children = GetDescendElementList(elemBuild, "Building");
                foreach(XmlElement child in children)
                {
                    CIdxNameCount obj = new CIdxNameCount();
                    obj.dwIdx = UInt32.Parse(child.GetAttribute("id"));
                    obj.strName = child.GetAttribute("name");
                    obj.wCount = UInt16.Parse(child.GetAttribute("value"));

                    if(obj.dwIdx > 0)
                    {
                        taskInfo.Buildings.Add(obj);
                    }
                }

                children = GetDescendElementList(elemBuild, "Technic");
                foreach(XmlElement child in children)
                {
                    CIdxNameCount obj = new CIdxNameCount();
                    obj.dwIdx = UInt32.Parse(child.GetAttribute("id"));
                    obj.strName = child.GetAttribute("name");
                    obj.wCount = UInt16.Parse(child.GetAttribute("value"));

                    if(obj.dwIdx > 0)
                    {
                        taskInfo.Technics.Add(obj);
                    }
                }
            }

            //任务奖励
            XmlElement elemAward = GetDescendElement(doc, "Award");
            XmlElement elemAwardGeneral = GetDescendElement(elemAward, "General");
            if (elemAwardGeneral != null)
            {
                IEnumerable<XmlElement> elemItemList = GetDescendElementList(elemAwardGeneral, "Item");
                foreach (XmlElement elem in elemItemList)
                {
                    SAwardGeneral award = new SAwardGeneral();
                    award.type = (EAwardGeneral)UInt32.Parse(elem.GetAttribute("type"));
                    award.value = UInt32.Parse(elem.GetAttribute("value"));
                    taskInfo.AwardGeneral.Add(award);
                }
            }

            XmlElement elemAwardMercen = GetDescendElement(elemAward, "Mercen");
            if (elemAwardMercen != null)
            {
                IEnumerable<XmlElement> elemItemList = GetDescendElementList(elemAwardMercen, "Item");
                foreach (XmlElement elem in elemItemList)
                {
                    CIdxMercenPos award = new CIdxMercenPos();
                    award.wIdx = UInt16.Parse(elem.GetAttribute("monster"));
                    award.wNameIDx = UInt16.Parse(elem.GetAttribute("name"));
                    award.wPos = UInt16.Parse(elem.GetAttribute("pos"));
                    taskInfo.AwardMercen.Add(award);
                }
            }

            XmlElement elemCoef = GetDescendElement(elemAward, "Coef");
            if (elemCoef != null)
            {
                str = elemCoef.GetAttribute("star");
                float.TryParse(str, out taskInfo.fStarCoef);
                str = elemCoef.GetAttribute("ring");
                float.TryParse(str, out taskInfo.fRingCoef);
            }

            XmlElement elemMustItem = GetDescendElement(elemAward, "MustItem");
            if (elemMustItem != null)
            {
                IEnumerable<XmlElement> elemItemList = GetDescendElementList(elemMustItem, "Item");
                foreach (XmlElement elem in elemItemList)
                {
                    CIdxNameCountJob idxNameCount = new CIdxNameCountJob();
                    str = elem.GetAttribute("id");
                    idxNameCount.dwIdx = UInt32.Parse(str);
                    idxNameCount.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("count");
                    idxNameCount.wCount = UInt16.Parse(str);
                    if (elem.HasAttribute("jobname"))
                    {
                        idxNameCount.strJobName = elem.GetAttribute("jobname");
                        str = elem.GetAttribute("job");
                        idxNameCount.wJob = UInt16.Parse(str);
                    }
                    else
                    {
                        idxNameCount.wJob = 0;
                    }
                    taskInfo.ArMustAwardItem.Add(idxNameCount);
                }
            }

            XmlElement elemOptItem = GetDescendElement(elemAward, "OptItem");
            if (elemOptItem != null)
            {
                IEnumerable<XmlElement> elemItemList = GetDescendElementList(elemOptItem, "Item");
                foreach (XmlElement elem in elemItemList)
                {
                    CIdxNameCountJob idxNameCount = new CIdxNameCountJob();
                    str = elem.GetAttribute("id");
                    idxNameCount.dwIdx = UInt32.Parse(str);
                    idxNameCount.strName = elem.GetAttribute("name");
                    str = elem.GetAttribute("count");
                    idxNameCount.wCount = UInt16.Parse(str);
                    if (elem.HasAttribute("jobname"))
                    {
                        idxNameCount.strJobName = elem.GetAttribute("jobname");
                        str = elem.GetAttribute("job");
                        idxNameCount.wJob = UInt16.Parse(str);
                    }
                    else
                    {
                        idxNameCount.wJob = 0;
                    }
                    taskInfo.ArOptAwardItem.Add(idxNameCount);
                }
            }

            //称号奖励
            XmlElement elemTitle = GetDescendElement(elemAward, "Title");
            if (elemTitle != null)
            {
                IEnumerable<XmlElement> children = GetDescendElementList(elemTitle, "Item");
                foreach (XmlElement child in children)
                {
                    CIdxName obj = new CIdxName();
                    obj.id = UInt32.Parse(child.GetAttribute("id"));
                    obj.name = child.GetAttribute("name");

                    taskInfo.AwardTitles.Add(obj);
                }
            }

            //属性奖励
            XmlElement elemProp = GetDescendElement(elemAward, "Property");
            if (elemProp != null)
            {
                IEnumerable<XmlElement> children = GetDescendElementList(elemProp, "Item");
                foreach (XmlElement child in children)
                {
                    CEnumValue obj = new CEnumValue();
                    obj.type = Byte.Parse(child.GetAttribute("type"));
                    obj.value = UInt32.Parse(child.GetAttribute("value"));

                    if(obj.type < (Byte)EAwardProperty.end)
                    {
                        taskInfo.AwardProps.Add(obj);

                        if (obj.type == (Byte)EAwardProperty.repute)
                        {
                            taskInfo.awardProp_campID = UInt32.Parse(child.GetAttribute("campID"));
                            taskInfo.awardProp_campName = child.GetAttribute("campName");
                        }
                    }
                }
            }
            return taskInfo;
        }

        public void SaveXMLFile(CTaskInfo taskInfo, string filePath)
        {
            XmlDocument doc = new XmlDocument();
            XmlElement elemTask = doc.CreateElement("Task");
            doc.AppendChild(elemTask);

            //基本属性
            XmlElement elemProperty = doc.CreateElement("Property");
            elemTask.AppendChild(elemProperty);
            elemProperty.SetAttribute("type", taskInfo.dwTaskType.ToString());
            elemProperty.SetAttribute("content", taskInfo.dwContentType.ToString());

            XmlElement elemBasic = doc.CreateElement("Basic");
            elemProperty.AppendChild(elemBasic);
            elemBasic.SetAttribute("id", taskInfo.wID.ToString());
            elemBasic.SetAttribute("name", taskInfo.strName);
            elemBasic.SetAttribute("level", taskInfo.byLevel.ToString());

            XmlElement elemMark = doc.CreateElement("Mark");
            elemProperty.AppendChild(elemMark);
            elemMark.SetAttribute("open", taskInfo.byOpen.ToString());
            elemMark.SetAttribute("share", taskInfo.byShare.ToString());
            elemMark.SetAttribute("giveUp", taskInfo.byCanGiveUp.ToString());
            elemMark.SetAttribute("linklevel", taskInfo.byAwardLinkLevel.ToString());
            elemMark.SetAttribute("repeat", taskInfo.dwRepeat.ToString());
            elemMark.SetAttribute("typeExtent", taskInfo.byTaskTypeExtent.ToString());
            if (1 == taskInfo.byGuideType || 2 == taskInfo.byGuideType)
            {
                elemMark.SetAttribute("guidetype", taskInfo.byGuideType.ToString());
            }
           
            if (taskInfo.dwTaskStar > 0)
            {
                XmlElement elemStar = doc.CreateElement("Star");
                elemProperty.AppendChild(elemStar);
                elemStar.SetAttribute("id", taskInfo.dwStarGroupID.ToString());
                elemStar.SetAttribute("level", taskInfo.dwTaskStar.ToString());
            }

            if (taskInfo.ArTriggerTarget.Count > 0)
            {
                XmlElement elemTrigger = doc.CreateElement("Trigger");
                elemProperty.AppendChild(elemTrigger);
                CIdxNameType[] arTriggerTarget = (CIdxNameType[])taskInfo.ArTriggerTarget.ToArray(typeof(CIdxNameType));
                foreach (CIdxNameType idxNameType in arTriggerTarget)
                {
                    XmlElement elemTarget = doc.CreateElement("Target");
                    elemTrigger.AppendChild(elemTarget);
                    elemTarget.SetAttribute("id", idxNameType.dwIdx.ToString());
                    elemTarget.SetAttribute("name", idxNameType.strName.ToString());
                    elemTarget.SetAttribute("type", idxNameType.byType.ToString());
                }
            }

            if (taskInfo.ArSubmitTarget.Count > 0)
            {
                XmlElement elemSubmit = doc.CreateElement("Submit");
                elemProperty.AppendChild(elemSubmit);
                CIdxNameType[] arSubmitTarget = (CIdxNameType[])taskInfo.ArSubmitTarget.ToArray(typeof(CIdxNameType));
                foreach (CIdxNameType idxNameType in arSubmitTarget)
                {
                    XmlElement elemTarget = doc.CreateElement("Target");
                    elemSubmit.AppendChild(elemTarget);
                    elemTarget.SetAttribute("id", idxNameType.dwIdx.ToString());
                    elemTarget.SetAttribute("name", idxNameType.strName.ToString());
                    elemTarget.SetAttribute("type", idxNameType.byType.ToString());
                }
            }

            //任务描述
            XmlElement elemDialog = doc.CreateElement("Dialog");
            elemTask.AppendChild(elemDialog);

            if (taskInfo.taskTextDesc.strText.Length > 0)
            {
                XmlElement elemDesc = doc.CreateElement("Desc");
                elemDialog.AppendChild(elemDesc);
                elemDesc.InnerText = taskInfo.taskTextDesc.ColorText;
            }

            if (taskInfo.taskTextPurpose.strText.Length > 0)
            {
                XmlElement elemPurpose = doc.CreateElement("Purpose");
                elemDialog.AppendChild(elemPurpose);
                elemPurpose.InnerText = taskInfo.taskTextPurpose.ColorText;
            }

            if (taskInfo.taskTextFail.strText.Length > 0)
            {
                XmlElement elemFail = doc.CreateElement("Fail");
                elemDialog.AppendChild(elemFail);
                elemFail.InnerText = taskInfo.taskTextFail.ColorText;
            }

            if (taskInfo.taskTextFinish.strText.Length > 0)
            {
                XmlElement elemFinish = doc.CreateElement("Finish");
                elemDialog.AppendChild(elemFinish);
                elemFinish.InnerText = taskInfo.taskTextFinish.ColorText;
            }

            //任务限制
            XmlElement elemLimit = doc.CreateElement("Limit");
            elemTask.AppendChild(elemLimit);
            if (taskInfo.limitGender > (Byte)ELimitGender.eLimitGender_none)
            {
                XmlElement elem = doc.CreateElement("Gender");
                elem.SetAttribute("value", taskInfo.limitGender.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitReputeMin > 0 || taskInfo.limitReputeMax > 0)
            {
                XmlElement elem = doc.CreateElement("Repute");
                elem.SetAttribute("Min", taskInfo.limitReputeMin.ToString());
                elem.SetAttribute("Max", taskInfo.limitReputeMax.ToString());
                elemLimit.AppendChild(elem);
            }

            //境界
            if (taskInfo.limitJingJieMin > 0 || taskInfo.limitJingJieMax > 0)
            {
                XmlElement elem = doc.CreateElement("JingJie");
                elem.SetAttribute("Min", taskInfo.limitJingJieMin.ToString());
                elem.SetAttribute("Max", taskInfo.limitJingJieMax.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitCamp > (Byte)ELimitCamp.eLimitCamp_none)
            {
                XmlElement elem = doc.CreateElement("Camp");
                elem.SetAttribute("value", taskInfo.limitCamp.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitFamily > (Byte)ELimitFamily.eLimitFamily_none)
            {
                XmlElement elem = doc.CreateElement("Family");
                elem.SetAttribute("value", taskInfo.limitFamily.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitRace > 0)
            {
                XmlElement elem = doc.CreateElement("Race");
                elem.SetAttribute("value", taskInfo.limitRace.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitDateFrom > 0 && taskInfo.limitDateTo > 0)
            {
                //保存32bit的时间
                DateTime offset = new DateTime(1970, 1, 1);
                TimeSpan timeFrom = (new DateTime(taskInfo.limitDateFrom)) - offset;
                TimeSpan timeTo = (new DateTime(taskInfo.limitDateTo)) - offset;
                XmlElement elem = doc.CreateElement("Date");
                elem.SetAttribute("From", timeFrom.TotalSeconds.ToString());
                elem.SetAttribute("To", timeTo.TotalSeconds.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.limitDayTimeFrom > 0 && taskInfo.limitDayTimeTo > 0)
            {
                XmlElement elem = doc.CreateElement("DayTime");
                elem.SetAttribute("From", taskInfo.limitDayTimeFrom.ToString());
                elem.SetAttribute("To", taskInfo.limitDayTimeTo.ToString());
                elemLimit.AppendChild(elem);
            }

            if (taskInfo.PreTasks.Count > 0)
            {
                XmlElement elem = doc.CreateElement("PreTask");
                elem.SetAttribute("flag", taskInfo.limitPreTaskFlag.ToString());

                foreach (CIdxName obj in taskInfo.PreTasks)
                {
                    XmlElement child = doc.CreateElement("Item");
                    child.SetAttribute("id", obj.id.ToString());
                    child.SetAttribute("name", obj.name);

                    elem.AppendChild(child);
                }

                elemLimit.AppendChild(elem);
            }

            if (taskInfo.LimitCareers.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Career");

                foreach (CIdxName obj in taskInfo.LimitCareers)
                {
                    XmlElement child = doc.CreateElement("Item");
                    child.SetAttribute("id", obj.id.ToString());
                    child.SetAttribute("name", obj.name);

                    elem.AppendChild(child);
                }

                elemLimit.AppendChild(elem);
            }

            //属性限制
            if (taskInfo.LimitProps.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Property");
                elemLimit.AppendChild(elem);

                foreach (CEnumValue obj in taskInfo.LimitProps)
                {
                    XmlElement child = doc.CreateElement("Item");
                    elem.AppendChild(child);

                    child.SetAttribute("type", obj.type.ToString());
                    child.SetAttribute("value", obj.value.ToString());

                    if (obj.type == (Byte)ETaskLimitPropType.eRepute)
                    {
                        child.SetAttribute("campID", taskInfo.limitProp_campID.ToString());
                    }
                }
            }


            //任务过程
            XmlElement elemProcess = doc.CreateElement("Process");
            elemTask.AppendChild(elemProcess);

            //综合设定
            XmlElement elemProcessGeneral = doc.CreateElement("General");
            elemProcess.AppendChild(elemProcessGeneral);
            if (taskInfo.dwLimitTime > 0)
                elemProcessGeneral.SetAttribute("time", taskInfo.dwLimitTime.ToString());

            if (taskInfo.ArGiveItem.Count > 0)
            {
                CIdxNameCount[] arItem = (CIdxNameCount[])taskInfo.ArGiveItem.ToArray(typeof(CIdxNameCount));
                foreach (CIdxNameCount idxNameCount in arItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemProcessGeneral.AppendChild(elemItem);
                    elemItem.SetAttribute("id", idxNameCount.dwIdx.ToString());
                    elemItem.SetAttribute("name", idxNameCount.strName.ToString());
                    elemItem.SetAttribute("count", idxNameCount.wCount.ToString());
                }
            }

            //猎杀
            if (taskInfo.ArKillMonster.Count > 0)
            {
                XmlElement elemKill = doc.CreateElement("Kill");
                elemProcess.AppendChild(elemKill);

                CIdxNameCountEx[] arMonster = (CIdxNameCountEx[])taskInfo.ArKillMonster.ToArray(typeof(CIdxNameCountEx));
                foreach (CIdxNameCountEx idxNameCount in arMonster)
                {
                    XmlElement elemMonster = doc.CreateElement("Monster");
                    elemKill.AppendChild(elemMonster);
                    elemMonster.SetAttribute("id", idxNameCount.dwIdx.ToString());
                    elemMonster.SetAttribute("name", idxNameCount.strName.ToString());
                    elemMonster.SetAttribute("count", idxNameCount.wCount.ToString());
                    elemMonster.SetAttribute("fake", idxNameCount.dwFakeIdx.ToString());
                    elemMonster.SetAttribute("strParam", idxNameCount.strParam.ToString());
                }
            }

            //收集
            if (taskInfo.ArCollectItem.Count > 0)
            {
                XmlElement elemCollect = doc.CreateElement("Collect");
                elemProcess.AppendChild(elemCollect);

                CIdxNameCount[] arCollectItem = (CIdxNameCount[])taskInfo.ArCollectItem.ToArray(typeof(CIdxNameCount));
                foreach (CIdxNameCount idxNameCount in arCollectItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemCollect.AppendChild(elemItem);
                    elemItem.SetAttribute("id", idxNameCount.dwIdx.ToString());
                    elemItem.SetAttribute("name", idxNameCount.strName.ToString());
                    elemItem.SetAttribute("count", idxNameCount.wCount.ToString());
                }
            }

            //击杀收集
            if (taskInfo.ArKillCollectItem.Count > 0)
            {
                XmlElement elemCollect = doc.CreateElement("KillCollect");
                elemProcess.AppendChild(elemCollect);

                CIdxKillItemCount[] arKillCollectItem = (CIdxKillItemCount[])taskInfo.ArKillCollectItem.ToArray(typeof(CIdxKillItemCount));
                foreach (CIdxKillItemCount idxNameCount in arKillCollectItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemCollect.AppendChild(elemItem);
                    elemItem.SetAttribute("monsterid", idxNameCount.dwIdx1.ToString());
                    elemItem.SetAttribute("itemid", idxNameCount.dwIdx2.ToString());
                    elemItem.SetAttribute("count", idxNameCount.wCount.ToString());
                    elemItem.SetAttribute("monstername", idxNameCount.strName1);
                    elemItem.SetAttribute("itemname", idxNameCount.strName2);
                    elemItem.SetAttribute("strParam", idxNameCount.strParam);
                }
            }

            //探索
            if (taskInfo.ArProbe.Count > 0)
            {
                XmlElement elemProbe = doc.CreateElement("Probe");
                elemProcess.AppendChild(elemProbe);
                elemProbe.SetAttribute("flag", taskInfo.ProbeFlag.ToString());

                CMapArea[] arMapArea = (CMapArea[])taskInfo.ArProbe.ToArray(typeof(CMapArea));
                foreach (CMapArea mapArea in arMapArea)
                {
                    XmlElement elemMap = doc.CreateElement("Map");
                    elemProbe.AppendChild(elemMap);
                    elemMap.SetAttribute("id", mapArea.dwMapID.ToString());
                    elemMap.SetAttribute("name", mapArea.strName);
                    elemMap.SetAttribute("x1", mapArea.x.ToString());
                    elemMap.SetAttribute("z1", mapArea.z.ToString());
                    elemMap.SetAttribute("x2", mapArea.x2.ToString());
                    elemMap.SetAttribute("z2", mapArea.z2.ToString());
                    elemMap.SetAttribute("strParam", mapArea.strParam);
                }
            }

            if (taskInfo.ArUseItem.Count > 0)
            {
                XmlElement elemUseItem = doc.CreateElement("UseItem");
                elemProcess.AppendChild(elemUseItem);

                CUseItem[] arUseItem = (CUseItem[])taskInfo.ArUseItem.ToArray(typeof(CUseItem));
                foreach (CUseItem useItem in arUseItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemUseItem.AppendChild(elemItem);
                    elemItem.SetAttribute("id", useItem.dwItemID.ToString());
                    elemItem.SetAttribute("name", useItem.strName);
                    if (useItem.mapArea != null)
                    {
                        elemItem.SetAttribute("mapid", useItem.mapArea.dwMapID.ToString());
                        elemItem.SetAttribute("mapname", useItem.mapArea.strName);
                        elemItem.SetAttribute("x1", useItem.mapArea.x.ToString());
                        elemItem.SetAttribute("z1", useItem.mapArea.z.ToString());
                        elemItem.SetAttribute("x2", useItem.mapArea.x2.ToString());
                        elemItem.SetAttribute("z2", useItem.mapArea.z2.ToString());
                    }
                }
            }

            if (taskInfo.ArUseSkill.Count > 0)
            {
                XmlElement elemUseSkill = doc.CreateElement("UseSkill");
                elemProcess.AppendChild(elemUseSkill);

                CUseSkill[] arUseSkill = (CUseSkill[])taskInfo.ArUseSkill.ToArray(typeof(CUseSkill));
                foreach (CUseSkill useSkill in arUseSkill)
                {
                    XmlElement elemSkill = doc.CreateElement("Skill");
                    elemUseSkill.AppendChild(elemSkill);
                    elemSkill.SetAttribute("id", useSkill.dwSkillID.ToString());
                    elemSkill.SetAttribute("name", useSkill.strName);
                    if (useSkill.mapArea != null)
                    {
                        elemSkill.SetAttribute("mapid", useSkill.mapArea.dwMapID.ToString());
                        elemSkill.SetAttribute("mapname", useSkill.mapArea.strName);
                        elemSkill.SetAttribute("x1", useSkill.mapArea.x.ToString());
                        elemSkill.SetAttribute("z1", useSkill.mapArea.z.ToString());
                        elemSkill.SetAttribute("x2", useSkill.mapArea.x2.ToString());
                        elemSkill.SetAttribute("z2", useSkill.mapArea.z2.ToString());
                    }
                }
            }

            //采集
            if (taskInfo.ArGather.Count > 0)
            {
                XmlElement elemGatherList = doc.CreateElement("GatherList");
                elemProcess.AppendChild(elemGatherList);

                CGatherIdxCount[] arIdxCount = (CGatherIdxCount[])taskInfo.ArGather.ToArray(typeof(CGatherIdxCount));
                foreach (CGatherIdxCount idxCount in arIdxCount)
                {
                    XmlElement elemGather = doc.CreateElement("Gather");
                    elemGatherList.AppendChild(elemGather);
                    elemGather.SetAttribute("id", idxCount.dwIdx.ToString());
                    elemGather.SetAttribute("count", idxCount.wCount.ToString());
                    elemGather.SetAttribute("strParam", idxCount.strParam);
                }
            }

            //对话
            if (taskInfo.MapNpc2Talk.Count > 0)
            {
                XmlElement elemTalk = doc.CreateElement("Talk");
                elemProcess.AppendChild(elemTalk);

                foreach (KeyValuePair<UInt32, CNpcTalk> kvp in taskInfo.MapNpc2Talk)
                {
                    XmlElement elemNPC = doc.CreateElement("NPC");
                    elemTalk.AppendChild(elemNPC);
                    UInt32 dwNpcIdx = kvp.Key;
                    CNpcTalk npcTalk = kvp.Value;
                    elemNPC.SetAttribute("id", dwNpcIdx.ToString());
                    elemNPC.SetAttribute("name", npcTalk.strName);

                    //对话内容
                    for (int i = 0; i < npcTalk.ArChat.Count; ++i )
                    {
                        CChat chat = (CChat)npcTalk.ArChat[i];
                        XmlElement elemChat = doc.CreateElement("Chat");
                        elemNPC.AppendChild(elemChat);
                        elemChat.SetAttribute("index", (i + 1).ToString());
                        if (chat.strPC.Length > 0)
                        {
                            XmlElement elemPCSpeak = doc.CreateElement("PCSpeak");
                            elemChat.AppendChild(elemPCSpeak);
                            elemPCSpeak.InnerText = chat.strPC;
                        }
                        if (chat.strNPC.Length > 0)
                        {
                            XmlElement elemNPCSpeak = doc.CreateElement("NPCSpeak");
                            elemChat.AppendChild(elemNPCSpeak);
                            elemNPCSpeak.InnerText = chat.strNPC;
                        }
                    }

                    //道具
                    foreach (CIdxNameCount obj in npcTalk.ArReceiveItem)
                    {
                        XmlElement child = doc.CreateElement("Item");
                        child.SetAttribute("id", obj.dwIdx.ToString());
                        child.SetAttribute("name", obj.strName);
                        child.SetAttribute("value", obj.wCount.ToString());

                        elemNPC.AppendChild(child);
                    }
                }
            }

            //成长
            if (taskInfo.RoleProps.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Grow");
                elemProcess.AppendChild(elem);

                foreach (CEnumValueExt obj in taskInfo.RoleProps)
                {
                    XmlElement child = doc.CreateElement("Item");
                    child.SetAttribute("type", obj.type.ToString());
                    child.SetAttribute("value", obj.value.ToString());

                    if (obj.type == (Byte)EProcessRoleProperty.eProcessRoleProperty_repute)
                    {
                        child.SetAttribute("extID", obj.dwIdx.ToString());
                        child.SetAttribute("extName", obj.name);
                    }

                    elem.AppendChild(child);
                }
            }

            //行为
            if (taskInfo.RoleActions.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Behave");
                elemProcess.AppendChild(elem);

                foreach (CEnumValueStr obj in taskInfo.RoleActions)
                {
                    XmlElement child = doc.CreateElement("Item");
                    child.SetAttribute("type", obj.type.ToString());
                    child.SetAttribute("value", obj.value.ToString());
                    child.SetAttribute("param", obj.param.ToString());

                    elem.AppendChild(child);
                }
            }

            //建筑
            if (taskInfo.Buildings.Count > 0 || taskInfo.Technics.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Build");
                elemProcess.AppendChild(elem);

                foreach (CIdxNameCount obj in taskInfo.Buildings)
                {
                    XmlElement child = doc.CreateElement("Building");
                    child.SetAttribute("id", obj.dwIdx.ToString());
                    child.SetAttribute("name", obj.strName);
                    child.SetAttribute("value", obj.wCount.ToString());

                    elem.AppendChild(child);
                }

                foreach (CIdxNameCount obj in taskInfo.Technics)
                {
                    XmlElement child = doc.CreateElement("Technic");
                    child.SetAttribute("id", obj.dwIdx.ToString());
                    child.SetAttribute("name", obj.strName);
                    child.SetAttribute("value", obj.wCount.ToString());

                    elem.AppendChild(child);
                }
            }

            //任务奖励
            XmlElement elemAward = doc.CreateElement("Award");
            elemTask.AppendChild(elemAward);

            XmlElement elemAwardGeneral = doc.CreateElement("General");
            elemAward.AppendChild(elemAwardGeneral);
            foreach (SAwardGeneral obj in taskInfo.AwardGeneral)
            {
                XmlElement child = doc.CreateElement("Item");
                elemAwardGeneral.AppendChild(child);

                child.SetAttribute("type", ((int)obj.type).ToString());
                child.SetAttribute("value", obj.value.ToString());
            }

            XmlElement elemAwardMercen = doc.CreateElement("Mercen");
            if (taskInfo.AwardMercen.Count > 0)
            {
                elemAward.AppendChild(elemAwardMercen);
                foreach (CIdxMercenPos obj in taskInfo.AwardMercen)
                {
                    XmlElement child = doc.CreateElement("Item");
                    elemAwardMercen.AppendChild(child);

                    child.SetAttribute("monster", ((int)obj.wIdx).ToString());
                    child.SetAttribute("name", obj.wNameIDx.ToString());
                    child.SetAttribute("pos", obj.wPos.ToString());
                }
            }           

            if (taskInfo.dwTaskStar > 0)
            {
                XmlElement elemCoef = doc.CreateElement("Coef");
                elemAward.AppendChild(elemCoef);
                if (taskInfo.fStarCoef > float.Epsilon)
                    elemCoef.SetAttribute("star", taskInfo.fStarCoef.ToString());
                if (taskInfo.fRingCoef > float.Epsilon)
                    elemCoef.SetAttribute("ring", taskInfo.fRingCoef.ToString());
            }

            if (taskInfo.ArMustAwardItem.Count > 0)
            {
                XmlElement elemMustItem = doc.CreateElement("MustItem");
                elemAward.AppendChild(elemMustItem);

                CIdxNameCountJob[] arMustItem = (CIdxNameCountJob[])taskInfo.ArMustAwardItem.ToArray(typeof(CIdxNameCountJob));
                foreach (CIdxNameCountJob idxNameCount in arMustItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemMustItem.AppendChild(elemItem);
                    elemItem.SetAttribute("id", idxNameCount.dwIdx.ToString());
                    elemItem.SetAttribute("name", idxNameCount.strName.ToString());
                    elemItem.SetAttribute("count", idxNameCount.wCount.ToString());
                    elemItem.SetAttribute("jobname", idxNameCount.strJobName.ToString());
                    elemItem.SetAttribute("job", idxNameCount.wJob.ToString());
                }
            }

            if (taskInfo.ArOptAwardItem.Count > 0)
            {
                XmlElement elemOptItem = doc.CreateElement("OptItem");
                elemAward.AppendChild(elemOptItem);

                CIdxNameCountJob[] arOptItem = (CIdxNameCountJob[])taskInfo.ArOptAwardItem.ToArray(typeof(CIdxNameCountJob));
                foreach (CIdxNameCountJob idxNameCount in arOptItem)
                {
                    XmlElement elemItem = doc.CreateElement("Item");
                    elemOptItem.AppendChild(elemItem);
                    elemItem.SetAttribute("id", idxNameCount.dwIdx.ToString());
                    elemItem.SetAttribute("name", idxNameCount.strName.ToString());
                    elemItem.SetAttribute("count", idxNameCount.wCount.ToString());
                    elemItem.SetAttribute("jobname", idxNameCount.strJobName.ToString());
                    elemItem.SetAttribute("job", idxNameCount.wJob.ToString());
                }
            }

            //称号奖励
            if (taskInfo.AwardTitles.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Title");
                elemAward.AppendChild(elem);

                foreach (CIdxName obj in taskInfo.AwardTitles)
                {
                    XmlElement child = doc.CreateElement("Item");
                    elem.AppendChild(child);

                    child.SetAttribute("id", obj.id.ToString());
                    child.SetAttribute("name", obj.name);
                }
            }

            //属性奖励
            if (taskInfo.AwardProps.Count > 0)
            {
                XmlElement elem = doc.CreateElement("Property");
                elemAward.AppendChild(elem);

                foreach (CEnumValue obj in taskInfo.AwardProps)
                {
                    XmlElement child = doc.CreateElement("Item");
                    elem.AppendChild(child);

                    child.SetAttribute("type", obj.type.ToString());
                    child.SetAttribute("value", obj.value.ToString());

                    if (obj.type == (Byte)EAwardProperty.repute)
                    {
                        child.SetAttribute("campID", taskInfo.awardProp_campID.ToString());
                        child.SetAttribute("campName", taskInfo.awardProp_campName);
                    }
                }
            }

            XmlDeclaration xmldecl;
            xmldecl = doc.CreateXmlDeclaration("1.0", null, null);
            xmldecl.Encoding = "UTF-8";

            XmlElement root = doc.DocumentElement;
            doc.InsertBefore(xmldecl, root);
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Encoding = new UTF8Encoding(false);
            settings.Indent = true;
            using (XmlWriter w = XmlWriter.Create(filePath, settings))
            {
                doc.Save(w);
            }
        }
    }
}
