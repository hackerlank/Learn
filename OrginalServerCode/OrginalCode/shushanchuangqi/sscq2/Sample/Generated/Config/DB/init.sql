-- MySQL dump 10.13  Distrib 5.1.54, for unknown-linux-gnu (x86_64)
--
-- Host: 192.168.88.250    Database: GameDB_st
-- ------------------------------------------------------
-- Server version	5.1.54-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tblBattleReport`
--

DROP TABLE IF EXISTS `tblBattleReport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblBattleReport` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `qwBattleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '战报ID',
    `qwAttackID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '对手ID',
    `strAttackID` char(30) NOT NULL COMMENT '对手名字',
    `eActionType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '战斗方式',
    `eType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '战斗原因',
    `eSuc` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '胜利方',
    `dwTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战报时间',
    `dwParam1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '参数1',
    `dwParam2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '参数2',
    `dwParam3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '参数3',
    `dwIndex` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '序号',
    PRIMARY KEY (`qwRoleID`,`qwBattleID`),
    KEY `qwRoleID` (`qwRoleID`),
    KEY `ReportByType` (`qwRoleID`,`eType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家战报';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblbeastdata`
--

DROP TABLE IF EXISTS `tblbeastdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblbeastdata` (
    `qwRoleId` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `wBeastID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '兽魂id',
    PRIMARY KEY (`qwRoleId`,`wBeastID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家兽魂数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblbeastsouldata`
--

DROP TABLE IF EXISTS `tblbeastsouldata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblbeastsouldata` (
    `qwRoleID` bigint(20) NOT NULL COMMENT '玩家ID',
    `byType` tinyint(3) NOT NULL COMMENT '兽魂类型',
    `byRank` tinyint(3) NOT NULL COMMENT '兽魂档次',
    `byLevel` tinyint(3) NOT NULL COMMENT '兽魂等级',
    PRIMARY KEY (`qwRoleID`,`byType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='兽魂信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblbuffdata`
--

DROP TABLE IF EXISTS `tblbuffdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblbuffdata` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '对应玩家ID',
    `qwOwnerID` bigint(20) NOT NULL DEFAULT '0' COMMENT '所属实例ID(Role/Fighter/...)',
    `byBuffType` tinyint(3) NOT NULL DEFAULT '0' COMMENT 'Buff大类',
    `wBuffID` smallint(5) NOT NULL DEFAULT '0' COMMENT 'Buff种类',
    `byBuffState` tinyint(3) NOT NULL DEFAULT '0' COMMENT 'Buff当前状态',
    `dwBuffTime` int(10) NOT NULL DEFAULT '0' COMMENT 'Buff失效时间',
    `strBuffParam` char(128) NOT NULL COMMENT 'Buff效果参数',
    `dwBuffCount` int(10) NOT NULL COMMENT 'Buff次数',
    PRIMARY KEY (`qwOwnerID`,`byBuffType`,`wBuffID`),
    UNIQUE KEY `BUFF_UNIQUE` (`qwOwnerID`,`byBuffType`,`wBuffID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='有关各种BUFF的记录存储';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbldemontower`
--

DROP TABLE IF EXISTS `tbldemontower`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbldemontower` (
    `qwUserID` bigint(16) unsigned NOT NULL DEFAULT '0' COMMENT '玩家UserID',
    `qwRoleID` bigint(16) unsigned NOT NULL DEFAULT '0' COMMENT '玩家RoleID',
    `strRoleName` char(255) NOT NULL DEFAULT '' COMMENT '角色名',
    `bySex` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '性别',
    `byLevel` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
    `dwFloorID` int(10) unsigned NOT NULL DEFAULT '1' COMMENT '当前所在塔层',
    `dwGuardFloorID` int(10) unsigned NOT NULL DEFAULT '1' COMMENT '镇守塔层',
    `dwGuardPos` int(10) unsigned NOT NULL DEFAULT '1' COMMENT '镇守位置',
    `dwGuardStartTime` int(10) unsigned NOT NULL DEFAULT '1' COMMENT '镇守开始时间',
    `dwGuardNextAttackTime` int(10) unsigned NOT NULL DEFAULT '1' COMMENT '镇守可以攻击的时间',
    `sFailSoulPrize` char(255) NOT NULL DEFAULT '' COMMENT '失败后的魄奖励',
    `sDaySoulPrize` char(255) NOT NULL DEFAULT '' COMMENT '7点结算的魄奖励',
    `sGatherSoulPrize` char(255) NOT NULL DEFAULT '' COMMENT '聚魂奖励',
    `dwGuardGatherSpeed` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '聚魂加速',
    `dwGuardGatherSpeedEndTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '聚魂加速结束时间',
    `dwGuardReduceRate` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '元神减弱比例',
    `dwGuardEndTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '镇守结束时间',
    `dwGuardNextPrizeTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '下次奖励时间',
    `dwGuardNextReduceRateTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '下次减弱元神时间',
    `dwPower` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战斗力',
    `byColor` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '颜色',
    PRIMARY KEY (`qwUserID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='锁妖塔相关信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbldemontowerfighter`
--

DROP TABLE IF EXISTS `tbldemontowerfighter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbldemontowerfighter` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `dwFloorID` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '层数',
    `dwMinTurns` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '是否领奖',
    `wTakePrize` smallint(11) unsigned NOT NULL DEFAULT '0' COMMENT '是否获取奖励',
    PRIMARY KEY (`qwRoleID`,`dwFloorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='镇妖塔挑战表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbldiscount`
--

DROP TABLE IF EXISTS `tbldiscount`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbldiscount` (
    `byPos` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '限购位置(0,1,2表示)',
    `qwMarkID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '栏位版本ID',
    `strDisItem` char(255) NOT NULL DEFAULT '' COMMENT '限购道具ID及其价格',
    `byLimitType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '类型限制(0无条件、1充值限购、2消费限购)',
    `dwLimitValue` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '达到的仙石数量限制(0无条件、1充值限购、2消费限购)',
    `wLimitCount` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '购买道具个数限制',
    `dwBeginTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '限购开始时间',
    `dwEndTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '限购结束时间',
    PRIMARY KEY (`byPos`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='商城折扣物品信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblfightercombination`
--

DROP TABLE IF EXISTS `tblfightercombination`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblfightercombination` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `byGroupID` tinyint(3) NOT NULL COMMENT '散仙组合ID',
    `byGroupLvl` tinyint(3) NOT NULL COMMENT '散仙组合等级',
    `dwGroupExp` int(10) unsigned NOT NULL COMMENT '散仙组合当前经验值',
    `byInLineUp` tinyint(3) NOT NULL COMMENT '是否上线',
    `byInEMei` tinyint(3) NOT NULL COMMENT '是否峨眉',
    PRIMARY KEY (`qwRoleID`,`byGroupID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家的散仙组合信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblfighterxinfa`
--

DROP TABLE IF EXISTS `tblfighterxinfa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblfighterxinfa` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色唯一ID',
    `qwOwnerID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属散仙ID',
    `dwXinFaID` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '心法ID',
    `byXinFaLvl` int(11) unsigned NOT NULL DEFAULT '1' COMMENT '心法等级',
    `iSlot` int(11) NOT NULL DEFAULT '-1' COMMENT '装备位置',
    PRIMARY KEY (`qwRoleID`,`qwOwnerID`,`dwXinFaID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='散仙心法相关信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblformation`
--

DROP TABLE IF EXISTS `tblformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblformation` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `wFormationID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '阵形ID',
    `bySelected` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否启用',
    PRIMARY KEY (`qwRoleID`,`wFormationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='阵形信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblgamevars`
--

DROP TABLE IF EXISTS `tblgamevars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblgamevars` (
    `byServerType` tinyint(3) unsigned NOT NULL DEFAULT '0',
    `wVar` smallint(5) unsigned NOT NULL DEFAULT '0',
    `qwValue` bigint(20) unsigned NOT NULL DEFAULT '0',
    `dwExpired` int(11) unsigned NOT NULL DEFAULT '0',
    `wGroup` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '服务器组',
    PRIMARY KEY (`wGroup`,`wVar`),
    KEY `RoleVar` (`wVar`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='游戏全局变量';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildapplydata`
--

DROP TABLE IF EXISTS `tblguildapplydata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildapplydata` (
    `qwRoleID` bigint(20) NOT NULL COMMENT '玩家ID',
    `qwGuildID` bigint(20) NOT NULL COMMENT '帮派ID',
    `strName` char(20) DEFAULT NULL COMMENT '玩家姓名',
    `wLevel` smallint(6) DEFAULT NULL COMMENT '玩家等级',
    `dwBattlePoint` int(10) DEFAULT NULL COMMENT '战斗力',
    PRIMARY KEY (`qwRoleID`,`qwGuildID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派申请列表信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildauthority`
--

DROP TABLE IF EXISTS `tblguildauthority`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildauthority` (
    `qwGuildID` bigint(20) NOT NULL COMMENT '帮派ID',
    `byMemberRank` tinyint(3) NOT NULL COMMENT '帮派职位',
    `dwAuthority` int(10) DEFAULT NULL COMMENT '对应权限',
    PRIMARY KEY (`qwGuildID`,`byMemberRank`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派权限设置';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildbattle`
--

DROP TABLE IF EXISTS `tblguildbattle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildbattle` (
    `qwGuildID` bigint(20) NOT NULL COMMENT '帮派ID',
    `dwScore` int(10) NOT NULL COMMENT '帮派战分数',
    `dwUpdateTime` int(10) NOT NULL COMMENT '帮派战分数更新时间',
    PRIMARY KEY (`qwGuildID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派战信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildbuilding`
--

DROP TABLE IF EXISTS `tblguildbuilding`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildbuilding` (
    `qwGuildID` bigint(20) NOT NULL COMMENT '帮派ID',
    `byType` tinyint(3) NOT NULL DEFAULT '0' COMMENT '建筑类型',
    `wLevel` smallint(5) DEFAULT NULL COMMENT '建筑等级',
    PRIMARY KEY (`qwGuildID`,`byType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派建筑';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguilddata`
--

DROP TABLE IF EXISTS `tblguilddata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguilddata` (
    `qwGuildID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮派唯一ID',
    `strName` char(30) NOT NULL COMMENT '帮派名称',
    `strInfo` char(120) DEFAULT NULL COMMENT '帮派公告',
    `byLevel` tinyint(3) NOT NULL DEFAULT '0' COMMENT '帮派等级',
    `qwOwnerID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮主ID',
    `qwQQGroupID` bigint(20) DEFAULT NULL COMMENT '帮派qq群号',
    `dwMoney` int(11) DEFAULT NULL COMMENT '帮派资金',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `byQuality` tinyint(3) unsigned NOT NULL COMMENT '主将品质',
    `dwScore` int(11) DEFAULT '0' COMMENT '天元神兽积分',
    `dwCount` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换所有类型物品的数量总和',
    `strLingShan` char(30) DEFAULT NULL COMMENT '占领灵山',
    PRIMARY KEY (`qwGuildID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildexchangeditem`
--

DROP TABLE IF EXISTS `tblguildexchangeditem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildexchangeditem` (
    `qwGuildID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮派ID',
    `dwExchangeID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换id',
    `dwCount` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换数量',
    PRIMARY KEY (`qwGuildID`,`dwExchangeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='兑换物品';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildlistinfo`
--

DROP TABLE IF EXISTS `tblguildlistinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildlistinfo` (
    `qwGuildID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮派唯一ID',
    `strName` char(30) NOT NULL COMMENT '帮派名称',
    `strInfo` char(120) DEFAULT NULL COMMENT '帮派公告',
    `qwOwnerID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮主ID',
    `strOwnerName` char(30) NOT NULL COMMENT '帮主名称',
    `byLevel` tinyint(3) NOT NULL DEFAULT '0' COMMENT '帮派等级',
    `wUserCount` smallint(5) NOT NULL DEFAULT '0' COMMENT '成员数量',
    `wMaxUserCount` smallint(5) NOT NULL DEFAULT '0' COMMENT '最大成员数量',
    PRIMARY KEY (`qwGuildID`),
    UNIQUE KEY `strName_UNIQUE` (`strName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派列表信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildlog`
--

DROP TABLE IF EXISTS `tblguildlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildlog` (
    `qwInstID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '唯一自增长流水ID',
    `qwGuildID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '帮派唯一ID',
    `wMsgID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '日志类型ID',
    `vecString` char(64) NOT NULL DEFAULT '' COMMENT '变量字符',
    `vecParam` char(64) NOT NULL DEFAULT '' COMMENT '变量数值（XX,XX,XX）',
    `dwTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '日志时间',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB AUTO_INCREMENT=380 DEFAULT CHARSET=utf8 COMMENT='帮派日志信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildstatue`
--

DROP TABLE IF EXISTS `tblguildstatue`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildstatue` (
    `qwGuildID` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '帮派ID',
    `wLevel` smallint(6) NOT NULL DEFAULT '0' COMMENT '神像等级',
    `dwExp` int(11) NOT NULL DEFAULT '0',
    `byWorshipCount` tinyint(3) NOT NULL COMMENT '帮派神像当日供奉人数',
    `dwTime` int(10) NOT NULL DEFAULT '0' COMMENT '操作时间',
    PRIMARY KEY (`qwGuildID`)
) ENGINE=InnoDB AUTO_INCREMENT=4525589859933593 DEFAULT CHARSET=utf8 COMMENT='帮派神像';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblguildxihe`
--

DROP TABLE IF EXISTS `tblguildxihe`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblguildxihe` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `byStage` tinyint(2) NOT NULL COMMENT '当前阶段',
    `dwEndTime` int(10) NOT NULL COMMENT '当前阶段的结束时间',
    `strXihe` char(255) NOT NULL COMMENT '羲和神车货物信息',
    `byRequest` tinyint(2) NOT NULL COMMENT '已请求帮助的次数',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家的羲和神车任务信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblmaxid`
--

DROP TABLE IF EXISTS `tblmaxid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblmaxid` (
    `Grp` int(10) unsigned NOT NULL,
    `Idx` int(10) unsigned NOT NULL,
    `Type` int(10) unsigned NOT NULL,
    `Counter` int(10) unsigned NOT NULL,
    PRIMARY KEY (`Grp`,`Idx`,`Type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='各类型ID的最大值';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblnewguildbattlehistory`
--

DROP TABLE IF EXISTS `tblnewguildbattlehistory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblnewguildbattlehistory` (
    `byMountainType` tinyint(3) unsigned NOT NULL COMMENT '灵山类型',
    `qwGuildID` bigint(20) unsigned NOT NULL COMMENT '帮派ID',
    `strGuildName` char(30) DEFAULT NULL COMMENT '帮派名称',
    `strGuildOwnerName` char(30) DEFAULT NULL COMMENT '帮主名称',
    `dwTime` int(11) unsigned NOT NULL COMMENT '占领时间',
    PRIMARY KEY (`byMountainType`,`dwTime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='新帮派战历史帮派';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblnotice`
--

DROP TABLE IF EXISTS `tblnotice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblnotice` (
    `dwNoticeID` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '公告ID',
    `byNoticeType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '公告类型',
    `strContent` char(255) DEFAULT NULL COMMENT '公告内容',
    `dwBeginTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '开始时间',
    `dwEndTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '结束时间',
    PRIMARY KEY (`dwNoticeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='公告';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblpendres`
--

DROP TABLE IF EXISTS `tblpendres`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblpendres` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `byResType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '资源类型',
    `dwValue` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '资源值',
    `dwParam` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '参数',
    `bySource` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '来源',
    PRIMARY KEY (`qwRoleID`,`byResType`,`bySource`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='暂存资源';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblpetdata`
--

DROP TABLE IF EXISTS `tblpetdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblpetdata` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `wPetID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '宠物ID',
    `bySelected` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否出战',
    `byLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '宠物等级',
    `dwExp` int(10) unsigned DEFAULT '0' COMMENT '经验',
    PRIMARY KEY (`qwRoleID`,`wPetID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='阵灵信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblprepaid`
--

DROP TABLE IF EXISTS `tblprepaid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblprepaid` (
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `dwGold` int(10) NOT NULL COMMENT '预先充值的仙石总数量',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家未注册预先充值仙石记录';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrecharge`
--

DROP TABLE IF EXISTS `tblrecharge`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrecharge` (
    `strNo` char(255) NOT NULL DEFAULT '' COMMENT '充值流水号',
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `wGoldID` smallint(4) unsigned NOT NULL COMMENT '仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])',
    `dwCount` int(10) unsigned NOT NULL COMMENT '充值的仙石包数量',
    `dwGold` int(10) NOT NULL COMMENT '充值的仙石数量',
    `byStatus` tinyint(3) NOT NULL COMMENT '仙石是否到账(0-准备/不成功 1-成功,2-补单成功)',
    `dwHappenedTime` int(10) unsigned NOT NULL COMMENT '充值时间',
    PRIMARY KEY (`strNo`),
    KEY `noplayer` (`strNo`,`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家充值仙石记录';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleAchievement`
--

DROP TABLE IF EXISTS `tblroleAchievement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleAchievement` (
    `qwRoleID` bigint(20) NOT NULL COMMENT '角色ID',
    `wAchievementID` int(4) NOT NULL COMMENT '成就ID',
    `dwCount` int(4) DEFAULT NULL COMMENT '是否完成',
    `dwProcess` int(4) DEFAULT NULL COMMENT '进度',
    `dwFinishTime` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '完成时间',
    PRIMARY KEY (`qwRoleID`,`wAchievementID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='成就';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleActivitytaskinfo`
--

DROP TABLE IF EXISTS `tblroleActivitytaskinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleActivitytaskinfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
    `wId` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '活力纪录点',
    `byTimes` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '完成次数',
    `byIsSpecial` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否特别',
    PRIMARY KEY (`qwRoleID`,`wId`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='活力刷新纪录';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleAttaked`
--

DROP TABLE IF EXISTS `tblroleAttaked`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleAttaked` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '被攻击玩家ID',
    `dwPos` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '位置索引',
    `qwAtkRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '攻击玩家ID',
    `strRoleName` char(200) NOT NULL DEFAULT '' COMMENT '攻击玩家名字',
    `dwAttackedTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '攻击时间',
    `dwFighterType` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战斗类型',
    `byLevel` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
    PRIMARY KEY (`qwRoleID`,`dwPos`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家被攻击信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleCollection`
--

DROP TABLE IF EXISTS `tblroleCollection`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleCollection` (
    `qwRoleID` bigint(20) NOT NULL COMMENT '角色ID',
    `wCollectionID` int(4) NOT NULL COMMENT '成就ID',
    `dwCount` int(4) NOT NULL DEFAULT '0' COMMENT '是否完成',
    `dwProcess` int(4) NOT NULL DEFAULT '0' COMMENT '进度',
    `dwFinishTime` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '完成时间',
    PRIMARY KEY (`qwRoleID`,`wCollectionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='成就';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleGEMdata`
--

DROP TABLE IF EXISTS `tblroleGEMdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleGEMdata` (
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `wMissionID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '关卡ID',
    `byGEMType` tinyint(3) unsigned NOT NULL COMMENT '正在进行的类型（注：0表示没有；1：守卫；2：扫荡）',
    `wCurProgress` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '当前进度',
    `wGuardProgress` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '守卫进度',
    `dwGuardMonsterGroupID` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '守卫怪物组ID',
    `dwSweepEndTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '扫荡结束时间',
    `strBuff` char(255) NOT NULL DEFAULT '' COMMENT '守卫峨眉Buff(2,10|300,5)',
    PRIMARY KEY (`qwRoleID`,`wMissionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='守卫峨眉信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleTHdata`
--

DROP TABLE IF EXISTS `tblroleTHdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleTHdata` (
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `byCopyID` tinyint(3) unsigned NOT NULL COMMENT '副本ID',
    `dwTime` int(10) unsigned NOT NULL COMMENT '寻宝时间',
    `strAward` char(255) NOT NULL DEFAULT '' COMMENT '寻宝奖励(2,10|300,5)',
    `byStatus` tinyint(3) unsigned NOT NULL COMMENT '寻宝状态（1：正在进行；2：结束，等待领取奖品）',
    `dwBossCurHP` int(10) unsigned NOT NULL COMMENT 'Boss当前血量',
    `dwLastTime` int(10) unsigned NOT NULL COMMENT '攻打上一波怪时间',
    `dwNum` int(10) unsigned NOT NULL COMMENT '寻宝累计波数',
    PRIMARY KEY (`qwRoleID`,`byCopyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='寻宝奖励信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleadore`
--

DROP TABLE IF EXISTS `tblroleadore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleadore` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色唯一ID',
    `dwCount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '被崇拜数量',
    `dwUpdateTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最后更新时间',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家崇拜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolearena`
--

DROP TABLE IF EXISTS `tblrolearena`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolearena` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `dwCDTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '挑战冷却时间戳',
    `AwardLoot1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '第一个奖励包',
    `AwardLoot2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '第二个奖励包',
    `AwardLoot3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '第三个奖励包',
    `AwardbyDraw1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第一个奖励包领取状态',
    `AwardbyDraw2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第二个奖励包领取状态',
    `AwardbyDraw3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第三个奖励报领取状态',
    `FighterID1` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '第一个战斗对象',
    `FighterID2` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '第二个战斗对象',
    `FighterID3` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '第三个战斗对象',
    `FighterID4` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '第四个战斗对象',
    `FighterID5` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '第五个战斗对象',
    `FighterbySuc1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第一个战斗是否胜利',
    `FighterbySuc2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第二个战斗是否胜利',
    `FighterbySuc3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第三个战斗是否胜利',
    `FighterbySuc4` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第四个战斗是否胜利',
    `FighterbySuc5` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第五个战斗是否胜利',
    `dwLastAwardTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近评级时间',
    `AwardType1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第一个奖励包类型',
    `AwardType2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第二个奖励包类型',
    `AwardType3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第三个奖励包类型',
    `dwLadderCDTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '天梯战斗冷却到期时间戳',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='竞技场数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleautostore`
--

DROP TABLE IF EXISTS `tblroleautostore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleautostore` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '对应玩家ID',
    `wType` smallint(5) NOT NULL DEFAULT '0' COMMENT '大类',
    `dwClassID` int(10) NOT NULL DEFAULT '0' COMMENT '小类',
    `dwValue` int(10) NOT NULL DEFAULT '0' COMMENT '数值',
    PRIMARY KEY (`qwRoleID`,`wType`,`dwClassID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='有关各种计数的存储';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolebattlearray`
--

DROP TABLE IF EXISTS `tblrolebattlearray`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolebattlearray` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '对应玩家ID',
    `wBattleArrayID` smallint(5) NOT NULL DEFAULT '0' COMMENT '阵id',
    `dwBattleArrayLevelID` int(10) NOT NULL DEFAULT '0' COMMENT '进度(阵图id)',
    `byBattleArrayStatus` tinyint(3) NOT NULL DEFAULT '0' COMMENT '状态',
    PRIMARY KEY (`qwRoleID`,`wBattleArrayID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='破阵信息表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolebeauty`
--

DROP TABLE IF EXISTS `tblrolebeauty`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolebeauty` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色id',
    `wBeautyID` smallint(10) unsigned NOT NULL DEFAULT '0' COMMENT '美女id',
    `wBeautyLevel` smallint(10) unsigned DEFAULT '0' COMMENT '亲密等级',
    `dwBeautyExp` int(10) unsigned DEFAULT '0' COMMENT '亲密度',
    `wDayLoveType` smallint(10) unsigned DEFAULT '0' COMMENT '当天喜欢物品类型',
    `dwChatTime` int(11) DEFAULT '0' COMMENT '美女聊天cd',
    `dwPrizeExp` int(3) unsigned NOT NULL COMMENT '爱心已奖励经验',
    PRIMARY KEY (`qwRoleID`,`wBeautyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='美女';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolebubble`
--

DROP TABLE IF EXISTS `tblrolebubble`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolebubble` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `qwTransID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家的气泡流水ID',
    `wMsgID` smallint(6) NOT NULL DEFAULT '0' COMMENT '气泡ID',
    `dwTime` bigint(20) NOT NULL DEFAULT '0' COMMENT '气泡时间',
    `vecString` char(64) NOT NULL DEFAULT '' COMMENT '字符串参数',
    `vecParam` char(64) NOT NULL DEFAULT '' COMMENT '整型参数',
    PRIMARY KEY (`qwRoleID`,`qwTransID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家气泡信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolebuyitemlimit`
--

DROP TABLE IF EXISTS `tblrolebuyitemlimit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolebuyitemlimit` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwInstID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '商店购买实例id',
    `dwCount` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '购买次数',
    PRIMARY KEY (`qwRoleID`,`dwInstID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='每日购买物品限购计数';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolecittadata`
--

DROP TABLE IF EXISTS `tblrolecittadata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolecittadata` (
    `qwInstID` bigint(20) NOT NULL COMMENT '物品唯一ID',
    `qwRoleID` bigint(20) NOT NULL COMMENT '拥有者玩家ID',
    `qwOwnerID` bigint(20) NOT NULL COMMENT '拥有者散仙ID',
    `byAttrType1` tinyint(3) DEFAULT NULL COMMENT '增益属性类型1',
    `dwAttrValue1` int(10) DEFAULT NULL COMMENT '增益属性值1',
    `byAttrType2` tinyint(3) DEFAULT NULL COMMENT '增益属性类型2',
    `dwAttrValue2` int(10) DEFAULT NULL COMMENT '增益属性值2',
    `byAttrType3` tinyint(3) DEFAULT NULL COMMENT '增益属性类型3',
    `dwAttrValue3` int(10) DEFAULT NULL COMMENT '增益属性值3',
    `byAttrType4` tinyint(3) DEFAULT NULL COMMENT '增益属性类型4',
    `dwAttrValue4` int(10) DEFAULT NULL COMMENT '增益属性值4',
    `dwSkillID` int(10) DEFAULT NULL COMMENT '带出心法ID',
    `dwSignetID` int(10) DEFAULT NULL COMMENT '附带符印ID',
    PRIMARY KEY (`qwInstID`),
    UNIQUE KEY `qwInstID_UNIQUE` (`qwInstID`),
    KEY `OnlyIndex` (`qwInstID`,`qwRoleID`,`qwOwnerID`),
    KEY `OwnerIndex` (`qwInstID`,`qwOwnerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='心法道具相关属性';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroledata`
--

DROP TABLE IF EXISTS `tblroledata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroledata` (
    `qwRoleID` bigint(20) unsigned NOT NULL,
    `strName` char(30) NOT NULL COMMENT '名字',
    `byLevel` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT '等级',
    `qwExp` bigint(20) NOT NULL COMMENT '玩家经验值',
    `eCareer` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '职业',
    `eSex` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '性别',
    `wMapId` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT '世界地图',
    `fX` float(5,2) NOT NULL DEFAULT '0.00' COMMENT '世界地图坐标X',
    `fY` float(5,2) NOT NULL DEFAULT '0.00' COMMENT '世界地图坐标Y',
    `byNation` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '国籍',
    `byGMLvl` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'GM等级',
    `dwTotalRecharge` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '冲值总数',
    `dwLoginTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '上次登陆时间',
    `dwOfflineTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '上次下线时间',
    `dwLockExpireTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '封号结束时间',
    `dwForbExpireTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '禁言结束时间',
    `dwGold` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '仙石',
    `dwFreeGold` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '免费仙石',
    `dwSilver` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '银币',
    `dwCoupon` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '礼券',
    `dwSoul` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '魂魄',
    `dwPrestige` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '声望',
    `dwHonor` int(10) unsigned NOT NULL COMMENT '荣誉',
    `dwPExp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '修为',
    `dwAction` int(10) unsigned NOT NULL DEFAULT '100' COMMENT '体力',
    `dwPoten` int(10) unsigned NOT NULL COMMENT '副本星级',
    `dwReiki` int(10) unsigned NOT NULL COMMENT '渡劫点数',
    `dwDemonSoul` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '魂值',
    `dwSoulAttack` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '攻击之魄',
    `dwSoulHp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '生命之魄',
    `dwSoulCritical` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '暴击之魄',
    `dwSoulCounter` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '反击之魄',
    `dwSoulSpeed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '身法之魄',
    `dwSoulDefence` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '防御之魄',
    `dwSoulHit` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '命中之魄',
    `dwSoulDodge` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '闪避之魄',
    `dwBTPoint` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '战斗力',
    `szOwnTitle` char(255) NOT NULL DEFAULT '' COMMENT '拥有称号',
    `szEquipTitle` char(255) NOT NULL DEFAULT '' COMMENT '装备称号',
    `byDomain` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '渠道',
    `byDomainLvl` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '渠道等级',
    `byDisplayLvl` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '显示等级',
    `byDomainYear` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '年费',
    `szOpenId` char(255) NOT NULL DEFAULT '' COMMENT '腾讯平台登陆时的openid',
    `szOpenKey` char(255) NOT NULL DEFAULT '' COMMENT '腾讯平台登陆时的openkey',
    `qwInvitedID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT ' 邀请',
    `byWallow` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '防沉迷',
    `qwDgnId` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '当前副本实例',
    `dwDgnTypeID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '当前副本类型',
    `wDgnMapId` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT '当前副本地图',
    `fDgnfX` float(5,2) unsigned NOT NULL DEFAULT '0.00' COMMENT '当前副本坐标X',
    `fDgnfY` float(5,2) unsigned NOT NULL DEFAULT '0.00' COMMENT '当前副本坐标Y',
    `dwPendSilver` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '延迟发放的银币',
    `dwPendCoupon` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '延迟发放的礼券',
    `dwPendExp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '延迟发主的经验',
    `dwPendGold` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '延迟发放的金币',
    `strSign` char(255) NOT NULL DEFAULT '' COMMENT '签名',
    `wMood` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT '心情表情',
    `dwDemonTowerPrizeFloorID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '镇妖塔领奖层数',
    `dwDemonTowerFloorID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '镇妖塔最高层',
    `strGuide` char(32) NOT NULL DEFAULT '' COMMENT '新手引导内容',
    `szIcon` char(255) NOT NULL DEFAULT '' COMMENT '开放的Icon',
    `szIconDel` char(255) NOT NULL DEFAULT '' COMMENT '关闭的Icon',
    `szIconActive` char(255) NOT NULL DEFAULT '' COMMENT '活动的Icon',
    `dwPackUnlocked` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '背包上次解锁时间',
    `byPackUnlockable` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '背包是否可解锁',
    `dwPackNextUnlockTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '背包下次解锁时间',
    `dwActivity` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '活跃值',
    `dwStampHuang` int(10) unsigned NOT NULL COMMENT '黄阶除魔印',
    `dwStampXuan` int(10) unsigned NOT NULL COMMENT '玄阶除魔印',
    `dwStampDi` int(10) unsigned NOT NULL COMMENT '地阶除魔印',
    `dwStampTian` int(10) unsigned NOT NULL COMMENT '天阶除魔印',
    `dwStampXing` int(10) unsigned NOT NULL COMMENT '星阶除魔印',
    `dwStampYue` int(10) unsigned NOT NULL COMMENT '月阶除魔印',
    `dwStampDi2` int(10) unsigned NOT NULL COMMENT '帝阶除魔印',
    `dwStampXian` int(10) unsigned NOT NULL COMMENT '仙阶除魔印',
    `dwStampSheng` int(10) unsigned NOT NULL COMMENT '圣阶除魔印',
    `dwStampFo` int(10) unsigned NOT NULL COMMENT '佛阶除魔印',
    `wAchievementLevel` int(3) unsigned NOT NULL DEFAULT '0' COMMENT '成就等级',
    `dwAchievementAP` int(3) unsigned NOT NULL DEFAULT '0' COMMENT '成就点',
    `wCollectLevel` int(3) unsigned NOT NULL DEFAULT '0' COMMENT '收藏等级',
    `dwCollectAP` int(3) unsigned NOT NULL DEFAULT '0' COMMENT '收藏点',
    `qwSittingPlayer` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '双修玩家',
    `dwIndulgeKickTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '防沉迷t人时间',
    `byYDLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '玩家黄钻等级',
    `dwCreateTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家创角时间',
    `strCreateIP` char(255) NOT NULL DEFAULT '' COMMENT '玩家创角时IP',
    `strLoginIP` char(255) NOT NULL DEFAULT '' COMMENT '玩家登录时IP',
    `wLastSaveMapID` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT '保存地图ID',
    `fLastSaveX` float(5,2) NOT NULL DEFAULT '0.00' COMMENT '保存X坐标',
    `fLastSaveY` float(5,2) NOT NULL DEFAULT '0.00' COMMENT '保存X坐标',
    `dwLoveHeart` int(11) DEFAULT '0' COMMENT '爱心值',
    `dwBlueFairyFate` int(10) unsigned NOT NULL COMMENT '蓝色仙缘',
    `dwPurpleFairyFate` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '紫色仙缘',
    `dwOrangeFairyFate` int(10) unsigned NOT NULL COMMENT '橙色仙缘',
    `dwDuJieFu` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '散仙渡劫符数量',
    `qwInivitID` bigint(11) DEFAULT '0' COMMENT '邀请好友id',
    `szDgnStarAward` char(255) NOT NULL DEFAULT '' COMMENT '副本星级领奖状况',
    `dwLuckyCoupon` int(11)  DEFAULT '0' COMMENT '幸运券',
    PRIMARY KEY (`qwRoleID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家基本数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroledgninfo`
--

DROP TABLE IF EXISTS `tblroledgninfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroledgninfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `dwDgnType` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '副本模板ID',
    `dwLastEnterTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近副本进入时间',
    `byCost` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '消费此次进入',
    `dwEnterTimesAppend` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '额外进入次数',
    `dwAppendEndTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '额外进入次数到期时间',
    `dwEnterTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进入总次数',
    `dwLastCompleteTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近副本完成时间',
    `dwCompleteTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '副本完成次数',
    `wMinTurns` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '最少回合数',
    `dwBuyTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近购买的时间',
    `dwBuyTimesToday` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '当天购买的次数',
    `dwFinishTimesToday` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '当天购买的次数',
    PRIMARY KEY (`qwRoleID`,`dwDgnType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家副本数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleequiptrumpdata`
--

DROP TABLE IF EXISTS `tblroleequiptrumpdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleequiptrumpdata` (
  `qwInstID` BIGINT(20) UNSIGNED NOT NULL COMMENT '道具唯一ID' ,
  `qwOwnerID` BIGINT(20) UNSIGNED NOT NULL COMMENT '所属散仙ID' ,
  `qwRoleID` BIGINT(20) UNSIGNED NOT NULL COMMENT '角色ID' ,
  `byIntensifyLvl` TINYINT(3) UNSIGNED NOT NULL COMMENT '强化等级' ,
  `byIntensifyLvlMax` TINYINT(3) UNSIGNED NOT NULL COMMENT '所能达到的最高强化等级' ,
  `dwBlessing` INT(10) UNSIGNED NOT NULL default '0' COMMENT '强化祝福值',
  `dwXiLianBlessing`   INT(10) UNSIGNED NOT NULL default '0' COMMENT '洗练祝福值（次数)' ,
  `strRandomAttr` char(255)  NOT NULL default "" COMMENT '洗练属性',
  `strReplaceAttr` char(255)  NOT NULL default "" COMMENT'替换洗练属性(保留不用)',
  PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='散仙装备法宝';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleevent`
--

DROP TABLE IF EXISTS `tblroleevent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleevent` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `byActClassID` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '活动类别ID',
    `dwEventInstID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '事件实例',
    `dwApplyID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '应用id',
    `wEventStatus` smallint(10) unsigned NOT NULL DEFAULT '0' COMMENT '事件状态',
    `bySave` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否存数据库',
    `dwParam1` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '参数1',
    `dwParam2` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '参数2',
    PRIMARY KEY (`qwRoleID`,`byActClassID`,`dwEventInstID`,`dwApplyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家事件中心';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleexchangeditem`
--

DROP TABLE IF EXISTS `tblroleexchangeditem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleexchangeditem` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwExchangeID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换id',
    `dwCount` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '兑换次数',
    `dwFinishTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最后兑换时间',
    PRIMARY KEY (`qwRoleID`,`dwExchangeID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家被攻击信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefashion`
--

DROP TABLE IF EXISTS `tblrolefashion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefashion` (
    `qwInstID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家唯一ID',
    `byLevel` tinyint(3) unsigned DEFAULT '1' COMMENT '时装等级',
    `dwExp` int(11) unsigned DEFAULT '0' COMMENT '幻化经验',
    `bySelected` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否选中',
    `byHide` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否启用模型',
    PRIMARY KEY (`qwInstID`,`qwRoleID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='主将时装信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefighter`
--

DROP TABLE IF EXISTS `tblrolefighter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefighter` (
    `qwInstID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `wFighterID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '将类型ID',
    `byRecruited` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否已招募',
    `byStar` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '星级',
    `iSlot` int(10) NOT NULL DEFAULT '-1' COMMENT '在将收集器中的位置',
    `iPos` int(10) NOT NULL DEFAULT '-1' COMMENT '在阵型中的位置[255-表示不在阵型中]',
    `byLevel` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
    `qwExp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '经验',
    `byLianPi` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '炼皮',
    `byTongJin` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '通筋',
    `byQiangJi` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '强肌',
    `byDuanGu` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '锻骨',
    `byHuoLuo` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '活络',
    `byXiSui` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '洗髓',
    `dwDujieExp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '散仙当前渡劫经验',
    `dwSpiritPower` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '元神力',
    PRIMARY KEY (`qwInstID`),
    KEY `qwRoleID` (`qwRoleID`),
    KEY `FighterRole` (`qwInstID`,`qwRoleID`),
    KEY `RoleFighterID` (`qwRoleID`,`wFighterID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家将数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefighterpassiveskill`
--

DROP TABLE IF EXISTS `tblrolefighterpassiveskill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefighterpassiveskill` (
    `qwOwnerID` BIGINT(20) UNSIGNED NOT NULL COMMENT '拥有者散仙唯一ID' ,
    `qwRoleID` BIGINT(20) UNSIGNED NOT NULL COMMENT '玩家唯一ID' ,
    `dwSkillID` INT(10) UNSIGNED NOT NULL COMMENT '技能ID' ,
    `dwSkillQuality` INT(10) UNSIGNED NOT NULL COMMENT '技能品质' ,
    `dwSkillLevel` INT(10) UNSIGNED NOT NULL COMMENT '技能等级' ,
    PRIMARY KEY (`qwOwnerID`,`dwSkillID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='散仙被动技能';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefightformation`
--

DROP TABLE IF EXISTS `tblrolefightformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefightformation` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '对应玩家ID',
    `wBattleType` smallint(5) NOT NULL DEFAULT '0' COMMENT '战斗类型',
    `wFormationID` smallint(5) NOT NULL DEFAULT '0' COMMENT '当前阵形ID',
    `strBattlePosInfo` char(255) NOT NULL DEFAULT '' COMMENT '阵型信息',
    PRIMARY KEY (`qwRoleID`,`wBattleType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='新阵型';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefighthero`
--

DROP TABLE IF EXISTS `tblrolefighthero`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefighthero` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '对应玩家ID',
    `wBattleType` smallint(5) NOT NULL DEFAULT '0' COMMENT '战斗类型',
    `qwInstID` bigint(20) NOT NULL DEFAULT '0' COMMENT '散仙instID',
    `dwHP` int(10) NOT NULL DEFAULT '0' COMMENT '当前生命值',
    `dwMaxHP` int(10) NOT NULL DEFAULT '0' COMMENT '最大生命值（可能用到）',
    `dwAura` int(10) NOT NULL DEFAULT '0' COMMENT '灵气值',
    PRIMARY KEY (`qwRoleID`,`wBattleType`,`qwInstID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='新阵型';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolefriends`
--

DROP TABLE IF EXISTS `tblrolefriends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolefriends` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `qwUserID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `byGroup` tinyint(3) unsigned NOT NULL DEFAULT '0',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    `byColor` tinyint(3) unsigned NOT NULL COMMENT '品质',
    PRIMARY KEY (`qwRoleID`,`qwUserID`,`byGroup`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家好友数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolegemstone`
--

DROP TABLE IF EXISTS `tblrolegemstone`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolegemstone` (
    `qwInstID` bigint(20) unsigned NOT NULL COMMENT '物品ID',
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `qwOwnerID` bigint(20) unsigned NOT NULL COMMENT '将ID',
    PRIMARY KEY (`qwInstID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家宝石信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolegodmonster`
--

DROP TABLE IF EXISTS `tblrolegodmonster`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolegodmonster` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `qwGuildID` bigint(20) NOT NULL DEFAULT '0' COMMENT '神兽ID',
    `dwFruit` int(10) NOT NULL DEFAULT '0' COMMENT '朱果数量',
    `dwScore` int(10) NOT NULL DEFAULT '0' COMMENT '玩家积分',
    `dwTotalScore` int(11) DEFAULT '0' COMMENT '总积分',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家天元神兽信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolegrouptaskinfo`
--

DROP TABLE IF EXISTS `tblrolegrouptaskinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolegrouptaskinfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
    `dwRepute` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '声望',
    `byReputeLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '声望等级',
    `byBuyTimes` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '购买次数',
    `dwFlushTask1` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '第1个任务',
    `eState1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第1任务状态',
    `dwFlushTask2` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '第2个任务',
    `eState2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第2任务状态',
    `dwFlushTask3` int(30) unsigned NOT NULL DEFAULT '0' COMMENT '第3个任务',
    `eState3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第3任务状态',
    `dwFlushTask4` int(40) unsigned NOT NULL DEFAULT '0' COMMENT '第4个任务',
    `eState4` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第4任务状态',
    `dwFlushTask5` int(50) unsigned NOT NULL DEFAULT '0' COMMENT '第5个任务',
    `eState5` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第5任务状态',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='师门任务';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleguilddata`
--

DROP TABLE IF EXISTS `tblroleguilddata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleguilddata` (
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `wLevel` int(5) unsigned NOT NULL COMMENT '玩家等级',
    `qwGuildID` bigint(20) unsigned NOT NULL COMMENT '帮派ID',
    `dwJoinTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '成员 - 加入时间    待审核 - 申请时间',
    `dwContribution` int(10) unsigned NOT NULL COMMENT '贡献度',
    `dwLastOnline` int(10) unsigned NOT NULL COMMENT '最后在线时间',
    `byMemberRank` tinyint(3) unsigned NOT NULL COMMENT '帮派职位',
    `byMemberLastRank` tinyint(3) unsigned NOT NULL COMMENT '帮派上一次职位',
    `dwAuthority` int(10) unsigned NOT NULL COMMENT '帮派权限',
    `strTech` char(64) NOT NULL DEFAULT '' COMMENT '帮派科技(1,12|2,22)',
    `dwBattleScore` int(10) unsigned NOT NULL COMMENT '帮派战积分',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `byQuality` tinyint(3) unsigned NOT NULL COMMENT '主将品质',
    PRIMARY KEY (`qwRoleID`),
    KEY `qwGuildID` (`qwGuildID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='帮派成员信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolehorse`
--

DROP TABLE IF EXISTS `tblrolehorse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolehorse` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色id',
    `qwUserID` bigint(20) unsigned DEFAULT '0' COMMENT '账号',
    `dwHorseID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '坐骑模型id',
    `dwHorseLevel` int(10) unsigned DEFAULT '0' COMMENT '坐骑等级',
    `dwPos` int(10) unsigned DEFAULT '0' COMMENT '装备位置 1表示已经装备',
    `dwModelID` int(10) unsigned DEFAULT '0' COMMENT '模型id',
    `dwExp` int(11) DEFAULT '0' COMMENT '当前经验值',
    `dwLock` int(11) DEFAULT '0' COMMENT '技能解锁位置',
    `strModel` char(255) DEFAULT '' COMMENT '已激活模型集合',
    PRIMARY KEY (`qwRoleID`,`dwHorseID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='坐骑';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleitemdata`
--

DROP TABLE IF EXISTS `tblroleitemdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleitemdata` (
    `qwInstID` bigint(20) unsigned NOT NULL,
    `qwRoleID` bigint(20) unsigned NOT NULL,
    `byStoreType` tinyint(3) unsigned NOT NULL COMMENT '背包类型',
    `wIndex` smallint(3) unsigned NOT NULL COMMENT '所属背包位置',
    `wItemID` smallint(5) unsigned NOT NULL COMMENT '物品模板ID',
    `wCount` smallint(5) unsigned NOT NULL COMMENT '物品个数',
    `byBind` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT '是否绑定 0-非绑定 1-绑定',
    `byExpired` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否到期 0-未到期 1-已到期',
    `dwExpireTime` int(11) unsigned NOT NULL COMMENT '时效过期时间',
    `dwMark` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '标记为Mark时间',
    PRIMARY KEY (`qwInstID`) USING BTREE,
    KEY `qwRoleID` (`qwRoleID`),
    KEY `ItemRole` (`qwInstID`,`qwRoleID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家物品数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolelevelprize`
--

DROP TABLE IF EXISTS `tblrolelevelprize`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolelevelprize` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `wActID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '活动id',
    `wLevel` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '领奖等级',
    `wStatus` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '活动状态',
    PRIMARY KEY (`qwRoleID`,`wActID`,`wLevel`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家等级奖励';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolelimitprize`
--

DROP TABLE IF EXISTS `tblrolelimitprize`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolelimitprize` (
    `qwInstID` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '流水号',
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `wPrizeID` int(10) NOT NULL DEFAULT '0' COMMENT '礼品ID',
    `wNum` int(10) NOT NULL DEFAULT '0' COMMENT '购买数量',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='天元神兽限购礼包';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolemail`
--

DROP TABLE IF EXISTS `tblrolemail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolemail` (
    `qwMailId` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件ID',
    `byMailType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件类型',
    `byInvalid` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否有效',
    `byGetted` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '附件是否提取',
    `strMailTitle` char(30) NOT NULL COMMENT '邮件标题',
    `strSenderName` char(30) NOT NULL COMMENT '邮件发送者名字',
    `byMailState` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件状态',
    `dwSendTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '邮件发送时间',
    `qwSenderID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件发送者ID',
    `qwReceiveID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件接受者ID',
    `strMailMsg` char(255) DEFAULT NULL COMMENT '邮件正文',
    `timeUpdateTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '邮件最近改变时间',
    `dwProtocolVersion` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '版本号',
    PRIMARY KEY (`qwMailId`),
    KEY `RoleMail` (`qwMailId`,`qwReceiveID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家邮件数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolemailattachtype`
--

DROP TABLE IF EXISTS `tblrolemailattachtype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolemailattachtype` (
    `qwMailId` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件ID',
    `wItemID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '模板id',
    `eItemQuelity` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '物品品质',
    `wCount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '数量',
    `eBindType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '绑定类型',
    `byExpired` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否过期',
    `dwExpireTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '过期时间',
    `qwOPID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '操作ID'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家邮件数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolemoney`
--

DROP TABLE IF EXISTS `tblrolemoney`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolemoney` (
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `byMoneyType` tinyint(3) unsigned NOT NULL COMMENT '货币类型',
    `qwData` bigint(20) unsigned NOT NULL COMMENT '货币数量',
    PRIMARY KEY (`qwRoleID`,`byMoneyType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家货币总表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolepetdata`
--

DROP TABLE IF EXISTS `tblrolepetdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolepetdata` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `dwExp` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '经验值',
    `byLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '阵灵等级',
    `dwSpirit` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '灵力值',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='阵灵全局信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolerankbattlepoint`
--

DROP TABLE IF EXISTS `tblrolerankbattlepoint`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolerankbattlepoint` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwBattlePoint` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家战斗力',
    `strName` char(32) NOT NULL COMMENT '玩家姓名',
    `dwUpdateTime` int(10) unsigned NOT NULL COMMENT '更新时间',
    `strGuildName` char(32) NOT NULL COMMENT '帮派名称',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `byQuality` tinyint(3) NOT NULL COMMENT '散仙品质',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家战斗力排行榜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolerankformation`
--

DROP TABLE IF EXISTS `tblrolerankformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolerankformation` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwBattlePoint` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家战斗力',
    `strName` char(32) NOT NULL COMMENT '玩家姓名',
    `dwUpdateTime` int(10) unsigned NOT NULL COMMENT '更新时间',
    `strGuildName` char(32) NOT NULL COMMENT '帮派名称',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `wID` smallint(5) unsigned NOT NULL COMMENT '阵灵ID',
    `byQuality` tinyint(3) NOT NULL COMMENT '主将品质',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`,`wID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家阵灵排行榜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolerankherofighter`
--

DROP TABLE IF EXISTS `tblrolerankherofighter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolerankherofighter` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwBattlePoint` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家战斗力',
    `strName` char(32) NOT NULL COMMENT '玩家姓名',
    `dwUpdateTime` int(10) unsigned NOT NULL COMMENT '更新时间',
    `strGuildName` char(32) NOT NULL COMMENT '帮派名称',
    `wID` smallint(5) unsigned NOT NULL COMMENT '散仙ID',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `byQuality` tinyint(3) NOT NULL COMMENT '散仙品质',
    `byInfoQuality` tinyint(3) NOT NULL COMMENT '散仙品质',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`,`wID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家散仙排行榜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleranklevel`
--

DROP TABLE IF EXISTS `tblroleranklevel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleranklevel` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `strName` char(32) NOT NULL COMMENT '玩家姓名',
    `dwUpdateTime` int(10) unsigned NOT NULL COMMENT '更新时间',
    `wLevel` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
    `qwExp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '经验值',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `byQuality` tinyint(3) NOT NULL COMMENT '散仙品质',
    `byVIPLevel` tinyint(3) NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家等级排行榜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleranktrump`
--

DROP TABLE IF EXISTS `tblroleranktrump`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleranktrump` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwBattlePoint` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家战斗力',
    `strName` char(32) NOT NULL COMMENT '玩家姓名',
    `dwUpdateTime` int(10) unsigned NOT NULL COMMENT '更新时间',
    `strGuildName` char(32) NOT NULL COMMENT '帮派名称',
    `wPlayerFighterID` smallint(5) unsigned NOT NULL COMMENT '主将ID',
    `wID` smallint(5) unsigned NOT NULL COMMENT '法宝ID',
    `byQuality` tinyint(3) NOT NULL COMMENT '主将品质',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`,`wID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家法宝排行榜信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleshipinfo`
--

DROP TABLE IF EXISTS `tblroleshipinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleshipinfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwBuyOpenShipTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '购买的运船次数',
    `dwBuyRoBShipTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '购买的抢劫次数',
    `dwBuyReflushShipTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '购买的刷新次数',
    `wReflushShip` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '刷出来的船',
    `qwInviteDefense` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邀请的护送者',
    `dwInviteDefenseAgreeTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '别人同意护送的时间',
    `dwInviteDefensePoint` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '护送者战斗力',
    `byInviteDefenseLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '护送者等级',
    `byInviteDefenseColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '护送者颜色',
    `qwAgreeDefenseShipOwer` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '我同意护送的船主',
    `dwAgreeDefenseShipOwerTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '我同意护送的时间',
    `dwReflushShipTimer` int(11) DEFAULT '0' COMMENT '刷船时间',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家运船信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleskill`
--

DROP TABLE IF EXISTS `tblroleskill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleskill` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `qwOwnerID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID,一般是将ID',
    `dwUpSkill1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能1',
    `dwUpSkill2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能2',
    `dwUpSkill3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能3',
    `dwUpSkill4` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能4',
    `dwUpSkill5` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能5',
    `dwUpSkill6` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '使用中的技能6',
    `dwSkill1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能1',
    `dwSkill2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能2',
    `dwSkill3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能3',
    `dwSkill4` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能4',
    `dwSkill5` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能5',
    `dwSkill6` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能6',
    `dwSkill7` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能7',
    `dwSkill8` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能8',
    `dwSkill9` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能9',
    `dwRune1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文1',
    `dwRune2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文2',
    `dwRune3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文3',
    `dwRune4` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文4',
    `dwRune5` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文5',
    `dwRune6` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文6',
    `dwRune7` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文7',
    `dwRune8` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文8',
    `dwRune9` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '符文9',
    `dwSkillAdv1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶1',
    `dwSkillAdv2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶2',
    `dwSkillAdv3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶3',
    `dwSkillAdv4` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶4',
    `dwSkillAdv5` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶5',
    `dwSkillAdv6` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶6',
    `dwSkillAdv7` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶7',
    `dwSkillAdv8` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶8',
    `dwSkillAdv9` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能进阶9',
    PRIMARY KEY (`qwRoleID`,`qwOwnerID`) USING BTREE,
    KEY `qwOwnerID` (`qwOwnerID`),
    KEY `RoleOwner` (`qwRoleID`,`qwOwnerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家技能数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolesweep`
--

DROP TABLE IF EXISTS `tblrolesweep`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolesweep` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `wCurDgnID` smallint(10) unsigned NOT NULL DEFAULT '0' COMMENT '当前扫荡副本',
    `wCurCount` smallint(11) unsigned NOT NULL DEFAULT '0' COMMENT '当前剩余扫荡次数',
    `dwReserverTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '下次扫荡剩余时间',
    `dwSaveTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '保存时间',
    `wOptions` smallint(11) unsigned NOT NULL DEFAULT '0' COMMENT '扫荡类型',
    `wCount` smallint(11) unsigned NOT NULL DEFAULT '0' COMMENT '扫荡需求次数',
    `strVecDgn` char(250) NOT NULL DEFAULT '' COMMENT '未开始扫荡副本',
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家扫荡信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroletarget`
--

DROP TABLE IF EXISTS `tblroletarget`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroletarget` (
    `qwRoleID` bigint(20) NOT NULL COMMENT '角色ID',
    `wTaskID` smallint(4) NOT NULL COMMENT '任务ID',
    `byStatus` tinyint(4) DEFAULT NULL COMMENT '否完成',
    `dwProcess` int(4) DEFAULT NULL COMMENT '进度',
    PRIMARY KEY (`qwRoleID`,`wTaskID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='成就';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroletaskinfo`
--

DROP TABLE IF EXISTS `tblroletaskinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroletaskinfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `dwTaskId` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '任务Id',
    `eTaskState` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '任务状态',
    `dwAcceptTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '总共接受任务次数',
    `dwLastAcceptTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近任务接受时间',
    `dwFinishTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近完成任务时间',
    `dwLastFinishTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近完成任务时间',
    `byProcessType1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '进度1的类型',
    `dwProcessParam11` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度1的第1个参数',
    `dwProcessParam12` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度1的第2个参数',
    `byProcessType2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '进度2的类型',
    `dwProcessParam21` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度2的第1个参数',
    `dwProcessParam22` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度2的第2个参数',
    `byProcessType3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '进度3的类型',
    `dwProcessParam31` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度3的第1个参数',
    `dwProcessParam32` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进度3的第2个参数',
    `dwRepeatAcceptTimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '当前接的任务次数',
    PRIMARY KEY (`qwRoleID`,`dwTaskId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家任务数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroletitle`
--

DROP TABLE IF EXISTS `tblroletitle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroletitle` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
    `wId` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '称号Id',
    `byEquipPos` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '装备位置',
    `dwValidTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '有效截至时间',
    PRIMARY KEY (`qwRoleID`,`wId`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='称号数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroletrumpdata`
--

DROP TABLE IF EXISTS `tblroletrumpdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroletrumpdata` (
    `qwInstID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '唯一ID',
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `byUsed` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否出战',
    `dwExp` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '升级经验值',
    `wLevel` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '祭炼等级',
    `wRank` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '祭炼阶数',
    PRIMARY KEY (`qwInstID`),
    KEY `qwRoleID` (`qwRoleID`),
    KEY `InstRoleOwner` (`qwInstID`,`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='散仙本命法宝';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolevars`
--

DROP TABLE IF EXISTS `tblrolevars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblrolevars` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0',
    `byServerType` tinyint(3) unsigned NOT NULL DEFAULT '0',
    `wVar` smallint(5) unsigned NOT NULL DEFAULT '0',
    `qwValue` bigint(20) unsigned NOT NULL DEFAULT '0',
    `dwExpired` int(11) unsigned NOT NULL DEFAULT '0',
    PRIMARY KEY (`qwRoleID`,`byServerType`,`wVar`) USING BTREE,
    KEY `RoleVar` (`qwRoleID`,`wVar`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家变量数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleyamentaskinfo`
--

DROP TABLE IF EXISTS `tblroleyamentaskinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleyamentaskinfo` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
    `dwHoly` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '圣义',
    `byHolyLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '圣义等级',
    `byBuyTimes` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '购买次数',
    `dwFlushTask1` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '第1个任务',
    `eState1` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第1任务状态',
    `dwFlushTask2` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '第2个任务',
    `eState2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第2任务状态',
    `dwFlushTask3` int(30) unsigned NOT NULL DEFAULT '0' COMMENT '第3个任务',
    `eState3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第3任务状态',
    `dwFlushTask4` int(40) unsigned NOT NULL DEFAULT '0' COMMENT '第4个任务',
    `eState4` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第4任务状态',
    `dwFlushTask5` int(50) unsigned NOT NULL DEFAULT '0' COMMENT '第5个任务',
    `eState5` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第5任务状态',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='衙门任务';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblroleyd`
--

DROP TABLE IF EXISTS `tblroleyd`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblroleyd` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
    `byPtType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '平台类型',
    `byQQPtType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'QQpingt类型',
    `byQQPtLv` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
    `bySPType` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '额外标志位（Bit0:豪华/超级钻，Bit1:年费）',
    PRIMARY KEY (`qwRoleID`,`byPtType`,`byQQPtType`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='黄钻信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblslotsdata`
--

DROP TABLE IF EXISTS `tblslotsdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblslotsdata` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `qwOwnerID` bigint(20) NOT NULL DEFAULT '0' COMMENT '拥有者ID',
    `byStoreType` tinyint(3) NOT NULL DEFAULT '0' COMMENT '槽的类型',
    `wMaxSlot` smallint(5) NOT NULL DEFAULT '0' COMMENT '当前槽支持的最大数量',
    `wMaxAvaliableSlot` smallint(5) NOT NULL DEFAULT '0' COMMENT '当前槽已经开启的最大数量',
    PRIMARY KEY (`qwRoleID`,`byStoreType`,`qwOwnerID`),
    UNIQUE KEY `SLOT_UNIQUE` (`qwRoleID`,`qwOwnerID`,`byStoreType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='有关各种槽的记录存储（心法槽，装备槽，背包仓库槽）';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblsoulspace`
--

DROP TABLE IF EXISTS `tblsoulspace`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblsoulspace` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色id',
    `dwSoulSpaceID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '魄空间Id',
    `dwSoulSpaceLevel` int(11) DEFAULT '0' COMMENT '魄空间等级',
    PRIMARY KEY (`qwRoleID`,`dwSoulSpaceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='魄空间';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltotalarena`
--

DROP TABLE IF EXISTS `tbltotalarena`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltotalarena` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `dwRanking` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '所属积分序号',
    `dwScore` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '积分',
    `eLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '段位',
    `dwLastFlushTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '玩家最近操作时间',
    `dwLastRank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最近排名',
    `eLastLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '最近段位',
    `dwLadderRank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '天梯排名',
    `dwFighterPower` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战斗力',
    `dwLastLadderRank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '上次结算排名',
    `byQuality` tinyint(3) unsigned NOT NULL COMMENT '散仙品质',
    `byVIPLevel` tinyint(3) unsigned NOT NULL COMMENT 'VIP等级',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='竞技场数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltotaloffevent`
--

DROP TABLE IF EXISTS `tbltotaloffevent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltotaloffevent` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `dwEventType` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '事件类型',
    `byServerType` int(3) unsigned NOT NULL DEFAULT '0' COMMENT '服务器类型',
    `dwTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '事件时间',
    `strParam1` char(255) DEFAULT NULL COMMENT '参数1',
    `strParam2` char(255) DEFAULT NULL COMMENT '参数2',
    PRIMARY KEY (`qwRoleID`,`dwEventType`,`byServerType`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='离线事件';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltotalship`
--

DROP TABLE IF EXISTS `tbltotalship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltotalship` (
    `qwInsID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '金船唯一ID',
    `qwOwer` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '金船拥有者',
    `dwOwerPoint` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '金船拥有者战斗力',
    `byOwerLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '拥有者等级',
    `byOwerColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '拥有者颜色',
    `byChannel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '航道',
    `wShipId` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '金船模板',
    `qwDefense` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '护送者ID',
    `dwDefensePoint` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '护送者战斗力',
    `byDefenseLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '护送者等级',
    `byDefenseColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '护送者颜色',
    `qwRoBId1` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者1',
    `byRoB1Color` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者1颜色',
    `dwRoB1Point` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者1战斗力',
    `byRoB1Level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者1等级',
    `qwRoBId2` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者2',
    `byRoB2Color` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者2颜色',
    `dwRoB2Point` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者2战斗力',
    `byRoB2Level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者2等级',
    `qwRoBId3` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者3',
    `byRoB3Color` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者3颜色',
    `dwRoB3Point` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者3战斗力',
    `byRoB3Level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者3等级',
    `dwBeginTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '开船时间',
    `dwEndTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '结束时间',
    `dwAwardRate` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '运船倍率',
    PRIMARY KEY (`qwInsID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='正在开的金船';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltotalshipreport`
--

DROP TABLE IF EXISTS `tbltotalshipreport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltotalshipreport` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '战报拥有者',
    `qwInsID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '金船唯一ID',
    `eSource` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '战斗原因',
    `qwOwer` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '金船拥有者',
    `byOwerColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '拥有者颜色',
    `wShipId` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '金船模板',
    `qwDefense` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '护送者ID',
    `byDefenseColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '护送者颜色',
    `qwRoBId` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者',
    `byRoBColor` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '打劫者颜色',
    `qwBattleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '战报ID',
    `dwFinishTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '该船到达时间',
    `dwTimer` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '发生时间',
    `byRobTimes` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '被抢劫次数',
    `dwAwardRate` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '运船倍率',
    KEY `qwInsID` (`qwInsID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='金船战报';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltripoddata`
--

DROP TABLE IF EXISTS `tbltripoddata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltripoddata` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `byTripodID` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '九疑鼎ID',
    `byLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '九疑鼎等级',
    `dwExp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '九疑鼎当前经验值',
    `wFireID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '火种ID',
    `byFireLvl` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '火种等级(品质)',
    `dwStartTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '上一次结算时间',
    `dwShanfengTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '上一次扇风时间(为0未扇风)',
    `dwSoul` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '当前已结算的总元气值',
    `dwLine` int(10) unsigned NOT NULL COMMENT '加成系数（万分比）',
    PRIMARY KEY (`qwRoleID`,`byTripodID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家九疑鼎数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltripodfiredata`
--

DROP TABLE IF EXISTS `tbltripodfiredata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltripodfiredata` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `wFireID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '九疑鼎火种ID',
    `dwSucceed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '火种起火成功次数',
    `dwRemain` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '火种剩余起火次数',
    PRIMARY KEY (`qwRoleID`,`wFireID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家九疑鼎火种数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltripodhelpdata`
--

DROP TABLE IF EXISTS `tbltripodhelpdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltripodhelpdata` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属者ID',
    `strFighterHelp` char(255) NOT NULL DEFAULT '' COMMENT '散仙协助数据',
    `strPlayerHelp` char(255) NOT NULL DEFAULT '' COMMENT '玩家协助数据',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家九疑鼎协助数据';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tbltripodlog`
--

DROP TABLE IF EXISTS `tbltripodlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbltripodlog` (
    `qwInstID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '流水号ID',
    `qwRoleID` bigint(20) unsigned NOT NULL COMMENT '玩家ID',
    `wMsgID` smallint(5) unsigned NOT NULL COMMENT '协议ID',
    `vecParam` char(250) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '数字参数',
    `vecString` char(250) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL COMMENT '文字参数',
    `dwTime` int(10) unsigned NOT NULL COMMENT '日志时间',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8 COMMENT='九疑鼎动态日志';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblwonderprize`
--

DROP TABLE IF EXISTS `tblwonderprize`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblwonderprize` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `wActType` int(10) unsigned NOT NULL COMMENT '活动类型',
    `wActID` int(10) unsigned NOT NULL COMMENT '活动ID',
    `wCond` int(10) unsigned NOT NULL COMMENT '活动条件',
    `byStatus` tinyint(3) NOT NULL COMMENT '奖励状态',
    PRIMARY KEY (`qwRoleID`,`wActID`,`wCond`),
    KEY `qwRoleID_wActID` (`qwRoleID`,`wActID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='精彩活动奖励信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblwonderretain`
--

DROP TABLE IF EXISTS `tblwonderretain`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblwonderretain` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `strName` char(30) NOT NULL COMMENT '玩家名字',
    `byCareer` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家职业',
    `bySex` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家性别',
    `wActID` int(10) unsigned NOT NULL COMMENT '活动ID',
    `wType` int(10) unsigned NOT NULL COMMENT '保留类型',
    `dwValue` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '保留值',
    `dwTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
    `strGuildName` char(30) NOT NULL COMMENT '帮派名',
    `wID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '保留ID',
    PRIMARY KEY (`qwRoleID`,`wActID`,`wType`),
    KEY `qwRoleID_wActID` (`qwRoleID`,`wActID`),
    KEY `qwRoleID` (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='精彩活动保留值信息';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblworldboss`
--

DROP TABLE IF EXISTS `tblworldboss`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblworldboss` (
    `wBossID` smallint(5) unsigned NOT NULL COMMENT 'BOSS ID',
    `dwLast` int(10) unsigned NOT NULL COMMENT '上次被击杀所用时长，单位秒',
    `dwHP` int(10) unsigned NOT NULL COMMENT '上次最大血量',
    `dwAtk` int(10) unsigned NOT NULL COMMENT '上次物理攻击力',
    `dwMAtk` int(10) unsigned NOT NULL COMMENT '上次魔法攻击力',
    `dwLastEndTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '最后结束时间',
    PRIMARY KEY (`wBossID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='世界BOSS信息';
/*!40101 SET character_set_client = @saved_cs_client */;

DROP TABLE IF EXISTS `tblrolebeauty`;
CREATE TABLE `tblrolebeauty` (
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色id',
    `wBeautyID` smallint(10) unsigned NOT NULL DEFAULT '0' COMMENT '美女id',
    `wBeautyLevel` smallint(10) unsigned DEFAULT '0' COMMENT '亲密等级',
    `dwBeautyExp` int(10) unsigned DEFAULT '0' COMMENT '亲密度',
    `wDayLoveType` smallint(10) unsigned DEFAULT '0' COMMENT '当天喜欢物品类型',
    `dwChatTime` int(11) DEFAULT '0' COMMENT '美女聊天cd',
    `dwPrizeExp` int(11) DEFAULT '0' COMMENT '美女聊天cd',
    PRIMARY KEY (`qwRoleID`,`wBeautyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='美女';

DROP TABLE IF EXISTS `tblcenterdata`;
CREATE TABLE `tblcenterdata` (
    `wType` smallint(10) unsigned DEFAULT '0' COMMENT '类型',
    `qwInstID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'id',
    `qwInstID2` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'id',
    `qwParam` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '64位参数',
    `strParam` char(30) NOT NULL DEFAULT '' COMMENT '字符参数',
    `dwParam1` int(10) unsigned DEFAULT '0' COMMENT '32位参数1',
    `dwParam2` int(10) unsigned DEFAULT '0' COMMENT '32位参数2',
    `dwParam3` int(10) unsigned DEFAULT '0' COMMENT '32位参数2',
    `qwParam4` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '64位参数',
    PRIMARY KEY (`qwInstID`,`qwInstID2`,`wType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='center全局数据';


DROP TABLE IF EXISTS `tblguildexchangeditem`;
CREATE TABLE `tblguildexchangeditem` (
    `qwGuildID` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮派ID',
    `dwExchangeID` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换id',
    `dwCount` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '兑换数量',
    PRIMARY KEY (`qwGuildID`,`dwExchangeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='兑换物品';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tblrolelimitprize`
--

DROP TABLE IF EXISTS `tblrolelimitprize`;
CREATE TABLE `tblrolelimitprize` (
    `qwInstID` bigint(20) NOT NULL  AUTO_INCREMENT COMMENT '流水号',
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `wPrizeID` int(10)    NOT NULL DEFAULT '0' COMMENT '礼品ID',
    `wNum` int(10)        NOT NULL DEFAULT '0' COMMENT '购买数量',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='天元神兽限购礼包';

--
-- Table structure for table `tblactivitycenter`
--

DROP TABLE IF EXISTS `tblactivitycenter`;
CREATE  TABLE `tblactivitycenter` (
    `dwActID`   INT(11)    UNSIGNED NOT NULL DEFAULT "1" COMMENT '活动ID' ,
    `byIndex`   TINYINT(3)    UNSIGNED NOT NULL DEFAULT "1" COMMENT '场次' ,
    `strName`       char(30)  NOT NULL COMMENT '名字' ,
    `dwSync`    INT(11)    UNSIGNED NOT NULL DEFAULT "120" COMMENT '什么时间同步默认2分钟' ,
    `dwAlarm`   INT(11)    UNSIGNED NOT NULL DEFAULT "0" COMMENT '活动公告时间' ,
    `dwReady`   INT(11)    UNSIGNED NOT NULL DEFAULT "0" COMMENT '活动准备时间' ,
    `dwBegin`   INT(11)    UNSIGNED NOT NULL DEFAULT "0" COMMENT '活动开启时间' ,
    `dwEnd`     INT(11)    UNSIGNED NOT NULL DEFAULT "0" COMMENT '活动结束时间' ,
    `IsSync`    TINYINT(3) UNSIGNED NOT NULL DEFAULT "0" COMMENT '是否需要同步到GameServer' ,
    `dwOptTime` INT(11) UNSIGNED NOT NULL COMMENT '操作时间',
    PRIMARY KEY (`dwActID`,`byIndex`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT = '运营活动中心流水';

--
-- Table structure for table `tblrolegodmonster`
--

DROP TABLE IF EXISTS `tblrolegodmonster`;
CREATE TABLE `tblrolegodmonster` (
    `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `qwGuildID`bigint(20) NOT NULL DEFAULT '0' COMMENT '神兽ID',
    `dwFruit` int(10) NOT NULL     DEFAULT '0' COMMENT '朱果数量',
    `dwScore` int(10) NOT NULL     DEFAULT '0' COMMENT '玩家积分',
    `dwTotalScore` int(10) NOT NULL     DEFAULT '0' COMMENT '玩家总积分',
    PRIMARY KEY (`qwRoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家天元神兽信息';

--
-- Table structure for table `tblroleshengling`
--

DROP TABLE IF EXISTS `tblroleshengling`;
CREATE TABLE `tblroleshengling` (
      `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
      `byLevel`  tinyint(3) NOT NULL DEFAULT '0' COMMENT '层数',
      `byIndex`  tinyint(3) NOT NULL DEFAULT '0' COMMENT '格子Id',
      `byType`   tinyint(3) NOT NULL DEFAULT '0' COMMENT '格子类型',
      `wNoteID`  int(10)    NOT NULL DEFAULT '0' COMMENT '格子记录ID',
      `byRandom` tinyint(3) NOT NULL DEFAULT '0' COMMENT '是否随机格子',
      `byFinish` tinyint(3) NOT NULL DEFAULT '0' COMMENT '是否完成格子任务',
      PRIMARY KEY (`qwRoleID`,`byLevel`,`byIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家圣陵信息';

--
-- Table structure for table `tblroleshenglingprize`
--

DROP TABLE IF EXISTS `tblroleshenglingprize`;
CREATE TABLE `tblroleshenglingprize` (
      `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
      `wItemID`  int(10) NOT NULL DEFAULT '0' COMMENT '层数',
      `wNum`     int(10) NOT NULL DEFAULT '0' COMMENT '格子Id',
      PRIMARY KEY (`qwRoleID`,`wItemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家圣陵信息';

--
-- Table structure for table `tblzodtrumpdata`
--

DROP TABLE IF EXISTS `tblzodtrumpdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tblzodtrumpdata` (
    `qwInstID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '唯一ID',
    `qwRoleID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属角色ID',
    `qwOwnerID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所属散仙ID',
    `dwExp` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '升级经验值',
    `byLevel` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT '本命法宝等级',
    `bySkillUnlocked2` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第2个技能是否解锁',
    `bySkillUnlocked3` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '第3个技能是否解锁',
    `dwSkill1` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能1',
    `dwSkill2` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能2',
    `dwSkill3` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '技能3',
    PRIMARY KEY (`qwInstID`),
    KEY `qwRoleID` (`qwRoleID`),
    KEY `InstRoleOwner` (`qwInstID`,`qwRoleID`,`qwOwnerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='散仙本命法宝';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;
--
-- Table structure for table `ladderrobot`
--
DROP TABLE IF EXISTS `ladderrobot`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ladderrobot` (
    `wMonsterID` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT '怪物id',
    `wRank` smallint(6) unsigned DEFAULT '0' COMMENT '天梯排名',
    PRIMARY KEY (`wMonsterID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='天梯排名信息';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

DROP TABLE IF EXISTS `tbllingshanshopbuylog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbllingshanshopbuylog` (
    `qwInstID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '唯一自增长流水ID',
    `qwGuildID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '帮派唯一ID',
    `wMsgID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '日志类型ID',
    `vecString` char(64) NOT NULL DEFAULT '' COMMENT '变量字符',
    `vecParam` char(64) NOT NULL DEFAULT '' COMMENT '变量数值（XX,XX,XX）',
    `dwTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '日志时间',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8 COMMENT='帮派购买日志信息';

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-03-31 16:06:36
