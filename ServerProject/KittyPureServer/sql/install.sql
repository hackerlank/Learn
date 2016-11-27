DROP TABLE IF EXISTS `t_charbase`;
CREATE TABLE `t_charbase` (
    `f_charid` bigint(20) NOT NULL DEFAULT '0',
    `f_account` varchar(50) NOT NULL DEFAULT '',
    `f_email` varchar(50) NOT NULL DEFAULT '',
    `f_phonenum` varchar(50) NOT NULL DEFAULT '',
    `f_createtime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_onlinetime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_offlinetime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_allbinary` blob,
    PRIMARY KEY (`f_charid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `t_serverlist`(
    `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
    `TYPE` int(10) unsigned NOT NULL DEFAULT '0',
    `NAME` varchar(32) NOT NULL DEFAULT '',
    `IP` varchar(16) NOT NULL DEFAULT '127.0.0.1',
    `PORT` int(10) unsigned NOT NULL DEFAULT '0',
    `EXTIP` varchar(16) NOT NULL DEFAULT '127.0.0.1',
    `EXTPORT` int(10) unsigned NOT NULL DEFAULT '0',
    `NETTYPE` int(10) unsigned NOT NULL DEFAULT '0',
    `DBTABLE` varchar(100) NOT NULL DEFAULT '',
    PRIMARY KEY (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=2204 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_version`;
CREATE TABLE `t_version` (
    `f_updatetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `f_version` int(10) unsigned NOT NULL DEFAULT '0',
    KEY `index_time` (`f_updatetime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_recordbinary`;
CREATE TABLE IF NOT EXISTS `t_recordbinary`(
    `f_allbinary` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
