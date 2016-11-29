/*
Navicat MySQL Data Transfer

Source Server         : sss
Source Server Version : 50615
Source Host           : localhost:3306
Source Database       : lbxx_db

Target Server Type    : MYSQL
Target Server Version : 50615
File Encoding         : 65001

Date: 2015-07-07 11:25:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `activation_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `activation_tbl`;
CREATE TABLE `activation_tbl` (
  `activation_id` varchar(45) NOT NULL COMMENT '激活码id',
  `flag` int(11) DEFAULT '1' COMMENT '可以领取次数',
  PRIMARY KEY (`activation_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of activation_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `activeness_reward_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `activeness_reward_tbl`;
CREATE TABLE `activeness_reward_tbl` (
  `character_id` int(11) NOT NULL,
  `activeness_point` int(11) NOT NULL,
  `obtain_date` date NOT NULL,
  PRIMARY KEY (`character_id`,`activeness_point`,`obtain_date`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of activeness_reward_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `character_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `character_tbl`;
CREATE TABLE `character_tbl` (
  `user_id` int(11) DEFAULT NULL,
  `name` varchar(45) DEFAULT NULL,
  `coin` int(11) DEFAULT NULL,
  `money` int(11) DEFAULT NULL,
  `last_login_time` int(11) DEFAULT NULL,
  `login_bonus_count` int(11) DEFAULT NULL,
  `login_count` int(11) DEFAULT NULL,
  `create_time` int(11) DEFAULT NULL,
  `property` blob,
  `rank_data` blob,
  `buy_energy_count` int(11) DEFAULT NULL,
  `buy_energy_time` int(11) DEFAULT NULL,
  `character_id` int(11) NOT NULL AUTO_INCREMENT,
  `level` int(11) DEFAULT NULL,
  `equipment_list` blob,
  `energy` int(11) DEFAULT NULL,
  `energy_restore_time` int(11) DEFAULT NULL,
  `exp` int(11) DEFAULT NULL,
  `power_point` int(11) DEFAULT NULL,
  `skill_id` int(11) DEFAULT NULL,
  `recharge_count` int(11) DEFAULT NULL,
  `recharge_amount` int(11) DEFAULT NULL,
  `package_max` int(11) DEFAULT NULL,
  `tutorial_flag` int(11) DEFAULT NULL,
  `use_luck_count` int(11) DEFAULT NULL,
  `vip_level` int(11) DEFAULT NULL,
  `vip_amount` int(11) DEFAULT NULL COMMENT '当前vip阔值',
  `pvp_energy` int(11) DEFAULT NULL,
  `vip_gift` blob COMMENT '已领取vip礼包列表',
  `pvp_energy_restore_time` int(11) DEFAULT NULL,
  `honour` int(11) DEFAULT NULL,
  `flag` int(11) NOT NULL DEFAULT '0',
  `buy_month_card_time` int(11) DEFAULT NULL,
  `gift_bag_code_flag` blob,
  `used_double_drop` blob,
  `changed_date` int(11) DEFAULT '0',
  `friendship` int(11) DEFAULT '0',
  `golden_touch_count` int(11) DEFAULT '0',
  `buy_energy_num` int(11) DEFAULT NULL COMMENT '买体力',
  `bitfield` int(11) DEFAULT NULL COMMENT '特殊标记，首充，分享活动标记',
  `account_flag` int(11) DEFAULT NULL COMMENT '停封解封',
  PRIMARY KEY (`character_id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=1225 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of character_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `character_tmp_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `character_tmp_tbl`;
CREATE TABLE `character_tmp_tbl` (
  `character_id` int(11) NOT NULL,
  `team_info` blob,
  `rank` int(11) DEFAULT NULL,
  `pvp_season` int(11) DEFAULT NULL,
  `pvp_team_info` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of character_tmp_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `config_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `config_tbl`;
CREATE TABLE `config_tbl` (
  `current_pvp_season` int(11) DEFAULT NULL,
  `rank_update_flag` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of config_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `cooldown_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `cooldown_tbl`;
CREATE TABLE `cooldown_tbl` (
  `character_id` int(11) NOT NULL,
  `info` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cooldown_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `count_limit_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `count_limit_tbl`;
CREATE TABLE `count_limit_tbl` (
  `character_id` int(11) NOT NULL,
  `info` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of count_limit_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `dailytak_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `dailytak_tbl`;
CREATE TABLE `dailytak_tbl` (
  `character_id` int(11) NOT NULL,
  `recordDate` int(11) DEFAULT NULL,
  `list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dailytak_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `friend_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `friend_tbl`;
CREATE TABLE `friend_tbl` (
  `character_id` int(11) NOT NULL,
  `max_count` int(11) DEFAULT NULL,
  `invite_list` blob,
  `friend_list` blob,
  `assist_list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of friend_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `function_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `function_tbl`;
CREATE TABLE `function_tbl` (
  `character_id` int(11) NOT NULL,
  `lock_list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of function_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `gift_bag_code_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `gift_bag_code_tbl`;
CREATE TABLE `gift_bag_code_tbl` (
  `gift_bag_code` varchar(32) NOT NULL,
  `gift_bag_type` int(11) NOT NULL,
  `code_type` int(11) NOT NULL,
  `used` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`gift_bag_code`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of gift_bag_code_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `gift_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `gift_tbl`;
CREATE TABLE `gift_tbl` (
  `character_id` int(11) NOT NULL,
  `gift_list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of gift_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `gm_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `gm_tbl`;
CREATE TABLE `gm_tbl` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `from_id` int(11) DEFAULT NULL,
  `from_name` text COMMENT '发送者名字',
  `to_id` int(11) DEFAULT NULL,
  `type` int(11) DEFAULT '0',
  `info` text,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of gm_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `handbook_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `handbook_tbl`;
CREATE TABLE `handbook_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of handbook_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `items_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `items_tbl`;
CREATE TABLE `items_tbl` (
  `character_id` int(11) NOT NULL,
  `idx` int(11) NOT NULL,
  `count` int(11) DEFAULT NULL,
  `info` blob,
  `item_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`character_id`,`idx`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of items_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `limit_activity_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `limit_activity_tbl`;
CREATE TABLE `limit_activity_tbl` (
  `character_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '角色id',
  `limited_id` int(11) NOT NULL DEFAULT '0' COMMENT '限时活动id',
  `closetime` int(11) DEFAULT NULL COMMENT '关闭时间',
  `progress` int(11) DEFAULT NULL,
  `linktype` int(11) DEFAULT NULL COMMENT '关联条件',
  `related_list` blob,
  PRIMARY KEY (`character_id`,`limited_id`)
) ENGINE=MyISAM AUTO_INCREMENT=516 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of limit_activity_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `mail_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `mail_tbl`;
CREATE TABLE `mail_tbl` (
  `mail_id` int(11) NOT NULL,
  `mail_template_id` int(11) NOT NULL,
  `mail_owner_id` int(11) NOT NULL,
  `mail_attachment` blob,
  `mail_title` varchar(24) DEFAULT NULL,
  `mail_body` blob COMMENT '邮件内容',
  `mail_sender` varchar(32) DEFAULT NULL,
  `mail_flag` int(11) NOT NULL DEFAULT '0',
  `mail_timeout` int(11) NOT NULL DEFAULT '0',
  `mail_read_date` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`mail_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of mail_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `map_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `map_tbl`;
CREATE TABLE `map_tbl` (
  `character_id` int(11) NOT NULL,
  `current_map_info` blob,
  `current_reward` blob,
  `flag_list` blob,
  `last_reward_time` int(11) DEFAULT NULL,
  `free_reborn_count` int(11) DEFAULT NULL,
  `last_reborn_time` int(11) DEFAULT NULL,
  `map_gift_list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of map_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `material_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `material_tbl`;
CREATE TABLE `material_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of material_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `moneytree_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `moneytree_tbl`;
CREATE TABLE `moneytree_tbl` (
  `character_id` int(11) NOT NULL,
  `level` int(11) DEFAULT NULL,
  `exp` int(11) DEFAULT NULL,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of moneytree_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `month_card_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `month_card_tbl`;
CREATE TABLE `month_card_tbl` (
  `character_id` int(11) NOT NULL DEFAULT '0' COMMENT '用户id',
  `end_time` int(11) DEFAULT NULL COMMENT '结束时间（这个时间之前30天都有一封）',
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of month_card_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `order_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `order_tbl`;
CREATE TABLE `order_tbl` (
  `order_id` varchar(32) NOT NULL,
  `character_id` int(11) DEFAULT NULL,
  `buy_id` varchar(45) DEFAULT NULL,
  `timestamp` varchar(45) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  PRIMARY KEY (`order_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `player_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `player_tbl`;
CREATE TABLE `player_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  `selected_list` blob,
  `staff` blob,
  `player_skill_list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of player_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `product_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `product_tbl`;
CREATE TABLE `product_tbl` (
  `character_id` int(11) NOT NULL DEFAULT '0',
  `product` blob COMMENT '已经买商品列表',
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of product_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `pvp100_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `pvp100_tbl`;
CREATE TABLE `pvp100_tbl` (
  `character_id` int(11) NOT NULL,
  `opponent` blob,
  `rank_info` blob,
  `opponent_list` blob,
  `max_kill` int(11) DEFAULT '0',
  `ref_times` int(11) DEFAULT '0',
  `team_info` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pvp100_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `pvp_season_tbl0`
-- ----------------------------
DROP TABLE IF EXISTS `pvp_season_tbl0`;
CREATE TABLE `pvp_season_tbl0` (
  `character_id` int(11) NOT NULL,
  `score` int(11) DEFAULT NULL,
  `total` int(11) DEFAULT NULL,
  `win` int(11) DEFAULT NULL,
  `season_id` int(11) DEFAULT NULL,
  `update_time` int(11) DEFAULT NULL,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pvp_season_tbl0
-- ----------------------------

-- ----------------------------
-- Table structure for `pvp_season_tbl1`
-- ----------------------------
DROP TABLE IF EXISTS `pvp_season_tbl1`;
CREATE TABLE `pvp_season_tbl1` (
  `character_id` int(11) NOT NULL,
  `score` int(11) DEFAULT NULL,
  `total` int(11) DEFAULT NULL,
  `win` int(11) DEFAULT NULL,
  `season_id` int(11) DEFAULT NULL,
  `update_time` int(11) DEFAULT NULL,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pvp_season_tbl1
-- ----------------------------

-- ----------------------------
-- Table structure for `pvp_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `pvp_tbl`;
CREATE TABLE `pvp_tbl` (
  `character_id` int(11) NOT NULL,
  `opponent` blob,
  `basic_info` blob,
  `rank_info` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pvp_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `recharge_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `recharge_tbl`;
CREATE TABLE `recharge_tbl` (
  `order_id` varchar(32) NOT NULL COMMENT '订单号',
  `character_id` int(11) DEFAULT NULL COMMENT '用户id',
  `creat_time` int(11) DEFAULT NULL COMMENT '订单创建时间',
  `product_id` int(11) DEFAULT NULL COMMENT '商品id',
  `product_count` int(11) DEFAULT NULL COMMENT '商品数量',
  `deal_time` varchar(32) DEFAULT NULL COMMENT '订单处理时间',
  `money` int(11) DEFAULT NULL COMMENT '金卡数量',
  `rmb` int(11) DEFAULT NULL COMMENT '人民币',
  `channel_id` varchar(16) DEFAULT NULL COMMENT '渠道',
  `state` int(11) DEFAULT NULL COMMENT '状态',
  PRIMARY KEY (`order_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of recharge_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `secret_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `secret_tbl`;
CREATE TABLE `secret_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  `cell_count` int(11) DEFAULT '3',
  `refresh_times` int(11) DEFAULT '0',
  `last_refresh` int(11) DEFAULT '0',
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of secret_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `skill_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `skill_tbl`;
CREATE TABLE `skill_tbl` (
  `character_id` int(11) NOT NULL,
  `skill_list` blob,
  `player_skill_list` blob,
  `player_skill_res` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of skill_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `sms_callback_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `sms_callback_tbl`;
CREATE TABLE `sms_callback_tbl` (
  `callback_id` int(11) NOT NULL AUTO_INCREMENT,
  `cpparam` varchar(45) DEFAULT NULL,
  `code` int(11) DEFAULT NULL,
  `pay_type` varchar(45) DEFAULT NULL,
  `timestamp` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`callback_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of sms_callback_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `statistics_info_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `statistics_info_tbl`;
CREATE TABLE `statistics_info_tbl` (
  `statistics_type` int(11) NOT NULL,
  `record_time` date NOT NULL,
  `digital_data` int(11) NOT NULL,
  `blob_data` blob,
  PRIMARY KEY (`statistics_type`,`record_time`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of statistics_info_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `task_progress_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `task_progress_tbl`;
CREATE TABLE `task_progress_tbl` (
  `character_id` int(11) NOT NULL,
  `task_progress` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of task_progress_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `task_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `task_tbl`;
CREATE TABLE `task_tbl` (
  `character_id` int(11) NOT NULL,
  `task_id` int(11) NOT NULL,
  `progress` int(11) NOT NULL,
  `task_status` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`character_id`,`task_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of task_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `team_rank_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `team_rank_tbl`;
CREATE TABLE `team_rank_tbl` (
  `character_id` int(11) NOT NULL,
  `point` int(11) DEFAULT NULL,
  `update_time` int(11) DEFAULT NULL,
  `team_info` blob,
  `star_count` int(11) DEFAULT '0',
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of team_rank_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `test_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `test_tbl`;
CREATE TABLE `test_tbl` (
  `test_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `aaa` int(11) DEFAULT NULL,
  PRIMARY KEY (`test_id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of test_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `transaction_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `transaction_tbl`;
CREATE TABLE `transaction_tbl` (
  `transaction_id` varchar(45) NOT NULL,
  `purchase_date` varchar(60) DEFAULT NULL,
  `transaction_data` blob,
  `purchase_id` varchar(45) DEFAULT NULL,
  `character_id` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  PRIMARY KEY (`transaction_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of transaction_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `user_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `user_tbl`;
CREATE TABLE `user_tbl` (
  `mac` varchar(45) DEFAULT NULL,
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) DEFAULT NULL,
  `password` varchar(45) DEFAULT NULL,
  `open_id` varchar(130) DEFAULT NULL,
  `open_token` varchar(130) DEFAULT NULL,
  `platform` varchar(45) DEFAULT NULL,
  `channel_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `mac_UNIQUE` (`mac`)
) ENGINE=MyISAM AUTO_INCREMENT=1164 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `weapon_skill_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `weapon_skill_tbl`;
CREATE TABLE `weapon_skill_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  `improve_property` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of weapon_skill_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for `wing_tbl`
-- ----------------------------
DROP TABLE IF EXISTS `wing_tbl`;
CREATE TABLE `wing_tbl` (
  `character_id` int(11) NOT NULL,
  `list` blob,
  PRIMARY KEY (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of wing_tbl
-- ----------------------------

-- ----------------------------
-- Procedure structure for `do_ACU_statistics`
-- ----------------------------
DROP PROCEDURE IF EXISTS `do_ACU_statistics`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `do_ACU_statistics`(IN p_ACU_int INT, IN p_ACU_blob BLOB)
BEGIN
insert into statistics_info_tbl(statistics_type, digital_data, blob_data, record_time) VALUES(7, p_ACU_int, p_ACU_blob, CURRENT_DATE())  ON DUPLICATE KEY UPDATE digital_data=p_ACU_int, blob_data=p_ACU_blob;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `do_creat_user`
-- ----------------------------
DROP PROCEDURE IF EXISTS `do_creat_user`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `do_creat_user`(IN `p_max` int,IN `p_name` int)
BEGIN
	#Routine body goes here...
declare i int;
set i = 569;
repeat
  #insert into user_tbl(mac,user_id,email,password) values (concat("32FEAC98C2F34DAA873990",i+p_name),i,concat(i+p_name,"@qq.com"),"12345678");
	insert into player_tbl(character_id) values(i);
  set i = i + 1;
  until i >= 100000
end repeat;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `do_gm_sys_insert`
-- ----------------------------
DROP PROCEDURE IF EXISTS `do_gm_sys_insert`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `do_gm_sys_insert`(IN `p_from_id` int,IN `p_from_name` int,IN `p_to_id` int,IN `p_type` int,IN `p_info` text)
BEGIN
	#Routine body goes here...
	DELETE FROM gm_tbl WHERE type = p_type;
	INSERT INTO gm_tbl(from_id,from_name,to_id,type,info) VALUES(p_from_id,p_from_name,p_to_id,p_type,p_info);
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `do_limited_activity_select`
-- ----------------------------
DROP PROCEDURE IF EXISTS `do_limited_activity_select`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `do_limited_activity_select`(IN `p_character_id` int,IN `p_time` int)
BEGIN
	#Routine body goes here...
	DELETE FROM limit_activity_tbl WHERE closetime < p_time;
	SELECT limited_id,closetime,progress,linktype,related_list from limit_activity_tbl where character_id=p_character_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `do_login_statistics`
-- ----------------------------
DROP PROCEDURE IF EXISTS `do_login_statistics`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `do_login_statistics`()
BEGIN
  DECLARE p_iAmount INT DEFAULT 0;
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = CURRENT_DATE();
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(1, p_iAmount, CURRENT_DATE());
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 1 DAY);
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(2, p_iAmount, CURRENT_DATE());
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 3 DAY);
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(3, p_iAmount, CURRENT_DATE());
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 7 DAY);
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(4, p_iAmount, CURRENT_DATE());
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 15 DAY);
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(5, p_iAmount, CURRENT_DATE());
  select count(1) into p_iAmount from character_tbl where DATE(FROM_UNIXTIME(last_login_time)) = DATE_ADD(FROM_UNIXTIME(last_login_time),INTERVAL 30 DAY);
  insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(6, p_iAmount, CURRENT_DATE());
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `update_gift_bag_code_flag`
-- ----------------------------
DROP PROCEDURE IF EXISTS `update_gift_bag_code_flag`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `update_gift_bag_code_flag`(IN p_increment_value BLOB, IN p_character_id INT)
BEGIN
  update character_tbl set gift_bag_code_flag=(case when gift_bag_code_flag = '' or gift_bag_code_flag is null then unhex(hex(p_increment_value)) else  concat(unhex(hex(gift_bag_code_flag)), unhex(hex(p_increment_value)) ) end) where character_id = p_character_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Event structure for `e_do_login_statistics`
-- ----------------------------
DROP EVENT IF EXISTS `e_do_login_statistics`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` EVENT `e_do_login_statistics` ON SCHEDULE EVERY 1 DAY STARTS '2015-02-04 00:00:00' ON COMPLETION NOT PRESERVE ENABLE COMMENT 'daily statistics' DO CALL e_do_login_statistics()
;;
DELIMITER ;
