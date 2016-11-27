#flyer   2016-05-08 服务器数据表
CREATE TABLE IF NOT EXISTS t_serverinfo
(
    `id` BIGINT(20) UNSIGNED NOT NULL,
    `servertype` BIGINT(20) UNSIGNED NOT NULL,
    `ip` varchar(20) NOT NULL,
    `port` BIGINT(20) UNSIGNED NOT NULL,
    `name` varchar(20) NOT NULL,
    PRIMARY KEY(id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#flyer   201605-05-08 登录服务器数据表
CREATE TABLE IF NOT EXISTS t_logininfo
(
    `id` BIGINT(20) UNSIGNED NOT NULL,
    `servertype` BIGINT(20) UNSIGNED NOT NULL,
    `ip` varchar(20) NOT NULL,
    `port` BIGINT(20) UNSIGNED NOT NULL,
    `areaname` varchar(20) NOT NULL,
    PRIMARY KEY(id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#flyer   201605-05-29 注册表
CREATE TABLE IF NOT EXISTS t_register
(
    `id` BIGINT(20) UNSIGNED NOT NULL AUTO_INCREMENT,
    `phone` varchar(20) NOT NULL,
    `passwd` varchar(20) NOT NULL,
    `regtime` timestamp not null default current_timestamp,  
    PRIMARY KEY(id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#flyer   201606-07-21 注册表
CREATE TABLE IF NOT EXISTS t_user
(
    `charid` BIGINT(20) UNSIGNED NOT NULL AUTO_INCREMENT,
    `phone` varchar(20) NOT NULL,
    `binary` blob, 
    PRIMARY KEY(charid)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#flyer   201606-07-21 添加外网ip
alter table t_serverinfo add outip varchar(20) NOT NULL;
#flyer   201606-07-21 添加外网端口
alter table t_serverinfo add outport BIGINT(20) UNSIGNED NOT NULL;



