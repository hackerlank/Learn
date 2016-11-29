CREATE  TABLE IF NOT EXISTS `tblrolefighterpassiveskill`(
      `qwOwnerID` BIGINT(20) UNSIGNED NOT NULL COMMENT '拥有者散仙唯一ID' ,
      `qwRoleID` BIGINT(20) UNSIGNED NOT NULL COMMENT '玩家唯一ID' ,
      `dwSkillID` INT(10) UNSIGNED NOT NULL COMMENT '技能ID' ,
      `dwSkillQuality` INT(10) UNSIGNED NOT NULL COMMENT '技能品质' ,
      `dwSkillLevel` INT(10) UNSIGNED NOT NULL COMMENT '技能等级' ,
      PRIMARY KEY (`qwOwnerID`, `dwSkillID`) )
ENGINE = InnoDB
COMMENT = '散仙被动技能';
