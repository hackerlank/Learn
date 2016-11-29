export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../ThirdParty/mysql++-3.2.0
./ServerManagerD -x
sleep 2
./ServerManagerD -d
