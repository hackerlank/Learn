@echo on
set NoPause=1

start /b ruby ../Robot.rb 1 20
echo " [r1.bat] completed"
echo " Sleep about 60s" 
for /l %%i in(1,1,5) do ping localhost 1>nul 2>nul
echo "End Sleep"


