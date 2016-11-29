CREATE  TABLE IF NOT EXISTS `tblroleequiptrumpdata` (
      `qwInstID` BIGINT(20) UNSIGNED NOT NULL COMMENT '道具唯一ID' ,
      `qwOwnerID` BIGINT(20) UNSIGNED NOT NULL COMMENT '所属散仙ID' ,
      `byIntensifyLvl` TINYINT(3) UNSIGNED NOT NULL COMMENT '强化等级' ,
      `byIntensifyLvlMax` TINYINT(3) UNSIGNED NOT NULL COMMENT '所能达到的最高强化等级' ,
      PRIMARY KEY (`qwInstID`) )
ENGINE = InnoDB
COMMENT = '散仙装备法宝';
