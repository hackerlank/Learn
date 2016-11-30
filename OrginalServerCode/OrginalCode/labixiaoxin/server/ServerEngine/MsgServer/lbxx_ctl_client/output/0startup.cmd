for /l %%a in (1,1,100) do (
choice /t 1 /d y /n >nul
start /min "" "lbxx_ctl_clientD.exe"
)