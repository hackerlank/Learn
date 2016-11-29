
--DROP PROCEDURE IF EXISTS AlterTable;
CALL ExecSQLForTable("alter table ", "tblTrumpLog_%", "add trump_exp;");
