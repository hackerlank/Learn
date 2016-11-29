
--DROP PROCEDURE IF EXISTS AlterTable;
CALL ExecSQLForTable("alter table ", "tblDgnLog%", "drop LogID;");
