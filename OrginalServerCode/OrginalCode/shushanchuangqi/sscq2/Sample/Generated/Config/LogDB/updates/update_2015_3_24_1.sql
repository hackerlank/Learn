
CALL ExecSQLForTable("alter table ", "tblMoneyCoursesLog_%", "add from_toStr;");
CALL ExecSQLForTable("alter table ", "tblMoneyCoursesLog_%", "add strOpen_id;");
CALL ExecSQLForTable("alter table ", "tblMoneyCoursesLog_%", "add bIsFreeGold;");

CALL ExecSQLForTable("alter table ", "tblItemCoursesLog_%", "add from_toStr;");
CALL ExecSQLForTable("alter table ", "tblItemCoursesLog_%", "add strOpen_id;");
