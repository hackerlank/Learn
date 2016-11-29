CREATE TABLE `tbllingshanshopbuylog` (
    `qwInstID` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '唯一自增长流水ID',
    `qwGuildID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '帮派唯一ID',
    `wMsgID` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT '日志类型ID',
    `vecString` char(64) NOT NULL DEFAULT '' COMMENT '变量字符',
    `vecParam` char(64) NOT NULL DEFAULT '' COMMENT '变量数值（XX,XX,XX）',
    `dwTime` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '日志时间',
    PRIMARY KEY (`qwInstID`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8 COMMENT='帮派购买日志信息';

