--
-- Table structure for table `tblroleshenglingprize`
--

CREATE TABLE `tblroleshenglingprize` (
      `qwRoleID` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
      `wItemID`  int(10) NOT NULL DEFAULT '0' COMMENT '物品',
      `wNum`     int(10) NOT NULL DEFAULT '0' COMMENT '数量',
      PRIMARY KEY (`qwRoleID`,`wItemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='圣陵奖励信息';

