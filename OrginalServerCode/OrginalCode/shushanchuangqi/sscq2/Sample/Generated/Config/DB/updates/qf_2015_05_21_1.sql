ALTER TABLE `tblroleequiptrumpdata` ADD COLUMN `dwBlessing` INT(10) UNSIGNED NOT NULL default '0' COMMENT '强化祝福值';
ALTER TABLE `tblroleequiptrumpdata` ADD COLUMN `dwXiLianBlessing`   INT(10) UNSIGNED NOT NULL default '0' COMMENT '洗练祝福值（次数）';
ALTER TABLE `tblroleequiptrumpdata` ADD COLUMN `strRandomAttr` char(255)  NOT NULL default "" COMMENT '洗练属性';
ALTER TABLE `tblroleequiptrumpdata` ADD COLUMN `strReplaceAttr` char(255)  NOT NULL default ""  COMMENT '替换洗练属性(保留不用)';
