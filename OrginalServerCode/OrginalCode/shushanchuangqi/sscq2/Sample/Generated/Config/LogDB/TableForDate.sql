DELIMITER $$
DROP PROCEDURE IF EXISTS ExecSQL $$
CREATE PROCEDURE ExecSQL (IN strSQL TEXT)
BEGIN
    SET @sql_text = strSQL;
    PREPARE stmt FROM @sql_text;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
END$$

DROP PROCEDURE IF EXISTS ExecSQLForTable $$
CREATE PROCEDURE ExecSQLForTable (IN strSQLPre Text, IN strName TEXT, IN strSQLPost Text)
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE tablename TEXT;
    DECLARE cur CURSOR FOR SELECT TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA=DATABASE() AND TABLE_NAME LIKE strName;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    OPEN cur;
    read_loop: LOOP
    FETCH cur INTO tablename;
    IF done THEN
        LEAVE read_loop;
    END IF;
    CALL ExecSQL(CONCAT(strSQLPre, "`", tablename, "`", strSQLPost));
END LOOP;
END$$

DROP PROCEDURE IF EXISTS CreateLogTables $$
CREATE PROCEDURE CreateLogTables (IN nYear INT, IN nMonth INT)
BEGIN

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblDgnLog_", nYear, "_", nMonth, "` (
                `qwDgnInsID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '副本实例',
                `wDgnType` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '副本模板',
                `eOpType`  tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型',
                `qwUserID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '操作者',
                `LogTime`  DateTime,
                INDEX LogTime_Index (LogTime),
                INDEX UserID_Index(qwUserID),
                INDEX DgnInsID_Index(qwDgnInsID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblRegisterLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `player_name` varchar(255) NOT NULL DEFAULT '' COMMENT '玩家名字',
                `reg_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '注册时间',
                PRIMARY KEY(server_id, player_id) 
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblLoginLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `login_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '登录时间',
                `login_ip` varchar(255) NOT NULL DEFAULT '' COMMENT '登录IP',
                `logout_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '离开时间',
                PRIMARY KEY(server_id, player_id, login_time) 
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblItemCoursesLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strOpen_id` varchar(255) NOT NULL DEFAULT '' COMMENT '玩家openID',
                `qwInst_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '流水ID',
                `item_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '物品ID',
                `item_num` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '物品数量',
                `from_to` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '出处',
                `from_toStr` varchar(255) NOT NULL DEFAULT '' COMMENT '玩家道具来源或者消耗描述',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                INDEX(`server_id`, `player_id`, `qwInst_id`),
                INDEX (`server_id`, `player_id`),
                INDEX (`server_id`, `qwInst_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblMoneyCoursesLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strOpen_id` varchar(255) NOT NULL DEFAULT '' COMMENT '玩家openID',
                `money_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '货币类型ID',
                `money_num` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '货币使用or增加数量',
                `total_num` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '当前货币总数量',
                `from_to` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '出处',
                `from_toStr` varchar(255) NOT NULL DEFAULT '' COMMENT '玩家货币来源或者消耗描述',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                `bIsFreeGold` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '是否使用免费仙石',
                KEY `server_player` (`server_id`, `player_id`),
                KEY `server_player_time` (`server_id`, `player_id`, `happened_time`),
                KEY `server_player_item` (`server_id`, `player_id`, `money_id`),
                KEY `server_player_type` (`server_id`, `player_id`, `from_to`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblPetLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `pet_name` varchar(255) NOT NULL DEFAULT '' COMMENT '阵灵名字',
                `opt_type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型',
                `pet_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '阵灵等级',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                 KEY `server_player` (`server_id`, `player_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblDujieLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `fighter_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '散仙ID',
                `fighter_name` varchar(255) NOT NULL DEFAULT '' COMMENT '散仙名字',
                `period_name` varchar(255) NOT NULL DEFAULT '' COMMENT '渡劫阶段',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                `fighter_exp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '渡劫值',
                 KEY `server_player_fighter` (`server_id`, `player_id`, `fighter_id`),
                 KEY `server_player` (`server_id`, `player_id`),
                 KEY `server_player_time` (`server_id`, `player_id`, `happened_time`),
                 KEY `server_player_name` (`server_id`, `player_id`, `fighter_name`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
     CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblFashionLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `fashion_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时装ID',
                `fashion_name` varchar(255) NOT NULL DEFAULT '' COMMENT '时装名字',
                `fashion_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时装等级',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                 KEY `server_player_fashion` (`server_id`, `player_id`, `fashion_id`),
                 KEY `server_player` (`server_id`, `player_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblFighterLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `fighter_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '散仙ID',
                `fighter_name` varchar(255) NOT NULL DEFAULT '' COMMENT '散仙名字',
                `fighter_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '散仙等级',
                `fighter_quality` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '散仙品质',
                `opt_type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型1',
                `opt_detail` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型2',
                `opt_result` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '操作结果',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                 KEY `server_player` (`server_id`, `player_id`),
                 KEY `server_player_name` (`server_id`, `player_id`,`fighter_name`),
                 KEY `server_player_type` (`server_id`, `player_id`,`opt_type`)
                
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblHorseLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `horse_name` varchar(255) NOT NULL DEFAULT '' COMMENT '坐骑名字',
                `horse_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '坐骑ID',
                `horse_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '坐骑等级',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                KEY `server_player` (`server_id`, `player_id`),
                KEY `server_player_horse` (`server_id`, `player_id`,`horse_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblTrumpLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `trump_name` varchar(255) NOT NULL DEFAULT '' COMMENT '法宝名字',
                `trump_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '法宝ID',
                `trump_skillid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '法宝技能ID',
                `trump_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '法宝品节',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                `trump_exp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '法宝祭炼值',
                KEY `server_player` (`server_id`, `player_id`),
                KEY `server_player_trump` (`server_id`, `player_id`,`trump_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblBeautyLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `beauty_name` varchar(255) NOT NULL DEFAULT '' COMMENT '美女名字',
                `beauty_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '美女ID',
                `beauty_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT ' 美女等级',
                `beauty_exp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT ' 美女亲密度',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                KEY `server_player` (`server_id`, `player_id`),
                KEY `server_player_trump` (`server_id`, `player_id`,`beauty_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblEquipLog_", nYear, "_", nMonth, "` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `equip_name` varchar(255) NOT NULL DEFAULT '' COMMENT '装备名字',
                `equip_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '装备ID',
                `equip_level` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '装备等级',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '时间',
                KEY `server_player` (`server_id`, `player_id`),
                KEY `server_player_equip` (`server_id`, `player_id`,`equip_id`)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));
        
    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblSendMoneyLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byMoneyType` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '货币类型',
                `dwMoneyValue` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '发送数量',
                `strReason` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送理由',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblSendItemLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strTitle` varchar(255)  NOT NULL DEFAULT '' COMMENT '标题',
                `strBody`  varchar(255)  NOT NULL DEFAULT '' COMMENT '内容',
                `strItemList`  varchar(255)  NOT NULL DEFAULT '' COMMENT '物品列表',
                `strReason` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送理由',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));


    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblMailOpLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byMailOpType` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '邮件操作类型',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblForbiddenLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byOpType` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型',
                `dwForbidTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '封禁时间',
                `strReason` varchar(255)  NOT NULL DEFAULT '' COMMENT '理由',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblForbiddenChatLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byOpType` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型',
                `dwForbidTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '封禁时间',
                `strReason` varchar(255)  NOT NULL DEFAULT '' COMMENT '理由',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblGlobalSendItemLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `dwGold` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '仙石',
                `dwCoupon` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '礼卷', 
                `dwSliver` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '银币', 
                `dwHonor` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '荣誉', 
                `strItemList` varchar(255)  NOT NULL DEFAULT '' COMMENT '物品列表',
                `strReason` varchar(255)  NOT NULL DEFAULT '' COMMENT '理由',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblQuesOptLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byOpType` tinyint(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作类型',
                `wQuestType` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '任务类型',
                `strQuestName` varchar(255)  NOT NULL DEFAULT '' COMMENT '任务名字',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblSendMailLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strTitle` varchar(255)  NOT NULL DEFAULT '' COMMENT '标题',
                `strBody`  varchar(255)  NOT NULL DEFAULT '' COMMENT '内容',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblVIPSendLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strBody`  varchar(255)  NOT NULL DEFAULT '' COMMENT '内容',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));


    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblActivityOpenLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `strActivityName`  varchar(255)  NOT NULL DEFAULT '' COMMENT '活动名称',
                `dwBeginTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '开始时间',
                `dwEndTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '结束时间',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));


    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblDiscountItemLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byType` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '类型',
                `dwBegomTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '开始时间',
                `dwEndTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '结束时间',
                `strItemList`  varchar(255)  NOT NULL DEFAULT '' COMMENT '物品列表',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

    CALL ExecSQL(CONCAT("
            CREATE TABLE IF NOT EXISTS `tblLevelChangeLog_", nYear, "_", nMonth, "` (
                `LogID` int(11) UNSIGNED NOT NULL auto_increment, 
                `strSendName` varchar(255)  NOT NULL DEFAULT '' COMMENT '发送人',
                `byStatus` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT '状态',
                `dwServerId` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '大区',
                `qwUserId` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
                `byLevel` tinyint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'byLevel',
                `dwOpTime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '操作时间',
                 PRIMARY KEY(LogID)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
                "));

END$$

DROP PROCEDURE IF EXISTS OnDBStartup$$
CREATE PROCEDURE OnDBStartup ()
BEGIN
    DECLARE tNow DATE;
    DECLARE nYear int;
    DECLARE nMonth int;
    SET tNow = NOW();
    SET nYear = YEAR(tNow);
    SET nMonth = MONTH(tNow);
    CALL CreateLogTables(nYear, nMonth);
    SET tNow = DATE_ADD(tNow, INTERVAL 1 MONTH);
    SET nYear = YEAR(tNow);
    SET nMonth = MONTH(tNow);
    CALL CreateLogTables(nYear, nMonth);
    SET tNow = DATE_ADD(tNow, INTERVAL 1 MONTH);
    SET nYear = YEAR(tNow);
    SET nMonth = MONTH(tNow);
    CALL CreateLogTables(nYear, nMonth);
END$$
DELIMITER ;
Call OnDBStartup()
