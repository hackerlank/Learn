--
-- Table structure for table `tblroleshengling`
--

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

