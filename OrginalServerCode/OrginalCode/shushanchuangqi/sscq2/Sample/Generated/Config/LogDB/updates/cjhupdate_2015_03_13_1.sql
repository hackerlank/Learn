ALTER TABLE `tblGuildLog` DROP PRIMARY key;
ALTER TABLE `tblGuildLog` DROP COLUMN `build_type`;
ALTER TABLE `tblGuildLog` DROP COLUMN `build_level`;
ALTER TABLE `tblGuildLog` ADD COLUMN `tower_level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '神谕塔等级';
ALTER TABLE `tblGuildLog` ADD COLUMN `store_level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '仓库等级';
ALTER TABLE `tblGuildLog` ADD COLUMN `hourse_level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '剑阁等级';
ALTER TABLE `tblGuildLog` ADD COLUMN `guild_score`  int(10) NOT NULL DEFAULT '0' COMMENT '积分';
ALTER TABLE `tblGuildLog` ADD PRIMARY key(server_id,guild_id);
