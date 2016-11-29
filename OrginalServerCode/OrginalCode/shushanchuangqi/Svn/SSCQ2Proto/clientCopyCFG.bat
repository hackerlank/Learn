@echo off 
echo 正在拷贝文件
set /p TARGETPATH= < ClientPath.ini
 
xcopy /e Generated\ActionScript\*.as %TARGETPATH%

echo.&pause