DROP TABLE IF EXISTS `tblmaillog`;

CREATE TABLE  `tblmaillog` (
    `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
    `player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
    `mail_id` bigint(10) unsigned NOT NULL DEFAULT '0' COMMENT '邮件ID',
    `mail_type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件类型',
    `mail_title` varchar(200)  NOT NULL DEFAULT '' COMMENT '邮件标题',
    `mail_text` varchar(10000) NOT NULL DEFAULT '' COMMENT '邮件正文',
    `mail_item` varchar(2000)  NOT NULL DEFAULT '' COMMENT '邮件附件',
    `mail_state` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件状态,0接受,1领取附件,2自己删除,3超时删除',
    `mail_rev_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '接收时间',
    `mail_del_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '删除时间',
    PRIMARY KEY (`player_id`,`mail_id`),
    KEY `server_player` ( `player_id`)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tblGuildLog`;
CREATE TABLE `tblGuildLog` (
                `server_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '服务器ID',
                `guild_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '帮派ID',
                `guild_name` varchar(255) NOT NULL DEFAULT '' COMMENT '帮派名字',
                `guild_level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '帮派等级',
                `member_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '人员数量',
                `guild_money` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '帮派金钱',
                `tower_level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '神谕塔等级',
                `store_level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '仓库等级',
                `hourse_level` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '剑阁等级',
                `guild_score` int(10)    unsigned NOT NULL DEFAULT '0' COMMENT '帮派积分',
                `happened_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
                 PRIMARY KEY (server_id, guild_id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8;


