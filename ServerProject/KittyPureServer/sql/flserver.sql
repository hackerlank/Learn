DROP TABLE IF EXISTS `account_zone`;
CREATE TABLE `account_zone` (
  `account` varchar(24) NOT NULL DEFAULT '',
  `phonenum` varchar(24) NOT NULL DEFAULT '',
  `email` varchar(24) NOT NULL DEFAULT '',
  `passwd` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`phonenum`,`email`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_zone`;
CREATE TABLE IF NOT EXISTS `t_zone` (
  `game` int(10) unsigned NOT NULL DEFAULT '0',
  `zone` int(10) unsigned NOT NULL DEFAULT '0',
  `zoneType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ip` varchar(100) NOT NULL DEFAULT '',
  `port` smallint(5) unsigned NOT NULL DEFAULT '0',
  `name` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`game`,`zone`),
  UNIQUE KEY `ip_port` (`ip`,`port`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

