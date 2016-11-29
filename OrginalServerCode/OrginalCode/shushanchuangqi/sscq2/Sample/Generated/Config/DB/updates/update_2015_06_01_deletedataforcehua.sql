   update tblroledgninfo set dwCompleteTimes = 0, dwFinishTimesToday =0 where dwDgnType >= 203 and dwDgnType <= 299 ; 
    delete from tblrolebattlearray;
    update tblroledata set dwDemonTowerFloorID = 0,dwDemonTowerPrizeFloorID=0;
    delete from  tblrolevars where wVar = 1031 or wVar = 60004;
    update tbldemontower set dwGuardFloorID=0,dwFloorID=0,dwGuardStartTime=0,dwGuardEndTime=0;
    delete from tblcenterdata where wType=4;
    delete from tblcenterdata where wType=5;
    delete from tblroleautostore  where wType=10;
    delete from tblroleautostore  where wType=1;

