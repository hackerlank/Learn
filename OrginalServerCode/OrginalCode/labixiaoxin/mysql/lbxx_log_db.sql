/*
Navicat MySQL Data Transfer

Source Server         : 192.168.1.12
Source Server Version : 50532
Source Host           : 192.168.1.12:3306
Source Database       : lbxx_log_db

Target Server Type    : MYSQL
Target Server Version : 50532
File Encoding         : 65001

Date: 2015-06-08 15:09:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `log_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `log_tbl`;
CREATE TABLE `log_tbl` (
  `log_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) DEFAULT '0' COMMENT '帐号id',
  `name` varchar(45) DEFAULT NULL COMMENT '角色名',
  `level` int(11) DEFAULT NULL COMMENT '角色等级',
  `channel_id` int(11) DEFAULT NULL COMMENT '渠道id',
  `log_type` int(11) DEFAULT NULL COMMENT '日志等级',
  `goods_id` int(11) DEFAULT NULL COMMENT '装备名称',
  `operate_before` int(11) DEFAULT NULL COMMENT '操作前',
  `operate_after` int(11) DEFAULT NULL COMMENT '操作后',
  `operate_involve` int(11) DEFAULT NULL COMMENT '操作涉及',
  `operate_action` int(11) DEFAULT NULL COMMENT '动作发生原因',
  `operate_way` varchar(45) DEFAULT NULL COMMENT '途径',
  `operate_time` int(11) DEFAULT NULL COMMENT '操作时间',
  PRIMARY KEY (`log_id`)
) ENGINE=MyISAM AUTO_INCREMENT=49347 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of log_tbl
-- ----------------------------
