@echo on
set NoPause=1
set tool="bin\GenProtocol.exe"
set genroot="Generated"
set package="net.protocol"
for /f "usebackq" %%f in (`dir /b /s XML\*.xml`) do %tool% 0 %%f %genroot%  %package%